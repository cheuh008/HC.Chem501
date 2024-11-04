#include "secrets.h"                                    // Include the secrets header
#include <WiFiNINA.h>                                   // Include WiFi library
#include <ArduinoMqttClient.h>                          // Include MQTT library

const char ssid[] = SECRET_SSID;                        // Replace with your WiFi SSID
const char pass[] = SECRET_PASS;                        // Replace with your WiFi password
const char broker[] = SECRET_BROKER;                    // MQTT broker address
int port = SECRET_PORT;                                 // MQTT port number
int baudrate = SECRET_BAUDRATE;

const char topic[] = "real_unique_topic";               // MQTT topic for publishing
const char topic2[] = "real_unique_topic_2";            // Additional topic for publishing
const char topic3[] = "real_unique_topic_3";            // Another topic for publishing

const long interval = 5000;                             // Set interval for sending messages (milliseconds)
unsigned long previousMillis = 0;                       // Store the last time a message was sent

WiFiClient wifiClient;                                  // Create WiFi client
MqttClient mqttClient(wifiClient);                      // Create MQTT client

void setup() {
    Serial.begin(baudrate);                             // Initialize serial communication at defined baud rate
    while (!Serial);                                    // Wait for serial port to connect (needed for native USB port only)
    Serial.println("Cinnecting to:" + String(ssid));    // Print the SSID
    while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
        Serial.print(".");                              // Print dot while waiting for connection
        delay(5000);                                    // Wait to retry in ms
    }
    Serial.println("Connected to: " + String(ssid));    // Print connected SSID
    Serial.println("Connecting to: " + String(broker)); // Print broker info
    if (!mqttClient.connect(broker, port)) {
        Serial.println("MQTT connection failed!");      // Notify about connection failure
        Serial.println(
            "Error code = " +
            String(mqttClient.connectError()));         // Print error code
        while (1);                                      // Halt the program if connection fails
    }
    Serial.println("\nConnected to: " + String(broker)); // Print successful connection
}

void loop()
{
}
