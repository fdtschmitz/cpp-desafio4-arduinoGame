#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define CONTROLLER_PIN A0

// Define the voltage thresholds for different buttons
#define BUTTON_UP_THRESHOLD 166
#define BUTTON_DOWN_THRESHOLD 0
#define BUTTON_LEFT_THRESHOLD 31
#define BUTTON_RIGHT_THRESHOLD 87
#define BUTTON_START_THRESHOLD 351

// Define pill constants
#define PILL_SIZE 2
#define NUM_PILLS 5

// Initialize the OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pacman position variables
int pacmanX = SCREEN_WIDTH / 2;
int pacmanY = SCREEN_HEIGHT / 2;

// Pill positions
int pillX[NUM_PILLS];
int pillY[NUM_PILLS];

// Flag to track if pill is eaten
bool pillEaten[NUM_PILLS];

void setup() {
  // Initialize the display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

  // Initialize pill positions and status
  for (int i = 0; i < NUM_PILLS; i++) {
    pillX[i] = random(SCREEN_WIDTH - PILL_SIZE);
    pillY[i] = random(SCREEN_HEIGHT - PILL_SIZE);
    pillEaten[i] = false;
  }
}

void loop() {
  // Clear the display
  display.clearDisplay();

  // Read the analog voltage from the controller pin
  int controllerValue = analogRead(CONTROLLER_PIN);

  // Determine the button action based on the analog voltage
  if (controllerValue < BUTTON_UP_THRESHOLD && pacmanY > 0) {
    pacmanY--;
  } else if (controllerValue < BUTTON_DOWN_THRESHOLD && pacmanY < SCREEN_HEIGHT - 1) {
    pacmanY++;
  } else if (controllerValue < BUTTON_LEFT_THRESHOLD && pacmanX > 0) {
    pacmanX--;
  } else if (controllerValue < BUTTON_RIGHT_THRESHOLD && pacmanX < SCREEN_WIDTH - 1) {
    pacmanX++;
  } else if (controllerValue < BUTTON_START_THRESHOLD) {
    // Perform the start button action here
  }

  // Draw Pacman on the display
  display.fillCircle(pacmanX, pacmanY, 4, SSD1306_WHITE);

  // Check for collision with pills
  for (int i = 0; i < NUM_PILLS; i++) {
    if (!pillEaten[i]) {
      // Check if Pacman collides with a pill
      if (pacmanX >= pillX[i] - PILL_SIZE && pacmanX <= pillX[i] + PILL_SIZE &&
          pacmanY >= pillY[i] - PILL_SIZE && pacmanY <= pillY[i] + PILL_SIZE) {
        // Pacman ate the pill
        pillEaten[i] = true;
      } else {
        // Draw the pill on the display
        display.fillRect(pillX[i] - PILL_SIZE, pillY[i] - PILL_SIZE, PILL_SIZE * 2, PILL_SIZE * 2, SSD1306_WHITE);
      }
    }
  }

  // Display the updated image
  display.display();
}
