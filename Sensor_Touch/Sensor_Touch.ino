
// ESP32 Touch Test
// Touch0 es T4 en el pin GPIO 13.

void setup() {

  Serial.begin(115200);
  delay(1000);
  Serial.println("Sensor Touch");
}

void loop() {
  Serial.println(touchRead(T4));  // toma valor del Touch 4 pin = GPIO13
  delay(100);
}