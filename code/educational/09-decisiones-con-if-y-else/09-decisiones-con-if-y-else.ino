// Curso PX-32 — programa mínimo de la lección 09
// Cargar solo después de leer la sección de seguridad.
int cuenta=0;
void setup(){ Serial.begin(9600); }
void loop(){ bool alcanzo = cuenta >= 5; if(alcanzo){ Serial.println("LIMITE"); } else { Serial.println("ANTES"); } cuenta++; delay(500); }
