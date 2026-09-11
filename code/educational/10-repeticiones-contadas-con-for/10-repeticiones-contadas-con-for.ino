// Curso PX-32 — Lección 10: contar destellos con for.
const int DESTELLOS = 4;
const int INTERVALO_MS = 150;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  for (int contador = 0; contador < DESTELLOS; contador = contador + 1) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(INTERVALO_MS);

    digitalWrite(LED_BUILTIN, LOW);
    delay(INTERVALO_MS);
  }

  delay(1500);  // Separa un grupo del siguiente.
}
