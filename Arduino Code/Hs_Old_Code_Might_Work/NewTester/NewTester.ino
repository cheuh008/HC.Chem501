/* 
 * This sketch shows how nicla can be used in standalone mode.
 * Without the need for an host, nicla can run sketches that 
 * are able to configure the bhi sensors and are able to read all 
 * the bhi sensors data.
*/

#include "Arduino.h"
#include "Arduino_BHY2.h"

SensorXYZ accel(SENSOR_ID_ACC);
SensorXYZ gyro(SENSOR_ID_GYRO);
Sensor temp(SENSOR_ID_TEMP);
Sensor gas(SENSOR_ID_GAS);
SensorQuaternion rotation(SENSOR_ID_RV);
SensorBSEC2 bsec2(SENSOR_ID_BSEC2);

const uint8_t BSEC2CONFIG[1943] =
  // Example, empty [], gas 0 alcohol, gas 1 ambient
  //{ 0, 0, 2, 2, 189, 1, 0, 0, 0, 0, 0, 0, 213, 8, 0, 0, 52, 0, 1, 0, 0, 168, 19, 73, 64, 49, 119, 76, 0, 192, 40, 72, 0, 192, 40, 72, 137, 65, 0, 191, 205, 204, 204, 190, 0, 0, 64, 191, 225, 122, 148, 190, 10, 0, 3, 0, 216, 85, 0, 100, 0, 0, 96, 64, 23, 183, 209, 56, 28, 0, 2, 0, 0, 244, 1, 150, 0, 50, 0, 0, 128, 64, 0, 0, 32, 65, 144, 1, 0, 0, 112, 65, 0, 0, 0, 63, 16, 0, 3, 0, 10, 215, 163, 60, 10, 215, 35, 59, 10, 215, 35, 59, 13, 0, 5, 0, 0, 0, 0, 0, 100, 254, 131, 137, 87, 88, 0, 9, 0, 7, 240, 150, 61, 0, 0, 0, 0, 0, 0, 0, 0, 28, 124, 225, 61, 52, 128, 215, 63, 0, 0, 160, 64, 0, 0, 0, 0, 0, 0, 0, 0, 205, 204, 12, 62, 103, 213, 39, 62, 230, 63, 76, 192, 0, 0, 0, 0, 0, 0, 0, 0, 145, 237, 60, 191, 251, 58, 64, 63, 177, 80, 131, 64, 0, 0, 0, 0, 0, 0, 0, 0, 93, 254, 227, 62, 54, 60, 133, 191, 0, 0, 64, 64, 12, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 173, 6, 11, 0, 0, 0, 2, 231, 201, 67, 189, 125, 37, 201, 61, 179, 41, 106, 189, 97, 167, 196, 61, 84, 172, 113, 62, 155, 213, 214, 61, 133, 10, 114, 61, 62, 67, 214, 61, 56, 97, 57, 62, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42, 215, 83, 190, 42, 215, 83, 62, 0, 0, 0, 0, 0, 0, 0, 0, 97, 101, 165, 61, 88, 151, 51, 190, 184, 89, 165, 62, 240, 207, 20, 191, 47, 208, 53, 63, 177, 43, 63, 190, 176, 56, 145, 189, 228, 194, 10, 191, 173, 194, 44, 191, 0, 0, 0, 0, 146, 253, 150, 61, 217, 5, 157, 59, 36, 134, 171, 190, 159, 38, 128, 59, 58, 78, 29, 189, 204, 88, 63, 191, 210, 42, 125, 190, 59, 171, 228, 190, 78, 165, 243, 190, 0, 0, 0, 0, 171, 98, 187, 188, 83, 234, 57, 191, 66, 87, 75, 62, 209, 91, 130, 62, 133, 244, 221, 61, 242, 192, 118, 190, 13, 13, 52, 62, 235, 86, 146, 62, 147, 48, 2, 191, 0, 0, 0, 0, 80, 192, 203, 190, 252, 170, 134, 189, 5, 138, 208, 62, 255, 220, 147, 62, 184, 119, 166, 62, 192, 231, 125, 189, 181, 36, 79, 190, 124, 71, 210, 62, 55, 239, 13, 191, 0, 0, 0, 0, 226, 139, 200, 189, 182, 220, 91, 190, 113, 205, 238, 189, 235, 255, 228, 190, 201, 16, 66, 63, 123, 50, 149, 61, 80, 26, 112, 62, 66, 108, 128, 62, 233, 205, 253, 190, 0, 0, 0, 0, 223, 117, 24, 189, 133, 115, 60, 62, 197, 48, 0, 189, 60, 64, 194, 61, 189, 86, 246, 61, 185, 197, 54, 189, 133, 63, 90, 190, 239, 233, 46, 190, 14, 247, 19, 191, 0, 0, 0, 0, 193, 26, 240, 62, 151, 185, 23, 190, 33, 105, 234, 190, 5, 24, 166, 190, 197, 45, 23, 63, 196, 211, 145, 190, 178, 103, 164, 190, 125, 36, 6, 191, 234, 28, 114, 190, 0, 0, 0, 0, 136, 73, 125, 62, 234, 189, 27, 62, 200, 69, 225, 189, 15, 56, 142, 190, 188, 47, 134, 190, 174, 248, 193, 190, 221, 81, 161, 190, 152, 89, 51, 189, 86, 157, 105, 61, 0, 0, 0, 0, 116, 72, 209, 190, 237, 104, 63, 189, 60, 50, 39, 189, 40, 194, 15, 191, 232, 34, 133, 62, 163, 192, 193, 61, 38, 90, 147, 189, 198, 159, 7, 191, 240, 239, 146, 61, 0, 0, 0, 0, 93, 146, 86, 61, 185, 23, 6, 62, 12, 52, 10, 62, 9, 82, 26, 191, 186, 80, 1, 63, 130, 184, 195, 190, 43, 204, 83, 62, 73, 27, 220, 189, 254, 195, 200, 189, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 9, 53, 212, 189, 25, 224, 132, 190, 0, 0, 0, 0, 0, 0, 0, 0, 133, 45, 39, 63, 65, 50, 45, 191, 0, 0, 0, 0, 0, 0, 0, 0, 76, 73, 7, 62, 150, 167, 209, 189, 0, 0, 0, 0, 0, 0, 0, 0, 242, 163, 107, 63, 193, 223, 173, 62, 0, 0, 0, 0, 0, 0, 0, 0, 192, 205, 68, 190, 213, 103, 28, 63, 0, 0, 0, 0, 0, 0, 0, 0, 60, 148, 171, 62, 151, 246, 154, 189, 0, 0, 0, 0, 0, 0, 0, 0, 162, 104, 218, 62, 88, 44, 237, 190, 0, 0, 0, 0, 0, 0, 0, 0, 253, 226, 216, 62, 249, 223, 161, 189, 0, 0, 0, 0, 0, 0, 0, 0, 168, 65, 13, 190, 119, 123, 179, 190, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 160, 184, 18, 72, 125, 52, 223, 75, 204, 85, 211, 75, 119, 27, 192, 75, 83, 228, 150, 73, 122, 154, 142, 73, 133, 214, 135, 73, 145, 149, 237, 71, 56, 196, 2, 72, 221, 197, 11, 72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 158, 236, 10, 72, 35, 30, 221, 75, 206, 136, 209, 75, 14, 146, 190, 75, 218, 105, 148, 73, 65, 65, 140, 73, 150, 149, 133, 73, 206, 248, 222, 71, 219, 117, 246, 71, 96, 19, 4, 72, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 0, 87, 1, 254, 0, 2, 1, 5, 48, 117, 100, 0, 44, 1, 112, 23, 151, 7, 132, 3, 197, 0, 92, 4, 144, 1, 64, 1, 64, 1, 144, 1, 48, 117, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 48, 117, 48, 117, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 100, 0, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 100, 0, 100, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 220, 5, 220, 5, 220, 5, 255, 255, 255, 255, 255, 255, 220, 5, 220, 5, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 48, 117, 0, 1, 0, 5, 0, 2, 0, 10, 0, 30, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 64, 1, 100, 0, 100, 0, 100, 0, 200, 0, 200, 0, 200, 0, 64, 1, 64, 1, 64, 1, 10, 0, 0, 0, 0, 95, 8, 0, 0 };
  // [1943] Ambient, Ethanol, Acetone, EthylAcetate
  { 0, 1, 6, 2, 189, 1, 0, 0, 0, 0, 0, 0, 127, 7, 0, 0, 56, 0, 1, 0, 0, 168, 19, 73, 64, 49, 119, 76, 0, 0, 97, 69, 0, 0, 97, 69, 10, 0, 3, 0, 0, 0, 96, 64, 23, 183, 209, 56, 43, 24, 149, 60, 140, 74, 106, 188, 43, 24, 149, 60, 216, 129, 243, 190, 151, 255, 80, 190, 216, 129, 243, 190, 8, 0, 2, 0, 0, 0, 72, 66, 16, 0, 3, 0, 10, 215, 163, 60, 10, 215, 35, 59, 10, 215, 35, 59, 13, 0, 5, 0, 0, 0, 0, 0, 100, 254, 131, 137, 87, 88, 0, 9, 0, 7, 240, 150, 61, 0, 0, 0, 0, 0, 0, 0, 0, 28, 124, 225, 61, 52, 128, 215, 63, 0, 0, 160, 64, 0, 0, 0, 0, 0, 0, 0, 0, 205, 204, 12, 62, 103, 213, 39, 62, 230, 63, 76, 192, 0, 0, 0, 0, 0, 0, 0, 0, 145, 237, 60, 191, 251, 58, 64, 63, 177, 80, 131, 64, 0, 0, 0, 0, 0, 0, 0, 0, 93, 254, 227, 62, 54, 60, 133, 191, 0, 0, 64, 64, 12, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45, 5, 11, 0, 0, 0, 2, 17, 87, 230, 62, 10, 71, 49, 62, 30, 227, 48, 63, 129, 5, 105, 62, 69, 230, 147, 63, 41, 24, 134, 63, 102, 65, 168, 62, 145, 223, 29, 189, 146, 252, 185, 189, 237, 91, 34, 63, 47, 82, 37, 62, 227, 158, 230, 189, 117, 168, 215, 190, 14, 220, 231, 61, 87, 188, 194, 188, 7, 182, 114, 188, 190, 49, 13, 63, 145, 182, 153, 189, 56, 76, 145, 189, 149, 209, 57, 62, 12, 195, 212, 190, 25, 70, 236, 62, 6, 13, 167, 62, 221, 150, 79, 191, 145, 239, 132, 191, 227, 104, 88, 187, 85, 62, 63, 191, 129, 126, 77, 190, 129, 13, 59, 190, 61, 205, 179, 190, 154, 207, 132, 190, 33, 85, 109, 62, 143, 246, 180, 190, 224, 195, 46, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 149, 2, 189, 127, 187, 253, 62, 12, 59, 114, 191, 252, 248, 18, 191, 10, 198, 188, 188, 197, 194, 197, 190, 193, 187, 17, 191, 149, 220, 24, 62, 183, 249, 93, 190, 123, 22, 160, 190, 236, 205, 224, 190, 8, 251, 59, 189, 211, 24, 159, 191, 150, 96, 212, 190, 125, 100, 36, 60, 35, 41, 128, 190, 253, 216, 193, 59, 120, 98, 188, 190, 226, 94, 144, 190, 109, 169, 107, 62, 163, 68, 113, 191, 18, 99, 129, 61, 93, 10, 115, 191, 121, 251, 10, 191, 168, 240, 10, 191, 101, 217, 106, 60, 30, 193, 9, 191, 174, 129, 129, 62, 12, 184, 45, 62, 143, 240, 135, 190, 109, 152, 40, 191, 11, 191, 28, 63, 134, 115, 63, 191, 31, 150, 212, 61, 112, 254, 130, 190, 229, 144, 184, 62, 220, 154, 82, 191, 188, 120, 104, 186, 42, 227, 201, 61, 52, 1, 1, 63, 252, 213, 58, 191, 63, 108, 144, 61, 231, 213, 137, 191, 28, 22, 229, 190, 52, 17, 252, 61, 79, 133, 27, 190, 204, 34, 120, 191, 105, 130, 180, 60, 192, 233, 119, 191, 166, 69, 119, 63, 210, 45, 216, 190, 136, 254, 213, 62, 59, 107, 174, 191, 111, 109, 168, 60, 240, 75, 27, 63, 239, 27, 12, 61, 218, 235, 108, 191, 3, 6, 236, 189, 99, 227, 57, 190, 228, 166, 202, 61, 47, 74, 145, 191, 5, 154, 9, 192, 88, 135, 5, 63, 36, 87, 81, 190, 50, 177, 184, 191, 87, 185, 131, 63, 40, 115, 153, 63, 169, 79, 155, 63, 3, 163, 108, 63, 143, 51, 21, 61, 76, 49, 5, 191, 228, 119, 25, 63, 236, 186, 47, 63, 1, 194, 147, 62, 129, 75, 155, 62, 47, 240, 153, 191, 111, 65, 101, 188, 95, 135, 147, 191, 142, 211, 48, 63, 131, 3, 230, 190, 243, 217, 2, 63, 198, 120, 187, 62, 169, 220, 132, 191, 23, 111, 138, 63, 183, 142, 244, 62, 77, 151, 151, 63, 234, 9, 135, 191, 149, 96, 2, 191, 217, 254, 50, 62, 19, 51, 221, 191, 8, 17, 144, 61, 58, 134, 130, 190, 74, 5, 19, 192, 223, 39, 125, 191, 20, 111, 126, 190, 108, 85, 213, 191, 242, 203, 184, 189, 238, 243, 67, 190, 231, 81, 202, 190, 223, 136, 56, 63, 58, 94, 135, 63, 235, 105, 171, 62, 212, 83, 152, 62, 132, 53, 25, 64, 85, 162, 92, 190, 52, 31, 120, 190, 15, 36, 190, 191, 168, 136, 77, 62, 15, 43, 25, 63, 79, 193, 66, 63, 86, 199, 107, 191, 137, 15, 74, 189, 8, 78, 28, 63, 233, 167, 113, 62, 28, 159, 22, 188, 104, 137, 57, 63, 253, 99, 11, 63, 198, 69, 218, 190, 253, 144, 21, 190, 172, 119, 50, 63, 158, 189, 114, 63, 122, 208, 65, 62, 139, 56, 217, 190, 215, 121, 217, 190, 232, 101, 193, 190, 218, 72, 12, 190, 184, 31, 186, 190, 94, 54, 239, 62, 17, 13, 35, 190, 183, 207, 95, 63, 57, 241, 139, 62, 216, 238, 239, 189, 36, 227, 99, 191, 80, 104, 140, 62, 64, 122, 155, 189, 88, 152, 5, 191, 148, 132, 200, 62, 34, 152, 254, 190, 73, 8, 183, 190, 174, 182, 139, 63, 36, 94, 35, 63, 24, 217, 186, 190, 173, 116, 45, 63, 27, 120, 36, 62, 205, 166, 178, 190, 156, 249, 92, 62, 187, 89, 236, 63, 35, 101, 190, 190, 108, 242, 252, 62, 69, 10, 86, 191, 104, 242, 138, 191, 130, 86, 204, 190, 68, 145, 234, 62, 119, 242, 171, 190, 241, 83, 38, 190, 20, 92, 137, 63, 9, 65, 21, 63, 58, 129, 252, 190, 209, 161, 212, 188, 250, 168, 162, 190, 179, 166, 23, 62, 98, 138, 71, 191, 127, 215, 54, 63, 180, 3, 215, 63, 217, 205, 3, 62, 245, 35, 38, 63, 12, 160, 73, 191, 87, 225, 120, 190, 185, 215, 70, 62, 201, 209, 187, 189, 218, 131, 29, 190, 42, 37, 228, 61, 41, 91, 68, 189, 246, 136, 213, 190, 139, 156, 147, 62, 93, 25, 80, 63, 170, 250, 229, 190, 39, 6, 172, 62, 63, 10, 12, 62, 66, 223, 217, 62, 165, 236, 115, 62, 53, 136, 180, 190, 214, 11, 144, 62, 57, 33, 16, 62, 169, 154, 7, 189, 175, 108, 61, 190, 74, 85, 45, 64, 71, 229, 101, 190, 190, 133, 240, 62, 70, 157, 106, 190, 253, 208, 94, 62, 210, 232, 248, 63, 97, 135, 3, 192, 5, 161, 139, 191, 15, 102, 27, 190, 192, 191, 123, 62, 15, 76, 1, 190, 94, 17, 7, 63, 201, 30, 8, 192, 206, 25, 92, 191, 159, 62, 131, 190, 40, 215, 37, 63, 193, 14, 134, 63, 11, 225, 211, 191, 173, 75, 106, 191, 203, 31, 206, 63, 167, 63, 221, 62, 81, 65, 133, 62, 73, 254, 143, 62, 11, 104, 41, 63, 183, 115, 26, 63, 93, 125, 189, 190, 240, 194, 46, 192, 118, 50, 77, 63, 127, 20, 96, 191, 127, 192, 140, 63, 23, 107, 79, 191, 171, 116, 246, 190, 49, 195, 237, 190, 250, 81, 187, 190, 18, 59, 204, 62, 47, 196, 11, 190, 43, 178, 73, 63, 207, 26, 45, 191, 164, 184, 109, 61, 185, 97, 240, 190, 132, 10, 132, 62, 48, 73, 149, 190, 214, 241, 189, 63, 165, 46, 92, 191, 10, 10, 4, 125, 142, 236, 71, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 176, 165, 121, 73, 38, 141, 114, 73, 171, 9, 108, 73, 165, 191, 213, 71, 8, 139, 223, 71, 154, 225, 230, 71, 170, 109, 44, 66, 75, 95, 248, 65, 204, 0, 195, 71, 180, 103, 76, 72, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 208, 78, 0, 74, 207, 175, 248, 73, 98, 119, 241, 73, 157, 8, 57, 72, 246, 231, 65, 72, 184, 61, 72, 72, 35, 102, 5, 65, 8, 95, 167, 63, 146, 98, 200, 68, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 145, 1, 254, 0, 2, 1, 5, 48, 117, 100, 0, 44, 1, 112, 23, 151, 7, 132, 3, 197, 0, 92, 4, 144, 1, 64, 1, 64, 1, 144, 1, 48, 117, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 48, 117, 48, 117, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 100, 0, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 100, 0, 100, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 112, 23, 112, 23, 112, 23, 112, 23, 8, 7, 8, 7, 8, 7, 8, 7, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 112, 23, 112, 23, 112, 23, 112, 23, 255, 255, 255, 255, 220, 5, 220, 5, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 220, 5, 220, 5, 220, 5, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 48, 117, 0, 1, 0, 5, 0, 2, 0, 10, 0, 30, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 64, 1, 100, 0, 100, 0, 100, 0, 200, 0, 200, 0, 200, 0, 64, 1, 64, 1, 64, 1, 10, 1, 0, 0, 0, 0, 0, 15, 16, 0, 0 };

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;

  BHY2.begin();

  accel.begin();
  gyro.begin();
  temp.begin();
  gas.begin();
  rotation.begin();

  sensortec.bhy2_bsec2_setConfigString(BSEC2CONFIG, sizeof(BSEC2CONFIG) / sizeof(BSEC2CONFIG[0]));
  bsec2.begin();

  SensorConfig cfg = accel.getConfiguration();
  Serial.println(String("range of accel: +/-") + cfg.range + String("g"));
  accel.setRange(2);  //this sets the range of accel to +/-4g,
  cfg = accel.getConfiguration();
  Serial.println(String("range of accel: +/-") + cfg.range + String("g"));

  cfg = gyro.getConfiguration();
  Serial.println(String("range of gyro: +/-") + cfg.range + String("dps"));
  gyro.setRange(1000);
  cfg = gyro.getConfiguration();
  Serial.println(String("range of gyro: +/-") + cfg.range + String("dps"));
}

void loop() {
  static auto printTime = millis();

  // Update function should be continuously polled
  BHY2.update();

  if (millis() - printTime >= 1000) {
    printTime = millis();

    if (accel.dataAvailable()) {
      Serial.println(String("acceleration: ") + accel.toString());
      accel.clearDataAvailFlag();
    }

    if (gyro.dataAvailable()) {
      Serial.println(String("gyroscope: ") + gyro.toString());
      gyro.clearDataAvailFlag();
    }

    if (temp.dataAvailable()) {
      Serial.println(String("temperature: ") + String(temp.value(), 3));
      temp.clearDataAvailFlag();
    }

    if (gas.dataAvailable()) {
      Serial.println(String("gas: ") + String(gas.value(), 3));
      gas.clearDataAvailFlag();
    }

    if (rotation.dataAvailable()) {
      Serial.println(String("rotation: ") + rotation.toString());
      rotation.clearDataAvailFlag();
    }
  }
}
