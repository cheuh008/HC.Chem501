# ===========================================================================================================
# File: config.py
# Description: Reads, writes, and manages configuration for ThingSpeak channels.
# Author: Harry @https://github.com/cheuh008
# Created: 2024-11-20
# ===========================================================================================================

import json                                                           # Module for JSON handling
import os                                                             # Module for file system operations

# ===========================================================================================================
# region: Keys Management
# Description: Handles API key loading from a secure JSON file (keys.json).
# Note: Ensure keys.json is added to .gitignore to avoid exposing API keys.
# Expected Format:
# {
#     "api_keys": {
#         "channel_1": "API_KEY_1",
#         "channel_2": "API_KEY_2"
#     }
# }
# Replace API_KEY_1 and API_KEY_2 with the actual API keys.
# ===========================================================================================================

try:
    with open("./keys.json", "r") as key:                             # Open keys.json in read mode
        keys = json.load(key)                                         # Load and parse JSON content
except FileNotFoundError:                                             # Handle missing keys.json file
    raise FileNotFoundError("The keys.json file is missing. Please provide the file with API keys.")
except json.JSONDecodeError:                                          # Handle invalid JSON formatting
    raise ValueError("Invalid JSON format in keys.json. Please fix the file.")

API_KEY_1 = keys["api_keys"]["channel_1"]                             # Retrieve API key for channel 1
API_KEY_2 = keys["api_keys"]["channel_2"]                             # Retrieve API key for channel 2

# ===========================================================================================================
# region: Default Config
# Description: Contains default configuration values for ThingSpeak channels.
# Note: These defaults will be used if config.json does not exist or needs to be reset.
# ===========================================================================================================

CONFIG_FILE = "config.json"                                           # File name for the configuration file

DEFAULT_CONFIG = {                                                    # Default configuration dictionary
    "channel_1": {
        "id": 2753096,                                                # ThingSpeak Channel ID 1
        "fields": 5,                                                  # Number of fields in the channel 1
        "api_key": API_KEY_1,                                         # API key for accessing the channel 1
        "labels": ["Ambient", "Acetone", "Ethyl Acetate", "Ethanol", "Accuracy"]
    },
    "channel_2": {
        "id": 2758654,                                                # ThingSpeak Channel ID 2
        "fields": 8,                                                  # Number of fields in the channel 2
        "api_key": API_KEY_2,                                         # API key for accessing the channel 2
        "labels": [                                                   # Field Headers in channel 2
            "Gas Resistance (Ohms)", "Pressure (Pa)", "Stationary IAQ", 
            "Breath VOC Equivalent (ppm)", "CO2 Equivalent (ppm)", 
            "Compensated Temperature (°C)", "Compensated Humidity (Relative %)", 
            "BSEC Accuracy (%3)"
        ]
    }
}

# ===========================================================================================================
# region: Configuration Management
# Description: Load or create the configuration file for channel details.
# ===========================================================================================================

def get_channels() -> dict[str, dict[int, int, str, list]]:
    """Returns: dictionary of channel: id, fields, api_key, labels[] """
    if not os.path.exists(CONFIG_FILE):                               # Check if config.json exists
        with open(CONFIG_FILE, "w") as file:                          # Open config.json in write mode
            json.dump(DEFAULT_CONFIG, file, indent=4)                 # Save default config as indented JSON
    try:
        with open(CONFIG_FILE, "r") as file:                          # Open config.json in read mode
            return json.load(file)                                    # Parse and return JSON as dictionary
    except json.JSONDecodeError:                                      # Handle invalid JSON formatting
        raise ValueError("Invalid JSON format in config.json. Please fix the file.")

# ===========================================================================================================
# End of config.py
# ===========================================================================================================
