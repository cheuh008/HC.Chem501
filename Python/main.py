# ===========================================================================================================
# File: main.py
# Description: Main programme: calls functions to fetch, store, and visualize data from ThingSpeak Server.
# Author: Harry @https://github.com/cheuh008
# Created: 2024-11-20
# ===========================================================================================================

# ===========================================================================================================
# region: Imports submodules functions for database handling, plotting, and configuration.
# ===========================================================================================================

from dbHandler import dbHandler         # Handles database setup, data fetching, and storage
from plotting import plot      # Handles plotting data in a 4x4 grid format
from config import get_channels         # Loads channel configuration from config.json

# ===========================================================================================================
# region: Constants
# Description: Define constant variables for database and channel configurations.
# ===========================================================================================================

CHANNELS = get_channels()               # Fetch the channel configurations
DB_NAME = "thingspeak_data.db"          # Name of the SQLite database file

# ===========================================================================================================
# region: Main Execution Block
# Description: Orchestrates the entire process of fetching, storing, and visualizing data.
# ===========================================================================================================

if __name__ == "__main__":
    dfs = dbHandler(DB_NAME, CHANNELS)  # Fetch and store data from ThingSpeak, return DataFrames

    plot(dfs, CHANNELS)        # Visualize data using a 4x4 grid plot

    for channel, df in dfs.items():     # Iterate over each channel and its DataFrame
        print(f"Data for {channel}:")   # Print channel name for reference
        print(df.head())                # Print the first few rows of the DataFrame for inspection

# ==============================================================================================================================
# End of main.py
# ==============================================================================================================================
