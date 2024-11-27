
#include <Wire.h>              // Library for I2C communication with Nicla (needed for BSEC2)
#include <WiFiNINA.h>          // Library for Wi-Fi connectivity
#include <WiFiUdp.h>           // Library for UDP communication over Wi-Fi
#include <RTCZero.h>           // Library for Real Time Clock (RTC) on MKR boards
#include "secrets.h"           // Include file with sensitive info like SSID, password, ThingSpeak API keys
#include "ThingSpeak.h"        // ThingSpeak library for cloud data logging
#include <Arduino_BHY2Host.h>  //


SensorXYZ accel(SENSOR_ID_ACC);
SensorXYZ gyro(SENSOR_ID_GYRO);
Sensor temp(SENSOR_ID_TEMP);
Sensor gas(SENSOR_ID_GAS);
SensorQuaternion rotation(SENSOR_ID_RV);

WiFiClient client;  // Client to establish Wi-Fi connections
RTCZero rtc;        // Real-time clock instance for managing date and time

int size = 5;
uint8_t receivedData[5];

void setup() {
  Wire.begin();          // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output debug

  BHY2Host.begin();

  accel.begin();
  gyro.begin();
  temp.begin();
  gas.begin();
  rotation.begin();

  rtc.begin();
  wifiConnect();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) wifiConnect();

  static unsigned long lastCheck  = millis();
  BHY2Host.update();

  if (millis() - lastCheck  >= 2000) {
    lastCheck  = millis();
    Serial.println(String("acceleration: ") + accel.toString());
    Serial.println(String("gyroscope: ") + gyro.toString());



    Wire.requestFrom(2, size);        // Request 5 bytes from slave device #2
    Serial.print("Received data: ");  // Print received data

    if (Wire.available() == size) {  // Ensure 5 bytes are received
      for (int i = 0; i < size; i++) {
        receivedData[i] = Wire.read();
        ThingSpeak.setField(i + 1, receivedData[i]);
        Serial.print(receivedData[i]);
        Serial.print(" ");
      }
      Serial.println();
    } else {
      Serial.println("Error: Received less than expected bytes!");
      while (Wire.available()) Wire.read();                     // Clear buffer
    }                                                           // Newline after printing all data
    String msg = "Values updated at: " + printTime();           // Construct the status message with the current timestamp
    ThingSpeak.setStatus(msg);                                  // Set the ThingSpeak channel status with the timestamp message
    Serial.println(msg);                                        // Print the status message to the Serial Monitor
    int x = ThingSpeak.writeFields(ChannelIDs[2], APIKeys[2]);  // Write the fields to ThingSpeak
    if (x == 200) {                                             // If the update is successful
      Serial.println("Channel update successful.");             // Print success message
    } else {                                                    // If there was an error with the HTTP request
      Serial.println(" HTTP error code " + String(x));          // Print HTTP error code to help debug
    }
  }
}

void sendData() {  //
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