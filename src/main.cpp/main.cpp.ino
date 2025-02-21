#include "DisplayInit.h"  // Ensure the correct path
#include "ArithmeticStack.h"
#include "Exiomatrix.h"
#include <iostream>
#include "CursorFunctions.h"
#include "TCA9554PWR.h"
#include <vector>

RTC_DATA_ATTR int currentpage = 0;

int *currentpageptr = &currentpage;



void setup() {
    TCA9554PWR_Init(0x00); 
    setCpuFrequencyMhz(100);
    setupDisplay();  // Initialize displays and setup the initial screen
    esp_sleep_enable_timer_wakeup(10* 1000000); // No timer, stays asleep indefinitely
}




void loop() {
    if (*currentpageptr < 2) {
        (*pages[*currentpageptr])();
    }

    if (*currentpageptr == 2) {
       calcrun();
    }
}
