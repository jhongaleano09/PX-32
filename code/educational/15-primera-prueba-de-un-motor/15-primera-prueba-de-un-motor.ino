// Curso PX-32 - Leccion 15: primera prueba del motor AK1.
// El sketch queda detenido hasta cambiar EJECUTAR_PRUEBA a true.
const bool EJECUTAR_PRUEBA = false;

// Model Y, zona B: motores delanteros.
const byte PWM_BK1 = 9;
const byte BK1_IN1 = 22;
const byte BK1_IN2 = 24;
const byte PWM_BK3 = 10;
const byte BK3_IN3 = 26;
const byte BK3_IN4 = 28;

// Model Y, zona A: motores traseros.
const byte PWM_AK1 = 11;
const byte AK1_IN1 = 5;
const byte AK1_IN2 = 6;
const byte PWM_AK3 = 12;
const byte AK3_IN3 = 7;
const byte AK3_IN4 = 8;

void detenerTodos() {
  // Primero se deshabilita la potencia de los cuatro canales.
  analogWrite(PWM_BK1, 0);
  analogWrite(PWM_BK3, 0);
  analogWrite(PWM_AK1, 0);
  analogWrite(PWM_AK3, 0);

  // Luego las entradas de direccion quedan en LOW.
  digitalWrite(BK1_IN1, LOW);
  digitalWrite(BK1_IN2, LOW);
  digitalWrite(BK3_IN3, LOW);
  digitalWrite(BK3_IN4, LOW);
  digitalWrite(AK1_IN1, LOW);
  digitalWrite(AK1_IN2, LOW);
  digitalWrite(AK3_IN3, LOW);
  digitalWrite(AK3_IN4, LOW);
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

void girarAK1Adelante(byte potenciaPwm) {
  digitalWrite(AK1_IN1, HIGH);
  digitalWrite(AK1_IN2, LOW);
  analogWrite(PWM_AK1, potenciaPwm);
}

void setup() {
  prepararMotores();

  if (!EJECUTAR_PRUEBA) {
    return;
  }

  // Da tiempo para retirar el USB y, despues, energizar desde baterias.
  delay(15000);
  girarAK1Adelante(100);
  delay(500);
  detenerTodos();
}

void loop() {
  detenerTodos();
}
