// Curso PX-32 — programa mínimo de la lección 44
// Cargar solo después de leer la sección de seguridad.
const byte TRIG=30,ECHO=31;
void setup(){ pinMode(TRIG,OUTPUT); pinMode(ECHO,INPUT); Serial.begin(9600); }
void loop(){ digitalWrite(TRIG,LOW); delayMicroseconds(2); digitalWrite(TRIG,HIGH); delayMicroseconds(10); digitalWrite(TRIG,LOW); unsigned long us=pulseIn(ECHO,HIGH,30000UL); if(us==0) Serial.println("SIN_ECO"); else { float cm=us*0.0343/2.0; Serial.println(cm); } delay(100); }
