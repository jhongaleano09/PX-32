// Curso PX-32 - Leccion 43: enviar el pulso TRIG.
// Hoy solo aprendemos a dar la orden: todavia no medimos el eco.

const byte TRIG = 30;  // orden: cable desde D30 al pin Trig del modulo
const byte ECHO = 31;  // respuesta: cable desde el pin Echo a D31 (manana)

void setup() {
  pinMode(TRIG, OUTPUT);    // TRIG lo maneja la Mega
  digitalWrite(TRIG, LOW);  // empezar en reposo
  pinMode(ECHO, INPUT);     // ECHO lo maneja el modulo
  Serial.begin(9600);
  Serial.println("Leccion 43: solo TRIG.");
  Serial.println("El eco se mide en la Leccion 44.");
}

void loop() {
  Serial.println("--- nuevo pulso ---");

  Serial.println("1) TRIG en LOW  durante 2 us (reposo)");
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  Serial.println("2) TRIG en HIGH durante 10 us (la orden)");
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  Serial.println("3) TRIG vuelve a LOW (fin de la orden)");
  digitalWrite(TRIG, LOW);

  Serial.println("El modulo acaba de emitir su rafaga silenciosa.");
  delay(1000);  // pausa humana: un pulso por segundo
}
