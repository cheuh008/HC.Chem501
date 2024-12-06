//======================================================================================================================================================
// Importing Libraries
//======================================================================================================================================================

#include <Wire.h>                       // Library for I2C communication with Nicla (needed for BSEC2)
#include <WiFiNINA.h>                   // Library for Wi-Fi connectivity
#include <WiFiUdp.h>                    // Library for UDP communication over Wi-Fi
#include <RTCZero.h>                    // Library for Real Time Clock (RTC) on MKR boards
#include "secrets.h"                    // Include file with sensitive info like SSID, password, ThingSpeak API keys
#include "ThingSpeak.h"                 // ThingSpeak library for cloud data logging
#include <ArduinoMqttClient.h>          //

//======================================================================================================================================================
// Declaring Global Variables
//=======================================//===============================================================================================================

RTCZero rtc;                      // Real-time clock instance for managing date and time
WiFiClient client;                // Client to establish Wi-Fi connections
// FirebaseData fbdo;                // Define Firebase data object
MqttClient mqttClient(client);    //
const long interval = 1000;       //
uint8_t receivedData[5];          //
int size = sizeof(receivedData)/receivedData[5];  //
bool allZeros = true;             // Flag to track if all sensor readings are zero

//======================================================================================================================================================
// Main Loop Function
//======================================================================================================================================================
void setup() {           // Initial Setup Function (called once)
  Wire.begin();          // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output debug
  rtc.begin();           // Start real time Clock
  wifiConnect();         // Call function to connect to Wifi and Servers
}
//======================================================================================================================================================
// Main Loop Function
//======================================================================================================================================================
void loop() {
  mqttClient.poll();                                                //
  static unsigned long lastCheck = millis();                        // Using millis instead of delay; which stops all processes
  if (WiFi.status() != WL_CONNECTED) wifiConnect();                 // Double checking wifi is connected before sending data
                                                                    //
  if (millis() - lastCheck >= interval) {                           // Updating Every set interval "1" second(s)
    lastCheck = millis();                                           //     Reseting timer
    Wire.requestFrom(2, size);                                      //     Wire: Request 5 bytes from slave device #2 (Nicla)
    Serial.print("Received data: ");                                //         : Print received data
    if (Wire.available() == size) {                                 //         : Ensure 5 bytes are received
      sendData();                                                   //         : sending data if recived
    } else {                                                        //         : If corrupted data gets passed
      Serial.println("Error: Received less than expected bytes!");  //         : Show errormsg
      while (Wire.available()) Wire.read();                         //         : Clears buffer
    }
  }
}
//======================================================================================================================================================
// Main Loop Function
//======================================================================================================================================================
void sendData() {
  String jsonStr = "{";                            // FireBase: Start JSON structure
  for (int i = 0; i < size; i++) {                 // Iterate through the data points 1 at a time (for the size of the array)
    receivedData[i] = Wire.read();                 //     Gets uint8_t data sent from Nicla over ESLOV
    if (receivedData[i] != 0) allZeros = false;    //     If any value is non-zero, set the flag to false
    Serial.print(receivedData[i]);                 //     DEBUG: Show Sensor Readings
    Serial.print(" ");                             //     ===========================================================================
    ThingSpeak.setField(i + 1, receivedData[i]);   //     ThingSpeak: Sets Readings to be sent 1 by 1
                                                   //     ===========================================================================
    jsonStr += ("\"" + String(topics[i]) + "\": "  //     FireBase: add sensor key and reading to JSON
                + String(receivedData[i]));        //             :
    if (i < size - 1) jsonStr += ",";              //             : Add a comma only if it's not the last element
                                                   //     ===========================================================================
    mqttClient.beginMessage(topics[i], true);      //     MQTT: Sends the topic matched to the reading and the retainment true
    mqttClient.print(receivedData[i]);             //         : Print interface used to set the message content
    mqttClient.endMessage();                       //         : Ending msg
  }                                                //===========================================================================
  Serial.println();                                // Breaking off wire readings with Newline
                                                   //===========================================================================
  if (!allZeros) {                                 // Only sending none Zero data (Just in case)
    jsonStr.replace(jsonStr.lastIndexOf(","), 1);  //     FireBase: Removing the last comma in json
    jsonStr += "}";                                //             : Closing the JSON structure
    // Serial.println(jsonStr);                                    //
    // if (Firebase.pushJSON(fbdo, "/NiclaDataV1", jsonStr)) {     //             : Attempt to push JSON to Firebase
    //   Serial.println("Firebase push successful!");              //             : Success msg
    // } else {                                                    //             :   or
    //   Serial.println("Push failed: " + fbdo.errorReason());     //             : Failure code
    // }                                                           //===========================================================================
    String msg = "Gas Estimates updated at: " + printTime();    //     ThingSpeak: Constructing  status message with timestamp
    ThingSpeak.setStatus(msg);                                  //               : Setting channel status message
                                                                //===========================================================================
    int x = ThingSpeak.writeFields(ChannelIDs[2], APIKeys[2]);  //     ThingSpeak: Writing to set Fields
    if (x == 200) {                                             //               : If the update is successful
      Serial.println(msg);                                      //               : Print the status message to the Serial Monitor
      Serial.println("Channel update successful.");             //               : Print success message
    } else {                                                    //               : If there was an error with the HTTP request
      Serial.println(" HTTP error code " + String(x));          //               : Prints HTTP error code to help debug
    }
  }
}
//======================================================================================================================================================
// Reuseable WIFI (Autoreconnect) Function,
//======================================================================================================================================================
void wifiConnect() {
  Serial.println("Connecting to WiFi...");                    // Debug message indicating Wi-Fi connection attempt
  while (WiFi.status() != WL_CONNECTED) {                     // Wait for Wi-Fi connection to be established
    WiFi.begin(SECRET_SSID, SECRET_PASS);                     // Initialize Wi-Fi using the provided SSID and password
    delay(5000);                                              // Wait 5 seconds before attempting to reconnect
  }                                                           //===========================================================================
  getTime();                                                  // RTC: Call the function to get the current time via NTP
  ThingSpeak.begin(client);                                   // ThingSpeak: Initialize the ThingSpeak client for data communication
  Serial.println("ThingSpeak Client Connected");              //           : Output confirmation of the ThingSpeak client connection
                                                              //===========================================================================
  Firebase.begin(DB_URL, DB_SCRT, SECRET_SSID, SECRET_PASS);  // FIrebase:
  Firebase.reconnectWiFi(true);                               //
                                                              //===========================================================================
  if (!mqttClient.connect(broker, port)) {                    // MQTT:
    Serial.print("MQTT connection failed! Error code = ");    //
    Serial.println(mqttClient.connectError());                //
    while (1)
      ;
  }
  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}

//======================================================================================================================================================
// Syncing RTC to NTP server Clock
//======================================================================================================================================================
void getTime() {
  unsigned long epoch;                                   // Variable to store the epoch time
  int numberOfTries = 0, maxTries = 6;                   // Set max retries in case NTP fails
  do {                                                   // Attempt to get the epoch time from Wi-Fi (NTP)
    epoch = WiFi.getTime();                              // Fetch the time from the Wi-Fi connection (NTP)
    numberOfTries++;                                     // Increment the retry counter
  } while ((epoch == 0) && (numberOfTries < maxTries));  // Retry if epoch is 0 (no NTP response)
  if (numberOfTries == maxTries) {                       // If the maximum retries are reached
    Serial.print("NTP unreachable!!");                   // Print error message
    delay(5000);
    wifiConnect();                     //
  } else {                             //
    Serial.print("Epoch received: ");  // Print the fetched epoch time
    Serial.println(epoch);             // Print the actual epoch value
    rtc.setEpoch(epoch);               // Set the RTC with the fetched epoch time
    Serial.println();                  // Newline for readability
  }                                    //
  Serial.print("Time is: ");           // Output message showing the current time
  Serial.println(printTime());         // Print the current time formatted by the printTime() function
}

//======================================================================================================================================================
// Timestamp Formatter Function
//======================================================================================================================================================
String printTime() {                          // Returns time formatted: "DD/MM HH:MM:SS"
  String day = String(rtc.getDay());          // Get current day from RTC
  String month = String(rtc.getMonth());      // Get current month from RTC
  String hour = String(rtc.getHours());       // Get current hour from RTC
  String minute = String(rtc.getMinutes());   // Get current minute from RTC
  String seconds = String(rtc.getSeconds());  // Get current seconds from RTC
  return day + "/" + month + " " + hour + ":" + minute + ":" + seconds;
}