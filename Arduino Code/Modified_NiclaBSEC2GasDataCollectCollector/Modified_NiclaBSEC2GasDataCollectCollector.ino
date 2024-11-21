#include "Arduino_BHY2.h"

SensorBSEC2Collector bsec2Collector(SENSOR_ID_BSEC2_COLLECTOR);

const uint16_t BSEC2HP_TEMP[] = { 320, 100, 100, 100, 200, 200, 200, 320, 320, 320 };  // HP-354 // Default Heater temperature and time base(Recommendation)
const uint16_t BSEC2HP_DUR[] = { 5, 2, 10, 30, 5, 5, 5, 5, 5, 5 };                     // the duration in steps of 140ms, 5 means 700ms, 2 means 280ms

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
  BHY2.begin();
  sensortec.bhy2_bsec2_setHP((uint8_t*)BSEC2HP_TEMP, sizeof(BSEC2HP_TEMP), (uint8_t*)BSEC2HP_DUR, sizeof(BSEC2HP_DUR));
  bsec2Collector.begin();
}

void loop() {
  static auto last_index = 0;
  BHY2.update();   // Update function should be continuously polled
  if (last_index != bsec2Collector.gas_index()) {
    last_index = bsec2Collector.gas_index();
    Serial.println(String((uint32_t)bsec2Collector.timestamp()) + " "
                   + String(bsec2Collector.temperature()) + " "
                   + String(bsec2Collector.pressure()) + " "
                   + String(bsec2Collector.humidity()) + " "
                   + String(bsec2Collector.gas()) + " "
                   + String(bsec2Collector.gas_index()));
  }
}

/*
// customized Heater temperature and time base
const uint16_t BSEC2HP_TEMP[] = {100, 320, 320, 200, 200, 200, 320, 320, 320, 320}; // HP-321 / 
const uint16_t BSEC2HP_DUR[] = {43, 2, 2, 2, 21, 21, 2, 14, 14, 14};  // the duration in steps of 140ms, 5 means 700ms, 2 means 280ms

*/