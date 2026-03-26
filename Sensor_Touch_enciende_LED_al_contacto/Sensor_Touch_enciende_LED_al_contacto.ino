const int touchPin = 13; 
const int ledPin = 2;

const int limite = 500; // valor limite con el que cambia de estado
int valorTouch;        // almacena el valor del pin Touch 


void setup(){
  Serial.begin(115200);
  delay(3000);
  pinMode (ledPin, OUTPUT);
  Serial.println("Sensor Touch controla LED");
}

void loop(){
  valorTouch = touchRead(touchPin);
  Serial.print(valorTouch);
  
  if(valorTouch < limite){
    digitalWrite(ledPin, HIGH);  // enciende el LED
    Serial.println(" - LED encendido");
  }
  else{
    digitalWrite(ledPin, LOW);  // apaga el LED
    Serial.println(" - LED apagado");
  }
  delay(500);
}