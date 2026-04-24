#include <WiFi.h>
#include "secrets.h"
#include <ThingSpeak.h>
#include <Ticker.h>

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
WiFiClient  client;

// variables de canal público
unsigned long nroCanalPublico = SECRET_CH_ID_PUBLIC;
unsigned int nroCampoPublico = 2;

// variables de canal privado
unsigned long nroCanalPrivado = SECRET_CH_ID_PRIVATE;
const char * ReadAPIKey = SECRET_READ_APIKEY;
unsigned int nroCampoPrivado = 2; 
Ticker mostrarDatos;

void setup() {
  Serial.begin(115200);

  ThingSpeak.begin(client);
  mostrarDatos.attach(10, realizarLectura);
  // Connecta a WiFi
  conectarWiFi();
}

void loop() {

}

void realizarLectura() {

  if(WiFi.status() != WL_CONNECTED){
    conectarWiFi();
  }

  // Lee un campo de Canal Privado
  float temperatureInF = ThingSpeak.readFloatField(nroCanalPublico, nroCampoPublico);
  //float temperatureInF = ThingSpeak.readFloatField(nroCanalPrivado, nroCampoPrivado, ReadAPIKey);
  // Checkea lectura
  int statusCode = ThingSpeak.getLastReadStatus();
  if(statusCode == 200){
    Serial.println("Temperatura en Canal de ThingSpeak: " + String(temperatureInF) + " °C");
  }
  else{
    Serial.println("Problemas leyendo el canal. HTTP error code " + String(statusCode)); 
  }
}

void conectarWiFi(){
  Serial.print("\nConectando a: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);     
  } 
  Serial.println("\nConectado a WiFi");
}

//Secret Key    JcExn9qqy#4odxGge!anfDNvi
//DEVICE ID     f7007162-2359-48fe-8fd0-7b3373e57ed9
