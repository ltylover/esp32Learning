#include <Servo.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WebServer.h>

Servo lightServo;
String servoState = "待机";

const char* ssid = "ESP32";
const char* password = "12345678";

WebServer server(80); 


String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<meta charset = \"utf-8\">\
<style> html{text-align:center;}</style>\
<h1>ESP32 Web Server</h1>\
<p>GPIO 25 - " + servoState + "</p>\
<p><a href =\"/servo_0\"><button>0度</button></a></p>\
<p><a href =\"/servo_90\"><button>90度</button></a></p>\
</body>\
</html>";

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");
  WiFi.softAP(ssid,password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("ESP32 AP IP address:  ");
  Serial.println(myIP);
  Serial.println();

  lightServo.attach(25);

  server.on("/", handle_root);
  server.on("/servo_0",handle_servo_0);
  server.on("/servo_90",handle_servo_90);
   
  server.begin();
  Serial.println("HTTP server started");
  delay(100);
}

void loop() {
  server.handleClient(); 
}

// Handle root url (/)
void handle_root() {
  server.send(200, "text/html", HTML);
}
void handle_servo_0(){
  lightServo.write(0);
  servoState = "ON";
  server.send(200, "text/html", HTML);
}
void handle_servo_90(){
  lightServo.write(90);
  servoState = "90";
  server.send(200, "text/html", HTML);
}
