

#include "TCA9554PWR.h"

void setup() {
  TCA9554PWR_Init(0x00);             // Initialize TCA9554PWR, all pins as output by default
  Serial.begin(9600);                // Begin Serial communication

  Mode_EXIO(5, 1);       // Configure pin 6 (EXIO) as input (button pin)
  pinMode(21, OUTPUT);                // Configure pin 7 (GPIO) as output
  digitalWrite(21, LOW);              // Set pin 7 to LOW (simulate ground for button)
}

void loop() {
  // Read the button state from pin 6 (EXIO)
  int buttonState = Read_EXIO(5);  // Read from EXIO pin 6

  // Print the state of pin 6 (EXIO) and pin 7 (GPIO)
  Serial.println(buttonState);       // Print the state of pin 6 (button)
  Serial.println(digitalRead(21));    // Print the state of pin 7 (simulated ground)

  if (buttonState == 1) {            // Button not pressed
    Serial.println("you are fat");
  } else {                           // Button pressed
    Serial.println("button is being touched");
  }

  delay(200);                        // Debounce delay to stabilize input readings
}
