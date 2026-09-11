// Curso PX-32 — Lección 06: primer Blink seguro.
const int PIN_LED = LED_BUILTIN;

void setup() {
  // D13 producirá la señal para el LED integrado.
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  digitalWrite(PIN_LED, HIGH);  // Enciende el LED L.
  delay(500);                   // Mantiene la luz medio segundo.

  digitalWrite(PIN_LED, LOW);   // Apaga el LED L.
  delay(500);                   // Mantiene la oscuridad medio segundo.
}
