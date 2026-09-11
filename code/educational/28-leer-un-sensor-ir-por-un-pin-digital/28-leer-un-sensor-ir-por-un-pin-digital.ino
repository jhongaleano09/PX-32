// Curso PX-32 - Leccion 28: leer el sensor IR izquierdo en D3.

const byte SENSOR_IR_IZQUIERDO = 3;

void setup() {
  pinMode(SENSOR_IR_IZQUIERDO, INPUT);
  Serial.begin(9600);
}

void loop() {
  int lectura = digitalRead(SENSOR_IR_IZQUIERDO);
  Serial.println(lectura);
  delay(200);
}
