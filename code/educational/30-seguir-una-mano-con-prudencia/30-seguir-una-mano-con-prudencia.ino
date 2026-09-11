// Curso PX-32 - Leccion 30: seguir una mano con dos sensores IR.
// Con MOTOR_ACTIVO en false el programa solo imprime la decision:
// no ordena ningun movimiento.

const bool MOTOR_ACTIVO = false;
const byte POTENCIA_PRUEBA = 65;

// Orden: frontal derecho, frontal izquierdo, trasero derecho,
// trasero izquierdo.
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

const byte SENSOR_IR_IZQUIERDO = 3;
const byte SENSOR_IR_DERECHO = 2;

// Segun la evidencia de tu cuaderno en la Leccion 28: si tu modulo
// entrega HIGH al detectar, cambia LOW por HIGH en esta linea.
const int LECTURA_AL_DETECTAR = LOW;

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

void mover(
  int frontalDerecho,
  int frontalIzquierdo,
  int traseroDerecho,
  int traseroIzquierdo
) {
  controlarMotor(PWM_BK1, BK1_IN1, BK1_IN2, frontalDerecho, POTENCIA_PRUEBA);
  controlarMotor(PWM_BK3, BK3_IN3, BK3_IN4, frontalIzquierdo, POTENCIA_PRUEBA);
  controlarMotor(PWM_AK1, AK1_IN1, AK1_IN2, traseroDerecho, POTENCIA_PRUEBA);
  controlarMotor(PWM_AK3, AK3_IN3, AK3_IN4, traseroIzquierdo, POTENCIA_PRUEBA);
}

void detenerTodos() {
  mover(0, 0, 0, 0);
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

void ordenarAvance() {
  if (MOTOR_ACTIVO) {
    mover(+1, +1, +1, +1);
  } else {
    detenerTodos();
  }
}

void ordenarGiroIzquierda() {
  if (MOTOR_ACTIVO) {
    mover(+1, -1, +1, -1);
  } else {
    detenerTodos();
  }
}

void ordenarGiroDerecha() {
  if (MOTOR_ACTIVO) {
    mover(-1, +1, -1, +1);
  } else {
    detenerTodos();
  }
}

void setup() {
  prepararMotores();
  pinMode(SENSOR_IR_IZQUIERDO, INPUT);
  pinMode(SENSOR_IR_DERECHO, INPUT);
  Serial.begin(9600);

  if (MOTOR_ACTIVO) {
    Serial.println("MODO: MOVIMIENTO ACTIVO");
  } else {
    Serial.println("MODO: SOLO IMPRIMIR");
  }

  // Tres segundos de calma antes de escuchar los sensores.
  delay(3000);
}

void loop() {
  bool izquierdaDetecta =
      digitalRead(SENSOR_IR_IZQUIERDO) == LECTURA_AL_DETECTAR;
  bool derechaDetecta =
      digitalRead(SENSOR_IR_DERECHO) == LECTURA_AL_DETECTAR;

  if (izquierdaDetecta && derechaDetecta) {
    Serial.println("AVANZAR");
    ordenarAvance();
  } else if (izquierdaDetecta) {
    Serial.println("GIRAR A LA IZQUIERDA");
    ordenarGiroIzquierda();
  } else if (derechaDetecta) {
    Serial.println("GIRAR A LA DERECHA");
    ordenarGiroDerecha();
  } else {
    Serial.println("ALTO");
    detenerTodos();
  }

  delay(150);
}
