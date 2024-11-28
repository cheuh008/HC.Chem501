/*
 * =======================================================================================================================
 * # BME688 Data Collection & Classification Sketch
 * =======================================================================================================================
 *    Based on: App.ino, BSEC2GasScannerClassify.ino  and Wire  Sender by Nicholas Zambetti <http://www.zambetti.com>
 * Description: 0 Defaults to periferal use or 1. Collects raw BME688 data for gas classification / 2. AI Studio training 
 *   Edited by: Harry Cheung (@cheuh008) | Details: https://github.com/cheuh008/HC.Chem501
 *       Modes: 0: Standalone, 1: BSEC2Classifier, 2: BSEC2Collector
 * =======================================================================================================================
 */

#include <Wire.h>
#include "Arduino.h"
#include "Arduino_BHY2.h"

#define Mode 1  // Default mode: 0 for Standalone, 1 for Classifier, 2 for Collector

#if Mode == 1
SensorBSEC2 bsec2(SENSOR_ID_BSEC2);
#include "BSEC2CONFIG.h"
#elif Mode == 2  // Configuration for BSEC2Collector
SensorBSEC2Collector bsec2Collector(SENSOR_ID_BSEC2_COLLECTOR);
#include "CONFIG_BSEC2_HP.h"
#endif

void setup() {                   //
  BHY2.begin();                  //
  conditional();                 //
  Wire.begin(2);                 // join i2c bus (address optional for master)
  Wire.onRequest(requestEvent);  // register event
}

void loop() {
  BHY2.update();  //
  modeSelector();
  serialiser();
}

void serialiser() {
#if Mode == 1
  static auto printTime = millis();
  if (millis() - printTime >= 1000) {
    printTime = millis();
    Serial.println(bsec2.toString());
  }

#elif Mode == 2  // Configuration for BSEC2Collector
  if (last_index != bsec2Collector.gas_index()) {
    last_index = bsec2Collector.gas_index();
    Serial.println(String((uint32_t)bsec2Collector.timestamp()) + " "
                   + String(bsec2Collector.temperature()) + " "
                   + String(bsec2Collector.pressure()) + " "
                   + String(bsec2Collector.humidity()) + " "
                   + String(bsec2Collector.gas()) + " "
                   + String(bsec2Collector.gas_index()));
#endif
}

void modeSelector() {
  if (Serial.available() > 0) {             // Check if data is available on the serial port
    int newMode = Serial.parseInt();        // Read integer input
    if (newMode >= 0 && newMode <= 2) {     // Validate the mode
      mode = newMode;                       // Update the mode
      Serial.print("Mode updated to: ");    //
      Serial.println(mode);                 //
      conditional();                        // Reinitialize sensors based on the new mode
    } else {                                //
      Serial.println("Mode: 0, 1, or 2.");  //
    }
  }
}

void conditional() {
#if Mode == 1
  SensorBSEC2 bsec2(SENSOR_ID_BSEC2);
#include "BSEC2CONFIG.h"
  sensortec.bhy2_bsec2_setConfigString(BSEC2CONFIG, sizeof(BSEC2CONFIG) / sizeof(BSEC2CONFIG[0]));
  bsec2.begin();
#elif Mode == 2  // Configuration for BSEC2Collector
    SensorBSEC2Collector bsec2Collector(SENSOR_ID_BSEC2_COLLECTOR);
#include "CONFIG_BSEC2_HP.h"
    sensortec.bhy2_bsec2_setHP((uint8_t*)BSEC2HP_TEMP, sizeof(BSEC2HP_TEMP), (uint8_t*)BSEC2HP_DUR, sizeof(BSEC2HP_DUR));
    bsec2Collector.begin();
#endif
}


void requestEvent() {
#if Mode == 1
  String dataToSend[5] = {
    String(bsec2.gas_estimates0()),
    String(bsec2.gas_estimates1()),
    String(bsec2.gas_estimates2()),
    String(bsec2.gas_estimates3()),
    String(bsec2.accuracy())
  };
#elif Mode == 2
    String dataToSend[6] = {
      String((uint32_t)bsec2Collector.timestamp()),
      String(bsec2Collector.temperature()),
      String(bsec2Collector.pressure()),
      String(bsec2Collector.humidity()),
      String(bsec2Collector.gas()),
      String(bsec2Collector.gas_index())
    };
#endif
  Wire.write(dataToSend, sizeof(dataToSend));
}
