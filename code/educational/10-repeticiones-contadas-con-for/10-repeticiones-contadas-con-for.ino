// Curso PX-32 — programa mínimo de la lección 10
// Cargar solo después de leer la sección de seguridad.
void setup(){ pinMode(LED_BUILTIN,OUTPUT); }
void loop(){ for(int i=0;i<4;i++){ digitalWrite(LED_BUILTIN,HIGH); delay(150); digitalWrite(LED_BUILTIN,LOW); delay(150); } delay(1500); }
