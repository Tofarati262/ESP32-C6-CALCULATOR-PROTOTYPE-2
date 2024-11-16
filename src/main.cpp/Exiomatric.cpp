#include "esp32-hal-gpio.h"
#include "Exiomatrix.h"

const int rowpins[]={3,4,7,14,8,15,19};
const int numRows = sizeof(rowpins) / sizeof(rowpins[0]);  // Calculate number of rows


const int colpins[]={1,2,3,4,5};
const int numCols = sizeof(colpins) / sizeof(colpins[0]);  // Calculate number of rows


void Setupkeypad() {
    // INITIALIZING columns as INPUTS
    for(int x = 0; x < numCols;x++){
        Mode_EXIO(colpins[x],1);
    }
    // INITIALIZING rows as OUTPUTS
    for(int x = 0; x < numRows;x++){
      pinMode(rowpins[x],OUTPUT);
      digitalWrite(rowpins[x],LOW);
    }
}

char Scankeypad() {
    // Define the keypad keys layout (1 row, 5 columns)

    char hexaKeys[1][5] = {
        {'C', 'O', 'M', 'R', '='}  // Row 1: Clear, Mode, Recall, Equals
        /* Uncomment and define additional rows if needed:
        {'B', 'L', '(', ')', 'T'},      // Row 2
        {'F', 'P', '7', '8', '9'},      // Row 3
        {'X', '/', 'S', '4', '5'},      // Row 4
        {'6', '+', '-', '^', '1'},      // Row 5
        {'2', '3', 'A', '0', '.'},      // Row 6
        {'G', 'N', 'D', 'Q', 'R'}       // Row 7
        */
    };
    // Scan through columns (assuming 5 columns defined here)
   for (int col = 0; col < numCols; col++) {  // Scan columns
        delay(5);  // Allow signal to stabilize

        for (int row = 0; row < 1; row++) {  // Only 1 row defined here
            Serial.print("Scanning row ");
            Serial.print(row);
            Serial.print(", column ");
            Serial.print(col);
            Serial.print(", Row state: ");
            Serial.print(digitalRead(rowpins[row]));
            Serial.print(", Col state:");
            Serial.println(Read_EXIO(colpins[col]));

            /*if (digitalRead(rowpins[row]) == LOW) {  // Button pressed
                return hexaKeys[row][col];
            }*/
        }
    }

    return '\0';  // Return null character if no key is pressed
}
