/***************************************************
 Library for network stuff, connection, AP and so on.

 License: Creative Common V1. 

 Benjamin Voelker, voelkerb@me.com
 Embedded Systems Engineer
 ****************************************************/

#include "relay.h"


Relay::Relay(int pinSet, int pinReset, bool activeLow) {
  _activeLow = activeLow;
  _bistableMode = false;
  if (pinReset != -1) _bistableMode = true;
  _SET_PIN = pinSet;
  _RES_PIN = pinReset;
  state = -1;
  pinMode(_SET_PIN, INPUT);
  if (_bistableMode) {
    pinMode(_RES_PIN, INPUT);
  }

  _switchCB = NULL;
  holdTime = DEFAULT_HOLD_TIME_MS;
}

void Relay::init(bool state) {
  if (!_bistableMode) {
    pinMode(_SET_PIN, OUTPUT);
  }
  set(state); 
}

void Relay::setCallback(void (*cb)(bool)) {
  _switchCB = cb;
}

void Relay::set(bool value) {
  if (state != -1 and (bool)state == value) return;
  if (_bistableMode) {
    pinMode(_SET_PIN, OUTPUT);
    pinMode(_RES_PIN, OUTPUT);
    digitalWrite(_SET_PIN, _activeLow?HIGH:LOW);
    digitalWrite(_RES_PIN, _activeLow?HIGH:LOW);
    digitalWrite(_SET_PIN, _activeLow?value:value);
    digitalWrite(_RES_PIN, _activeLow?value:!value);
    delay(holdTime);
    // Relais is bistable, so disable pins to avoid constant power drawn by transistor
    digitalWrite(_SET_PIN, _activeLow?HIGH:LOW);
    digitalWrite(_RES_PIN, _activeLow?HIGH:LOW);
    // Relay is bistable, so we do not have to keep this high
    pinMode(_SET_PIN, INPUT);
    pinMode(_RES_PIN, INPUT);
  } else {
    digitalWrite(_SET_PIN, _activeLow?value:!value);
  }
  state = (int)value;
  if (_switchCB) _switchCB(value);
}
