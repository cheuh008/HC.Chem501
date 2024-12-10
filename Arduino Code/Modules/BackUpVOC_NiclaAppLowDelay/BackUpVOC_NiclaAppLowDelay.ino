#include "Arduino.h"
#include "Arduino_BHY2.h"

void setup() {
  BHY2.begin();
}

void loop() {
  BHY2.update();
}
