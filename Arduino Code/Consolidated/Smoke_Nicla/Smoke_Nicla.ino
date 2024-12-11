// =======================================================================================================================
//  # BME688 Data Collection & Classification Sketch
//  =======================================================================================================================
//    Based on: App.ino, BSEC2GasScannerClassify.ino  and Wire  Sender by Nicholas Zambetti <http://www.zambetti.com>
// Description: 0 Defaults to periferal use or 1. Collects raw BME688 data for gas classification / 2. AI Studio training
//   Edited by: Harry Cheung (@cheuh008) | Details: https://github.com/cheuh008/HC.Chem501
//       modes: 0: Standalone, 1: BSEC2Classifier, 2: BSEC2Collector
// =======================================================================================================================

// =======================================================================================================================
// Importing the Library and defining variables
// =======================================================================================================================

#include "Wire.h"
#include "Arduino.h"
#include "Arduino_BHY2.h"
#include "BSEC2CONFIG.h"
#include "CONFIG_BSEC2_HP.h"

int input;
int mode = 1;  // Default mode: 0 for Standalone, 1 for Classifier, 2 for Collector
SensorBSEC2Collector bsec2Collector(SENSOR_ID_BSEC2_COLLECTOR);
SensorBSEC2 bsec2(SENSOR_ID_BSEC2);  //

// =======================================================================================================================
//  Setup and Mainloop initialises and calls functions as needed
//  =======================================================================================================================

void setup() {                   //
  Serial.begin(115200);          //
  BHY2.begin();                  //
  Wire.begin(2);                 // join i2c bus (address optional for master)
  Wire.onRequest(requestEvent);  // register event
  Wire.onReceive(modeSelector);  // register event
  conditional();                 // Function to turn on/off sensors
}

void loop() {
  BHY2.update();
  serialiser();                  //
  if (Serial.available() > 0) {  // Check if data is available on the serial port
    input = Serial.parseInt();   // Read integer input
    Serial.read();               // Clear the buffer after parsing
    modeSelector(input);         //
  }                              //
}

// =======================================================================================================================
//  Initialising Sensors Based on Mode
//  =======================================================================================================================

void conditional() {
  bsec2.end();  // Cuz u have to turn it off and back on again?
  bsec2Collector.end();
  Serial.println("Initialising Sensors ");  //
  if (mode == 1) {
    // Ask user for configuration after mode 1 is selected
    Serial.println("Select Configuration (1-9):");
    for (int i = 0; i < 9; i++) {
      Serial.print(configNames[i]);
      Serial.print(", ");
    }
    Serial.println();
    while (Serial.available() == 0) {
    }
    int configChoice = Serial.parseInt();  // Get user input (1-9)
    Serial.read();
    if (configChoice >= 1 && configChoice <= 9) {
      memcpy(buffer, configArray[configChoice - 1], 1943);
      for (int i = 0; i < 10; i++) { 
        Serial.print(String(buffer[1933 + i]) + ", ");
      }
      Serial.println();
      sensortec.bhy2_bsec2_setConfigString(buffer, 1943);  // Pass selected config to the sensor
      Serial.print(configNames[configChoice - 1]);
      Serial.println(" Classifier On.");
    } else {
      Serial.println("Invalid configuration selected.");
      sensortec.bhy2_bsec2_setConfigString(BSEC2CONFIG, sizeof(BSEC2CONFIG) / sizeof(BSEC2CONFIG[0]));
      Serial.println("Reverted to Default Classifier");
    }
    bsec2.begin();
  } else if (mode == 2) {
    sensortec.bhy2_bsec2_setHP((uint8_t*)BSEC2HP_TEMP, sizeof(BSEC2HP_TEMP), (uint8_t*)BSEC2HP_DUR, sizeof(BSEC2HP_DUR));
    bsec2Collector.begin();
    Serial.println("Collector On ");
  } else {
    Serial.println("Senosrs Turned Off ");
  }
}

// =======================================================================================================================
//  For printing to Serial if connected
//  =======================================================================================================================

void serialiser() {                    //
  static auto printTime = millis();    //
  if (millis() - printTime >= 1000) {  //
    printTime = millis();              //
    if (mode == 1) {                   //
      Serial.print(bsec2.toString());  //
    } else if (mode == 2) {            //
      Serial.println(
        String((uint32_t)bsec2Collector.timestamp()) + " "
        + String(bsec2Collector.temperature()) + " "
        + String(bsec2Collector.pressure()) + " "
        + String(bsec2Collector.humidity()) + " "
        + String(bsec2Collector.gas()) + " "
        + String(bsec2Collector.gas_index()));
    }
  }
}

void modeSelector(int input) {
  if (Wire.available()) {  //
    input = Wire.read();   //
  }
  if (input >= 0 && input <= 2) {      // Validate the mode
    mode = input;                      // Update the mode
    Serial.print("Mode: ");            //
    Serial.print(mode);                //
    Serial.println(" selected ");      //
    conditional();                     // Reinitialize sensors based on the new mode
  } else {                             //
    Serial.println("Invalid Input ");  //
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
  Serial.print("I²C request received. ");  // Acknowledging request
}
