#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WebServer.h>

//定义WIFI名称和密码
const char* ssid = "ESP32-WiFi";
const char* password = "12345678";

IPAddress local_IP(192,168,4,10);//IP地址
IPAddress gateway(192,168,4,1);//网关
IPAddress subnet(255,255,255,0);//网络掩码


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_IP,gateway,subnet);
  WiFi.softAP(ssid,password);
  WiFi.softAPsetHostname("LTY");
  Serial.println(WiFi.softAPgetHostname());
  Serial.print("接入点IP地址：");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  Serial.println(WiFi.softAPgetStationNum());
  delay(1000);
}
