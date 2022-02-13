#include <Servo.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WebServer.h>

//阿里云网络
#define NTP1  "ntp1.aliyun.com"
#define NTP2  "ntp2.aliyun.com"
#define NTP3  "ntp3.aliyun.com"

//定义所连接的WIFI名称和密码
const char* wifi_network_ssid = "MERCURY_0F88";
const char* wifi_network_password = "88592661";

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

//获取时间
void setClock() {
    
  struct tm timeinfo;
    if (!getLocalTime(&timeinfo)){
      //如果获取失败，就开启联网模式，获取时间
      Serial.println("Failed to obtain time");
      WiFi.disconnect(false);
      WiFi.mode(WIFI_MODE_APSTA);//开启网络  
      WiFi.begin(wifi_network_ssid, wifi_network_password);
      while (WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
      }
      configTime(8 * 3600, 0, NTP1, NTP2,NTP3);
      return;
    }
    Serial.println();
    Serial.println(&timeinfo, "%F %T %A"); // 格式化输出:2021-10-24 23:00:44 Sunday
//    Serial.print(asctime(&timeinfo));//默认打印格式：Mon Oct 25 11:13:29 2021
//    WiFi.disconnect(true);
}

void setup() {
  pinMode(2, OUTPUT);
  
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_APSTA);
  WiFi.softAP(soft_ap_ssid, soft_ap_password);
  WiFi.begin(wifi_network_ssid, wifi_network_password);
  Serial.print("Connect to WiFi");
  while (WiFi.status()!= WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("AP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("STA connected IP address: ");
  Serial.println(WiFi.localIP());

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

  // 从网络时间服务器上获取并设置时间，获取成功后芯片会使用RTC时钟保持时间的更新
  configTime(8 * 3600, 0, NTP1, NTP2, NTP3);
  setClock();
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
  setClock();
  server.send(200, "text/html", HTML);
}
void handle_light1_off(){
//  lightServo1.write(0);
  Serial.println("Light 1 OFF");
  digitalWrite(2, LOW);
  setClock();
  server.send(200, "text/html", HTML);
}
void handle_light2_on(){
//  lightServo2.write(0);
  Serial.println("Light 2 ON");
  setClock();
  server.send(200, "text/html", HTML);
}
void handle_light2_off(){
//  lightServo2.write(0);
  Serial.println("Light 2 OFF");
  setClock();
  server.send(200, "text/html", HTML);
}
