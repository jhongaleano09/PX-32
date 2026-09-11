// Curso PX-32 - Leccion 29: dos sensores IR, cuatro situaciones.

const byte SENSOR_IR_IZQUIERDO = 3;
const byte SENSOR_IR_DERECHO = 2;

// Segun la evidencia de tu cuaderno en la Leccion 28: si tu modulo
// entrega HIGH al detectar, cambia LOW por HIGH en esta linea.
const int LECTURA_AL_DETECTAR = LOW;

void setup() {
  pinMode(SENSOR_IR_IZQUIERDO, INPUT);
  pinMode(SENSOR_IR_DERECHO, INPUT);
  Serial.begin(9600);
}

void loop() {
  bool izquierdaDetecta =
      digitalRead(SENSOR_IR_IZQUIERDO) == LECTURA_AL_DETECTAR;
  bool derechaDetecta =
      digitalRead(SENSOR_IR_DERECHO) == LECTURA_AL_DETECTAR;

  if (izquierdaDetecta && derechaDetecta) {
    Serial.println("AMBOS DETECTAN");
  } else if (izquierdaDetecta) {
    Serial.println("SOLO IZQUIERDA");
  } else if (derechaDetecta) {
    Serial.println("SOLO DERECHA");
  } else {
    Serial.println("NINGUNO DETECTA");
  }

  delay(300);
}
