# =======================================================================================================================================
# File: database_handler.py
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

def setup_database(db, channels):
    """
    Create tables in the database for each channel using the labels from the channels dictionary.

    Args:
        db (str): The name of the database file.
        channels (dict): Dictionary containing channel information and labels.
    """
    conn = sqlite3.connect(db)                                      # Connect to the SQLite database
    cursor = conn.cursor()                                          # Create a cursor for executing SQL queries

    for name, data in channels.items():                             # Iterate through each channel configuration
        labels = data["labels"]                                     # Get the field labels for this channel
        field_columns = ", ".join([f'"{l}" REAL' for l in labels])  # Construct SQL to create a table dynamically based on the labels
        cursor.execute(f"""
            CREATE TABLE IF NOT EXISTS {name} (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                created_at TEXT,
                {field_columns}
                ) """)
    conn.commit()                                                         # Commit the changes to the database
    conn.close()                                                          # Close the database connection

# =======================================================================================================================================
# region: Data Fetch and Store
# Description: Fetch data from ThingSpeak, clean it, and store only valid rows in the database.
# =======================================================================================================================================

def fetch_and_store_data(db, channels):
    """
    Fetch data from ThingSpeak, clean it, and store only valid rows in the database.

    Args:
        db (str): The name of the SQLite database.
        channels (dict): Dictionary containing channel information and labels.
    """
    THINGSPEAK_URL = "https://api.thingspeak.com/channels/{}/feeds.json"  # 
    conn = sqlite3.connect(db)                                            # Connect to the SQLite database

    for name, data in channels.items():                                   # Iterate through each channel configuration
        url = THINGSPEAK_URL.format(data["id"])                           # Format the URL with the channel ID
        params = {"api_key": data["api_key"], "results": 8000}            # Define the parameters
        response = requests.get(url, params=params)                       # Pass the URL and parameters to requests.get()

        if response.status_code == 200:                                   # If the HTTP request is successful
            data = response.json()["feeds"]                               # Parse the JSON data
            labels = data["labels"]                                       # Get the field labels for this channel

            rows = []                                                     # Fetch data and construct a pandas DataFrame
            for entry in data:                                            # Iterate through the fetched entries
                row = ([entry["created_at"]] + [                          # Start with a list containing the "created_at" timestamp
                    entry.get(f"field{i+1}") for i in range(len(labels))  # Append values for each field (field1, field2, ...) dynamically
                ])
                rows.append(row)                                          # Append each row of data

            columns = ["created_at"] + labels                             # Define column names (created_at + labels)
            df = pd.DataFrame(rows, columns=columns)                      # Create a DataFrame from the fetched data

            df[labels] = df[labels].apply(pd.to_numeric, errors="coerce") # Convert numeric columns, invalid values to NaN
            df_cleaned = df.dropna(subset=labels)                         # Drop rows with invalid (non-numeric) values

            df_cleaned.to_sql(name, conn, if_exists="append", index=False)  # Insert data into the database
            print(f"Stored cleaned data for table '{name}' - {len(df_cleaned)} rows added.")
        else:
            print(f"Failed to fetch data for channel {data['id']}: HTTP {response.status_code}")

    conn.commit()                                                         # Commit the changes to the database
    conn.close()                                                          # Close the database connection

# =======================================================================================================================================
# region: Fetch Data for Analysis
# Description: Retrieve stored data from the database and return it as pandas DataFrames for analysis.
# =======================================================================================================================================

def fetch_data_from_db(db, channels):
    """
    Fetch data from the database and return it as a dictionary of DataFrames.

    Args:
        db (str): The name of the database file.
        channels (dict): Dictionary containing channel information.

    Returns:
        dict: A dictionary of pandas DataFrames for each channel.
    """
    conn = sqlite3.connect(db)                 # Connect to the SQLite database
    df = {}                                         # Initialize empty dict to store dataframe

    for name, data in channels.items():             # Iterate through each channel configuration
        query = f"SELECT * FROM {name}"             # Construct a SQL query to select all data
        df[name] = pd.read_sql_query(query, conn)   # Load the data into a pandas DataFrame

    conn.close()                                    # Close the database connection
    return df                                       # Return the dictionary of DataFrames

# =======================================================================================================================================
# END the SQLsss squigglesssss
# =======================================================================================================================================
