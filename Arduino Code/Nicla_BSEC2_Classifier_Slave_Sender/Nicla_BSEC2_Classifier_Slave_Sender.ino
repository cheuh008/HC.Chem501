/*
 * Code Based on
 *    Wire Master Writer by Nicholas Zambetti <http://www.zambetti.com>
 *    and
 *    BSEC2GasScannerClassify.ino from BHY2 example
 *
 * Edited by Harry Cheung @cheuh008
 *  For more detail, refer to docs @https://github.com/cheuh008/HC.Chem501
 *  This example code is in the public domain.
 */

#include <Wire.h>
#include "Arduino.h"
#include "Arduino_BHY2.h"

SensorBSEC2 bsec2(SENSOR_ID_BSEC2);

const uint8_t BSEC2CONFIG[1943] = //currently on ALgo 4 
// 1. Example, empty [], gas 0 alcohol, gas 1 ambient
// { 0, 0, 2, 2, 189, 1, 0, 0, 0, 0, 0, 0, 213, 8, 0, 0, 52, 0, 1, 0, 0, 168, 19, 73, 64, 49, 119, 76, 0, 192, 40, 72, 0, 192, 40, 72, 137, 65, 0, 191, 205, 204, 204, 190, 0, 0, 64, 191, 225, 122, 148, 190, 10, 0, 3, 0, 216, 85, 0, 100, 0, 0, 96, 64, 23, 183, 209, 56, 28, 0, 2, 0, 0, 244, 1, 150, 0, 50, 0, 0, 128, 64, 0, 0, 32, 65, 144, 1, 0, 0, 112, 65, 0, 0, 0, 63, 16, 0, 3, 0, 10, 215, 163, 60, 10, 215, 35, 59, 10, 215, 35, 59, 13, 0, 5, 0, 0, 0, 0, 0, 100, 254, 131, 137, 87, 88, 0, 9, 0, 7, 240, 150, 61, 0, 0, 0, 0, 0, 0, 0, 0, 28, 124, 225, 61, 52, 128, 215, 63, 0, 0, 160, 64, 0, 0, 0, 0, 0, 0, 0, 0, 205, 204, 12, 62, 103, 213, 39, 62, 230, 63, 76, 192, 0, 0, 0, 0, 0, 0, 0, 0, 145, 237, 60, 191, 251, 58, 64, 63, 177, 80, 131, 64, 0, 0, 0, 0, 0, 0, 0, 0, 93, 254, 227, 62, 54, 60, 133, 191, 0, 0, 64, 64, 12, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 173, 6, 11, 0, 0, 0, 2, 231, 201, 67, 189, 125, 37, 201, 61, 179, 41, 106, 189, 97, 167, 196, 61, 84, 172, 113, 62, 155, 213, 214, 61, 133, 10, 114, 61, 62, 67, 214, 61, 56, 97, 57, 62, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42, 215, 83, 190, 42, 215, 83, 62, 0, 0, 0, 0, 0, 0, 0, 0, 97, 101, 165, 61, 88, 151, 51, 190, 184, 89, 165, 62, 240, 207, 20, 191, 47, 208, 53, 63, 177, 43, 63, 190, 176, 56, 145, 189, 228, 194, 10, 191, 173, 194, 44, 191, 0, 0, 0, 0, 146, 253, 150, 61, 217, 5, 157, 59, 36, 134, 171, 190, 159, 38, 128, 59, 58, 78, 29, 189, 204, 88, 63, 191, 210, 42, 125, 190, 59, 171, 228, 190, 78, 165, 243, 190, 0, 0, 0, 0, 171, 98, 187, 188, 83, 234, 57, 191, 66, 87, 75, 62, 209, 91, 130, 62, 133, 244, 221, 61, 242, 192, 118, 190, 13, 13, 52, 62, 235, 86, 146, 62, 147, 48, 2, 191, 0, 0, 0, 0, 80, 192, 203, 190, 252, 170, 134, 189, 5, 138, 208, 62, 255, 220, 147, 62, 184, 119, 166, 62, 192, 231, 125, 189, 181, 36, 79, 190, 124, 71, 210, 62, 55, 239, 13, 191, 0, 0, 0, 0, 226, 139, 200, 189, 182, 220, 91, 190, 113, 205, 238, 189, 235, 255, 228, 190, 201, 16, 66, 63, 123, 50, 149, 61, 80, 26, 112, 62, 66, 108, 128, 62, 233, 205, 253, 190, 0, 0, 0, 0, 223, 117, 24, 189, 133, 115, 60, 62, 197, 48, 0, 189, 60, 64, 194, 61, 189, 86, 246, 61, 185, 197, 54, 189, 133, 63, 90, 190, 239, 233, 46, 190, 14, 247, 19, 191, 0, 0, 0, 0, 193, 26, 240, 62, 151, 185, 23, 190, 33, 105, 234, 190, 5, 24, 166, 190, 197, 45, 23, 63, 196, 211, 145, 190, 178, 103, 164, 190, 125, 36, 6, 191, 234, 28, 114, 190, 0, 0, 0, 0, 136, 73, 125, 62, 234, 189, 27, 62, 200, 69, 225, 189, 15, 56, 142, 190, 188, 47, 134, 190, 174, 248, 193, 190, 221, 81, 161, 190, 152, 89, 51, 189, 86, 157, 105, 61, 0, 0, 0, 0, 116, 72, 209, 190, 237, 104, 63, 189, 60, 50, 39, 189, 40, 194, 15, 191, 232, 34, 133, 62, 163, 192, 193, 61, 38, 90, 147, 189, 198, 159, 7, 191, 240, 239, 146, 61, 0, 0, 0, 0, 93, 146, 86, 61, 185, 23, 6, 62, 12, 52, 10, 62, 9, 82, 26, 191, 186, 80, 1, 63, 130, 184, 195, 190, 43, 204, 83, 62, 73, 27, 220, 189, 254, 195, 200, 189, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 9, 53, 212, 189, 25, 224, 132, 190, 0, 0, 0, 0, 0, 0, 0, 0, 133, 45, 39, 63, 65, 50, 45, 191, 0, 0, 0, 0, 0, 0, 0, 0, 76, 73, 7, 62, 150, 167, 209, 189, 0, 0, 0, 0, 0, 0, 0, 0, 242, 163, 107, 63, 193, 223, 173, 62, 0, 0, 0, 0, 0, 0, 0, 0, 192, 205, 68, 190, 213, 103, 28, 63, 0, 0, 0, 0, 0, 0, 0, 0, 60, 148, 171, 62, 151, 246, 154, 189, 0, 0, 0, 0, 0, 0, 0, 0, 162, 104, 218, 62, 88, 44, 237, 190, 0, 0, 0, 0, 0, 0, 0, 0, 253, 226, 216, 62, 249, 223, 161, 189, 0, 0, 0, 0, 0, 0, 0, 0, 168, 65, 13, 190, 119, 123, 179, 190, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 160, 184, 18, 72, 125, 52, 223, 75, 204, 85, 211, 75, 119, 27, 192, 75, 83, 228, 150, 73, 122, 154, 142, 73, 133, 214, 135, 73, 145, 149, 237, 71, 56, 196, 2, 72, 221, 197, 11, 72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 158, 236, 10, 72, 35, 30, 221, 75, 206, 136, 209, 75, 14, 146, 190, 75, 218, 105, 148, 73, 65, 65, 140, 73, 150, 149, 133, 73, 206, 248, 222, 71, 219, 117, 246, 71, 96, 19, 4, 72, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 0, 87, 1, 254, 0, 2, 1, 5, 48, 117, 100, 0, 44, 1, 112, 23, 151, 7, 132, 3, 197, 0, 92, 4, 144, 1, 64, 1, 64, 1, 144, 1, 48, 117, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 48, 117, 48, 117, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 100, 0, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 100, 0, 100, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 220, 5, 220, 5, 220, 5, 255, 255, 255, 255, 255, 255, 220, 5, 220, 5, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 48, 117, 0, 1, 0, 5, 0, 2, 0, 10, 0, 30, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 64, 1, 100, 0, 100, 0, 100, 0, 200, 0, 200, 0, 200, 0, 64, 1, 64, 1, 64, 1, 10, 0, 0, 0, 0, 95, 8, 0, 0 };
// 2. from BME Ai Studio, Algo 3, [1943] gas 0 Ambient, Gas 1 Acetone, Gas 2 Ethyl Acetate
// { 0, 1, 6, 2, 189, 1, 0, 0, 0, 0, 0, 0, 127, 7, 0, 0, 56, 0, 1, 0, 0, 168, 19, 73, 64, 49, 119, 76, 0, 0, 97, 69, 0, 0, 97, 69, 10, 0, 3, 0, 0, 0, 96, 64, 23, 183, 209, 56, 43, 24, 149, 60, 140, 74, 106, 188, 43, 24, 149, 60, 216, 129, 243, 190, 151, 255, 80, 190, 216, 129, 243, 190, 8, 0, 2, 0, 0, 0, 72, 66, 16, 0, 3, 0, 10, 215, 163, 60, 10, 215, 35, 59, 10, 215, 35, 59, 13, 0, 5, 0, 0, 0, 0, 0, 100, 254, 131, 137, 87, 88, 0, 9, 0, 7, 240, 150, 61, 0, 0, 0, 0, 0, 0, 0, 0, 28, 124, 225, 61, 52, 128, 215, 63, 0, 0, 160, 64, 0, 0, 0, 0, 0, 0, 0, 0, 205, 204, 12, 62, 103, 213, 39, 62, 230, 63, 76, 192, 0, 0, 0, 0, 0, 0, 0, 0, 145, 237, 60, 191, 251, 58, 64, 63, 177, 80, 131, 64, 0, 0, 0, 0, 0, 0, 0, 0, 93, 254, 227, 62, 54, 60, 133, 191, 0, 0, 64, 64, 12, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45, 5, 11, 0, 0, 0, 2, 239, 157, 147, 62, 122, 236, 202, 187, 178, 81, 243, 62, 184, 215, 133, 62, 168, 95, 89, 62, 138, 166, 212, 62, 48, 54, 68, 62, 106, 43, 141, 62, 74, 71, 177, 62, 203, 120, 163, 62, 204, 19, 181, 62, 38, 128, 18, 62, 183, 47, 180, 61, 72, 88, 118, 62, 156, 118, 131, 62, 195, 158, 55, 62, 0, 0, 0, 0, 37, 168, 216, 61, 55, 143, 150, 62, 215, 232, 112, 62, 165, 149, 10, 190, 80, 72, 16, 62, 45, 33, 53, 189, 0, 0, 0, 0, 196, 178, 241, 190, 25, 98, 177, 61, 70, 95, 12, 190, 32, 176, 55, 191, 226, 0, 196, 62, 130, 0, 177, 62, 210, 172, 137, 62, 187, 188, 110, 191, 222, 147, 18, 190, 16, 21, 18, 190, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 118, 145, 254, 190, 62, 166, 149, 189, 20, 199, 107, 190, 101, 255, 191, 190, 88, 11, 8, 63, 75, 49, 176, 62, 119, 141, 70, 61, 223, 253, 117, 190, 248, 215, 98, 191, 113, 195, 221, 60, 243, 156, 184, 190, 52, 143, 138, 189, 218, 80, 40, 62, 137, 235, 132, 190, 104, 15, 232, 61, 2, 176, 171, 62, 36, 106, 79, 62, 0, 12, 99, 190, 226, 79, 47, 190, 244, 147, 9, 62, 87, 100, 174, 190, 221, 217, 45, 62, 77, 140, 156, 62, 248, 54, 223, 190, 167, 81, 59, 190, 185, 165, 222, 62, 241, 247, 176, 62, 97, 12, 162, 190, 40, 72, 245, 190, 118, 247, 174, 62, 91, 42, 125, 190, 78, 182, 47, 190, 216, 230, 138, 60, 246, 179, 70, 61, 92, 23, 247, 62, 49, 91, 134, 61, 68, 117, 104, 62, 166, 160, 182, 61, 11, 164, 178, 190, 196, 223, 172, 62, 254, 164, 131, 61, 131, 166, 32, 60, 244, 131, 156, 190, 71, 175, 149, 189, 41, 231, 14, 190, 119, 76, 4, 63, 245, 161, 129, 62, 110, 125, 129, 191, 194, 76, 168, 190, 62, 165, 132, 62, 222, 225, 104, 190, 123, 205, 164, 62, 81, 202, 7, 63, 129, 148, 207, 190, 9, 105, 38, 63, 39, 0, 103, 61, 189, 80, 145, 62, 142, 48, 23, 191, 221, 183, 187, 61, 225, 95, 142, 61, 25, 127, 83, 191, 95, 167, 163, 63, 35, 218, 4, 191, 233, 186, 33, 63, 33, 69, 132, 189, 3, 62, 196, 190, 140, 53, 74, 62, 193, 43, 224, 190, 139, 49, 169, 63, 177, 175, 253, 190, 115, 168, 15, 63, 221, 166, 167, 62, 229, 221, 128, 191, 143, 63, 36, 190, 53, 205, 56, 187, 230, 28, 194, 190, 131, 179, 251, 190, 138, 198, 148, 189, 236, 251, 40, 62, 45, 239, 78, 61, 150, 240, 30, 191, 207, 62, 209, 62, 24, 4, 70, 191, 115, 220, 41, 63, 164, 156, 199, 61, 4, 117, 151, 190, 203, 95, 43, 63, 171, 175, 223, 190, 53, 103, 112, 61, 180, 165, 189, 190, 56, 208, 214, 62, 113, 21, 106, 62, 172, 210, 218, 59, 49, 77, 196, 189, 73, 34, 157, 62, 31, 63, 31, 63, 123, 162, 163, 61, 117, 120, 159, 190, 189, 199, 170, 62, 26, 248, 220, 62, 30, 129, 210, 189, 33, 53, 132, 63, 251, 60, 75, 63, 73, 61, 47, 63, 93, 241, 241, 189, 231, 50, 158, 191, 126, 104, 125, 189, 195, 222, 177, 63, 112, 190, 8, 191, 117, 110, 169, 191, 241, 18, 236, 62, 75, 22, 146, 62, 12, 167, 164, 63, 83, 243, 188, 189, 183, 49, 91, 63, 120, 140, 40, 191, 157, 30, 206, 190, 152, 62, 65, 63, 94, 98, 9, 190, 207, 213, 81, 191, 75, 38, 142, 191, 235, 65, 244, 190, 243, 1, 156, 62, 145, 242, 60, 63, 184, 219, 181, 190, 192, 228, 169, 189, 189, 76, 2, 191, 39, 212, 97, 63, 112, 1, 226, 190, 177, 124, 159, 189, 144, 16, 186, 62, 12, 6, 58, 63, 140, 169, 15, 61, 182, 191, 194, 60, 19, 170, 81, 62, 240, 35, 5, 191, 246, 231, 225, 61, 240, 150, 73, 191, 123, 123, 226, 61, 247, 34, 252, 190, 4, 240, 14, 63, 176, 26, 207, 62, 128, 75, 113, 190, 96, 12, 133, 61, 56, 172, 165, 62, 33, 112, 80, 190, 136, 240, 9, 191, 155, 228, 224, 60, 192, 72, 24, 63, 200, 205, 233, 190, 63, 204, 40, 60, 238, 93, 21, 63, 148, 41, 162, 61, 96, 5, 4, 189, 54, 1, 40, 63, 15, 252, 126, 62, 252, 43, 247, 61, 86, 40, 79, 61, 32, 143, 243, 62, 133, 57, 17, 191, 185, 13, 163, 189, 149, 196, 75, 189, 30, 222, 175, 190, 98, 225, 223, 62, 4, 247, 11, 62, 230, 87, 243, 62, 150, 197, 22, 190, 141, 222, 228, 190, 250, 176, 38, 63, 249, 202, 248, 62, 23, 151, 16, 191, 222, 24, 211, 189, 165, 133, 224, 61, 9, 250, 28, 63, 32, 115, 114, 191, 143, 116, 110, 190, 53, 140, 17, 191, 149, 176, 173, 62, 136, 142, 126, 190, 188, 198, 167, 62, 66, 184, 126, 63, 128, 139, 61, 63, 172, 9, 6, 63, 135, 151, 170, 190, 115, 103, 84, 63, 26, 101, 4, 191, 113, 49, 151, 188, 5, 93, 94, 190, 50, 82, 67, 63, 59, 131, 182, 189, 21, 185, 137, 63, 155, 234, 18, 191, 214, 3, 156, 191, 0, 0, 0, 0, 148, 70, 31, 63, 76, 34, 193, 60, 203, 175, 34, 191, 0, 0, 0, 0, 208, 70, 227, 62, 248, 241, 182, 63, 23, 118, 214, 191, 0, 0, 0, 0, 91, 218, 61, 191, 139, 56, 133, 63, 176, 55, 106, 62, 0, 0, 0, 0, 184, 185, 208, 62, 254, 138, 151, 188, 160, 152, 46, 191, 0, 0, 0, 0, 36, 84, 175, 190, 21, 207, 158, 191, 206, 98, 145, 63, 0, 0, 0, 0, 185, 183, 160, 62, 40, 11, 227, 62, 90, 153, 76, 62, 0, 0, 0, 0, 159, 200, 90, 62, 214, 2, 143, 63, 232, 188, 147, 190, 0, 0, 0, 0, 67, 55, 51, 63, 185, 229, 206, 190, 99, 27, 62, 63, 0, 0, 0, 0, 98, 226, 102, 191, 140, 81, 80, 191, 143, 76, 130, 63, 0, 0, 0, 0, 10, 10, 3, 46, 111, 136, 72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40, 146, 39, 74, 7, 59, 34, 74, 209, 31, 29, 74, 128, 39, 118, 72, 187, 15, 129, 72, 213, 58, 133, 72, 103, 208, 22, 66, 126, 108, 247, 65, 22, 111, 196, 71, 230, 231, 189, 72, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 181, 69, 129, 74, 94, 88, 121, 74, 136, 156, 112, 74, 215, 46, 170, 72, 167, 69, 179, 72, 120, 108, 185, 72, 72, 243, 211, 64, 172, 174, 141, 63, 52, 43, 190, 68, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 145, 1, 254, 0, 2, 1, 5, 48, 117, 100, 0, 44, 1, 112, 23, 151, 7, 132, 3, 197, 0, 92, 4, 144, 1, 64, 1, 64, 1, 144, 1, 48, 117, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 48, 117, 48, 117, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 100, 0, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 100, 0, 100, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 112, 23, 112, 23, 112, 23, 112, 23, 8, 7, 8, 7, 8, 7, 8, 7, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 112, 23, 112, 23, 112, 23, 112, 23, 255, 255, 255, 255, 220, 5, 220, 5, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 220, 5, 220, 5, 220, 5, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 48, 117, 0, 1, 0, 5, 0, 2, 0, 10, 0, 30, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 64, 1, 100, 0, 100, 0, 100, 0, 200, 0, 200, 0, 200, 0, 64, 1, 64, 1, 64, 1, 10, 1, 0, 0, 0, 0, 0, 120, 2, 0, 0 };
// 3. [1943] Acetone, Ethanol, EthylAcetate
//{ 0, 1, 6, 2, 189, 1, 0, 0, 0, 0, 0, 0, 127, 7, 0, 0, 56, 0, 1, 0, 0, 168, 19, 73, 64, 49, 119, 76, 0, 0, 97, 69, 0, 0, 97, 69, 10, 0, 3, 0, 0, 0, 96, 64, 23, 183, 209, 56, 43, 24, 149, 60, 140, 74, 106, 188, 43, 24, 149, 60, 216, 129, 243, 190, 151, 255, 80, 190, 216, 129, 243, 190, 8, 0, 2, 0, 0, 0, 72, 66, 16, 0, 3, 0, 10, 215, 163, 60, 10, 215, 35, 59, 10, 215, 35, 59, 13, 0, 5, 0, 0, 0, 0, 0, 100, 254, 131, 137, 87, 88, 0, 9, 0, 7, 240, 150, 61, 0, 0, 0, 0, 0, 0, 0, 0, 28, 124, 225, 61, 52, 128, 215, 63, 0, 0, 160, 64, 0, 0, 0, 0, 0, 0, 0, 0, 205, 204, 12, 62, 103, 213, 39, 62, 230, 63, 76, 192, 0, 0, 0, 0, 0, 0, 0, 0, 145, 237, 60, 191, 251, 58, 64, 63, 177, 80, 131, 64, 0, 0, 0, 0, 0, 0, 0, 0, 93, 254, 227, 62, 54, 60, 133, 191, 0, 0, 64, 64, 12, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45, 5, 11, 0, 0, 0, 2, 139, 5, 24, 62, 85, 181, 35, 62, 245, 252, 107, 62, 157, 250, 131, 62, 69, 200, 106, 63, 200, 35, 205, 62, 185, 103, 30, 63, 249, 220, 127, 63, 75, 81, 76, 62, 151, 65, 113, 190, 58, 140, 15, 63, 148, 103, 63, 63, 39, 175, 110, 63, 195, 108, 246, 188, 13, 36, 233, 189, 224, 57, 154, 62, 146, 3, 36, 62, 193, 78, 178, 189, 118, 175, 23, 63, 216, 102, 162, 61, 92, 222, 138, 190, 49, 103, 38, 191, 240, 189, 41, 63, 0, 0, 0, 0, 59, 195, 173, 189, 217, 59, 119, 190, 14, 0, 145, 190, 194, 230, 182, 62, 149, 12, 213, 190, 6, 81, 226, 190, 38, 122, 204, 190, 176, 154, 227, 190, 233, 195, 25, 188, 106, 48, 132, 62, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 155, 24, 255, 190, 35, 254, 7, 190, 65, 49, 189, 190, 26, 217, 97, 189, 235, 55, 45, 63, 13, 205, 12, 63, 19, 114, 23, 62, 129, 249, 171, 62, 217, 242, 62, 191, 160, 36, 111, 190, 114, 254, 136, 191, 234, 103, 205, 62, 117, 249, 71, 191, 248, 164, 101, 191, 139, 81, 26, 63, 10, 238, 104, 62, 143, 63, 61, 190, 164, 8, 206, 189, 84, 186, 171, 190, 112, 25, 239, 190, 124, 183, 32, 191, 11, 161, 113, 190, 187, 254, 27, 191, 30, 247, 220, 190, 58, 181, 139, 62, 216, 57, 68, 62, 140, 196, 61, 62, 78, 206, 88, 190, 57, 53, 153, 62, 3, 56, 153, 189, 57, 167, 8, 191, 176, 135, 162, 189, 84, 120, 43, 191, 186, 89, 20, 62, 181, 4, 177, 59, 127, 185, 136, 190, 118, 1, 7, 189, 175, 138, 245, 61, 123, 1, 211, 61, 137, 34, 86, 63, 131, 80, 5, 191, 243, 249, 138, 190, 226, 142, 75, 62, 49, 9, 72, 62, 213, 217, 179, 61, 142, 145, 24, 189, 153, 55, 140, 189, 130, 222, 3, 62, 161, 150, 45, 190, 231, 176, 139, 62, 72, 90, 199, 190, 78, 17, 50, 190, 143, 121, 25, 191, 174, 126, 10, 63, 39, 28, 84, 63, 243, 147, 237, 190, 87, 185, 231, 62, 125, 224, 134, 62, 194, 144, 50, 61, 253, 39, 5, 63, 181, 190, 73, 63, 149, 112, 255, 62, 207, 235, 18, 63, 110, 6, 195, 63, 114, 189, 35, 63, 67, 83, 104, 190, 252, 77, 137, 191, 67, 129, 67, 61, 210, 193, 206, 191, 94, 113, 146, 191, 10, 150, 41, 62, 254, 192, 76, 191, 46, 92, 10, 191, 172, 177, 186, 190, 141, 204, 179, 189, 230, 212, 145, 62, 53, 61, 97, 190, 42, 212, 238, 188, 220, 133, 253, 60, 21, 35, 38, 63, 41, 73, 116, 191, 248, 97, 230, 190, 226, 118, 83, 63, 168, 223, 144, 191, 114, 104, 125, 191, 79, 228, 147, 62, 40, 63, 212, 190, 89, 98, 132, 63, 111, 116, 98, 63, 36, 175, 117, 63, 217, 246, 42, 60, 89, 233, 69, 189, 144, 241, 237, 190, 192, 166, 103, 63, 212, 105, 106, 63, 237, 54, 171, 61, 158, 34, 75, 63, 17, 167, 72, 188, 118, 231, 163, 189, 84, 66, 172, 60, 236, 50, 103, 191, 78, 0, 135, 191, 191, 47, 180, 62, 240, 51, 162, 59, 32, 251, 146, 62, 214, 198, 183, 190, 45, 168, 55, 62, 100, 14, 117, 60, 171, 63, 158, 191, 69, 251, 28, 191, 173, 189, 54, 63, 130, 186, 70, 63, 166, 28, 71, 190, 40, 198, 23, 63, 0, 55, 90, 61, 148, 107, 38, 62, 123, 111, 204, 62, 16, 164, 243, 190, 153, 193, 93, 63, 104, 144, 82, 63, 56, 104, 104, 191, 214, 89, 70, 191, 131, 29, 92, 190, 72, 126, 138, 63, 106, 135, 140, 63, 19, 147, 30, 191, 150, 155, 130, 63, 216, 168, 104, 61, 171, 118, 137, 191, 56, 13, 225, 190, 191, 168, 6, 63, 24, 140, 0, 62, 202, 92, 38, 191, 69, 131, 106, 63, 149, 5, 159, 61, 4, 114, 10, 63, 28, 118, 49, 63, 111, 161, 96, 61, 18, 87, 21, 63, 43, 42, 226, 62, 219, 229, 35, 63, 234, 219, 162, 62, 80, 228, 105, 63, 224, 238, 157, 190, 212, 54, 144, 191, 38, 87, 187, 62, 201, 77, 26, 191, 113, 49, 243, 189, 118, 84, 209, 62, 43, 244, 16, 62, 194, 33, 27, 190, 224, 188, 232, 62, 143, 20, 137, 63, 5, 180, 97, 190, 221, 53, 176, 188, 188, 60, 6, 63, 231, 149, 70, 189, 196, 139, 167, 190, 132, 122, 55, 62, 135, 210, 156, 62, 169, 126, 163, 63, 145, 252, 204, 63, 98, 43, 208, 63, 36, 79, 16, 191, 136, 82, 59, 191, 133, 60, 132, 63, 158, 57, 147, 191, 88, 8, 191, 190, 161, 236, 255, 63, 39, 165, 70, 63, 66, 73, 128, 191, 148, 10, 200, 191, 13, 25, 128, 63, 248, 116, 11, 191, 113, 127, 169, 190, 126, 43, 118, 191, 78, 117, 10, 191, 134, 221, 254, 62, 28, 180, 168, 191, 185, 34, 120, 190, 210, 242, 42, 191, 255, 125, 7, 191, 234, 200, 147, 63, 35, 252, 150, 61, 192, 105, 175, 62, 141, 202, 64, 191, 130, 37, 83, 62, 217, 154, 80, 190, 119, 126, 129, 191, 108, 137, 69, 191, 91, 122, 208, 63, 241, 144, 249, 190, 34, 225, 155, 191, 0, 0, 0, 0, 143, 182, 238, 63, 70, 160, 59, 191, 91, 38, 21, 191, 0, 0, 0, 0, 228, 4, 173, 190, 217, 137, 160, 190, 157, 213, 165, 63, 0, 0, 0, 0, 68, 148, 226, 190, 146, 137, 155, 62, 126, 147, 34, 191, 0, 0, 0, 0, 140, 217, 14, 191, 157, 187, 3, 63, 220, 115, 158, 190, 0, 0, 0, 0, 1, 2, 27, 63, 246, 238, 1, 191, 18, 1, 42, 191, 0, 0, 0, 0, 132, 2, 194, 190, 254, 40, 104, 63, 135, 32, 163, 191, 0, 0, 0, 0, 26, 170, 209, 62, 168, 219, 134, 190, 74, 253, 176, 61, 0, 0, 0, 0, 221, 167, 188, 63, 17, 223, 153, 191, 65, 70, 151, 191, 0, 0, 0, 0, 197, 211, 117, 63, 237, 41, 148, 190, 96, 125, 58, 190, 0, 0, 0, 0, 10, 10, 3, 105, 211, 237, 70, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 146, 17, 220, 71, 142, 122, 214, 71, 3, 195, 209, 71, 163, 141, 210, 70, 168, 144, 220, 70, 57, 167, 228, 70, 61, 189, 54, 66, 28, 207, 249, 65, 151, 51, 194, 71, 244, 149, 159, 70, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 187, 234, 188, 71, 212, 160, 179, 71, 151, 151, 172, 71, 238, 20, 138, 70, 238, 86, 145, 70, 106, 224, 150, 70, 78, 255, 226, 64, 33, 100, 158, 63, 134, 36, 170, 68, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 145, 1, 254, 0, 2, 1, 5, 48, 117, 100, 0, 44, 1, 112, 23, 151, 7, 132, 3, 197, 0, 92, 4, 144, 1, 64, 1, 64, 1, 144, 1, 48, 117, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 48, 117, 48, 117, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 100, 0, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 100, 0, 100, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 112, 23, 112, 23, 112, 23, 112, 23, 8, 7, 8, 7, 8, 7, 8, 7, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 112, 23, 112, 23, 112, 23, 112, 23, 255, 255, 255, 255, 220, 5, 220, 5, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 220, 5, 220, 5, 220, 5, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 48, 117, 0, 1, 0, 5, 0, 2, 0, 10, 0, 30, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 64, 1, 100, 0, 100, 0, 100, 0, 200, 0, 200, 0, 200, 0, 64, 1, 64, 1, 64, 1, 10, 1, 0, 0, 0, 0, 0, 80, 249, 0, 0 };
// 4. [1943] Ambient, Ethanol, Acetone, EthylAcetate
{ 0, 1, 6, 2, 189, 1, 0, 0, 0, 0, 0, 0, 127, 7, 0, 0, 56, 0, 1, 0, 0, 168, 19, 73, 64, 49, 119, 76, 0, 0, 97, 69, 0, 0, 97, 69, 10, 0, 3, 0, 0, 0, 96, 64, 23, 183, 209, 56, 43, 24, 149, 60, 140, 74, 106, 188, 43, 24, 149, 60, 216, 129, 243, 190, 151, 255, 80, 190, 216, 129, 243, 190, 8, 0, 2, 0, 0, 0, 72, 66, 16, 0, 3, 0, 10, 215, 163, 60, 10, 215, 35, 59, 10, 215, 35, 59, 13, 0, 5, 0, 0, 0, 0, 0, 100, 254, 131, 137, 87, 88, 0, 9, 0, 7, 240, 150, 61, 0, 0, 0, 0, 0, 0, 0, 0, 28, 124, 225, 61, 52, 128, 215, 63, 0, 0, 160, 64, 0, 0, 0, 0, 0, 0, 0, 0, 205, 204, 12, 62, 103, 213, 39, 62, 230, 63, 76, 192, 0, 0, 0, 0, 0, 0, 0, 0, 145, 237, 60, 191, 251, 58, 64, 63, 177, 80, 131, 64, 0, 0, 0, 0, 0, 0, 0, 0, 93, 254, 227, 62, 54, 60, 133, 191, 0, 0, 64, 64, 12, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45, 5, 11, 0, 0, 0, 2, 17, 87, 230, 62, 10, 71, 49, 62, 30, 227, 48, 63, 129, 5, 105, 62, 69, 230, 147, 63, 41, 24, 134, 63, 102, 65, 168, 62, 145, 223, 29, 189, 146, 252, 185, 189, 237, 91, 34, 63, 47, 82, 37, 62, 227, 158, 230, 189, 117, 168, 215, 190, 14, 220, 231, 61, 87, 188, 194, 188, 7, 182, 114, 188, 190, 49, 13, 63, 145, 182, 153, 189, 56, 76, 145, 189, 149, 209, 57, 62, 12, 195, 212, 190, 25, 70, 236, 62, 6, 13, 167, 62, 221, 150, 79, 191, 145, 239, 132, 191, 227, 104, 88, 187, 85, 62, 63, 191, 129, 126, 77, 190, 129, 13, 59, 190, 61, 205, 179, 190, 154, 207, 132, 190, 33, 85, 109, 62, 143, 246, 180, 190, 224, 195, 46, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 149, 2, 189, 127, 187, 253, 62, 12, 59, 114, 191, 252, 248, 18, 191, 10, 198, 188, 188, 197, 194, 197, 190, 193, 187, 17, 191, 149, 220, 24, 62, 183, 249, 93, 190, 123, 22, 160, 190, 236, 205, 224, 190, 8, 251, 59, 189, 211, 24, 159, 191, 150, 96, 212, 190, 125, 100, 36, 60, 35, 41, 128, 190, 253, 216, 193, 59, 120, 98, 188, 190, 226, 94, 144, 190, 109, 169, 107, 62, 163, 68, 113, 191, 18, 99, 129, 61, 93, 10, 115, 191, 121, 251, 10, 191, 168, 240, 10, 191, 101, 217, 106, 60, 30, 193, 9, 191, 174, 129, 129, 62, 12, 184, 45, 62, 143, 240, 135, 190, 109, 152, 40, 191, 11, 191, 28, 63, 134, 115, 63, 191, 31, 150, 212, 61, 112, 254, 130, 190, 229, 144, 184, 62, 220, 154, 82, 191, 188, 120, 104, 186, 42, 227, 201, 61, 52, 1, 1, 63, 252, 213, 58, 191, 63, 108, 144, 61, 231, 213, 137, 191, 28, 22, 229, 190, 52, 17, 252, 61, 79, 133, 27, 190, 204, 34, 120, 191, 105, 130, 180, 60, 192, 233, 119, 191, 166, 69, 119, 63, 210, 45, 216, 190, 136, 254, 213, 62, 59, 107, 174, 191, 111, 109, 168, 60, 240, 75, 27, 63, 239, 27, 12, 61, 218, 235, 108, 191, 3, 6, 236, 189, 99, 227, 57, 190, 228, 166, 202, 61, 47, 74, 145, 191, 5, 154, 9, 192, 88, 135, 5, 63, 36, 87, 81, 190, 50, 177, 184, 191, 87, 185, 131, 63, 40, 115, 153, 63, 169, 79, 155, 63, 3, 163, 108, 63, 143, 51, 21, 61, 76, 49, 5, 191, 228, 119, 25, 63, 236, 186, 47, 63, 1, 194, 147, 62, 129, 75, 155, 62, 47, 240, 153, 191, 111, 65, 101, 188, 95, 135, 147, 191, 142, 211, 48, 63, 131, 3, 230, 190, 243, 217, 2, 63, 198, 120, 187, 62, 169, 220, 132, 191, 23, 111, 138, 63, 183, 142, 244, 62, 77, 151, 151, 63, 234, 9, 135, 191, 149, 96, 2, 191, 217, 254, 50, 62, 19, 51, 221, 191, 8, 17, 144, 61, 58, 134, 130, 190, 74, 5, 19, 192, 223, 39, 125, 191, 20, 111, 126, 190, 108, 85, 213, 191, 242, 203, 184, 189, 238, 243, 67, 190, 231, 81, 202, 190, 223, 136, 56, 63, 58, 94, 135, 63, 235, 105, 171, 62, 212, 83, 152, 62, 132, 53, 25, 64, 85, 162, 92, 190, 52, 31, 120, 190, 15, 36, 190, 191, 168, 136, 77, 62, 15, 43, 25, 63, 79, 193, 66, 63, 86, 199, 107, 191, 137, 15, 74, 189, 8, 78, 28, 63, 233, 167, 113, 62, 28, 159, 22, 188, 104, 137, 57, 63, 253, 99, 11, 63, 198, 69, 218, 190, 253, 144, 21, 190, 172, 119, 50, 63, 158, 189, 114, 63, 122, 208, 65, 62, 139, 56, 217, 190, 215, 121, 217, 190, 232, 101, 193, 190, 218, 72, 12, 190, 184, 31, 186, 190, 94, 54, 239, 62, 17, 13, 35, 190, 183, 207, 95, 63, 57, 241, 139, 62, 216, 238, 239, 189, 36, 227, 99, 191, 80, 104, 140, 62, 64, 122, 155, 189, 88, 152, 5, 191, 148, 132, 200, 62, 34, 152, 254, 190, 73, 8, 183, 190, 174, 182, 139, 63, 36, 94, 35, 63, 24, 217, 186, 190, 173, 116, 45, 63, 27, 120, 36, 62, 205, 166, 178, 190, 156, 249, 92, 62, 187, 89, 236, 63, 35, 101, 190, 190, 108, 242, 252, 62, 69, 10, 86, 191, 104, 242, 138, 191, 130, 86, 204, 190, 68, 145, 234, 62, 119, 242, 171, 190, 241, 83, 38, 190, 20, 92, 137, 63, 9, 65, 21, 63, 58, 129, 252, 190, 209, 161, 212, 188, 250, 168, 162, 190, 179, 166, 23, 62, 98, 138, 71, 191, 127, 215, 54, 63, 180, 3, 215, 63, 217, 205, 3, 62, 245, 35, 38, 63, 12, 160, 73, 191, 87, 225, 120, 190, 185, 215, 70, 62, 201, 209, 187, 189, 218, 131, 29, 190, 42, 37, 228, 61, 41, 91, 68, 189, 246, 136, 213, 190, 139, 156, 147, 62, 93, 25, 80, 63, 170, 250, 229, 190, 39, 6, 172, 62, 63, 10, 12, 62, 66, 223, 217, 62, 165, 236, 115, 62, 53, 136, 180, 190, 214, 11, 144, 62, 57, 33, 16, 62, 169, 154, 7, 189, 175, 108, 61, 190, 74, 85, 45, 64, 71, 229, 101, 190, 190, 133, 240, 62, 70, 157, 106, 190, 253, 208, 94, 62, 210, 232, 248, 63, 97, 135, 3, 192, 5, 161, 139, 191, 15, 102, 27, 190, 192, 191, 123, 62, 15, 76, 1, 190, 94, 17, 7, 63, 201, 30, 8, 192, 206, 25, 92, 191, 159, 62, 131, 190, 40, 215, 37, 63, 193, 14, 134, 63, 11, 225, 211, 191, 173, 75, 106, 191, 203, 31, 206, 63, 167, 63, 221, 62, 81, 65, 133, 62, 73, 254, 143, 62, 11, 104, 41, 63, 183, 115, 26, 63, 93, 125, 189, 190, 240, 194, 46, 192, 118, 50, 77, 63, 127, 20, 96, 191, 127, 192, 140, 63, 23, 107, 79, 191, 171, 116, 246, 190, 49, 195, 237, 190, 250, 81, 187, 190, 18, 59, 204, 62, 47, 196, 11, 190, 43, 178, 73, 63, 207, 26, 45, 191, 164, 184, 109, 61, 185, 97, 240, 190, 132, 10, 132, 62, 48, 73, 149, 190, 214, 241, 189, 63, 165, 46, 92, 191, 10, 10, 4, 125, 142, 236, 71, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 176, 165, 121, 73, 38, 141, 114, 73, 171, 9, 108, 73, 165, 191, 213, 71, 8, 139, 223, 71, 154, 225, 230, 71, 170, 109, 44, 66, 75, 95, 248, 65, 204, 0, 195, 71, 180, 103, 76, 72, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 208, 78, 0, 74, 207, 175, 248, 73, 98, 119, 241, 73, 157, 8, 57, 72, 246, 231, 65, 72, 184, 61, 72, 72, 35, 102, 5, 65, 8, 95, 167, 63, 146, 98, 200, 68, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 145, 1, 254, 0, 2, 1, 5, 48, 117, 100, 0, 44, 1, 112, 23, 151, 7, 132, 3, 197, 0, 92, 4, 144, 1, 64, 1, 64, 1, 144, 1, 48, 117, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 48, 117, 48, 117, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 100, 0, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 48, 117, 100, 0, 100, 0, 100, 0, 48, 117, 48, 117, 100, 0, 100, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 44, 1, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 112, 23, 112, 23, 112, 23, 112, 23, 8, 7, 8, 7, 8, 7, 8, 7, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 112, 23, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 112, 23, 112, 23, 112, 23, 112, 23, 255, 255, 255, 255, 220, 5, 220, 5, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 220, 5, 220, 5, 220, 5, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 48, 117, 0, 1, 0, 5, 0, 2, 0, 10, 0, 30, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 64, 1, 100, 0, 100, 0, 100, 0, 200, 0, 200, 0, 200, 0, 64, 1, 64, 1, 64, 1, 10, 1, 0, 0, 0, 0, 0, 15, 16, 0, 0 };

uint8_t bsec2Data[5];

  
void setup() {
  Serial.begin(115200);  //
  BHY2.begin();          //
  sensortec.bhy2_bsec2_setConfigString(BSEC2CONFIG, sizeof(BSEC2CONFIG) / sizeof(BSEC2CONFIG[0]));
  bsec2.begin();                 //
  Wire.begin(2);                 // join i2c bus (address optional for master)
  Wire.onRequest(requestEvent);  // register event
}

void loop() {
  BHY2.update();
  static auto printTime = millis();
  if (millis() - printTime >= 1000) {
    printTime = millis();
    Serial.println(bsec2.toString());
    bsec2Data[0] = bsec2.gas_estimates0();
    bsec2Data[1] = bsec2.gas_estimates1();
    bsec2Data[2] = bsec2.gas_estimates2();
    bsec2Data[3] = bsec2.gas_estimates3();
    bsec2Data[4] = bsec2.accuracy();
  }
}

void requestEvent() {
  Serial.println("I²C request received. Sending data...");
  for (int i = 0; i < 5; i++) {
    Serial.print("bsec2Data[");
    Serial.print(i);
    Serial.print("]: ");
    Serial.println(bsec2Data[i]);
  }

  Wire.write(bsec2Data, sizeof(bsec2Data));  // Send all 5 bytes
}
