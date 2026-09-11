// Curso PX-32 - Leccion 44: medir cuanto dura el eco (ECHO).
// El monitor muestra microsegundos crudos: todavia sin convertir.

const byte TRIG = 30;
const byte ECHO = 31;

// Esperamos a que el eco empiece como maximo 30000 us
// (alrededor de 5 m de viaje de ida y vuelta).
const unsigned long TIMEOUT_US = 30000UL;

unsigned long medirEcoEnUs() {
  digitalWrite(TRIG, LOW);   // secuencia de la Leccion 43
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  return pulseIn(ECHO, HIGH, TIMEOUT_US);  // el cronometro
}

void setup() {
  pinMode(TRIG, OUTPUT);
  digitalWrite(TRIG, LOW);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);
  Serial.println("Leccion 44: duracion del eco en microsegundos.");
}

void loop() {
  unsigned long us = medirEcoEnUs();

  if (us == 0) {
    // pulseIn espero en vano a que ECHO subiera.
    Serial.println("SIN ECO: el pulso nunca empezo");
  } else if (us > 23200UL) {
    // 23200 us equivale a unos 400 cm: fuera de alcance util.
    Serial.print("ECO DEMORADO: ");
    Serial.print(us);
    Serial.println(" us (fuera de alcance)");
  } else {
    Serial.print("eco: ");
    Serial.print(us);
    Serial.println(" us");
  }

  delay(200);
}
