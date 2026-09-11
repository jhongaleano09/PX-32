// Curso PX-32 — programa mínimo de la lección 71
// Cargar solo después de leer la sección de seguridad.
enum Estado { STOP, MANUAL, AUTO };
Estado estado=STOP; unsigned long ultimaOrden=0;
void detener(){ /* escribir aquí las salidas seguras del bloque de movimiento */ }
void setup(){ Serial.begin(9600); detener(); }
void loop(){ if(Serial.available()){ char c=Serial.read(); ultimaOrden=millis(); if(c=='S') estado=STOP; else if(c=='M') estado=MANUAL; else if(c=='A') estado=AUTO; else estado=STOP; } if(millis()-ultimaOrden>500) estado=STOP; if(estado==STOP) detener(); Serial.println(estado); delay(100); }
