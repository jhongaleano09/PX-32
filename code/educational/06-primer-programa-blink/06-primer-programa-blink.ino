// Curso PX-32 — programa mínimo de la lección 06
// Cargar solo después de leer la sección de seguridad.
const byte LED = LED_BUILTIN;
void setup() { pinMode(LED, OUTPUT); }
void loop() { digitalWrite(LED,HIGH); delay(500); digitalWrite(LED,LOW); delay(500); }
