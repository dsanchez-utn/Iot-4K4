
const int potePin = 32;  //Pin del potenciometro
volatile int estadoPote;

void setup(){
  Serial.begin(115200);
  pinMode(potePin, INPUT);
  pinMode(23, OUTPUT);  
  analogWriteResolution(23, 8);
  analogReadResolution(8);
  //analogWriteResolution(2, 10);
}

void loop(){
  estadoPote = analogRead(potePin);
//  analogWrite(23, estadoPote);
  analogWrite(2, map(analogRead(potePin),0 ,255, 255, 0));
  Serial.println(estadoPote);
  delay(100);
}



//    VER RESOLUCION











//  analogWrite(LED_BUILTIN, map(analogRead(potePin),0 ,4095, 255, 0));
