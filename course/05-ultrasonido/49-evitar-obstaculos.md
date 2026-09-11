# Lección 49 — Evitar obstáculos

## 1. Tu misión de hoy

Hoy vas a **detenerse, observar y escoger un lado libre antes de avanzar**. Al terminar podrás demostrarlo con una explicación, un dato o un comportamiento observable; no basta con decir “funcionó”.

## 2. Tiempo estimado

- Lectura y conversación inicial: 10 minutos.
- Preparación y predicción: 5 minutos.
- Actividad o programación: 15 minutos.
- Desafío y depuración: 5 minutos.
- Cuéntale a papá y resumen: 5 minutos.

**Total: 40 minutos.** Si aparece una duda de cableado o la actividad necesita más intentos, detente al terminar la preparación y continúa otro día; la seguridad no se comprime para cumplir el reloj.

## 3. Lo que necesitas saber antes de empezar

[Lección 20: Vectores para mover PX-32](../02-movimiento/20-vectores-para-mover-px-32.md), [Lección 48: Escaneo espacial](48-escaneo-espacial.md). Debes poder explicar su idea central y repetir su prueba segura antes de continuar.

También necesitas distinguir tres capas de PX-32: la **energía** permite que algo ocurra, la **señal** representa información u órdenes y el **programa** decide qué hacer con ellas. Cuando algo falle, pregunta primero en cuál capa está la evidencia. Consulta el [glosario general](../../docs/reference/glosario.md) y el [mapa canónico de conexiones](../../docs/reference/mapa-conexiones-robot.md) sin modificar el montaje.

## 4. Lectura principal

### La idea intuitiva

El tema de hoy es **umbral de seguridad, elección y maniobra**. En lenguaje cotidiano, buscamos una forma fiable de detenerse, observar y escoger un lado libre antes de avanzar. La palabra “fiable” importa: una sola coincidencia puede ser suerte; una explicación científica conecta una causa, una prueba y un resultado que otra persona podría repetir.

El módulo ultrasónico estima distancia midiendo tiempo, no extendiendo una regla invisible. Envía una onda, espera un eco y usa la velocidad aproximada del sonido. El servo añade dirección y convierte una medición puntual en un pequeño mapa. Toda estimación tiene límites: objetos blandos, inclinados, muy cercanos o estrechos pueden devolver ecos débiles.

### De la intuición al concepto técnico

Los términos centrales son **umbral de seguridad, elección y maniobra**. No son etiquetas decorativas: cada uno nombra una relación que podremos observar. Una analogía útil es pensar en una receta: ingredientes, pasos y resultado ayudan a organizar la acción. Pero la analogía tiene límite; PX-32 no “sabe” qué desea el cocinero y un componente real responde a voltaje, tiempo, geometría y código, no a intenciones.

En PX-32, esta idea se usa para simular decisiones por Serial y luego probar a baja velocidad. Antes de actuar, separa cuatro preguntas: ¿qué cambiaremos?, ¿qué mantendremos igual?, ¿qué mediremos?, ¿qué resultado nos obligaría a detenernos? Ese orden convierte una demostración llamativa en un experimento. Si modificamos dos cosas a la vez, perdemos la posibilidad de saber cuál causó el cambio.

Un error frecuente es confundir el nombre de una pieza con una explicación. Decir “es un sensor” no explica qué magnitud detecta, qué señal entrega ni bajo qué condiciones puede equivocarse. Otro error es atribuir intención al programa: una condición `if` no “comprende” el obstáculo; compara representaciones y ejecuta una rama. Pregunta de reflexión: **¿qué evidencia distinguiría una decisión correcta de una coincidencia?**

La meta no es memorizar todo en una lectura. Primero forma un modelo: entrada → transformación → salida. Después contrástalo con la actividad. Si el resultado no coincide, el modelo gana detalle. Esa revisión es aprendizaje científico, no fracaso.

## 5. Palabras nuevas

- **Umbral de seguridad:** idea principal que podrás reconocer en la actividad.
- **Evidencia:** observación o medición que apoya o contradice una explicación.
- **Variable de prueba:** elemento que cambiamos deliberadamente mientras mantenemos los demás lo más estables posible.
- **Fallo seguro:** estado que reduce el riesgo cuando falta información; en PX-32 suele ser `STOP`.

Puedes consultar definiciones relacionadas en el [glosario general](../../docs/reference/glosario.md).

## 6. Así aparece en PX-32

**Hardware:** HW-004 a HW-006, HW-009, HW-010.

```text
fenómeno o comando → sensor/interfaz → pin y programa → decisión → actuador o mensaje
                         ↑                         |
                         └──── evidencia Serial ──┘
```

La cadena exacta de hoy se concentra en **umbral de seguridad, elección y maniobra**. No cambies conexiones basándote solo en este esquema conceptual. Para pines usa el [mapa canónico](../../docs/reference/mapa-conexiones-robot.md); para discrepancias usa la [errata del manual](../../docs/reference/errata-osoyoo.md). Los límites de potencia y la configuración interna del portabaterías siguen `PENDIENTE_DE_VERIFICAR`.

## 7. Seguridad y participación del adulto

- 🟢 El estudiante predice, lee el código y registra observaciones.
- 🟡 Un adulto permanece presente durante USB, calibración o cualquier prueba física.
- 🔴 El adulto manipula baterías 18650, interruptores de potencia, driver y cables. Toda conexión se revisa sin USB y con alimentación apagada.

Para movimiento: primero ruedas levantadas sobre una base estable, velocidad baja, área despejada y el interruptor accesible. Cabello, mangas y dedos lejos de ruedas. Si hay calor, olor, humo, chispa, zumbido fuerte o movimiento inesperado, el adulto corta energía; no se intenta frenar con la mano.

## 8. Predice antes de probar

1. ¿Qué esperas observar cuando logres detenerse, observar y escoger un lado libre antes de avanzar y qué mecanismo produciría ese resultado?
2. ¿Qué observación contraria te haría detenerte o revisar la explicación?

Respóndelas en voz alta o en tu cuaderno físico. No necesitas un diario digital.

## 9. Actividad o experimento guiado

1. **Preparar.** Coloca PX-32 estable, identifica HW-004 a HW-006, HW-009, HW-010 y confirma con el adulto que la energía está en el estado seguro. Continúa solo si no hay cables sueltos, daño, calor u olor.
2. **Trazar.** Señala la ruta entrada → proceso → salida relacionada con umbral de seguridad, elección y maniobra. Si no puedes justificar un pin, consulta el mapa; no adivines.
3. **Predecir.** Elige un resultado concreto y una señal de parada. Di qué variable cambiarás y cuáles permanecerán iguales.
4. **Probar.** Vas a simular decisiones por Serial y luego probar a baja velocidad. Haz un solo cambio. Observa antes de repetir y mantén accesible la forma de detener la prueba.
5. **Comprobar.** El resultado que permite continuar es: STOP antecede al giro y ninguna lectura ausente autoriza avance. Si no aparece, apaga cuando corresponda y pasa a “Si no funciona”.
6. **Repetir.** Realiza una segunda prueba cambiando solo un valor, posición o entrada. Compara, no persigas un resultado “bonito”.
7. **Restaurar.** Detén el programa, apaga la alimentación y devuelve cualquier ajuste temporal a su posición anotada. El adulto confirma que PX-32 conserva su ensamblaje y que ningún cable invade ruedas o engranajes.

## 10. Código

Abre [49-evitar-obstaculos.ino](../../code/educational/49-evitar-obstaculos/49-evitar-obstaculos.ino). Antes de cargarlo, localiza `setup()`, `loop()` y la línea que representa **umbral de seguridad**. Lee el programa de arriba abajo y predice su salida.

```cpp
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
```

La sintaxis —llaves, paréntesis y punto y coma— permite que el compilador separe instrucciones. El comportamiento es lo que ocurre al ejecutarlas. El propósito de este sketch es aislar la idea de hoy; todavía no es el programa final del robot. No añadas una segunda mejora hasta comprobar la primera.

## 11. Qué deberías observar

El resultado normal es **STOP antecede al giro y ninguna lectura ausente autoriza avance**. Puede haber variación por tolerancias, superficie, luz, fricción, carga, eco o tiempos del programa. Una variación pequeña y repetible es información; un salto grande, un reinicio, una lectura imposible o un movimiento inesperado exige STOP.

No concluyas “está dañado” por un solo dato. Tampoco concluyas “es seguro” porque funcionó una vez. Repite bajo las mismas condiciones y compara. En sensores, conserva una condición conocida; en código, observa Serial; en movimiento, vuelve primero a ruedas levantadas.

## 12. Si no funciona

| Síntoma | Prueba sencilla | Interpretación | Siguiente acción segura |
|---|---|---|---|
| No ocurre nada | Comprueba alimentación lógica, placa y programa esperado | Puede faltar energía o haberse elegido placa/puerto incorrectos | Detén, revisa una capa y vuelve a intentar |
| El dato no cambia | Cambia solo la entrada física prevista | El sensor, pin o lógica puede no coincidir | Imprime la lectura cruda y compárala con el mapa |
| El resultado es intermitente | Repite sin mover cables y observa el tiempo | Puede haber umbral, ruido o conexión inestable | Apaga; el adulto inspecciona conectores |
| Hay movimiento inesperado, calor u olor | No hagas otra prueba | Es una condición de riesgo, no un reto de software | El adulto corta energía y revisa antes de continuar |

El método es siempre **síntoma → prueba pequeña → interpretación → una acción**. Cambiar cinco cosas puede ocultar el problema y crear uno nuevo.

## 13. Desafío

Diseña una variante que cambie una sola condición de la actividad. Antes de ejecutarla, escribe una frase “Si…, entonces…, porque…”. Luego explica si el resultado apoya la predicción. No copies una solución completa: el valor del desafío está en elegir la variable y justificarla.

## 14. Lecturas y videos para explorar

- [Velocidad, frecuencia y longitud de onda del sonido](https://openstax.org/books/physics/pages/14-1-speed-of-sound-frequency-and-wavelength) — Inglés; libro abierto; 12 min. Aprenderás velocidad, frecuencia y longitud de onda del sonido. Esencial.
- [Biblioteca Servo](https://docs.arduino.cc/libraries/servo/) — Inglés; referencia oficial Arduino; 10 min. Aprenderás biblioteca servo. Opcional.

Comprueba con un adulto antes de abandonar el material del curso. Un recurso externo amplía la explicación; nunca reemplaza el mapa de conexiones ni las reglas de seguridad de PX-32.

## 15. Cuéntale a papá

- Cuéntale con tus palabras qué significa **umbral de seguridad** y dónde aparece en PX-32.
- Muéstrale la evidencia y explícale qué cambiaste y qué mantuviste igual.
- Pregúntale qué ejemplo parecido conoce fuera de la robótica.
- Explícale un error posible y la prueba pequeña que usarías para localizarlo.
- Dile qué te gustaría probar después y qué regla de seguridad conservarías.

Esto es una conversación, no un examen. Si una explicación se atasca, vuelvan juntos al diagrama entrada → proceso → salida.

## 16. Resumen de la jornada

Hoy aprendiste a **detenerse, observar y escoger un lado libre antes de avanzar** y lo conectaste con **umbral de seguridad, elección y maniobra**. Pudiste observar STOP antecede al giro y ninguna lectura ausente autoriza avance. La regla de seguridad es cambiar conexiones únicamente sin energía y usar `STOP` ante información dudosa. La próxima sesión será la [Lección 50: Radio: otra región del espectro](../06-bluetooth/50-radio-otra-region-del-espectro.md).
