// Curso PX-32 - Leccion 36: convertir el patron del tracker
// en una posicion con signo.
// Pesos: IR1 = -2 ... IR3 = 0 ... IR5 = +2.

const int PINES[5] = { A4, A3, A2, A1, A0 };

// Ley de tu cuaderno (Leccion 34): que imprime un canal sobre negro.
// Si tu tracker imprime 1 sobre negro, cambia LOW por HIGH.
const int LECTURA_SOBRE_NEGRO = LOW;

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(PINES[i], INPUT);
  }
  Serial.begin(9600);
}

void loop() {
  int sumaDePesos = 0;
  int cuantosVenLinea = 0;

  for (int i = 0; i < 5; i++) {
    if (digitalRead(PINES[i]) == LECTURA_SOBRE_NEGRO) {
      sumaDePesos = sumaDePesos + (i - 2);
      cuantosVenLinea = cuantosVenLinea + 1;
    }
  }

  for (int i = 0; i < 5; i++) {
    Serial.print(digitalRead(PINES[i]));
  }

  if (cuantosVenLinea == 0) {
    Serial.println("   linea perdida");
  } else {
    float posicion = float(sumaDePesos) / cuantosVenLinea;
    Serial.print("   posicion: ");
    Serial.println(posicion, 1);
  }

  delay(200);
}
