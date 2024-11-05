/*
 * https://docs.arduino.cc/tutorials/nicla-sense-me/cheat-sheet/#sensors
 *
 *
 * define the following in secrets.h (recommended) or below #include... (not recommended)
 *
 * #define SECRET_SSID "Wifi SSID"
 * #define SECRET_PASS "Wifi Password"
 * #define SUPABASE_URL "https:// {Ur DATA BASE} .supabase.co"
 * #define tableRealtime "table_name"
 * #define SUPABASE_KEY ""
 * #define PROJECT_ID ""
 * #define CLIENT_EMAIL ""
 * #define PRIVATE_KEY ""
 * #define SHEET_ID ""

 * Initial author: @cheuh008
 *
 */


#include "secrets.h"            // Include the secrets header
#include "Arduino_BHY2Host.h"   // BHY2Host library for sensor data from Nicla
#include <WiFiNINA.h>           // Include WiFi library
#include <utility/wifi_drv.h>   // include wifi LED library
#include <ArduinoHttpClient.h>  // Http library for handling webhook


const char WEB_APP_URL[] = WebappURL;

//Sensors init from nicla sense over Eslov
Sensor temp(SENSOR_ID_TEMP);
Sensor gas(SENSOR_ID_GAS);
Sensor humid(SENSOR_ID_HUM);
Sensor pres(SENSOR_ID_BARO);
SensorXYZ gyro(SENSOR_ID_GYRO);
SensorXYZ accel(SENSOR_ID_ACC);
SensorQuaternion quat(SENSOR_ID_RV);
SensorBSEC bsec(SENSOR_ID_BSEC);  // init Bosch Sensortec Environmental Cluster BME688 to  access the air quality (IAQ)
SensorActivity acti(SENSOR_ID_AR);

WiFiClient wifi;                                                           // Create WiFi client to connect to wifi and SQL
HttpClient gSheetClient = HttpClient(wifi, "sheets.googleapis.com", 80);  // Create http...

void setup() {
    Serial.begin(9600);                     // Initialize serial communication at defined baud rate
    BHY2Host.begin(false, NICLA_VIA_ESLOV); // Begin collecting Nicla BHY2 Data over Eslov
    sesnorsLedInit();                       // Abstract init fucntion for LEDs and all Sensors foreasier reading
    connectWiFi();                          // function to Connect to wifi (flashes orange if unsuccesful)
}

void loop() {
    static auto lastCheck = millis();    // starting a clock
    BHY2Host.update();                   // Updating Sensors
    if (millis() - lastCheck >= 1000) {  // after 1s passed:
        lastCheck = millis();            // rest clock
        sendData();                      // read data in real time without waiting for delay
    }
}

void sesnorsLedInit() {
    WiFiDrv::pinMode(25, OUTPUT);                   // Define green pin (looks Red to me)
    WiFiDrv::pinMode(26, OUTPUT);                   // Define red pin (so probs green)
    WiFiDrv::pinMode(27, OUTPUT);                   // Define blue pin
    temp.begin();                                   // Init each sensor 1 by 1
    gas.begin();                                    //      |
    humid.begin();                                  //      |
    pres.begin();                                   //      |
    gyro.begin();                                   //      |
    accel.begin();                                  //      |
    quat.begin();                                   //      |
    bsec.begin();                                   //      V
    acti.begin();                                   // -----------  // End of sensor init
    if (Serial) Serial.println("Setup complete.");  // If serial interface is connected Output init complete to Baudrate
}

void connectWiFi() {                                                    // Wifi Connetion Loop (LED Orange Flash)
    while (WiFi.begin(SECRET_SSID, SECRET_PASS) != WL_CONNECTED) {      // Loops until connected to internet
        Serial.println("Connecting to: " + String(SECRET_SSID));        // output to serial if serial is connected
        WiFiDrv::analogWrite(25, 255);  WiFiDrv::analogWrite(26, 165);  // Flsah Red255 + Green165 = orange LED rgb(255,165,0)
        delay(2500);                                                    // Waiting 2s before trying to connect again
        Serial.println(".");                                            // output to serial to shown reconnect attempt
        WiFiDrv::analogWrite(25, 0); WiFiDrv::analogWrite(26, 0);       // Turning off LEDs for flash
    }
    Serial.println("Connected to WiFi");                                // Serial output if connection succesful
    WiFiDrv::analogWrite(26, 26);                                        // Dim Green LED once connected
}

void sendData() {
    const char* labels[] = {        // Here we label the json data and give each sensor's values a unique header in a list of 23 readings
      "temperature","humidity","pressure","gyroscope_x","gyroscope_y","gyroscope_z","accelerometer_x","accelerometer_y","accelerometer_z","quaternion_x","quaternion_y","quaternion_z","quaternion_w","quaternion_accuracy","bsec_iaq","bsec_iaq_s","bsec_b_voc_eq","bsec_co2_eq","bsec_accuracy","bsec_comp_t","bsec_comp_h","bsec_comp_g","gas","activity"
    };
    float sensorReadings[] = {      // We then store each of the floating point values returned from the sensors in a list of 22 array ( - acti as string)
      temp.value(),humid.value(),pres.value(),gyro.x(),gyro.y(),gyro.z(),accel.x(),accel.y(),accel.z(),quat.x(),quat.y(),quat.z(),quat.w(),quat.accuracy(),bsec.iaq(),bsec.iaq_s(),bsec.b_voc_eq(),bsec.co2_eq(),bsec.accuracy(),bsec.comp_t(),bsec.comp_h(),bsec.comp_g(),gas.value()
    };
    String data = "{";                                                            // Structuring the JSON data String starting with the { 
    int sensorCount = sizeof(sensorReadings) / sizeof(sensorReadings[0]);          //creating a counter for the first 22 floats
    for (int i = 0; i <= sensorCount; ++i) {                                    // Looping through all 22 + 1 data type
        if (i != 0) data += ",";                                                  // We add a comma to the end of the data for the csv
        if (i < sensorCount) {
            data += "\"" + String(labels[i]) + "\": " + String(sensorReadings[i]);  // Here we're checking for the first for the 22 floats which are stored as , "header": value, 
        }
        else {
            data += "\"" + String(labels[i]) + "\": " + acti.toString();            // for the only non float we just do  "header": string 
        }
    }
    data += "}";

    gSheetClient.beginRequest();
    gSheetClient.post(WEB_APP_URL);
    gSheetClient.sendHeader("Content-Type", "application/json");
    gSheetClient.sendHeader("Content-Length", data.length());
    gSheetClient.beginBody();
    gSheetClient.print(data);
    gSheetClient.endRequest();
    int statusCode = gSheetClient.responseStatusCode();
    Serial.println("Google Sheets Status code: " + String(statusCode));
    Serial.println("Sent to Google Sheets: " + data);
}
