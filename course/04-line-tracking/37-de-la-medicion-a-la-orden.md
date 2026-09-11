# Lección 37 — De la medición a la orden

## Tres empleos, un robot

Mira hacia atrás un momento. En la Lección 34 mediste: cinco lecturas y un patrón. En la Lección 36 interpretaste: pesos, promedio y una posición con signo. Hoy falta el tercer empleo de la cadena: **decidir**. Dada una posición —o la falta de ella—, ¿qué orden recibe el chasis: avanzar, corregir hacia un lado o detenerse?

La tentación es escribir todo junto: leer, calcular y decidir en un solo bloque gigante. Los programas reales hacen lo contrario, y tienen un nombre bonito para el principio: **separación de responsabilidades**. Cada parte del programa tiene un solo trabajo y lo hace bien, como un equipo de expedición: el **explorador** mira el terreno y reporta; el **navegante** traduce el reporte en un rumbo; el **piloto** ejecuta la maniobra. Si la expedición se pierde, sabes a quién preguntar: ¿falló la vista, el cálculo o el volante?

En el programa de hoy serán tres funciones con esos tres empleos: `imprimirPatron()` reporta, `estimarPosicion()` calcula y `elegirOrden()` decide. El `loop()` se convierte en algo casi aburrido de tan claro: las tres llamadas en orden, una por línea. Eso es una victoria: cuando un programa se entiende por partes, los errores se encuentran por partes.

Y una decisión de diseño que ya conoces del bloque de infrarrojo: **hoy no hay motores**. El sketch ni siquiera tiene un pin de motor. La orden se imprime — `AVANZA`, `CORRIGE HACIA IR1`, `STOP` — y las ruedas ni se enteran. Es la regla de integración que te llevaste de la Lección 30: primero datos, luego decisiones impresas, y solo al final motores.

## La política: cinco reglas y una zona muerta de decisión

El corazón de la clase es la **política de control**: el conjunto completo de reglas que traduce cualquier situación posible en exactamente una orden. No "más o menos": una orden por situación, siempre. La política de hoy, escrita como tabla:

| Situación (posición) | Orden | Por qué |
|---|---|---|
| Ningún canal ve la línea | `STOP: linea perdida` | Sin testigos no hay rumbo; parar es lo único honesto |
| Los cinco canales ven línea | `STOP: patron ambiguo` | Cruce o franja gigante: el promedio de -2..+2 no representa un rumbo (Lección 36) |
| Posición menor o igual a -0.4 | `CORRIGE hacia IR1` | La línea está del lado IR1: girar hacia ella |
| Posición mayor o igual a +0.4 | `CORRIGE hacia IR5` | La línea está del lado IR5: girar hacia ella |
| Resto: -0.4 < posición < +0.4 | `AVANZA` | La línea está bastante centrada: seguir |

Observa los bordes de la tabla. Los dos primeros casos no usan la posición para nada: miran directamente a los testigos, porque son situaciones donde la posición miente o no existe. Solo los tres últimos usan el número. Y el 0.4 no es magia: es la **banda de tolerancia**, el ancho de error que decidimos perdonar antes de corregir. Con tolerancia muy angosta (0.1) el robot zigzaguea nervioso corrigiendo cada milímetro; con tolerancia holgada (1.5) deja escaparse la línea antes de reaccionar. Hoy vale 0.4; en el hito podrás afinarla.

Nota también el orden de las preguntas: primero los casos sintestigos y ambiguos, después los signos de la posición. Si preguntaras al revés, un cruce (posición 0.0) recibiría `AVANZA` — exactamente la mentira aritmética que destapamos con la tira ancha. En una política, **el orden de las preguntas es parte de la política**.

## Lo que necesitas

- PX-32 con tracker calibrado (Lección 33) y las lecciones 34–36 frescas en el cuaderno: ley digital, lado de IR1 y tabla de puestos de control.
- Tu pista de práctica: hoja blanca, tira de 25 mm y la tira ancha de ~60 mm de la Lección 36.
- Computador con Arduino IDE 2 y cable USB.
- El sketch [37-de-la-medicion-a-la-orden.ino](../../code/educational/37-de-la-medicion-a-la-orden/37-de-la-medicion-a-la-orden.ino).

🟢 Programar, cargar, probar patrones y llenar la tabla es tuyo. 🟡 El adulto conecta el USB. 🔴 Nada de baterías: el sketch no puede mover una rueda aunque quisiera.

## El programa, por dentro

1. 🟢 Abre el `.ino` y recórrelo completo; debe ser idéntico a este bloque:

```cpp
// Curso PX-32 - Leccion 37: del patron a la orden, sin tocar motores.
// Tres funciones, tres empleos: reportar, estimar y decidir.
// La orden solo se imprime: ningun pin de motor existe aqui.

const int PINES[5] = { A4, A3, A2, A1, A0 };

// Ley de tu cuaderno (Leccion 34): que imprime un canal sobre negro.
const int LECTURA_SOBRE_NEGRO = LOW;

// Banda de tolerancia: cuanto perdonamos antes de corregir.
const float TOLERANCIA = 0.4;

// La llena estimarPosicion() y la lee elegirOrden():
// el puente de datos entre las dos funciones.
int cuantosVenLinea;

void imprimirPatron() {
  for (int i = 0; i < 5; i++) {
    Serial.print(digitalRead(PINES[i]));
  }
}

float estimarPosicion() {
  int sumaDePesos = 0;
  cuantosVenLinea = 0;

  for (int i = 0; i < 5; i++) {
    if (digitalRead(PINES[i]) == LECTURA_SOBRE_NEGRO) {
      sumaDePesos = sumaDePesos + (i - 2);
      cuantosVenLinea = cuantosVenLinea + 1;
    }
  }

  if (cuantosVenLinea == 0) {
    return 0;
  }

  return float(sumaDePesos) / cuantosVenLinea;
}

void elegirOrden(float posicion) {
  if (cuantosVenLinea == 0) {
    Serial.println(" -> STOP: linea perdida");
  } else if (cuantosVenLinea == 5) {
    Serial.println(" -> STOP: patron ambiguo");
  } else if (posicion < -TOLERANCIA) {
    Serial.println(" -> CORRIGE hacia IR1");
  } else if (posicion > TOLERANCIA) {
    Serial.println(" -> CORRIGE hacia IR5");
  } else {
    Serial.println(" -> AVANZA");
  }
}

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(PINES[i], INPUT);
  }
  Serial.begin(9600);
}

void loop() {
  imprimirPatron();
  float posicion = estimarPosicion();
  elegirOrden(posicion);
  Serial.println();
  delay(300);
}
```

2. 🟢 **El `loop()` como organigrama.** Tres llamadas y ya: `imprimirPatron()`, `estimarPosicion()` y `elegirOrden(posicion)`. Compara con el `loop()` de la Lección 36, donde todo vivía amontonado. El comportamiento es el mismo; lo que cambió es que ahora el programa **declara su propia estructura**: se lee como la cadena explorador → navegante → piloto. Cuando en el hito algo falle, mirarás la función que corresponde y no el sketch entero.

3. 🟢 **Una función que devuelve.** `estimarPosicion()` empieza con `float` en lugar de `void`: anuncia que **retorna** un número con decimal. Ya conocías la idea de la Lección 11 (una función puede entregar un resultado), y aquí la ves trabajar: el resultado viaja hacia `float posicion = ...` y de ahí como **argumento** a `elegirOrden(posicion)`. El dato fluye por las funciones como un informe que sube por la cadena de mando.

4. 🟢 **El puente `cuantosVenLinea`.** `elegirOrden()` necesita dos datos: la posición **y** si había testigos. La posición llega por argumento; `cuantosVenLinea` es una variable declarada fuera de toda función (una variable **global**) que `estimarPosicion()` llena y `elegirOrden()` lee. Las globales hay que manejarlas con cuidado —cualquier función puede escribirlas—, pero aquí hacen de puente limpio entre dos empleos que comparten un insumo.

5. 🟢 **El `return 0` del caso perdido** parece devolver "centrada", pero fíjate que `elegirOrden()` nunca usa esa posición: revisa `cuantosVenLinea == 0` **antes** de mirar el número. El cero viaja, pero nadie lo escucha. Aun así, hay que devolver *algo* válido, y el cero es el pasajero inofensivo de siempre.

6. 🟢 **`TOLERANCIA` como constante.** Podríamos escribir `0.4` directo en las comparaciones, pero la constante tiene nombre y vive arriba, donde se ve. Cambiar una sola línea para afinar el comportamiento del robot entero es el tipo de poder que dan las constantes bien nombradas (Lección 07).

7. 🟢 **Predice la tabla completa.** Antes de cargar, copia la tabla de abajo y completa la columna "Orden que imprimirá" para TU ley digital. Después comprobarás con el monitor: siete aciertos de siete, sin mirar el código, es la meta.

## El experimento de los siete patrones

8. 🟡 El adulto conecta el USB. Carga el sketch, abre el monitor a 9600 baudios y espera la lluvia de líneas `patron -> orden`.

9. 🟢 **Llena la tabla con tus manos.** Coloca bajo el robot, una a una, las siete situaciones y anota lo que imprime:

| # | Qué pones bajo la fila | Patrón (con tu ley) | Orden que imprime |
|---|---|---|---|
| 1 | Nada (todo blanco) | | |
| 2 | Tira de 25 mm bajo IR3 | | |
| 3 | Tira bajo IR2 (o entre IR2 e IR3) | | |
| 4 | Tira bajo IR4 (o entre IR3 e IR4) | | |
| 5 | Tira bajo IR1 | | |
| 6 | Tira bajo IR5 | | |
| 7 | Tira ancha de ~60 mm (los cinco canales) | | |

10. 🟢 **Contrasta la tabla.** Compara con tus predicciones del paso 7. Cada discrepancia es una joya: ¿no entendías la regla, o la regla no dice lo que creías? Relee la tabla de la política y el código de `elegirOrden()` hasta que la discrepancia muera.

11. 🟢 **La frontera de la tolerancia.** Desliza la tira lentamente desde el centro hacia IR1. En algún punto la orden saltará de `AVANZA` a `CORRIGE hacia IR1`: esa es la banda de tolerancia en vivo. Estima con tus puestos de control (Lección 36) en qué posición ocurrió el salto: debería andar cerca de -0.4. ¿Te gustaría un robot más nervioso o más paciente? Cambia `TOLERANCIA` a 0.1, carga, repite el deslizamiento… y devuelve el 0.4 antes de la próxima lección.

12. 🟢 **La orden dominante.** Termina siempre el experimento retirando la tira por completo: la orden debe ser `STOP: linea perdida` en menos de un segundo (el `delay(300)` es el techo). Repítelo tres veces. Esa maniobra es tu freno de mano del hito: si algún día el robot no se detiene al perder la línea, algo grave falla en la política y la sesión termina ahí.

13. 🟢 **Cierra la sesión.** Monitor cerrado, USB desconectado (🟡 si lo prefiere el adulto). Tu cuaderno se queda con la tabla completa de siete filas: es el certificado de que la política funciona sobre papel antes de tocar un motor.

> **[PENDIENTE VISUAL]**
> - **Tipo:** diagrama de flujo de la política de decisión.
> - **Objetivo:** mostrar el orden de las preguntas y por qué los casos sin testigos y ambiguos se atienden antes de mirar la posición.
> - **Descripción:** flujo vertical con cuatro rombos de decisión en orden: "¿cuantosVenLinea == 0?" → STOP linea perdida; "¿== 5?" → STOP patron ambiguo; "¿posicion < -0.4?" → CORRIGE hacia IR1; "¿posicion > +0.4?" → CORRIGE hacia IR5; rombo final a AVANZA; cada salida lleva la línea de código exacta que la produce.
> - **Elementos que deben señalarse:** las cinco órdenes finales, la constante TOLERANCIA en los umbrales, el orden secuencial de las preguntas.
> - **Fuente técnica:** sketch 37 del repositorio, función `elegirOrden()`.
> - **Texto alternativo sugerido:** "Diagrama de flujo con las preguntas de la política de línea en orden y las cinco órdenes posibles".

## Desafío: el arquitecto de políticas

Sin cargar nada, propón un cambio a la política y discútelo con tu padre: ¿debería el robot, al perder la línea, **recordar** hacia qué lado la vio por última vez y girar hacia allá para buscarla en lugar de parar? Ese es el truco de muchos seguidores reales (los rallies pierden la pista una fracción de segundo en las curvas). Dibuja la regla nueva y discutan el riesgo: ¿qué pasa si recuerda mal? Guarda la idea: es una mejora posible para después del hito, no para mañana.

## Si no funciona

| Síntoma | Qué revisar | Acción |
|---|---|---|
| Siempre imprime STOP o siempre AVANZA | ¿`LECTURA_SOBRE_NEGRO` contradice tu ley de la Lección 34? | Con la ley invertida, "todo es línea" o "nada es línea"; corrige la constante y repite la tabla |
| CORRIGE hacia el lado que no esperabas | ¿Los pesos quedaron corridos? ¿IR1 es el extremo que crees? | Repite el paso 12 de la Lección 34 con la marca de cinta; la política sigue la fila, no la costumbre |
| Con la tira al centro imprime CORRIGE | ¿La tira quedó entre IR3 y su vecino? | Centra mejor; si persiste, baja el titileo recalibrando (Lección 33) |
| Con la tira ancha imprime AVANZA | ¿La tira cubre de verdad los cinco canales? | Ensánchala o alinéala; el caso ambiguo exige cinco testigos simultáneos |
| No compila | ¿Copiaste las tres funciones completas y en orden? | Cada función necesita su tipo de retorno, sus llaves y vivir fuera de las otras |
| Las órdenes llegan lentas | ¿`delay(300)` duplicado o muy grande? | Debe ser uno solo; el ritmo se ajusta en esa única línea |

## Lecturas y videos para explorar

- [Diagrama correcto del tracker de cinco canales](../../assets/osoyoo-manual/pagina-18-pinout-tracker-correcto.png) — Inglés; manual del fabricante; 8 min. Aprenderás diagrama correcto del tracker de cinco canales. Esencial.
- [Erratas y decisión canónica IR1–IR5](../../docs/reference/errata-osoyoo.md) — Español; referencia interna; 8 min. Aprenderás erratas y decisión canónica ir1–ir5. Opcional.

La cadena está completa en papel: medir, estimar, decidir. En la [Lección 38](38-hito-seguir-una-linea.md) llega el cuarto empleo — el piloto — y con él las ruedas, las baterías y el hito del bloque.

## Referencias técnicas de la clase

- [Referencia del lenguaje Arduino](https://docs.arduino.cc/language-reference/), declaración de funciones con tipo de retorno (`float`), `return`, argumentos y variables globales.
- Regla de integración del curso: decisiones impresas antes de motores (Lección 30) y STOP dominante ante pérdida de señal.
- Casos "sin línea" y "patrón ambiguo" verificados en la Lección 36 antes de convertirse en ramas de la política.

## Cuéntale a papá

Muéstrale el juego de los siete patrones y explícale la tabla de la política: por qué perder la línea y el cruce terminan en STOP antes de que el número diga nada, y qué papel juega la tolerancia de 0.4. Pregúntale qué haría él si su GPS perdiera la señal en una curva: ¿seguir derecho, frenar o recordar el último rumbo? Conecta esa charla con el desafío. Marca la sesión en [PROGRESS.md](../../PROGRESS.md).

Todo está probado en papel. La [Lección 38](38-hito-seguir-una-linea.md) enciende los motores: tres fases, una pista real y el día que PX-32 lee el piso solo.
