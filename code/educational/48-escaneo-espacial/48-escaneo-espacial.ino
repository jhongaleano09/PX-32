// Curso PX-32 - Leccion 48: escaneo espacial.
// Mover, esperar el asentamiento, medir, informar: tres direcciones.

#include <Servo.h>

const byte TRIG = 30;
const byte ECHO = 31;
const byte PIN_SERVO = 13;
const unsigned long TIMEOUT_US = 30000UL;
const float SONIDO_CM_POR_US = 0.0343;

Servo cabeza;

// Los tres angulos del barrido (array como en la Leccion 35).
const int ANGULOS[3] = { 45, 90, 135 };

float medirDistanciaCm() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  unsigned long us = pulseIn(ECHO, HIGH, TIMEOUT_US);

  if (us == 0 || us > 23200UL) {
    return -1.0;  // -1 = lectura no fiable (convenio de esta leccion)
  }

  return us * SONIDO_CM_POR_US / 2.0;
}

void setup() {
  pinMode(TRIG, OUTPUT);
  digitalWrite(TRIG, LOW);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);
  cabeza.attach(PIN_SERVO);
  cabeza.write(90);  // empezar mirando al frente
  delay(1000);
  Serial.println("Leccion 48: escaneo 45 / 90 / 135.");
}

void loop() {
  for (byte i = 0; i < 3; i++) {
    cabeza.write(ANGULOS[i]);
    delay(500);  // asentamiento: la mecanica necesita su tiempo

    float cm = medirDistanciaCm();

    Serial.print("angulo ");
    Serial.print(ANGULOS[i]);
    Serial.print(": ");

    if (cm < 0) {
      Serial.println("sin eco fiable");
    } else {
      Serial.print(cm, 1);
      Serial.println(" cm");
    }
  }

  Serial.println("--- barrido completo: vuelta al frente ---");
  cabeza.write(90);
  delay(1500);
}
