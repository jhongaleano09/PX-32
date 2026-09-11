// Curso PX-32 — programa mínimo de la lección 70
// Cargar solo después de leer la sección de seguridad.
#include <Servo.h>
Servo cabeza; const byte TRIG=30,ECHO=31,PIN_SERVO=13;
float distancia(){ digitalWrite(TRIG,LOW); delayMicroseconds(2); digitalWrite(TRIG,HIGH); delayMicroseconds(10); digitalWrite(TRIG,LOW); unsigned long us=pulseIn(ECHO,HIGH,30000UL); return us?us*0.0343/2.0:-1; }
void setup(){ Serial.begin(9600); pinMode(TRIG,OUTPUT); pinMode(ECHO,INPUT); cabeza.attach(PIN_SERVO); }
void loop(){ for(int a=45;a<=135;a+=45){ cabeza.write(a); delay(500); Serial.print(a); Serial.print(','); Serial.println(distancia()); } cabeza.write(90); delay(1500); }
