// Curso PX-32 - Leccion 34: leer los cinco canales del tracker
// e imprimirlos como un patron de cinco digitos.
// El digito de la izquierda es IR1; el de la derecha, IR5.

const int CANAL_IR1 = A4;
const int CANAL_IR2 = A3;
const int CANAL_IR3 = A2;
const int CANAL_IR4 = A1;
const int CANAL_IR5 = A0;

void setup() {
  pinMode(CANAL_IR1, INPUT);
  pinMode(CANAL_IR2, INPUT);
  pinMode(CANAL_IR3, INPUT);
  pinMode(CANAL_IR4, INPUT);
  pinMode(CANAL_IR5, INPUT);
  Serial.begin(9600);
}

void loop() {
  int lecturaIR1 = digitalRead(CANAL_IR1);
  int lecturaIR2 = digitalRead(CANAL_IR2);
  int lecturaIR3 = digitalRead(CANAL_IR3);
  int lecturaIR4 = digitalRead(CANAL_IR4);
  int lecturaIR5 = digitalRead(CANAL_IR5);

  Serial.print(lecturaIR1);
  Serial.print(lecturaIR2);
  Serial.print(lecturaIR3);
  Serial.print(lecturaIR4);
  Serial.println(lecturaIR5);

  delay(200);
}
