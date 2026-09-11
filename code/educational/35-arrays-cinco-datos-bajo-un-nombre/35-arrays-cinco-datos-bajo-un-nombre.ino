// Curso PX-32 - Leccion 35: el mismo patron de la Leccion 34,
// ahora con un array y un bucle for.
// PINES[0] es IR1 (A4) ... PINES[4] es IR5 (A0).

const int PINES[5] = { A4, A3, A2, A1, A0 };

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(PINES[i], INPUT);
  }
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 5; i++) {
    Serial.print(digitalRead(PINES[i]));
  }
  Serial.println();

  delay(200);
}
