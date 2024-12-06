# Arduino Code File Tree and Coding Paradigms

This repository illustrates two coding paradigms for Arduino projects: **Consolidated Code** and **Modular Code**. Below is an explanation of these paradigms, their differences, and the repository's structure.

## File Tree Structure
```
├── Consolidated
│   ├── Smoke_MKR
│   │   ├── README.md
│   │   ├── secrets.h
│   │   ├── secrets_template.h
│   │   └── Smoke_MKR.ino
│   └── Smoke_Nicla
│       ├── BSEC2CONFIG.h
│       ├── CONFIG_BSEC2_HP.h
│       ├── README.md
│       └── Smoke_Nicla.ino
└── Modules
    ├── BackUpVOC_MKR
    │   ├── BackUpVOC_MKR.ino
    │   ├── README.md
    │   └── secrets_template.h
    ├── BackUpVOC_NiclaAppLowDelay
    │   └── BackUpVOC_NiclaAppLowDelay.ino
    ├── MKR_Master_to_ThingSpeak
    │   ├── MKR_Master_to_ThingSpeak.ino
    │   ├── README.md
    │   └── secrets_template.h
    ├── Nicla_BSEC2_Classifier_Slave_Sender
    │   └── Nicla_BSEC2_Classifier_Slave_Sender.ino
    └── Nicla_Gas_Collector
        └── Nicla_Gas_Collector.ino
```

## Coding Paradigms

### 1. Consolidated Code
In the **Consolidated** approach, the code combines increased logic complexity to reduce the effort required for manual setup and deployment. While this approach requires a deeper understanding of the integrated structure, it significantly streamlines human tasks.

#### Characteristics:
- **Centralized:** All logic, configurations, and dependencies are grouped into a single directory, minimising the need for manual intervention.
- **Reduced Setup Effort:** Designed to simplify deployment, making it easier to upload and run without constant reconfiguration.
- **Ease of Deployment:** It is easier to upload and go without re-uploading different modules.
- **Code Duplication:** Removes redundant duplicate code across modules.

#### Example:
- **Smoke_MKR:** Contains the main `Smoke_MKR.ino` file and `secrets.h` for managing sensitive data.
- **Smoke_Nicla:** Includes specialized header files such as `BSEC2CONFIG.h` and `CONFIG_BSEC2_HP.h` for configuring the Nicla board.

### 2. Modular Code
The **Modular** approach divides functionality into discrete modules, each focusing on a specific task or feature. This structure improves reusability and scalability.

#### Characteristics:
- **Separation of Concerns:** Each module performs a distinct role (e.g., data collection, classification, communication).
- **Scalability:** Simplifies adding or modifying functionality.

#### Example:
- **BackUpVOC_MKR:** Handles specific VOC tasks for the MKR board as the project back up.
- **Nicla_BSEC2_Classifier_Slave_Sender:** Focuses on transmitting classifier data from the Nicla board.
- **MKR_Master_to_ThingSpeak:** Implements data transmission to ThingSpeak.

## Contribution and Usage
Refer to the individual `README.md` files in each project or module folder for specific instructions and details.
