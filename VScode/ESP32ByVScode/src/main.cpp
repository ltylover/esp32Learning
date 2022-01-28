#include <Arduino.h>
#define EXT_TSR_MODE 0
//定义外部中断的Mode模式

void interruptEvent()
{
  digitalWrite(2,HIGH);
}
//中断服务函数

void setup() {
  Serial.begin(115200);

  #if 1 == EXT_TSR_MODE
  pinMode(2,OUTPUT);
  pinMode(0,INPUT_PULLUP);
  attachInterrupt(0,interruptEvent,FALLING);//(pin,中断服务函数，IO口引起的电平类型)
    //触发中断事件
  #elif 2 == EXT_TSR_MODE
  
  #endif
}

void loop() {
  #if 1 == EXT_TSR_MODE
    //触发中断事件
  #elif 2 == EXT_TSR_MODE

  #endif

}