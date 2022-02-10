#include <OLEDDisplay.h>
#include <OLEDDisplayFonts.h>
#include <OLEDDisplayUi.h>
#include <SSD1306Spi.h>

#include <Wire.h>

SSD1306Spi display(0, 2, 14);  // RES, DC, CS

void setup() {
  display.init();

  display.setFont(ArialMT_Plain_24);
  display.drawString(0,0,"hello world!");
  display.display();
  
}
void loop() {
}
