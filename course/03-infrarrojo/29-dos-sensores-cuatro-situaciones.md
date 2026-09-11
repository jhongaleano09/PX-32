# Lección 29 — Dos sensores, cuatro situaciones

## Dos preguntas sí/no son cuatro mundos

Un sensor entrega un solo dato: detecta o no detecta. La respuesta a una pregunta sí/no se llama un **bit** de información. Con un bit hay dos mundos posibles. Pero PX-32 tiene dos sensores apuntando al frente, uno a cada lado: izquierda y derecha. Dos preguntas sí/no se combinan en 2 × 2 = **cuatro situaciones**:

| ¿Izquierdo detecta? | ¿Derecho detecta? | Situación frente al robot |
|---|---|---|
| no | no | nada detectado a la vista |
| sí | no | algo está hacia la izquierda |
| no | sí | algo está hacia la derecha |
| sí | sí | algo está al frente (grande o cercano) |

Esta tabla es una **tabla de verdad**: lista todas las combinaciones posibles de las entradas, sin repetir ni olvidar ninguna. Es la herramienta que usarás después con cinco sensores del tracker, donde las combinaciones serán 2 × 2 × 2 × 2 × 2 = 32.

Para que el programa distinga las cuatro situaciones necesita combinar condiciones, y ahí entra un operador nuevo: `&&`, que se lee "y". `izquierdaDetecta && derechaDetecta` es `true` solamente cuando las dos condiciones son `true` a la vez; si una falla, el conjunto es `false`. Es el hermano del bloque "y" de Scratch, ese que unías debajo de un "si… entonces" para exigir dos condiciones juntas. Su primo es `||` ("o"), que es `true` cuando al menos una condición se cumple.

Antes de dejar que el código piense por ti, llena la tabla a mano: es tu mapa del territorio. Y una advertencia de orientación, que en este experimento es fácil perderse: "izquierda" y "derecha" se cuentan **desde el punto de vista del robot**, no del tuyo. Si miras a PX-32 de frente, tu izquierda es la derecha de él. Cuando quieras probar "la izquierda del robot", párate detrás de él o usa el cono que dibujaste en la Lección 28.

## Lo que necesitas

- PX-32 con ambos sensores calibrados a la ventana de 10/15 cm (Lección 27).
- Tu cuaderno con la tabla de verdad vacía copiada.
- Tus dos manos, o una mano y el cartón blanco para ocupar los dos sensores a la vez.
- Computador con Arduino IDE 2, cable USB y el sketch [29-dos-sensores-cuatro-situaciones.ino](../../code/educational/29-dos-sensores-cuatro-situaciones/29-dos-sensores-cuatro-situaciones.ino).
- Un adulto para el USB.

Estado inicial: robot apagado y sin baterías, quieto sobre la mesa. Ningún movimiento en esta clase: hoy el robot aprende a nombrar lo que ve, no a reaccionar.

🟡 El adulto conecta el USB y lo retira al final. Si el sketch imprimiera algo distinto a lo que ocurre frente al robot, primero se revisa el montaje, no el experimento.

## Lee el programa que nombra situaciones

1. 🟢 Abre el `.ino` y recórrelo completo. Debe ser idéntico a este bloque:

```cpp
// Curso PX-32 - Leccion 29: dos sensores IR, cuatro situaciones.

const byte SENSOR_IR_IZQUIERDO = 3;
const byte SENSOR_IR_DERECHO = 2;

// Segun la evidencia de tu cuaderno en la Leccion 28: si tu modulo
// entrega HIGH al detectar, cambia LOW por HIGH en esta linea.
const int LECTURA_AL_DETECTAR = LOW;

void setup() {
  pinMode(SENSOR_IR_IZQUIERDO, INPUT);
  pinMode(SENSOR_IR_DERECHO, INPUT);
  Serial.begin(9600);
}

void loop() {
  bool izquierdaDetecta =
      digitalRead(SENSOR_IR_IZQUIERDO) == LECTURA_AL_DETECTAR;
  bool derechaDetecta =
      digitalRead(SENSOR_IR_DERECHO) == LECTURA_AL_DETECTAR;

  if (izquierdaDetecta && derechaDetecta) {
    Serial.println("AMBOS DETECTAN");
  } else if (izquierdaDetecta) {
    Serial.println("SOLO IZQUIERDA");
  } else if (derechaDetecta) {
    Serial.println("SOLO DERECHA");
  } else {
    Serial.println("NINGUNO DETECTA");
  }

  delay(300);
}
```

2. 🟢 **Dos constantes de pin.** `3` y `2`: los dos cables OUT que verificaste en la Lección 24. Escucharlos juntos en el mismo `loop()` es gratuito: cada `digitalRead` pregunta a un pin distinto y guarda su respuesta en su propia variable `bool`.

3. 🟢 **`LECTURA_AL_DETECTAR` es tu ley del paso 11 de la Lección 28**, convertida en constante. La comparación `digitalRead(...) == LECTURA_AL_DETECTAR` traduce el número crudo a algo con significado: "¿este sensor está detectando?". Gracias a eso, el resto del programa piensa en detecciones, no en 0 y 1. Si tu evidencia dijo que detectar era `HIGH`, cambias una línea y todo el programa sigue funcionando: eso es lo que gana un programa que habla el idioma de su dueño.

4. 🟢 **El `&&` del primer `if`** exige las dos detecciones juntas para imprimir "AMBOS DETECTAN". Repásalo como en Scratch: "si ¿izquierda detecta? y ¿derecha detecta?".

5. 🟢 **La escalera `else if`** reparte las otras tres situaciones. La estructura es la de la Lección 09: en cada vuelta del `loop()` se ejecuta una sola rama. Comprueba con la tabla de verdad que las cuatro ramas corresponden a las cuatro filas: ni una repetida, ni una olvidada. La última (`else`) es la que atrapa el "no, no".

6. 🟢 **`delay(300)`** imprime tres líneas por segundo: tiempo de sobra para mover tu mano entre línea y línea sin perder el hilo.

7. 🟢 **Predice las cuatro.** Antes de conectar, escribe el orden en que harás las cuatro situaciones y qué palabra esperas en cada una.

## Llena la tabla de verdad con tu cuerpo

8. 🟡 **Energiza.** El adulto conecta el USB; sube el sketch y abre el monitor a 9600 baudios.

9. 🟢 **Situación "ninguno".** Aléjate del robot. La palabra estable debe ser "NINGUNO DETECTA". Cópiala en la primera fila de tu tabla con un check.

10. 🟢 **Situación "solo izquierda".** Coloca una mano frente al sensor izquierdo, cuidando no invadir el campo del derecho (usa tu cono dibujado de la Lección 28 como guía). Debería aparecer "SOLO IZQUIERDA". Si aparece "SOLO DERECHA", no corrijas nada todavía: lee la advertencia del punto de vista del robot, párate detrás de PX-32 y comprueba con los ojos del robot. Confirma físicamente qué sensor estás tapando (su LED de señal encendido te lo dice) y qué cable lo une al shield.

11. 🟢 **Situación "solo derecha".** Mano al sensor derecho: "SOLO DERECHA".

12. 🟢 **Situación "ambos".** Usa las dos manos, una frente a cada sensor, o un cartón ancho que cubra los dos a la vez y a la misma distancia: "AMBOS DETECTAN". Con una sola mano cerrada a 5 cm del centro también puedes lograrlo si los conos se cruzan; experimenta dónde se cruzan.

13. 🟢 **Cierra la tabla.** Vuelve a pasar por las cuatro situaciones en desorden, anunciando en voz alta la palabra ANTES de mirar el monitor. Acierta las cuatro seguidas y tu tabla de verdad queda firmada.

14. 🟢 **El juego del adulto.** Pide a tu papá que esconda las manos y produzca una situación a su elección mientras tú miras el monitor; tú anuncias qué está pasando frente al robot y él confirma. Intercambien papeles. Si alguien pierde, revisen juntos cuál fila de la tabla se confundió.

15. 🟡 **Cierre.** Cierra el monitor; el adulto retira el USB.

> **[PENDIENTE VISUAL]**
> - **Tipo:** diagrama cenital con tabla de verdad integrada.
> - **Objetivo:** asociar cada posición de la mano con una fila de la tabla y una rama del programa.
> - **Descripción:** vista desde arriba de la mitad frontal de PX-32 con los dos sensores y sus conos de detección dibujados; cuatro escenas pequeñas alrededor: manos ausentes, mano izquierda, mano derecha, cartón ancho cubriendo ambos; cada escena conectada con una flecha a su fila de la tabla de verdad y a la palabra impresa por el programa.
> - **Elementos que deben señalarse:** sensor izquierdo y su cono, sensor derecho y su cono, punto de vista del robot, las cuatro palabras del monitor.
> - **Fuente técnica:** manual OSOYOO, https://osoyoo.com/manual/2021006600-2026.pdf, página 43, comportamiento con objeto a izquierda, derecha y centro.
> - **Texto alternativo sugerido:** "Vista superior del robot con los conos de sus dos sensores y cuatro posiciones de la mano conectadas a las filas de una tabla de verdad".

## Desafío: el operador que falta

Agrega una sola línea nueva antes de los cuatro casos: `bool hayAlgo = izquierdaDetecta || derechaDetecta;` e imprime primero "HAY ALGO" o "DESPEJADO" según ella. Sube y prueba: ¿en cuántas de las cuatro situaciones dice "HAY ALGO"? Esa es la tabla de verdad del "o". Cuando termines, deja el sketch como estaba.

## Si no funciona

| Síntoma | Qué revisar | Acción |
|---|---|---|
| Las palabras salen al revés (izquierda por derecha) | ¿Estás mirando al robot de frente? | Cuenta desde el punto de vista del robot; confirma con el LED de señal del sensor tapado y su cable en el shield |
| Una palabra nunca aparece | ¿La mano llega a la distancia de calibración de ese sensor? | Repite la ventana 10/15 de la Lección 27 para ese sensor |
| "AMBOS" aparece con un objeto pequeño y lejano al centro | ¿Los conos se cruzan antes de lo que creías? | Es normal a corta distancia; anota dónde se cruzan los tuyos |
| El monitor no cambia nunca | ¿Compilaste con tu constante de la Lección 28 al revés? | Si "NINGUNO DETECTA" se vuelve "AMBOS DETECTAN" al tapar, invierte `LECTURA_AL_DETECTAR` |
| Aparecen palabras intermedias o mezcladas | ¿Algún `else if` quedó fuera de la escalera? | Repasa las llaves: una sola rama por vuelta (Lección 09) |

## Lecturas y videos para explorar

- [El espectro electromagnético y el infrarrojo](https://science.nasa.gov/ems/07_infraredwaves/) — Inglés; lectura NASA; 8 min. Aprenderás el espectro electromagnético y el infrarrojo. Esencial.
- [Sensores de PX-32](../../docs/reference/sensores.md) — Español; referencia interna; 6 min. Aprenderás sensores de px-32. Opcional.

Después de jugar con las cuatro situaciones, la tabla de sensores de la referencia te da una idea del siguiente reto: el tracker multiplicará este juego por cinco canales.

## Referencias técnicas de la clase

- [Referencia del lenguaje Arduino](https://docs.arduino.cc/language-reference/), operadores booleanos `&&` y `||`, comparación `==` y tipo `bool`.
- [Manual oficial de OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), páginas 42 a 43, comportamiento combinado de los dos sensores IR.
- [Mapa canónico de conexiones](../../docs/reference/mapa-conexiones-robot.md), sensores IR de obstáculos en D3 y D2.

## Cuéntale a papá

Jueguen al adivinario de las cuatro palabras y luego explícale por qué dos sensores dan exactamente cuatro situaciones y no tres ni cinco. Muéstrale el `&&` en el código y compáralo con el bloque "y" de Scratch que usabas en tus juegos. Para cerrar, cuéntale cuántas combinaciones tendría el tracker de cinco sensores del próximo bloque y por qué conviene una tabla de verdad antes de programar.

El robot ya nombra las cuatro situaciones. En la [Lección 30](30-seguir-una-mano-con-prudencia.md) cada situación se convierte en una orden de movimiento… con el freno de mano puesto.
