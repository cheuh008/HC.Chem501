/*
  RTCZero Epoch Example Uused  
  Epoch time example for Arduino Zero and MKR1000
  created by Sandeep Mistry <s.mistry@arduino.cc>

  Documentation for the ThingSpeak Communication Library for Arduino is in the README.md folder where the library was installed.
  See https://www.mathworks.com/help/thingspeak/index.html for the full ThingSpeak documentation.

  Copyright 2020, The MathWorks, Inc.
*/

// ================================================================================================================================================================================================
// Including all the required Libraries and Files
// ================================================================================================================================================================================================

#include <Wire.h>              // Library for I2C communication with Nicla (needed for BSEC2)
#include <WiFiNINA.h>          // Library for Wi-Fi connectivity
#include <WiFiUdp.h>           // Library for UDP communication over Wi-Fi
#include <RTCZero.h>           // Library for Real Time Clock (RTC) on MKR boards
#include "secrets.h"           // Include file with sensitive info like SSID, password, ThingSpeak API keys
#include "ThingSpeak.h"        // ThingSpeak library for cloud data logging
#include "Arduino_BHY2Host.h"  // Library for BHY2 sensor data from Nicla Vision/BME688

// ================================================================================================================================================================================================
// iniitlisinf sesnors global variable
// ================================================================================================================================================================================================

Sensor temp(SENSOR_ID_TEMP);          // Temperature sensor instance
Sensor gas(SENSOR_ID_GAS);            // Gas sensor instance for air quality
Sensor pres(SENSOR_ID_BARO);          // Barometric pressure sensor instance
SensorQuaternion quat(SENSOR_ID_RV);  // Quaternion sensor for rotational vector data
SensorBSEC bsec(SENSOR_ID_BSEC);      // BSEC sensor for advanced air quality measurements

WiFiClient client;  // Client to establish Wi-Fi connections
RTCZero rtc;        // Real-time clock instance for managing date and time

// ================================================================================================================================================================================================
// Inital Setup Function
// ================================================================================================================================================================================================

void setup() {
  Wire.begin();                               // Start I2C communication as master
  Serial.begin(9600);                         // Initialize serial communication at 9600 baud rate for debugging
  BHY2Host.begin();                           // Begin data collection from the Nicla BHY2 sensor over Eslov (I2C communication)
  while (!BHY2Host.begin())                   // Wait for the BHY2 host to initialize
    ;                                         //
  temp.begin();                               //
  gas.begin();                                //
  pres.begin();                               //
  quat.begin();                               //
  bsec.begin();                               // Initialize the BSEC (Bosch Sensor) library for air quality data acquisition
  while (!bsec.begin())                       //
    ;                                         //
  Serial.println("BSEC sensor initialised");  // Debug message indicating the BSEC sensor is initialized

  rtc.begin();    // Start the RTC (Real-Time Clock) instance
  wifiConnect();  // Connect to Wi-Fi by calling the custom wifiConnect function
}

// ================================================================================================================================================================================================
// Main Function Loop
// ================================================================================================================================================================================================

void loop() {

  bool allZeros = true;                              // Flag to track if all sensor readings are zero
  if (WiFi.status() != WL_CONNECTED) wifiConnect();  // Check Wi-Fi status and reconnect if necessary
  static auto lastCheck = millis();                  //
  BHY2Host.update();                                 // Update sensor data from the BHY2 host (Nicla Vision or similar sensor)
  Wire.requestFrom(0x10, 87);                        //
                                                     //
  if (millis() - lastCheck >= 2000) {                // Check sensor values every second
    lastCheck = millis();                            //

    String sesnorReadings[] = {
       quat.toString()),
       String(int(temp.value())),
       String(gas.value()),
       pres.toString()
    };

    sendData(sesnorReadings, "Default Values Updated ", channelIDs[0], APIKeys[0]);

    String bsecReadings[] = {
      String(bsec.iaq_s()),     // IAQ value (Indoor Air Quality) when stationary
      String(bsec.b_voc_eq()),  // Breath VOC equivalent (ppm)
      String(bsec.co2_eq()),    // CO2 equivalent (ppm), typically starts from 400 ppm
      String(bsec.accuracy()),  // Accuracy level of the sensor readings (0-3)
      String(bsec.comp_t()),    // Compensated temperature (in Celsius)
      String(bsec.comp_h()),    // Compensated humidity (in %)
      String(bsec.comp_g())     // Compensated gas resistance (Ohms)
    };

    sendData(bsecReadings, "BSEC Values Updated ", channelIDs[1], APIKeys[1]);

    String gasPrediction[] = {};

    sendData(gasPrediction, "Gases Deteced ", channelIDs[2], APIKeys[2]);
  }
}


// ================================================================================================================================================================================================
// Function to connect to Wi-Fi and initialize the ThingSpeak client
// ================================================================================================================================================================================================

void wifiConnect() {

  Serial.println("Connecting to WiFi...");        // Debug message indicating Wi-Fi connection attempt
  while (WiFi.status() != WL_CONNECTED) {         // Wait for Wi-Fi connection to be established
    WiFi.begin(SECRET_SSID, SECRET_PASS);         // Initialize Wi-Fi using the provided SSID and password
    delay(5000);                                  // Wait 5 seconds before attempting to reconnect
  }                                               //
  getTime();                                      // Call the function to get the current time via NTP
  Serial.print("Time is: ");                      // Output message showing the current time
  Serial.println(printTime());                    // Print the current time formatted by the printTime() function
  ThingSpeak.begin(client);                       // Initialize the ThingSpeak client for data communication
  Serial.println("ThingSpeak Client Connected");  // Output confirmation of the ThingSpeak client connection
}

// ================================================================================================================================================================================================
// Function to get time from the NTP server and set the RTC epoch
// ================================================================================================================================================================================================

void getTime() {
  unsigned long epoch;                                   // Variable to store the epoch time
  int numberOfTries = 0, maxTries = 6;                   // Set max retries in case NTP fails
                                                         //
  do {                                                   // Attempt to get the epoch time from Wi-Fi (NTP)
    epoch = WiFi.getTime();                              // Fetch the time from the Wi-Fi connection (NTP)
    numberOfTries++;                                     // Increment the retry counter
  } while ((epoch == 0) && (numberOfTries < maxTries));  // Retry if epoch is 0 (no NTP response)
                                                         //
  if (numberOfTries == maxTries) {                       // If the maximum retries are reached
    Serial.print("NTP unreachable!!");                   // Print error message
    wifiConnect();                                       //
                                                         //
  } else {                                               //
    Serial.print("Epoch received: ");                    // Print the fetched epoch time
    Serial.println(epoch);                               // Print the actual epoch value
    rtc.setEpoch(epoch);                                 // Set the RTC with the fetched epoch time
    Serial.println();                                    // Newline for readability
  }
}

// ================================================================================================================================================================================================
// Function to format and print the current time from the RTC
// ================================================================================================================================================================================================

String printTime() {
  String day = String(rtc.getDay());          // Get current day from RTC
  String month = String(rtc.getMonth());      // Get current month from RTC
  String hour = String(rtc.getHours());       // Get current hour from RTC
  String minute = String(rtc.getMinutes());   // Get current minute from RTC
  String seconds = String(rtc.getSeconds());  // Get current seconds from RTC

  return day + "/" + month + " " + hour + ":" + minute + ":" + seconds;  // Return formatted time string in the format: "DD/MM HH:MM:SS"
}

void sendData(String data[], String msg, ChannelID, APIKey) {

  Serial.print(msg + ": ");
  int items = sizeof(data) / sizeof(data[0]);           // Get the number of items in the sensorReadings array
  for (int i = 0; i < items; i++) {                     //
    ThingSpeak.setField(i + 1, data[i]);                // Assign each sensor reading to the corresponding field on ThingSpeak
    Serial.print(data[i]);                              //
    Serial.print(", ");                                 //
    if (data[i] != 0) allZeros = false;                 // If any value is non-zero, set the flag to false
  }                                                     //
  Serial.println();                                     //
  if (!allZeros) {                                      //
    String msg += " updated at: " + printTime();        // Construct the status message with the current timestamp
    ThingSpeak.setStatus(msg);                          // Set the ThingSpeak channel status with the timestamp message
    Serial.println(msg);                                // Print the status message to the Serial Monitor
    int x = ThingSpeak.writeFields(ChannelID, APIKey);  // Write the fields to ThingSpeak
    if (x == 200) {                                     // If the update is successful
      Serial.println("Channel update successful.");     // Print success message
    } else {                                            // If there was an error with the HTTP request
      Serial.println(" HTTP error code " + String(x));  // Print HTTP error code to help debug
    }
  }
}
