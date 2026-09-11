// Curso PX-32 - Leccion 46: medir objetos conocidos.
// Tres distancias reales, cinco mediciones cada una.
// Tu trabajo: copiar la tabla en el cuaderno, ordenar cada
// grupo de cinco y hallar la mediana (el valor del medio).

const byte TRIG = 30;
const byte ECHO = 31;
const unsigned long TIMEOUT_US = 30000UL;
const float SONIDO_CM_POR_US = 0.0343;
const byte DISPAROS = 5;  // cinco mediciones por distancia

unsigned long medirEcoEnUs() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  return pulseIn(ECHO, HIGH, TIMEOUT_US);
}

void rondaDeMediciones(const char *nombre, int realCm) {
  Serial.print("=== ");
  Serial.print(nombre);
  Serial.print(" | real: ");
  Serial.print(realCm);
  Serial.println(" cm ===");

  for (byte i = 1; i <= DISPAROS; i++) {
    unsigned long us = medirEcoEnUs();
    Serial.print(i);
    Serial.print(": ");

    if (us == 0) {
      Serial.println("SIN ECO");
    } else if (us > 23200UL) {
      Serial.println("FUERA DE ALCANCE");
    } else {
      Serial.print(us * SONIDO_CM_POR_US / 2.0, 1);
      Serial.println(" cm");
    }

    delay(150);  // pausa entre disparos para no mezclar ecos
  }
}

void setup() {
  pinMode(TRIG, OUTPUT);
  digitalWrite(TRIG, LOW);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);
  Serial.println("Leccion 46: cinco mediciones por distancia.");
  Serial.println("Coloca el objeto: la ronda empieza en 3 segundos.");
  delay(3000);  // tiempo para apartar la mano
}

void loop() {
  rondaDeMediciones("CERCA", 10);
  delay(500);
  rondaDeMediciones("MEDIA", 20);
  delay(500);
  rondaDeMediciones("LEJOS", 30);
  Serial.println("Copia la tabla y busca la mediana de cada grupo.");
  Serial.println("Siguiente ronda en 30 segundos...");
  delay(30000);  // tiempo de copiar con calma
}
