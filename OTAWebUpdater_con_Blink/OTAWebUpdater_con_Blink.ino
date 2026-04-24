#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include "secrets.h"

const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;

//variables to blink without delay:
const int led = 2;
unsigned long previousMillis = 0;
const long interval = 1000;
int ledState = LOW;

WebServer server(80);
const char* host = "esp32";

#include "OTA.h"


void setup(void) {
  Serial.begin(115200);

  //Code to blink without delay:
  pinMode(led, OUTPUT);

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  iniciaOTA();
}

void loop(void) {
  server.handleClient();
  delay(1);

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    ledState = not(ledState);

    digitalWrite(led, ledState);
  }

}
