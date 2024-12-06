
#include "Arduino.h"
#include "Arduino_BHY2.h"

SensorBSEC2Collector bsec2Collector(SENSOR_ID_BSEC2_COLLECTOR);

// Default Heater temperature and time base(Recommendation)
const uint16_t BSEC2HP_TEMP[] = { 320, 100, 100, 100, 200, 200, 200, 320, 320, 320 };  // HP-354 /
const uint16_t BSEC2HP_DUR[] = { 5, 2, 10, 30, 5, 5, 5, 5, 5, 5 };                     // the duration in steps of 140ms, 5 means 700ms, 2 means 280ms


void setup() {
  Serial.begin(115200);
  while (!Serial) delay(1000);
  BHY2.begin();
  sensortec.bhy2_bsec2_setHP((uint8_t*)BSEC2HP_TEMP, sizeof(BSEC2HP_TEMP), (uint8_t*)BSEC2HP_DUR, sizeof(BSEC2HP_DUR));
  bsec2Collector.begin();
}

void loop() {
  BHY2.update();
  Serial.println(String((uint32_t)bsec2Collector.timestamp()) + " "
                 + String(bsec2Collector.temperature()) + " "
                 + String(bsec2Collector.pressure()) + " "
                 + String(bsec2Collector.humidity()) + " "
                 + String(bsec2Collector.gas()) + " "
                 + String(bsec2Collector.gas_index()));
  delay(1000);
}
