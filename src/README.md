# BSEC Sensor Data Logging to ThingSpeak - Source Code

## Overview
This source code is designed to collect environmental sensor data from the Nicla Sense ME using an Arduino MKR WiFi 1010 board, and log the data to ThingSpeak every 30 seconds. The code utilizes the internal RTC of the MKR WiFi 1010, synchronizing with an NTP server to timestamp the data.
For more detail visit: (https://github.com/cheuh008/HC.Chem501)
## Functionality
- **WiFi Connectivity**: Connects to WiFi using credentials provided in `secrets.h`.
- **RTC Initialization**: Sets up the real-time clock and synchronizes with an NTP server.
- **Sensor Data Collection**: Reads data from the Nicla Sense ME connected over ESLOV.
- **ThingSpeak Integration**: Uploads sensor data to ThingSpeak with a timestamp.

## Requirements
- Arduino MKR WiFi 1010
- Nicla Sense ME (connected over ESLOV)
- Internet connection (optional, for NTP synchronization)
- Arduino IDE with the following libraries:
  - `WiFiNINA`
  - `RTCZero`
  - `ThingSpeak`
  - `Arduino_BHY2Host`

## Setup Instructions
1. **Hardware Connection**:
   - Connect the Nicla Sense ME to the MKR WiFi 1010 using ESLOV.

2. **Library Installation**:
   - Install the required libraries via the Arduino IDE Library Manager.

3. **Configure `secrets.h`**:
   - Provide your WiFi SSID, password, ThingSpeak Channel ID, and API Key in the `secrets.h` file.
   ```cpp
   #define SECRET_SSID "your_SSID"
   #define SECRET_PASS "your_PASSWORD"
   #define SECRET_CH_ID your_ChannelID
   #define SECRET_W_APIKEY "your_APIKey"
   ```cpp
   
## License
See [LICENSE.txt](LICENSE.txt)
   
