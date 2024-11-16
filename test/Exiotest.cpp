
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Fonts/FreeSerifBold9pt7b.h>

#include "TCA9554PWR.h"

void setup() {
  TCA9554PWR_Init(0x00);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 while(Read_EXIO(TCA9554_EXIO6)==1){
  Serial.println("you are fat");
 }
  Serial.println("button is being touched");
}
