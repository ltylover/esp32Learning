#include <ETH.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiSTA.h>
#include <WiFiType.h>
#include <WiFiUdp.h>

String led1State = "OFF";
String receline = "";

const char * ssid = "ESP32";
const char * password = "12345678";

WiFiServer server(80);
WiFiClient newClient;

void pageDisplay(){
  newClient.println("HTTP/1.1 200 OK");
  newClient.println("Connect - type:text/html");
  newClient.println();
  newClient.println("<! DOCTYPE HTML >");
  newClient.println("< html >");
  newClient.println("< head >");
  newClient.println("< title >ESP32 Web Server </title>");
  newClient.println("< meta charset = \"utf-8\">");
  newClient.println("< style > html{text-align:center;}</style> ");
  newClient.println("< /head >");
  newClient.println("< body >");
  newClient.println("< h2 >ESP32 Web Server </h2 >");
  newClient.println("< p >GPIO 4 - " + led1State + "< /p >");
  newClient.println("< p > < a href =\"/led1_on\"> < button > 打开 < /button > < /a > < /p >");
  newClient.println("< p > < a href =\"/led1_off\"> < button > 关闭 < /button > < /a > < /p >"); 
  newClient.println("< /body > < /html >");
  newClient.println();  
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");
  WiFi.softAP(ssid,password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("ESP32 AP IP address:  ");
  Serial.println(myIP);
  Serial.println();
  server.begin();
}

void loop() {
  newClient = server.available();
  if(newClient){
    Serial.print("new Client connected. IP address is : ");
    Serial.println(newClient.remoteIP());

    while(newClient.connected()){
      if(newClient.available()>0){
        char c =newClient.read();
        Serial.print(c);
        if(c == '\n' ){
          if(receline.length() == 0){
            pageDisplay();
            break;
          }
          else{
            receline = "";
          }
        }
        else if( c != '\r'){
          receline += c;
        }
      }
    }
    newClient.stop();
    Serial.println("Client disconnected.");
  }
}
