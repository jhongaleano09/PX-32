// Curso PX-32 — programa mínimo de la lección 67
// Cargar solo después de leer la sección de seguridad.
// Puente de diagnóstico ESP8266 por Serial1. No contiene credenciales.
void setup(){ Serial.begin(9600); Serial1.begin(115200); Serial.println("Escribe AT; no conectes Bluetooth a la vez"); }
void loop(){ while(Serial.available()) Serial1.write(Serial.read()); while(Serial1.available()) Serial.write(Serial1.read()); }
