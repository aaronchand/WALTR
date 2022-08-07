#include <ESP8266WiFi.h>
#include <espnow.h>

uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t newMACAddress[] = {0x44, 0x44, 0x44, 0x44, 0x44, 0x44}; //MAC Address

typedef struct struct_message { //structure example to send data //must match the receiver structure
  char a[32];
} struct_message;

struct_message myData; // create a structmeassage called myData
char s [32];

void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) { //receive data
  Serial.print (mac[5]);
}

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("*");
}

void setup() {
  Serial.begin(115200); //Init Serial Monitor

  Serial.println("ok");
  
  WiFi.mode(WIFI_STA); //Set Device as a WiFi Station
  WiFi.disconnect();

  newMACAddress[5] = 1;  // set this to device number

  wifi_set_macaddr(STATION_IF, &newMACAddress[0]);

  esp_now_init(); //init esp now

  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);

  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);

  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0); //add peer
}

void loop() {
  strcpy(myData.a,"THIS IS A CHAR"); //set values to send
  esp_now_send(0, (uint8_t*) &myData, sizeof(myData)); // send a message
  delay(100);
}
