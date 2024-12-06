
#include <Wire.h>              // Library for I2C communication with Nicla (needed for BSEC2)
#include <WiFiNINA.h>          // Library for Wi-Fi connectivity
#include <WiFiUdp.h>           // Library for UDP communication over Wi-Fi
#include <RTCZero.h>           // Library for Real Time Clock (RTC) on MKR boards
#include "Arduino.h"           //
#include "functions.h"         //
#include "secrets.h"           // Include file with sensitive info like SSID, password, ThingSpeak API keys
#include "ThingSpeak.h"        // ThingSpeak library for cloud data logging
#include "Arduino_BHY2Host.h"  // Bosch Host library for managing sensor data

Sensor gas(SENSOR_ID_GAS);        // Gas sensor instance using the GAS sensor ID
Sensor pres(SENSOR_ID_BARO);      // Pressure sensor instance using the BARO sensor ID
SensorBSEC bsec(SENSOR_ID_BSEC);  // Bosch BSEC sensor instance for air quality data

WiFiClient client;  // Client to establish Wi-Fi connections
RTCZero rtc;        // Real-time clock instance for managing date and time

int mode = 2;  // Default mode: 0 for Standalone, 1 for Classifier, 2 for Collector

void setup() {
  Serial.begin(115200);  // start serial for output debug
  BHY2Host.begin();      //
  conditional();
  rtc.begin();
  wifiConnect();
}

void loop() {
  if (mode == 0) BHY2Host.update();
  static unsigned long lastCheck = millis();
  if (WiFi.status() != WL_CONNECTED) wifiConnect();
  if (Serial.available() > 0) {      // Check if data is available on the serial port
    int input = Serial.parseInt();   // Read integer input
    Serial.read();                   // Clear
    if (input >= 0 && input <= 2) {  // Validate the mode
      Wire.beginTransmission(2);     // Begin transmission to slave with address 2
      Wire.write(input);             //
      Wire.endTransmission();        // End transmission
      mode = input;                  // Update Mode
      conditional();                 // Init Sensors
    }
  }
  if (millis() - lastCheck >= 1000) {
    lastCheck = millis();
    getData();
  }
}

void conditional() {  //
  if (mode == 0) {    //
    gas.begin();      // Initialize the gas sensor
    pres.begin();     // Initialize the pressure sensor
    bsec.begin();     // Initialize the Bosch BSEC sensor
    Wire.end();       //
  } else if (mode == 1 || mode == 2) {
    gas.end();     // Initialize the gas sensor
    pres.end();    // Initialize the pressure sensor
    bsec.end();    // Initialize the Bosch BSEC sensor
    Wire.begin();  //
  }
}

void getData() {
  if (mode == 0) {
    String sensorData[8] = {
      String(gas.value()),      // Get the gas sensor value as comp_g is 0 due to oversized byte in liobary (can change to 30 to accomadate)
      String(pres.value()),     // Get the humidity data as a value
      String(bsec.iaq_s()),     // Get the temperature sensor value
      String(bsec.b_voc_eq()),  // Get the pressure sensor value
      String(bsec.co2_eq()),    // Get the IAQ (Indoor Air Quality) value from BSEC
      String(bsec.comp_t()),    // Get the VOC equivalent value from BSEC
      String(bsec.comp_h()),    // Get the CO2 equivalent value from BSEC
      String(bsec.accuracy())   // Get the accuracy level from BSEC
    };
    int size = 8;
    String VOCmsg = "VOC values updated at: " + printTime();            // Construct the status message with the current timestamp
    sendData(sensorData, size, VOCmsg, ChannelIDs[3], APIKeys[3]);      //
  } else if (mode == 1) {                                               //
    int size = 5;                                                       //
    String receivedData[5];                                             //
    Wire.requestFrom(2, size);                                          // Request 5 bytes from slave device #2
    Serial.print("Received data: ");                                    // Print received data
    if (Wire.available() == size) {                                     // Ensure 5 bytes are received
      for (int i = 0; i < size; i++) {                                  //
        receivedData[i] = String(Wire.read());                          //
        Serial.print(receivedData[i]);                                  //
      }                                                                 //
    }                                                                   //
    String BSEC2msg = "BSEC2 values updated at: " + printTime();        // Construct the status message with the current timestamp
    sendData(receivedData, size, BSEC2msg, ChannelIDs[2], APIKeys[2]);  //
  } else if (mode == 2) {                                               //
    int size = 6;
    String data = "";
    while (Wire.available()) {
      char c = Wire.read();  // Read each character from the I2C buffer
      data += c;
    }
    int index = 0;
    String fields[6];
    for (int i = 0; i < size; i++) {
      index = data.indexOf(' ');
      fields[i] = data.substring(0, index);
      data.remove(0, index + 1);
    }
    String collectormsg = "Gas values updated at: " + printTime();
    sendData(fields, size, collectormsg, ChannelIDs[1], APIKeys[1]);
  }
}

void sendData(String data[], int size, String msg, unsigned long channelId, const char* ApiKey) {
  for (int i = 0; i < size; i++) {        // Send data to ThingSpeak and print to Serial for debugging
    ThingSpeak.setField(i + 1, data[i]);  // Set the appropriate field on ThingSpeak (Starts at 1)
    Serial.print(data[i]);                // Print sensor value to Serial
    Serial.print(" ");                    // Add space between values for readability
  }
  Serial.println();                                   // Newline after printing all sensor values
  ThingSpeak.setStatus(msg);                          // Set the ThingSpeak channel status with the timestamp message
  int x = ThingSpeak.writeFields(channelId, ApiKey);  // Write the fields to ThingSpeak
  if (x == 200) {                                     // If the update is successful
    Serial.println("Channel update successful.");     // Print success message
    Serial.println(msg);                              // Print the status message to the Serial Monitor
  } else {                                            // If there was an error with the HTTP request
    Serial.println(" HTTP error code " + String(x));  // Print HTTP error code to help debug
  }
}

void wifiConnect() {
  Serial.println("Connecting to WiFi...");  // Debug message indicating Wi-Fi connection attempt
  while (WiFi.status() != WL_CONNECTED) {   // Wait for Wi-Fi connection to be established
    WiFi.begin(SECRET_SSID, SECRET_PASS);   // Initialize Wi-Fi using the provided SSID and password
    delay(5000);                            // Wait 5 seconds before attempting to reconnect
  }
  getTime();                                      // Call the function to get the current time via NTP
  ThingSpeak.begin(client);                       // Initialize the ThingSpeak client for data communication
  Serial.println("ThingSpeak Client Connected");  // Output confirmation of the ThingSpeak client connection
}

void getTime() {
  unsigned long epoch;                                   // Variable to store the epoch time
  int numberOfTries = 0, maxTries = 6;                   // Set max retries in case NTP fails
  do {                                                   // Attempt to get the epoch time from Wi-Fi (NTP)
    epoch = WiFi.getTime();                              // Fetch the time from the Wi-Fi connection (NTP)
    numberOfTries++;                                     // Increment the retry counter
  } while ((epoch == 0) && (numberOfTries < maxTries));  // Retry if epoch is 0 (no NTP response)
  if (numberOfTries == maxTries) {                       // If the maximum retries are reached
    Serial.print("NTP unreachable!!");                   // Print error message
    wifiConnect();                                       //
  } else {
    Serial.print("Epoch received: ");  // Print the fetched epoch time
    Serial.println(epoch);             // Print the actual epoch value
    rtc.setEpoch(epoch);               // Set the RTC with the fetched epoch time
    Serial.println();                  // Newline for readability
  }
  Serial.print("Time is: ");    // Output message showing the current time
  Serial.println(printTime());  // Print the current time formatted by the printTime() function
}

String printTime() {                          // Returns formatted time: "DD/MM HH:MM:SS"
  String day = String(rtc.getDay());          // Get current day from RTC
  String month = String(rtc.getMonth());      // Get current month from RTC
  String hour = String(rtc.getHours());       // Get current hour from RTC
  String minute = String(rtc.getMinutes());   // Get current minute from RTC
  String seconds = String(rtc.getSeconds());  // Get current seconds from RTC
  return day + "/" + month + " " + hour + ":" + minute + ":" + seconds;
}
