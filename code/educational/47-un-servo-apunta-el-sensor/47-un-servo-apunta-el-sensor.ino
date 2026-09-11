// Curso PX-32 — programa mínimo de la lección 47
// Cargar solo después de leer la sección de seguridad.
#include <Servo.h>
Servo cabeza; const byte PIN_SERVO=13;
void setup(){ cabeza.attach(PIN_SERVO); }
void loop(){ for(int a=45;a<=135;a+=45){ cabeza.write(a); delay(700); } cabeza.write(90); delay(1200); }
