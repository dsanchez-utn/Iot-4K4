const int touchPin = 13;  // Pin táctil capacitivo a utilizar
const int ledPin = 2;     // Pin digital para controlar el LED

volatile bool touchDetectado = false;  // Variable para indicar si se detectó un toque

void IRAM_ATTR handleTouch() {
  touchDetectado = true;  // Establece la variable touchDetectado como verdadera al detectar un toque
}

// Al marcar un trozo de código con el atributo IRAM_ATTR estamos declarando que 
// el código compilado se colocará en la RAM interna (IRAM) de la ESP32.
// Es más rápida que la memoria Flash

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);  // Configura el pin del LED como salida
  touchAttachInterrupt(digitalPinToInterrupt(touchPin), handleTouch, 500);  // Asigna la función handleTouch como interrupción
}

void loop() {
  Serial.println(touchRead(touchPin));

  if (touchDetectado) {
    digitalWrite(ledPin, !digitalRead(ledPin));  // Cambia el estado del LED al detectar un toque
    Serial.print(digitalRead(ledPin));
    Serial.println("   Cambio de estado del LED");
    delay(1000);  // Agrega un pequeño retardo para evitar detecciones repetidas durante el toque
    touchDetectado = false;  // Restablece la variable touchDetected
  }
  delay(100);
}
