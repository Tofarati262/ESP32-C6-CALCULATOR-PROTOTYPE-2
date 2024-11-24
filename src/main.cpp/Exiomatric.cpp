#include "TCA9554PWR.h"
#include "Exiomatrix.h"

// Define row and column pins
const int rowpins[] = {3, 7, 8, 14, 15, 19,20};
const int numRows = sizeof(rowpins) / sizeof(rowpins[0]); // Calculate number of rows

const int colpins[] = {6, 7, 4, 1, 5};
const int numCols = sizeof(colpins) / sizeof(colpins[0]); // Calculate number of columns


// Define key mapping
char hexaKeys[7][5] = {
    {'C', 'O', 'M', 'B', '='}, // Row 1: Clear, Mode, Recall, Equals
    {'L','(', 'T','F','P'},
    {'7', '8', '9','x','/'},
    {'4', '5', '6','-','+'},
    {'1', '2', '3','A','B'},
    { '0','.','G','N','D'},
    {'S','%','E','#','^'},
};

// Setup function
void settup() {

  // Initialize columns as inputs with pull-up resistors
  Mode_EXIO(colpins[0], 1);
  Mode_EXIO(colpins[1], 1);
  Mode_EXIO(colpins[2], 1);
  Mode_EXIO(colpins[3], 1);
  Mode_EXIO(colpins[4], 1); // Set column pins as inputs
  // Initialize rows as outputs
    pinMode(rowpins[0], OUTPUT);
    digitalWrite(rowpins[0], HIGH); // Set rows LOW initially
    pinMode(rowpins[1], OUTPUT);
    digitalWrite(rowpins[1], HIGH);
    pinMode(rowpins[2], OUTPUT);
    digitalWrite(rowpins[2], HIGH);
    pinMode(rowpins[3], OUTPUT);
    digitalWrite(rowpins[3], HIGH);
    pinMode(rowpins[4], OUTPUT);
    digitalWrite(rowpins[4], HIGH);
    pinMode(rowpins[5], OUTPUT);
    digitalWrite(rowpins[5], HIGH);
    pinMode(rowpins[6], OUTPUT);
    digitalWrite(rowpins[6], HIGH);
   pinMode(rowpins[7], OUTPUT);
    digitalWrite(rowpins[7], HIGH);
}

// Function to scan the keypad matrix
char loopy() {
  settup();
  static bool buttonPressed = false; // Track button press state
  static int lastCol = -1;           // Track last column where a button was pressed

  for (int col = 0; col < numCols; col++) { // Scan columns
    // Configure column pins: set current column as INPUT, others as OUTPUT LOW
    // Scan rows
    for (int row = 0; row <7; row++) { // Only 1 row defined here
      // Read the state of the current column

      digitalWrite(rowpins[row],LOW);
      

      bool isPressed = (Read_EXIO(colpins[col]) == 0);
      

      // Detect state change (from unpressed to pressed)
      if (isPressed && !buttonPressed) {
        buttonPressed = true; // Mark button as pressed
        lastCol = col;        // Save the column where the button was pressed
        Serial.print("Button pressed: ");
        Serial.println(hexaKeys[row][col]);
        delay(50);
        return hexaKeys[row][col]; // Return the pressed key
        
      } else if (!isPressed && buttonPressed && lastCol == col) {
        // Reset button state when released
        buttonPressed = false;
        lastCol = -1;
      }

    }
    settup();
      
  }

  return 'z'; // Return a space if no button is pressed
}