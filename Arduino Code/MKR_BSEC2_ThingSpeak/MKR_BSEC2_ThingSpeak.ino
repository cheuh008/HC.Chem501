
#include <Wire.h>  // Library for I2C communication with Nicla (needed for BSEC2)
// #include <WiFiNINA.h>          // Library for Wi-Fi connectivity
// #include <WiFiUdp.h>           // Library for UDP communication over Wi-Fi
// #include <RTCZero.h>           // Library for Real Time Clock (RTC) on MKR boards
// #include "secrets.h"           // Include file with sensitive info like SSID, password, ThingSpeak API keys
// #include "ThingSpeak.h"        // ThingSpeak library for cloud data logging
#include "Arduino_BHY2Host.h"  // Library for BHY2 sensor data from Nicla Vision/BME688

// ================================================================================================================================================================================================
// iniitlising sesnors global variable
// ================================================================================================================================================================================================

// unsigned long channelIDs[] = { 2753094, 2753095, 2753096 };  // ThingSpeak credentials (for 1 or more servers)
// ssid = "VodafoneMobileWiFi-594684"
// WiFiClient client;  // Client to establish Wi-Fi connections
// RTCZero rtc;        // Real-time clock instance for managing date and time

struct SensorData {
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

SensorData SensorData;

// ================================================================================================================================================================================================
// Inital Setup Function
// ================================================================================================================================================================================================

void setup() {
  Wire.begin();        // Start I2C communication as master
  Serial.begin(9600);  // Initialize serial communication at 9600 baud rate for debugging
  while (!Serial)
    (1);
  Serial.println("Serialed");
  BHY2Host.begin(); 
  //rtc.begin();    // Start the RTC (Real-Time Clock) instance
  //wifiConnect();  // Connect to Wi-Fi by calling the custom wifiConnect function
  Serial.println("Inited");
}

// ================================================================================================================================================================================================
// Main Function Loop
// ================================================================================================================================================================================================

void loop() {

  //if (WiFi.status() != WL_CONNECTED) wifiConnect();  // Check Wi-Fi status and reconnect if necessary
  static auto lastCheck = millis();  //

  BHY2Host.update();                   // Update sensor data from the BHY2 host (Nicla Vision or similar sensor)
  Wire.requestFrom(0x10, 87);          //
                                       //
  if (millis() - lastCheck >= 1000) {  // Check sensor values every second

    lastCheck = millis();  //

    Wire.requestFrom(0x10, sizeof(SensorData));  // Request the size of the struct from Nicla
    if (Wire.available() >= sizeof(SensorData)) {
      Wire.readBytes((char*)&SensorData, sizeof(SensorData));  // print the character
    }
    Serial.println("IAQ: " + String(SensorData.iaq));
    Serial.println("IAQ S: " + String(SensorData.iaq_s));
    Serial.println("B VOC EQ: " + String(SensorData.b_voc_eq));
    Serial.println("CO2 EQ: " + String(SensorData.co2_eq));
    Serial.println("BSEC Accuracy: " + String(SensorData.bsec_accu));
    Serial.println("Comp T: " + String(SensorData.comp_t));
    Serial.println("Comp H: " + String(SensorData.comp_h));
    Serial.println("Comp G: " + String(SensorData.comp_g));
    Serial.println("Gas Value: " + String(SensorData.gasVal));
    Serial.println("Pressure Value: " + String(SensorData.presVal));
    Serial.println("Temperature Value: " + String(SensorData.tempValue));
    Serial.println("Gas Estimate 0: " + String(SensorData.gas0));
    Serial.println("Gas Estimate 1: " + String(SensorData.gas1));
    Serial.println("Gas Estimate 2: " + String(SensorData.gas2));
    Serial.println("Gas Estimate 3: " + String(SensorData.gas3));

    // ThingSpeak.setField(1, gas.value());      // Assign each sensor reading to the corresponding field on ThingSpeak
    // ThingSpeak.setField(2, temp.value());     //
    // ThingSpeak.setField(3, pres.value());     // Assign each sensor reading to the corresponding field on ThingSpeak
    // ThingSpeak.setField(4, bsec.iaq());       //
    // ThingSpeak.setField(5, bsec.iaq_s());     // IAQ value (Indoor Air Quality) when stationary
    // ThingSpeak.setField(6, bsec.b_voc_eq());  // Breath VOC equivalent (ppm)
    // ThingSpeak.setField(7, bsec.co2_eq());    // CO2 equivalent (ppm), typically starts from 400 ppm
    // ThingSpeak.setField(8, bsec.accuracy());  // Assign each sensor reading to the corresponding field on ThingSpeak

    // String msg += "Sensors updated at: " + printTime();  // Construct the status message with the current timestamp
    // ThingSpeak.setStatus(msg);                           // Set the ThingSpeak channel status with the timestamp message

    // int x = ThingSpeak.writeFields(ChannelID[0], APIKeya[0]);  // Write the fields to ThingSpeak
    // if (x == 200) {                                            // If the update is successful
    //   Serial.println("Channel update successful.");            // Print success message
    // } else {                                                   // If there was an error with the HTTP request
    //   Serial.println(" HTTP error code " + String(x));         // Print HTTP error code to help debug
    // }

    // ThingSpeak.setField(1, bsec.comp_t();    // Compensated temperature (in Celsius)
    // ThingSpeak.setField(2, bsec.comp_h()),    // Compensated humidity (in %)
    // ThingSpeak.setField(3, bsec.comp_g())     // Compensated gas resistance (Ohms)
    // ThingSpeak.setField(4, bsec.iaq());                        //
    // ThingSpeak.setField(5, bsec.iaq_s());                      //
    // ThingSpeak.setField(6, bsec.b_voc_eq());                   // Assign each sensor reading to the corresponding field on ThingSpeak
    // ThingSpeak.setField(7, bsec.co2_eq());                     //
    // ThingSpeak.setField(8, bsec.accuracy());                   // Assign each sensor reading to the corresponding field on ThingSpeak

    // String msg += "BSEC Values updated at: " + printTime();        // Construct the status message with the current timestamp
    // ThingSpeak.setStatus(msg);                                 // Set the ThingSpeak channel status with the timestamp message

    // int x = ThingSpeak.writeFields(ChannelID[1], APIKeya[1]);  // Write the fields to ThingSpeak
    // if (x == 200) {                                            // If the update is successful
    //   Serial.println("Channel update successful.");            // Print success message
    // } else {                                                   // If there was an error with the HTTP request
    //   Serial.println(" HTTP error code " + String(x));         // Print HTTP error code to help debug
    // }

    //Debug...
    // Serial.println(String("gas: ") + String(gas.value()));
    // Serial.println(String("temperature: ") + String(temp.value(), 2));
    // Serial.println(String("temperature: ") + String(pres.value(), 2));
    // Serial.print(bsec.toString());
  }
}

// ================================================================================================================================================================================================
// Function to connect to Wi-Fi and initialize the ThingSpeak client
// ================================================================================================================================================================================================

// void wifiConnect() {

//   Serial.println("Connecting to WiFi...");        // Debug message indicating Wi-Fi connection attempt
//   while (WiFi.status() != WL_CONNECTED) {         // Wait for Wi-Fi connection to be established
//     WiFi.begin(SECRET_SSID, SECRET_PASS);         // Initialize Wi-Fi using the provided SSID and password
//     delay(5000);                                  // Wait 5 seconds before attempting to reconnect
//   }                                               //
//   getTime();                                      // Call the function to get the current time via NTP
//   Serial.print("Time is: ");                      // Output message showing the current time
//   Serial.println(printTime());                    // Print the current time formatted by the printTime() function
//   ThingSpeak.begin(client);                       // Initialize the ThingSpeak client for data communication
//   Serial.println("ThingSpeak Client Connected");  // Output confirmation of the ThingSpeak client connection
// }

// // ================================================================================================================================================================================================
// // Function to get time from the NTP server and set the RTC epoch
// // ================================================================================================================================================================================================

// void getTime() {
//   unsigned long epoch;                                   // Variable to store the epoch time
//   int numberOfTries = 0, maxTries = 6;                   // Set max retries in case NTP fails
//                                                          //
//   do {                                                   // Attempt to get the epoch time from Wi-Fi (NTP)
//     epoch = WiFi.getTime();                              // Fetch the time from the Wi-Fi connection (NTP)
//     numberOfTries++;                                     // Increment the retry counter
//   } while ((epoch == 0) && (numberOfTries < maxTries));  // Retry if epoch is 0 (no NTP response)
//                                                          //
//   if (numberOfTries == maxTries) {                       // If the maximum retries are reached
//     Serial.print("NTP unreachable!!");                   // Print error message
//     wifiConnect();                                       //
//                                                          //
//   } else {                                               //
//     Serial.print("Epoch received: ");                    // Print the fetched epoch time
//     Serial.println(epoch);                               // Print the actual epoch value
//     rtc.setEpoch(epoch);                                 // Set the RTC with the fetched epoch time
//     Serial.println();                                    // Newline for readability
//   }
// }

// // ================================================================================================================================================================================================
// // Function to format and print the current time from the RTC
// // ================================================================================================================================================================================================

// String printTime() {
//   String day = String(rtc.getDay());          // Get current day from RTC
//   String month = String(rtc.getMonth());      // Get current month from RTC
//   String hour = String(rtc.getHours());       // Get current hour from RTC
//   String minute = String(rtc.getMinutes());   // Get current minute from RTC
//   String seconds = String(rtc.getSeconds());  // Get current seconds from RTC

//   return day + "/" + month + " " + hour + ":" + minute + ":" + seconds;  // Return formatted time string in the format: "DD/MM HH:MM:SS"
// }