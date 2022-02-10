#define sw1 13
#define led1 2

int ledStatus = 0;

void IRAM_ATTR ZD() {
  if(ledStatus % 2 == 0){
    digitalWrite(led1,HIGH);
    Serial.println("led1 ON");
    ledStatus = 1;
  }
  else{
    digitalWrite(led1,LOW);
    Serial.println("led1 OFF");
    ledStatus = 0;
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("led1 SET");
  pinMode(led1,OUTPUT);
  pinMode(sw1,INPUT);
  digitalWrite(led1,LOW);
  attachInterrupt(sw1,ZD,FALLING);
}

void loop() {
  Serial.println("led1 WAIT");
}
