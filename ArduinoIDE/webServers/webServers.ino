#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WebServer.h>

boolean led1Flag = false;

String led1State = "OFF";
String receline = "";
String receAll = "";

const char* ssid = "ESP32";
const char* password = "12345678";

//WiFiServer server(80);
//WiFiClient newClient;
 
WebServer server(80); 


String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<meta charset = \"utf-8\">\
<style> html{text-align:center;}</style>\
<h1>ESP32 Web Server </h1>\
<p>GPIO 4 - " + led1State + "</p>\
<p><a href =\"/led1_on\"><button>打开</button></a></p>\
<p><a href =\"/led1_off\"><button>关闭</button></a></p>\
</body>\
</html>";

//void pageDisplay(){
//  newClient.println("HTTP/1.1 200 OK");
//  newClient.println("Connect - type:text/html");
//  newClient.println();
//  newClient.println("<! DOCTYPE html >");
//  newClient.println("< html >");
//  newClient.println("< head >");
//  newClient.println("< title >ESP32 Web Server </title>");
//  newClient.println("< meta charset = \"utf-8\">");
//  newClient.println("< style > html{text-align:center;}</style> ");
//  newClient.println("< /head >");
//  newClient.println("< body >");
//  newClient.println("< h2 >ESP32 Web Server </h2 >");
//  newClient.println("< p >GPIO 4 - " + led1State + "< /p >");
//  newClient.println("< p > < a href =\"/led1_on\"> < button > 打开 < /button > < /a > < /p >");
//  newClient.println("< p > < a href =\"/led1_off\"> < button > 关闭 < /button > < /a > < /p >"); 
//  newClient.println("< /body > < /html >");
//  newClient.println();  
//}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");
  WiFi.softAP(ssid,password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("ESP32 AP IP address:  ");
  Serial.println(myIP);
  Serial.println();

  pinMode(2,OUTPUT);

  server.on("/", handle_root);
  server.on("/led1_on",handle_led1On);
  server.on("/led1_off",handle_led1Off);
   
  server.begin();
  Serial.println("HTTP server started");
  delay(100);
}

void loop() {
//  newClient = server.available();
//  if(newClient){
//    Serial.print("new Client connected. IP address is : ");
//    Serial.println(newClient.remoteIP());
//
//    while(newClient.connected()){
//      if(newClient.available()>0){
//        char c =newClient.read();
//        Serial.print(c);
//        receAll += c;
//        if(c == '\n' ){
//          if(receline.length() == 0){
//            getCommand();
//            pageDisplay();
//            break;
//          }
//          else{
//            receline = "";
//          }
//        }
//        else if( c != '\r'){
//          receline += c;
//        }
//      }
//    }
//    newClient.stop();
//    Serial.println("Client disconnected.");
//  }

  server.handleClient();
  
}

// Handle root url (/)
void handle_root() {
  server.send(200, "text/html", HTML);
}
void handle_led1On(){
  digitalWrite(2,HIGH);
  led1State = "ON";
  server.send(200, "text/html", HTML);
}
void handle_led1Off(){
  digitalWrite(2,LOW);
  led1State = "OFF";
  server.send(200, "text/html", HTML);
}
