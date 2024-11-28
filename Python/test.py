import requests
import sqlite3
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import pandas as pd
import json

with open("./keys.json", "r") as file:
    keys = json.load(file)

API_KEY_1 = keys["api_keys"]["channel_1"]
API_KEY_2 = keys["api_keys"]["channel_2"]

CHANNELS = [
    {"id": 2753096, "fields": 5, "api_key": API_KEY_1},
    {"id": 2758654, "fields": 8, "api_key": API_KEY_2},
]
THINGSPEAK_URL = "https://api.thingspeak.com/channels/{}/feeds.json"

# Database setup
DB_NAME = "thingspeak_data.db"

# Define field labels for Channel 1 and Channel 2
FIELD_LABELS = {
    "channel_1": ["Ambient", "Acetone", "Ethyl Acetate", "Ethanol", "Accuracy"],
    "channel_2": [
        "Gas Resistance (Ohms)", "Pressure (Pa)", "Stationary IAQ",
        "Breath VOC Equivalent (ppm)", "CO2 Equivalent (ppm)", 
        "Compensated Temperature (°C)", "Compensated Humidity (Relative %)", "BSEC Accuracy (/3)"
    ]
}
def setup_database():
    """Create tables for storing ThingSpeak data."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()

    # Channel 1: 5 fields
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS channel_1 (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            created_at TEXT,
            ambient REAL,
            acetone REAL,
            ethyl_acetate REAL,
            ethanol REAL,
            accuracy REAL
        )
    """)
    # Channel 2: 8 fields
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS channel_2 (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            created_at TEXT,
            gas_resistance REAL,
            pressure REAL,
            stationary_iaq REAL,
            breath_voc_equivalent REAL,
            co2_equivalent REAL,
            compensated_temperature REAL,
            compensated_humidity REAL,
            bsec_accuracy REAL
        )
    """)
    conn.commit()
    conn.close()


def fetch_and_store_data():
    """Fetch data from ThingSpeak and store it in the database."""
    conn = sqlite3.connect(DB_NAME)
    cursor = conn.cursor()

    for i, channel in enumerate(CHANNELS):
        response = requests.get(THINGSPEAK_URL.format(channel["id"]), params={"api_key": channel["api_key"], "results": 8000})
        if response.status_code == 200:
            data = response.json()["feeds"]
            table_name = f"channel_{i + 1}"
            if i == 0:  # Channel 1 (5 fields)
                for entry in data:
                    cursor.execute(f"""
                        INSERT INTO {table_name} (created_at, ambient, acetone, ethyl_acetate, ethanol, accuracy)
                        VALUES (?, ?, ?, ?, ?, ?)
                    """, [
                        entry["created_at"],
                        entry.get("field1"),
                        entry.get("field2"),
                        entry.get("field3"),
                        entry.get("field4"),
                        entry.get("field5"),
                    ])
            else:  # Channel 2 (8 fields)
                for entry in data:
                    cursor.execute(f"""
                        INSERT INTO {table_name} (created_at, gas_resistance, pressure, stationary_iaq,
                            breath_voc_equivalent, co2_equivalent, compensated_temperature, compensated_humidity, bsec_accuracy)
                        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)
                    """, [
                        entry["created_at"],
                        entry.get("field1"),
                        entry.get("field2"),
                        entry.get("field3"),
                        entry.get("field4"),
                        entry.get("field5"),
                        entry.get("field6"),
                        entry.get("field7"),
                        entry.get("field8"),
                    ])
        else:
            print(f"Failed to fetch data for channel {channel['id']}: HTTP {response.status_code}")
    conn.commit()
    conn.close()


def fetch_data_from_db():
    """Fetch data from the database and return as a dictionary of DataFrames."""
    conn = sqlite3.connect(DB_NAME)
    dataframes = {}
    for channel in CHANNELS:
        table_name = f"channel_{channel['id']}"
        query = f"SELECT * FROM {table_name}"
        df = pd.read_sql_query(query, conn)
        dataframes[table_name] = df
    conn.close()
    return dataframes

def plot_graphs(dataframes):
    """Plot fields in a 4x4 grid:
       - Channel 1: Fields 1-5 in columns 1-2.
       - Channel 2: Fields 1-8 in columns 3-4.
    """
    fig = plt.figure(figsize=(15, 10))  # Define the overall figure size
    gs = gridspec.GridSpec(4, 4, figure=fig, wspace=0.5, hspace=0.5)  # Create a 4x4 grid layout

    # Plot for Channel 1 (5 fields in columns 1 and 2)
    table_name_1 = f"channel_{CHANNELS[0]['id']}"  # First channel table name
    df_1 = dataframes[table_name_1]  # DataFrame for Channel 1
    time_1 = pd.to_datetime(df_1["created_at"])  # Convert timestamps to datetime

    # Plot for Channel 1
    for i, label in enumerate(FIELD_LABELS["channel_1"]):  # Use field labels
        row, col = divmod(i, 2)
        ax = fig.add_subplot(gs[row, col])  # Place in columns 1 and 2
        ax.plot(time_1, df_1.iloc[:, i + 1], label=label)  # Use iloc for indexed column
        ax.set_title(label, fontsize=8)
        ax.set_xlabel("Time")
        ax.set_ylabel("Value")
        ax.grid(True)

    # Plot for Channel 2 (8 fields in columns 3 and 4)
    table_name_2 = f"channel_{CHANNELS[1]['id']}"  # Second channel table name
    df_2 = dataframes[table_name_2]  # DataFrame for Channel 2
    time_2 = pd.to_datetime(df_2["created_at"])  # Convert timestamps to datetime

    # Plot for Channel 2
    for i, label in enumerate(FIELD_LABELS["channel_2"]):  # Use field labels
        row, col = divmod(i, 2)
        ax = fig.add_subplot(gs[row, col + 2])  # Place in columns 3 and 4
        ax.plot(time_2, df_2.iloc[:, i + 1], label=label)  # Use iloc for indexed column
        ax.set_title(label, fontsize=8)
        ax.set_xlabel("Time")
        ax.set_ylabel("Value")
        ax.grid(True)

    plt.tight_layout()  # Adjust layout to prevent overlap
    plt.show()


if __name__ == "__main__":
    setup_database()        # Step 1: Set up the database
    fetch_and_store_data()  # Step 2: Fetch and store data
    dataframes = fetch_data_from_db()  # Step 3: Load data from DB
    plot_graphs(dataframes)  # Step 4: Plot the graphs
