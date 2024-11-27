#include <Wire.h>        // Library for I2C communication with Nicla (needed for BSEC2)
#include <WiFiNINA.h>    // Library for Wi-Fi connectivity
#include <WiFiUdp.h>     // Library for UDP communication over Wi-Fi
#include <RTCZero.h>     // Library for Real Time Clock (RTC) on MKR boards
#include "secrets.h"     // Include file with sensitive info like SSID, password, ThingSpeak API keys
#include "ThingSpeak.h"  // ThingSpeak library for cloud data logging

WiFiClient client;  // Client to establish Wi-Fi connections
RTCZero rtc;        // Real-time clock instance for managing date and time


void setup() {
  Wire.begin();          // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output debug
  rtc.begin();
  wifiConnect();
}
// ================================================================================================================================================================================================
// Main Function Loop
// ================================================================================================================================================================================================

void loop() {
  if (WiFi.status() != WL_CONNECTED) wifiConnect();
  Wire.requestFrom(2, 6);   // request 6 bytes from slave device #2
  while (Wire.available())  // slave may send less than requested
  {
    char c = Wire.read();  // receive a byte as character
    Serial.print(c);       // print the character
  }
}


// ================================================================================================================================================================================================
// Function to connect to Wi-Fi and initialize the ThingSpeak client
// ================================================================================================================================================================================================

void wifiConnect() {
  Serial.println("Connecting to WiFi...");  // Debug message indicating Wi-Fi connection attempt
  while (WiFi.status() != WL_CONNECTED) {   // Wait for Wi-Fi connection to be established
    WiFi.begin(SECRET_SSID, SECRET_PASS);   // Initialize Wi-Fi using the provided SSID and password
    delay(5000);                            // Wait 5 seconds before attempting to reconnect
  }
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