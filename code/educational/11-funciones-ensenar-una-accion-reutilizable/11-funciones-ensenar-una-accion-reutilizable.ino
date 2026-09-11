// Curso PX-32 — programa mínimo de la lección 11
// Cargar solo después de leer la sección de seguridad.
void parpadear(int veces,int intervalo){ for(int i=0;i<veces;i++){ digitalWrite(LED_BUILTIN,HIGH); delay(intervalo); digitalWrite(LED_BUILTIN,LOW); delay(intervalo); } }
void setup(){ pinMode(LED_BUILTIN,OUTPUT); }
void loop(){ parpadear(3,200); delay(1500); }
