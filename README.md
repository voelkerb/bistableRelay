# BistableRelay
A simple library to control a bistable relay with set and reset pins.\
Pins are not held HIGH or LOW only during active toggling. 

```C++
#include "relay.h"

Relay relay(26, 27);

void setup() {
  Serial.begin(115200);
  relay.setCallback(relayCB);
}

void loop() {
  delay(5000);
  relay.set(!relay.state);
}

void relayCB(bool state) {
  Serial.printf("Switched %s\n", state ? "on" : "off");
}
```


Output
```bash
Switched off
Switched on
Switched off
Switched on
```
