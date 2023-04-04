#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include "secrets.h"

const char* host = "143.215.123.121"; // your local machine's public IP address
const int port = 5000; // the port your Flask app is listening on

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("FUUU");

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.print("Connecting to ");
  Serial.print(host);
  Serial.print(":");
  Serial.println(port);

  WiFiClient client;

  if (client.connect(host, port)) {
    Serial.println("Connected to server");

    // Make a GET request to the /my-endpoint endpoint
    client.println("GET /my-endpoint HTTP/1.1");
    client.println("Host: " + String(host));
    client.println("Connection: close");
    client.println();

    // Wait for response from server
    while (client.connected()) {
      if (client.available()) {
        String line = client.readStringUntil('\n');
        Serial.println(line);
      }
    }

    Serial.println();
    Serial.println("Closing connection");
    client.stop();
  } else {
    Serial.println("Connection failed");
  }

  delay(5000);
}
