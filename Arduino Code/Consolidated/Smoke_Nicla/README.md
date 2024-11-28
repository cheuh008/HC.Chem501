# Nicla BME688 Data Collection & Classification

## Overview

This Arduino application enables dynamic mode selection for the Nicla Sense ME with a BME688 sensor. Users can choose between three modes via serial input:

- **Mode 0:** Standalone Peripheral with BHY2Host to act as sensor.
- **Mode 1:** Classification using `BSEC2CONFIG.h` for gas estimation. Data Sent over ESLOV.
- **Mode 2:** Data collection for AI Studio training, Also send over ESLOV.
  - `CONFIG_BSEC2_HP.h` file allows user to define and select different heating profile if desired
  - However For demo use case. Only the default HP_354 will be used

---

## Key Features

### 1. **Dynamic Mode Selection**

- Users can input the desired mode via the serial monitor (0, 1, or 2).
- The application reconfigures sensors based on the selected mode without requiring a restart/code recompile/upload

### 2. **Custom Machine Learning**

- `BSEC2CONFIG.h` allows users to define and load different machine learning configurations for gas classification in Mode 1.

### 3. **As needed GasDataCollector**

- Mode 2 allows user to select GasCollector mode, data is sent via ESLOV to server and can be downaloaded as .log

### 4. **I2C Communication**

- Outputs sensor data over I2C, formatted dynamically based on the active mode.

---

## Usage

### 1. **Mode Selection**

- Open the serial monitor at 9600 baud.
- Input `0`, `1`, or `2` to select the desired mode.

### 2. **Custom ML Configuration**

- Edit the `BSEC2CONFIG.h` file to include machine learning algorithms for specific gas classifications.
- Upload the sketch to apply new configurations.

### 3. **Data Transmission**

- Sensor data is sent over ESLOV(I2C) to MKR WIFI 1010 to wirelessly send to server.

---

## Files

- **`BSEC2CONFIG.h`**: ML configurations for gas classification (Mode 1).
- **`CONFIG_BSEC2_HP.h`**: High-performance configurations for data collection (Mode 2).
- **`Smoke_Nicla.ino`**: Main application sketch.

---

## Pending Update:

- Mode Selection for alogrithm as well as MODES.
