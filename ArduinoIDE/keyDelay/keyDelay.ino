#define sw1 13
#define led1 2
unsigned long X;
unsigned long Y;


void IRAM_ATTR ZD() {
  X = millis();//定时1毫秒送给变量X
  Serial.println(X);
  if( (Y+500) < X ){
    if(digitalRead(led1) == LOW){
      digitalWrite(led1,HIGH);
      Serial.println("led1 ON");
      Y = millis();
    }
    else{
      digitalWrite(led1,LOW);
      Serial.println("led1 OFF");
      Y = millis();
    }
  }
  Serial.println(Y);
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  Serial.println("led1 SET");
  pinMode(led1,OUTPUT);
  pinMode(sw1,INPUT_PULLUP);
  digitalWrite(led1,LOW);
  attachInterrupt(sw1,ZD,FALLING);
  Y = millis();
}
void loop() {
//  Serial.println("led1 WAIT");
  delay(100);
}
