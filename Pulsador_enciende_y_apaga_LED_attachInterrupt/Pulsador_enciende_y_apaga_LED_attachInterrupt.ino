struct Button {
  const uint8_t PIN;
  uint32_t numberKeyPresses;
  bool pressed;
};

Button button1 = {19, 0, false};

void IRAM_ATTR isr() {
  static uint32_t lastMillis = 0;
  if (millis() - lastMillis > 500) {
    lastMillis = millis();
    button1.numberKeyPresses += 1;
    button1.pressed = true;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(button1.PIN, INPUT_PULLUP);
  attachInterrupt(button1.PIN, isr, FALLING);
}

void loop() {
  if (button1.pressed) {
      Serial.printf("El pulsador fue presionado %u veces\n", button1.numberKeyPresses);
      button1.pressed = false;
  }

  //Detach Interrupt after 1 Minute
}