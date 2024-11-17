#include "TCA9554PWR.h"
#include "Exiomatrix.h"

const int rowpins[]={3,4,7,14,8,15,19};
const int numRows = sizeof(rowpins) / sizeof(rowpins[0]);  // Calculate number of rows


const int colpins[]={6,7,4,1,5};
const int numCols = sizeof(colpins) / sizeof(colpins[0]);  // Calculate number of rows

  char hexaKeys[1][5] = {
        {'C', 'O', 'M', 'R', '='}  // Row 1: Clear, Mode, Recall, Equals

  };

void settup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 baud rate

    for(int x = 0; x < numCols + 1;x++){
        Mode_EXIO(colpins[x],1);
    }
    // INITIALIZING rows as OUTPUTS
    for(int x = 0; x < numRows + 1;x++){
      pinMode(rowpins[x],OUTPUT);
      digitalWrite(rowpins[x],LOW);
    }
}

char loopy() {
  settup();

   // Scan through columns (assuming 5 columns defined here)
   for (int col = 0; col < numCols; col++) {  // Scan columns
          // Allow signal to stabilize
only allow column it loops to be input and set others as output
        for (int row = 0; row < 1; row++) {  // Only 1 row defined here
            Serial.print("Scanning col ");
            Serial.print(col);
            Serial.print(", Col state:");
            Serial.print(Read_EXIO(colpins[col]));
            Serial.print(", Scanning row ");
            Serial.print(row);
            Serial.print(", R0W state:");
            Serial.println(digitalRead(rowpins[0]));

          if(Read_EXIO(colpins[col])!=1 ){
            return hexaKeys[row][col];
          }
        }
        delay(200);

  }
  return' ';
}