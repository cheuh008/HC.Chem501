# Project Overview: Smoking The Nicla

 ## Overview

The Nicla project, code-named **Smoking the Nicla**, integrates Arduino-based hardware, Python software, and BME (Bosch Measurement Engineering) configurations to monitor, classify, and analyse environmental data, with a focus on gas and vapour detection. It leverages the **Nicla Sense ME** board, equipped with the **BME688 gas sensor** and Bosch's **AI Studio**, to identify specific solvent vapours and particulate matter in applications like laboratory fume hood monitoring.

This repository creates a cohesive project ecosystem by combining:
- **Arduino Code**: Handles sensor data collection and processing using the Nicla and MKR boards.
- **BME AI Studio**: Enables sensor training for vapour classification using onboard AI capabilities.
- **Python Scripts**: Processes, stores, and visualises data, offering insights through plots and databases.

### Key Concepts and Inspirations
- **Project Origin**: It began as an idea to detect smoke particulate detectors and was later adapted for lab fume hood applications.
- **Sensor Exploration**: Focused on the capabilities of the **BME688 sensor** and Bosch's **BSEC2 gas scanner**.
- **Learning Goals**: Teaching the Nicla board to identify specific solvent vapours using AI and integrated sensors.
- 
---

## Initial Setup, installation and Use (Recommended)
The following layout the method in which I set up my envioremtn. By no means do you have to dio it exaclty this way. Refer to docs and other Libraries for support

### **Hardware Requirements**

- [Nicla Sense ME](https://store.arduino.cc/products/nicla-sense-me)  
  *(ESLOV cable included with the board)*

- [Arduino MKR WiFi 1010](https://store.arduino.cc/products/arduino-mkr-wifi-1010)

- **Power and Data Micro USB Cable**  
  Ensure the cable supports both power and data transfer.

- *(Recommended)* [Portable Wi-Fi Source](https://www.amazon.com/s?k=portable+wifi+hotspot)  
  Useful for remote applications where a stable internet connection is required.

  ### **Software Setup**
Asumming you have and ide like VS Code() and git installed if not follow this guide: ()
Clone this repo into your working Directory for your choice of IDE
in terminal cd into ur working dir and run 
``` bash
git clone https://github.com/cheuh008/HC.Chem501
```
#### **1. Arduino Environment**
1. **Install Arduino IDE**: t[here](https://www.arduino.cc/en/software).T
 - his project Uses Arduino IDE 2
- VS Code can also be used with arduino comunity or PIO but refer to them for init
- for me personally, I changed where the library was installed to have my arduino code folder in the same as the Libraries
```bash
H.C.Chem501                  or              Arduino 
├── Arduino Code                              ├── Arduino Code   
│   ├── Consolidated                          └── libraries
│   │       └── ...
│   └── Modules
│           └── ...
└── libraries
    ├── Arduino_BHY2
    └── ...
```
   
2. **Required Board and Libraries**:
   From Board Manaagers type nicla nd mkr 1010 ti install requried 
    -  Mbed OS Nicla boards dobwlaod the following libraires viua library manaegr
    -  MKR SAMBD
    n the same sidebar  libaries  to be installed
    -  Arduino_BHY2
     -  Arduino_BLE
     - `Arduino_BHY2Host`
     - RTCZero
     - `WiFiNINA`
     - `ThingSpeak`

3. **Configure secrets.h and Upload**:
   At this stage u can begin collect gas data from your nicla sense me to be used in BME_AI_Studio
   run either `Smoke_Nicla.ino` in `Mode = 2` or `Ncla_Gas_Collector.ino` (which is basically the same code copied from `BSEC2GasScannerCollectData.ino`, in `Arduino/libraries/Arduino_BHY2/examples/BSEC2GasScannerCollectData/`
   to collate Gas data from serial, see below #2. BME AI Studio (& Putty)
   for remote loggin, Setup a [thingspeak](https://thingspeak.mathworks.com/) account 
configure serecrt.h, or u can come back to it before u upload the code 
   Create a new tab and name it secrets.h
   Copy the code from secrets_template.h into    secrets.h and fill in the required fields
   ```cpp
     #define SECRET_SSID "YourWiFiSSID"
     #define SECRET_PASS "YourWiFiPassword"
     #define SECRET_API_KEY "YourThingSpeakAPIKey"
     ```
   Upload the Nicla Code ANd MKR code you want to use to ur respective devices

#### **2. BME AI Studio (& Putty)**
1. downlaod BME AI STUDIo from the BME688 Software page. which also has etensive duicmentation and Putty from offical https://www.putty.org. for details refer to [Hackster Project](https://www.hackster.io/lucasguocn/use-bme-ai-studio-with-bme688-on-the-nicla-sense-me-board-5f1b55)
 -(BME_AI_Studio)[BME AI STUDIo[https://www.bosch-sensortec.com/software-tools/software/bme688-software/]
 - [Putty](https://www.putty.org/)

2. Save your log to a directory (in/near ur BME Project Folder), with z



#### **3. Python Environment**
The pyhton is used to analyeaand visu;laise the data so thi can be done at any time before / atfer you have accumulated enoguh data. (Python 3.12 used, Recommended a vitual enviuoremt env)
 1. in ur working directory, with your venv activated, onstal the folowing dependenncies by running
 
 ```bash
cd Python
pip install -r requirements.txt

```
2. **Add API Keys**:
   - Create a `keys.json` file in the `Python` directory:
   - `.gitignore` should alreay be cionfigured to ignore key.json to keep ur API keys safe
     ```json
     {
         "api_keys": {
             "channel_1": "YourChannel1APIKey",
             "channel_2": "YourChannel2APIKey"
         }
     }
     ```
3. configure your ThingSpeak Channel 
4.       open 'config.py and edit the channel details for your needs. 
   

   
   


---


### Further Reading
- [BME688 Sensor Overview](https://www.bosch-sensortec.com/products/environmental-sensors/gas-sensors/bme688/)  
- [BME688 Datasheet](https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bme688-ds000.pdf)  
- [Bosch AI Studio](https://www.bosch-sensortec.com/media/boschsensortec/downloads/application_notes_1/bst-bme688-an001.pdf)  
- **Demonstration**: [How gas sensing gets intelligent with BME688](https://www.youtube.com/watch?v=dO7DRoLsDNM)

### Potential Methods
- **AI Training**: Use Bosch's BME AI Studio to train the Nicla to classify vapours.
- **Example Implementations**:
  - [BSEC2 Gas Scanner Classify](https://github.com/arduino-libraries/Arduino_BHY2/blob/main/examples/BSEC2GasScannerClassify/BSEC2GasScannerClassify.ino)
  - [BSEC2 Gas Scanner Collect Data](https://github.com/arduino-libraries/Arduino_BHY2/blob/main/examples/BSEC2GasScannerCollectData/BSEC2GasScannerCollectData.ino)
- **Implementation Guide**: [Hackster Project](https://www.hackster.io/lucasguocn/use-bme-ai-studio-with-bme688-on-the-nicla-sense-me-board-5f1b55)
- **Community Verification**: [Bosch Forum Discussion](https://community.bosch-sensortec.com/mems-sensors-forum-jrmujtaw/post/bme-ai-studio-config-on-arduino-nicla-TPCJdSxmesNaGIM)



## File Tree Structure
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
│       ├──...
│       ├── acetone_2_1.bmespecimen
│       ├──...
│       ├── acetone_4_9.bmespecimen
│       ├──...
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

## Components

### 1. **Python Scripts**
- **`BSEC2DataLogConverter.py`:** A Python script to convert raw data logs from the BME sensors into an analyzable format.
- **`data_analysis.ipynb`:** A Jupyter Notebook for analysing and visualising environmental data, with examples for plotting and statistical analysis.

### 2. **BME Configurations**
- **`NiclaBME_HP-354.bmeconfig`:** High-performance configuration tailored for specific environmental monitoring tasks.
- **`Nicla_BME2.bmeproject`:** The base project configuration for Nicla BME2 boards.
- **`Nicla_BME2V2.bmeproject`:** An optimised version of the base configuration for enhanced accuracy.

### 3. **Arduino Code**
#### Consolidated Approach:
- **Smoke_MKR:** A single project focused on data collection and transmission for the MKR board.
- **Smoke_Nicla:** Configurations and code for the Nicla board, including specific headers like `BSEC2CONFIG.h`.

#### Modular Approach:
- **MKR_Master_to_ThingSpeak:** Sends processed data to the ThingSpeak platform.
- **Nicla_BSEC2_Classifier_Slave_Sender:** Focuses on transmitting classifier data from the Nicla board.

## Workflow
1. **Data Collection:**
   - Use Arduino code to collect data from BME sensors on the MKR or Nicla boards.
   - Store logs in the `ataLogs` folder or equivalent.

2. **Data Conversion:**
   - Run `BSEC2DataLogConverter.py` to process raw logs into a structured format.

3. **Analysis:**
   - Use `PYTHON` to perform detailed analyses and visualisation.

4. **Configuration Management:**
   - Modify `.bmeconfig` or `.bmeproject` files to fine-tune sensor performance for specific use cases.

## Contribution Guidelines
- Keep the Python, BME, and Arduino sections organised.
- Document changes to configurations and scripts in their respective `README.md` files.
- Test all changes before committing to ensure compatibility across components.

## Notes
- Ensure proper synchronisation between hardware configurations and scripts for optimal performance.
- Refer to individual README files within each folder for more specific usage instructions.

For further assistance, contact the repository maintainers or refer to the official documentation of the respective tools.
