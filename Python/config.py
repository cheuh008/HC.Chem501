# ===========================================================================================================
# File: config.py
# Description: Reads, writes, and manages configuration for ThingSpeak channels.
# Author: Harry @https://github.com/cheuh008
# Created: 2024-11-20
# =============================================================================================================

import json
import os

# =============================================================================================================
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
# =============================================================================================================

with open("./keys.json", "r") as file:
    keys = json.load(file)

API_KEY_1 = keys["api_keys"]["channel_1"]
API_KEY_2 = keys["api_keys"]["channel_2"]

# =============================================================================================================
# region: Default Config
# Description: Contains default configuration values for ThingSpeak channels.
# Note: These defaults will be used if config.json does not exist or needs to be reset.
# =============================================================================================================

CONFIG_FILE = "config.json"

DEFAULT_CONFIG = {  "channel_1": { "id": 2753096, "fields": 5, "api_key": API_KEY_1,
                    "labels": ["Ambient", "Acetone", "Ethyl Acetate", "Ethanol", "Accuracy"]
                    },
                    "channel_2": { "id": 2758654, "fields": 8, "api_key": API_KEY_2,
                        "labels": ["Gas Resistance (Ohms)", "Pressure (Pa)", "Stationary IAQ", 
                                "Breath VOC Equivalent (ppm)", "CO2 Equivalent (ppm)", 
                                "Compensated Temperature (°C)", "Compensated Humidity (Relative %)", 
                                "BSEC Accuracy (/3)"
                        ]
                    }}

# =============================================================================================================
# REGION: Configuration Management
# Description: Functions to load, save, and retrieve configuration data.
# - `load_config()`: Reads config.json, or initializes it with defaults if missing.
# - `save_config()`: Writes configuration to config.json.
# - `get_channels()`: Provides the current channel configuration as a dictionary.
# =============================================================================================================

def load_config():
    """Load the config from the config.json """

    if not os.path.exists(CONFIG_FILE):             # Checks if config.json exists 
        save_config(DEFAULT_CONFIG)                 # If not, created and saved based on default config
        return DEFAULT_CONFIG                       # Returns the default config dictionary

    with open(CONFIG_FILE, "r") as file:            # Opens config.json in read mode
        return json.load(file)                      # Parse and returns JSON as Python dictionary

def save_config(config):
    """ Saves / overwrites config to  config.json """
    with open(CONFIG_FILE, "w") as file:            # Opens json in write mode to write, or overwrite if needed
        json.dump(config, file, indent=4)           # Dumps Serialised dictionary to JSON format (indentated)

def get_channels() -> dict:
    """ Returns: Configed Channel Dictionary  """
    return load_config()                            # Call load_config to fetch and return the configuration

# =============================================================================================================
# End 
# =============================================================================================================
