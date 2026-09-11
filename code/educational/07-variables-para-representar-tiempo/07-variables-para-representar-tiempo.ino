// Curso PX-32 — Lección 07: una variable representa el tiempo.
const int PIN_LED = LED_BUILTIN;
int intervaloMs = 500;

void setup() {
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  digitalWrite(PIN_LED, HIGH);
  delay(intervaloMs);

  digitalWrite(PIN_LED, LOW);
  delay(intervaloMs);
}
