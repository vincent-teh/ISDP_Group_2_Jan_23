#include <ESP8266WiFi.h>

#define DEBUG   true
#define TIMEOUT 5000 // in milliseconds

const char* MY_SSID      = "YUSHENG";
const char* MY_PASSWORD  = "z888}26E";
// IPAddress SERVER_IP(192,168,137,1);
const char* SERVER_IP =  "yusheng";
const uint16_t PORT   = 5050;

/* Attempted to declare inside the loop function. However,
 * this causes error as the class is deleted everytime
 * the loops end due to scope declaration
 */
WiFiClient client;

void setup()
{
  init_wifi_connection(MY_SSID, MY_PASSWORD, DEBUG);
}

void loop() {
  bool is_debug = DEBUG;
  if (is_debug && !client.connected())
    Serial.print("Connecting to server...");
  while (!client.connected()) {
    if (client.connect(SERVER_IP, PORT) && is_debug) {
      Serial.println();
      Serial.println("Connected to the server");
      client.println("ESP8266 connected");
    } else if (is_debug)
      Serial.print(".");
  }

  while (client.available()) {
    char ch = static_cast<char>(client.read());
    if (is_debug)
      Serial.print(ch);
  }
}

/**
 * @brief Initilise the wifi connection.
 *
 * This function initialise the wifi connection of the ESP8266. Enable is_debug
 * for verbosing output
 *
 * @param SSID ssid of the network
 * @param PASSWORD password of the network
 * @param is_debug Enable debug mode for verbose
 * @return none
 */
void init_wifi_connection(const char* SSID, const char* PASSWORD, bool is_debug)
{
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi network
  WiFi.begin(SSID, PASSWORD);
  if (is_debug) {
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(SSID);
  }

  // Wait for WiFi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (is_debug)
      Serial.print(".");
  }
  WiFi.setAutoReconnect(true);

  if (is_debug) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

