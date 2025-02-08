#include "DisplayInit.h"  // Ensure the correct path


void setup() {
  TCA9554PWR_Init(0x00); 
    setCpuFrequencyMhz(80);
  setupDisplay();  // Initialize displays and setup the initial screen
}

void loop() {
    // Call the current page function
    (*pages[*currentpageptr])();

    // Increment the page index
    if (*currentpageptr >= 3) {
        *currentpageptr = 0;  // Reset to the first page (Startup)
    }
}
