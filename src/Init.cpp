#include "Init.h"
Adafruit_ST7735  tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void initfunction(){
    TCA9554PWR_Init(0x00); //initialises the gpio expander
    delay(1000);
    //initialises the screen display
    tft.initR(INITR_BLACKTAB);
    tft.setFont(&FreeSerifBold9pt7b);
    tft.setRotation(3);
    tft.fillScreen(ST7735_WHITE);
    tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
    tft.setTextSize(1);
    delay(200);
    Serial.begin(9600);
}

void cleanscreen(){
    tft.fillScreen(ST7735_WHITE);
}