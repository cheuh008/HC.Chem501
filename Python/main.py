# ===========================================================================================================
# File: main.py
# Description: Main programme: calls functions to fetch, store, and visualizing data from ThingSpeak Server.
# Author: Harry @https://github.com/cheuh008
# Created: 2024-11-20
# ===========================================================================================================


from database_handler import setup_database, fetch_and_store_data, fetch_data_from_db
from plotting import plot_4x4_grid
from config import get_channels

CHANNELS = get_channels()

DB_NAME = "thingspeak_data.db"                          # Name of the database file

if __name__ == "__main__":
    setup_database(DB_NAME, CHANNELS)                   # Step 1: Setup the database
    fetch_and_store_data(DB_NAME, CHANNELS)             # Step 2: Fetch data from ThingSpeak and store in the database
    dataframes = fetch_data_from_db(DB_NAME, CHANNELS)  # Step 3: Fetch data from the database for visualization
    plot_4x4_grid(dataframes, CHANNELS)                 # Step 4: Plot the data

    for channel_name, df in dataframes.items():         # 
        print(f"Data for {channel_name}:")
        print(df.head())
