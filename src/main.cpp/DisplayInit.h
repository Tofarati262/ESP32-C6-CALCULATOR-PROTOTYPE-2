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
#define  minPotValue 0
#define maxPotValue  3260

// Button and potentiometer configuration


extern int mappedValue;
extern int lastMappedValue;
extern int currentpage;
extern int screencount;


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
extern bool calcenginerun;

struct MenuItem {
    const char* name;
    int x, y;
};


class Potentiometer
{
private:
  
public:
  int getPotValue()
  {
    int potValue = analogRead(potPin);  // Read potentiometer
      if (potValue < minPotValue) {
        mappedValue = 0;
      } else {
        mappedValue = map(potValue, minPotValue, maxPotValue, 10, 360);
    }

    return mappedValue;

  }

};

#endif // DISPLAY_INIT_H
