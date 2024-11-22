#include "Arduino.h"
#include "Arduino_BHY2.h"

Sensor gas(SENSOR_ID_GAS);
Sensor temp(SENSOR_ID_TEMP);
SensorXYZ gyro(SENSOR_ID_GYRO);
SensorXYZ accel(SENSOR_ID_ACC);
SensorBSEC bsec(SENSOR_ID_BSEC);
SensorBSEC2 bsec2(SENSOR_ID_BSEC2);
SensorQuaternion rotation(SENSOR_ID_RV);

const uint8_t BSEC2CONFIG[1943] = { 0, 1, 6, 2, 189, 1, 0, 0, 0, 0, 0, 0, 127, 7, 0, 0, 56, 0, 1, 0, 0, 168, 19, 73, 64, 49, 119, 76, 0, 0, 97, 69, 0, 0, 97, 69, 10, 0, 3, 0, 0, 0, 96, 64, 23, 183, 209, 56, 43, 24, 149, 60, 140, 74, 106, 188, 43, 24, 149, 60, 216, 129, 243, 190, 151, 255, 80, 190, 216, 129, 243, 190, 8, 0, 2, 0, 0, 0, 72, 66, 16, 0, 3, 0, 10, 215, 163, 60, 10, 215, 35, 59, 10, 215, 35, 59, 13, 0, 5, 0, 0, 0, 0, 0, 100, 254, 131, 137, 87, 88, 0, 9, 0, 7, 240, 150, 61, 0, 0, 0, 0, 0, 0, 0, 0, 28, 124, 225, 61, 52, 128, 215, 63, 0, 0, 160, 64, 0, 0, 0, 0, 0, 0, 0, 0, 205, 204, 12, 62, 103, 213, 39, 62, 230, 63, 76, 192, 0, 0, 0, 0, 0, 0, 0, 0, 145, 237, 60, 191, 251, 58, 64, 63, 177, 80, 131, 64, 0, 0, 0, 0, 0, 0, 0, 0, 93, 254, 227, 62, 54, 60, 133, 191, 0, 0, 64, 64, 12, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45, 5, 11, 0, 0, 0, 2, 239, 157, 147, 62, 122, 236, 202, 187, 178, 81, 243, 62, 184, 215, 133, 62, 168, 95, 89, 62, 138, 166, 212, 62, 48, 54, 68, 62, 106, 43, 141, 62, 74, 71, 177, 62, 203, 120, 163, 62, 204, 19, 181, 62, 38, 128, 18, 62, 183, 47, 180, 61, 72, 88, 118, 62, 156, 118, 131, 62, 195, 158, 55, 62, 0, 0, 0, 0, 37, 168, 216, 61, 55, 143, 150, 62, 215, 232, 112, 62, 165, 149, 10, 190, 80, 72, 16, 62, 45, 33, 53, 189, 0, 0, 0, 0, 196, 178, 241, 190, 25, 98, 177, 61, 70, 95, 12, 190, 32, 176, 55, 191, 226, 0, 196, 62, 130, 0, 177, 62, 210, 172, 137, 62, 187, 188, 110, 191, 222, 147, 18, 190, 16, 21, 18, 190, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 118, 145, 254, 190, 62, 166, 149, 189, 20, 199, 107, 190, 101, 255, 191, 190, 88, 11, 8, 63, 75, 49, 176, 62, 119, 141, 70, 61, 223, 253, 117, 190, 248, 215, 98, 191, 113, 195, 221, 60, 243, 156, 184, 190, 52, 143, 138, 189, 218, 80, 40, 62, 137, 235, 132, 190, 104, 15, 232, 61, 2, 176, 171, 62, 36, 106, 79, 62, 0, 12, 99, 190, 226, 79, 47, 190, 244, 147, 9, 62, 87, 100, 174, 190, 221, 217, 45, 62, 77, 140, 156, 62, 248, 54, 223, 190, 167, 81, 59, 190, 185, 165, 222, 62, 241, 247, 176, 62, 97, 12, 162, 190, 40, 72, 245, 190, 118, 247, 174, 62, 91, 42, 125, 190, 78, 182, 47, 190, 216, 230, 138, 60, 246, 179, 70, 61, 92, 23, 247, 62, 49, 91, 134, 61, 68, 117, 104, 62, 166, 160, 182, 61, 11, 164, 178, 190, 196, 223, 172, 62, 254, 164, 131, 61, 131, 166, 32, 60, 244, 131, 156, 190, 71, 175, 149, 189, 41, 231, 14, 190, 119, 76, 4, 63, 245, 161, 129, 62, 110, 125, 129, 191, 194, 76, 168, 190, 62, 165, 132, 62, 222, 225, 104, 190, 123, 205, 164, 62, 81, 202, 7, 63, 129, 148, 207, 190, 9, 105, 38, 63, 39, 0, 103, 61, 189, 80, 145, 62, 142, 48, 23, 191, 221, 183, 187, 61, 225, 95, 142, 61, 25, 127, 83, 191, 95, 167, 163, 63, 35, 218, 4, 191, 233, 186, 33, 63, 33, 69, 132, 189, 3, 62, 196, 190, 140, 53, 74, 62, 193, 43, 224, 190, 139, 49, 169, 63, 177, 175, 253, 190, 115, 168, 15, 63, 221, 166, 167, 62, 229, 221, 128, 191, 143, 63, 36, 190, 53, 205, 56, 187, 230, 28, 194, 190, 131, 179, 251, 190, 138, 198, 148, 189, 236, 251, 40, 62, 45, 239, 78, 61, 150, 240, 30, 191, 207, 62, 209, 62, 24, 4, 70, 191, 115, 220, 41, 63, 164, 156, 199, 61, 4, 117, 151, 190, 203, 95, 43, 63, 171, 175, 223, 190, 53, 103, 112, 61, 180, 165, 189, 190, 56, 208, 214, 62, 113, 21, 106, 62, 172, 210, 218, 59, 49, 77, 196, 189, 73, 34, 157, 62, 31, 63, 31, 63, 123, 162, 163, 61, 117, 120, 159, 190, 189, 199, 170, 62, 26, 248, 220, 62, 30, 129, 210, 189, 33, 53, 132, 63, 251, 60, 75, 63, 73, 61, 47, 63, 93, 241, 241, 189, 231, 50, 158, 191, 126, 104, 125, 189, 195, 222, 177, 63, 112, 190, 8, 191, 117, 110, 169, 191, 241, 18, 236, 62, 75, 22, 146, 62, 12, 167, 164, 63, 83, 243, 188, 189, 183, 49, 91, 63, 120, 140, 40, 191, 157, 30, 206, 190, 152, 62, 65, 63, 94, 98, 9, 190, 207, 213, 81, 191, 75, 38, 142, 191, 235, 65, 244, 190, 243, 1, 156, 62, 145, 242, 60, 63, 184, 219, 181, 190, 192, 228, 169, 189, 189, 76, 2, 191, 39, 212, 97, 63, 112, 1, 226, 190, 177, 124, 159, 189, 144, 16, 186, 62, 12, 6, 58, 63, 140, 169, 15, 61, 182, 191, 194, 60, 19, 170, 81, 62, 240, 35, 5, 191, 246, 231, 225, 61, 240, 150, 73, 191, 123, 123, 226, 61, 247, 34, 252, 190, 4, 240, 14, 63, 176, 26, 207, 62, 128, 75, 113, 190, 96, 12, 133, 61, 56, 172, 165, 62, 33, 112, 80, 190, 136, 240, 9, 191, 155, 228, 224, 60, 192, 72, 24, 63, 200, 205, 233, 190, 63, 204, 40, 60, 238, 93, 21, 63, 148, 41, 162, 61, 96, 5, 4, 189, 54, 1, 40, 63, 15, 252, 126, 62, 252, 43, 247, 61, 86, 40, 79, 61, 32, 143, 243, 62, 133, 57, 17, 191, 185, 13, 163, 189, 149, 196, 75, 189, 30, 222, 175, 190, 98, 225, 223, 62, 4, 247, 11, 62, 230, 87, 243, 62, 150, 197, 22, 190, 141, 222, 228, 190, 250, 176, 38, 63, 249, 202, 248, 62, 23, 151, 16, 191, 222, 24, 211, 189, 165, 133, 224, 61, 9, 250, 28, 63, 32, 115, 114, 191, 143, 116, 110, 190, 53, 140, 17, 191, 149, 176, 173, 62, 136, 142, 126, 190, 188, 198, 167, 62, 66, 184, 126, 63, 128, 139, 61, 63, 172, 9, 6, 63, 135, 151, 170, 190, 115, 103, 84, 63, 26, 101, 4, 191, 113, 49, 151, 188, 5, 93, 94, 190, 50, 82, 67, 63, 59, 131, 182, 189, 21, 185, 137, 63, 155, 234, 18, 191, 214, 3, 156, 191, 0, 0, 0, 0, 148, 70, 31, 63, 76, 34, 193, 60, 203, 175, 34, 191, 0, 0, 0, 0, 208, 70, 227, 62, 248, 241, 182, 63, 23, 118, 214, 191, 0, 0, 0, 0, 91, 218, 61, 191, 139, 56, 133, 63, 176, 55, 106, 62, 0, 0, 0, 0, 184, 185, 208, 62, 254, 138, 151, 188, 160, 152, 46, 191, 0, 0, 0, 0, 36, 84, 175, 190, 21, 207, 158, 191, 206, 98, 145, 63, 0, 0, 0, 0, 185, 183, 160, 62, 40, 11, 227, 62, 90, 153, 76, 62, 0, 0, 0, 0, 159, 200, 90, 62, 214, 2, 143, 63, 232, 188, 147, 190, 0, 0, 0, 0, 67, 55, 51, 63, 185, 229, 206, 190, 99, 27, 62, 63, 0, 0, 0, 0, 98, 226, 102, 191, 140, 81, 80, 191, 143, 76, 130, 63, 0, 0, 0, 0, 10, 10, 3, 46, 111, 136, 72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40, 146, 39, 74, 7, 59, 34, 74, 209, 31, 29, 74, 128, 39, 118, 72, 187, 15, 129, 72, 213, 58, 133, 72, 103, 208, 22, 66, 126, 108, 247, 65, 22, 111, 196, 71, 230, 231, 189, 72, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 181, 69, 129, 74, 94, 88, 121, 74, 136, 156, 112, 74, 215, 46, 170, 72, 167, 69, 179, 72, 120, 108, 185, 72, 72, 243, 211, 64, 172, 174, 141, 63, 52, 43, 190, 68, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 145, 1, 254, 0, 2, 1, 5, 48, 117, 100, 0, 44, 1, 112, 23, 151, 7, 132, 3, 197, 0, 92, 4, 144, 1, 64, 1, 64, 1, 144, 1, 48, 117, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 48, 117, 48, 117, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 100, 0, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 100, 0, 100, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 112, 23, 112, 23, 112, 23, 112, 23, 8, 7, 8, 7, 8, 7, 8, 7, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 112, 23, 112, 23, 112, 23, 112, 23, 255, 255, 255, 255, 220, 5, 220, 5, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 220, 5, 220, 5, 220, 5, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 48, 117, 0, 1, 0, 5, 0, 2, 0, 10, 0, 30, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 64, 1, 100, 0, 100, 0, 100, 0, 200, 0, 200, 0, 200, 0, 64, 1, 64, 1, 64, 1, 10, 1, 0, 0, 0, 0, 0, 120, 2, 0, 0 };
//Example configu: gas 0: Ambient, gas 1: alcohol leave bracket empty[]
// { 0, 0, 2, 2, 189, 1, 0, 0, 0, 0, 0, 0, 213, 8, 0, 0, 52, 0, 1, 0, 0, 168, 19, 73, 64, 49, 119, 76, 0, 192, 40, 72, 0, 192, 40, 72, 137, 65, 0, 191, 205, 204, 204, 190, 0, 0, 64, 191, 225, 122, 148, 190, 10, 0, 3, 0, 216, 85, 0, 100, 0, 0, 96, 64, 23, 183, 209, 56, 28, 0, 2, 0, 0, 244, 1, 150, 0, 50, 0, 0, 128, 64, 0, 0, 32, 65, 144, 1, 0, 0, 112, 65, 0, 0, 0, 63, 16, 0, 3, 0, 10, 215, 163, 60, 10, 215, 35, 59, 10, 215, 35, 59, 13, 0, 5, 0, 0, 0, 0, 0, 100, 254, 131, 137, 87, 88, 0, 9, 0, 7, 240, 150, 61, 0, 0, 0, 0, 0, 0, 0, 0, 28, 124, 225, 61, 52, 128, 215, 63, 0, 0, 160, 64, 0, 0, 0, 0, 0, 0, 0, 0, 205, 204, 12, 62, 103, 213, 39, 62, 230, 63, 76, 192, 0, 0, 0, 0, 0, 0, 0, 0, 145, 237, 60, 191, 251, 58, 64, 63, 177, 80, 131, 64, 0, 0, 0, 0, 0, 0, 0, 0, 93, 254, 227, 62, 54, 60, 133, 191, 0, 0, 64, 64, 12, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 173, 6, 11, 0, 0, 0, 2, 231, 201, 67, 189, 125, 37, 201, 61, 179, 41, 106, 189, 97, 167, 196, 61, 84, 172, 113, 62, 155, 213, 214, 61, 133, 10, 114, 61, 62, 67, 214, 61, 56, 97, 57, 62, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42, 215, 83, 190, 42, 215, 83, 62, 0, 0, 0, 0, 0, 0, 0, 0, 97, 101, 165, 61, 88, 151, 51, 190, 184, 89, 165, 62, 240, 207, 20, 191, 47, 208, 53, 63, 177, 43, 63, 190, 176, 56, 145, 189, 228, 194, 10, 191, 173, 194, 44, 191, 0, 0, 0, 0, 146, 253, 150, 61, 217, 5, 157, 59, 36, 134, 171, 190, 159, 38, 128, 59, 58, 78, 29, 189, 204, 88, 63, 191, 210, 42, 125, 190, 59, 171, 228, 190, 78, 165, 243, 190, 0, 0, 0, 0, 171, 98, 187, 188, 83, 234, 57, 191, 66, 87, 75, 62, 209, 91, 130, 62, 133, 244, 221, 61, 242, 192, 118, 190, 13, 13, 52, 62, 235, 86, 146, 62, 147, 48, 2, 191, 0, 0, 0, 0, 80, 192, 203, 190, 252, 170, 134, 189, 5, 138, 208, 62, 255, 220, 147, 62, 184, 119, 166, 62, 192, 231, 125, 189, 181, 36, 79, 190, 124, 71, 210, 62, 55, 239, 13, 191, 0, 0, 0, 0, 226, 139, 200, 189, 182, 220, 91, 190, 113, 205, 238, 189, 235, 255, 228, 190, 201, 16, 66, 63, 123, 50, 149, 61, 80, 26, 112, 62, 66, 108, 128, 62, 233, 205, 253, 190, 0, 0, 0, 0, 223, 117, 24, 189, 133, 115, 60, 62, 197, 48, 0, 189, 60, 64, 194, 61, 189, 86, 246, 61, 185, 197, 54, 189, 133, 63, 90, 190, 239, 233, 46, 190, 14, 247, 19, 191, 0, 0, 0, 0, 193, 26, 240, 62, 151, 185, 23, 190, 33, 105, 234, 190, 5, 24, 166, 190, 197, 45, 23, 63, 196, 211, 145, 190, 178, 103, 164, 190, 125, 36, 6, 191, 234, 28, 114, 190, 0, 0, 0, 0, 136, 73, 125, 62, 234, 189, 27, 62, 200, 69, 225, 189, 15, 56, 142, 190, 188, 47, 134, 190, 174, 248, 193, 190, 221, 81, 161, 190, 152, 89, 51, 189, 86, 157, 105, 61, 0, 0, 0, 0, 116, 72, 209, 190, 237, 104, 63, 189, 60, 50, 39, 189, 40, 194, 15, 191, 232, 34, 133, 62, 163, 192, 193, 61, 38, 90, 147, 189, 198, 159, 7, 191, 240, 239, 146, 61, 0, 0, 0, 0, 93, 146, 86, 61, 185, 23, 6, 62, 12, 52, 10, 62, 9, 82, 26, 191, 186, 80, 1, 63, 130, 184, 195, 190, 43, 204, 83, 62, 73, 27, 220, 189, 254, 195, 200, 189, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 9, 53, 212, 189, 25, 224, 132, 190, 0, 0, 0, 0, 0, 0, 0, 0, 133, 45, 39, 63, 65, 50, 45, 191, 0, 0, 0, 0, 0, 0, 0, 0, 76, 73, 7, 62, 150, 167, 209, 189, 0, 0, 0, 0, 0, 0, 0, 0, 242, 163, 107, 63, 193, 223, 173, 62, 0, 0, 0, 0, 0, 0, 0, 0, 192, 205, 68, 190, 213, 103, 28, 63, 0, 0, 0, 0, 0, 0, 0, 0, 60, 148, 171, 62, 151, 246, 154, 189, 0, 0, 0, 0, 0, 0, 0, 0, 162, 104, 218, 62, 88, 44, 237, 190, 0, 0, 0, 0, 0, 0, 0, 0, 253, 226, 216, 62, 249, 223, 161, 189, 0, 0, 0, 0, 0, 0, 0, 0, 168, 65, 13, 190, 119, 123, 179, 190, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 160, 184, 18, 72, 125, 52, 223, 75, 204, 85, 211, 75, 119, 27, 192, 75, 83, 228, 150, 73, 122, 154, 142, 73, 133, 214, 135, 73, 145, 149, 237, 71, 56, 196, 2, 72, 221, 197, 11, 72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 158, 236, 10, 72, 35, 30, 221, 75, 206, 136, 209, 75, 14, 146, 190, 75, 218, 105, 148, 73, 65, 65, 140, 73, 150, 149, 133, 73, 206, 248, 222, 71, 219, 117, 246, 71, 96, 19, 4, 72, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 0, 87, 1, 254, 0, 2, 1, 5, 48, 117, 100, 0, 44, 1, 112, 23, 151, 7, 132, 3, 197, 0, 92, 4, 144, 1, 64, 1, 64, 1, 144, 1, 48, 117, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 48, 117, 48, 117, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 100, 0, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 100, 0, 100, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 220, 5, 220, 5, 220, 5, 255, 255, 255, 255, 255, 255, 220, 5, 220, 5, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 48, 117, 0, 1, 0, 5, 0, 2, 0, 10, 0, 30, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 64, 1, 100, 0, 100, 0, 100, 0, 200, 0, 200, 0, 200, 0, 64, 1, 64, 1, 64, 1, 10, 0, 0, 0, 0, 95, 8, 0, 0 };
// { 0, 1, 6, 2, 189, 1, 0, 0, 0, 0, 0, 0, 127, 7, 0, 0, 56, 0, 1, 0, 0, 168, 19, 73, 64, 49, 119, 76, 0, 0, 97, 69, 0, 0, 97, 69, 10, 0, 3, 0, 0, 0, 96, 64, 23, 183, 209, 56, 43, 24, 149, 60, 140, 74, 106, 188, 43, 24, 149, 60, 216, 129, 243, 190, 151, 255, 80, 190, 216, 129, 243, 190, 8, 0, 2, 0, 0, 0, 72, 66, 16, 0, 3, 0, 10, 215, 163, 60, 10, 215, 35, 59, 10, 215, 35, 59, 13, 0, 5, 0, 0, 0, 0, 0, 100, 254, 131, 137, 87, 88, 0, 9, 0, 7, 240, 150, 61, 0, 0, 0, 0, 0, 0, 0, 0, 28, 124, 225, 61, 52, 128, 215, 63, 0, 0, 160, 64, 0, 0, 0, 0, 0, 0, 0, 0, 205, 204, 12, 62, 103, 213, 39, 62, 230, 63, 76, 192, 0, 0, 0, 0, 0, 0, 0, 0, 145, 237, 60, 191, 251, 58, 64, 63, 177, 80, 131, 64, 0, 0, 0, 0, 0, 0, 0, 0, 93, 254, 227, 62, 54, 60, 133, 191, 0, 0, 64, 64, 12, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45, 5, 11, 0, 0, 0, 2, 33, 145, 55, 191, 191, 145, 40, 63, 208, 15, 119, 63, 229, 206, 100, 191, 77, 207, 175, 63, 4, 69, 104, 62, 42, 129, 174, 62, 86, 63, 67, 62, 138, 6, 120, 191, 182, 167, 130, 62, 159, 88, 137, 62, 71, 100, 3, 62, 247, 74, 113, 191, 172, 150, 140, 61, 165, 27, 162, 59, 22, 4, 128, 191, 223, 167, 44, 63, 243, 22, 139, 62, 198, 145, 20, 191, 98, 98, 42, 63, 3, 42, 12, 191, 247, 209, 56, 190, 135, 238, 20, 63, 0, 0, 0, 0, 22, 39, 50, 63, 27, 59, 128, 190, 204, 206, 71, 190, 175, 90, 135, 63, 186, 152, 43, 191, 127, 67, 25, 63, 135, 118, 24, 191, 59, 130, 82, 189, 180, 99, 64, 63, 166, 254, 95, 63, 24, 7, 227, 61, 137, 165, 72, 62, 105, 153, 190, 62, 10, 25, 148, 62, 220, 45, 173, 62, 218, 105, 162, 62, 62, 116, 159, 189, 189, 11, 233, 190, 147, 197, 26, 63, 215, 215, 55, 63, 95, 79, 147, 62, 118, 152, 234, 188, 243, 232, 251, 62, 67, 30, 216, 61, 156, 234, 92, 63, 197, 65, 83, 62, 64, 11, 185, 190, 234, 88, 207, 190, 89, 68, 248, 189, 112, 207, 87, 63, 15, 52, 11, 63, 168, 78, 29, 61, 107, 212, 37, 63, 182, 72, 42, 63, 142, 178, 81, 63, 90, 214, 79, 63, 180, 209, 24, 191, 1, 75, 25, 191, 125, 20, 215, 60, 175, 45, 139, 63, 117, 191, 179, 61, 196, 127, 141, 190, 53, 173, 242, 188, 51, 204, 70, 189, 137, 106, 215, 190, 175, 197, 107, 62, 144, 48, 221, 190, 89, 168, 187, 62, 24, 20, 86, 188, 238, 39, 213, 62, 116, 184, 151, 190, 165, 137, 38, 191, 72, 133, 179, 62, 197, 160, 182, 190, 79, 236, 174, 61, 226, 39, 72, 62, 46, 225, 211, 190, 117, 201, 140, 60, 250, 199, 123, 62, 114, 51, 224, 62, 175, 73, 173, 62, 88, 176, 74, 191, 31, 8, 178, 189, 139, 205, 209, 62, 134, 107, 5, 62, 147, 120, 226, 189, 112, 219, 232, 190, 21, 170, 15, 187, 104, 188, 141, 61, 104, 38, 44, 63, 186, 84, 166, 62, 100, 28, 79, 191, 86, 177, 61, 190, 61, 40, 223, 62, 127, 183, 167, 190, 224, 213, 82, 63, 18, 216, 132, 191, 142, 121, 232, 190, 49, 204, 127, 63, 140, 163, 91, 63, 43, 7, 122, 62, 108, 23, 0, 191, 157, 197, 72, 189, 15, 53, 114, 63, 15, 168, 226, 61, 231, 1, 142, 61, 248, 3, 57, 191, 35, 64, 208, 190, 132, 200, 184, 62, 219, 98, 131, 63, 100, 248, 247, 62, 87, 65, 45, 191, 177, 240, 160, 61, 36, 165, 235, 61, 153, 95, 223, 190, 123, 124, 117, 62, 50, 101, 39, 190, 231, 53, 38, 191, 138, 243, 151, 63, 55, 243, 92, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 160, 115, 129, 188, 141, 19, 209, 191, 189, 188, 64, 62, 215, 200, 171, 191, 144, 70, 185, 62, 36, 109, 55, 63, 250, 42, 156, 62, 81, 162, 245, 190, 19, 96, 105, 62, 154, 203, 135, 186, 2, 100, 204, 62, 146, 15, 206, 62, 181, 232, 189, 190, 144, 202, 147, 62, 198, 33, 45, 63, 161, 87, 152, 63, 213, 241, 227, 59, 110, 135, 13, 63, 140, 209, 47, 63, 85, 242, 199, 189, 173, 218, 183, 189, 203, 43, 113, 63, 176, 60, 63, 191, 236, 66, 44, 190, 47, 17, 179, 190, 44, 208, 162, 191, 32, 0, 18, 63, 3, 203, 54, 190, 34, 63, 50, 191, 87, 153, 60, 63, 251, 207, 100, 189, 221, 214, 146, 191, 169, 43, 80, 63, 77, 111, 173, 191, 31, 241, 64, 190, 131, 237, 12, 63, 253, 170, 42, 63, 170, 195, 169, 189, 77, 242, 76, 63, 78, 18, 217, 188, 213, 138, 42, 63, 196, 229, 133, 63, 255, 133, 169, 191, 150, 240, 242, 62, 211, 183, 43, 191, 167, 151, 142, 191, 109, 29, 7, 63, 179, 219, 170, 62, 154, 175, 70, 191, 59, 167, 226, 62, 55, 126, 158, 191, 213, 220, 23, 63, 38, 72, 206, 62, 112, 26, 154, 62, 27, 50, 211, 190, 249, 39, 134, 189, 201, 142, 12, 63, 8, 101, 56, 191, 72, 74, 142, 189, 224, 3, 123, 62, 157, 96, 66, 63, 13, 67, 221, 190, 151, 175, 239, 60, 63, 181, 33, 63, 33, 209, 18, 62, 30, 205, 106, 63, 215, 68, 89, 62, 187, 104, 71, 63, 93, 163, 39, 63, 103, 89, 248, 61, 153, 188, 4, 191, 162, 52, 8, 191, 167, 231, 60, 61, 103, 253, 52, 63, 171, 28, 42, 63, 139, 252, 183, 63, 46, 43, 105, 191, 160, 154, 238, 62, 73, 13, 80, 63, 224, 37, 108, 191, 175, 26, 73, 190, 150, 161, 255, 191, 18, 51, 101, 63, 27, 237, 185, 191, 48, 137, 222, 61, 234, 205, 94, 63, 154, 246, 191, 190, 64, 190, 254, 189, 49, 73, 195, 62, 60, 175, 29, 63, 190, 2, 172, 191, 214, 214, 185, 61, 15, 13, 113, 59, 124, 40, 76, 63, 52, 91, 9, 61, 248, 46, 134, 62, 48, 41, 170, 62, 217, 51, 152, 191, 85, 147, 240, 61, 74, 34, 97, 63, 64, 231, 194, 191, 202, 120, 113, 190, 56, 184, 204, 63, 0, 0, 0, 0, 73, 149, 220, 63, 111, 38, 148, 191, 88, 54, 39, 191, 0, 0, 0, 0, 169, 60, 236, 63, 255, 232, 135, 190, 119, 236, 158, 191, 0, 0, 0, 0, 14, 149, 133, 62, 162, 0, 38, 63, 43, 48, 204, 190, 0, 0, 0, 0, 144, 105, 228, 190, 243, 133, 135, 63, 243, 252, 22, 191, 0, 0, 0, 0, 245, 74, 181, 63, 228, 226, 17, 63, 49, 124, 181, 191, 0, 0, 0, 0, 217, 126, 250, 190, 249, 149, 139, 191, 21, 12, 180, 62, 0, 0, 0, 0, 212, 132, 208, 191, 88, 135, 36, 63, 247, 56, 84, 63, 0, 0, 0, 0, 114, 122, 150, 63, 248, 244, 70, 63, 117, 126, 182, 191, 0, 0, 0, 0, 21, 57, 26, 61, 62, 138, 220, 190, 12, 56, 228, 62, 0, 0, 0, 0, 10, 10, 3, 88, 90, 253, 72, 169, 253, 127, 76, 149, 89, 123, 76, 137, 117, 120, 76, 83, 245, 204, 74, 88, 57, 201, 74, 238, 201, 197, 74, 219, 211, 236, 72, 154, 220, 242, 72, 169, 199, 248, 72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 66, 221, 234, 72, 92, 124, 99, 76, 110, 243, 95, 76, 185, 80, 94, 76, 206, 156, 207, 74, 179, 12, 204, 74, 122, 200, 200, 74, 122, 81, 221, 72, 189, 109, 226, 72, 249, 34, 231, 72, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 145, 1, 254, 0, 2, 1, 5, 48, 117, 100, 0, 44, 1, 112, 23, 151, 7, 132, 3, 197, 0, 92, 4, 144, 1, 64, 1, 64, 1, 144, 1, 48, 117, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 48, 117, 48, 117, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 100, 0, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 100, 0, 100, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 112, 23, 112, 23, 112, 23, 112, 23, 8, 7, 8, 7, 8, 7, 8, 7, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 112, 23, 112, 23, 112, 23, 112, 23, 255, 255, 255, 255, 220, 5, 220, 5, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 220, 5, 220, 5, 220, 5, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 48, 117, 0, 1, 0, 5, 0, 2, 0, 10, 0, 30, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 64, 1, 100, 0, 100, 0, 100, 0, 200, 0, 200, 0, 200, 0, 64, 1, 64, 1, 64, 1, 10, 1, 0, 0, 0, 0, 0, 76, 183, 0, 0 };

void setup() {
  Serial.begin(115200);
  BHY2.begin();
  gas.begin();
  temp.begin();
  gyro.begin();
  accel.begin();
  bsec.begin();
  sensortec.bhy2_bsec2_setConfigString(BSEC2CONFIG, sizeof(BSEC2CONFIG) / sizeof(BSEC2CONFIG[0]));
  bsec2.begin();
  rotation.begin();
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
  BHY2.update();  // Update function should be continuously polled
  if (millis() - printTime >= 1000) {
    printTime = millis();
    Serial.println(String("gas: ") + String(gas.value()));
    Serial.println(String("temperature: ") + String(temp.value(), 2));
    Serial.print(String("gyroscope: ") + gyro.toString());
    Serial.print(String("acceleration: ") + accel.toString());
    Serial.print(rotation.toString());
    Serial.print(bsec.toString());
    Serial.print(bsec2.toString());




  }
}
