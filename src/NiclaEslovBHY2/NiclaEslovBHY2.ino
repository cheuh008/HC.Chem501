#include "Arduino_BHY2.h"
#define DEBUG false

void setup(){
  #if DEBUG
    Serial.begin(115200);
    BHY2.debug(Serial);
  #endif
  BHY2.begin(NICLA_I2C, NICLA_VIA_ESLOV);
}

void loop(){
  BHY2.update(100);
}