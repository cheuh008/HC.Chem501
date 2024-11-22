
// ================================================================================================================================================================================================
// Note From Authour @cheuh008 @https://github.com/cheuh008/HC.Chem501
// ================================================================================================================================================================================================


// ================================================================================================================================================================================================
// Libaries
// ================================================================================================================================================================================================

#include <Wire.h>              // Library for I2C communication with Nicla (needed for BSEC2)
#include <WiFiNINA.h>          // Library for Wi-Fi connectivity
#include <WiFiUdp.h>           // Library for UDP communication over Wi-Fi
#include <RTCZero.h>           // Library for Real Time Clock (RTC) on MKR boards
#include "secrets.h"           // Include file with sensitive info like SSID, password, ThingSpeak API keys
#include "ThingSpeak.h"        // ThingSpeak library for cloud data logging
#include "Arduino_BHY2Host.h"  // Library for BHY2 sensor data from Nicla Vision/BME688

// ================================================================================================================================================================================================
// iniitlising sesnors global variable
// ================================================================================================================================================================================================

struct SenosrData {
  uint16_t iaq;
  uint16_t iaq_s;
  float b_voc_eq;
  uint32_t co2_eq;
  uint8_t bsec_accu;
  float comp_t;
  float comp_h;
  uint32_t comp_g;
  float gasVal;
  float presVal;
  float tempValue;
  uint8_t gas0;
  uint8_t gas1;
  uint8_t gas2;
  uint8_t gas3;
  uint8_t bsec2_accu;
};

SenosrData sensorData;

WiFiClient client;  // Client to establish Wi-Fi connections
RTCZero rtc;        // Real-time clock instance for managing date and time


// ================================================================================================================================================================================================
// Inital Setup Function
// ================================================================================================================================================================================================

void setup() {
  Serial.begin(115200);
  while (!Serial) { (1); }
  BHY2Host.begin();
  rtc.begin();
  wifiConnect();
  Wire.begin();
  Wire.onReceive(receiveEvent);
}
// ================================================================================================================================================================================================
// Main Function Loop
// ================================================================================================================================================================================================

void loop() {
  BHY2Host.update();
  static auto lastCheck = millis();
  if (WiFi.status() != WL_CONNECTED) wifiConnect();
  Wire.requestFrom(0x10, sizeof(SensorData))) {
    Wire.readBytes((char*)&sensorData, sizeof(SensorData));
    sendData(0);
    sendData(1);
  }
}

void receiveEvent(size_t howMany) {
  int receivedValue = Wire.read(); // Read received value from Master

  Serial.print("Received value: ");
  Serial.println(receivedValue);

  digitalWrite(ledPin, receivedValue % 2); // Toggle LED based on received value
}

// ================================================================================================================================================================================================
// Function to send data to ThingSpeak client
// ================================================================================================================================================================================================

void sendData(int batch) {
  int startField = batch * 8;
  String msg;
  float* dataPtr = (float*)&receivedData;
  for (int i = 0; i < 8; i++) {
    int fieldIndex = startField + i;
    if (fieldIndex >= (sizeof(SensorData) / sizeof(float))) break;  // Prevent overflow
    ThingSpeak.setField(i + 1, dataPtr[fieldIndex]);                // Set ThingSpeak field
  }
  msg = (batch == 0) ? "BSEC data updated at: " + printTime() : "Gas data updated at: " + printTime() ThingSpeak.setStatus(msg);
  int result = ThingSpeak.writeFields(channelIDs[batch + 2], APIKeys[batch + 2]);
  if (result == 200) {
    Serial.println("Channel " ++String(batch + 2) + " update successful: ");
  } else {
    Serial.println("HTTP error code: " + String(result));
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