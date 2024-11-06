/*
  WriteMultipleFields
  Description: Writes values to fields 1,2,3,4 and status in a single ThingSpeak update every 1 seconds.
  Hardware: Arduino MKR WiFi 1010  

  ThingSpeak ( https://www.thingspeak.com ) is an analytic IoT platform service that allows you to aggregate, visualize, and 
  analyze live data streams in the cloud. Visit https://www.thingspeak.com to sign up for a free account and create a channel.  
  
  Documentation for the ThingSpeak Communication Library for Arduino is in the README.md folder where the library was installed.
  See https://www.mathworks.com/help/thingspeak/index.html for the full ThingSpeak documentation.
  
  For licensing information, see the accompanying license file.
  
  Copyright 2020, The MathWorks, Inc.
*/

// Including all the required Libraries and Files ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <WiFiNINA.h>          // Include Library for connecting to wifi
#include <RTCZero.h>           // Include a library to keep track of the time
#include <algorithm>           // Include algorithm for std::any_of
#include "secrets.h"           // Inlcude the file that contain SSID, Password, API Channel ID and Keys
#include "Arduino_BHY2Host.h"  // BHY2Host library for sensor data from Nicla
#include "ThingSpeak.h"        // always include thingspeak header file after other header files and custom macros

// Defining some key variables needed / grabbing them from secrets.h ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char ssid[] = SECRET_SSID;               // deifine network SSID (name) from secrets.h or define your own
char pass[] = SECRET_PASS;               // your network password
unsigned long ChannelID = SECRET_CH_ID;  // ThingSpeak Channel ID
const char* APIKey = SECRET_W_APIKEY;    // ThingSpeak API Key

RTCZero rtc;
WiFiClient client;                // Initialise a client for connecting to WIFI
SensorBSEC bsec(SENSOR_ID_BSEC);  // Define varibale name for Bosch Sensortec Environmental Cluster BME688 to access the air quality (IAQ)

// Inital Setup Function ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);  // Initialize serial communication at defined baud rate
  rtc.begin();
  rtc.setDateTime(__DATE__, __TIME__);        // Set the date and time (optional)
  BHY2Host.begin(false, NICLA_VIA_ESLOV);     // Begin collecting Nicla BHY2 Data over Eslov
  delay(2500);                                // Give delay for for Serial a chance to connect
  bsec.begin();                               // Initalise the BSEC Sensor and the data it provides
  Serial.println("BSEC sensor initialised");  // Serial Debug Output
}

// Main Function Loop ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void loop() {
  BHY2Host.update();                 // Updating the Sensor readings
  static auto lastCheck = millis();  // starting a clock

  // Here we only grab 7/8 data values in the dictionary and store it as a list of floats
  float sensorReadings[] = {
    bsec.iaq_s(),     // The IAQ value for stationary whilst stationary
    bsec.b_voc_eq(),  // The breath VOC equivalent (ppm)
    bsec.co2_eq(),    // The CO2 equivalent (ppm) [400,]
    bsec.accuracy(),  // accuracy level: [0-3]
    bsec.comp_t(),    // The compensated temperature (Celsius)
    bsec.comp_h(),    // Compensated humidity
    bsec.comp_g()     // compensated gas resistance (Ohms)
  };

  if (WiFi.status() != WL_CONNECTED) {       // In the event that the wifi is not set / lost
    Serial.println("Connecting to wifi ");   // Debug message signalling wifi reconnect
    while (WiFi.status() != WL_CONNECTED) {  // Wait for wifi to connect
      WiFi.begin(ssid, pass);                // initalise wifi using given ssid and password
      Serial.println(".");                   // output to serial to shown reconnect attempt
      delay(2500);                           // delay until reconnect
    }
    Serial.println("Connected to WiFi");  // Serial output if connection succesful
    ThingSpeak.begin(client);             // Initialize connection to ThingSpeak
  }
  if (millis() - lastCheck >= 30000) {    // wait until 30s passed:
    lastCheck = millis();                 // reset clock counter
    for (float value : sensorReadings) {  // simple loop through all value
      std::cout << value << " ";          //
    }                                     //
    std::cout << std::endl;
    if (std::any_of(std::begin(sensorReadings), std::end(sensorReadings), [](float value) {
          return value != 0.0f;  // Check if the value is non-zero
        })) {
      int items = sizeof(sensorReadings) / sizeof(sensorReadings[0]);  //
      for (int i = 0; i < items; i++) {                                //
        ThingSpeak.setField(i + 1, sensorReadings[i]);                 //
      }                                                                //
      ThingSpeak.setStatus("BSEC Values updated at: " + rtc.now());    //
      int x = ThingSpeak.writeFields(ChannelID, APIKey);               // write to the specified ThingSpeak channel
      if (x == 200) {                                                  //
        Serial.println("Channel update successful.");                  //
      } else {                                                         //
        Serial.println(" HTTP error code " + String(x));               //
      }
    }
  }
}
