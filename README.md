# BSEC Sensor Data Logging to ThingSpeak

University of Liverpool MSC Digital Chemistry Project

- Harry

## Project Overview

This project involves collecting environmental sensor data from the Bosch Sensortec Environmental Cluster (BSEC) BME688 using an Arduino MKR WiFi 1010 board. The data is logged to ThingSpeak, an IoT analytics platform, every 30 seconds. Additionally, the project leverages the internal RTC (Real-Time Clock) on the MKR WiFi 1010 to timestamp the data.

## Hardware Requirements

- Arduino MKR WiFi 1010
- Arduino Nicla Sense Me
- Internet connection

## Software Requirements

- Arduino IDE
- Libraries:
  - `Arduino_BHY2`
  - `Arduino_BHY2Host`
  - `ThingSpeak`
  - `WiFiNINA`
  - `RTCZero`


## Setup Instructions

1. **Connect the Hardware:**

   - Connect the Nicla Sense Me to the MKR WiFi 1010 board Via Eslov (or I2C should work too)
     
2. **Install Required Libraries:**

   - Open the Arduino IDE.
   - Go to **Sketch** > **Include Library** > **Manage Libraries**.
   - Search for and install the following libraries:
      - `Arduino_BHY2`
      - `Arduino_BHY2Host`
      - `ThingSpeak`
      - `WiFiNINA`
      - `RTCZero`

3. **Configure ThingSpeak:**

   - Create an account on [ThingSpeak](https://www.thingspeak.com).
   - Create deseried no. of channels (up to 4) and note down the Channel IDs and Write API Keys.

4. **Setup WiFi Credentials:**
   - Create a `secrets.h` file with your network SSID and password, ThingSpeak Channel ID, and Write API Key.
   ```cpp
   #define SECRET_SSID "your_SSID"
   #define SECRET_PASS "your_PASSWORD"
   #define SECRET_CH_ID your_ChannelID
   #define SECRET_W_APIKEY "your_APIKey"
   ```
