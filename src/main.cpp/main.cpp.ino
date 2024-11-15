#include "DisplayInit.h"  // Ensure the correct path

void setup() {
  TCA9554PWR_Init(0x00); 
  setupDisplay();  // Initialize displays and setup the initial screen
}

void loop() {
    // Call the current page function
    (*pages[currentpage])();

    // Increment the page index
    if (currentpage >= 3) {
        currentpage = 0;  // Reset to the first page (Startup)
    }
}
