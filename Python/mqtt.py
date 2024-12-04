import paho.mqtt.client as mqtt
import sqlite3

# Configuration
MQTT_BROKER = "mqtt.example.com"
MQTT_PORT = 1883
MQTT_TOPIC = "your/topic"
DB_FILE = "mqtt_data.db"

# Database setup

# Function to store messages in the database
def store_message(topic, payload):
    conn = sqlite3.connect(DB_FILE)
    cursor = conn.cursor()
    cursor.execute("INSERT INTO mqtt_messages (topic, payload) VALUES (?, ?)", (topic, payload))
    conn.commit()
    conn.close()

# MQTT Callbacks
def on_connect(client, userdata, flags, reason_code, properties):
    if reason_code == 0:
        print("Connected to MQTT Broker!")
        client.subscribe(MQTT_TOPIC)     # on_connect() means that if we lose the connection and reconnect then subscriptions will be renewed.
    else:
        print(f"Failed to connect, return code {reason_code}")

def on_message(client, userdata, msg):
    try:
        payload = msg.payload.decode('utf-8')
        print(f"Received message on topic {msg.topic}: {payload}")
        store_message(msg.topic, payload)
    except Exception as e:
        print(f"Error processing message: {e}")

# Main function
def main():
    conn = sqlite3.connect(DB_FILE)
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS mqtt_messages (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        topic TEXT NOT NULL,
                        payload TEXT NOT NULL,
                        timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
                      )''')
    conn.commit()
    conn.close()

    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message

    try:
        client.connect(MQTT_BROKER, MQTT_PORT, 60)
        client.loop_forever()
    except KeyboardInterrupt:
        print("Disconnected from MQTT Broker.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()
