// Curso PX-32 - Leccion 49: evitar obstaculos (hito del bloque).
// Politica: STOP primero, medir tres veces y mover solo con evidencia.
// Ninguna lectura no fiable autoriza avanzar o continuar un giro.

#include <Servo.h>
#include <WiFiEsp.h>
#include <WiFiEspUdp.h>

// El movimiento esta habilitado, pero siempre subordinado a los sensores.
const bool MOTOR_ACTIVO = true;
// En este modo el carro espera ordenes UDP de la app oficial. Nunca arranca
// solo y una perdida de comunicacion produce STOP.
const bool MODO_CONTROL_WIFI = true;
// Contingencia: la reductora trasera izquierda esta averiada. Durante el
// juego se usan las tres ruedas sanas y la averiada permanece sin energia.
const bool MODO_CONTINGENCIA_TRES_RUEDAS = true;
const bool INICIO_AUTONOMO = false;
const byte SEGUNDOS_ANTES_DE_MOVER = 8;

// Ajustar despues de comprobar fisicamente hacia donde apunta el servo.
const bool GRADOS_45_MIRA_A_TU_IZQUIERDA = true;

const float DISTANCIA_SEGURA_CM = 25.0;
const float DISTANCIA_PELIGRO_GIRO_CM = 12.0;
// El par delantero necesitaba algo mas de fuerza para arrancar junto. La
// rueda trasera derecha recibe menos PWM para reducir el desvio del carro.
const byte POTENCIA_AVANCE_DELANTERA = 125;
const byte POTENCIA_AVANCE_TRASERA = 100;
const byte POTENCIA_REVERSA_DELANTERA = 110;
const byte POTENCIA_REVERSA_TRASERA = 90;
const byte POTENCIA_GIRO = 105;
const byte POTENCIA_PRUEBA_MOTOR = 90;
const unsigned int DURACION_PRUEBA_MOTOR_MS = 2000;
const unsigned int DURACION_REVERSA_MS = 600;
const unsigned int PASO_VIGILANCIA_REVERSA_MS = 30;
const unsigned int DURACION_GIRO_MS = 420;
const unsigned int PASO_VIGILANCIA_GIRO_MS = 60;
const unsigned int TIMEOUT_ORDEN_WIFI_MS = 800;
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
const byte AK3_IN3 = 7;
const byte AK3_IN4 = 8;

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
    if (MODO_CONTINGENCIA_TRES_RUEDAS) {
      controlarMotor(PWM_BK1, BK1_IN1, BK1_IN2, +1, POTENCIA_AVANCE_DELANTERA);
      controlarMotor(PWM_BK3, BK3_IN3, BK3_IN4, +1, POTENCIA_AVANCE_DELANTERA);
      controlarMotor(PWM_AK1, AK1_IN1, AK1_IN2, +1, POTENCIA_AVANCE_TRASERA);
      controlarMotor(PWM_AK3, AK3_IN3, AK3_IN4, 0, 0);
    } else {
      moverConPotencia(+1, +1, +1, +1, POTENCIA_AVANCE_DELANTERA);
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
      controlarMotor(PWM_BK1, BK1_IN1, BK1_IN2, -1, POTENCIA_REVERSA_DELANTERA);
      controlarMotor(PWM_BK3, BK3_IN3, BK3_IN4, -1, POTENCIA_REVERSA_DELANTERA);
      controlarMotor(PWM_AK1, AK1_IN1, AK1_IN2, -1, POTENCIA_REVERSA_TRASERA);
      controlarMotor(PWM_AK3, AK3_IN3, AK3_IN4, 0, 0);
    } else {
      moverConPotencia(-1, -1, -1, -1, POTENCIA_REVERSA_DELANTERA);
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
      moverConPotencia(+1, -1, +1, -1, POTENCIA_GIRO);
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
      moverConPotencia(-1, +1, -1, +1, POTENCIA_GIRO);
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
  desactivarServo();
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
      distanciaEsSegura(distanciaFrontal, DISTANCIA_SEGURA_CM);
    if (!frenteWifiConfirmado) {
      imprimirDistancia("OBSTACULO WIFI: ultrasonido ", distanciaFrontal);
    }
  }

  return frenteWifiConfirmado;
}

void aceptarOrdenWifi(char orden) {
  if (orden == 'E') {
    frenarControlWifi("boton de pausa");
    return;
  }

  if (orden != 'A' && orden != 'B' && orden != 'L' && orden != 'R') {
    frenarControlWifi("orden desconocida");
    return;
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

void ejecutarOrdenWifi() {
  if (!wifiListo || !sistemaArmado || ordenWifiActual == 'E') {
    detenerTodos();
    return;
  }

  if (millis() - ultimaOrdenWifiMs > TIMEOUT_ORDEN_WIFI_MS) {
    frenarControlWifi("sin orden reciente de la tablet");
    return;
  }

  // No hay sensor trasero: la reversa solo dura mientras la orden sea
  // reciente y siempre termina por el timeout de 800 ms.
  if (ordenWifiActual == 'B') {
    controlarMotor(PWM_BK1, BK1_IN1, BK1_IN2, -1, POTENCIA_REVERSA_DELANTERA);
    controlarMotor(PWM_BK3, BK3_IN3, BK3_IN4, -1, POTENCIA_REVERSA_DELANTERA);
    controlarMotor(PWM_AK1, AK1_IN1, AK1_IN2, -1, POTENCIA_REVERSA_TRASERA);
    controlarMotor(PWM_AK3, AK3_IN3, AK3_IN4, 0, 0);
    return;
  }

  if (!frenteSeguroParaWifi()) {
    frenarControlWifi("pared u obstaculo frontal");
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
  Serial.println("MODO DE JUEGO: tres ruedas sanas; trasera izquierda apagada");
  Serial.println("Al detectar obstaculo confirmado: reversa corta y exploracion");

  if (MODO_CONTROL_WIFI) {
    Serial.println("MODO WIFI MANUAL: no existe arranque automatico");
    Serial.println("App: OSOYOO Wifi UDP Robot Car Controller");
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
