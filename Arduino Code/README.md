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
In the **Consolidated** approach, all logic, configurations, and dependencies are grouped into a single project directory. This simple and compact structure can become harder to manage as the project scales.

#### Characteristics:
- **Centralized:** All code and configurations are in one location.
- **Specificity:** Designed for a single hardware configuration (e.g., Smoke_MKR, Smoke_Nicla).
- **Ease of Deployment:** Ideal for small projects with unnecessary modularity.
- **Code Duplication:** Similar functionality may require repeating code across projects.

#### Example:
- **Smoke_MKR:** Contains the main `Smoke_MKR.ino` file and `secrets.h` for managing sensitive data.
- **Smoke_Nicla:** Includes specialized header files such as `BSEC2CONFIG.h` and `CONFIG_BSEC2_HP.h` for configuring the Nicla board.

### 2. Modular Code
The **Modular** approach divides functionality into discrete modules, each focusing on a specific task or feature. This structure improves reusability and scalability.

#### Characteristics:
- **Separation of Concerns:** Each module performs a distinct role (e.g., data collection, classification, communication).
- **Scalability:** Simplifies adding or modifying functionality.
- **Complexity:** Initial setup and integration may require more effort.

#### Example:
- **BackUpVOC_MKR:** Handles specific VOC backup tasks for the MKR board.
- **Nicla_BSEC2_Classifier_Slave_Sender:** Focuses on transmitting classifier data from the Nicla board.
- **MKR_Master_to_ThingSpeak:** Implements data transmission to ThingSpeak, demonstrating integration with external services.


## When to Use Each Approach
- **Consolidated Approach:**
  - Suitable for small-scale or one-off projects.
  - Best for simple setups requiring minimal changes.

- **Modular Approach:**
  - Ideal for larger, more complex projects.
  - Useful when the functionality needs to be shared across multiple projects or hardware configurations.

## Contribution and Usage
Refer to the individual `README.md` files in each project or module folder for specific instructions and details.
