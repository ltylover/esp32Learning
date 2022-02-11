void setup() {
  Serial.begin(115200);
}

void loop() {
  unsigned long X = millis();//定时1毫秒送给变量X
//  unsigned long X = micros();//定时1微秒送给变量X
  Serial.println(X);
}
