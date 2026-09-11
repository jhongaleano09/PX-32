// Curso PX-32 — Lección 09: una comparación elige una rama.
const int LIMITE = 5;
unsigned int cuenta = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  bool alcanzoLimite = cuenta >= LIMITE;

  Serial.print("Cuenta ");
  Serial.print(cuenta);
  Serial.print(": ");

  if (alcanzoLimite) {
    Serial.println("LIMITE ALCANZADO");
  } else {
    Serial.println("ANTES DEL LIMITE");
  }

  cuenta = cuenta + 1;
  delay(500);
}
