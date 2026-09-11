// Curso PX-32 — programa mínimo de la lección 28
// Cargar solo después de leer la sección de seguridad.
const byte IR_IZQ=3, IR_DER=2;
void setup(){ pinMode(IR_IZQ,INPUT); pinMode(IR_DER,INPUT); Serial.begin(9600); }
void loop(){ int izq=digitalRead(IR_IZQ), der=digitalRead(IR_DER); Serial.print(izq); Serial.print(','); Serial.println(der); delay(100); }
