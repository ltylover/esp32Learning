#include <Servo.h>

Servo myServo;
int angle = 0;

void setup() {
  myServo.attach(35);
  Serial.begin(115200);
  delay(1000);
  myServo.write(30);
}

void loop() {
  angle = myServo.read();
  Serial.println(angle);
}
