#include "Exiomatrix.h"

void Setupkeypad() {
    // INITIALIZING columns as outputs
    Mode_EXIO(TCA9554_EXIO1, 0);  // Set EXIO1 as 0
    Mode_EXIO(TCA9554_EXIO2, 0);  // Set EXIO2 as 0
    Mode_EXIO(TCA9554_EXIO3, 0);  // Set EXIO3 as 0
    Mode_EXIO(TCA9554_EXIO4, 0);  // Set EXIO4 as 0
    Mode_EXIO(TCA9554_EXIO5, 0);  // Set EXIO5 as output

    // INITIALIZING rows as inputs
    pinMode(3, INPUT);   // Row 1
    pinMode(4, INPUT);   // Row 2
    pinMode(7, INPUT);   // Row 3
    pinMode(14, INPUT);  // Row 4
    pinMode(8, INPUT);   // Row 5
    pinMode(15, INPUT);  // Row 6
    pinMode(18, INPUT);  // Row 7
    pinMode(19, INPUT);  // Row 8
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
    for (int i = 0; i < 1; i++) {  // Only 1 row defined in hexaKeys
        for (int j = 0; j < 5; j++) {  // Check all 5 columns
            if (Read_EXIO(TCA9554_EXIO1 + j) == 0) {  // Assuming LOW means button press
                return hexaKeys[i][j];  // Return the pressed key
            }
        }
    }
    return '0';  // Default return value if no key is pressed
}
