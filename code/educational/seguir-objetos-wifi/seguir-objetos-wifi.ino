// PX-32: control Wi-Fi, evasion, linea y seguimiento de objetos.
// Politica: STOP primero, medir tres veces y mover solo con evidencia.
// Ninguna lectura no fiable autoriza avanzar o continuar un giro.

#include <Servo.h>
#include <WiFiEsp.h>
#include <WiFiEspUdp.h>

// En modo autonomo el movimiento queda subordinado a los sensores. En modo
// Wi-Fi la app tiene control directo y la proximidad no bloquea las ordenes.
const bool MOTOR_ACTIVO = true;
// En este modo el carro espera ordenes UDP de la app oficial. Nunca arranca
// solo y una perdida de comunicacion produce STOP.
const bool MODO_CONTROL_WIFI = true;
// La polaridad de la reductora trasera izquierda quedo invertida durante el
// mantenimiento. Los pines AK3 se intercambian aqui para conservar el mismo
// sentido logico en avance, reversa, giros y pruebas individuales.
const bool MODO_CONTINGENCIA_TRES_RUEDAS = false;
const bool INICIO_AUTONOMO = false;
const byte SEGUNDOS_ANTES_DE_MOVER = 8;

// Ajustar despues de comprobar fisicamente hacia donde apunta el servo.
const bool GRADOS_45_MIRA_A_TU_IZQUIERDA = true;

const float DISTANCIA_SEGURA_CM = 25.0;
// Umbral propio del control Wi-Fi: el veto frontal del avance entra a 10 cm.
const float DISTANCIA_SEGURA_WIFI_CM = 10.0;
const float DISTANCIA_PELIGRO_GIRO_CM = 12.0;
// Compensacion individual: el lado derecho recibe un poco mas de empuje para
// corregir la tendencia a desviarse a la derecha. La trasera izquierda nueva
// recibe compensacion adicional por su menor fuerza bajo carga.
const byte POTENCIA_AVANCE_FRONTAL_DERECHA = 130;
const byte POTENCIA_AVANCE_FRONTAL_IZQUIERDA = 115;
const byte POTENCIA_AVANCE_TRASERA_DERECHA = 110;
const byte POTENCIA_AVANCE_TRASERA_IZQUIERDA = 120;
const byte POTENCIA_REVERSA_FRONTAL_DERECHA = 120;
const byte POTENCIA_REVERSA_FRONTAL_IZQUIERDA = 105;
const byte POTENCIA_REVERSA_TRASERA_DERECHA = 100;
const byte POTENCIA_REVERSA_TRASERA_IZQUIERDA = 115;
// PWM 80 no vencio la friccion con el carro apoyado. Los cuatro motores de
// giro usan 110 y el motoreductor trasero izquierdo compensado usa 125.
const byte POTENCIA_GIRO = 110;
const byte POTENCIA_GIRO_TRASERA_IZQUIERDA = 125;
// F5: seguimiento de una linea negra sobre fondo claro. La correccion usa
// los cinco sensores como una posicion ponderada en medios pasos (-4 a +4),
// evitando perder precision cuando dos sensores contiguos ven la pista.
const byte POTENCIA_LINEA_BASE_IZQUIERDA = 85;
const byte POTENCIA_LINEA_BASE_DERECHA = 95;
const byte CORRECCION_LINEA_POR_MEDIO_PASO = 14;
// F6: los IR estan calibrados a unos 10 cm. El ultrasonico permanece
// centrado: un eco ausente, demasiado lejano o cercano conserva STOP.
const float DISTANCIA_FRENO_OBJETO_CM = 7.0;
const float DISTANCIA_REANUDAR_OBJETO_CM = 8.0;
const float DISTANCIA_MAXIMA_OBJETO_CM = 12.0;
// Una misma orden PWM para los cuatro motores en avance y giros de F6.
// Igual PWM no implica igual corriente ni velocidad real sin realimentacion.
const byte POTENCIA_OBJETO = 110;
const unsigned int ESTABILIDAD_IR_OBJETO_MS = 60;
const unsigned int INTERVALO_MEDICION_OBJETO_MS = 60;
const byte POTENCIA_PRUEBA_MOTOR = 90;
const unsigned int DURACION_PRUEBA_MOTOR_MS = 2000;
const unsigned int DURACION_REVERSA_MS = 600;
const unsigned int PASO_VIGILANCIA_REVERSA_MS = 30;
const unsigned int DURACION_GIRO_MS = 420;
const unsigned int PASO_VIGILANCIA_GIRO_MS = 60;
// Control tipo "hombre muerto": mientras el boton esta sostenido la app
// renueva la orden. Al soltarlo, la ausencia de paquetes produce STOP.
const unsigned int TIMEOUT_ORDEN_WIFI_MS = 250;
const unsigned int INTERVALO_ULTRASONIDO_WIFI_MS = 80;

// Punto de acceso local del carro. No usa el router ni Internet.
char NOMBRE_RED_WIFI[] = "osoyoo_robot";
char CLAVE_RED_WIFI[] = "genomo123";
const unsigned int PUERTO_CONTROL_UDP = 8888;
const byte TAMANO_PAQUETE_WIFI = 8;

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
const byte AK3_IN3 = 8;
const byte AK3_IN4 = 7;

const byte TRIG = 30;
const byte ECHO = 31;
const byte PIN_SERVO = 13;
const byte SENSOR_IR_IZQUIERDO = 3;
const byte SENSOR_IR_DERECHO = 2;
const int LECTURA_IR_AL_DETECTAR = LOW;
const byte TRACKER_IR1 = A4;
const byte TRACKER_IR2 = A3;
const byte TRACKER_IR3 = A2;
const byte TRACKER_IR4 = A1;
const byte TRACKER_IR5 = A0;
const unsigned long TIMEOUT_US = 30000UL;
const float SONIDO_CM_POR_US = 0.0343;
const byte CANTIDAD_LECTURAS = 3;
const unsigned int PAUSA_ENTRE_LECTURAS_MS = 25;

const byte ANGULO_45 = 45;
const byte ANGULO_FRENTE = 90;
const byte ANGULO_135 = 135;
const unsigned int ESPERA_SERVO_BASE_MS = 60;
const unsigned int ESPERA_SERVO_POR_GRADO_MS = 3;
const unsigned long DURACION_BARRIDO_SERVO_MS = 60000UL;
const unsigned long DURACION_PAUSA_SERVO_MS = 60000UL;
const unsigned int INTERVALO_PASO_SERVO_MS = 30;

enum PerfilConduccion {
  PERFIL_SUAVE,
  PERFIL_NORMAL,
  PERFIL_POTENCIA
};

enum DecisionMovimiento {
  DECISION_DETENER,
  DECISION_AVANZAR,
  DECISION_GIRAR_45,
  DECISION_GIRAR_135
};

Servo cabeza;
WiFiEspUDP controlUdp;
byte anguloActualServo = ANGULO_FRENTE;
bool sistemaArmado = false;
bool wifiListo = false;
char ordenWifiActual = 'E';
unsigned long ultimaOrdenWifiMs = 0;
unsigned long ultimaMedicionWifiMs = 0;
bool frenteWifiConfirmado = false;
unsigned long inicioCicloServoMs = 0;
unsigned long ultimoPasoServoMs = 0;
bool servoAvanzaHacia135 = true;
bool servoEnPausa = false;
PerfilConduccion perfilConduccion = PERFIL_NORMAL;
bool modoAutonomoWifi = false;
bool modoSeguidorLineaWifi = false;
bool modoSeguidorObjetoWifi = false;
byte deteccionObjeto = 0;
byte direccionObjeto = 0;
unsigned long cambioDeteccionObjetoMs = 0;
unsigned long ultimaMedicionObjetoMs = 0;
bool medicionObjetoDisponible = false;
float distanciaObjetoCm = -1.0;
byte confirmacionesObjeto = 0;
bool objetoDemasiadoCerca = true;
char ultimoEstadoObjeto = '\0';
int ultimoErrorLinea = 0;

byte ajustarPotenciaAlPerfil(byte potenciaBase) {
  unsigned int porcentaje = 100;
  if (perfilConduccion == PERFIL_SUAVE) {
    porcentaje = 90;
  } else if (perfilConduccion == PERFIL_POTENCIA) {
    porcentaje = 120;
  }

  unsigned int ajustada = (unsigned int)potenciaBase * porcentaje / 100;
  return ajustada > 255 ? 255 : (byte)ajustada;
}

// ---------------- Movimiento ----------------

void controlarMotor(
  byte pinPwm,
  byte pin1,
  byte pin2,
  int sentido,
  byte potenciaPwm
) {
  byte potenciaAplicada = ajustarPotenciaAlPerfil(potenciaPwm);
  if (sentido > 0) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    analogWrite(pinPwm, potenciaAplicada);
  } else if (sentido < 0) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    analogWrite(pinPwm, potenciaAplicada);
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
    if (MODO_CONTINGENCIA_TRES_RUEDAS) {
      controlarMotor(PWM_BK1, BK1_IN1, BK1_IN2, +1, POTENCIA_AVANCE_FRONTAL_DERECHA);
      controlarMotor(PWM_BK3, BK3_IN3, BK3_IN4, +1, POTENCIA_AVANCE_FRONTAL_IZQUIERDA);
      controlarMotor(PWM_AK1, AK1_IN1, AK1_IN2, +1, POTENCIA_AVANCE_TRASERA_DERECHA);
      controlarMotor(PWM_AK3, AK3_IN3, AK3_IN4, 0, 0);
    } else {
      controlarMotor(PWM_BK1, BK1_IN1, BK1_IN2, +1, POTENCIA_AVANCE_FRONTAL_DERECHA);
      controlarMotor(PWM_BK3, BK3_IN3, BK3_IN4, +1, POTENCIA_AVANCE_FRONTAL_IZQUIERDA);
      controlarMotor(PWM_AK1, AK1_IN1, AK1_IN2, +1, POTENCIA_AVANCE_TRASERA_DERECHA);
      controlarMotor(PWM_AK3, AK3_IN3, AK3_IN4, +1, POTENCIA_AVANCE_TRASERA_IZQUIERDA);
    }
  } else {
    detenerTodos();
  }
}

bool retrocederBrevemente() {
  if (!MOTOR_ACTIVO || !sistemaArmado) {
    detenerTodos();
    return false;
  }

  Serial.println("REVERSA CORTA: despejando el obstaculo frontal");
  unsigned long inicioReversaMs = millis();
  while (millis() - inicioReversaMs < DURACION_REVERSA_MS) {
    if (MODO_CONTINGENCIA_TRES_RUEDAS) {
      controlarMotor(PWM_BK1, BK1_IN1, BK1_IN2, -1, POTENCIA_REVERSA_FRONTAL_DERECHA);
      controlarMotor(PWM_BK3, BK3_IN3, BK3_IN4, -1, POTENCIA_REVERSA_FRONTAL_IZQUIERDA);
      controlarMotor(PWM_AK1, AK1_IN1, AK1_IN2, -1, POTENCIA_REVERSA_TRASERA_DERECHA);
      controlarMotor(PWM_AK3, AK3_IN3, AK3_IN4, 0, 0);
    } else {
      controlarMotor(PWM_BK1, BK1_IN1, BK1_IN2, -1, POTENCIA_REVERSA_FRONTAL_DERECHA);
      controlarMotor(PWM_BK3, BK3_IN3, BK3_IN4, -1, POTENCIA_REVERSA_FRONTAL_IZQUIERDA);
      controlarMotor(PWM_AK1, AK1_IN1, AK1_IN2, -1, POTENCIA_REVERSA_TRASERA_DERECHA);
      controlarMotor(PWM_AK3, AK3_IN3, AK3_IN4, -1, POTENCIA_REVERSA_TRASERA_IZQUIERDA);
    }

    delay(PASO_VIGILANCIA_REVERSA_MS);
    if (Serial.available() > 0) {
      char comando = Serial.read();
      if (comando == 'S' || comando == 's') {
        sistemaArmado = false;
        detenerTodos();
        desactivarServo();
        Serial.println("STOP MANUAL DURANTE REVERSA: sistema desarmado");
        return false;
      }
    }
  }

  detenerTodos();
  Serial.println("REVERSA TERMINADA: motores en STOP");
  return true;
}

void girarHaciaLaIzquierda() {
  if (MOTOR_ACTIVO && sistemaArmado) {
    if (MODO_CONTINGENCIA_TRES_RUEDAS) {
      moverConPotencia(+1, -1, +1, 0, POTENCIA_GIRO);
    } else {
      controlarMotor(PWM_BK1, BK1_IN1, BK1_IN2, +1, POTENCIA_GIRO);
      controlarMotor(PWM_BK3, BK3_IN3, BK3_IN4, -1, POTENCIA_GIRO);
      controlarMotor(PWM_AK1, AK1_IN1, AK1_IN2, +1, POTENCIA_GIRO);
      controlarMotor(PWM_AK3, AK3_IN3, AK3_IN4, -1, POTENCIA_GIRO_TRASERA_IZQUIERDA);
    }
  } else {
    detenerTodos();
  }
}

void girarHaciaLaDerecha() {
  if (MOTOR_ACTIVO && sistemaArmado) {
    if (MODO_CONTINGENCIA_TRES_RUEDAS) {
      moverConPotencia(-1, +1, -1, 0, POTENCIA_GIRO);
    } else {
      controlarMotor(PWM_BK1, BK1_IN1, BK1_IN2, -1, POTENCIA_GIRO);
      controlarMotor(PWM_BK3, BK3_IN3, BK3_IN4, +1, POTENCIA_GIRO);
      controlarMotor(PWM_AK1, AK1_IN1, AK1_IN2, -1, POTENCIA_GIRO);
      controlarMotor(PWM_AK3, AK3_IN3, AK3_IN4, +1, POTENCIA_GIRO_TRASERA_IZQUIERDA);
    }
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

void probarMotor(byte numeroMotor, int sentido) {
  sistemaArmado = false;
  detenerTodos();

  Serial.print("PRUEBA MOTOR ");
  Serial.print(numeroMotor);
  Serial.print(sentido > 0 ? " ADELANTE" : " ATRAS");
  Serial.println(": 2 segundos a potencia moderada");

  if (numeroMotor == 1) {
    controlarMotor(PWM_BK1, BK1_IN1, BK1_IN2, sentido, POTENCIA_PRUEBA_MOTOR);
  } else if (numeroMotor == 2) {
    controlarMotor(PWM_BK3, BK3_IN3, BK3_IN4, sentido, POTENCIA_PRUEBA_MOTOR);
  } else if (numeroMotor == 3) {
    controlarMotor(PWM_AK1, AK1_IN1, AK1_IN2, sentido, POTENCIA_PRUEBA_MOTOR);
  } else if (numeroMotor == 4) {
    controlarMotor(PWM_AK3, AK3_IN3, AK3_IN4, sentido, POTENCIA_PRUEBA_MOTOR);
  }

  delay(DURACION_PRUEBA_MOTOR_MS);
  detenerTodos();
  Serial.println("PRUEBA TERMINADA: todos los motores en STOP");
}

// ---------------- Medicion ----------------

void activarServo() {
  if (!cabeza.attached()) {
    cabeza.attach(PIN_SERVO);
  }
  cabeza.write(ANGULO_FRENTE);
  anguloActualServo = ANGULO_FRENTE;
  delay(300);
}

void desactivarServo() {
  if (cabeza.attached()) {
    cabeza.detach();
  }
}

void iniciarCicloServo() {
  if (!cabeza.attached()) {
    cabeza.attach(PIN_SERVO);
  }
  cabeza.write(ANGULO_FRENTE);
  anguloActualServo = ANGULO_FRENTE;
  inicioCicloServoMs = millis();
  ultimoPasoServoMs = millis();
  servoAvanzaHacia135 = true;
  servoEnPausa = false;
}

void actualizarCicloServo() {
  if (!cabeza.attached()) {
    return;
  }

  const unsigned long duracionCicloMs =
    DURACION_BARRIDO_SERVO_MS + DURACION_PAUSA_SERVO_MS;
  unsigned long faseMs = (millis() - inicioCicloServoMs) % duracionCicloMs;

  if (faseMs >= DURACION_BARRIDO_SERVO_MS) {
    if (!servoEnPausa) {
      cabeza.write(ANGULO_FRENTE);
      anguloActualServo = ANGULO_FRENTE;
      servoEnPausa = true;
    }
    return;
  }

  if (servoEnPausa) {
    servoEnPausa = false;
    ultimoPasoServoMs = millis();
  }

  if (millis() - ultimoPasoServoMs < INTERVALO_PASO_SERVO_MS) {
    return;
  }
  ultimoPasoServoMs = millis();

  if (servoAvanzaHacia135) {
    anguloActualServo++;
    if (anguloActualServo >= ANGULO_135) {
      anguloActualServo = ANGULO_135;
      servoAvanzaHacia135 = false;
    }
  } else {
    anguloActualServo--;
    if (anguloActualServo <= ANGULO_45) {
      anguloActualServo = ANGULO_45;
      servoAvanzaHacia135 = true;
    }
  }
  cabeza.write(anguloActualServo);
}

void apuntarSensor(byte anguloDestino) {
  if (!cabeza.attached()) {
    return;
  }

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

bool obstaculoIrFrontalDetectado() {
  return digitalRead(SENSOR_IR_IZQUIERDO) == LECTURA_IR_AL_DETECTAR ||
         digitalRead(SENSOR_IR_DERECHO) == LECTURA_IR_AL_DETECTAR;
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

void diagnosticarSensoresIr() {
  sistemaArmado = false;
  detenerTodos();
  Serial.println("PRUEBA IR: 6 segundos; acerca y retira una mano");

  for (byte muestra = 1; muestra <= 30; muestra++) {
    int lecturaIzquierda = digitalRead(SENSOR_IR_IZQUIERDO);
    int lecturaDerecha = digitalRead(SENSOR_IR_DERECHO);

    Serial.print("IR ");
    Serial.print(muestra);
    Serial.print(" | izquierda=");
    Serial.print(lecturaIzquierda);
    Serial.print(lecturaIzquierda == LECTURA_IR_AL_DETECTAR ? " DETECTA" : " libre");
    Serial.print(" | derecha=");
    Serial.print(lecturaDerecha);
    Serial.println(lecturaDerecha == LECTURA_IR_AL_DETECTAR ? " DETECTA" : " libre");
    delay(200);
  }

  Serial.println("PRUEBA IR TERMINADA: motores en STOP");
}

void diagnosticarTracker() {
  sistemaArmado = false;
  detenerTodos();
  Serial.println("PRUEBA TRACKER: 8 segundos; mueve papel blanco y franja negra");

  for (byte muestra = 1; muestra <= 40; muestra++) {
    Serial.print("TRACKER ");
    Serial.print(muestra);
    Serial.print(" | IR1..IR5=");
    Serial.print(digitalRead(TRACKER_IR1));
    Serial.print(digitalRead(TRACKER_IR2));
    Serial.print(digitalRead(TRACKER_IR3));
    Serial.print(digitalRead(TRACKER_IR4));
    Serial.println(digitalRead(TRACKER_IR5));
    delay(200);
  }

  Serial.println("PRUEBA TRACKER TERMINADA: motores en STOP");
}

int leerErrorLinea(bool *lineaDetectada) {
  const byte sensores[5] = {
    TRACKER_IR1, TRACKER_IR2, TRACKER_IR3, TRACKER_IR4, TRACKER_IR5
  };
  const int posiciones[5] = {-2, -1, 0, 1, 2};
  int sumaPosiciones = 0;
  byte sensoresSobreLinea = 0;

  // El ejemplo oficial de OSOYOO invierte digitalRead(): LOW significa que
  // el sensor esta sobre la pista negra.
  for (byte i = 0; i < 5; i++) {
    if (digitalRead(sensores[i]) == LOW) {
      sumaPosiciones += posiciones[i];
      sensoresSobreLinea++;
    }
  }

  *lineaDetectada = sensoresSobreLinea > 0;
  if (!*lineaDetectada) {
    return ultimoErrorLinea;
  }

  int error = (sumaPosiciones * 2) / (int)sensoresSobreLinea;
  ultimoErrorLinea = error;
  return error;
}

void ejecutarSeguidorLinea() {
  if (!sistemaArmado || !frenteSeguroParaWifi()) {
    detenerTodos();
    return;
  }

  bool lineaDetectada = false;
  int error = leerErrorLinea(&lineaDetectada);
  if (!lineaDetectada) {
    detenerTodos();
    return;
  }

  int potenciaIzquierda =
    (int)POTENCIA_LINEA_BASE_IZQUIERDA +
    error * CORRECCION_LINEA_POR_MEDIO_PASO;
  int potenciaDerecha =
    (int)POTENCIA_LINEA_BASE_DERECHA -
    error * CORRECCION_LINEA_POR_MEDIO_PASO;
  potenciaIzquierda = constrain(potenciaIzquierda, 0, 150);
  potenciaDerecha = constrain(potenciaDerecha, 0, 150);

  controlarMotor(
    PWM_BK1, BK1_IN1, BK1_IN2, +1, (byte)potenciaDerecha
  );
  controlarMotor(
    PWM_BK3, BK3_IN3, BK3_IN4, +1, (byte)potenciaIzquierda
  );
  controlarMotor(
    PWM_AK1, AK1_IN1, AK1_IN2, +1, (byte)potenciaDerecha
  );
  controlarMotor(
    PWM_AK3, AK3_IN3, AK3_IN4, +1, (byte)potenciaIzquierda
  );
}

bool consultarEsp(
  const char *etiqueta,
  const char *comando,
  unsigned long esperaMaximaMs,
  byte *cantidadRedes,
  int *modoWifi
) {
  while (Serial1.available() > 0) {
    Serial1.read();
  }

  Serial.print("ESP ");
  Serial.print(etiqueta);
  Serial.print(": ");
  Serial1.print(comando);
  Serial1.print("\r\n");

  char linea[64];
  byte longitud = 0;
  bool respondioOk = false;
  bool respondioError = false;
  unsigned long inicioMs = millis();

  while (millis() - inicioMs < esperaMaximaMs && !respondioOk && !respondioError) {
    while (Serial1.available() > 0) {
      char caracter = Serial1.read();
      if (caracter == '\n') {
        linea[longitud] = '\0';
        if (strcmp(linea, "OK") == 0) {
          respondioOk = true;
        } else if (strstr(linea, "ERROR") != NULL || strstr(linea, "FAIL") != NULL) {
          respondioError = true;
        } else if (cantidadRedes != NULL && strstr(linea, "+CWLAP:") != NULL) {
          (*cantidadRedes)++;
        } else if (modoWifi != NULL && strstr(linea, "+CWMODE:") != NULL) {
          *modoWifi = atoi(strchr(linea, ':') + 1);
        }
        longitud = 0;
      } else if (caracter != '\r' && longitud < sizeof(linea) - 1) {
        linea[longitud++] = caracter;
      }
    }
  }

  if (respondioOk) {
    Serial.println("APROBADO");
    return true;
  }
  if (respondioError) {
    Serial.println("RESPONDIO ERROR");
  } else {
    Serial.println("SIN RESPUESTA");
  }
  return false;
}

void diagnosticarEsp() {
  sistemaArmado = false;
  detenerTodos();
  desactivarServo();

  Serial.println("PRUEBA WIFI: solo consultas; SSID ocultos");
  bool enlace = consultarEsp("enlace AT", "AT", 2000UL, NULL, NULL);
  if (!enlace) {
    Serial.println("PRUEBA WIFI CANCELADA: revisar UART E");
    return;
  }

  consultarEsp("firmware", "AT+GMR", 3000UL, NULL, NULL);
  int modoOriginal = -1;
  consultarEsp("modo", "AT+CWMODE?", 3000UL, NULL, &modoOriginal);
  Serial.print("MODO WIFI ORIGINAL: ");
  Serial.println(modoOriginal);
  consultarEsp("estado de red", "AT+CWJAP?", 3000UL, NULL, NULL);
  consultarEsp("direccion IP", "AT+CIFSR", 3000UL, NULL, NULL);

  bool cambioTemporal = false;
  if (modoOriginal == 2) {
    cambioTemporal = consultarEsp(
      "activar estacion temporal",
      "AT+CWMODE_CUR=3",
      3000UL,
      NULL,
      NULL
    );
  }

  byte cantidadRedes = 0;
  bool escaneoOk = consultarEsp(
    "radio y escaneo",
    "AT+CWLAP",
    15000UL,
    &cantidadRedes,
    NULL
  );
  if (escaneoOk) {
    Serial.print("REDES WIFI DETECTADAS (nombres ocultos): ");
    Serial.println(cantidadRedes);
  }

  if (cambioTemporal) {
    consultarEsp(
      "restaurar modo original",
      "AT+CWMODE_CUR=2",
      3000UL,
      NULL,
      NULL
    );
  }
  Serial.println("PRUEBA WIFI TERMINADA: motores en STOP");
}

// ---------------- Control Wi-Fi seguro ----------------

void frenarControlWifi(const char *motivo) {
  detenerTodos();
  modoSeguidorObjetoWifi = false;
  confirmacionesObjeto = 0;
  direccionObjeto = 0;
  sistemaArmado = false;
  ordenWifiActual = 'E';
  frenteWifiConfirmado = false;
  if (motivo != NULL) {
    Serial.print("STOP WIFI: ");
    Serial.println(motivo);
  }
}

void iniciarControlWifi() {
  frenarControlWifi(NULL);
  WiFi.init(&Serial1);

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WIFI NO DISPONIBLE: revisar E_TX/E_RX; motores en STOP");
    return;
  }

  Serial.print("Creando red WiFi: ");
  Serial.println(NOMBRE_RED_WIFI);
  int estadoWifi = WiFi.beginAP(
    NOMBRE_RED_WIFI,
    10,
    CLAVE_RED_WIFI,
    ENC_TYPE_WPA2_PSK
  );
  if (estadoWifi != WL_CONNECTED) {
    Serial.println("NO SE PUDO CREAR LA RED: motores en STOP");
    return;
  }

  if (controlUdp.begin(PUERTO_CONTROL_UDP) == 0) {
    Serial.println("NO SE PUDO ABRIR UDP 8888: motores en STOP");
    return;
  }

  wifiListo = true;
  Serial.print("WIFI LISTO | IP: ");
  Serial.print(WiFi.localIP());
  Serial.print(" | puerto: ");
  Serial.println(PUERTO_CONTROL_UDP);
  Serial.println("Esperando la tablet: el carro permanece en STOP");
}

bool frenteSeguroParaWifi() {
  // Los IR se consultan en cada vuelta para conseguir el freno mas rapido.
  if (obstaculoIrFrontalDetectado()) {
    Serial.println("OBSTACULO WIFI: sensor IR frontal");
    return false;
  }

  unsigned long ahoraMs = millis();
  if (!frenteWifiConfirmado ||
      ahoraMs - ultimaMedicionWifiMs >= INTERVALO_ULTRASONIDO_WIFI_MS) {
    float distanciaFrontal = medirDistanciaMedianaCm();
    ultimaMedicionWifiMs = millis();
    frenteWifiConfirmado =
      distanciaEsSegura(distanciaFrontal, DISTANCIA_SEGURA_WIFI_CM);
    if (!frenteWifiConfirmado) {
      imprimirDistancia("OBSTACULO WIFI: ultrasonido ", distanciaFrontal);
    }
  }

  return frenteWifiConfirmado;
}

void aceptarOrdenWifi(char orden) {
  if (orden == 'E') {
    bool estabaEnAutonomo = modoAutonomoWifi;
    bool estabaEnSeguidorLinea = modoSeguidorLineaWifi;
    bool estabaEnSeguidorObjeto = modoSeguidorObjetoWifi;
    modoAutonomoWifi = false;
    modoSeguidorLineaWifi = false;
    frenarControlWifi("boton de pausa");
    if (estabaEnAutonomo || estabaEnSeguidorLinea || estabaEnSeguidorObjeto) {
      iniciarCicloServo();
    }
    return;
  }

  if (orden == 'F' || orden == 'G' || orden == 'H') {
    detenerTodos();
    sistemaArmado = false;
    ordenWifiActual = 'E';
    modoAutonomoWifi = false;
    modoSeguidorLineaWifi = false;
    modoSeguidorObjetoWifi = false;

    if (orden == 'F') {
      perfilConduccion = PERFIL_SUAVE;
      Serial.println("PERFIL F1: SUAVE (90%)");
    } else if (orden == 'G') {
      perfilConduccion = PERFIL_NORMAL;
      Serial.println("PERFIL F2: NORMAL (100%)");
    } else {
      perfilConduccion = PERFIL_POTENCIA;
      Serial.println("PERFIL F3: POTENCIA (120%)");
    }
    iniciarCicloServo();
    return;
  }

  if (orden == 'I') {
    detenerTodos();
    perfilConduccion = PERFIL_NORMAL;
    ordenWifiActual = 'E';
    frenteWifiConfirmado = false;
    modoAutonomoWifi = true;
    modoSeguidorLineaWifi = false;
    modoSeguidorObjetoWifi = false;
    activarServo();
    sistemaArmado = MOTOR_ACTIVO;
    Serial.println("MODO F4: AUTONOMO CON EVASION DE OBSTACULOS");
    return;
  }

  if (orden == 'J') {
    detenerTodos();
    perfilConduccion = PERFIL_NORMAL;
    ordenWifiActual = 'E';
    frenteWifiConfirmado = false;
    modoAutonomoWifi = false;
    modoSeguidorLineaWifi = true;
    modoSeguidorObjetoWifi = false;
    ultimoErrorLinea = 0;
    activarServo();
    sistemaArmado = MOTOR_ACTIVO;
    Serial.println("MODO F5: MISION LINEA CON FRENO ANTI-OBSTACULOS");
    return;
  }

  if (orden == 'K') {
    // La app puede repetir F6; no interrumpir el seguimiento ni las lecturas.
    if (modoSeguidorObjetoWifi) {
      return;
    }
    detenerTodos();
    perfilConduccion = PERFIL_NORMAL;
    ordenWifiActual = 'E';
    modoAutonomoWifi = false;
    modoSeguidorLineaWifi = false;
    deteccionObjeto = 0;
    direccionObjeto = 0;
    cambioDeteccionObjetoMs = millis();
    ultimaMedicionObjetoMs = millis();
    medicionObjetoDisponible = false;
    distanciaObjetoCm = -1.0;
    confirmacionesObjeto = 0;
    objetoDemasiadoCerca = true;
    ultimoEstadoObjeto = '\0';
    activarServo();
    modoSeguidorObjetoWifi = true;
    sistemaArmado = MOTOR_ACTIVO;
    Serial.println("MODO F6: CONTINUO | PWM 110 IGUAL | freno 7 cm | reanudar 8 cm");
    return;
  }

  if (orden != 'A' && orden != 'B' && orden != 'L' && orden != 'R') {
    modoAutonomoWifi = false;
    modoSeguidorLineaWifi = false;
    frenarControlWifi("orden desconocida");
    iniciarCicloServo();
    return;
  }

  if (modoAutonomoWifi) {
    modoAutonomoWifi = false;
    iniciarCicloServo();
    Serial.println("MODO AUTONOMO CANCELADO: control manual");
  }
  if (modoSeguidorLineaWifi) {
    modoSeguidorLineaWifi = false;
    iniciarCicloServo();
    Serial.println("MISION LINEA CANCELADA: control manual");
  }
  if (modoSeguidorObjetoWifi) {
    modoSeguidorObjetoWifi = false;
    confirmacionesObjeto = 0;
    detenerTodos();
    iniciarCicloServo();
    Serial.println("SEGUIR OBJETO CANCELADO: control manual");
  }
  ordenWifiActual = orden;
  ultimaOrdenWifiMs = millis();
  frenteWifiConfirmado = false;
  sistemaArmado = MOTOR_ACTIVO;
  Serial.print("ORDEN WIFI: ");
  Serial.println(ordenWifiActual);
}

void recibirOrdenWifi() {
  int tamanoPaquete = controlUdp.parsePacket();
  if (tamanoPaquete <= 0) {
    return;
  }

  char paquete[TAMANO_PAQUETE_WIFI];
  int leidos = controlUdp.read((uint8_t *)paquete, sizeof(paquete));
  if (leidos <= 0) {
    frenarControlWifi("paquete vacio");
    return;
  }

  char orden = paquete[0];
  if (orden >= 'a' && orden <= 'z') {
    orden -= ('a' - 'A');
  }
  aceptarOrdenWifi(orden);
}

byte leerDeteccionObjeto() {
  byte deteccion = 0;
  if (digitalRead(SENSOR_IR_IZQUIERDO) == LECTURA_IR_AL_DETECTAR) {
    deteccion |= 1;
  }
  if (digitalRead(SENSOR_IR_DERECHO) == LECTURA_IR_AL_DETECTAR) {
    deteccion |= 2;
  }
  return deteccion;
}

void informarEstadoObjeto(char estado, const char *mensaje) {
  if (estado != ultimoEstadoObjeto) {
    ultimoEstadoObjeto = estado;
    Serial.print("OBJETO: ");
    Serial.println(mensaje);
  }
}

void moverHaciaObjeto(byte deteccion) {
  if (deteccion == 3) {
    informarEstadoObjeto('A', "AVANZAR CONTINUO");
    controlarMotor(PWM_BK1, BK1_IN1, BK1_IN2, +1, POTENCIA_OBJETO);
    controlarMotor(PWM_BK3, BK3_IN3, BK3_IN4, +1, POTENCIA_OBJETO);
    controlarMotor(PWM_AK1, AK1_IN1, AK1_IN2, +1, POTENCIA_OBJETO);
    controlarMotor(PWM_AK3, AK3_IN3, AK3_IN4,
      MODO_CONTINGENCIA_TRES_RUEDAS ? 0 : +1, POTENCIA_OBJETO);
    return;
  }
  informarEstadoObjeto(deteccion == 1 ? 'L' : 'R',
    deteccion == 1 ? "GIRAR IZQUIERDA CONTINUO" : "GIRAR DERECHA CONTINUO");
  int sentidoDerecho = deteccion == 1 ? +1 : -1;
  controlarMotor(PWM_BK1, BK1_IN1, BK1_IN2, sentidoDerecho, POTENCIA_OBJETO);
  controlarMotor(PWM_BK3, BK3_IN3, BK3_IN4, -sentidoDerecho, POTENCIA_OBJETO);
  controlarMotor(PWM_AK1, AK1_IN1, AK1_IN2, sentidoDerecho, POTENCIA_OBJETO);
  controlarMotor(PWM_AK3, AK3_IN3, AK3_IN4,
    MODO_CONTINGENCIA_TRES_RUEDAS ? 0 : -sentidoDerecho,
    POTENCIA_OBJETO);
}

void ejecutarSeguidorObjeto() {
  if (!sistemaArmado) {
    detenerTodos();
    confirmacionesObjeto = 0;
    direccionObjeto = 0;
    return;
  }

  unsigned long ahoraMs = millis();
  byte deteccion = leerDeteccionObjeto();
  if (deteccion != deteccionObjeto) {
    deteccionObjeto = deteccion;
    cambioDeteccionObjetoMs = ahoraMs;
  }
  if (deteccion == 0) {
    detenerTodos();
    confirmacionesObjeto = 0;
    direccionObjeto = 0;
    medicionObjetoDisponible = false;
    objetoDemasiadoCerca = true;
    informarEstadoObjeto('P', "PERDIDO; STOP");
    return;
  }
  if (direccionObjeto == 0 &&
      ahoraMs - cambioDeteccionObjetoMs < ESTABILIDAD_IR_OBJETO_MS) {
    detenerTodos();
    return;
  }

  if (!medicionObjetoDisponible ||
      ahoraMs - ultimaMedicionObjetoMs >= INTERVALO_MEDICION_OBJETO_MS) {
    // Una muestra por ciclo, sin parar para medir ni esperar entre muestras.
    // Se requieren tres muestras seguras para arrancar; en movimiento basta
    // una muestra peligrosa/ausente para frenar. pulseIn limita la espera a
    // 30 ms si no hay eco, tras lo cual se atiende la orden STOP pendiente.
    distanciaObjetoCm = medirUnaDistanciaCm();
    ultimaMedicionObjetoMs = millis();
    medicionObjetoDisponible = true;
    recibirOrdenWifi();
    if (!modoSeguidorObjetoWifi || !sistemaArmado) {
      return;
    }
    byte deteccionDespuesDeMedir = leerDeteccionObjeto();
    if (deteccionDespuesDeMedir == 0) {
      detenerTodos();
      direccionObjeto = 0;
      confirmacionesObjeto = 0;
      medicionObjetoDisponible = false;
      objetoDemasiadoCerca = true;
      return;
    }
    if (deteccionDespuesDeMedir != deteccion) {
      deteccion = deteccionDespuesDeMedir;
      deteccionObjeto = deteccion;
      cambioDeteccionObjetoMs = millis();
    }
    if (distanciaObjetoCm < 0 || distanciaObjetoCm > DISTANCIA_MAXIMA_OBJETO_CM) {
      detenerTodos();
      confirmacionesObjeto = 0;
      direccionObjeto = 0;
      objetoDemasiadoCerca = true;
      informarEstadoObjeto('N', "ECO AUSENTE O FUERA DE ALCANCE; STOP");
      return;
    }
    if (distanciaObjetoCm <= DISTANCIA_FRENO_OBJETO_CM) {
      objetoDemasiadoCerca = true;
    } else if (distanciaObjetoCm >= DISTANCIA_REANUDAR_OBJETO_CM) {
      objetoDemasiadoCerca = false;
    }
    if (!objetoDemasiadoCerca && confirmacionesObjeto < CANTIDAD_LECTURAS) {
      confirmacionesObjeto++;
    }
  }
  // Conservar la causa de parada entre mediciones, sin alternar mensajes
  // de eco invalido y cercania ni permitir usar un eco anterior.
  if (distanciaObjetoCm < 0 || distanciaObjetoCm > DISTANCIA_MAXIMA_OBJETO_CM) {
    detenerTodos();
    confirmacionesObjeto = 0;
    direccionObjeto = 0;
    informarEstadoObjeto('N', "ECO AUSENTE O FUERA DE ALCANCE; STOP");
    return;
  }
  if (objetoDemasiadoCerca) {
    detenerTodos();
    confirmacionesObjeto = 0;
    direccionObjeto = 0;
    informarEstadoObjeto('C', "DEMASIADO CERCA; STOP");
    return;
  }
  if (confirmacionesObjeto < CANTIDAD_LECTURAS) {
    detenerTodos();
    return;
  }
  // Filtrar cambios breves de lado sin cortar el avance. Las mediciones
  // siguen activas durante el filtro y perder ambos IR siempre frena.
  if (millis() - cambioDeteccionObjetoMs >= ESTABILIDAD_IR_OBJETO_MS) {
    direccionObjeto = deteccion;
  }
  if (direccionObjeto == 0) {
    detenerTodos();
    return;
  }
  moverHaciaObjeto(direccionObjeto);
}

void ejecutarOrdenWifi() {
  if (!wifiListo) {
    detenerTodos();
    return;
  }

  if (modoAutonomoWifi) {
    if (sistemaArmado) {
      evaluarYActuar();
    } else {
      detenerTodos();
    }
    return;
  }

  if (modoSeguidorLineaWifi) {
    ejecutarSeguidorLinea();
    return;
  }
  if (modoSeguidorObjetoWifi) {
    ejecutarSeguidorObjeto();
    return;
  }

  if (!sistemaArmado || ordenWifiActual == 'E') {
    detenerTodos();
    return;
  }

  if (millis() - ultimaOrdenWifiMs > TIMEOUT_ORDEN_WIFI_MS) {
    frenarControlWifi("boton liberado; no llegan ordenes");
    return;
  }

  // La orden solo permanece activa mientras la app la renueva.
  if (ordenWifiActual == 'B') {
    controlarMotor(PWM_BK1, BK1_IN1, BK1_IN2, -1, POTENCIA_REVERSA_FRONTAL_DERECHA);
    controlarMotor(PWM_BK3, BK3_IN3, BK3_IN4, -1, POTENCIA_REVERSA_FRONTAL_IZQUIERDA);
    controlarMotor(PWM_AK1, AK1_IN1, AK1_IN2, -1, POTENCIA_REVERSA_TRASERA_DERECHA);
    controlarMotor(PWM_AK3, AK3_IN3, AK3_IN4, -1, POTENCIA_REVERSA_TRASERA_IZQUIERDA);
    return;
  }

  if (ordenWifiActual == 'A') {
    avanzar();
  } else if (ordenWifiActual == 'L') {
    girarHaciaLaIzquierda();
  } else if (ordenWifiActual == 'R') {
    girarHaciaLaDerecha();
  }
}

void procesarControlWifi() {
  if (!wifiListo) {
    detenerTodos();
    return;
  }
  recibirOrdenWifi();
  ejecutarOrdenWifi();
}

void procesarComandosSerial() {
  while (Serial.available() > 0) {
    char comando = Serial.read();

    if ((comando == 'A' || comando == 'a') && MOTOR_ACTIVO) {
      detenerTodos();
      activarServo();
      sistemaArmado = true;
      Serial.println("SISTEMA ARMADO: motores autorizados");
    } else if (comando == 'S' || comando == 's') {
      sistemaArmado = false;
      detenerTodos();
      desactivarServo();
      Serial.println("STOP MANUAL: sistema desarmado");
    } else if (comando >= '1' && comando <= '4') {
      probarMotor(comando - '0', +1);
    } else if (comando >= '5' && comando <= '8') {
      probarMotor(comando - '4', -1);
    } else if (comando == 'I' || comando == 'i') {
      diagnosticarSensoresIr();
    } else if (comando == 'T' || comando == 't') {
      diagnosticarTracker();
    } else if (comando == 'W' || comando == 'w') {
      diagnosticarEsp();
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

    // Los IR miran siempre al frente: cualquiera de ellos ordena STOP sin
    // esperar las tres muestras del ultrasonido.
    if (obstaculoIrFrontalDetectado()) {
      detenerTodos();
      Serial.println("PELIGRO DURANTE GIRO: sensor IR; STOP");
      return false;
    }

    // Durante el giro una sola lectura peligrosa o ausente basta para parar.
    float distanciaDuranteGiro = medirUnaDistanciaCm();
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

  if (obstaculoIrFrontalDetectado() ||
      !distanciaEsSegura(frenteDespuesDelGiro, DISTANCIA_SEGURA_CM)) {
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

  if (!obstaculoIrFrontalDetectado() &&
      distanciaEsSegura(frente, DISTANCIA_SEGURA_CM)) {
    Serial.println("DECISION: AVANZAR");
    avanzar();
    return;
  }

  detenerTodos();
  Serial.println("DECISION: STOP Y EXPLORAR");

  // Sin sensor trasero, la reversa solo se permite por un tiempo corto y
  // cuando existe evidencia real de obstaculo. Una medicion ausente por si
  // sola conserva STOP y nunca autoriza movimiento.
  bool obstaculoIrConfirmado = obstaculoIrFrontalDetectado();
  bool obstaculoUltrasonicoConfirmado =
    frente >= 0 && frente < DISTANCIA_SEGURA_CM;
  if ((obstaculoIrConfirmado || obstaculoUltrasonicoConfirmado) &&
      !retrocederBrevemente()) {
    return;
  }

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
  pinMode(SENSOR_IR_IZQUIERDO, INPUT);
  pinMode(SENSOR_IR_DERECHO, INPUT);
  pinMode(TRACKER_IR1, INPUT);
  pinMode(TRACKER_IR2, INPUT);
  pinMode(TRACKER_IR3, INPUT);
  pinMode(TRACKER_IR4, INPUT);
  pinMode(TRACKER_IR5, INPUT);

  Serial.begin(9600);
  Serial1.begin(115200);
  desactivarServo();

  Serial.println("PX-32: EVASION ACTIVA CON MEDIANA DE 3");
  Serial.println("Seguridad: una lectura no fiable siempre produce STOP");
  Serial.println("Comandos: A = armar motores; S = STOP y desarmar");
  Serial.println("Motores adelante: 1-4; motores atras: 5-8");
  Serial.println("Prueba sin movimiento: I = sensores IR durante 6 segundos");
  Serial.println("Prueba sin movimiento: T = tracker de linea durante 8 segundos");
  Serial.println("Prueba sin movimiento: W = diagnostico WiFi del ESP-12S");
  Serial.println("MODO DE JUEGO: cuatro ruedas activas");

  if (MODO_CONTROL_WIFI) {
    Serial.println("MODO WIFI MANUAL: no existe arranque automatico");
    Serial.println("Movimiento solo mientras el boton permanece oprimido");
    Serial.println("F1 suave | F2 normal | F3 potencia | F4 autonomo");
    Serial.println("F5 Mision Linea: sigue pista negra y frena ante obstaculos");
    Serial.println("F6 Seguir Objeto: IR a 10 cm; ultrasonico centrado; STOP cancela");
    Serial.println("Servo: 1 min de barrido y 1 min centrado");
    Serial.println("App: OSOYOO Wifi UDP Robot Car Controller");
    iniciarCicloServo();
    iniciarControlWifi();
    return;
  }

  if (INICIO_AUTONOMO && MOTOR_ACTIVO) {
    activarServo();
    Serial.println("INICIO AUTONOMO: manten el carro elevado");
    for (byte restante = SEGUNDOS_ANTES_DE_MOVER; restante > 0; restante--) {
      detenerTodos();
      Serial.print("Arranque seguro en ");
      Serial.println(restante);
      delay(1000);
    }
    sistemaArmado = true;
    Serial.println("SISTEMA ARMADO: primero mide, despues decide");
  } else {
    Serial.println("ESTADO INICIAL: DESARMADO");
  }
}

void loop() {
  if (MODO_CONTROL_WIFI) {
    if (!modoAutonomoWifi && !modoSeguidorLineaWifi && !modoSeguidorObjetoWifi) {
      actualizarCicloServo();
    }
    procesarControlWifi();
    delay(15);
    return;
  }

  procesarComandosSerial();
  if (sistemaArmado) {
    evaluarYActuar();
    delay(40);
  } else {
    detenerTodos();
    delay(20);
  }
}
