int ADC_PIN = 34;
int timeDelay = 500;

int ADC_read = 0;
int ADC_counter = 0;
int ADC_flag = 0;


unsigned long ADC_timer1 = 0;
unsigned long ADC_timer2 = 0;

void setup() {
  Serial.begin(115200);

  pinMode(ADC_PIN, INPUT);
}

void loop() {
  ADC_read = analogRead(ADC_PIN);
//  Serial.println(ADC_read);
  ADC_timer2 = millis();
  if(ADC_read == 0 && ADC_flag == 0){
    ADC_timer1 = millis();
    ADC_flag = 1;
    ADC_counter ++;
    Serial.println(ADC_counter);
  }
  if( ADC_timer2 > (ADC_timer1 + timeDelay)){
    ADC_flag = 0;
  }
}
