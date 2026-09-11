# Lección 34 — Leer cinco sensores sin perderse

## Cinco testigos, una fila de números

Ayer terminaste la clase con una ley escrita en tu cuaderno: sobre negro, el LED de señal de un canal se enciende; sobre blanco, se apaga. Pero los LED son para humanos. El programa de PX-32 no puede "mirar" la placa: necesita que cada canal le entregue su veredicto como número por un pin. Eso ya ocurrió una vez: en la Lección 28 leíste un sensor de mano con `digitalRead()` y obtuviste `1` o `0`. Hoy lo harás **cinco veces en la misma vuelta del `loop()`**.

Cuando los cinco veredictos se escriben juntos, nacen cosas nuevas. Un canal decía `0` o `1`; cinco canales en fila forman un **patrón**: algo como `00100` o `10000`. Ese patrón es un mapa del piso bajo el frente del robot: dónde hay negro y dónde no, de un solo vistazo. La palabra **muestreo** nombra el acto de tomar esa foto: preguntarle a los cinco canales en un instante y anotar las cinco respuestas juntas.

Y hay una promesa pendiente de la Lección 31 que hoy se cumple: con la tira bajo un canal a la vez, verás **qué dígito del patrón cambia**. Dígito y canal quedan emparejados con evidencia, y por fin podrás contestar la pregunta incómoda: ¿IR1 queda a tu izquierda o a tu derecha cuando miras a PX-32 desde atrás?

## Lo que necesitas

- PX-32 ensamblado, con el tracker calibrado con la luz de hoy (Lección 33) y su conector verificado (Lección 32).
- Tu pista de práctica: la hoja blanca y la tira negra de 25 mm de la Lección 33.
- Computador con Arduino IDE 2 y el cable USB.
- El sketch [34-leer-cinco-sensores-sin-perderse.ino](../../code/educational/34-leer-cinco-sensores-sin-perderse/34-leer-cinco-sensores-sin-perderse.ino).
- Tu cuaderno con el mapa del frente y la ley de LED.

🟢 Programar, cargar, mover la tira y leer el monitor es cosa tuya. 🟡 El adulto conecta el USB. 🔴 Las baterías siguen fuera: hoy no se mueve nada.

## El programa, por dentro

1. 🟢 Abre el `.ino` y recórrelo completo; debe ser idéntico a este bloque:

```cpp
// Curso PX-32 - Leccion 34: leer los cinco canales del tracker
// e imprimirlos como un patron de cinco digitos.
// El digito de la izquierda es IR1; el de la derecha, IR5.

const int CANAL_IR1 = A4;
const int CANAL_IR2 = A3;
const int CANAL_IR3 = A2;
const int CANAL_IR4 = A1;
const int CANAL_IR5 = A0;

void setup() {
  pinMode(CANAL_IR1, INPUT);
  pinMode(CANAL_IR2, INPUT);
  pinMode(CANAL_IR3, INPUT);
  pinMode(CANAL_IR4, INPUT);
  pinMode(CANAL_IR5, INPUT);
  Serial.begin(9600);
}

void loop() {
  int lecturaIR1 = digitalRead(CANAL_IR1);
  int lecturaIR2 = digitalRead(CANAL_IR2);
  int lecturaIR3 = digitalRead(CANAL_IR3);
  int lecturaIR4 = digitalRead(CANAL_IR4);
  int lecturaIR5 = digitalRead(CANAL_IR5);

  Serial.print(lecturaIR1);
  Serial.print(lecturaIR2);
  Serial.print(lecturaIR3);
  Serial.print(lecturaIR4);
  Serial.println(lecturaIR5);

  delay(200);
}
```

2. 🟢 **Lo conocido.** No hay ni una instrucción nueva: `const`, `pinMode(..., INPUT)`, `digitalRead()`, `Serial.print()` y `delay()` ya son tuyos desde las Lecciones 07, 08 y 28. Lo nuevo es la **cantidad**: lo mismo cinco veces, en orden de fila.

3. 🟢 **Las constantes siguen el mapa.** `CANAL_IR1 = A4` … `CANAL_IR5 = A0`: exactamente la escalera que verificaste en la Lección 32 contra el diagrama de la página 18. Si algún día dudas de un pin, no lo cambies por gusto: vuelve al mapa canónico.

4. 🟢 **Las cinco lecturas ocurren "a la vez".** En realidad el procesador las hace una tras otra en millonésimas de segundo; para lo que importa aquí, las cinco describen el mismo instante. Después de leerlas, el programa no decide nada: solo imprime. Medir y decidir son trabajos distintos, y hoy solo medimos.

5. 🟢 **El formato del patrón.** Cuatro `print` y un `println` final: los cinco dígitos quedan pegados en una línea (`00100`) y el `println` hace el salto de línea para la próxima foto. Elegimos imprimir IR1 primero para que el patrón se lea como tu dibujo del frente: de IR1 a IR5. Esa decisión de **formato** —cómo se muestra un dato— la tomamos nosotros y la mantendremos en todo el bloque.

6. 🟢 **`delay(200)`**: cinco fotos por segundo. Suficiente para tu ojo en la mesa; en el hito bajaremos esta pausa porque el robot necesitará decidir más rápido.

7. 🟢 **Predice antes de cargar.** En el cuaderno, con la tira bajo el canal central: ¿qué patrón esperas? ¿Y con la tira bajo IR1? No sigas hasta tener tu apuesta escrita.

## El experimento del dígito que cambia

8. 🟡 El adulto conecta el USB. Carga el sketch, elige la placa Mega 2560 y el puerto correcto, y abre el monitor serie a 9600 baudios (Lección 08). Debe comenzar a llover una línea tras otra con el patrón del momento.

9. 🟢 **Condiciones de partida.** Pon la hoja blanca bajo el robot y observa el patrón "todo blanco": anótalo. Debe ser cinco dígitos iguales (`00000` o `11111`, según tu módulo). Esa es tu línea base.

10. 🟢 **La ley digital.** Desliza la tira bajo el canal central hasta que el LED de IR3 encienda (Lección 33). Mira el monitor: ¿qué dígito cambió respecto de la línea base? Si sobre negro el patrón muestra `1` en el canal, tu tracker entrega `HIGH` sobre negro; si muestra `0`, entrega `LOW`. Escríbelo con fecha en el cuaderno: "**En mi tracker, sobre negro el canal imprime ___**". Esta ley digital es la gemela de la ley de LED de la Lección 33 y será una constante en los programas de las Lecciones 36, 37 y 38.

11. 🟢 **Empareja dígitos y canales.** Ahora la parte detective: colócate **detrás del robot**, como su piloto, mirando en la misma dirección en la que avanzaría PX-32 (su frente queda lejos de ti). Sin perder esa posición, desliza la tira bajo el canal de tu marca de cinta (IR1) y observa el monitor: el dígito que cambia es el primero de la izquierda. Repite con IR2, IR4 e IR5: cada tira bajo un canal debe cambiar un único dígito, en orden. Anota la correspondencia completa en tu mapa del cuaderno.

12. 🟢 **La pregunta incómoda, respondida.** Sigues detrás del robot: la tira está bajo IR1, a tu izquierda o a tu derecha. Esa es la respuesta que dos lecciones esperaban. Escribe en el cuaderno, en grande: "**IR1 queda a mi ____ cuando miro a PX-32 desde atrás**". A partir de este momento, cuando el curso diga "extremo IR1" podrás traducirlo a izquierda o derecha con tu propia evidencia.

13. 🟢 **Fotos que el ojo no alcanza.** Desliza la tira lentamente entre IR3 e IR4 y observa el momento en que dos dígitos valen "negro" a la vez (`01100` o su gemelo, según tu ley). Esa zona de transición —la línea entre dos canales— es la que el robot del hito cruzará cientos de veces por segundo. Verla en números ahora es entender su corrección después.

14. 🟢 **Cierra la sesión.** Cierra el monitor, desconecta el USB (🟡 si lo prefiere el adulto) y guarda la pista. El cuaderno debe quedar con tres tesoros: la línea base, la ley digital y el lado de IR1.

> **[PENDIENTE VISUAL]**
> - **Tipo:** captura anotada del monitor serie.
> - **Objetivo:** que el niño asocie cada posición de la tira con su patrón de cinco dígitos antes de intentarlo en el robot real.
> - **Descripción:** captura del monitor con cuatro patrones característicos apilados (línea base en blanco, tira bajo IR3, tira bajo IR1, tira entre IR3 e IR4); a la derecha de cada patrón, un mini-dibujo del frente del robot con la tira en la posición correspondiente y el canal activo resaltado.
> - **Elementos que deben señalarse:** dígitos individuales del patrón, canal correspondiente a cada dígito, posición de la tira en cada mini-dibujo.
> - **Fuente técnica:** sketch 34 del repositorio, formato de impresión IR1→IR5.
> - **Texto alternativo sugerido:** "Monitor serie mostrando cuatro patrones de cinco dígitos junto al dibujo de la posición de la tira que produce cada uno".

## Desafío: el patrón imposible

Sin poner la tira bajo el robot, escribe en el cuaderno los patrones que **no** podrían aparecer jamás con una sola tira de 25 mm. ¿`10101`? ¿`11111`? ¿`01010`? Razona por ancho: la tira cabe en uno o dos canales vecinos, no en tres alternados. Guarda tu lista: en la Lección 37 servirá para reconocer lecturas imposibles o ambiguas y enviarlas a STOP.

## Si no funciona

| Síntoma | Qué revisar | Acción |
|---|---|---|
| El monitor no muestra nada | ¿Velocidad del monitor en 9600? ¿Placa y puerto correctos? | Repite la verificación de la Lección 08; desconectar y reconectar el USB renombra a veces el puerto |
| El patrón nunca cambia al mover la tira | ¿Está cargado el sketch correcto y el conector de 7 pines bien sentado? | Revisa el mapa de la Lección 32; si el conector se movió, 🔴 el adulto lo revisa sin energía |
| Cambian varios dígitos a la vez con la tira en un solo canal | ¿La tira es más ancha que 25 mm o está torcida? | Mide de nuevo; una tira ancha tapa dos canales legítimamente |
| El patrón salta entre dos valores sin mover nada | ¿Estás en el borde del umbral o hay sombra parpadeante? | Aleja la tira del borde, iguala la luz de la sala; si persiste, recalibra (Lección 33) |
| Los dígitos parecen al revés (tira bajo IR5 cambia el primero) | ¿Estás mirando el robot desde adelante en vez de desde atrás? | Vuelve a colocarte detrás del robot; el formato IR1-primero fue tu decisión en el paso 5 |
| Todo marca "negro" siempre | ¿La tira o la sombra de tu cuerpo cubre toda la fila? | Aléjate; el secuestro de luz de la Lección 33 también aplica aquí |

## Lecturas y videos para explorar

- [Diagrama correcto del tracker de cinco canales](../../assets/osoyoo-manual/pagina-18-pinout-tracker-correcto.png) — Inglés; manual del fabricante; 8 min. Aprenderás diagrama correcto del tracker de cinco canales. Esencial.
- [Erratas y decisión canónica IR1–IR5](../../docs/reference/errata-osoyoo.md) — Español; referencia interna; 8 min. Aprenderás erratas y decisión canónica ir1–ir5. Opcional.

El patrón ya vive en tu monitor y en tu cuaderno. En la [Lección 35](35-arrays-cinco-datos-bajo-un-nombre.md) mirarás este programa con otros ojos y preguntarás: ¿veintiuna líneas para cinco lecturas… no habrá una forma más elegante?

## Referencias técnicas de la clase

- [Referencia del lenguaje Arduino](https://docs.arduino.cc/language-reference/), `digitalRead()`, `pinMode()` con `INPUT`, `Serial.print()`/`println()`.
- Uso de A0–A4 como entradas digitales en la Mega 2560: [pinout oficial](https://docs.arduino.cc/resources/pinouts/A000067-full-pinout.pdf) y mapa canónico del repositorio.
- [Manual oficial de OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), páginas 34–38: el proyecto del fabricante lee los mismos cinco canales para seguir la línea.

## Cuéntale a papá

Muéstrale el juego de la tira y el dígito que cambia, y explícale tu descubrimiento del paso 12: de qué lado quedó IR1 y cómo lo sabes (no lo que dice el manual: lo que tú mediste). Cuéntale qué patrón apareció con la tira entre dos canales. Pregúntale qué cree que debería hacer el robot si ve ese patrón. Marca la sesión en [PROGRESS.md](../../PROGRESS.md).

El programa de hoy funciona, pero te invito a contar sus líneas: en la [Lección 35](35-arrays-cinco-datos-bajo-un-nombre.md) aprenderás la estructura de datos favorita de todos los lenguajes y el programa encogerá sin perder nada.
