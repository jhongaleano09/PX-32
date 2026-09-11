// Curso PX-32 — programa mínimo de la lección 38
// Cargar solo después de leer la sección de seguridad.
const byte EN[4]={9,10,11,12};
const byte P1[4]={22,26,5,7};
const byte P2[4]={24,28,6,8};
// Orden: frontal derecha, frontal izquierda, trasera derecha, trasera izquierda.
void rueda(byte i,int sentido,byte pwm){
  digitalWrite(P1[i],sentido>0?HIGH:LOW);
  digitalWrite(P2[i],sentido<0?HIGH:LOW);
  analogWrite(EN[i],sentido==0?0:pwm);
}
void parar(){ for(byte i=0;i<4;i++) rueda(i,0,0); }
void mover(int fd,int fi,int td,int ti,byte pwm){
  int s[4]={fd,fi,td,ti}; for(byte i=0;i<4;i++) rueda(i,s[i],pwm);
}
void prepararMotores(){ for(byte i=0;i<4;i++){ pinMode(EN[i],OUTPUT); pinMode(P1[i],OUTPUT); pinMode(P2[i],OUTPUT); } parar(); }
const byte PINES[5]={A4,A3,A2,A1,A0}; const int LINEA=LOW;
void setup(){ prepararMotores(); for(byte i=0;i<5;i++) pinMode(PINES[i],INPUT); delay(3000); }
void loop(){ int suma=0,cuantos=0; for(byte i=0;i<5;i++){ if(digitalRead(PINES[i])==LINEA){ suma+=int(i)-2; cuantos++; } }
  if(cuantos==0) parar(); else { float pos=float(suma)/cuantos; if(pos<-0.4) mover(-1,+1,-1,+1,55); else if(pos>0.4) mover(+1,-1,+1,-1,55); else mover(+1,+1,+1,+1,65); } delay(20); }
