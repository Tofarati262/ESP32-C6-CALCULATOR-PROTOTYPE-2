#ifndef INIT_H
#define INIT_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Fonts/FreeSerifBold9pt7b.h>
#include "TCA9554PWR.h"
#include <WString.h>
#include "Arduino.h"

#define TFT_CS 16  // FSPICS0
#define TFT_RST 3 
#define TFT_DC 17  
#define TFT_MOSI 7 //fspid
#define TFT_SCLK 6 //fpsiclk
#define potPin 4
#define buttonPin 5
#define minPotValue 500
#define maxPotValue 4095
int  mappedValue = 0;
extern void initfunction();
extern void cleanscreen();
extern int mappedValue;  // Declare mappedValue





#endif 