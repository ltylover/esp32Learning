#include <WiFi.h>

const char* wifi_network_ssid = "ChinaNet-WUSs";
const char* wifi_network_password = "20001208";

const char *soft_ap_ssid = "ESP32-WiFi";
const char *soft_ap_password = "12345678";

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
}

void loop() {
    if(WiFi.status() != WL_CONNECTED){
      digitalWrite(2, LOW); 
      }
    else{
      digitalWrite(2, HIGH);
      }
}
