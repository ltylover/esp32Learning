#include <Arduino.h>

#define EXT_TSR_MODE 0
//定义外部中断的Mode模式

void interruptEvent()
{
  digitalWrite(2,HIGH);
}
//中断事件内容

void setup() {
  Serial.begin(115200);


#if 0 == EXT_TSR_MODE
  pinMode(2,OUTPUT);
  pinMode(0,INPUT_PULLUP);
  attachInterrupt(0,interruptEvent,FALLING);
    //触发中断事件
#elif 1 == EXT_TSR_MODE
  
#endif

}

void loop() {
  #if 0 == EXT_TSR_MODE
    //触发中断事件
  #elif 1 == EXT_TSR_MODE

  #endif

  digitalWrite(2,HIGH);

}