// Curso PX-32 - Leccion 37: del patron a la orden, sin tocar motores.
// Tres funciones, tres empleos: reportar, estimar y decidir.
// La orden solo se imprime: ningun pin de motor existe aqui.

const int PINES[5] = { A4, A3, A2, A1, A0 };

// Ley de tu cuaderno (Leccion 34): que imprime un canal sobre negro.
const int LECTURA_SOBRE_NEGRO = LOW;

// Banda de tolerancia: cuanto perdonamos antes de corregir.
const float TOLERANCIA = 0.4;

// La llena estimarPosicion() y la lee elegirOrden():
// el puente de datos entre las dos funciones.
int cuantosVenLinea;

void imprimirPatron() {
  for (int i = 0; i < 5; i++) {
    Serial.print(digitalRead(PINES[i]));
  }
}

float estimarPosicion() {
  int sumaDePesos = 0;
  cuantosVenLinea = 0;

  for (int i = 0; i < 5; i++) {
    if (digitalRead(PINES[i]) == LECTURA_SOBRE_NEGRO) {
      sumaDePesos = sumaDePesos + (i - 2);
      cuantosVenLinea = cuantosVenLinea + 1;
    }
  }

  if (cuantosVenLinea == 0) {
    return 0;
  }

  return float(sumaDePesos) / cuantosVenLinea;
}

void elegirOrden(float posicion) {
  if (cuantosVenLinea == 0) {
    Serial.println(" -> STOP: linea perdida");
  } else if (cuantosVenLinea == 5) {
    Serial.println(" -> STOP: patron ambiguo");
  } else if (posicion < -TOLERANCIA) {
    Serial.println(" -> CORRIGE hacia IR1");
  } else if (posicion > TOLERANCIA) {
    Serial.println(" -> CORRIGE hacia IR5");
  } else {
    Serial.println(" -> AVANZA");
  }
}

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(PINES[i], INPUT);
  }
  Serial.begin(9600);
}

void loop() {
  imprimirPatron();
  float posicion = estimarPosicion();
  elegirOrden(posicion);
  Serial.println();
  delay(300);
}
