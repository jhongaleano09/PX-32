// Curso PX-32 — programa mínimo de la lección 49
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
#include <Servo.h>
Servo cabeza; const byte TRIG=30,ECHO=31; float cm(){ digitalWrite(TRIG,LOW); delayMicroseconds(2); digitalWrite(TRIG,HIGH); delayMicroseconds(10); digitalWrite(TRIG,LOW); unsigned long us=pulseIn(ECHO,HIGH,30000UL); return us?us*0.0343/2.0:-1; }
void setup(){ prepararMotores(); pinMode(TRIG,OUTPUT); pinMode(ECHO,INPUT); cabeza.attach(13); cabeza.write(90); delay(3000); }
void loop(){ float frente=cm(); if(frente<0||frente<25){ parar(); cabeza.write(45); delay(500); float izq=cm(); cabeza.write(135); delay(500); float der=cm(); cabeza.write(90); if(izq<0||der<0) parar(); else if(izq>der) mover(-1,+1,-1,+1,60); else mover(+1,-1,+1,-1,60); delay(350); parar(); } else mover(+1,+1,+1,+1,60); delay(40); }
