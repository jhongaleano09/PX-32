// Curso PX-32 — programa mínimo de la lección 36
// Cargar solo después de leer la sección de seguridad.
const byte PINES[5]={A4,A3,A2,A1,A0}; const int LINEA=LOW;
void setup(){ Serial.begin(9600); for(byte i=0;i<5;i++) pinMode(PINES[i],INPUT); }
void loop(){ int suma=0,cuantos=0; for(byte i=0;i<5;i++){ if(digitalRead(PINES[i])==LINEA){ suma+=int(i)-2; cuantos++; } }
  if(cuantos==0) Serial.println("STOP_LINEA_PERDIDA"); else { float pos=float(suma)/cuantos; if(pos<-0.4) Serial.println("CORRIGE_IZQ"); else if(pos>0.4) Serial.println("CORRIGE_DER"); else Serial.println("AVANZA"); } delay(100); }
