// Curso PX-32 — programa mínimo de la lección 08
// Cargar solo después de leer la sección de seguridad.
unsigned long cuenta=0;
void setup(){ Serial.begin(9600); Serial.println("Hola, soy PX-32"); }
void loop(){ Serial.print("Cuenta: " ); Serial.println(cuenta++); delay(1000); }
