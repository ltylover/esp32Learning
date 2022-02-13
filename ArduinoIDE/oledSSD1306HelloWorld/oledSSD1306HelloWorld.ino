#include "SSD1306.h"

#include <Wire.h>

SSD1306 display(0x7A, 21, 22); 

void setup() {
  Serial.begin(115200);
  pinMode(14,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  digitalWrite(14,LOW);
  delay(500);
  digitalWrite(14,HIGH);
  display.init();

  display.setFont(ArialMT_Plain_24);
  display.drawString(0,0,"hello world!");
  Serial.println("hello world!");
  display.display();
  
}
void loop() {
}
