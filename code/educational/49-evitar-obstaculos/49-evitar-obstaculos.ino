// Curso PX-32 - Leccion 49: evitar obstaculos (hito del bloque).
// Politica: STOP primero, medir tres veces y mover solo con evidencia.
// Ninguna lectura no fiable autoriza avanzar o continuar un giro.

#include <Servo.h>

// El movimiento esta habilitado, pero siempre subordinado a los sensores.
const bool MOTOR_ACTIVO = true;

// Ajustar despues de comprobar fisicamente hacia donde apunta el servo.
const bool GRADOS_45_MIRA_A_TU_IZQUIERDA = true;

const float DISTANCIA_SEGURA_CM = 25.0;
const float DISTANCIA_PELIGRO_GIRO_CM = 12.0;
const byte POTENCIA_AVANCE = 60;
const byte POTENCIA_GIRO = 55;
const byte POTENCIA_PRUEBA_MOTOR = 45;
const unsigned int DURACION_PRUEBA_MOTOR_MS = 300;
const unsigned int DURACION_GIRO_MS = 420;
const unsigned int PASO_VIGILANCIA_GIRO_MS = 60;

// Orden: frontal derecho, frontal izquierdo, trasero derecho,
// trasero izquierdo.
const byte PWM_BK1 = 9;
const byte BK1_IN1 = 22;
const byte BK1_IN2 = 24;
const byte PWM_BK3 = 10;
const byte BK3_IN3 = 26;
const byte BK3_IN4 = 28;
const byte PWM_AK1 = 11;
const byte AK1_IN1 = 5;
const byte AK1_IN2 = 6;
const byte PWM_AK3 = 12;
const byte AK3_IN3 = 7;
const byte AK3_IN4 = 8;

const byte TRIG = 30;
const byte ECHO = 31;
const byte PIN_SERVO = 13;
const unsigned long TIMEOUT_US = 30000UL;
const float SONIDO_CM_POR_US = 0.0343;
const byte CANTIDAD_LECTURAS = 3;
const unsigned int PAUSA_ENTRE_LECTURAS_MS = 25;

const byte ANGULO_45 = 45;
const byte ANGULO_FRENTE = 90;
const byte ANGULO_135 = 135;
const unsigned int ESPERA_SERVO_BASE_MS = 60;
const unsigned int ESPERA_SERVO_POR_GRADO_MS = 3;

enum DecisionMovimiento {
  DECISION_DETENER,
  DECISION_AVANZAR,
  DECISION_GIRAR_45,
  DECISION_GIRAR_135
};

Servo cabeza;
byte anguloActualServo = ANGULO_FRENTE;
bool sistemaArmado = false;

// ---------------- Movimiento ----------------

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

void avanzar() {
  if (MOTOR_ACTIVO && sistemaArmado) {
    moverConPotencia(+1, +1, +1, +1, POTENCIA_AVANCE);
  } else {
    detenerTodos();
  }
}

void girarHaciaLaIzquierda() {
  if (MOTOR_ACTIVO && sistemaArmado) {
    moverConPotencia(+1, -1, +1, -1, POTENCIA_GIRO);
  } else {
    detenerTodos();
  }
}

void girarHaciaLaDerecha() {
  if (MOTOR_ACTIVO && sistemaArmado) {
    moverConPotencia(-1, +1, -1, +1, POTENCIA_GIRO);
  } else {
    detenerTodos();
  }
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

void probarMotor(byte numeroMotor) {
  sistemaArmado = false;
  detenerTodos();

  Serial.print("PRUEBA MOTOR ");
  Serial.print(numeroMotor);
  Serial.println(": 300 ms a baja potencia");

  if (numeroMotor == 1) {
    controlarMotor(PWM_BK1, BK1_IN1, BK1_IN2, +1, POTENCIA_PRUEBA_MOTOR);
  } else if (numeroMotor == 2) {
    controlarMotor(PWM_BK3, BK3_IN3, BK3_IN4, +1, POTENCIA_PRUEBA_MOTOR);
  } else if (numeroMotor == 3) {
    controlarMotor(PWM_AK1, AK1_IN1, AK1_IN2, +1, POTENCIA_PRUEBA_MOTOR);
  } else if (numeroMotor == 4) {
    controlarMotor(PWM_AK3, AK3_IN3, AK3_IN4, +1, POTENCIA_PRUEBA_MOTOR);
  }

  delay(DURACION_PRUEBA_MOTOR_MS);
  detenerTodos();
  Serial.println("PRUEBA TERMINADA: todos los motores en STOP");
}

// ---------------- Medicion ----------------

void apuntarSensor(byte anguloDestino) {
  int desplazamiento = abs((int)anguloDestino - (int)anguloActualServo);
  cabeza.write(anguloDestino);

  // La espera baja automaticamente para recorridos cortos y evita los
  // delay fijos de 500 ms. Un recorrido mayor conserva tiempo suficiente.
  delay(ESPERA_SERVO_BASE_MS + desplazamiento * ESPERA_SERVO_POR_GRADO_MS);
  anguloActualServo = anguloDestino;
}

float medirUnaDistanciaCm() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  unsigned long duracionUs = pulseIn(ECHO, HIGH, TIMEOUT_US);
  if (duracionUs == 0 || duracionUs > 23200UL) {
    return -1.0;
  }

  return duracionUs * SONIDO_CM_POR_US / 2.0;
}

float calcularMedianaDeTres(float a, float b, float c) {
  if ((a <= b && b <= c) || (c <= b && b <= a)) {
    return b;
  }
  if ((b <= a && a <= c) || (c <= a && a <= b)) {
    return a;
  }
  return c;
}

float medirDistanciaMedianaCm() {
  float lecturas[CANTIDAD_LECTURAS];

  for (byte i = 0; i < CANTIDAD_LECTURAS; i++) {
    lecturas[i] = medirUnaDistanciaCm();

    // Una muestra ausente vuelve inseguro al grupo completo.
    if (lecturas[i] < 0) {
      return -1.0;
    }

    if (i + 1 < CANTIDAD_LECTURAS) {
      delay(PAUSA_ENTRE_LECTURAS_MS);
    }
  }

  return calcularMedianaDeTres(lecturas[0], lecturas[1], lecturas[2]);
}

bool distanciaEsSegura(float distanciaCm, float umbralCm) {
  return distanciaCm >= umbralCm;
}

void imprimirDistancia(const char *etiqueta, float distanciaCm) {
  Serial.print(etiqueta);
  if (distanciaCm < 0) {
    Serial.println("NO FIABLE");
  } else {
    Serial.print(distanciaCm, 1);
    Serial.println(" cm");
  }
}

void procesarComandosSerial() {
  while (Serial.available() > 0) {
    char comando = Serial.read();

    if ((comando == 'A' || comando == 'a') && MOTOR_ACTIVO) {
      sistemaArmado = true;
      Serial.println("SISTEMA ARMADO: motores autorizados");
    } else if (comando == 'S' || comando == 's') {
      sistemaArmado = false;
      detenerTodos();
      Serial.println("STOP MANUAL: sistema desarmado");
    } else if (comando >= '1' && comando <= '4') {
      probarMotor(comando - '0');
    }
  }
}

// ---------------- Decision ----------------

DecisionMovimiento decidirEvasion(float lado45, float lado135) {
  bool libre45 = distanciaEsSegura(lado45, DISTANCIA_SEGURA_CM);
  bool libre135 = distanciaEsSegura(lado135, DISTANCIA_SEGURA_CM);

  if (!libre45 && !libre135) {
    return DECISION_DETENER;
  }
  if (libre45 && (!libre135 || lado45 >= lado135)) {
    return DECISION_GIRAR_45;
  }
  return DECISION_GIRAR_135;
}

void ordenarGiro(DecisionMovimiento decision) {
  bool girarHaciaIzquierda =
    (decision == DECISION_GIRAR_45 && GRADOS_45_MIRA_A_TU_IZQUIERDA) ||
    (decision == DECISION_GIRAR_135 && !GRADOS_45_MIRA_A_TU_IZQUIERDA);

  if (girarHaciaIzquierda) {
    girarHaciaLaIzquierda();
  } else {
    girarHaciaLaDerecha();
  }
}

bool ejecutarGiroVigilado(DecisionMovimiento decision) {
  byte anguloElegido =
    decision == DECISION_GIRAR_45 ? ANGULO_45 : ANGULO_135;
  apuntarSensor(anguloElegido);

  unsigned long inicioGiroMs = millis();
  while (millis() - inicioGiroMs < DURACION_GIRO_MS) {
    ordenarGiro(decision);
    delay(PASO_VIGILANCIA_GIRO_MS);

    float distanciaDuranteGiro = medirDistanciaMedianaCm();
    if (!distanciaEsSegura(distanciaDuranteGiro, DISTANCIA_PELIGRO_GIRO_CM)) {
      detenerTodos();
      imprimirDistancia("PELIGRO DURANTE GIRO: ", distanciaDuranteGiro);
      return false;
    }
  }

  detenerTodos();
  apuntarSensor(ANGULO_FRENTE);

  // No se vuelve a avanzar hasta verificar el nuevo frente.
  float frenteDespuesDelGiro = medirDistanciaMedianaCm();
  imprimirDistancia("FRENTE DESPUES DEL GIRO: ", frenteDespuesDelGiro);

  if (!distanciaEsSegura(frenteDespuesDelGiro, DISTANCIA_SEGURA_CM)) {
    Serial.println("STOP: el nuevo frente no es seguro");
    return false;
  }

  Serial.println("GIRO COMPLETADO: nuevo frente seguro");
  return true;
}

void evaluarYActuar() {
  apuntarSensor(ANGULO_FRENTE);
  float frente = medirDistanciaMedianaCm();
  imprimirDistancia("FRENTE: ", frente);

  if (distanciaEsSegura(frente, DISTANCIA_SEGURA_CM)) {
    Serial.println("DECISION: AVANZAR");
    avanzar();
    return;
  }

  detenerTodos();
  Serial.println("DECISION: STOP Y EXPLORAR");

  apuntarSensor(ANGULO_45);
  float lado45 = medirDistanciaMedianaCm();
  apuntarSensor(ANGULO_135);
  float lado135 = medirDistanciaMedianaCm();

  imprimirDistancia("LADO 45: ", lado45);
  imprimirDistancia("LADO 135: ", lado135);

  DecisionMovimiento decision = decidirEvasion(lado45, lado135);
  if (decision == DECISION_DETENER) {
    apuntarSensor(ANGULO_FRENTE);
    Serial.println("DECISION: AMBOS LADOS BLOQUEADOS; STOP");
    return;
  }

  if (decision == DECISION_GIRAR_45) {
    Serial.println("DECISION: GIRAR HACIA EL LADO 45");
  } else {
    Serial.println("DECISION: GIRAR HACIA EL LADO 135");
  }

  ejecutarGiroVigilado(decision);
}

void setup() {
  prepararMotores();
  pinMode(TRIG, OUTPUT);
  digitalWrite(TRIG, LOW);
  pinMode(ECHO, INPUT);

  Serial.begin(9600);
  cabeza.attach(PIN_SERVO);
  cabeza.write(ANGULO_FRENTE);
  anguloActualServo = ANGULO_FRENTE;
  delay(600);

  Serial.println("PX-32: EVASION ACTIVA CON MEDIANA DE 3");
  Serial.println("Seguridad: una lectura no fiable siempre produce STOP");
  Serial.println("Comandos: A = armar motores; S = STOP y desarmar");
  Serial.println("Pruebas con ruedas levantadas: 1, 2, 3 o 4 = un motor");
  Serial.println("ESTADO INICIAL: DESARMADO");
  delay(3000);
}

void loop() {
  procesarComandosSerial();
  evaluarYActuar();
  delay(40);
}
