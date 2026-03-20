const short  PIN_PULSADOR = 19;  // tomado de la configuración de la placa de la cátedra

bool encendido = true;

void setup() {
  Serial.begin(115200);
  Serial.println("Hola, 4K4!");
  delay(1000);
  pinMode(PIN_PULSADOR, INPUT_PULLUP); // *
  pinMode(LED_BUILTIN, OUTPUT); 
  digitalWrite(LED_BUILTIN, encendido);   // actúa sobre el LED;
}


void loop() {
  encendido = digitalRead(PIN_PULSADOR); // lee estado llave
  digitalWrite(LED_BUILTIN, encendido);   // actúa sobre el LED;

  Serial.print("Lectura del Pulsador: ");
  Serial.print(digitalRead(PIN_PULSADOR)); 
  Serial.print("    LED: ");
  if (digitalRead(PIN_PULSADOR) == HIGH) {
    Serial.println("ENCENDIDO!");
  } else {
    Serial.println("Apagado");
  }
  delay(100);
}
