#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(25);
  Serial.begin(115200);
  delay(1000);
  myServo.write(0);
//  myServo.writeMicroseconds(1300); 
}

void loop() {
}
