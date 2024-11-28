#include "Arduino.h"
#include "Arduino_BHY2.h"
#include "BSEC2CONFIG.h"

Sensor gas(SENSOR_ID_GAS);
Sensor pres(SENSOR_ID_BARO);
Sensor temp(SENSOR_ID_TEMP);
SensorBSEC bsec(SENSOR_ID_BSEC);
SensorBSEC2 bsec2(SENSOR_ID_BSEC2);

void setup() {
  Serial.begin(115200);
  BHY2.begin();
  gas.begin();
  pres.begin();
  temp.begin();
  bsec.begin();
  sensortec.bhy2_bsec2_setConfigString(BSEC2CONFIG, sizeof(BSEC2CONFIG) / sizeof(BSEC2CONFIG[0]));
  bsec2.begin();
}

void loop() {
  BHY2.update();
  static auto printTime = millis();
  if (millis() - printTime >= 1000) {
    printTime = millis();
    Serial.println(String("gas: ") + String(gas.value()));
    Serial.println(String("Pressure: ") + String(pres.value()));
    Serial.println(String("temperature: ") + String(temp.value(), 2));
    Serial.print(bsec.toString());
    Serial.print(bsec2.toString());
  }
}
