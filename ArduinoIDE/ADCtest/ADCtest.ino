//ADC
const int ADC_PIN1  = 34;
const int ADC_PIN2  = 35;
const int timeDelay = 500;
int ADC_read1 = 0;
int ADC_read2 = 0;
int ADC_counter = 0;
int ADC_flag = 0;
unsigned long ADC_timer1 = 0;
unsigned long ADC_timer2 = 0;

//ledcPWM波
const int ledc_PIN        = 25;     //设置LEDCPWM波的输出引脚
const int ledc_channel    = 8;      //设置LEDC通道
const int ledc_frequency  = 1000;   //设置LEDC频率,单位Hz
const int ledc_resolution = 10;     //设置LEDC分辨率
const int ledc_dutyBasis  = 500;    //设置LEDC基础占空比，为最大值为2的分辨率次方的一半
int ledc_duty = ledc_dutyBasis;    //设置LEDC占空比，最大值为2的分辨率次方

void setup() {
  Serial.begin(115200);

  pinMode(ADC_PIN1, INPUT);
  pinMode(ADC_PIN2, INPUT);

  ledcSetup(ledc_channel, ledc_frequency, ledc_resolution);  //设置LEDC通道8频率为1000Hz，分辨率为10位，即占空比可选0~1024
  ledcAttachPin(ledc_PIN, ledc_channel);                     //pin25输出ledc PWM，与led1602的V0连接
  ledcWrite(ledc_channel,ledc_duty);                         //占空比为ledc_duty，会影响显示的对比度
}

void loop() {
  ADC_read1 = analogRead(ADC_PIN1);
  ADC_read2 = analogRead(ADC_PIN2);
  ADC_timer2 = millis();
  if(ADC_read1 == 0 && ADC_flag == 0){
    ADC_timer1 = millis();
    ADC_flag = 1;
    ADC_counter ++;
    Serial.println(ADC_counter);

    ledc_duty = ledc_dutyBasis + ADC_counter * 10;
    if(ledc_duty > 1000){
      ledc_duty = 1000;
    }
    ledcWrite(ledc_channel,ledc_duty);
    Serial.println(ledc_duty);
  }
  if(ADC_read2 == 0 && ADC_flag == 0){
    ADC_timer1 = millis();
    ADC_flag = 1;
    ADC_counter--;
    Serial.println(ADC_counter);

    ledc_duty = ledc_dutyBasis + ADC_counter * 10;
    if(ledc_duty < 0){
      ledc_duty = 0;
    }
    ledcWrite(ledc_channel,ledc_duty);
    Serial.println(ledc_duty);
  }
  if( ADC_timer2 > (ADC_timer1 + timeDelay)){
    ADC_flag = 0;
  }
}
