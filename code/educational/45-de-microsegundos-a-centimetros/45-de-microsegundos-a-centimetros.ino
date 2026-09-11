// Curso PX-32 - Leccion 45: de microsegundos a centimetros.
// distancia_cm = eco_us x 0.0343 / 2  (343 m/s a ~20 grados C,
// dividido entre 2 porque el sonido va y vuelve).

const byte TRIG = 30;
const byte ECHO = 31;
const unsigned long TIMEOUT_US = 30000UL;

// Velocidad del sonido a ~20 grados C: 343 m/s = 0.0343 cm/us.
const float SONIDO_CM_POR_US = 0.0343;

unsigned long medirEcoEnUs() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  return pulseIn(ECHO, HIGH, TIMEOUT_US);
}

float distanciaEnCm(unsigned long ecoUs) {
  return ecoUs * SONIDO_CM_POR_US / 2.0;  // entre 2: ida y vuelta
}

void setup() {
  pinMode(TRIG, OUTPUT);
  digitalWrite(TRIG, LOW);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);
  Serial.println("Leccion 45: distancia estimada en cm.");
}

void loop() {
  unsigned long us = medirEcoEnUs();

  if (us == 0) {
    Serial.println("SIN ECO: nada fiable adelante");
  } else if (us > 23200UL) {
    Serial.println("ECO DEMORADO: fuera de alcance");
  } else {
    Serial.print(us);
    Serial.print(" us  ->  ");
    Serial.print(distanciaEnCm(us), 1);
    Serial.println(" cm");
  }

  delay(200);
}
