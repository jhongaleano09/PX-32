# Lección 35 — Arrays: cinco datos bajo un nombre

## Un programa con cinco gemelos

Vuelve a abrir el sketch de la Lección 34 y míralo con ojos de diseñador. ¿Ves el patrón? Cinco constantes que solo difieren en el número; cinco `pinMode` idénticos salvo el nombre; cinco `digitalRead` gemelos; cinco `Serial.print` que solo cambian de variable. Contaste veintiuna líneas y ninguna idea nueva después de la segunda. Funciona, sí. Pero imaginemos el tracker de 32 canales de una impresora industrial: ¿escribirías treinta y dos `pinMode` a mano? ¿Y si luego cambiaran el pin 27?

Los programadores detestan la repetición tanto como tú copiar veinte veces la misma frase en el cuaderno. Y C++ tiene la herramienta exacta para este problema: el **array**, una fila de casillas que viven bajo **un solo nombre** y se distinguen por un **índice** numerado.

Si hiciste listas en Scratch —esa caja donde guardabas puntajes o nombres y los leías por posición— ya conocías la idea. En C++ la lista se escribe distinto, pero la esencia es la misma: **un nombre, muchas casillas, y el índice para elegir una**. La diferencia importante es que en C++ la fila tiene un largo fijo que tú declaras, y las casillas se cuentan desde **cero**.

## Cómo se escribe una fila de pines

Mira la línea que reemplaza a las cinco constantes de ayer:

```cpp
const int PINES[5] = { A4, A3, A2, A1, A0 };
```

Léela por partes, de derecha a izquierda:

- `{ A4, A3, A2, A1, A0 }` es el contenido: los cinco pines del mapa canónico, en orden de fila IR1 a IR5.
- `PINES` es el nombre de la fila completa.
- `[5]` declara cuántas casillas tiene: su **longitud**. Fija, declarada de una vez.
- `const int` dice que cada casilla guarda un `int` y que no vamos a cambiarlos.

Ahora la parte que más conviene entender bien: las casillas se numeran **desde cero**. `PINES[0]` es `A4` (el pin de IR1), `PINES[1]` es `A3`, `PINES[2]` es `A2`, `PINES[3]` es `A1` y `PINES[4]` es `A0` (IR5). La primera casilla no es `PINES[1]` sino `PINES[0]`, y por eso la última de una fila de cinco es la número 4, no la 5. Contar desde cero parece exótico la primera vez, pero tiene una razón útil: el índice mide **cuántos pasos das desde el inicio**. Cero pasos = primera casilla.

| Expresión | Vale | Es el pin de |
|---|---|---|
| `PINES[0]` | `A4` | IR1 |
| `PINES[1]` | `A3` | IR2 |
| `PINES[2]` | `A2` | IR3 |
| `PINES[3]` | `A1` | IR4 |
| `PINES[4]` | `A0` | IR5 |

Y la casilla que **no existe**: `PINES[5]`. En una fila de cinco, los índices válidos van de 0 a 4. Pedir `PINES[5]` es preguntar por una casilla fuera de la fila: el compilador no te detiene, y el programa leerá lo que haya en esa dirección de memoria, que puede ser cualquier cosa. Es la primera vez en el curso que un error **no se ve como error**: el programa compila y corre, pero lee un dato absurdo. Los límites del array los cuidas tú; por eso la condición del bucle de hoy se escribe con tanto cuidado.

## El bucle que recorre la fila

La segunda herramienta es un viejo conocido: el `for` de la Lección 10, que repetía un bloque contando. Ahora el contador `i` no solo cuenta: **es el índice**. En cada vuelta del bucle, `i` vale 0, luego 1, luego 2, 3, 4, y `PINES[i]` va siendo cada casilla por turno:

```cpp
for (int i = 0; i < 5; i++) {
  pinMode(PINES[i], INPUT);
}
```

Una línea que hace el trabajo de cinco. Y lo mejor: si el tracker tuviera 32 canales, la misma línea serviría cambiando el 5 por 32. Los datos cambiaron; el programa no.

## Lo que necesitas

- Todo lo de la Lección 34: PX-32 con tracker calibrado, pista de práctica (hoja blanca y tira de 25 mm), computador con Arduino IDE 2, cable USB, cuaderno con tu ley digital y tu mapa.
- El sketch [35-arrays-cinco-datos-bajo-un-nombre.ino](../../code/educational/35-arrays-cinco-datos-bajo-un-nombre/35-arrays-cinco-datos-bajo-un-nombre.ino).

🟢 Todo el trabajo de hoy es tuyo: programar, cargar y probar. 🟡 El adulto conecta el USB. 🔴 Nada de baterías: sigue siendo un experimento de mesa.

## El programa, por dentro

1. 🟢 Abre el `.ino` nuevo y ponlo junto al de la Lección 34 en dos ventanas. Debe ser idéntico a este bloque:

```cpp
// Curso PX-32 - Leccion 35: el mismo patron de la Leccion 34,
// ahora con un array y un bucle for.
// PINES[0] es IR1 (A4) ... PINES[4] es IR5 (A0).

const int PINES[5] = { A4, A3, A2, A1, A0 };

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(PINES[i], INPUT);
  }
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 5; i++) {
    Serial.print(digitalRead(PINES[i]));
  }
  Serial.println();

  delay(200);
}
```

2. 🟢 **El contrato de igualdad.** Este programa debe comportarse exactamente igual que el de la Lección 34: mismo patrón, mismo formato IR1-primero, mismo ritmo. Un cambio de estructura —de cinco variables a un array— no debería cambiar nada visible. Esa es la definición de un buen **refactor**: mismo comportamiento, mejor forma. Si algo cambia en el monitor, el refactor falló y hay un error escondido.

3. 🟢 **Sigue una vuelta completa con el dedo.** En el `loop()`, primera vuelta del `for`: `i` vale 0, entonces `digitalRead(PINES[0])` lee A4 (IR1) y lo imprime. Segunda vuelta: `i` vale 1, lee A3. Y así hasta `i = 4`, que lee A0. Cuando `i` llega a 5, la condición `i < 5` es falsa, el bucle termina, el `println` cierra la línea y el `delay` espera. Todo el trabajo de ayer, en dos líneas.

4. 🟢 **¿Por qué `i < 5` y no `i <= 5`?** Escribe la respuesta antes de seguir. Con `i <= 5`, la última vuelta usaría `PINES[5]`: la casilla que no existe, el dato absurdo. El `<` sin `=` es el guardián del límite. Cuando tus bucles recorran arrays, esta será tu primera sospecha en todo error raro. Si la curiosidad te gana, puedes hacer el experimento **una vez y con cuidado**: cambia `i < 5` por `i <= 5` en una copia, carga y mira llegar el sexto dígito absurdo. Luego devuelve el guardián a su puesto antes de seguir la lección.

5. 🟢 **Predice.** Antes de cargar: ¿qué imprimirá el monitor con la tira bajo IR4? ¿Y con el robot totalmente sobre blanco? Anota tus dos apuestas.

## El experimento del refactor honesto

6. 🟡 El adulto conecta el USB. Carga el sketch y abre el monitor a 9600 baudios.

7. 🟢 **Repite la batería de pruebas de la Lección 34**: línea base sobre blanco, tira bajo el centro, tira bajo cada canal por turno, tira entre dos canales. Cada patrón debe ser idéntico al que anotaste ayer con el sketch de las cinco variables. Marca cada coincidencia en tu cuaderno con una ✔. Si un patrón difiere, detente: algo se movió entre las dos versiones (¿un pin mal copiado? ¿el orden del contenido del array?).

8. 🟢 **La prueba del dedo fantasma.** Sin cargar nada, señala en el código el `PINES[i]` del `loop()` y explica en voz alta qué casilla se lee en la tercera vuelta del bucle y a qué canal físico corresponde (respuestas: `PINES[2]`, pin A2, canal IR3, el del centro). Si puedes responder sin mirar la tabla de arriba, el índice ya es tuyo.

9. 🟢 **Cambia una sola cosa: el ritmo.** Como variación controlada, sube el `delay(200)` a `delay(500)`. El patrón debe llegar más lento, idéntico en contenido. Devuélvelo luego a 200: el ritmo de muestreo no cambia qué se mide, solo cuán seguido.

10. 🟢 **Cierra la sesión.** Cierra el monitor y desconecta el USB (🟡 si lo prefiere el adulto). Este sketch es la base de las Lecciones 36, 37 y 38: no lo pierdas de vista.

> **[PENDIENTE VISUAL]**
> - **Tipo:** diagrama conceptual del array y el bucle.
> - **Objetivo:** visualizar la fila de casillas, los índices 0–4 y el bucle que las recorre una por una.
> - **Descripción:** fila horizontal de cinco casillas etiquetadas PINES[0] a PINES[4] con los pines A4–A0 dentro y debajo el canal (IR1–IR5); sobre la fila, una flecha del bucle `for` que entra por la casilla 0 y sale tras la 4; una casilla fantasma PINES[5] fuera de la fila, en gris y tachada, con la nota "no existe".
> - **Elementos que deben señalarse:** índices 0–4, pines, canales, condición `i < 5` junto a la salida del bucle, casilla 5 tachada.
> - **Fuente técnica:** referencia del lenguaje Arduino, https://docs.arduino.cc/language-reference/, secciones array y for.
> - **Texto alternativo sugerido:** "Fila de cinco casillas PINES con índices del 0 al 4 y una casilla 5 tachada que no existe".

## Desafío: leer la fila al revés

Sin romper nada, haz una copia del sketch en tu computador y modifícala para que el patrón se imprima de IR5 a IR1 (el dígito de la izquierda pasaría a ser IR5). Pista: el bucle puede contar hacia atrás: `for (int i = 4; i >= 0; i--)`. Carga la copia y verifica con la tira bajo IR1: ahora ¿qué dígito cambia? Este ejercicio entrena la diferencia entre el orden físico de la fila y el orden en que tú decides recorrerla — y explica por qué el curso fija el formato IR1-primero como convención.

## Si no funciona

| Síntoma | Qué revisar | Acción |
|---|---|---|
| No compila | ¿Puntos y comas o llaves perdidas al copiar? | Revisa que el array termine en `};` y que cada `for` tenga sus llaves |
| El patrón salió en otro orden (A0 primero) | ¿Copiaste el contenido del array en orden? | Debe ser exactamente `{ A4, A3, A2, A1, A0 }`; cuenta desde la izquierda |
| Los patrones no coinciden con los de la Lección 34 | ¿Cambió algo más además de la estructura? | Compara las dos ventanas línea por línea; el contrato de igualdad del paso 2 no admite excepciones |
| El monitor muestra caracteres extraños | ¿Velocidad distinta de 9600 baudios? | Ajústala en el selector del monitor (Lección 08) |
| Nada se imprime pero compila bien | ¿Placa y puerto correctos tras reconectar el USB? | Verifica con la prueba de desconexión de la Lección 05 |

## Lecturas y videos para explorar

- [Diagrama correcto del tracker de cinco canales](../../assets/osoyoo-manual/pagina-18-pinout-tracker-correcto.png) — Inglés; manual del fabricante; 8 min. Aprenderás diagrama correcto del tracker de cinco canales. Esencial.
- [Erratas y decisión canónica IR1–IR5](../../docs/reference/errata-osoyoo.md) — Español; referencia interna; 8 min. Aprenderás erratas y decisión canónica ir1–ir5. Opcional.

Misma salida, la mitad del código: eso es haber ganado una herramienta. En la [Lección 36](36-estimar-donde-esta-la-linea.md) le sacarás provecho de verdad, cuando los cinco dígitos se conviertan en un solo número con signo que dice hacia dónde se desvió la línea.

## Referencias técnicas de la clase

- [Referencia del lenguaje Arduino](https://docs.arduino.cc/language-reference/), secciones `array` y `for`: declaración con longitud fija, indexación desde cero y recorrido con contador.
- El array `PINES[5]` y su orden reproducen el mapa canónico verificado en la [Lección 32](32-ir1-a-ir5-un-mapa-espacial.md) contra el diagrama de la página 18 del [manual OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf).

## Cuéntale a papá

Enséñale las dos ventanas lado a lado: el programa de las cinco variables y el del array. Cuéntale qué se repite en el primero y cómo el bucle lo reemplaza. Explícale por qué la fila cuenta desde cero y qué pasa si pides la casilla 5 — el error que no se ve como error. Si él programa en su trabajo, pregúntale cómo llaman a este tipo de mejora que no cambia lo que se ve. Marca la sesión en [PROGRESS.md](../../PROGRESS.md).

Con la fila de casillas dominada, la [Lección 36](36-estimar-donde-esta-la-linea.md) le pone números a la posición de la línea: pesos, promedio y el primer número con decimal del curso.
