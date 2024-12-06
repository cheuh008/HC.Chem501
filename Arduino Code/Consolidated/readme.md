# WORK IN PROGRESS....

In an effort to reduce the abundant amount of files/Folders in the Arduino Code Folder, 
This App attempts to consolidate all of the different codes needed into 1 appusing serial input tp switch between use cases and or designing the code to dynamically adapt to different modes


idea to consolidate data acquisition, retrieval and remote broadcast
 - a slight hick... Thingspeak might be too slow to collect enough data. it might **HAVE** to be plugged into a PC...

 - UNLESS MQTT can handle +/- 1 request per second (MQTT?)


# Consolidated

The `Consolidated` folder contains the integrated and optimised Arduino sketches for the HC.Chem501 project. This codebase is designed to replace individual modules by combining their functionality into unified sketches. The consolidated code aims to improve efficiency, reduce redundancy, and simplify deployment.

## Purpose
The consolidated codebase serves as:
1. A **unified solution** that integrates features from individual modules.
2. A **centralised system** to handle data collection, processing, and communication across devices.
3. A **future-ready** implementation that streamlines updates and scalability.

---

## Folder Structure and Descriptions

### `Smoke_MKR`
- **Description**: The MKR-based sketch for collecting and transmitting smoke-related data to ThingSpeak.
- **Files**:
  - `Smoke_MKR.ino`: Main sketch for handling sensor data, Wi-Fi connectivity, and ThingSpeak updates.
  - `secrets_template.h`: Placeholder for sensitive information (e.g., Wi-Fi credentials, API keys).
  - `README.md`: Documentation specific to this sketch.

### `Smoke_Nicla`
- **Description**: The Nicla Sense-based sketch for advanced smoke and gas data classification and collection.
- **Files**:
  - `Smoke_Nicla.ino`: Main sketch handling BSEC2 gas classification and data collection.
  - `BSEC2CONFIG.h`: Configuration for Bosch BSEC2 gas classification.
  - `CONFIG_BSEC2_HP.h`: High-precision heater configuration for BME688 sensors.
  - `README.md`: Documentation specific to this sketch.

---

## Features and Functionality

### Key Features
1. **Modular Modes**: 
   - **Mode 0**: Standalone for independent operations.
   - **Mode 1**: Classification mode using Bosch BSEC2 for gas estimates.
   - **Mode 2**: Data collection mode for AI Studio training.

2. **I²C Communication**:
   - Seamless master-slave communication using the I²C protocol.

3. **Cloud Integration**:
   - Data logging and visualisation through ThingSpeak.

4. **Dynamic Sensor Control**:
   - Sensors are activated or deactivated based on the selected mode, optimising resource usage.

5. **Real-Time Clock (RTC)**:
   - Time synchronisation using NTP via Wi-Fi.

---

## Usage Instructions

### Setup
1. Replace the placeholders in `secrets_template.h` with your actual credentials (e.g., Wi-Fi SSID, password, ThingSpeak API keys).
2. Select the appropriate sketch for your hardware:
   - Use `Smoke_MKR.ino` for MKR-based systems.
   - Use `Smoke_Nicla.ino` for Nicla Sense boards.

### Compilation and Upload
1. Open the sketch in the Arduino IDE.
2. Verify and upload it to the respective board.

### Mode Selection
- **Default Mode**: The sketch starts in Mode 1 (Classification).
- **Change Mode**:
  - Open the Serial Monitor in the Arduino IDE.
  - Send a number (`0`, `1`, or `2`) to switch between modes.

### Data Logging
- Sensor data is logged and transmitted to ThingSpeak.
- For Mode 2, data can be exported for AI training in Bosch Sensortec's AI Studio.

---

## Dependencies
- **Libraries**:
  - `Wire`: For I²C communication.
  - `WiFiNINA`: For Wi-Fi connectivity.
  - `RTCZero`: For real-time clock operations.
  - `ThingSpeak`: For cloud data logging.
  - `Arduino_BHY2Host`: For managing Bosch BSEC2 sensors.

- **Hardware**:
  - MKR boards with Wi-Fi support.
  - Nicla Sense ME board with BME688 sensor.

---

## Future Plans
- Further optimisation to enhance performance and reduce memory usage.
- Integration of additional sensors and features.
- Improvements to the AI training pipeline.

---

## Support
For detailed documentation and project updates, refer to the main repository:
[HC.Chem501 GitHub Repository](https://github.com/cheuh008/HC.Chem501)
