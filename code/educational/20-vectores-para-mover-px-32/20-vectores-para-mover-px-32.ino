// Curso PX-32 - Leccion 20: seis movimientos Mecanum.
// El sketch queda detenido hasta cambiar EJECUTAR_PRUEBA a true.
const bool EJECUTAR_PRUEBA = false;

// false: prueba los seis patrones con las ruedas elevadas.
// true: prueba solo avance y lateral derecho sobre piso despejado.
const bool PRUEBA_EN_SUELO = false;

const byte POTENCIA_PWM = 100;

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
  controlarMotor(PWM_BK1, BK1_IN1, BK1_IN2, frontalDerecho, POTENCIA_PWM);
  controlarMotor(PWM_BK3, BK3_IN3, BK3_IN4, frontalIzquierdo, POTENCIA_PWM);
  controlarMotor(PWM_AK1, AK1_IN1, AK1_IN2, traseroDerecho, POTENCIA_PWM);
  controlarMotor(PWM_AK3, AK3_IN3, AK3_IN4, traseroIzquierdo, POTENCIA_PWM);
}

void detenerTodos() {
  mover(0, 0, 0, 0);
}

void avanzar() {
  mover(+1, +1, +1, +1);
}

void retroceder() {
  mover(-1, -1, -1, -1);
}

void desplazarDerecha() {
  mover(-1, +1, +1, -1);
}

void desplazarIzquierda() {
  mover(+1, -1, -1, +1);
}

void girarHorario() {
  mover(-1, +1, -1, +1);
}

void girarAntihorario() {
  mover(+1, -1, +1, -1);
}

void esperarYDetener() {
  delay(500);
  detenerTodos();
  delay(1200);
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

void setup() {
  prepararMotores();

  if (!EJECUTAR_PRUEBA) {
    return;
  }

  // Da tiempo para retirar el USB y, despues, energizar desde baterias.
  delay(15000);

  if (PRUEBA_EN_SUELO) {
    avanzar();
    esperarYDetener();
    desplazarDerecha();
    esperarYDetener();
  } else {
    avanzar();
    esperarYDetener();
    retroceder();
    esperarYDetener();
    desplazarDerecha();
    esperarYDetener();
    desplazarIzquierda();
    esperarYDetener();
    girarHorario();
    esperarYDetener();
    girarAntihorario();
    esperarYDetener();
  }

  detenerTodos();
}

void loop() {
  detenerTodos();
}
