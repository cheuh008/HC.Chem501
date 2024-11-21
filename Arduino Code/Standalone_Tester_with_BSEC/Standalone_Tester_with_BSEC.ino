
#include "Arduino_BHY2.h"

SensorXYZ accel(SENSOR_ID_ACC);
SensorXYZ gyro(SENSOR_ID_GYRO);
Sensor temp(SENSOR_ID_TEMP);
Sensor gas(SENSOR_ID_GAS);
SensorQuaternion rotation(SENSOR_ID_RV);
SensorBSEC bsec(SENSOR_ID_BSEC);


void setup() {
  Serial.begin(115200);
  BHY2.begin();
  accel.begin();
  gyro.begin();
  temp.begin();
  gas.begin();
  rotation.begin();
  bsec.begin();

  SensorConfig cfg = accel.getConfiguration();
  Serial.println(String("range of accel: +/-") + cfg.range + String("g"));
  accel.setRange(2);  //this sets the range of accel to +/-4g,
  cfg = accel.getConfiguration();
  Serial.println(String("range of accel: +/-") + cfg.range + String("g"));

  cfg = gyro.getConfiguration();
  Serial.println(String("range of gyro: +/-") + cfg.range + String("dps"));
  gyro.setRange(1000);
  cfg = gyro.getConfiguration();
  Serial.println(String("range of gyro: +/-") + cfg.range + String("dps"));
}

void loop() {
  static auto printTime = millis();
  BHY2.update();  // Update function should be continuously polled
  if (millis() - printTime >= 1000) {
    printTime = millis();
    Serial.println(String("acceleration: ") + accel.toString());
    Serial.println(String("gyroscope: ") + gyro.toString());
    Serial.println(String("temperature: ") + String(temp.value(), 3));
    Serial.println(String("gas: ") + String(gas.value(), 3));
    Serial.println(String("rotation: ") + rotation.toString());
    Serial.println(String("BSEC: ") + bsec.toString());
  }
}
