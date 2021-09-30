#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WebServer.h>

//默认地址 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//舵机PWM min:102 (0) max:510 (180)

//连接计数器
int counter = 0;

const char* ssid = "ESP32";
const char* password = "12345678";

WebServer server(80); 

String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<meta charset = \"utf-8\">\
<style> html{text-align:center;}</style>\
<h1>ESP32 Web Server</h1>\
<p>SERVO</p>\
<form action = \"#\" method = \"get\">\
通道<input type = \"radio\" name = \"number0\"/>  0  <input type = \"radio\" name = \"number1\"/>  1  <input type = \"radio\" name = \"number2\"/>  2<br/><br/>\
角度<input type = \"text\" name = \"angle\" value = \"0\"/><br/><br/>\
<input type = \"reset\" name = \"reset\" value = \"重置\"/><input type = \"submit\" name = \"submit\" value = \"提交\"/>\
</form>\
</body>\
</html>";

void setup() {
  //串口初始化
  Serial.begin(115200);

  //pwm初始化
  pwm.begin();
  pwm.setPWMFreq(50);  // 50HZ更新频率，相当于20ms的周期
  
  //WiFi初始化
  Serial.println();
  Serial.println("Configuring access point...");
  WiFi.softAP(ssid,password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("ESP32 AP IP address:  ");
  Serial.println(myIP);
  Serial.println();

  server.on("/", handle_root);
  
  server.begin();
  Serial.println("HTTP server started");

  delay(100);
}

void loop() {
  server.handleClient();
}

void handle_root() {
  //串口输出参数
  Serial.println(server.uri());
  
  String switch0 = server.arg("number0");
  String switch1 = server.arg("number1");
  String switch2 = server.arg("number2");
  int number = 0;
  String angleStr = server.arg("angle");
  int angle = angleStr.toInt();
  int anglePWM = (angle*204*1000/90+102*1000)/1000;
  
  if(counter != 0 && switch0 == "on"){
    number = 0; 
  }else if(switch1 == "on"){
    number = 1;
  }else{
    number = 2;
  }

  //限制最大值
  if(angle > 180){
    anglePWM = 510;
  }

  if(angle != 0 && angle != 180){
    anglePWM = 0.915 * anglePWM;
  }

  server.send(200, "text/html", HTML);

  if(counter != 0){
  Serial.println(number);
  Serial.println(anglePWM);
  Serial.println("--------"); 
  pwm.setPWM(number, 0, anglePWM);
  }

  //连接计数器累加
  counter++;
}
