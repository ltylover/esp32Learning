#include <LiquidCrystal.h>

#include <Servo.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WebServer.h>

//定义Lcd1602的连接引脚
const int rs = 22, rw = 23, e = 32, d4 = 2, d5 = 4, d6 = 18, d7 = 19;
LiquidCrystal lcd(rs, rw, e, d4, d5, d6, d7);

//定义舵机对象
Servo lightServo1;
Servo lightServo2;

//定义WIFI名称和密码
const char* ssid = "LightControl";
const char* password = "12345678";

//定义webserver的端口
WebServer server(80); 

//HTML页面
String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<meta charset = \"utf-8\">\
<style> html{text-align:center;}</style>\
<h1>ESP32 Light Control</h1>\
<h2>Light 1 (left)</h2>\
<p><a href =\"/Light1_on\"><button>ON</button></a><a href =\"/Light1_off\"><button>OFF</button></a></p>\
<h2>Light 2 (right)</h2>\
<p><a href =\"/Light2_on\"><button>ON</button></a><a href =\"/Light1_off\"><button>OFF</button></a></p>\
</body>\
</html>";

void setup() {
  //网络功能初始化
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");
  WiFi.softAP(ssid,password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("ESP32 AP IP address:  ");
  Serial.println(myIP);
  Serial.println();

  //舵机初始化
  lightServo1.attach(25);//舵机控制引脚

  //html处理与函数对应
  server.on("/", handle_root);
  server.on("/Light1_on", handle_light1_on);
  server.on("/Light1_off", handle_light1_off);
  server.on("/Light2_on", handle_light2_on);
  server.on("/Light2_off", handle_light2_off);
  

  //lcd1602初始化
  ledcSetup(8, 1, 8);  //设置LEDC通道8频率为1，分辨率为8位，即占空比可选0~255
  ledcAttachPin(25, 8);//pin25输出ledc PWM，与led1602的V0连接
  ledcWrite(8, 90);//占空比为90
  lcd.begin(16, 2);//led1602尺寸
  delay(1000);
  lcd.clear();
  lcd.println(myIP);

  //网络webserver启动
  server.begin();
  Serial.println("HTTP server started");
  delay(100);
}

void loop() {
  server.handleClient(); 
  
//  lcd.setCursor(0, 1);//光标移至第二行第一位
//  lcd.print(millis() / 1000);//倒计时
}

//HTML发送函数
void handle_root() {
  server.send(200, "text/html", HTML);
}
void handle_light1_on(){
//  lightServo1.write(0);
  Serial.println("Light 1 ON");
  server.send(200, "text/html", HTML);
}
void handle_light1_off(){
//  lightServo1.write(0);
  Serial.println("Light 1 OFF");
  server.send(200, "text/html", HTML);
}
void handle_light2_on(){
//  lightServo1.write(0);
  Serial.println("Light 2 ON");
  server.send(200, "text/html", HTML);
}
void handle_light2_off(){
//  lightServo1.write(0);
  Serial.println("Light 2 OFF");
  server.send(200, "text/html", HTML);
}
