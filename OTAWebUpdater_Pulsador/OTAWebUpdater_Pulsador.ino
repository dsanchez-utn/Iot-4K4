#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include <secrets.h>

const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;

//variables para funcionamiento del pulsador
int pinBoton = 19;        // Pin del Pulsador
int pinLed = 23;          // Pin del Led de la placa de la cátedra
int estadoLed = LOW;     // Estado del LED
int ultimoEstado = HIGH; // Estado anterior del pulsador

//WebServer server(80);
WebServer server(80);
const char* host = "esp32";

#include "OTA.h"


void setup() {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);     // Configurar el pin del LED INTEGRADO como salida
  pinMode(pinLed, OUTPUT);          // Configurar el pin del LED de la placa
  pinMode(pinBoton, INPUT_PULLUP);  // Configurar el pin del pulsador como entrada

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

  // Leer el estado del pulsador
  int lectura = digitalRead(pinBoton);
  // Toma la lectura del pulsador
  if (lectura != ultimoEstado) {

    // Si el pulsador ha sido presionado, cambiar el estado del LED
    if (lectura == HIGH) {
      estadoLed = !estadoLed;
      //digitalWrite(LED_BUILTIN, estadoLed);
      digitalWrite(pinLed, estadoLed);
      //digitalWrite(23, estadoLed);
    }
  }
  // Guardar el último estado del pulsador
  ultimoEstado = lectura;
  delay(50);

}
