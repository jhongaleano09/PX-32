// Curso PX-32 — programa mínimo de la lección 57
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
unsigned long ultimaOrden=0;
void setup(){ prepararMotores(); Serial1.begin(9600); delay(3000); }
void loop(){ if(Serial1.available()){ char c=Serial1.read(); ultimaOrden=millis(); if(c=='F') mover(+1,+1,+1,+1,70); else if(c=='B') mover(-1,-1,-1,-1,70); else if(c=='L') mover(-1,+1,-1,+1,65); else if(c=='R') mover(+1,-1,+1,-1,65); else parar(); }
  if(millis()-ultimaOrden>500) parar(); }
