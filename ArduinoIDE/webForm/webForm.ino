#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WebServer.h>

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
角度<input type = \"text\" name = \"angle\"><br/>\
<input type = \"submit\" name = \"submit\" value = \"提交\">\
</form>\
</body>\
</html>";

String angle = "";

void setup() {
  //串口初始化
  Serial.begin(115200);

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
  Serial.println(server.uri());
  Serial.println(server.arg("angle"));
  server.send(200, "text/html", HTML);
}
