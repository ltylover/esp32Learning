#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WebServer.h>

//默认地址 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//舵机角度 min:102 max:510
#define SERVO_0  102 
#define SERVO_45  187 
//#define SERVO_90  280 
//#define SERVO_135  373 
//#define SERVO_180  510 

String servo0State = "待机";
String servo1State = "待机";
String servo2State = "待机";

const char* ssid = "ESP32";
const char* password = "12345678";

WebServer server(80); 

String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<meta charset = \"utf-8\">\
<style> html{text-align:center;}</style>\
<h1>ESP32 Web Server</h1>\
<p>SERVO 0 - " + servo0State + "</p>\
<p><a href =\"/servo0_0\"><button>0度</button></a></p>\
<p><a href =\"/servo0_45\"><button>45度</button></a></p>\
<p>SERVO 1 - " + servo1State + "</p>\
<p><a href =\"/servo1_0\"><button>0度</button></a></p>\
<p><a href =\"/servo1_45\"><button>45度</button></a></p>\
<p>SERVO 2 - " + servo2State + "</p>\
<p><a href =\"/servo2_0\"><button>0度</button></a></p>\
<p><a href =\"/servo2_45\"><button>45度</button></a></p>\
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
  server.on("/servo0_0",handle_servo0_0);
  server.on("/servo0_45",handle_servo0_45);
  server.on("/servo1_0",handle_servo1_0);
  server.on("/servo1_45",handle_servo1_45);
  server.on("/servo2_0",handle_servo2_0);
  server.on("/servo2_45",handle_servo2_45);  

  server.begin();
  Serial.println("HTTP server started");

  delay(100);
}

void loop() {
  server.handleClient();
}

void handle_root() {
  server.send(200, "text/html", HTML);
}
void handle_servo0_0(){
  pwm.setPWM(0, 0, SERVO_0);
  servo0State = "0";
  server.send(200, "text/html", HTML);
}
void handle_servo0_45(){
  pwm.setPWM(0, 0, SERVO_45);
  servo0State = "45";
  server.send(200, "text/html", HTML);
}
void handle_servo1_0(){
  pwm.setPWM(1, 0, SERVO_0);
  servo1State = "0";
  server.send(200, "text/html", HTML);
}
void handle_servo1_45(){
  pwm.setPWM(1, 0, SERVO_45);
  servo1State = "45";
  server.send(200, "text/html", HTML);
}
void handle_servo2_0(){
  pwm.setPWM(2, 0, SERVO_0);
  servo2State = "0";
  server.send(200, "text/html", HTML);
}
void handle_servo2_45(){
  pwm.setPWM(2, 0, SERVO_45);
  servo2State = "45";
  server.send(200, "text/html", HTML);
}
