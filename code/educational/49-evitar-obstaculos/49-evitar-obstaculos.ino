// Curso PX-32 - Leccion 49: evitar obstaculos (hito del bloque).
// Politica: STOP primero, mirar los dos lados y girar solo
// con evidencia. Ninguna lectura no fiable autoriza avanzar.

#include <Servo.h>

// FASE A: false -> solo imprime las decisiones.
// FASE B y C: true -> las ejecuta con los motores.
const bool MOTOR_ACTIVO = false;

// Tu evidencia de la Leccion 48: con el sensor mirando al frente,
// el angulo 45 apunta hacia TU izquierda? (true o false)
const bool GRADOS_45_MIRA_A_TU_IZQUIERDA = true;

const float DISTANCIA_SEGURA_CM = 25.0;
const byte POTENCIA_AVANCE = 60;
const byte POTENCIA_GIRO = 55;

// Orden de los motores: frontal derecho, frontal izquierdo,
// trasero derecho, trasero izquierdo (Lecciones 20 y 38).
const byte PWM_BK1 = 9;   // Frontal derecho
const byte BK1_IN1 = 22;
const byte BK1_IN2 = 24;
const byte PWM_BK3 = 10;  // Frontal izquierdo
const byte BK3_IN3 = 26;
const byte BK3_IN4 = 28;
const byte PWM_AK1 = 11;  // Trasero derecho
const byte AK1_IN1 = 5;
const byte AK1_IN2 = 6;
const byte PWM_AK3 = 12;  // Trasero izquierdo
const byte AK3_IN3 = 7;
const byte AK3_IN4 = 8;

const byte TRIG = 30;
const byte ECHO = 31;
const byte PIN_SERVO = 13;
const unsigned long TIMEOUT_US = 30000UL;
const float SONIDO_CM_POR_US = 0.0343;

Servo cabeza;

void controlarMotor(
  byte pinPwm,
  byte pin1,
  byte pin2,
  int sentido,
  byte potenciaPwm
) {
  if (sentido > 0) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    analogWrite(pinPwm, potenciaPwm);
  } else if (sentido < 0) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    analogWrite(pinPwm, potenciaPwm);
  } else {
    analogWrite(pinPwm, 0);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }
}

void moverConPotencia(
  int frontalDerecho,
  int frontalIzquierdo,
  int traseroDerecho,
  int traseroIzquierdo,
  byte potenciaPwm
) {
  controlarMotor(PWM_BK1, BK1_IN1, BK1_IN2, frontalDerecho, potenciaPwm);
  controlarMotor(PWM_BK3, BK3_IN3, BK3_IN4, frontalIzquierdo, potenciaPwm);
  controlarMotor(PWM_AK1, AK1_IN1, AK1_IN2, traseroDerecho, potenciaPwm);
  controlarMotor(PWM_AK3, AK3_IN3, AK3_IN4, traseroIzquierdo, potenciaPwm);
}

void detenerTodos() {
  moverConPotencia(0, 0, 0, 0, 0);
}

void prepararMotores() {
  pinMode(PWM_BK1, OUTPUT);
  pinMode(PWM_BK3, OUTPUT);
  pinMode(PWM_AK1, OUTPUT);
  pinMode(PWM_AK3, OUTPUT);
  pinMode(BK1_IN1, OUTPUT);
  pinMode(BK1_IN2, OUTPUT);
  pinMode(BK3_IN3, OUTPUT);
  pinMode(BK3_IN4, OUTPUT);
  pinMode(AK1_IN1, OUTPUT);
  pinMode(AK1_IN2, OUTPUT);
  pinMode(AK3_IN3, OUTPUT);
  pinMode(AK3_IN4, OUTPUT);
  detenerTodos();
}

void avanzar() {
  moverConPotencia(+1, +1, +1, +1, POTENCIA_AVANCE);
}

void girarHaciaLaIzquierda() {
  moverConPotencia(+1, -1, +1, -1, POTENCIA_GIRO);
}

void girarHaciaLaDerecha() {
  moverConPotencia(-1, +1, -1, +1, POTENCIA_GIRO);
}

void girarHaciaElLadoDe45() {
  if (GRADOS_45_MIRA_A_TU_IZQUIERDA) {
    girarHaciaLaIzquierda();
  } else {
    girarHaciaLaDerecha();
  }
}

void girarHaciaElLadoDe135() {
  if (GRADOS_45_MIRA_A_TU_IZQUIERDA) {
    girarHaciaLaDerecha();
  } else {
    girarHaciaLaIzquierda();
  }
}

float medirDistanciaCm() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  unsigned long us = pulseIn(ECHO, HIGH, TIMEOUT_US);

  if (us == 0 || us > 23200UL) {
    return -1.0;  // lectura no fiable: se trata como riesgo
  }

  return us * SONIDO_CM_POR_US / 2.0;
}

void setup() {
  prepararMotores();
  pinMode(TRIG, OUTPUT);
  digitalWrite(TRIG, LOW);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);
  cabeza.attach(PIN_SERVO);
  cabeza.write(90);  // alineacion: sensor mirando al frente
  delay(1000);

  if (MOTOR_ACTIVO) {
    Serial.println("MODO: EVASION ACTIVA");
  } else {
    Serial.println("MODO: SOLO IMPRIMIR");
  }

  if (GRADOS_45_MIRA_A_TU_IZQUIERDA) {
    Serial.println("angulo 45 mira a la IZQUIERDA (segun tu cuaderno)");
  } else {
    Serial.println("angulo 45 mira a la DERECHA (segun tu cuaderno)");
  }

  delay(3000);  // tres segundos de calma antes de empezar
}

void loop() {
  float frente = medirDistanciaCm();

  if (frente < 0 || frente < DISTANCIA_SEGURA_CM) {
    // 1) STOP: siempre antes que cualquier maniobra.
    detenerTodos();
    Serial.println("STOP: obstaculo o lectura no fiable");

    // 2) Mirar los dos lados con la cabeza.
    cabeza.write(45);
    delay(500);
    float lado45 = medirDistanciaCm();

    cabeza.write(135);
    delay(500);
    float lado135 = medirDistanciaCm();

    cabeza.write(90);
    delay(300);

    Serial.print("angulo 45: ");
    if (lado45 < 0) {
      Serial.println("no fiable");
    } else {
      Serial.print(lado45, 1);
      Serial.println(" cm");
    }

    Serial.print("angulo 135: ");
    if (lado135 < 0) {
      Serial.println("no fiable");
    } else {
      Serial.print(lado135, 1);
      Serial.println(" cm");
    }

    // 3) Elegir con evidencia: lado libre y fiable, o nada.
    bool libre45 = (lado45 >= DISTANCIA_SEGURA_CM);
    bool libre135 = (lado135 >= DISTANCIA_SEGURA_CM);

    if (!libre45 && !libre135) {
      Serial.println("AMBOS LADOS BLOQUEADOS: me quedo en STOP");
    } else if (libre45 && (!libre135 || lado45 >= lado135)) {
      Serial.println("GIRO hacia el lado del angulo 45");
      if (MOTOR_ACTIVO) {
        girarHaciaElLadoDe45();
        delay(350);
        detenerTodos();
      }
    } else {
      Serial.println("GIRO hacia el lado del angulo 135");
      if (MOTOR_ACTIVO) {
        girarHaciaElLadoDe135();
        delay(350);
        detenerTodos();
      }
    }
  } else {
    Serial.println("LIBRE: avanzar");
    if (MOTOR_ACTIVO) {
      avanzar();
    }
  }

  delay(40);
}
