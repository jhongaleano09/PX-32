// Curso PX-32 - Leccion 47: un servo apunta el sensor.
// El servo recibe ordenes de posicion, no de velocidad.

#include <Servo.h>

const byte PIN_SERVO = 13;  // cable de senal llega a D13 via el Model Y

Servo cabeza;  // el servo que gira el sensor ultrasonico

void setup() {
  Serial.begin(9600);
  Serial.println("Leccion 47: centrando la cabeza en 90 grados.");
  cabeza.attach(PIN_SERVO);  // la biblioteca envia los pulsos
  cabeza.write(90);          // 90 = mirar al frente
  delay(1500);               // tiempo de llegar y asentarse
}

void loop() {
  Serial.println("mirando a 45 grados");
  cabeza.write(45);
  delay(1500);

  Serial.println("mirando a 90 grados (frente)");
  cabeza.write(90);
  delay(1500);

  Serial.println("mirando a 135 grados");
  cabeza.write(135);
  delay(1500);

  Serial.println("de vuelta al frente");
  cabeza.write(90);
  delay(2000);
}
