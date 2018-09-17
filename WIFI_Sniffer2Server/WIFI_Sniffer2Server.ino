/*    #DtHack18 - WiFiScanOnly  - For the Repository in gitHub

Challenge:

- setup and cofigure the LIBs in Arduino Properly
- check the serial Monitor
- build / deploy the application to the NodeMcu
- Understand the basic Concept - What are the methods do?
- make some basic tests concerning scan-Range ( RSSI )

*/

#include <Arduino.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <Time.h>
#include "ntp.h"

#define DATA_LENGTH           112
#define TYPE_MANAGEMENT       0x00
#define TYPE_CONTROL          0x01
#define TYPE_DATA             0x02
#define SUBTYPE_PROBE_REQUEST 0x04

#define WIFI_SSID "Etadar-GmbH" 
#define WIFI_PASS "schatzimausi"
#define SENSOR_ID 7

String post_string;
WiFiClient client;

void updateDisplay(void) {
  time_t utc = now();
  Serial.println(utc);
}

time_t previousSecond = 0;


struct RxControl {
  signed rssi : 8; // signal intensity of packet
  unsigned rate : 4;
  unsigned is_group : 1;
  unsigned : 1;
  unsigned sig_mode : 2; // 0:is 11n packet; 1:is not 11n packet;
  unsigned legacy_length : 12; // if not 11n packet, shows length of packet.
  unsigned damatch0 : 1;
  unsigned damatch1 : 1;
  unsigned bssidmatch0 : 1;
  unsigned bssidmatch1 : 1;
  unsigned MCS : 7; // if is 11n packet, shows the modulation and code used (range from 0 to 76)
  unsigned CWB : 1; // if is 11n packet, shows if is HT40 packet or not
  unsigned HT_length : 16;// if is 11n packet, shows length of packet.
  unsigned Smoothing : 1;
  unsigned Not_Sounding : 1;
  unsigned : 1;
  unsigned Aggregation : 1;
  unsigned STBC : 2;
  unsigned FEC_CODING : 1; // if is 11n packet, shows if is LDPC packet or not.
  unsigned SGI : 1;
  unsigned rxend_state : 8;
  unsigned ampdu_cnt : 8;
  unsigned channel : 4; //which channel this packet in.
  unsigned : 12;
};

struct SnifferPacket {
  struct RxControl rx_ctrl;
  uint8_t data[DATA_LENGTH];
  uint16_t cnt;
  uint16_t len;
};


static void printDataSpan(uint16_t start, uint16_t size, uint8_t* data) {
  for (uint16_t i = start; i < DATA_LENGTH && i < start + size; i++) {
    Serial.write(data[i]);
  }
}

static void getMAC(char *addr, uint8_t* data, uint16_t offset) {
  sprintf(addr, "%02x:%02x:%02x:%02x:%02x:%02x", data[offset + 0], data[offset + 1], data[offset + 2], data[offset + 3], data[offset + 4], data[offset + 5]);
}


static void showMetadata(struct SnifferPacket *snifferPacket) {

  unsigned int frameControl = ((unsigned int)snifferPacket->data[1] << 8) + snifferPacket->data[0];

  uint8_t version = (frameControl & 0b0000000000000011) >> 0;
  uint8_t frameType = (frameControl & 0b0000000000001100) >> 2;
  uint8_t frameSubType = (frameControl & 0b0000000011110000) >> 4;
  uint8_t toDS = (frameControl & 0b0000000100000000) >> 8;
  uint8_t fromDS = (frameControl & 0b0000001000000000) >> 9;

  // Only look for probe request packets
  if (frameType != TYPE_MANAGEMENT ||
    frameSubType != SUBTYPE_PROBE_REQUEST)
    return;

  char addr[] = "00:00:00:00:00:00";
  getMAC(addr, snifferPacket->data, 10);
  post_string = post_string + "{\"mac\":\""+ addr +"\",\"sensor_id\":"+SENSOR_ID+", \"rssi\":" +  String(snifferPacket->rx_ctrl.rssi, DEC) +",\"timestamp\":" + String(now()) +"},";

  /*
  Serial.print("RSSI: ");
  Serial.print(snifferPacket->rx_ctrl.rssi, DEC);

  Serial.print(" Ch: ");
  Serial.print(wifi_get_channel());

  char addr[] = "00:00:00:00:00:00";
  getMAC(addr, snifferPacket->data, 10);
  Serial.print(" Peer MAC: ");
  Serial.println(addr);
  */
  Serial.print("*");
}

/**
* Callback for promiscuous mode
*Meaning of ICACHE_FLASH_ATTR: http://bbs.espressif.com/viewtopic.php?t=1183
*Die bedeutung ist wohl nicht ganz klar!?
*/
static void ICACHE_FLASH_ATTR sniffer_callback(uint8_t *buffer, uint16_t length) {
  struct SnifferPacket *snifferPacket = (struct SnifferPacket*) buffer;
  showMetadata(snifferPacket);
}


#define CHANNEL_HOP_INTERVAL_MS 300
#define CHANNEL_HOP_LOOPS 1
#define DISABLE 0
#define ENABLE  1

  
void sniffCycle() {
  Serial.println("Starting SniffCycle");

  delay(10);
  wifi_promiscuous_enable(ENABLE);
  delay(10);
  
  for (uint8 j=0;j<CHANNEL_HOP_LOOPS;j++) {
    for (uint8 i=1;i<14;i++) {
//      Serial.print("Scanning Channel ");
      Serial.print(i);
      Serial.print(" ");
      delay(10);
      wifi_set_channel(i);
      delay(CHANNEL_HOP_INTERVAL_MS);
    }
  }
  Serial.println(".done.");
}

char ssid[] = WIFI_SSID;  //  your network SSID (name)
char pass[] = WIFI_PASS;       // your network password
  
void clientMode() {
  Serial.println("Starting ClientMode");
  wifi_set_opmode(STATION_MODE);
  wifi_set_channel(1);
  wifi_promiscuous_enable(DISABLE);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
   }
  Serial.print("Connected to Internet: ");
  Serial.println(WiFi.localIP());
  delay(10);
}



void setup() {
  wifi_set_promiscuous_rx_cb(sniffer_callback);
  Serial.begin(115200);
  delay(10);
  
  clientMode();
  initNTP(WIFI_SSID, WIFI_PASS);
  delay(10);
}

void loop() {
  sniffCycle();
//  Serial.println("post_string is: >>"+post_string+"<<");
  if (post_string!="") {
    clientMode();
    Serial.println("Sending Data to cloud...");
    int length = post_string.length();
    post_string[length-1] = ' ';
  
    String post_string2 = "["+post_string+"]";
    Serial.println(post_string2);

    HTTPClient http;    //Declare object of class HTTPClient
 
    http.begin("http://mmf.etadar.de:8000/mmf/new");      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header
 
    int httpCode = http.POST(post_string2);
    String payload = http.getString();                                        //Get the response payload
 
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
 
    http.end();  //Close connection
    
    post_string="";
    post_string2="";
  
//    delay(100);
  }
}
