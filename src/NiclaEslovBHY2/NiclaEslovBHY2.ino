#include "Arduino.h"
#include "Arduino_BHY2.h"

void setup() {
  BHY2.begin(NICLA_I2C, NICLA_VIA_ESLOV);
}

void loop() {
  BHY2.update(100);
}