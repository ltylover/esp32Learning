#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

//默认地址 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//舵机角度
#define SERVO_0  102 
#define SERVO_45  187 
#define SERVO_90  280 
#define SERVO_135  373 
#define SERVO_180  510 

uint8_t servonum = 0;

void setup() {
  Serial.begin(115200);
  
  pwm.begin();
  pwm.setPWMFreq(50);  // 50HZ更新频率，相当于20ms的周期

  delay(100);
  
  pwm.setPWM(0, 0, SERVO_45);
}

void loop() {

}
