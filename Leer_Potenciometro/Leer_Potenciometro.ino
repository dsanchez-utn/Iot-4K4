

const int potePin = 32;  //Pin del potenciometro
volatile int estadoPote;

void setup(){
  Serial.begin(115200);
  delay(1000);
  Serial.println();
  Serial.println("Lecturas de Potenciometro");
  pinMode(potePin, INPUT); 
}

void loop(){
  estadoPote=analogRead(potePin);
  Serial.println(estadoPote);
  delay(100);
}







/*

//  printf("Valor del sensor: %d   %i   \n", estadoPote, potePin);

/n  salto de línea

%d o %i valores enteros con signo.
%u valores enteros sin signo.
%f  valores de punto flotante.
%s cadenas de caracteres.
%c caracteres individuales.
%x valores enteros en formato hexadecimal.
%e valores de punto flotante en notación científica.


//#include <stdio.h>


*/


