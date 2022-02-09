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

//定义所连接的WIFI名称和密码
const char* wifi_network_ssid = "ChinaNet-WUSs";
const char* wifi_network_password = "20001208";

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
  pinMode(2, OUTPUT);
  
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_APSTA);
  WiFi.softAP(soft_ap_ssid, soft_ap_password);
  WiFi.begin(wifi_network_ssid, wifi_network_password);
  while (WiFi.status()!= WL_CONNECTED) {
    delay(500);
    Serial.println("Connect to WiFi...");
  }
  Serial.print("AP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("STA connected IP address: ");
  Serial.println(WiFi.localIP());

  //舵机初始化
  lightServo1.attach(25);//舵机控制引脚
  lightServo2.attach(26);//舵机控制引脚

  //html处理与函数对应
  server.on("/", handle_root);
  server.on("/Light1_on", handle_light1_on);
  server.on("/Light1_off", handle_light1_off);
  server.on("/Light2_on", handle_light2_on);
  server.on("/Light2_off", handle_light2_off);
  
  //lcd1602初始化
  ledcSetup(8, 1, 10);  //设置LEDC通道8频率为1，分辨率为10位，即占空比可选0~1023
  ledcAttachPin(27, 8);//pin27输出ledc PWM，与led1602的V0连接
  ledcWrite(8, 90);//占空比为90
  lcd.begin(16, 2);//led1602尺寸
  delay(1000);
  lcd.clear();
  lcd.println(WiFi.softAPIP());

  //网络webserver启动
  server.begin();
  Serial.println("HTTP server started");
  delay(100);
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
  server.send(200, "text/html", HTML);
}
void handle_light1_off(){
//  lightServo1.write(0);
  Serial.println("Light 1 OFF");
  digitalWrite(2, LOW);
  server.send(200, "text/html", HTML);
}
void handle_light2_on(){
//  lightServo2.write(0);
  Serial.println("Light 2 ON");
  server.send(200, "text/html", HTML);
}
void handle_light2_off(){
//  lightServo2.write(0);
  Serial.println("Light 2 OFF");
  server.send(200, "text/html", HTML);
}
