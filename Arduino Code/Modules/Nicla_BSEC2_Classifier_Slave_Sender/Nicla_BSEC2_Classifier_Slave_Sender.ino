/*
 * Code Based on
 *    Wire Master Writer by Nicholas Zambetti <http://www.zambetti.com>
 *    and BSEC2GasScannerClassify.ino from BHY2 example
 *
 * Edited by Harry Cheung @cheuh008
 *  For more detail, refer to docs @https://github.com/cheuh008/HC.Chem501
 *  This code is in the public domain.
 */


#include <Wire.h>
#include "Arduino.h"
#include "Arduino_BHY2.h"
#include "BSEC2CONFIG.h"

uint8_t bsec2Data[5];
SensorBSEC2 bsec2(SENSOR_ID_BSEC2);
// const uint8_t BSEC2CONFIG[] = {}; // array BSEC2CONFIG moved to BSEC2CONFIG.h due to large size
const int size = sizeof(BSEC2CONFIG) / sizeof(BSEC2CONFIG[0]);


void setup() {
  Serial.begin(115200);  //
  while (!Serial) {}
  if (!BHY2.begin()) {
    Serial.println("BHY2 initialization failed!");
    while (1) {}
  }
  sensortec.bhy2_bsec2_setConfigString(BSEC2CONFIG, size);  //
  if (!bsec2.begin()) {
    Serial.println("BSEC2 initialization failed!");
    while (1) {}
  }
  Wire.begin(2);                 // join i2c bus (address optional for master)
  Wire.onRequest(requestEvent);  // register event
}

void loop() {
  BHY2.update();
  static auto printTime = millis();
  if (millis() - printTime >= 1000) {
    printTime = millis();
    Serial.print(bsec2.toString());
  }
}

void requestEvent() {
  bsec2Data[0] = bsec2.gas_estimates0();
  bsec2Data[1] = bsec2.gas_estimates1();
  bsec2Data[2] = bsec2.gas_estimates2();
  bsec2Data[3] = bsec2.gas_estimates3();
  bsec2Data[4] = bsec2.accuracy();           //
  Wire.write(bsec2Data, sizeof(bsec2Data));  // Sending all 5 bytes
  Serial.print("I²C request received. ");    // Acknowledging request
  Serial.print("Sending BSEC data...");      // Acknowledging Data sent
}
