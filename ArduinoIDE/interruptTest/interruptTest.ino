#define sw1 13
#define led1 2

void IRAM_ATTR ZD() {
  if(digitalRead(led1) == LOW){
    digitalWrite(led1,HIGH);
    Serial.println("led1 ON");
  }
  else{
    digitalWrite(led1,LOW);
    Serial.println("led1 OFF");
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("led1 SET");
  pinMode(led1,OUTPUT);
  pinMode(sw1,INPUT_PULLUP);
  digitalWrite(led1,LOW);
  attachInterrupt(sw1,ZD,FALLING);
}
void loop() {
  Serial.println("led1 WAIT");
  delay(100);
}
