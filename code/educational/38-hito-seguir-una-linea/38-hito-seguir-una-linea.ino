// Curso PX-32 - Leccion 38: hito de seguimiento de linea.
// Con MOTOR_ACTIVO en false el programa solo imprime la orden.
// La evidencia de tu cuaderno (Leccion 34) decide hacia donde
// girar cuando la linea corre hacia IR1.

const bool MOTOR_ACTIVO = false;

// Escribe true si IR1 quedo a tu IZQUIERDA mirando a PX-32
// desde atras (Leccion 34, paso 12). Si quedo a la derecha,
// cambia a false.
const bool IR1_DEL_LADO_IZQUIERDO = true;

const byte POTENCIA_AVANCE = 65;
const byte POTENCIA_GIRO = 55;
const float TOLERANCIA = 0.4;

// Orden de los motores: frontal derecho, frontal izquierdo,
// trasero derecho, trasero izquierdo (Leccion 20).
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

const int PINES[5] = { A4, A3, A2, A1, A0 };

// Ley de tu cuaderno (Leccion 34): que imprime un canal sobre negro.
const int LECTURA_SOBRE_NEGRO = LOW;

int cuantosVenLinea;

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

void girarHaciaElLadoDeIR1() {
  if (IR1_DEL_LADO_IZQUIERDO) {
    girarHaciaLaIzquierda();
  } else {
    girarHaciaLaDerecha();
  }
}

void girarHaciaElLadoDeIR5() {
  if (IR1_DEL_LADO_IZQUIERDO) {
    girarHaciaLaDerecha();
  } else {
    girarHaciaLaIzquierda();
  }
}

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

void elegirOrdenYEjecutar(float posicion) {
  if (cuantosVenLinea == 0) {
    Serial.println(" -> STOP: linea perdida");
    detenerTodos();
  } else if (cuantosVenLinea == 5) {
    Serial.println(" -> STOP: patron ambiguo");
    detenerTodos();
  } else if (posicion < -TOLERANCIA) {
    Serial.println(" -> CORRIGE hacia IR1");
    if (MOTOR_ACTIVO) {
      girarHaciaElLadoDeIR1();
    } else {
      detenerTodos();
    }
  } else if (posicion > TOLERANCIA) {
    Serial.println(" -> CORRIGE hacia IR5");
    if (MOTOR_ACTIVO) {
      girarHaciaElLadoDeIR5();
    } else {
      detenerTodos();
    }
  } else {
    Serial.println(" -> AVANZA");
    if (MOTOR_ACTIVO) {
      avanzar();
    } else {
      detenerTodos();
    }
  }
}

void setup() {
  prepararMotores();
  for (int i = 0; i < 5; i++) {
    pinMode(PINES[i], INPUT);
  }
  Serial.begin(9600);

  if (MOTOR_ACTIVO) {
    Serial.println("MODO: SEGUIMIENTO ACTIVO");
  } else {
    Serial.println("MODO: SOLO IMPRIMIR");
  }

  if (IR1_DEL_LADO_IZQUIERDO) {
    Serial.println("IR1 al lado IZQUIERDO (segun tu cuaderno)");
  } else {
    Serial.println("IR1 al lado DERECHO (segun tu cuaderno)");
  }

  // Tres segundos de calma antes de empezar.
  delay(3000);
}

void loop() {
  imprimirPatron();
  float posicion = estimarPosicion();
  elegirOrdenYEjecutar(posicion);
  delay(50);
}
