/***************************************************
 Library for switching a bistable relais using set
 and reset pins

 License: Creative Common V1. 

 Benjamin Voelker, voelkerb@me.com
 Embedded Systems Engineer
 ****************************************************/

#ifndef RELAY_h
#define RELAY_h

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define DEFAULT_HOLD_TIME_MS 20 // Relais must be held this ms until state is set

class Relay {
  public:
    Relay(int setPin, int resetPin);
    void set(bool value);
    void setCallback(void (*cb)(bool));
    int state;
    int holdTime;
  private:
    uint8_t _SET_PIN;
    uint8_t _RES_PIN;
    void (*_switchCB)(bool);
};

#endif
