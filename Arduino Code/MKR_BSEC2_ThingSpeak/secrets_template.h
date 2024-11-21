#ifndef SECRETS_H
#define SECRETS_H

// WiFi credentials
#define SECRET_SSID "ssid"     // Replace with your WiFi SSID
#define SECRET_PASS "wifi_pw" // Replace with your WiFi password

// ThingSpeak credentials (for only 1 server)
#define SECRET_CH_ID 0000000        // replace 0000000 with your channel number
#define SECRET_W_APIKEY "XYZ"  // replace XYZ with your channel write API Key

// ThingSpeak credentials (for more than 1 server)
unsigned long channelIDs[] = { YOUR_CHANNEL_ID1, YOUR_CHANNEL_ID2, YOUR_CHANNEL_ID3 };
const char* APIKeys[] = { "API_KEY1", "API_KEY2", "API_KEY3"};

#endif
