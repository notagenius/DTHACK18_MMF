#include <ESP8266WiFi.h>
#include <Time.h>
#include "ntp.h"
 
 

#define WIFI_SSID "TelekomOS1" 
#define WIFI_PASS "#dthack18" 

WiFiClient client;

void updateDisplay(void) {
  time_t utc = now();
  Serial.println(utc);
}

void setup() {
 
  Serial.begin(115200); 

  initNTP(WIFI_SSID, WIFI_PASS);
}
 

time_t previousSecond = 0;
 
void loop() {
  if (timeStatus() != timeNotSet) {
    if (second() != previousSecond) {
      previousSecond = second();
      updateDisplay();
    }
  }
  delay(1000);
}
