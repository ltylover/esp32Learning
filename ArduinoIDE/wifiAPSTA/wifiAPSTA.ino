#include <WiFi.h>

const char* wifi_network_ssid = "loveLTY";
const char* wifi_network_password = "qwertyuiop";

const char *soft_ap_ssid = "ESP32";
const char *soft_ap_password = "12345678";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_APSTA);
  WiFi.softAP(soft_ap_ssid, soft_ap_password);
  WiFi.begin(wifi_network_ssid, wifi_network_password);
  while (WiFi.status()!= WL_CONNECTED) {
    deday(500);
    Serial.println("Connect to WiFi...");
  }
  Serial.print("AP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("STA connected IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  
}
