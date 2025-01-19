
#include "TCA9554PWR.h"
#include "Exiomatrix.h"
#include <Arduino.h>
// Define row and column pins
const int rowpins[] = {6, 14, 15,8, 19,20,21};

const int colpins[] = {1,2,3,4,5};


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
void SetupButtons() {
   TCA9554PWR_Init(0x01);
  // Initialize columns as inputs with pull-up resistors

    pinMode(rowpins[0], OUTPUT);
    digitalWrite(rowpins[0], LOW); // Set rows LOW initially
  
}

// Function to scan the keypad matrix
  

char ButtonLoop() {
    for (int row = 1; row < 2; row++) { // Iterate over rows
        for (int col = 0; col < 5; col++) { // Scan columns
            int buttonState = Read_EXIO(colpins[col]); // Read column state
            printf("Row: %d, Col: %d, Button State: %d\n", row, col, buttonState);
            if(buttonState==0){
              return hexaKeys[row][col];
            }
        }
        ButtonLoop(); //done
        
    }

    return '\0'; // Return default value for now
}

