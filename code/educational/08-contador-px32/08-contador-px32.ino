// PX-32 - Leccion 08
// Un contador visible en el Serial Monitor.

int cuenta = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Hola, soy PX-32");
}

void loop() {
  Serial.print("Cuenta: ");
  Serial.println(cuenta);
  cuenta = cuenta + 1;
  delay(1000);
}
