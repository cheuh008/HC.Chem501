# Project: Smoking The Nicla

#### Brief: Training a ML Algorithm to identify a range of solvents using the BME688 sensor from Bosch onboard the Nicla Sense Me

The project/directory can be broken down into 3 main categories with the method further breaking down into step by step but TL:DR; 
1. Data Acquisition --> Arduino Code
    - Use Arduino IDE 2 to collect the gas data and PuTTy to log 
2. ML Training --> BME_AI_Data
    - Use [BME AI Studio](https://www.bosch-sensortec.com/software-tools/software/bme688-software/)
to train a custom solvent config. Or use the preconfigured data string in Arduino Code 
3. Data Processing and visualisation
   - Use Python to download data from your own thingSpeak Channel, or use cleaned data from `thingspeak_data.db` to create plots using given data
  
![WorkFlowDiagram](Workflow.png) 

---
## Method: 
By PiggyBacking the ML model onboard the Nicla, a custom algorithm can be made and used to identify solvents. The result is then collated on a server and processed by Python via an API
1. **Data Collection**: Gas data can be collected via an example Arduino code within the BHY2 Library
2. **Data Logging**:Gas Data is logged and Saved By PuTTY
3. **Data Processing**:A pre-written Python script processes data to a format usable by BME_AI_Studio
4. **ML Training**:Data is used to train a ML Algorithm and exported as a BSEC2 Config Array
5. **Gas Classification**: the configured array is uploaded back onto Nicla Sense ME to be used to classify different Solvents
6. **Data Storage**: That data is uploaded to a ThingSpeak channel, which enables remote logging, deployment and Analysis
7. **Data Analysis**: The Python script then enables the data to be pulled remotely from the ThingSpeak Channel for data analysis and visualisation

---

## Table of Contents
- [Background](#background)
- [File Tree Structure](#fil-tree-structure)
- [Project Setup, Installation, and Use](#project-setup-installation-and-use)
  - [Hardware Requirements](#hardware-requirements)
  - [Software Setup](#software-setup)
    - [Arduino Environment](#arduino-environment)
    - [BME AI Studio (& PuTTY)](#bme-ai-studio--putty)
    - [Python Environment](#python-environment)
- [Further Reading](#further-reading)

---

## Backgorund

The Nicla project, code-named **Smoking the Nicla**, integrates Arduino-based hardware, Python software, and BME (Bosch Measurement Engineering) configurations to monitor, classify, and analyse environmental data, with a focus on gas and vapour detection. It leverages the **Nicla Sense ME** board, equipped with the **BME688 gas sensor** and Bosch's **AI Studio**, to identify specific solvent vapours and particulate matter in applications like laboratory fume hood monitoring.
**Project Origin**: It began as an idea to detect smoke particulate detectors and was later adapted for lab fume hood applications. **Sensor Exploration**: Focused on the capabilities of the **BME688 sensor** and Bosch's **BSEC2 gas scanner**.

---

## File Tree Structure
- "Most" folders have a ReadMe.md for extended documentation as needed
- Data logs have been included in the repo for reproducibility
- 
``` bash
H.C.Chem501
├── Arduino Code
│   ├── Consolidated
│   │   ├── Smoke_MKR
│   │   │   └── ...
│   │   └── Smoke_Nicla
│   │       └── ...
│   └── Modules
│       ├── BackUpVOC_MKR
│       ├── BackUpVOC_NiclaAppLowDelay
│       ├── MKR_Master_to_ThingSpeak
│       ├── Nicla_BSEC2_Classifier_Slave_Sender
│       └── Nicla_Gas_Collector
├── BME_AI_Data
│   ├── BSEC2DataLogConverter.py
│   ├── DataLogs
│   │   ├── 1.1Ambient_Everton_30min.log
│   │   ├── ...
│   │   └── 4.3.2Ethanol-60ml.log
│   ├── Nicla_BME2.bmeproject
│   │   ├── algorithms
│   │   └── ...
│   ├── Nicla_BME2V2.bmeproject
│   │   ├── algorithms
│   │   └── ...
│   ├── NiclaBME_HP-354.bmeconfig
│   └── Specimen
│       ├── acetic_acid_4_3.bmespecimen
│       ├── acetone_4_9.bmespecimen
│       ├── ambient_4.bmespecimen
│       ├── ethanol_4_1_5.bmespecimen
│       ├──...
│       └── ethyl_acetate_2.bmespecimen
├── Python
│   ├── channel_1_data.csv
│   ├── channel_2_data.csv
│   ├── config.py
│   ├── dbHandler.py
│   ├── keys.json
│   ├── main.py
│   ├── plots
│   │   └── ... .png
│   ├── plotting.py
│   ├── requirements.txt
│   └── thingspeak_data.db
└── README.md
```
---

# Project Setup, installation and Use (Recommended)
The following layout describes how the recommended environment was set up, but you can modify it as needed. Refer to documentation and libraries for additional support.

### **Hardware Requirements**

- [Nicla Sense ME](https://store.managersc,/products/nicla-sense-me) *(Includes ESLOV cable)*
- [Arduino MKR WiFi 1010](https://store.arduino.cc/products/arduino-mkr-wifi-1010)
- **Power and Data Micro USB Cable**
- *(Optional)* **Portable Power Supply**
- *(Recommended)* **Portable Wi-Fi Source**

### Software Setup

Clone this repository into your working directory:
```bash
git clone https://github.com/cheuh008/HC.Chem501
```

#### Arduino Environment
1. **Install Arduino IDE**:  
   Download the latest Arduino IDE from [here](https://www.arduino.cc/en/software).  
   Also, you can use VS Code with the Arduino extension.

2. **Required Boards and Libraries**:  
   Install the following via the **Board Manager** and **Library Manager**:
   - **Boards**:
     - Nicla (Mbed OS Nicla Boards)
     - MKR SAMD Boards
   - **Libraries**:
     - `Arduino_BHY2`
     - `Arduino_BLE`
     - `Arduino_BHY2Host`
     - `RTCZero`
     - `WiFiNINA`
     - `ThingSpeak`

3. **Configure `secrets.h`**:  
   Create a `secrets.h` file in your Arduino project. Copy the template from `secrets_template.h` and fill in your Wi-Fi credentials and ThingSpeak API keys:
   ```cpp
   #define SECRET_SSID "YourWiFiSSID"
   #define SECRET_PASS "YourWiFiPassword"
   #define SECRET_API_KEY "YourThingSpeakAPIKey"
   ```

4. **Upload Code**:  
   - Run `Smoke_Nicla.ino` in **Mode = 2** or `Nicla_Gas_Collector.ino` to collect gas data.
   - To collate gas data from serial, refer to the **BME AI Studio (& PuTTY)** section below.
   - and the following youtube video for experimental setup
  
   [![How gas sensing gets intelligent with BME688 and BME AI-Studio](https://img.youtube.com/vi/4vdliMRtxBY/0.jpg)](https://www.youtube.com/watch?v=4vdliMRtxBY)


#### BME AI Studio (& PuTTY)
1. **Download Tools**:
   - [BME AI Studio](https://www.bosch-sensortec.com/software-tools/software/bme688-software/)
   - [PuTTY](https://www.putty.org/)

2. **Set Up AI Studio**:
   - Create a new project in BME AI Studio.
   - Create and save a heating profile (e.g., `HP-354`).

3. **Organise Logs**:  
   - Move log files into a dedicated directory for easier management.
   - Copy `BSEC2DataLogConverter.py` from the `tools` folder in the BHY2 library to your log directory.

4. **Run Data Conversion**:
   Use the Python script to process logs into raw data files for AI Studio:
   ```bash
   python BSEC2DataLogConverter.py ./datalogs/3.1.1Ambient30mins.log 0 ./NiclaBME_HP-354.bmeconfig
   python BSEC2DataLogConverter.py ./datalogs/4.3.2Ethanol-60ml.log 1 ./NiclaBME_HP-354.bmeconfig
   ```

5. **Import Data**:
   - Import the generated `_gas_x_{name}.bmerawdata` files separately for class classification
   - Create and train a new algorithm with the imported data.
   - Select the `Algorithm Settings` of your choice, ie: `Gas Data Channel, Apply Clipping Prevention`
   - Export as `BSEC Config File`

   
6 **Gas Classification**:
   - from the exported `BSEC Config File`, find the `.c` file: `dateTime_name_HP-354_RCS-1-0Continous.c`
   - take note of the number on bits inside the square brackets `[...]` as sometimes is needed if data is all 0s
   - replace the existing demo array in const uint8_5 BSECCONFIG[] = {...}; within the BHY2>example>BSEC2GasClassifier, or the `BSECCONFIG.h` file inside Nicla_Smoke
   - Upload the new code to the Nicla and test its efficacy on gas C


#### Python Environment
Python is used for data analysis and visualisation. The following steps assume you are using Python 3.12 with a virtual environment:

1. **Install Dependencies**:
   ```bash
   cd Python
   pip install -r requirements.txt
   ```

2. **Add API Keys**:  
   Create a `keys.json` file in the `Python` directory and ensure it is listed in `.gitignore`:
   ```json
   {
       "api_keys": {
           "channel_1": "YourChannel1APIKey",
           "channel_2": "YourChannel2APIKey"
       }
   }
   ```

3. **Configure ThingSpeak Channels**:
   - Edit `config.py` to customise channel details as needed.

---

### Further Reading
- [BME688 Sensor Overview](https://www.bosch-sensortec.com/products/environmental-sensors/gas-sensors/bme688/)
- [BME688 Datasheet](https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bme688-ds000.pdf)
- [Bosch AI Studio](https://www.bosch-sensortec.com/media/boschsensortec/downloads/application_notes_1/bst-bme688-an001.pdf)
- [How gas sensing gets intelligent with BME688](https://www.youtube.com/watch?v=dO7DRoLsDNM)
- [BSEC2 Gas Scanner Classify Example](https://github.com/arduino-libraries/Arduino_BHY2/blob/main/examples/BSEC2GasScannerClassify/BSEC2GasScannerClassify.ino)
- [BSEC2 Gas Scanner Collect Data Example](https://github.com/arduino-libraries/Arduino_BHY2/blob/main/examples/BSEC2GasScannerCollectData/BSEC2GasScannerCollectData.ino)
- [Hackster Project: BME AI Studio with Nicla Sense ME](https://www.hackster.io/lucasguocn/use-bme-ai-studio-with-bme688-on-the-nicla-sense-me-board-5f1b55)
- [Bosch Forum Discussion](https://community.bosch-sensortec.com/mems-sensors-forum-jrmujtaw/post/bme-ai-studio-config-on-arduino-nicla-TPCJdSxmesNaGIM)


### Notes

The model generated by BME_AI_Studio is a  neural network model created using TensorFlow.js
The model is based on a sequential feed-forward neural network (FNN) with 3 layers; Input, Hidden and Output, Each with 10 nodes (Neuron) 



