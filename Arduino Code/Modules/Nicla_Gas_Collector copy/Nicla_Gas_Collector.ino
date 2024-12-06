#include <Arduino_BHY2.h>

// =======================================================================================================================
//  # BME688 Data Collection & Classification Sketch
//  =======================================================================================================================
//    Based on: App.ino, BSEC2GasScannerClassify.ino  and Wire  Sender by Nicholas Zambetti <http://www.zambetti.com>
// Description: 0 Defaults to periferal use or 1. Collects raw BME688 data for gas classification / 2. AI Studio training
//   Edited by: Harry Cheung (@cheuh008) | Details: https://github.com/cheuh008/HC.Chem501
//       modes: 0: Standalone, 1: BSEC2Classifier, 2: BSEC2Collector
// =======================================================================================================================

#include <Wire.h>
#include "Arduino.h"
#include "Arduino_BHY2.h"
#include "BSEC2CONFIG.h"
#include "CONFIG_BSEC2_HP.h"

// =======================================================================================================================
//  Sensor Define
//  =======================================================================================================================

int mode = 1;                        // Default mode: 0 for Standalone, 1 for Classifier, 2 for Collector
SensorBSEC2 bsec2(SENSOR_ID_BSEC2);  //
SensorBSEC2Collector bsec2Collector(SENSOR_ID_BSEC2_COLLECTOR);

// =======================================================================================================================
//  Setup Function to initialise BHY2 and Wire
//  =======================================================================================================================

void setup() {                   //
  BHY2.begin();                  //
  Wire.begin(2);                 // join i2c bus (address optional for master)
  Wire.onRequest(requestEvent);  // register event
  conditional();                 // Function to turn on/off sensors
}

// =======================================================================================================================
//  Sensor Define
//  =======================================================================================================================

void conditional() {
  if (mode == 0) {
    bsec2.end();
    bsec2Collector.end();
  } else if (mode == 1) {
    bsec2Collector.end();
    sensortec.bhy2_bsec2_setConfigString(BSEC2CONFIG, sizeof(BSEC2CONFIG) / sizeof(BSEC2CONFIG[0]));
    bsec2.begin();
  } else if (mode == 2) {
    bsec2.end();
    sensortec.bhy2_bsec2_setHP((uint8_t*)BSEC2HP_TEMP, sizeof(BSEC2HP_TEMP), (uint8_t*)BSEC2HP_DUR, sizeof(BSEC2HP_DUR));
    bsec2Collector.begin();
  }
}

void loop() {
  BHY2.update();  //
  modeSelector();
  serialiser();
}

void modeSelector() {
  if (Serial.available() > 0) {             // Check if data is available on the serial port
    int input = Serial.parseInt();          // Read integer input
    if (input >= 0 && input <= 2) {         // Validate the mode
      mode = input;                         // Update the mode
      Serial.print("mode updated to: ");    //
      Serial.println(mode);                 //
      conditional();                        // Reinitialize sensors based on the new mode
    } else {                                //
      Serial.println("mode: 0, 1, or 2.");  //
    }
  }
}

void serialiser() {
  if (mode == 1) {
    static auto printTime = millis();
    if (millis() - printTime >= 1000) {
      printTime = millis();
      Serial.println(bsec2.toString());
    }
  }
}

void requestEvent() {
  if (mode == 1) {
    uint8_t dataToSend[5] = {
      bsec2.gas_estimates0(),
      bsec2.gas_estimates1(),
      bsec2.gas_estimates2(),
      bsec2.gas_estimates3(),
      bsec2.accuracy()
    };
    Wire.write(dataToSend, sizeof(dataToSend));
  } else if (mode == 2) {
    String data = "";
    data += (String((uint32_t)bsec2Collector.timestamp()) + " "
             + String(bsec2Collector.temperature()) + " "
             + String(bsec2Collector.pressure()) + " "
             + String(bsec2Collector.humidity()) + " "
             + String(bsec2Collector.gas()) + " "
             + String(bsec2Collector.gas_index()));
    Wire.write(data.c_str());
  }
}