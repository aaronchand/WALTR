#include <ESP8266WiFi.h>
#include <espnow.h>

uint8_t newMACAddress[] = {0x44, 0x44, 0x44, 0x44, 0x44, 0x44}; //MAC Address

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); //Set Device as a WiFi Station
  
  Serial.println("old macaddress");
  Serial.println(WiFi.macAddress());

  newMACAddress[5] = ?;  // set this to device number

  wifi_set_macaddr(STATION_IF, &newMACAddress[0]);
  
  Serial.println("new macaddress");
  Serial.println(WiFi.macAddress());
}
void loop() { }
