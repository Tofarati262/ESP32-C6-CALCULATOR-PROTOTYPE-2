#ifndef DISPLAY_INIT_H
#define DISPLAY_INIT_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Fonts/FreeSerifBold9pt7b.h>
#include "TCA9554PWR.h"

// Pin definitions
#define TFT_CS 16
#define TFT_RST 3
#define TFT_DC 17
#define TFT_MOSI 7
#define TFT_SCLK 6

#define buttonPin  1
#define potPin  4 //pin declaration
#define  minPotValue 500
#define maxPotValue  4095

// Button and potentiometer configuration


extern uint16_t mappedValue;
extern uint16_t lastMappedValue;
extern uint8_t currentpage;
extern uint8_t screencount;


// Array of function pointers for page handling
extern void (*pages[])(); // Declare as extern, define in DisplayInit.cpp

// Display objects
extern Adafruit_ST7735 tft;

// Function declarations
extern void setupDisplay();
extern void Startup();
extern void knob();
extern void button();
extern void drawmenu();
extern void calcengine();
extern void cleanscreen();

#endif // DISPLAY_INIT_H
