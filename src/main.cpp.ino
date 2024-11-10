#include "diplayinit.h"


void setup() {
    setupDisplay();  // Initialize displays and setup the initial screen
}

void loop() {
    // Call the curresnt page funsction
    (*pages[currentpage])();

    // Increment the page index
    
    // Loop back to the first page when the end is reached
    if (currentpage >= 3) {
        currentpage = 0;  // Reset to the first page (Startup)
    }
}
