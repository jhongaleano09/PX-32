// PX-32 - Leccion 07
// Una variable controla ambas fases del ciclo.

const int pinLed = LED_BUILTIN;
int intervaloMs = 500;

void setup() {
  pinMode(pinLed, OUTPUT);
}

void loop() {
  digitalWrite(pinLed, HIGH);
  delay(intervaloMs);
  digitalWrite(pinLed, LOW);
  delay(intervaloMs);
}
