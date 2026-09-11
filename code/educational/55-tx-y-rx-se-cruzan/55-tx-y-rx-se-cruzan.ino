// Curso PX-32 — programa mínimo de la lección 55
// Cargar solo después de leer la sección de seguridad.
unsigned long ultimo=0;
void setup(){ Serial.begin(9600); Serial1.begin(9600); }
void loop(){ if(Serial1.available()){ char c=Serial1.read(); ultimo=millis(); if(c=='F'||c=='B'||c=='L'||c=='R'||c=='S') Serial.println(c); else Serial.println("STOP_DATO_INVALIDO"); } if(millis()-ultimo>500) Serial.println("STOP_TIMEOUT"); delay(100); }
