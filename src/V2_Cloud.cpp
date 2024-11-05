#include "secrets.h"   
#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

float temperature, humidity, pressure, gyroX, gyroY, gyroZ, accelX, accelY, accelZ, quatX, quatY, quatZ, quatW, quatAccuracy, iaq, iaqS, bVocEq, co2Eq, compT, compH, compG, gas;
float* sensors[] = { &temperature, &humidity, &pressure, &gyroX, &gyroY, &gyroZ, &accelX, &accelY, &accelZ, &quatX, &quatY, &quatZ, &quatW, &quatAccuracy, &iaq, &iaqS, &bVocEq, &co2Eq, &compT, &compH, &compG, &gas };
const char* sensorNames[] = { "temperature", "humidity", "pressure", "gyroX", "gyroY", "gyroZ", "accelX", "accelY", "accelZ", "quatX", "quatY", "quatZ", "quatW", "quatAccuracy", "iaq", "iaqS", "bVocEq", "co2Eq", "compT", "compH", "compG" };

struct Property { const char* name; float* value; };
Property properties[sizeof(sensors) / sizeof(sensors[0])];

void setup() {
    for (int i = 0; i < sizeof(sensors) / sizeof(sensors[0]); i++) {
        properties[i] = { sensorNames[i], sensors[i] };
    }

    // Initialize other settings...
}
