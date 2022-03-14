#include <Servo.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WebServer.h>

#include <LiquidCrystal.h>

//定义led1602引脚
const int rs = 22, rw = 23, e = 32, d4 = 5, d5 = 4, d6 = 18, d7 = 19;
LiquidCrystal lcd(rs, rw, e, d4, d5, d6, d7);

//定义自身的WIFI名称和密码
const char *soft_ap_ssid = "ESP32-WiFi";
const char *soft_ap_password = "12345678";

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
<p><a href =\"/Light1_on\"><button>ON</button></a>   <a href =\"/Light1_off\"><button>OFF</button></a></p>\
<h2>Light 2 (right)</h2>\
<p><a href =\"/Light2_on\"><button>ON</button></a>   <a href =\"/Light2_off\"><button>OFF</button></a></p>\
</body>\
</html>";



void setup() {
  Serial.begin(115200);
  
  pinMode(2, OUTPUT);

  ledcSetup(8, 1000, 10);  //设置LEDC通道8频率为1000Hz，分辨率为10位，即占空比可选0~1024
  ledcAttachPin(25, 8);//pin25输出ledc PWM，与led1602的V0连接
  ledcWrite(8,120);//占空比为120，会影响显示的对比度
  lcd.begin(16, 2);//led1602尺寸
  delay(1000);
  lcd.clear();
  
  WiFi.mode(WIFI_AP);
  WiFi.softAP(soft_ap_ssid, soft_ap_password);
  
  Serial.print("Connect to WiFi");
  lcd.print("Connect...");
  
  Serial.println();
  Serial.print("AP address: ");
  Serial.println(WiFi.softAPIP());
  lcd.clear();
  lcd.print(WiFi.softAPIP());

  //html处理与函数对应
  server.on("/", handle_root);
  server.on("/Light1_on", handle_light1_on);
  server.on("/Light1_off", handle_light1_off);
  server.on("/Light2_on", handle_light2_on);
  server.on("/Light2_off", handle_light2_off);

  //网络webserver启动
  server.begin();
  Serial.println("HTTP server started!");
  delay(100);
  lcd.setCursor(0,1);//光标移至第二行第一位
  lcd.print("HTTP OK");
}

void loop() {
  server.handleClient();
}

//HTML发送函数
void handle_root() {
  server.send(200, "text/html", HTML);
}
void handle_light1_on(){
//  lightServo1.write(0);
  Serial.println("Light 1 ON");
  digitalWrite(2, HIGH);
  lcd.setCursor(0,1);//光标移至第二行第一位
  lcd.print(" 1 ON ");
  server.send(200, "text/html", HTML);
}
void handle_light1_off(){
//  lightServo1.write(0);
  Serial.println("Light 1 OFF");
  digitalWrite(2, LOW);
  lcd.setCursor(0,1);//光标移至第二行第一位
  lcd.print(" 1 OFF");
  server.send(200, "text/html", HTML);
}
void handle_light2_on(){
//  lightServo2.write(0);
  Serial.println("Light 2 ON");
  lcd.setCursor(0,1);//光标移至第二行第一位
  lcd.print(" 2 ON");
  server.send(200, "text/html", HTML);
}
void handle_light2_off(){
//  lightServo2.write(0);
  Serial.println("Light 2 OFF");
  lcd.setCursor(0,1);//光标移至第二行第一位
  lcd.print(" 2 OFF");
  server.send(200, "text/html", HTML);
}
