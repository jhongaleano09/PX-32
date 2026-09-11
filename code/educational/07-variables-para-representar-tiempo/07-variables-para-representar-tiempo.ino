// Curso PX-32 — programa mínimo de la lección 07
// Cargar solo después de leer la sección de seguridad.
const byte LED = LED_BUILTIN;
const unsigned long INTERVALO_MS = 500;
void setup(){ pinMode(LED,OUTPUT); }
void loop(){ digitalWrite(LED,HIGH); delay(INTERVALO_MS); digitalWrite(LED,LOW); delay(INTERVALO_MS); }
