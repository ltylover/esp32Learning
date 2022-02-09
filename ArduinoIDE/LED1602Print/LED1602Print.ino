#include <LiquidCrystal.h>

const int rs = 22, rw = 23, e = 32, d4 = 2, d5 = 4, d6 = 18, d7 = 19;
LiquidCrystal lcd(rs, rw, e, d4, d5, d6, d7);

void setup() {
//  pinMode(25,OUTPUT);
//  analogWrite(25,90);
  ledcSetup(7, 1, 8);  //设置LEDC通道8频率为1，分辨率为8位，即占空比可选0~255
  ledcAttachPin(25, 8);//pin25输出ledc PWM，与led1602的V0连接
  ledcWrite(8, 90);//占空比为90
  lcd.begin(16, 2);//led1602尺寸
  delay(1000);
  lcd.clear();
  lcd.println("hello, world!");
  
}

void loop() {
  lcd.setCursor(0, 1);//光标移至第二行第一位
  lcd.print(millis() / 1000);//倒计时
}
