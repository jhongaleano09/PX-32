// Curso PX-32 — programa mínimo de la lección 20
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
void paso(const char* nombre,int fd,int fi,int td,int ti){
  Serial.println(nombre); mover(fd,fi,td,ti,70); delay(500); parar(); delay(1000);
}
void setup(){ Serial.begin(9600); prepararMotores(); delay(3000);
  // +1/-1 son sentidos lógicos. Confirma en L18 cuál corresponde al avance físico.
  paso("PATRON 1",+1,+1,+1,+1); paso("PATRON 2",-1,-1,-1,-1);
  paso("PATRON 3",+1,-1,-1,+1); paso("PATRON 4",-1,+1,+1,-1);
  paso("PATRON 5",-1,+1,-1,+1); paso("PATRON 6",+1,-1,+1,-1);
}
void loop(){ parar(); }
