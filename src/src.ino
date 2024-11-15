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

// Including all the required Libraries and Files ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <WiFiNINA.h>          // Include Library for connecting to wifi
#include <NTPClient.h>         // Library for synchronizing time with an NTP server
#include <WiFiUdp.h>           // Library for sending and receiving UDP packets over Wi-Fi
#include "secrets.h"           // Inlcude the file that contain SSID, Password, API Channel ID and Keys
#include "Arduino_BHY2Host.h"  // BHY2Host library for sensor data from Nicla
#include "ThingSpeak.h"        // always include thingspeak header file after other header files and custom macros


// Defining some key variables needed / grabbing them from secrets.h ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char ssid[] = SECRET_SSID;               // Define Wi-Fi network SSID (name) from secrets.h or set your own
char pass[] = SECRET_PASS;               // Define Wi-Fi network password
unsigned long ChannelID = SECRET_CH_ID;  // ThingSpeak Channel ID for data upload
                                         //
const char* APIKey = SECRET_W_APIKEY;    // ThingSpeak API Key for authentication
char message[20];                        // Declare a character array to store the message to send to ThingSpeak
WiFiClient client;                       // Initializes a client to establish Wi-Fi connections
SensorBSEC bsec(SENSOR_ID_BSEC);         // Creates an instance of SensorBSEC for interacting with the Bosch BME688 sensor to access air quality data (IAQ)
Sensor pressure(SENSOR_ID_BARO);


WiFiUDP ntpUDP;                                          // Creates an instance of WiFiUDP to handle NTP communication
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 60000);  // Initializes the NTPClient with the NTP server, UTC offset (0), and update interval (60000 ms)


// Inital Setup Function ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);                         // Initialize serial communication at 9600 baud rate
  BHY2Host.begin(false, NICLA_VIA_ESLOV);     // Begin collecting data from the Nicla BHY2 sensor over Eslov
  delay(2500);                                // Delay to allow serial connection to establish
  bsec.begin();                               // Initialize the BSEC sensor and start acquiring data
  Serial.println("BSEC sensor initialised");  // Output debug message indicating BSEC sensor is initialized
  wifiConnect();                              // Call the wifiConnect function to connect to the Wi-Fi network
  pressure.begin();
}

// Main Function Loop ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void loop() {
  delay(1000);        // Delay for 2 seconds to allow time for processing and stable sensor readings
  Serial.print(".");  // Print a dot to indicate progress in the serial monitor
  BHY2Host.update();  // Update the sensor readings from the BHY2 host

  static auto lastCheck = millis();  // Initialize a static variable to track the last check time

  // Here we only grab 7/8 data values in the dictionary and store it as a list of floats
  float sensorReadings[] = {
    bsec.iaq_s(),     // The IAQ value for stationary whilst stationary
    bsec.b_voc_eq(),  // The breath VOC equivalent (ppm)
    bsec.co2_eq(),    // The CO2 equivalent (ppm) [400,]
    bsec.accuracy(),  // accuracy level: [0-3]
    bsec.comp_t(),    // The compensated temperature (Celsius)
    bsec.comp_h(),    // Compensated humidity
    bsec.comp_g()     // compensated gas resistance (Ohms)
  };

  if (WiFi.status() != WL_CONNECTED) {  // If Wi-Fi is not connected or lost
    wifiConnect();                      // Reconnect to Wi-Fi
  }

  bool allZeros = true;                 // Flag to track if all sensor readings are zero
  if (millis() - lastCheck >= 10000) {  // Wait for 30 seconds to pass
    lastCheck = millis();               // Reset the timer
    Serial.println(String("pressure: ") + pressure.toString());

    Serial.println("Readings ");          // Print label for sensor readings
    for (float value : sensorReadings) {  // Loop through each sensor reading
      Serial.print(value);                // Print the value
      Serial.print(", ");                 // Add a comma separator
      if (value != 0) allZeros = false;   // If any value is non-zero, set flag to false
    }                                     //
    Serial.println();                     // Prints a newline after readings
    if (allZeros == false) {              // If at least one value is non-zero
      uploadData(sensorReadings);         // Upload the sensor data to ThingSpeak
    }
  }
}

void wifiConnect() {
  Serial.println("Connecting to wifi ");   // Debug message signalling wifi reconnect
  while (WiFi.status() != WL_CONNECTED) {  // Wait for wifi to connect
    WiFi.begin(ssid, pass);                // initalise wifi using given ssid and password
    Serial.println(".");                   // output to serial to shown reconnect attempt
    delay(2500);                           // delay until reconnect
  }
  Serial.println("Connected to WiFi");  // Serial output if connection succesful
  ThingSpeak.begin(client);             // Initialize connection to ThingSpeak
  timeClient.begin();
}

void uploadData(float sensorReadings[]) {
  int items = sizeof(sensorReadings) / sizeof(sensorReadings[0]);  // Get the number of items in the sensorReadings array
  for (int i = 0; i < items; i++) {                                // Loop through the sensor readings
    ThingSpeak.setField(i + 1, sensorReadings[i]);                 // Set each sensor reading to its corresponding field on ThingSpeak
  }
  timeClient.update();                   // Update the time from the NTP server
  int day = timeClient.getDay();         // Get the current day
  int hour = timeClient.getHours();      // // hour
  int minute = timeClient.getMinutes();  // // and minute

  sprintf(message,                                        // Format and update the message
          "BSEC Values updated at: %02d/%02d %02d:%02d",  // // with day, hour, and minute
          day, hour, minute);                             // // from the values for day, hour, and minute

  Serial.println(message);        // Print the formatted timestamp message to the Serial Monitor
  ThingSpeak.setStatus(message);  // Set the ThingSpeak channel status with the timestamp message

  int x = ThingSpeak.writeFields(ChannelID, APIKey);  // Write the fields to the specified ThingSpeak channel
  if (x == 200) {                                     // If the update is successful
    Serial.println("Channel update successful.");     // Print success message
  } else {                                            // If there is an error
    Serial.println(" HTTP error code " + String(x));  // Print the HTTP error code
  }
}
