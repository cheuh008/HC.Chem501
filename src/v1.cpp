/*
 *
 * https://docs.arduino.cc/tutorials/nicla-sense-me/cheat-sheet/#sensors
 *
 * Initial author: @cheuh008
 */


#include "secrets.h"                                    // Include the secrets header
#include "Arduino_BHY2Host.h"                           // BHY2Host library for sensor data from Nicla
#include <WiFiNINA.h>                                   // Include WiFi library
#include <utility/wifi_drv.h>                           // include wifi LED library
#include <ArduinoHttpClient.h>                          // Http library for handling webhook
#include <ESP_Google_Sheet_Client.h>

 //Sensors init from nicla sense over Eslov      
Sensor temp(SENSOR_ID_TEMP);
Sensor gas(SENSOR_ID_GAS);
Sensor humid(SENSOR_ID_HUM);
Sensor pres(SENSOR_ID_BARO);
SensorXYZ gyro(SENSOR_ID_GYRO);
SensorXYZ accel(SENSOR_ID_ACC);
SensorQuaternion quat(SENSOR_ID_RV);
SensorBSEC bsec(SENSOR_ID_BSEC);                        // init Bosch Sensortec Environmental Cluster BME688 to  access the air quality (IAQ)
SensorActivity acti(SENSOR_ID_AR);

const long interval = 5000;                             // Set interval for sending messages (milliseconds)
unsigned long previousMillis = 0;                       // Store the last time a message was sent

const char ssid[] = SECRET_SSID;                        // Replace with your WiFi SSID
const char pass[] = SECRET_PASS;                        // Replace with your WiFi password
const char url[] = SUPABASE_URL;
const char key[] = SUPABASE_KEY;
const char private_key[] = PRIVATE_KEY;
const String sheet_id = SHEET_ID;

WiFiClient wifi;                                  // Create WiFi client to connect to wifi and SQL
HttpClient supabaseClient = HttpClient(wifi, SUPABASE_URL, 80);
HttpClient sheetsClient = HttpClient(wifi, "sheets.googleapis.com", 443);

void setup() {
    Serial.begin(115200);                               // Initialize serial communication at defined baud rate
    sensorLEDInit();                                    // function to Init all sensors and onboard LED   
    connectWiFi();                                      // function to Connect to wifi (flashes orange if unsuccesful)
}

void loop() {
    String sensorValues[] = {
      temp.toString(),
      humid.toString(),
      pres.toString(),
      gyro.toString(),
      accel.toString(),
      quat.toString(),
      bsec.toString(),
      gas.toString(),
      acti.toString()
    };

    const char* labels[] = {
        "temperature",
        "humidity",
        "Pressure",
        "gyroscope",
        "accelerometer",
        "quaternion",
        "bsec",
        "gas",
        "activity"
    };
    String data = "{";
    for (int i = 0; i < 9; i++) {
        if (Serial) { Serial.println(String(labels[i]) + ": " + String(sensorValues[i])); };
        data += "\"" + String(labels[i]) + "\": " + sensorValues[i];
        if (i < 8) { data += ","; };
    }
    data += "}";

    if (WiFi.status() == WL_CONNECTED) {
        sendDataToSupabase(data);
        sendDataToGoogleSheets(data);
    }
    delay(1000); // Delay for 1 second
}

void sendDataToSupabase(String json) {
    supabaseClient.beginRequest();
    supabaseClient.post("/rest/v1/sensor_data");
    supabaseClient.sendHeader("Content-Type", "application/json");
    supabaseClient.sendHeader("apikey", SUPABASE_KEY);
    supabaseClient.sendHeader("Content-Length", json.length());
    supabaseClient.beginBody();
    supabaseClient.print(json);
    supabaseClient.endRequest();
    if (Serial) {
        int statusCode = supabaseClient.responseStatusCode();
        Serial.println("Supabase Status code: " + String(statusCode));
        Serial.println("Sent to Supabase: " + json);
    }
}

void sendDataToGoogleSheets(String json) {
    String endpoint = "/v4/spreadsheets/" + String(SHEET_ID) + "/values/Sheet1!A1:append?valueInputOption=USER_ENTERED";

    sheetsClient.beginRequest();
    sheetsClient.post(endpoint);
    sheetsClient.sendHeader("Content-Type", "application/json");
    sheetsClient.sendHeader("Authorization", "Bearer YOUR_ACCESS_TOKEN");
    sheetsClient.sendHeader("Content-Length", json.length());
    sheetsClient.beginBody();
    sheetsClient.print("{\"values\":[[" + json + "]]}"); // Correct JSON format
    sheetsClient.endRequest();

    int statusCode = sheetsClient.responseStatusCode();
    if (Serial) {
        Serial.println("Google Sheets Status code: " + String(statusCode));
        Serial.println("Sent to Google Sheets: " + json);
    }
}

void connectWiFi() {                                    // Wifi Connetion Loop (LED Orange Flash)
    while (WiFi.begin(ssid, pass) != WL_CONNECTED) {    // Loop start until connected 
        delay(2000);                                    // 2s delay for wifi to catchup
        if (Serial) Serial.println("Connecting to: " + String(ssid));
        WiFiDrv::analogWrite(25, 255);                  //^ output to serial if connected
        WiFiDrv::analogWrite(26, 165);                  // Flsah orange LED rgb(255,165,0)
        delay(2000);
        if (Serial) Serial.println(".");
        WiFiDrv::analogWrite(25, 0);
        WiFiDrv::analogWrite(26, 0);
    }
    if (Serial) Serial.println("Connected to WiFi");    // Serial output if connection succesful
    WiFiDrv::analogWrite(26, 165);                      // Dim Green once connected
}

void sensorLEDInit() {
    WiFiDrv::pinMode(25, OUTPUT);                       //define green pin (looks Red to me)
    WiFiDrv::pinMode(26, OUTPUT);                       //define red pin (so probs green)
    WiFiDrv::pinMode(27, OUTPUT);                       //define blue pin
    BHY2Host.begin(false, NICLA_VIA_ESLOV);
    temp.begin();
    gas.begin();
    humid.begin();
    pres.begin();
    gyro.begin();
    accel.begin();
    quat.begin();
    bsec.begin();
    acti.begin();
    if (Serial) Serial.println("Setup complete. Ready to take readings.");
}
