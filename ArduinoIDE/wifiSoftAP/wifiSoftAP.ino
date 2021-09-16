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

const char * ssid = "ESP32";
const char * password = "12345678";

int staNum = 0;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  WiFi.softAP(ssid,password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("ESP32 AP IP address:  ");
  Serial.println(myIP);
  delay(1000);
  Serial.printf("Number connect to ESP32 : %d\n",staNum );

  pinMode(2,OUTPUT);
}

void loop() {
  int connectNum = WiFi.softAPgetStationNum();
  if (connectNum != staNum){
    Serial.printf("Number connect to ESP32 : %d\n",connectNum);
    staNum = connectNum;
  }
  if(staNum != 0){  
    digitalWrite(2,HIGH);
  }
  else if(staNum == 0){
    digitalWrite(2,LOW);
  }


}
