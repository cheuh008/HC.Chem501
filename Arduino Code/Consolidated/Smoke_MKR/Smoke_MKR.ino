
//======================================================================================================================================================
// Importing Libraries
//======================================================================================================================================================
#include <Wire.h>               // Library for I2C communication with Nicla (needed for BSEC2)
#include <WiFiNINA.h>           // Library for Wi-Fi connectivity
#include <WiFiUdp.h>            // Library for UDP communication over Wi-Fi
#include <RTCZero.h>            // Library for Real Time Clock (RTC) on MKR boards
#include "Arduino.h"            //
#include "secrets.h"            // Include file with sensitive info like SSID, password, ThingSpeak API keys
#include "ThingSpeak.h"         // ThingSpeak library for cloud data logging
#include "Arduino_BHY2Host.h"   // Bosch Host library for managing sensor data
#include <ArduinoMqttClient.h>  //

//======================================================================================================================================================
// Declaring Global Variables
//======================================================================================================================================================

int mode = 2;                   // Default mode: 0 for Standalone, 1 for Classifier, 2 for Collector
RTCZero rtc;                    // Real-time clock instance for managing date and time
WiFiClient client;              // Client to establish Wi-Fi connections
bool allZeros = true;           // Flag to track if all sensor readings are zero
const char* topics[] = {};      //
MqttClient mqttClient(client);  //
// Sensor gas(SENSOR_ID_GAS);        // Gas sensor instance using the GAS sensor ID
// Sensor pres(SENSOR_ID_BARO);      // Pressure sensor instance using the BARO sensor ID
// SensorBSEC bsec(SENSOR_ID_BSEC);  // Bosch BSEC sensor instance for air quality data

//======================================================================================================================================================
// Main Loop Function
//======================================================================================================================================================                                  //
void setup() {
  Serial.begin(115200);
  Wire.begin();
  rtc.begin();
  delay(1000);
  Serial.println("Serialed, Wired abd Clocked");
  wifiConnect();
  Serial.println("Wified");
  delay(1000);

  //   BHY2Host.begin();
  //   Serial.println("Hosted");
  //   conditional();
  //   Serial.println("Conditioned");
}

void loop() {
  mqttClient.poll();
  //   if (mode == 0) BHY2Host.update();
  static unsigned long lastCheck = millis();
  if (WiFi.status() != WL_CONNECTED) {  //
    wifiConnect();                      //
  }                                     //
  if (millis() - lastCheck >= 2000) {   //
    lastCheck = millis();               //
    Serial.println("Serialed");         //
    getData();
  }
  if (Serial.available() > 0) {      // Check if data is available on the serial port
    int input = Serial.parseInt();   // Read integer input
    Serial.read();                   // Clear
    if (input >= 0 && input <= 2) {  // Validate the mode
      mode = input;

      Serial.print("Mode ");
      Serial.print(mode);
      Serial.println(" selceted ");

      // Begin transmission to slave with address 2
      Wire.beginTransmission(2);
      Wire.write(input);
      Wire.endTransmission();

      Serial.println("Mode passed to Nicla ");  //
      // conditional();                          // Init Sensors
    }
  }
}
// //======================================//================================================================================================================
// // Main Loop Function                   //
// //======================================//================================================================================================================

// void conditional() {                    //
//   if (mode == 0) {                      //
//     gas.begin();                        // Initialize the gas sensor
//     pres.begin();                       // Initialize the pressure sensor
//     bsec.begin();                       // Initialize the Bosch BSEC sensor
//     Wire.end();                         //
//   } else if (mode == 1 || mode == 2) {  //
//     gas.end();                          // Initialize the gas sensor
//     pres.end();                         // Initialize the pressure sensor
//     bsec.end();                         // Initialize the Bosch BSEC sensor
//     Wire.begin();                       //
//   };                                    //
// };                                      //

void getData() {
  if (mode == 0) {
    //     String sensorData[8] = {
    //       //   String(gas.value()), String(pres.value()),
    //       //   String(bsec.iaq_s()), String(bsec.b_voc_eq()),
    //       //   String(bsec.co2_eq()), String(bsec.comp_t()),
    //       //   String(bsec.comp_h()), String(bsec.accuracy())
    //     };
    //     allZeros = false;  //     If any value is non-zero, set the flag to false
    //     int size = 8;
    //     const char* topics[8] = { "", "", "", "", "", "", "", "" };
    //     String VOCmsg = "VOC values updated at: " + printTime();                // Construct the status message with the current timestamp
    //     sendData(sensorData, size, VOCmsg, ChannelIDs[3], APIKeys[3], topics);  //
  } else if (mode == 1) {  //

    int size = 5;  //

    String receivedData[5];
    Serial.print("Received data: ");

    // Request 5 bytes from slave device #2
    Wire.requestFrom(2, size);
    if (Wire.available() == size) {
      for (int i = 0; i < size; i++) {               //
        receivedData[i] = String(Wire.read());       //
        Serial.print(receivedData[i]);               //
        if (receivedData[i] != 0) allZeros = false;  //     If any value is non-zero, set the flag to false
      }
    }
    const char* topics[5] = { "BSECGasEstimate0", "BSECGasEstimate1", "BSECGasEstimate2", "BSECGasEstimate3", "BSECGasAccuracy" };
    String BSEC2msg = "BSEC2 values updated at: " + printTime();  // Construct the status message with the current timestamp

    Serial.print("Sending Data ");                                              // Print received data
    sendData(receivedData, size, BSEC2msg, ChannelIDs[2], APIKeys[2], topics);  //
  } else if (mode == 2) {                                                       //
    int size = 6;                                                               //
    String data = "";                                                           //
    while (Wire.available()) {                                                  //
      char c = Wire.read();                                                     // Read each character from the I2C buffer
      data += c;                                                                //
    }
    Serial.println(data);
  
    int index = 0;                           //
    String fields[6];                        //
    for (int i = 0; i < size; i++) {         //
      index = data.indexOf(' ');             //
      fields[i] = data.substring(0, index);  //
      if (fields[i] != 0) allZeros = false;  //     If any value is non-zero, set the flag to false

      data.remove(0, index + 1);  //
    }                             //
    const char* topics[6] = { "", "", "", "", "", "" };
    String collectormsg = "Gas values updated at: " + printTime();            //
    sendData(fields, size, collectormsg, ChannelIDs[1], APIKeys[1], topics);  //
  }                                                                           //
}

void sendData(String data[], int size, String msg, unsigned long channelId, const char* ApiKey, const char* topics[]) {
  if (!allZeros) {
    for (int i = 0; i < size; i++) {             // Send data to ThingSpeak and print to Serial for debugging
      ThingSpeak.setField(i + 1, data[i]);       // Set the appropriate field on ThingSpeak (Starts at 1)
      Serial.print(data[i]);                     // Print sensor value to Serial
      Serial.print(" ");                         // Add space between values for readability
      mqttClient.beginMessage(topics[i], true);  //     MQTT: Sends the topic matched to the reading and the retainment true
      mqttClient.print(data[i]);                 //         : Print interface used to set the message content
      mqttClient.endMessage();                   //
    }                                            //
    Serial.println();                            // Newline after printing all sensor values
    // ThingSpeak.setStatus(msg);                          // Set the ThingSpeak channel status with the timestamp message
    // int x = ThingSpeak.writeFields(channelId, ApiKey);  // Write the fields to ThingSpeak
    // if (x == 200) {                                     // If the update is successful
    //   Serial.println("Channel update successful.");     // Print success message
    //   Serial.println(msg);                              // Print the status message to the Serial Monitor
    // } else {                                            // If there was an error with the HTTP request
    //   Serial.println(" HTTP error code " + String(x));  // Print HTTP error code to help debug
    // }
  }
}

void wifiConnect() {
  Serial.println("Connecting to WiFi...");                  // Debug message indicating Wi-Fi connection attempt
  while (WiFi.status() != WL_CONNECTED) {                   // Wait for Wi-Fi connection to be established
    WiFi.begin(SECRET_SSID, SECRET_PASS);                   // Initialize Wi-Fi using the provided SSID and password
    delay(5000);                                            // Wait 5 seconds before attempting to reconnect
  }                                                         //
  getTime();                                                // Call the function to get the current time via NTP
  ThingSpeak.begin(client);                                 // Initialize the ThingSpeak client for data communication
  Serial.println("ThingSpeak Client Connected");            // Output confirmation of the ThingSpeak client connection
  if (!mqttClient.connect(broker, port)) {                  // MQTT:
    Serial.print("MQTT connection failed! Error code = ");  //
    Serial.println(mqttClient.connectError());              //
    while (1)
      ;
  }
  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}

void getTime() {                                         //
  unsigned long epoch;                                   // Variable to store the epoch time
  int numberOfTries = 0, maxTries = 6;                   // Set max retries in case NTP fails
  do {                                                   // Attempt to get the epoch time from Wi-Fi (NTP)
    epoch = WiFi.getTime();                              // Fetch the time from the Wi-Fi connection (NTP)
    numberOfTries++;                                     // Increment the retry counter
  } while ((epoch == 0) && (numberOfTries < maxTries));  // Retry if epoch is 0 (no NTP response)
  if (numberOfTries == maxTries) {                       // If the maximum retries are reached
    Serial.print("NTP unreachable!!");                   // Print error message
    delay(2000);                                         // Wait 5 seconds before attempting to reconnect
    wifiConnect();                                       //
  } else {                                               //
    Serial.print("Epoch received: ");                    // Print the fetched epoch time
    Serial.println(epoch);                               // Print the actual epoch value
    rtc.setEpoch(epoch);                                 // Set the RTC with the fetched epoch time
    Serial.println();                                    // Newline for readability
  }                                                      //
  Serial.print("Time is: ");                             // Output message showing the current time
  Serial.println(printTime());                           // Print the current time formatted by the printTime() function
}

String printTime() {                          // Returns formatted time: "DD/MM HH:MM:SS"
  String day = String(rtc.getDay());          // Get current day from RTC
  String month = String(rtc.getMonth());      // Get current month from RTC
  String hour = String(rtc.getHours());       // Get current hour from RTC
  String minute = String(rtc.getMinutes());   // Get current minute from RTC
  String seconds = String(rtc.getSeconds());  // Get current seconds from RTC
  return day + "/" + month + " " + hour       //
         + ":" + minute + ":" + seconds;      //
}
