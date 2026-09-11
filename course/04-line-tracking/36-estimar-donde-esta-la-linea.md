# Lección 36 — Estimar dónde está la línea

## Del patrón al número que le sirve al robot

El patrón `00100` te dice a ti dónde está la línea. Pero piensa en el robot del hito: corrige cientos de veces por segundo y necesita una respuesta compacta, una sola cifra que resuma toda la fila: ¿cuán desviada está la línea del centro, y hacia qué lado? A esa cifra la llamaremos **posición**: cero significa "perfectamente centrada", y los signos dicen hacia qué extremo se corrió.

¿Cómo convertir cinco sí/no en un número con dirección? Con la misma lógica con la que tu maestra promedia notas, pero poniéndole pesos a cada puesto. Asignamos a cada canal un **peso** según su lugar en la fila: IR1 vale `-2`, IR2 vale `-1`, IR3 (el centro) vale `0`, IR4 vale `+1` e IR5 vale `+2`. No son cantidades físicas: son **nombres numéricos para posiciones**, con el centro en el número neutro. Después, para cada canal que está viendo la línea, sumamos su peso y dividimos por cuántos la ven: un **promedio ponderado**.

La aritmética se ve mejor con ejemplos. Supón que tu ley digital dice "negro = 1" (si es "negro = 0", los patrones se invierten pero el método es idéntico):

| Patrón | Canales que ven línea | Pesos sumados | Posición |
|---|---|---|---|
| `00100` | solo IR3 | 0 | **0.0** — centrada |
| `01100` | IR2 e IR3 | -1 + 0 | **-0.5** — apenas hacia el extremo IR1 |
| `11000` | IR1 e IR2 | -2 + (-1) | **-1.5** — bastante hacia IR1 |
| `10000` | solo IR1 | -2 | **-2.0** — en el extremo IR1 |
| `00011` | IR4 e IR5 | 1 + 2 | **+1.5** — bastante hacia IR5 |

Fíjate en dos cosas. Primera: la posición no salta de golpe entre valores enteros; con dos canales viendo línea aparecen los medios puntos, y el número se desliza suavemente a medida que la línea cruza bajo la fila. Segunda: el signo y el tamaño viajan juntos — hacia qué lado **y** cuánto. Eso es exactamente lo que un robot que corrige necesita: no solo "izquierda", sino "izquierda, un poquito".

Y si ningún canal ve la línea (`00000` según tu ley), no hay pesos que promediar. ¿Dirías que la posición es 0, "centrada"? ¡Sería una mentira peligrosa! Centrada es tener la línea bajo el centro; perderla de vista es no saber nada. La posición de "no sé" no existe, y el programa de hoy lo trata con su propio caso: **línea perdida**. En la Lección 38 ese caso se convertirá en STOP, no en un optimista "sigue derecho".

## Lo que necesitas

- PX-32 con tracker calibrado (Lección 33), conector verificado (Lección 32) y el descubrimiento del lado de IR1 en el cuaderno (Lección 34).
- Tu pista de práctica: hoja blanca y tira negra de 25 mm.
- Computador con Arduino IDE 2 y cable USB.
- El sketch [36-estimar-donde-esta-la-linea.ino](../../code/educational/36-estimar-donde-esta-la-linea/36-estimar-donde-esta-la-linea.ino).
- Tu cuaderno con la ley digital de la Lección 34 a la vista.

🟢 Programar, cargar, mover la tira y anotar es tuyo. 🟡 El adulto conecta el USB. 🔴 Sin baterías: el robot no se mueve hoy.

## El programa, por dentro

1. 🟢 Abre el `.ino` y recórrelo completo; debe ser idéntico a este bloque:

```cpp
// Curso PX-32 - Leccion 36: convertir el patron del tracker
// en una posicion con signo.
// Pesos: IR1 = -2 ... IR3 = 0 ... IR5 = +2.

const int PINES[5] = { A4, A3, A2, A1, A0 };

// Ley de tu cuaderno (Leccion 34): que imprime un canal sobre negro.
// Si tu tracker imprime 1 sobre negro, cambia LOW por HIGH.
const int LECTURA_SOBRE_NEGRO = LOW;

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(PINES[i], INPUT);
  }
  Serial.begin(9600);
}

void loop() {
  int sumaDePesos = 0;
  int cuantosVenLinea = 0;

  for (int i = 0; i < 5; i++) {
    if (digitalRead(PINES[i]) == LECTURA_SOBRE_NEGRO) {
      sumaDePesos = sumaDePesos + (i - 2);
      cuantosVenLinea = cuantosVenLinea + 1;
    }
  }

  for (int i = 0; i < 5; i++) {
    Serial.print(digitalRead(PINES[i]));
  }

  if (cuantosVenLinea == 0) {
    Serial.println("   linea perdida");
  } else {
    float posicion = float(sumaDePesos) / cuantosVenLinea;
    Serial.print("   posicion: ");
    Serial.println(posicion, 1);
  }

  delay(200);
}
```

2. 🟢 **La constante de tu ley.** `LECTURA_SOBRE_NEGRO` es la ley digital de tu cuaderno convertida en constante: si ayer anotaste que sobre negro el canal imprime `0`, déjala en `LOW`; si imprimió `1`, cámbiala a `HIGH`. Es la misma táctica de `LECTURA_AL_DETECTAR` en la Lección 30: el programa obedece a tu medición, no a una suposición del curso.

3. 🟢 **El peso es una resta escondida.** ¿Dónde están los pesos -2, -1, 0, +1, +2? En `(i - 2)`. Cuando `i` vale 0 (IR1), `i - 2` vale -2; cuando `i` vale 4 (IR5), vale +2; el centro, `i = 2`, vale 0. El índice del array y el peso de la posición son la misma recta, corrida dos lugares para que el centro caiga en el cero. Una sola resta reemplaza la tabla de pesos completa.

4. 🟢 **Dos acumuladores.** `sumaDePesos` acumula los pesos de los canales que ven línea; `cuantosVenLinea` cuenta cuántos son. Se declaran **dentro del `loop()`**, así vuelven a cero en cada foto nueva: cada muestreo parte de limpio.

5. 🟢 **El primer número con decimal.** Hasta hoy dividías enteros. Aquí aparece `float`: un tipo de dato que guarda números con punto decimal. ¿Por qué hace falta? Porque `(-1) / 2` como división de enteros da `0` (se descarta el resto), y la posición de `01100` es -0.5, no 0. La expresión `float(sumaDePesos)` convierte la suma a decimal **antes** de dividir, para que la división conserve sus medios puntos. Al imprimir, `Serial.println(posicion, 1)` muestra un solo decimal: `posicion: -0.5`.

6. 🟢 **El caso perdido vive antes del cálculo.** El `if` pregunta primero si `cuantosVenLinea == 0`. Solo si hay testigos se calcula la posición; si no, se imprime "linea perdida" y no se inventa ningún número. Fíjate en que el `else` evita hasta la división: dividir entre cero no tiene resultado, y en un microcontrolador puede producir un dato absurdo. El orden de estas preguntas no es decoración: es la frontera entre estimar y adivinar.

7. 🟢 **Predice la tabla.** Antes de cargar, completa en el cuaderno las dos filas que faltan de la tabla de arriba: `01000` y `00110`. Con tu ley digital, ¿qué patrón representa cada una?

## El experimento del número que se desliza

8. 🟡 El adulto conecta el USB. Carga el sketch y abre el monitor a 9600 baudios. Aparecerá el patrón de siempre y, a su derecha, la posición o el aviso de línea perdida.

9. 🟢 **Los cinco puestos de control.** Con la tira bajo cada canal por turno (IR1, IR2, IR3, IR4, IR5), anota el patrón y la posición exacta que imprime el monitor. Tu tabla debe acercarse a -2.0, -1.0, 0.0, +1.0, +2.0. Si tu ley digital resultó ser la otra (negro = 0), tus patrones serán los gemelos invertidos de la tabla de arriba: las posiciones, en cambio, son idénticas, porque el método no depende de la ley.

10. 🟢 **El deslizamiento continuo.** Ahora la parte hermosa: desliza la tira MUY despacio de IR1 a IR5, sin saltos. Observa la posición: pasa por -2.0, estira hacia -1.5 cuando la tira cabalga entre dos canales, cruza el 0.0 en el centro… El número camina contigo. Ese deslizarse suave es la información que en la Lección 38 se convertirá en correcciones suaves o fuertes según el tamaño del número.

11. 🟢 **El caso perdido, en vivo.** Retira la tira por completo y alza la vista: todo blanco, ningún canal en negro. El monitor debe decir "linea perdida", sin número alguno. Si apareciera un 0.0 ahí, sería un mentiroso disfrazado de programa: no dejes que ningún programa tuyo reporte certezas que no tiene.

12. 🟢 **El caso cruzado.** Corta un rectángulo de cartulina negra de unos 6 cm de ancho y ponlo bajo el robot: ahora los cinco canales ven negro a la vez. La posición imprimirá 0.0 — "centrada" — pero ¿lo está? La cartulina es una franja gigante, no una línea. El promedio dice la verdad aritmética (los pesos se cancelan) pero no la verdad del mundo. Anota este caso: en la Lección 37 lo bautizaremos como **patrón ambiguo** y también irá a STOP.

13. 🟢 **Cierra la sesión.** Monitor cerrado, USB desconectado (🟡 si lo prefiere el adulto). Tu cuaderno se queda con la tabla de puestos de control, el deslizamiento y los dos casos tramposos (perdido y cruzado). Son el alimento directo de las dos lecciones que faltan.

> **[PENDIENTE VISUAL]**
> - **Tipo:** diagrama de pesos bajo la fila de canales.
> - **Objetivo:** fijar la correspondencia canal-peso y el rango de la posición con signo.
> - **Descripción:** fila de los cinco canales IR1–IR5 vistos desde abajo con la tira en tres posiciones (bajo IR1, bajo el centro, bajo IR5); debajo de cada canal su peso (-2, -1, 0, +1, +2); a la derecha, una regla numérica vertical de -2.0 a +2.0 con las posiciones resultantes marcadas en cada caso.
> - **Elementos que deben señalarse:** pesos bajo cada canal, tira negra en cada caso, valores de posición con un decimal, el 0.0 destacado como centro.
> - **Fuente técnica:** sketch 36 del repositorio, expresión `(i - 2)` como tabla de pesos.
> - **Texto alternativo sugerido:** "Fila de cinco canales con pesos de -2 a +2 y tres posiciones de la tira con sus valores de posición".

## Desafío: la balanza asimétrica

Con la tira bajo IR1 e IR5 **a la vez** (dos tiras cortas separadas), predice la posición antes de mirar el monitor. ¿Cuánto da? ¿El robot tendría forma de distinguir "línea perfectamente centrada" de "dos líneas en los extremos"? Anota tu predicción, compruébala y explica por qué este patrón también merecerá STOP en la próxima lección: promedio cero con información no centrada es otra mentira aritmética.

## Si no funciona

| Síntoma | Qué revisar | Acción |
|---|---|---|
| La posición sale siempre 0.0 con la tira al centro… y también lejos | ¿`LECTURA_SOBRE_NEGRO` contradice tu ley de la Lección 34? | Con la ley invertida el `if` nunca suma (o suma siempre); revisa el cuaderno y corrige la constante |
| La posición sale con signo al revés | ¿Estás seguro de qué lado quedó IR1 (paso 12 de la Lección 34)? | Repite la verificación con la marca de cinta; los pesos siguen la fila, no tu memoria |
| El monitor dice "linea perdida" con la tira visible | ¿La calibración sobrevivió al cambio de luz de hoy? | Recalibra (Lección 33); el `if` solo ve lo que el umbral deja pasar |
| No aparece ningún decimal (0 en vez de -0.5) | ¿Se perdió el `float(...)` al copiar? | La división debe ser `float(sumaDePesos) / cuantosVenLinea`, no entre enteros |
| Todo imprime "posicion: 0.0" con cualquier patrón | ¿La suma acumula `(i - 2)` o quedó `i`? | Revisa la línea del `if`: sin el `- 2` todos los pesos son positivos y el centro no es 0 |
| Los valores titilan entre dos números | ¿La tira está en la frontera entre dos canales? | Es el umbral físico (Lección 33): muévela unos milímetros o acepta el titileo como información del borde |

## Lecturas y videos para explorar

- [Diagrama correcto del tracker de cinco canales](../../assets/osoyoo-manual/pagina-18-pinout-tracker-correcto.png) — Inglés; manual del fabricante; 8 min. Aprenderás diagrama correcto del tracker de cinco canales. Esencial.
- [Erratas y decisión canónica IR1–IR5](../../docs/reference/errata-osoyoo.md) — Español; referencia interna; 8 min. Aprenderás erratas y decisión canónica ir1–ir5. Opcional.

Ya sabes producir un número con dirección y tamaño. En la [Lección 37](37-de-la-medicion-a-la-orden.md) ese número atravesará una política de decisiones con nombres claros: qué órdenes existen, quién las elige y por qué los casos dudosos terminan siempre en STOP.

## Referencias técnicas de la clase

- [Referencia del lenguaje Arduino](https://docs.arduino.cc/language-reference/), tipos `float` e `int`, operadores aritméticos y `Serial.println()` con número de decimales.
- Promedio ponderado aplicado a fila de sensores: método verificado en el sketch 36 del repositorio contra los patrones de la Lección 34.
- Casos "sin línea" y "cruce" documentados en la actividad: preparan la política de STOP de las Lecciones 37 y 38.

## Cuéntale a papá

Muéstrale el número que se desliza mientras mueves la tira, y explícale qué significa el signo y qué el tamaño. Cuéntale los dos casos tramposos — línea perdida y tira ancha — y por qué un 0.0 puede ser una mentira. Pregúntale dónde se usa un promedio en su vida o su trabajo (calificaciones, sueldos, tiempos) y si algún promedio famoso le parece engañoso. Marca la sesión en [PROGRESS.md](../../PROGRESS.md).

La máquina ya estima. En la [Lección 37](37-de-la-medicion-a-la-orden.md) aprenderá a decidir — y tú aprenderás a organizar un programa como un equipo donde cada función tiene un solo trabajo.
