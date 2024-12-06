# Modules

This folder contains individual Arduino sketches that serve as the backbone of the HC.Chem501 project. Each module in this directory is designed to address specific functionalities of the project. These scripts are tested and functional as standalone backups. However, with the ongoing development of a consolidated codebase, these modules may soon be deprecated if the integrated version proves stable and operational.

## Purpose
The `Modules` folder acts as:
1. A **backup** for tested and verified code snippets.
2. A **modular reference** for understanding individual components of the project.
3. A **fallback option** in case the consolidated code does not meet performance or stability requirements.

---

## Folder Structure and Descriptions

### `BackUpVOC_MKR`
- **Description**: A backup module for managing VOC data using an MKR board.
- **Files**:
  - `BackUpVOC_MKR.ino`: Main sketch for VOC data collection and processing.
  - `secrets_template.h`: Template for sensitive information like Wi-Fi credentials and ThingSpeak API keys.
  - `README.md`: Documentation specific to this module.

### `BackUpVOC_NiclaAppLowDelay`
- **Description**: Handles VOC data collection with reduced delay, specifically designed for the Nicla Sense board.
- **Files**:
  - `BackUpVOC_NiclaAppLowDelay.ino`: Main sketch for low-latency VOC data handling.

### `MKR_Master_to_ThingSpeak`
- **Description**: Sends sensor data from the MKR board to ThingSpeak.
- **Files**:
  - `MKR_Master_to_ThingSpeak.ino`: Main sketch for handling MKR data transmission to ThingSpeak.
  - `secrets_template.h`: Template for storing Wi-Fi and API credentials.
  - `README.md`: Documentation specific to this module.

### `Nicla_BSEC2_Classifier_Slave_Sender`
- **Description**: A module for collecting and sending gas classification data from the Nicla Sense board.
- **Files**:
  - `Nicla_BSEC2_Classifier_Slave_Sender.ino`: Main sketch for classification and data transmission.

### `Nicla_Gas_Collector`
- **Description**: Focuses on collecting raw gas data using the Nicla Sense board for processing and analysis.
- **Files**:
  - `Nicla_Gas_Collector.ino`: Main sketch for gas data collection.

---

## General Notes
- **Dependencies**: Each module may depend on external libraries like:
  - `WiFiNINA` for Wi-Fi connectivity.
  - `RTCZero` for real-time clock operations.
  - `ThingSpeak` for cloud data logging.
  - `Arduino_BHY2Host` and `SensorBSEC` for Bosch sensor management.

- **Sensitive Information**:
  - The `secrets_template.h` files in some modules act as placeholders for sensitive details such as Wi-Fi SSID, passwords, and ThingSpeak API keys. Replace these placeholders with actual credentials before deployment.

- **Future Plans**:
  - These modules may become redundant as a **consolidated codebase** is developed. For now, they remain a reliable fallback.

---

## Usage Instructions
1. Choose the appropriate module for your needs.
2. Replace placeholders in `secrets_template.h` with your actual credentials.
3. Compile and upload the `.ino` file to the respective board using the Arduino IDE.
4. Verify functionality and data flow to ensure the module performs as expected.

---

## Support
For detailed documentation and project updates, refer to the main repository:
[HC.Chem501 GitHub Repository](https://github.com/cheuh008/HC.Chem501)
