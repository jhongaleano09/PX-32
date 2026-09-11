# Lección 47 — Un servo apunta el sensor

## El motor que no sabe girar, solo obedecer posiciones

Todos los motores que PX-32 tiene en las ruedas (Lección 12) son iguales en su alma: les llega corriente y **giran sin parar**, hasta que cortas la corriente. Les da igual dónde quedaron. Perfectos para rodar; inútiles para apuntar.

Hoy estrena un músculo de otra especie. En el frente del chasis, justo debajo del soporte del sensor ultrasónico, vive un **microservo MG90** (HW-010): un motor chico con caja reductora, un sensor de posición interno y una electrónica que no deja de hacer una sola pregunta: "¿estoy en el ángulo que me ordenaron?". Si no lo está, corrige; si lo está, se queda ahí y aguanta. No le ordenas velocidad como a las ruedas: le ordenas **posición**. "Quédate mirando a 45 grados" — y ahí se queda.

Ese talento es exactamente lo que necesita un sensor de distancias: los cilindros T y R miden lo que tienen **enfrente**, y con el servo debajo, PX-32 podrá girar su "cabeza" para mirar a la izquierda, al centro o a la derecha sin mover una rueda. Hoy no mediremos nada: hoy es el día del cuello.

¿Y cómo se le ordena un ángulo a algo que no tiene botones? Con la misma idea de la Lección 17: **pulsos rápidos que se repiten**. Al servo le llegan pulsos de control unas decenas de veces por segundo; el *ancho* de cada pulso (entre menos de un milisegundo y dos y pico) codifica el ángulo. No vas a fabricar esos pulsos a mano: la **biblioteca `Servo`** de Arduino los genera por ti, y tu programa solo dice `write(ángulo)`. La biblioteca es el traductor entre tu número y el idioma de pulsos del servo.

## Lo que necesitas

- PX-32 ensamblado, en la mesa, con espacio libre de 30 cm alrededor de la cabeza del sensor (nada que el soporte pueda golpear al girar).
- El servo MG90 conectado según el mapa: cable **naranja (señal)** al bloque S del Model Y que llega a **D13**, **rojo** a 5V, **marrón** a GND. 🟡 Verifícalo con tu padre con el robot apagado; si hay que tocar, lo hace él 🔴.
- Computador con Arduino IDE 2, cable USB, y **baterías 18650 con carga** (gestionadas por el adulto) para la fase de movimiento.
- El sketch [47-un-servo-apunta-el-sensor.ino](../../code/educational/47-un-servo-apunta-el-sensor/47-un-servo-apunta-el-sensor.ino).
- Tu cuaderno: hoy nace un dato que las lecciones 48 y 49 necesitarán.

🟢 Programar, cargar y anotar es tuyo. 🟡 El adulto presencia el USB y la fase de batería. 🔴 Baterías, interruptor y cualquier cable: el adulto, siempre con todo apagado al manipular.

## El programa: tres posiciones y un centro

1. 🟢 Abre el `.ino` y verifica que coincida con este bloque:

```cpp
// Curso PX-32 - Leccion 47: un servo apunta el sensor.
// El servo recibe ordenes de posicion, no de velocidad.

#include <Servo.h>

const byte PIN_SERVO = 13;  // cable de senal llega a D13 via el Model Y

Servo cabeza;  // el servo que gira el sensor ultrasonico

void setup() {
  Serial.begin(9600);
  Serial.println("Leccion 47: centrando la cabeza en 90 grados.");
  cabeza.attach(PIN_SERVO);  // la biblioteca envia los pulsos
  cabeza.write(90);          // 90 = mirar al frente
  delay(1500);               // tiempo de llegar y asentarse
}

void loop() {
  Serial.println("mirando a 45 grados");
  cabeza.write(45);
  delay(1500);

  Serial.println("mirando a 90 grados (frente)");
  cabeza.write(90);
  delay(1500);

  Serial.println("mirando a 135 grados");
  cabeza.write(135);
  delay(1500);

  Serial.println("de vuelta al frente");
  cabeza.write(90);
  delay(2000);
}
```

2. 🟢 **Lo nuevo, en cuatro piezas:**

   - `#include <Servo.h>` le pide al compilador que traiga la biblioteca oficial de servos de Arduino (viene instalada con el IDE). Es la primera vez en el curso que usas una biblioteca: código escrito y probado por otros, que tú invitas a tu sketch.
   - `Servo cabeza;` declara un **objeto** servo con nombre propio. Se llama `cabeza` porque literalmente es la cabeza del robot. Un objeto es una variable con superpoderes: sabe hacer cosas (`write`, `attach`).
   - `cabeza.attach(PIN_SERVO)` conecta el objeto con el pin D13 — que la Mega ya sabe que existe por el cable naranja del Model Y. Desde `attach`, la biblioteca le está mandando pulsos al servo **sin que tú escribas ningún `digitalWrite`**.
   - `cabeza.write(45)` ordena el ángulo 45. Los ángulos van de 0 a 180: 90 es el centro, y 45 y 135 son 45 grados a cada lado del centro.

3. 🟢 **Un detalle de convivencia en D13.** El pin 13 es famoso: es el mismo del LED `L` integrado de la placa (tu Blink de la Lección 06). Con `Servo` activo en D13, ese LED puede encenderse débil o parpadear con los pulsos: **es normal**, no es un error. La regla práctica que aprendiste en HW-010: mientras el servo viva en D13, no vuelvas a usar D13 para Blink. Y un dato que tranquiliza: en la Mega 2560, hasta 12 servos conviven con `analogWrite()` sin pelearse por los temporizadores — tus PWM de motores en 9, 10, 11 y 12 están a salvo.

4. 🟢 **Predice la coreografía.** Antes de cargar, dibuja en el cuaderno una flecha (el sensor) y qué debe hacer: centro al arrancar, luego 45, 90, 135, centro, y repetir. La pregunta del día —que solo tu robot puede responder— es esta: **con el sensor mirándote a ti de frente, ¿hacia qué lado de TU vista apunta 45°, y hacia cuál 135°?** Escribe tu apuesta: "45 apunta hacia mi ___". (La respuesta depende de cómo quedó montado el servo: no se puede deducir desde un manual, y por eso hoy se mide.)

5. 🟡 **Fase 1 — solo USB.** Tu padre conecta el USB, sube el sketch y abre el monitor a 9600. Observa qué pasa y qué no: las líneas deben avanzar cada 1,5 s. **El servo puede quedarse inmóvil.** No es un error: por el mapa de conexiones, la alimentación del servo viene del lado del Model Y, que se energiza con las baterías; con solo USB, la Mega le manda las órdenes pero al servo puede faltarle el músculo. Si en tu robot el servo sí se mueve con USB, anótalo también — cada robot declara su propia verdad, y esa es la costumbre de este curso.

6. 🔴 **Fase 2 — con energía.** El adulto retira el USB, instala las celdas 18650 y enciende el interruptor, con las ruedas apoyadas en la mesa (este sketch no envía ninguna orden a los motores: solo mueve la cabeza) y las manos lejos del soporte. Al encender, el servo debe **centrarse en 90° y quedarse ahí 1,5 s** antes de empezar el ciclo.

7. 🔴 **La alineación sagrada del fabricante.** Mira el sensor desde arriba: en 90° debe quedar **mirando exactamente al frente**, en línea con el chasis. El manual de OSOYOO dedica un procedimiento entero a esto: si al encender el sensor **no** queda al frente, el adulto apaga de inmediato, y con todo apagado se reajusta el soporte sobre el eje del servo hasta que en 90° mire derecho. Un sensor mal alineado arruina todos los barridos que vienen — es la diferencia entre "90 = frente" y "90 = mirando raro hacia la esquina".

8. 🟢 **Observa el ciclo y llena el dato del día.** Con el ciclo girando, párate **detrás** del robot (tú y el robot mirando al mismo horizonte, como en la Lección 20) y observa a dónde apunta el sensor en 45 y en 135. Anota en el cuaderno, con letra grande:

   ```text
   ANGULO 45 apunta hacia mi IZQUIERDA / DERECHA  (tacha lo que no sea)
   ANGULO 135 apunta hacia mi IZQUIERDA / DERECHA
   ```

   Ese dato es **oro**: la Lección 48 lo usará para nombrar sus barridos y la 49 para girar hacia el lado correcto al esquivar. Igual que el lado de IR1 en la Lección 34, es una verdad de TU robot que ningún manual puede darte.

9. 🟢 **Escucha a tu servo.** Aparte del movimiento, usa los oídos: al llegar a cada posición puede sonar un "toc" corto de asentamiento, y eso está bien. Lo que NO está bien es un **zumbido continuo** o un chirrido en una posición: sería el servo forcejeando contra algo (un cable, un tope). Si aparece, avisa al adulto: apagar, revisar que nada tropiece con el soporte y reintentar. Y una regla de oro de por vida: **jamás fuerces el eje del servo con la mano** para "acomodarlo" — sus engranajes internos no perdonan.

10. 🔴 **Cierre.** El adulto apaga y retira las celdas. El robot queda con su cabeza al frente (90) y tu cuaderno con el dato del lado de 45°.

> **[PENDIENTE VISUAL]**
> - **Tipo:** diagrama cenital de ángulos del servo.
> - **Objetivo:** fijar qué significan 45°, 90° y 135° vistos desde arriba, y que el niño entienda que el lado de 45/135 depende del montaje.
> - **Descripción:** vista superior del robot con el sensor dibujado como flecha; flecha al centro rotulada "90° = frente", flecha girada a un costado rotulada "45°" y a la otra "135°", con las dos etiquetas laterales marcadas con signo de interrogación: "¿izquierda o derecha? Tu robot responde".
> - **Elementos que deben señalarse:** chasis, flecha-sensor en las tres posiciones, rótulos de ángulos, interrogantes en los costados.
> - **Fuente técnica:** manual OSOYOO, https://osoyoo.com/manual/2021006600-2026.pdf, pp. 31–33, alineación inicial del servo del sensor ultrasónico.
> - **Texto alternativo sugerido:** "Vista superior del robot con el sensor apuntando a 45, 90 y 135 grados; los costados marcados con interrogante porque dependen del montaje".

## Si no funciona

| Síntoma | Qué revisar | Acción |
|---|---|---|
| Con USB no se mueve nada, monitor sí avanza | ¿Fase 1 con solo USB? | Es esperable: el servo puede alimentarse del lado de baterías. Pasa a la fase 2 con el adulto |
| Con baterías tampoco se mueve | ¿Cable naranja/rojo/marrón bien asentados en el Model Y? | 🔴 Apagado, el adulto revisa S/5V/GND contra el mapa; conector invertido es el error clásico |
| En 90° mira torcido | ¿Se corrió el soporte sobre el eje? | Procedimiento de alineación del paso 7: apagar, reajustar soporte, encender, verificar |
| Zumbido continuo en una posición | ¿Algo tropieza con el soporte o el servo llega a un tope? | 🔴 Apagar ya; liberar el camino del soporte; no usar ángulos fuera de 45–135 por ahora |
| El monitor no abre o sale basura | ¿9600 baudios, placa Mega 2560, puerto correcto? | La verificación de siempre de las Lecciones 05 y 08 |
| Se movió a saltos bruscos y se detiene | ¿Celdas con poca carga? (el servo pica corriente al arrancar) | 🔴 El adulto cambia por celdas cargadas antes de culpar al programa |

## Desafío: el recorrido del vigilante

Cambia el programa para que la cabeza haga un ciclo de vigilante: 90 → 60 → 90 → 120 → 90, deteniéndose 1 s en cada posición (es solo cambiar números de `write` y copiar el patrón de `delay`). Carga, observa, y responde: ¿qué ángulos intermedios cubren más territorio nuevo, los cercanos a 90 o los lejanos? Después devuelve el archivo a su forma original, para que el sketch quede como el de referencia.

## Lecturas y videos para explorar

- [Velocidad, frecuencia y longitud de onda del sonido](https://openstax.org/books/physics/pages/14-1-speed-of-sound-frequency-and-wavelength) — Inglés; libro abierto; 12 min. Aprenderás velocidad, frecuencia y longitud de onda del sonido. Esencial.
- [Biblioteca Servo](https://docs.arduino.cc/libraries/servo/) — Inglés; referencia oficial Arduino; 10 min. Aprenderás biblioteca servo. Opcional.

Hoy sí: ese "Opcional" de la biblioteca Servo que acompaña al bloque desde la Lección 39 por fin te toca a ti. Léela con tu padre: `attach`, `write` y el asunto de los temporizadores están explicados por sus autores.

## Referencias técnicas de la clase

- [Biblioteca Servo de Arduino](https://docs.arduino.cc/libraries/servo/): `attach()`, `write()` y la nota sobre PWM: en la Mega, hasta 12 servos no interfieren con `analogWrite()`.
- [HW-010 en el diccionario de hardware](../../docs/hardware/HW-010-servo-mg90.md): conexión S/5V/GND por el Model Y y errores frecuentes.
- [Manual OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), pp. 31–33: alineación inicial del servo del sensor ultrasónico (si en 90° no mira al frente, se reajusta apagado).

## Cuéntale a papá

Muéstrale la diferencia de especies: un motor de rueda gira y ya, un servo discute con su sensor interno hasta quedar en el ángulo exacto — por eso zumba cuando algo lo estorba. Cuéntale qué lado resultó ser el 45° en su robot y por qué eso lo saben ustedes y no ningún manual. Marca la casilla 47 en [PROGRESS.md](../../PROGRESS.md).

El cuello funciona y ya sabes hacia dónde mira cada ángulo. En la [Lección 48](48-escaneo-espacial.md) cabeza y sensor trabajan juntos: PX-32 aprenderá a **mirar alrededor y anotar lo que ve**.
