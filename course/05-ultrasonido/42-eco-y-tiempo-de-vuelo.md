# Lección 42 — Eco y tiempo de vuelo

## El truco de la tormenta

En una tormenta hay un juego que juegan los abuelos del campo: cuando brilla el relámpago, empiezan a contar "uno… dos… tres…" hasta que llega el trueno. Cada tres segundos, un kilómetro de distancia. Relámpago y trueno nacen en el mismo instante y del mismo lugar; el relámpago te llega casi al instante (la luz es rapidísima), pero el sonido viaja a su propio paso. Contando cuánto se demora, mides a qué distancia cayó el rayo **sin moverte de tu silla**.

Acabas de ver el corazón entero de este bloque: **una señal que viaja a velocidad conocida + un cronómetro = distancia**. PX-32 no tiene abuelo ni tormenta a mano, pero tiene el equivalente perfecto: grita un ultrasonido (su relámpago), espera el eco que rebota en el obstáculo (su trueno) y mide el tiempo entre ambos. A ese tiempo los ingenieros lo llaman **tiempo de vuelo**.

Falta solo una pieza de geometría, y es la pieza que más confunde a todo el mundo.

## El detalle del viaje de ida y vuelta

Cuando el grito del sensor rebotó en la pared y volvió, ¿cuánto camino recorrió? Piénsalo con calma: fue **hasta la pared y de regreso**. Si la pared está a 30 cm, el sonido recorrió 30 cm… y luego otros 30 cm de vuelta: **60 cm en total**.

Eso significa que el tiempo que mide el sensor es el tiempo de un viaje doble. Para conocer la distancia hasta la pared hay que dividir el recorrido total entre dos. Es la regla de la que depende todo el cálculo del robot, y vale la pena verla con el cuerpo y no solo con lápiz:

```text
distancia hasta el objeto = (velocidad × tiempo medido) / 2
```

Y falta la velocidad. En aire a unos 20 °C, el sonido viaja a aproximadamente **343 metros por segundo**. Un dato asombroso si lo piensas: mientras lees esta frase, el sonido pudo dar casi una vuelta a una cancha de fútbol. Y a la vez es tan lento comparado con la luz, que en una tormenta llega con segundos de retraso: ese retraso es exactamente lo que cuentan los abuelos.

## Lo que necesitas

- Un pasillo o un espacio libre de unos 3 a 4 metros en el piso (marcado con cinta si es posible).
- Cinta métrica o regla larga (para marcar 1, 2 y 3 metros).
- Cronómetro (el del teléfono de tu padre).
- Tu cuaderno y calculadora.
- Un cómplice: tu padre o alguien de la casa que camine parejo.

🟢 Todo el experimento es caminar y calcular: sin electricidad y sin robot encendido. PX-32 puede quedarse mirando desde la mesa.

## El experimento: camina como un sonido

1. 🟢 **Monta la pista.** En el piso, marca con cinta una línea de salida, y a 1, 2 y 3 metros marcas visibles. La última marca (o una pared a 3 metros) será "el obstáculo".

2. 🟢 **Predice en el cuaderno.** Antes de medir nada, escribe: "si mi cómplice camina parejo y tarda 6 segundos en ir hasta los 3 metros y volver, el viaje completo fue de ___ metros, así que la ida sola fue de ___ metros". (Respuestas para comprobar después: 6 y 3.)

3. 🟢 **El viaje de ida y vuelta, cronometrado.** Tu cómplice camina a paso parejo desde la salida hasta la marca de 3 m, toca la marca (¡ese toque es el rebote del eco!) y regresa. Tú cronometras **el viaje completo**. Anota el tiempo total.

4. 🟢 **Haz las cuentas del robot.** Con la cinta métrica mide el paso real de tu cómplice: cuántos centímetros avanza en una zancada, o mejor, cuánto tarda en recorrer un metro conocido. Calcula su **velocidad** (por ejemplo, 1 metro cada 2 segundos = 0,5 m/s). Ahora aplica la fórmula del robot:

   ```text
   distancia hasta la marca = (velocidad × tiempo total) / 2
   ```

   Compara con los 3 metros reales de la cinta. ¿Te acercaste? Repite el viaje dos veces más y promedia: una sola medición puede salir suertuda o desastrosa; tres te dan una idea honesta (esto volverá en la Lección 46, con el robot de verdad).

5. 🟢 **La prueba del trueno.** Ahora al revés: conoces la velocidad del sonido (343 m/s) y la distancia (3 m). Calcula cuánto tardaría el eco de una palmada en una pared a 3 m: recorrido total 6 m → tiempo = 6 / 343 ≈ **0,0175 segundos**, unos 17,5 ms o 17 500 µs. Ese número es tan corto que ningún humano lo cronometra: por eso necesitas un murciélago… o una Mega 2560, que mide microsegundos sin despeinarse.

6. 🟢 **El examen del ÷2.** Responde en el cuaderno sin mirar atrás: el sensor mide un eco de 5 860 µs. Con 0,0343 cm/µs, ¿qué recorrido total hizo el sonido y a qué distancia está el objeto? (Cálculo: 5860 × 0,0343 ≈ 201 cm de recorrido; ÷ 2 = 100,5 cm hasta el objeto.) Si obtuviste 100,5 cm, la división entre dos ya es tuya para siempre.

> **[PENDIENTE VISUAL]**
> - **Tipo:** diagrama de trayectoria.
> - **Objetivo:** fijar la diferencia entre recorrido total y distancia al objeto.
> - **Descripción:** vista cenital del robot frente a una pared; flecha de ida desde el sensor a la pared rotulada "30 cm", flecha de retorno rotulada "30 cm", llave que abarca ambas rotulada "recorrido total medido: 60 cm", y corchete simple desde el robot hasta la pared rotulado "distancia real: 60 / 2 = 30 cm".
> - **Elementos que deben señalarse:** sensor ultrasónico, pared, ambas flechas con sentido, rótulos de recorrido total y de distancia entre dos.
> - **Fuente técnica:** hoja de datos HC-SR04 (SparkFun), https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf, descripción del tiempo de eco de ida y vuelta.
> - **Texto alternativo sugerido:** "Diagrama del viaje de ida y vuelta del ultrasonido mostrando que el recorrido medido es el doble de la distancia al objeto".

## Desafío: el juego de la tormenta, con reglas

Con tu padre, inventa el juego completo: él dice "¡rayo!" en voz baja y aplaude fuerte 3, 6 o 9 segundos después (el trueno). Con la regla de los abuelos (3 segundos ≈ 1 kilómetro), calcula a qué "distancia" cayó cada rayo. Luego invierte el juego: él te da la distancia (2 km) y tú produces el trueno con el retraso correcto. El que menos se equivica en cinco rondas gana. Al final, calcula juntos cuántos microsegundos tardaría el eco de un rayo que cayera a 3 km… y descubre por qué el trueno de un rayo cercano retumba en vez de aplaudir una sola vez (pista: el rayo es largo, y cada punto de él está a una distancia distinta de ti).

## Si no funciona

| Síntoma | Qué revisar | Acción |
|---|---|---|
| Mi cálculo da el doble de lo esperado | ¿Olvidaste dividir entre 2? | Es el error clásico: el cronómetro midió ida **y** vuelta; el objeto está a la mitad |
| El cómplice camina a pasos desparejos | ¿Cambia de ritmo al girar? | Que ensaye el giro tocando la marca sin detenerse, y promedia varias corridas |
| No me sale 17,5 ms para la pared a 3 m | ¿Dividiste 6/343 o 3/343? | El recorrido es 6 m (ida y vuelta); si usaste 3 m obtendrás la mitad: 8,75 ms |
| Me pierdo entre ms y µs | ¿Recuerdas la Lección 40? | 1 ms = 1000 µs; 17,5 ms = 17 500 µs. La Mega hablará en µs |
| La velocidad del sonido, ¿siempre es 343? | ¿Hace frío o calor hoy? | 343 m/s corresponde a unos 20 °C; con aire más frío el sonido va un poco más lento. Anótalo como fuente de error, no lo escondas |

## Lecturas y videos para explorar

- [Velocidad, frecuencia y longitud de onda del sonido](https://openstax.org/books/physics/pages/14-1-speed-of-sound-frequency-and-wavelength) — Inglés; libro abierto; 12 min. Aprenderás velocidad, frecuencia y longitud de onda del sonido. Esencial.
- [Biblioteca Servo](https://docs.arduino.cc/libraries/servo/) — Inglés; referencia oficial Arduino; 10 min. Aprenderás biblioteca servo. Opcional.

En OpenStax encontrarás la tabla de velocidades del sonido en aire, agua y acero: el mismo grito viaja a velocidades distintas según el medio (¿te acuerdas de la Lección 39?).

## Referencias técnicas de la clase

- [OpenStax Physics, sección 14.1](https://openstax.org/books/physics/pages/14-1-speed-of-sound-frequency-and-wavelength): velocidad del sonido en el aire (343 m/s a 20 °C) y su variación con la temperatura.
- [Hoja de datos del módulo HC-SR04 (SparkFun)](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf): el eco como tiempo de ida y vuelta.

## Cuéntale a papá

Jueguen el juego de la tormenta del desafío y luego explícale el error del doble: por qué un robot que olvida dividir entre 2 creería que todo está al doble de su distancia real, y qué tan peligroso sería eso al frenar frente a un obstáculo. Muéstrale tu tabla de mediciones del pasillo. Marca la casilla 42 en [PROGRESS.md](../../PROGRESS.md).

Ya tienes la física completa: onda, frecuencia, eco, velocidad y la división entre dos. En la [Lección 43](43-trig-enviar-un-pulso-breve.md) se enciende el computador: PX-32 aprende por fin a **dar la orden de gritar**.
