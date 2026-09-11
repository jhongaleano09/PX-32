// Curso PX-32 — programa mínimo de la lección 15
// Cargar solo después de leer la sección de seguridad.
const byte ENA=11, IN1=5, IN2=6;
void parar(){ analogWrite(ENA,0); digitalWrite(IN1,LOW); digitalWrite(IN2,LOW); }
void setup(){ pinMode(ENA,OUTPUT); pinMode(IN1,OUTPUT); pinMode(IN2,OUTPUT); parar(); delay(2000); digitalWrite(IN1,HIGH); digitalWrite(IN2,LOW); analogWrite(ENA,80); delay(600); parar(); }
void loop(){ parar(); }
