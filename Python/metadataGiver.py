import matplotlib.pyplot as plt
import pandas as pd
import sqlite3
import uuid
import os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))  # Define the path to the Python Folder
FOLDER_DIR = 'data'                                      # Define the path to the Data Folder
DB_NAME = 'experiment_data.db'                            # Define name to the database
db_path = os.path.join(SCRIPT_DIR, FOLDER_DIR, DB_NAME)   # Dynamic path create to DB

def insert_data(df, channel_names, cursor):
    """
    This function takes the dataframe, channels, and cursor and inserts data into the database
    for each day and channel combination with a unique experiment_id.
    """
    df['created_at'] = pd.to_datetime(df['created_at'])  # Ensure 'created_at' is in datetime format
    unique_dates = df['created_at'].dt.date.unique()  # Get unique dates from the 'created_at' column

    # Loop through each date and process the data for that day
    for date in unique_dates:
        experiment_date = date.strftime('%Y-%m-%d')  # Format the date to YYYY-MM-DD
        experiment_id = str(uuid.uuid4())  # Generate unique experiment ID

        cursor.execute('''
        INSERT INTO experiments (experiment_id, experiment_date) VALUES (?, ?)
        ''', (experiment_id, experiment_date))

        # For each channel, insert metadata and data for that day
        for channel in channel_names:
            metadata_id = str(uuid.uuid4())  # Generate unique metadata ID
            cursor.execute('''
            INSERT INTO metadata (metadata_id, experiment_id, metadata_type, value)
            VALUES (?, ?, ?, ?)
            ''', (metadata_id, experiment_id, channel, str(df[df['created_at'].dt.date == date][channel].iloc[0])))

        # Insert data for the specific day and channel
        day_data = df[df['created_at'].dt.date == date]
        for _, row in day_data.iterrows():
            for channel in channel_names:
                data_id = str(uuid.uuid4())  # Generate unique data ID
                cursor.execute('''
                INSERT INTO data (data_id, experiment_id, channel_name, value)
                VALUES (?, ?, ?, ?)
                ''', (data_id, experiment_id, channel, row[channel]))

        plot(day_data, experiment_id, channel, experiment_date)

def get_csv(cursor):  # Main function to handle CSV file processing for two specific files
    file_1 = os.path.join(SCRIPT_DIR, FOLDER_DIR, 'channel_1_data.csv')  # Path to the first CSV file
    file_2 = os.path.join(SCRIPT_DIR, FOLDER_DIR, 'channel_2_data.csv')  # Path to the second CSV file

    # Process the first CSV file
    df1 = pd.read_csv(file_1)
    channel_names_1 = [col for col in df1.columns if col != 'created_at']  # Exclude 'created_at' column
    insert_data(df1, channel_names_1, cursor)

    # Process the second CSV file
    df2 = pd.read_csv(file_2)
    channel_names_2 = [col for col in df2.columns if col != 'created_at']  # Exclude 'created_at' column
    insert_data(df2, channel_names_2, cursor)

def db_setup():
    conn = sqlite3.connect(db_path)  # Connect to SQLite DB
    cursor = conn.cursor()

    # Create tables for experiments and metadata if not already present
    cursor.execute('''
    CREATE TABLE IF NOT EXISTS experiments (
        experiment_id TEXT PRIMARY KEY,
        experiment_date TEXT
    )''')

    cursor.execute('''
    CREATE TABLE IF NOT EXISTS metadata (
        metadata_id TEXT PRIMARY KEY,
        experiment_id TEXT,
        metadata_type TEXT,
        value TEXT,
        FOREIGN KEY(experiment_id) REFERENCES experiments(experiment_id)
    )''')

    cursor.execute('''
    CREATE TABLE IF NOT EXISTS data (
        data_id TEXT PRIMARY KEY,
        experiment_id TEXT,
        channel_name TEXT,
        value REAL,
        FOREIGN KEY(experiment_id) REFERENCES experiments(experiment_id)
    )''')

    # Process the CSV files
    get_csv(cursor)

    # Commit changes and close the connection
    conn.commit()
    conn.close()

    print("Data successfully inserted into the database.")


def show_db_contents():
    conn = sqlite3.connect(db_path)
    cursor = conn.cursor()

    cursor.execute('SELECT name FROM sqlite_master WHERE type="table";')
    tables = cursor.fetchall()

    for table in tables:
        table_name = table[0]
        print(f"\nContents of table: {table_name}")
        df = pd.read_sql_query(f"SELECT * FROM {table_name}", conn)
        print(df)

    conn.close()

def get_db():
    # Connect to the SQLite DB
    conn = sqlite3.connect(db_path)
    
    # Load data from the database
    query = '''
    SELECT e.experiment_id, e.experiment_date, m.metadata_type, d.value
    FROM experiments e
    JOIN metadata m ON e.experiment_id = m.experiment_id
    JOIN data d ON e.experiment_id = d.experiment_id
    ORDER BY e.experiment_date
    '''
    
    # Fetch data from the database into a DataFrame
    df = pd.read_sql_query(query, conn)
    
    # Close the database connection
    conn.close()

    return df

def plot(df, experiment_id, channel_name, date):
    """
    Plot each field (column) of the dataframe and save the plots in a folder named by the date and channel.
    """
    # Use channel_name correctly in the folder name
    folder_name = f"{date}_channel_{channel_name}"  # Add "channel_" prefix for clarity
    directory_path = os.path.join(SCRIPT_DIR, FOLDER_DIR, folder_name)
    os.makedirs(directory_path, exist_ok=True)

    # Loop through each column in the dataframe (excluding 'created_at' and 'experiment_id' columns)
    for column in df.columns:
        if column not in ['created_at', 'experiment_id']:
            # Plot the field (column)
            plt.figure(figsize=(10, 6))
            plt.plot(df['created_at'], df[column], label=column)
            plt.title(f"{column} - {experiment_id}")
            plt.xlabel("Time")
            plt.ylabel(column)
            plt.legend()

            # Save the plot as a PNG file in the correct folder
            plt.savefig(os.path.join(directory_path, f"{column}.png"))
            plt.close()  # Close the plot to free up memory


if __name__ == "__main__": 
    if not os.path.exists(db_path):
        db_setup()  # If DB doesn't exist, set up the database and insert data
    else:
        show_db_contents()  # If DB exists, show its contents

