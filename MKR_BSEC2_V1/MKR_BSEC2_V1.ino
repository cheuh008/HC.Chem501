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
#include <RTCZero.h>           // Library for internal RTC (Real Time Clock) on Arduino Zero or MKR boards
#include "secrets.h"           // Include file containing sensitive info (SSID, Password, API Channel ID, Keys)
#include "Arduino_BHY2Host.h"  // Library for sensor data from Nicla Vision/BME688 sensor
#include "ThingSpeak.h"        // ThingSpeak communication library for data logging to the cloud

// Defining key variables needed, from secrets.h if avaliable -------------------------------------------------------------------------------
char ssid[] = SECRET_SSID;               // Wi-Fi network SSID from secrets.h
char pass[] = SECRET_PASS;               // Wi-Fi network password
unsigned long ChannelID = SECRET_CH_ID;  // ThingSpeak Channel ID for data upload
const char* APIKey = SECRET_W_APIKEY;    // ThingSpeak API Key for authentication


SensorBSEC bsec(SENSOR_ID_BSEC);     // Instance of SensorBSEC for interacting with Bosch BME688 sensor to get IAQ data
SensorBSEC2 bsec2(SENSOR_ID_BSEC2);  // Init BSEC2 for Gas Classifier

// Example BSEC2CONFIG from BSEC2 Library where gas0: ambient and gas 1: Alcohol
/* 
 const uint8_t BSEC2CONFIG[] = {
  0, 0, 2, 2, 189, 1, 0, 0, 0, 0, 0, 0, 213, 8, 0, 0, 52, 0, 1, 0, 0, 168, 19, 73,
  64, 49, 119, 76, 0, 192, 40, 72, 0, 192, 40, 72, 137, 65, 0, 191, 205, 204, 204, 
  190, 0, 0, 64, 191, 225, 122, 148, 190, 10, 0, 3, 0, 216, 85, 0, 100, 0, 0, 96, 
  64, 23, 183, 209, 56, 28, 0, 2, 0, 0, 244, 1, 150, 0, 50, 0, 0, 128, 64, 0, 0, 
  32, 65, 144, 1, 0, 0, 112, 65, 0, 0, 0, 63, 16, 0, 3, 0, 10, 215, 163, 60, 10, 
  215, 35, 59, 10, 215, 35, 59, 13, 0, 5, 0, 0, 0, 0, 0, 100, 254, 131, 137, 87, 
  88, 0, 9, 0, 7, 240, 150, 61, 0, 0, 0, 0, 0, 0, 0, 0, 28, 124, 225, 61, 52, 128, 
  215, 63, 0, 0, 160, 64, 0, 0, 0, 0, 0, 0, 0, 0, 205, 204, 12, 62, 103, 213, 39, 
  62, 230, 63, 76, 192, 0, 0, 0, 0, 0, 0, 0, 0, 145, 237, 60, 191, 251, 58, 64, 63, 
  177, 80, 131, 64, 0, 0, 0, 0, 0, 0, 0, 0, 93, 254, 227, 62, 54, 60, 133, 191, 0, 
  0, 64, 64, 12, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 173, 6, 11, 0, 0, 0, 2, 231, 201, 
  67, 189, 125, 37, 201, 61, 179, 41, 106, 189, 97, 167, 196, 61, 84, 172, 113, 62, 
  155, 213, 214, 61, 133, 10, 114, 61, 62, 67, 214, 61, 56, 97, 57, 62, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 42, 215, 83, 190, 42, 215, 83, 62, 0, 0, 0, 0, 0, 0, 0, 0, 97, 
  101, 165, 61, 88, 151, 51, 190, 184, 89, 165, 62, 240, 207, 20, 191, 47, 208, 53, 
  63, 177, 43, 63, 190, 176, 56, 145, 189, 228, 194, 10, 191, 173, 194, 44, 191, 0, 
  0, 0, 0, 146, 253, 150, 61, 217, 5, 157, 59, 36, 134, 171, 190, 159, 38, 128, 59, 
  58, 78, 29, 189, 204, 88, 63, 191, 210, 42, 125, 190, 59, 171, 228, 190, 78, 165, 
  243, 190, 0, 0, 0, 0, 171, 98, 187, 188, 83, 234, 57, 191, 66, 87, 75, 62, 209, 
 }
 */
// Training Data 1 where ... gas 1 is Ambient and gas 0 is acetone
const uint8_t BSEC2CONFIG[] = { 
  0, 1, 6, 2, 189, 1, 0, 0, 0, 0, 0, 0, 127, 7, 0, 0, 56, 0, 1, 0, 0, 168, 19, 73, 64, 49, 119, 76, 0, 0, 97, 69, 0, 0, 97, 69, 10, 0, 3, 0, 0, 0, 96, 64, 23, 183, 209, 56, 43, 24, 149, 60, 140, 74, 106, 188, 43, 24, 149, 60, 216, 129, 243, 190, 151, 255, 80, 190, 216, 129, 243, 190, 8, 0, 2, 0, 0, 0, 72, 66, 16, 0, 3, 0, 10, 215, 163, 60, 10, 215, 35, 59, 10, 215, 35, 59, 13, 0, 5, 0, 0, 0, 0, 0, 100, 254, 131, 137, 87, 88, 0, 9, 0, 7, 240, 150, 61, 0, 0, 0, 0, 0, 0, 0, 0, 28, 124, 225, 61, 52, 128, 215, 63, 0, 0, 160, 64, 0, 0, 0, 0, 0, 0, 0, 0, 205, 204, 12, 62, 103, 213, 39, 62, 230, 63, 76, 192, 0, 0, 0, 0, 0, 0, 0, 0, 145, 237, 60, 191, 251, 58, 64, 63, 177, 80, 131, 64, 0, 0, 0, 0, 0, 0, 0, 0, 93, 254, 227, 62, 54, 60, 133, 191, 0, 0, 64, 64, 12, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45, 5, 11, 0, 0, 0, 2, 239, 34, 139, 189, 223, 109, 128, 189, 69, 179, 72, 63, 135, 169, 6, 62, 151, 167, 21, 62, 86, 74, 68, 191, 4, 70, 89, 62, 35, 142, 11, 191, 36, 178, 147, 62, 248, 62, 222, 62, 220, 208, 67, 63, 205, 173, 167, 189, 44, 0, 14, 63, 21, 25, 1, 62, 182, 12, 48, 62, 117, 53, 34, 188, 0, 0, 0, 0, 81, 166, 232, 190, 75, 29, 163, 61, 133, 163, 181, 190, 107, 160, 247, 188, 163, 73, 217, 190, 35, 78, 220, 62, 0, 0, 0, 0, 0, 221, 130, 62, 92, 196, 59, 189, 133, 230, 222, 62, 211, 97, 157, 189, 120, 87, 55, 189, 209, 137, 255, 190, 99, 113, 223, 190, 173, 63, 93, 189, 198, 57, 81, 190, 121, 220, 151, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 135, 120, 115, 62, 82, 156, 199, 190, 92, 149, 34, 191, 177, 35, 198, 189, 162, 58, 200, 189, 228, 95, 48, 63, 209, 16, 39, 191, 61, 180, 3, 63, 170, 57, 58, 191, 192, 217, 42, 62, 221, 178, 143, 190, 66, 178, 148, 61, 166, 6, 214, 190, 158, 14, 157, 190, 76, 126, 147, 189, 117, 0, 17, 63, 146, 132, 22, 191, 123, 59, 70, 63, 148, 171, 112, 188, 78, 76, 214, 62, 67, 38, 141, 190, 143, 225, 137, 190, 236, 12, 247, 189, 163, 95, 30, 191, 45, 167, 13, 191, 54, 127, 53, 189, 26, 146, 194, 61, 161, 69, 117, 63, 181, 176, 168, 62, 111, 6, 108, 63, 24, 30, 205, 190, 126, 252, 121, 62, 102, 223, 153, 61, 50, 139, 27, 189, 127, 249, 239, 190, 213, 112, 75, 63, 145, 177, 208, 190, 97, 98, 237, 62, 49, 111, 91, 191, 155, 96, 127, 63, 201, 171, 114, 62, 61, 13, 136, 190, 190, 136, 129, 62, 154, 154, 122, 190, 189, 83, 38, 191, 192, 209, 144, 62, 213, 67, 202, 190, 61, 69, 136, 62, 193, 175, 40, 191, 146, 123, 21, 189, 253, 95, 62, 62, 100, 116, 27, 63, 41, 162, 176, 62, 92, 230, 213, 190, 8, 87, 30, 62, 120, 107, 27, 190, 15, 7, 3, 190, 125, 36, 25, 61, 219, 223, 100, 191, 90, 66, 135, 62, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 44, 154, 149, 189, 194, 150, 255, 62, 249, 214, 60, 62, 96, 151, 152, 190, 35, 91, 54, 62, 171, 199, 43, 190, 10, 241, 53, 189, 227, 186, 111, 62, 112, 202, 43, 62, 127, 16, 223, 61, 76, 166, 157, 190, 83, 50, 6, 62, 162, 238, 18, 191, 186, 228, 133, 190, 179, 82, 126, 190, 162, 45, 20, 62, 109, 194, 17, 62, 71, 49, 60, 190, 51, 218, 192, 61, 28, 140, 166, 62, 178, 43, 94, 63, 251, 9, 104, 62, 246, 123, 148, 63, 46, 147, 2, 63, 120, 159, 168, 63, 195, 211, 39, 190, 154, 107, 225, 61, 103, 176, 25, 191, 233, 56, 233, 189, 237, 1, 64, 191, 100, 242, 97, 190, 167, 32, 235, 61, 125, 223, 201, 189, 174, 56, 93, 62, 184, 10, 58, 63, 39, 169, 76, 190, 53, 94, 228, 190, 42, 240, 135, 189, 239, 8, 138, 62, 106, 250, 146, 62, 246, 137, 74, 190, 169, 230, 133, 190, 130, 4, 30, 191, 205, 218, 68, 62, 128, 114, 17, 63, 77, 50, 202, 62, 27, 137, 146, 62, 174, 103, 185, 189, 29, 185, 177, 190, 210, 219, 154, 61, 253, 179, 124, 191, 175, 179, 109, 190, 28, 184, 93, 191, 86, 244, 163, 190, 209, 175, 194, 189, 47, 18, 165, 190, 117, 159, 190, 189, 26, 3, 177, 63, 124, 24, 135, 62, 13, 188, 168, 63, 109, 133, 70, 190, 202, 178, 149, 190, 93, 167, 219, 61, 178, 101, 140, 62, 56, 108, 88, 63, 129, 13, 222, 190, 129, 84, 4, 188, 197, 166, 218, 190, 50, 167, 108, 189, 119, 177, 236, 62, 18, 100, 226, 190, 193, 173, 26, 191, 135, 252, 140, 188, 70, 190, 149, 62, 225, 80, 15, 191, 99, 214, 145, 190, 135, 13, 183, 189, 128, 96, 120, 63, 194, 221, 237, 62, 51, 145, 26, 63, 246, 97, 52, 190, 21, 147, 208, 190, 113, 148, 205, 189, 135, 9, 30, 63, 73, 70, 182, 62, 148, 87, 83, 62, 75, 115, 202, 189, 56, 10, 65, 61, 16, 87, 175, 61, 19, 63, 95, 63, 159, 148, 172, 62, 200, 202, 87, 62, 177, 186, 129, 62, 6, 44, 236, 190, 139, 39, 21, 62, 146, 141, 119, 189, 76, 12, 89, 189, 18, 40, 24, 62, 122, 91, 33, 63, 144, 54, 80, 62, 227, 220, 114, 191, 186, 67, 112, 191, 148, 95, 178, 63, 0, 0, 0, 0, 183, 51, 219, 190, 225, 117, 47, 63, 119, 26, 184, 190, 0, 0, 0, 0, 168, 225, 78, 191, 38, 228, 254, 190, 140, 201, 143, 63, 0, 0, 0, 0, 173, 169, 251, 62, 151, 156, 165, 190, 72, 188, 209, 190, 0, 0, 0, 0, 247, 108, 107, 62, 12, 131, 230, 190, 50, 10, 165, 190, 0, 0, 0, 0, 57, 117, 138, 189, 51, 50, 204, 62, 116, 51, 159, 189, 0, 0, 0, 0, 57, 217, 50, 191, 232, 120, 77, 190, 251, 86, 222, 61, 0, 0, 0, 0, 126, 70, 180, 190, 9, 185, 130, 63, 252, 115, 245, 190, 0, 0, 0, 0, 151, 143, 95, 191, 237, 28, 203, 62, 45, 157, 56, 62, 0, 0, 0, 0, 100, 23, 200, 62, 13, 151, 215, 62, 194, 100, 22, 191, 0, 0, 0, 0, 10, 10, 3, 9, 152, 127, 72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 159, 100, 23, 74, 116, 228, 19, 74, 204, 163, 16, 74, 88, 16, 104, 72, 102, 224, 112, 72, 163, 60, 121, 72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 185, 99, 93, 72, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 168, 75, 9, 74, 153, 42, 6, 74, 210, 62, 3, 74, 94, 186, 73, 72, 51, 75, 81, 72, 207, 17, 88, 72, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 145, 1, 254, 0, 2, 1, 5, 48, 117, 100, 0, 44, 1, 112, 23, 151, 7, 132, 3, 197, 0, 92, 4, 144, 1, 64, 1, 64, 1, 144, 1, 48, 117, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 48, 117, 48, 117, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 100, 0, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 100, 0, 100, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 112, 23, 112, 23, 112, 23, 112, 23, 8, 7, 8, 7, 8, 7, 8, 7, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 112, 23, 112, 23, 112, 23, 112, 23, 255, 255, 255, 255, 220, 5, 220, 5, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 220, 5, 220, 5, 220, 5, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 48, 117, 0, 1, 0, 5, 0, 2, 0, 10, 0, 30, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 64, 1, 100, 0, 100, 0, 100, 0, 200, 0, 200, 0, 200, 0, 64, 1, 64, 1, 64, 1, 10, 1, 0, 0, 0, 0, 0, 129, 4, 0, 0 
};

//Sensor temp(SENSOR_ID_TEMP);//
//Sensor gas(SENSOR_ID_GAS);//
//Sensor pres(SENSOR_ID_BARO);//
//SensorQuaternion quat(SENSOR_ID_RV);//

WiFiClient client;  // Client to establish Wi-Fi connections
RTCZero rtc;        // Real-time clock instance for managing date and time

// Inital Setup Function ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Initial Setup Function -------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 baud rate for debugging
  BHY2Host.begin();    // Begin data collection from the Nicla BHY2 sensor over Eslov (I2C communication)
  //temp.begin();
  //gas.begin();
  //pres.begin();
  //quat.begin();
  while (!bsec.begin())
    ;  // Initialize the BSEC (Bosch Sensor) library for air quality data acquisition
  while (!bsec2.begin())
    ;  // Initialize the BSEC (Bosch Sensor) library for air quality data acquisition

  rtc.begin();    // Start the RTC (Real-Time Clock) instance
  wifiConnect();  // Connect to Wi-Fi by calling the custom wifiConnect function

  Serial.println("BSEC sensor initialised");  // Debug message indicating the BSEC sensor is initialized
  bsec.begin();                               // Initialize the BSEC (Bosch Sensor) library for air quality data acquisition
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
    //Serial.println(String("rotation: ") + quat.toString());
    //Serial.println(String("temperature: ") + String(int(temp.value())));
    //Serial.println(String("gas: ") + String(gas.value()));
    //Serial.println(String("pressure: ") + pres.toString());
    //Serial.println(String("BSEC info: ") + bsec.toString());

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
      } else {                                                // If there was an error with the HTTP request
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

  } else {
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
