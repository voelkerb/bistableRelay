/***************************************************
 Example file for using the bistableRelay library.
 
 License: Creative Common V1. 

 Benjamin Voelker, voelkerb@me.com
 Embedded Systems Engineer
 ****************************************************/

#include "relay.h"
const int RELAY_PIN_SET = 26;
const int RELAY_PIN_RES = 27; 

Relay relay(RELAY_PIN_SET, RELAY_PIN_RES);

void setup() {
  Serial.begin(115200);
  relay.setCallback(relayCB);
  // Optional, change hold time required to toggle relay
  // relay.holdTime = 20; // in ms
}

void loop() {
  // TOGGLE
  delay(5000);
  relay.set(!relay.state);
}

void relayCB(bool state) {
  Serial.printf("Switched %s\n", state ? "on" : "off");
}