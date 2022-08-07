/*
Super Simple Minimalist Easy ESPNOW
 
This is an easy way to communicate between ESP8266s.
 
*no error checking
*no encryption
*broadcast only
*unlimited number of transceivers
*Six bits+Five bytes of sender id and/or payload(two low order bits of first byte are reserved)
*250 bytes of optional payload
 
Aaron Chand 
Tim Hayward
 
License: MIT License
*/
 
#include <ESP8266WiFi.h>
#include <espnow.h>
 
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
 
/* Optional Custom MAC Address
uint8_t newMACAddress[] = {0x44, 0x44, 0x44, 0x44, 0x44, 0x44}; 
*/
 
bool OkayToSend; //Sending is Complete
 
typedef struct struct_message { 
  //structure example to send data //must match the receiver structure
 char a[250];
} struct_message;
 
struct_message myData; // create a data structure called myData

char s [32];
 
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) { //receive data
  memcpy(&myData, incomingData, sizeof(myData));
  char macStr[18];
 	Serial.print("Data received");
 	snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
 	mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
 	Serial.print(macStr);
  Serial.print("\t");
	Serial.println(myData.a);
}
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  OkayToSend = true;
}
 
void setup() {
  Serial.begin(115200); //Init Serial Monitor
 
  Serial.println("Super Simple Minimalist Easy ESPNOW");
 
  WiFi.mode(WIFI_STA); //Set Device as a WiFi Station
  WiFi.disconnect();
 
  /* Uncomment to Set Custom MAC Address
  wifi_set_macaddr(STATION_IF, &newMACAddress[0]);
  */

  esp_now_init(); //init ESPNOW
 
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
 
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
 
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0); //add peer
}
 
void loop() {
 
  strcpy(myData.a,"THIS IS THE PAYLOAD"); //set values to send
 
  while (!OkayToSend){}
 
  OkayToSend = false;
 
  esp_now_send(0, (uint8_t*) &myData, sizeof(myData)); // send a message
 	delay(100);
}