#include <WiFi.h>

WiFiServer server(80);

const char* ssid = "ACNET2";
const char* password = "";

String header;       // Variable para guardar el HTTP request
const int PIN_RELAY = 4 ;

//------------------------CODIGO HTML------------------------------
String pagina = "<!DOCTYPE html>"
                "<html>"
                "<head>"
                "<meta charset='utf-8' />"
                "<title>Servidor Web ESP32</title>"
                "</head>"
                "<body>"
                "<center>"
                "<h1>Comandos del Servidor Web ESP32</h1>"
                "<p><a href='/on'><button style='height:50px;width:100px;color:green'>ON</button></a></p>"
                "<p><a href='/off'><button style='height:50px;width:100px;color:red'>OFF</button></a></p>"
                "</center>"
                "</body>"
                "</html>";


void setup() {
  Serial.begin(115200);
  Serial.println("");

  pinMode(LED_BUILTIN, OUTPUT);
  
  // Conexión WIFI
  WiFi.begin(ssid, password);
  // Cuenta 500 milisegundos para preguntar nuevamente si se pudo conectar
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println(WiFi.localIP());
  server.begin();  // iniciamos el servidor
}

void loop() {
  //WiFiClient client = server.available();  // Escucha a los clientes entrantes. Verifica si hay alguna solicitud de conexión pendiente
  WiFiClient client = server.accept();       // Se declara un objeto client que representa a un navegador web (o dispositivo) que se conecta al ESP32.

  if (client) {                     // Si se conecta un nuevo cliente
    String currentLine = "";        // Se inicializa una cadena vacía para leer línea por línea lo que ese cliente (navegador) está pidiendo.
    while (client.connected()) {    // loop mientras el cliente está conectado
      if (client.available()) {     // si hay bytes para leer desde el cliente

        char c = client.read();     // lee un byte y lo elimina del buffer
        header += c;

        if (c == '\n') {                          // si el byte es un caracter de salto de linea
          if (currentLine.length() == 0) {        // y la línea actual está vacía, significa que terminó el encabezado del mensaje HTTP, y ahora se puede responder
            client.println("HTTP/1.1 200 OK");        // la solicitud HTTP se ha procesado correctamente.
            client.println("Content-type:text/html"); // establece el tipo de contenido que se enviará al cliente en la respuesta. En este caso se trata de una página HTML
            client.println("Connection: close");      // la conexión entre el servidor y el cliente se cerrará después de enviar la respuesta
            client.println();

            // enciende y apaga el GPIO
            if (header.indexOf("GET /on") >= 0) {   // busca la primera aparición de "GET /on" y devuelve la posición donde se encuentra. Si no se encuentra devuelve -1
              digitalWrite(LED_BUILTIN, HIGH);
            } else if (header.indexOf("GET /off") >= 0) {   // busca la primera aparición de "GET /off"
              digitalWrite(LED_BUILTIN, LOW);
            }

            // Muestra la página web
            client.println(pagina);

           
            client.println(); // La respuesta HTTP debe terminar con una linea en blanco, indicando que el contenido finalizó
            break;            // Finaliza el procesamiento del cliente actual. No sigue leyendo más líneas
          } else {
            currentLine = ""; // si tenemos una nueva linea limpiamos currentLine para preparar la lectura de la próxima línea del encabezado HTTP
          }
        } else if (c != '\r') {  // si C es distinto al caracter de retorno de carro
          currentLine += c;      // lo agrega al final de currentLine
        }
      }
    }
    // Mostramos por serial el header y la limpiamos
    Serial.println(header);
    header = "";

    // Cerramos la conexión
    client.stop();
  }
}
