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
// Including all the required Libraries and Files --------------------------------------------------------------------------------------
#include <WiFiNINA.h>          // Library for connecting to Wi-Fi
#include <WiFiUdp.h>           // Library for UDP communication over Wi-Fi
#include <RTCZero.h>           // Library for internal RTC (Real Time Clock) on Arduino Zero or MKR boards
#include "secrets.h"           // Include file containing sensitive info (SSID, Password, API Channel ID, Keys)
#include "Arduino_BHY2Host.h"  // Library for sensor data from Nicla Vision/BME688 sensor
#include "ThingSpeak.h"        // ThingSpeak communication library for data logging to the cloud

// Defining key variables needed, from secrets.h if avaliable -------------------------------------------------------------------------------
char ssid[] = SECRET_SSID;               // Wi-Fi network SSID from secrets.h
char pass[] = SECRET_PASS;               // Wi-Fi network password
unsigned long ChannelID = SECRET_CH_ID;  // ThingSpeak Channel ID for data upload
const char* APIKey = SECRET_W_APIKEY;    // ThingSpeak API Key for authentication

Sensor temp(SENSOR_ID_TEMP);
Sensor gas(SENSOR_ID_GAS);
Sensor pres(SENSOR_ID_BARO);
SensorQuaternion quat(SENSOR_ID_RV);
SensorBSEC bsec(uint8_t(171));;  // Instance of SensorBSEC for interacting with Bosch BME688 sensor to get IAQ data

WiFiClient client;  // Client to establish Wi-Fi connections
RTCZero rtc;        // Real-time clock instance for managing date and time

// Inital Setup Function ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Initial Setup Function -------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 baud rate for debugging
  BHY2Host.begin();    // Begin data collection from the Nicla BHY2 sensor over Eslov (I2C communication)
  bsec.begin();        // Initialize the BSEC (Bosch Sensor) library for air quality data acquisition
  temp.begin();
  gas.begin();
  pres.begin();
  quat.begin();
  rtc.begin();    // Start the RTC (Real-Time Clock) instance
  wifiConnect();  // Connect to Wi-Fi by calling the custom wifiConnect function

  Serial.println("BSEC sensor initialised");  // Debug message indicating the BSEC sensor is initialized
}
// Main Function Loop ------------------------------------------------------------------------------------------------
void loop() {
  bool allZeros = true;                              // Flag to track if all sensor readings are zero
  if (WiFi.status() != WL_CONNECTED) wifiConnect();  // Check Wi-Fi status and reconnect if necessary
  static auto lastCheck = millis();
  BHY2Host.update();  // Update sensor data from the BHY2 host (Nicla Vision or similar sensor)

  // Check sensor values every second
  if (millis() - lastCheck >= 2000) {
    lastCheck = millis();
    Serial.println(String("rotation: ") + quat.toString());
    Serial.println(String("temperature: ") + String(int(temp.value())));
    Serial.println(String("gas: ") + String(gas.value()));
    Serial.println(String("pressure: ") + pres.toString());
    Serial.println(String("BSEC info: ") + bsec.toString());

    // Grab 7/8 sensor values in the dictionary and store them in an array of floats
    float sensorReadings[] = {
      bsec.iaq_s(),     // IAQ value (Indoor Air Quality) when stationary
      bsec.b_voc_eq(),  // Breath VOC equivalent (ppm)
      bsec.co2_eq(),    // CO2 equivalent (ppm), typically starts from 400 ppm
      bsec.accuracy(),  // Accuracy level of the sensor readings (0-3)
      bsec.comp_t(),    // Compensated temperature (in Celsius)
      bsec.comp_h(),    // Compensated humidity (in %)
      bsec.comp_g()     // Compensated gas resistance (Ohms)
    };

    int items = sizeof(sensorReadings) / sizeof(sensorReadings[0]);  // Get the number of items in the sensorReadings array
    for (int i = 0; i < items; i++) {
      ThingSpeak.setField(i + 1, sensorReadings[i]);  // Assign each sensor reading to the corresponding field on ThingSpeak
      Serial.print(sensorReadings[i]);
      Serial.print(", ");
      if (sensorReadings[i] != 0) allZeros = false;  // If any value is non-zero, set the flag to false
    }
    Serial.println();
    if (!allZeros) {
      String msg = "BSEC Values updated at: " + printTime();  // Construct the status message with the current timestamp
      ThingSpeak.setStatus(msg);                              // Set the ThingSpeak channel status with the timestamp message
      Serial.println(msg);                                    // Print the status message to the Serial Monitor
      int x = ThingSpeak.writeFields(ChannelID, APIKey);      // Write the fields to ThingSpeak
      if (x == 200) {                                         // If the update is successful
        Serial.println("Channel update successful.");         // Print success message
        Serial.println("6");                                  // Debugging label for sensor readings
      }
      else {                                                // If there was an error with the HTTP request
        Serial.println(" HTTP error code " + String(x));      // Print HTTP error code to help debug
      }
    }
  }
}
// Function to connect to Wi-Fi and initialize the ThingSpeak client ---------------------------------------------------
void wifiConnect() {
  Serial.println("Connecting to WiFi...");  // Debug message indicating Wi-Fi connection attempt

  // Wait for Wi-Fi connection to be established
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, pass);  // Initialize Wi-Fi using the provided SSID and password
    Serial.print(".");       // Output a dot to show reconnect attempts
    delay(5000);             // Wait 5 seconds before attempting to reconnect
  }

  // Once connected to Wi-Fi, output  success messages
  Serial.println();
  Serial.println("Connected to WiFi");
  delay(2000);                                    // Wait for 2 seconds to ensure the Wi-Fi connection is stable
  Serial.println("Getting Time...");              // Output message indicating that we are fetching time
  getTime();                                      // Call the function to get the current time via NTP
  delay(2000);                                    // Wait 2 seconds after getting the time
  Serial.print("Time is: ");                      // Output message showing the current time
  Serial.println(printTime());                    // Print the current time formatted by the printTime() function
  ThingSpeak.begin(client);                       // Initialize the ThingSpeak client for data communication
  Serial.println("ThingSpeak Client Connected");  // Output confirmation of the ThingSpeak client connection
}
// Function to get time from the NTP server and set the RTC epoch -----------------------------------------------
void getTime() {
  unsigned long epoch;                  // Variable to store the epoch time
  int numberOfTries = 0, maxTries = 6;  // Set max retries in case NTP fails

  // Attempt to get the epoch time from Wi-Fi (NTP)
  do {
    epoch = WiFi.getTime();                              // Fetch the time from the Wi-Fi connection (NTP)
    numberOfTries++;                                     // Increment the retry counter
  } while ((epoch == 0) && (numberOfTries < maxTries));  // Retry if epoch is 0 (no NTP response)

  if (numberOfTries == maxTries) {      // If the maximum retries are reached
    Serial.print("NTP unreachable!!");  // Print error message
    wifiConnect();

  }
  else {
    Serial.print("Epoch received: ");  // Print the fetched epoch time
    Serial.println(epoch);             // Print the actual epoch value
    rtc.setEpoch(epoch);               // Set the RTC with the fetched epoch time
    Serial.println();                  // Newline for readability
  }
}

// Function to format and print the current time from the RTC -------------------------------------------
String printTime() {
  String day = String(rtc.getDay());          // Get current day from RTC
  String month = String(rtc.getMonth());      // Get current month from RTC
  String hour = String(rtc.getHours());       // Get current hour from RTC
  String minute = String(rtc.getMinutes());   // Get current minute from RTC
  String seconds = String(rtc.getSeconds());  // Get current seconds from RTC

  return day + "/" + month + " " + hour + ":" + minute + ":" + seconds;  // Return formatted time string in the format: "DD/MM HH:MM:SS"
}
