// Curso PX-32 — programa mínimo de la lección 34
// Cargar solo después de leer la sección de seguridad.
const byte PINES[5]={A4,A3,A2,A1,A0};
void setup(){ Serial.begin(9600); for(byte i=0;i<5;i++) pinMode(PINES[i],INPUT); }
void loop(){ for(byte i=0;i<5;i++) Serial.print(digitalRead(PINES[i])); Serial.println(); delay(100); }
