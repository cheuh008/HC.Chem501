# =======================================================================================================================================
# File: dbHandler.py
# Description: Handles database creation, data insertion, and retrieval for ThingSpeak channels.
# Author: Harry @https://github.com/cheuh008
# Created: 2024-11-20
# =======================================================================================================================================

import sqlite3
import requests
import pandas as pd

# =======================================================================================================================================
# region: Database Setup
# Description: Functions to create and manage database tables dynamically based on channel configuration.
# =======================================================================================================================================

def dbHandler(db: str, channels: dict[str, dict[str, any]]) -> dict[str, pd.DataFrame]:
    """
    Creates SQL table from ThingSpeak API, saves data as .db and .csv
    db (str): The database file name (e.g., 'data.db').
    channels (dict): A dictionary of channel configurations containing:
        - labels (list[str]): List of field labels.
        - api_key (str): API key for the channel.
        - id (int): ThingSpeak channel ID.    
    Returns: pandas DataFrames of cleaned data per channel.
    """
    dfs = {}                                                                    # Empty dict to store DataFrames
    THINGSPEAK_URL = "https://api.thingspeak.com/channels/{}/feeds.json"        # ThingSpeak URL format
    with sqlite3.connect(db) as conn:                                           # Open database connection
        cursor = conn.cursor()
        for name, data in channels.items():                                     # Iterate over channel configurations
            labels = data["labels"]                                             # Get the field labels for the channel

# ========= # ==========================================================================================================================
            # region: Database Dynamic Creation based on channel config
# ========= # ==========================================================================================================================
            field_columns = ", ".join([f'"{label}" REAL' for label in labels])  # Generate SQL columns dynamically based on labels
            try:
                cursor.execute(                                                 # Create table if it doesn't already exist
                    f"""CREATE TABLE IF NOT EXISTS {name} (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        created_at TEXT, {field_columns}
                    )
                """)
            except sqlite3.DatabaseError as e:
                print(f"Database error: {e}")
                continue

# ========= # ==========================================================================================================================
            # region: Data Acquisition from ThingSpeak
# ========= # ==========================================================================================================================
            url = THINGSPEAK_URL.format(data["id"])                             # Format URL with the channel ID
            params = {"api_key": data["api_key"], "results": 8000}              # API parameters for fetching data
            response = requests.get(url, params=params)                         # HTTP GET request to ThingSpeak

            if response.status_code == 200:                                     # Check if the HTTP request to ThingSpeak was successful
                feeds = response.json()["feeds"]                                # Extract the 'feeds' data from the JSON response

                # Construct rows of data for the DataFrame
                rows = [
                    [entry["created_at"]] +                                     # Add the 'created_at' timestamp as the first column
                    [entry.get(f"field{i+1}") for i in range(len(labels))]      # Dynamically retrieve field values
                    for entry in feeds
                ]
                columns = ["created_at"] + labels                               # Define DataFrame column names
                df = pd.DataFrame(rows, columns=columns)                        # Create the DataFrame with the rows and columns

# ============= # ======================================================================================================================
                # region: Data cleaning and saving as .db and .csv
# ============= # ======================================================================================================================
                df[labels] = df[labels].apply(pd.to_numeric, errors="coerce")   # Convert fields to numeric; non-convertible values become NaN
                df = df.dropna(subset=labels)                                   # Remove rows with NaN in any of the label columns
                df.to_sql(name, conn, if_exists="append", index=False)          # Append cleaned data to the SQL table
                dfs[name] = df                                                  # Add DataFrame to the dictionary
                csv_name = f"{name}_data.csv"                                   # Generate unique CSV file name
                df.to_csv(csv_name, index=False)                                # Save the DataFrame to a CSV file
                print(f"Stored '{name}' data - {len(df)} rows added.")          # Print success message
                print(f"Saved data for '{name}' to '{csv_name}'.")
            else:                                                               # If the HTTP request fails
                print(f"{data['id']} fetch failed: HTTP {response.status_code}") # Print the error

    return dfs                                                                  # Return the dictionary of DataFrames

# =======================================================================================================================================
# End of dbHandler.py
# =======================================================================================================================================