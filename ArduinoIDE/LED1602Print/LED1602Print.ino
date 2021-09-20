#include <LiquidCrystal.h>

const int rs = 34, rw = 35, e = 32, d4 = 2, d5 = 4, d6 = 18, d7 = 19;
LiquidCrystal lcd(rs, rw, e, d4, d5, d6, d7);

void setup() {
//  pinMode(25,OUTPUT);
//  analogWrite(25,90);
  ledcSetup(8, 1, 8);  //设置LEDC通道8频率为1，分辨率为10位，即占空比可选0~1023
  ledcAttachPin(25, 8);
  ledcWrite(8, 90);
  lcd.begin(16, 2);
  delay(1000);
  lcd.clear();
  lcd.println("hello, world!");
  
}

void loop() {
//  lcd.setCursor(0, 1);
//  lcd.print(millis() / 1000);
}
