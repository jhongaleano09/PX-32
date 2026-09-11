// Curso PX-32 — Lección 11: funciones con parámetros y retorno.
void parpadear(int veces, unsigned long intervaloMs) {
  for (int contador = 0; contador < veces; contador = contador + 1) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(intervaloMs);

    digitalWrite(LED_BUILTIN, LOW);
    delay(intervaloMs);
  }
}

unsigned long duracionGrupoMs(int veces, unsigned long intervaloMs) {
  return veces * intervaloMs * 2;
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  const int VECES = 3;
  const unsigned long INTERVALO_MS = 200;

  Serial.print("Duracion calculada del grupo: ");
  Serial.print(duracionGrupoMs(VECES, INTERVALO_MS));
  Serial.println(" ms");

  parpadear(VECES, INTERVALO_MS);
  delay(1500);
}
