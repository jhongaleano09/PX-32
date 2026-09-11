# Lección 46 — Medir objetos conocidos

## Cuatro tiradores, un mismo aro

Imagina cuatro jugadores de básquet lanzando al aro, cinco tiros cada uno:

- **Ana** clava los cinco… pero al aro del vecino. Sus tiros van todos juntos, pero lejos del objetivo.
- **Beto** acierta dos, falla uno corto, falla uno largo, acierta otro. Sus tiros andan por ahí, desparramados.
- **Camila** clava los cinco en el centro del aro.
- **Dani** tira uno al aro, uno a la valla, uno al pasto: cada bola en un barrio distinto.

Los ingenieros le ponen nombre a esas diferencias, y son dos palabras que la gente confunde todo el tiempo: **precisión** es qué tan juntos caen tus intentos (Ana es precisa, Beto no); **exactitud** es qué tan cerca caen del objetivo real (Ana no es exacta, Camila sí). Camila es las dos cosas; Beto tiene un problema de precisión; Ana, de exactitud; Dani, de todo un poco.

¿Y qué tiene que ver el básquet con PX-32? Que **tu sensor es un tirador**. Cada medión de distancia es un tiro: la regla de la mesa marcó el aro (10, 20, 30 cm), y las cinco lecturas del sensor son los lanzamientos. Hoy vas a averiguar qué tipo de tirador es tu módulo ultrasónico — y a aprender el truco estadístico que protege a los robots de las mediciones descabelladas: en lugar de creerle a una sola lectura, se toman **varias, se ordenan y se elige la del medio**. Esa del medio se llama **mediana**, y su superpoder es que un valor loco —un eco que se perdió, una lectura extraña— apenas la mueve.

¿Por qué la mediana y no el promedio? Pruébalo con números: cinco lecturas de 20,1 – 20,3 – 20,2 – 20,4 – **75,0** (una falló por el reflejo de algo). El promedio es 31,2 cm: la falla se llevó de remate a toda la cuenta. La mediana es 20,3: el disparate quedó en un extremo y no contaminó nada. Cuando las fallas son posibles, la mediana gana.

## Lo que necesitas

- PX-32 con el módulo verificado, sin baterías, frente al borde de la mesa.
- Las tres marcas de cinta de la Lección 45 (10, 20 y 30 cm desde los cilindros).
- Computador, Arduino IDE 2 y USB.
- El sketch [46-medir-objetos-conocidos.ino](../../code/educational/46-medir-objetos-conocidos/46-medir-objetos-conocidos.ino).
- Los "objetos conocidos" de la segunda parte: el libro duro de siempre, una toalla doblada (o almohada pequeña) y el mismo libro inclinado unos 45°.
- Tu cuaderno: hoy la tabla estrella del bloque.

🟢 Medir, copiar y calcular es tuyo. 🟡 Tu padre presencia el USB. 🔴 Cableado y energía, el adulto.

## El programa: una ronda, cinco disparos

1. 🟢 Abre el `.ino` y verifica que coincida con este bloque:

```cpp
// Curso PX-32 - Leccion 46: medir objetos conocidos.
// Tres distancias reales, cinco mediciones cada una.
// Tu trabajo: copiar la tabla en el cuaderno, ordenar cada
// grupo de cinco y hallar la mediana (el valor del medio).

const byte TRIG = 30;
const byte ECHO = 31;
const unsigned long TIMEOUT_US = 30000UL;
const float SONIDO_CM_POR_US = 0.0343;
const byte DISPAROS = 5;  // cinco mediciones por distancia

unsigned long medirEcoEnUs() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  return pulseIn(ECHO, HIGH, TIMEOUT_US);
}

void rondaDeMediciones(const char *nombre, int realCm) {
  Serial.print("=== ");
  Serial.print(nombre);
  Serial.print(" | real: ");
  Serial.print(realCm);
  Serial.println(" cm ===");

  for (byte i = 1; i <= DISPAROS; i++) {
    unsigned long us = medirEcoEnUs();
    Serial.print(i);
    Serial.print(": ");

    if (us == 0) {
      Serial.println("SIN ECO");
    } else if (us > 23200UL) {
      Serial.println("FUERA DE ALCANCE");
    } else {
      Serial.print(us * SONIDO_CM_POR_US / 2.0, 1);
      Serial.println(" cm");
    }

    delay(150);  // pausa entre disparos para no mezclar ecos
  }
}

void setup() {
  pinMode(TRIG, OUTPUT);
  digitalWrite(TRIG, LOW);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);
  Serial.println("Leccion 46: cinco mediciones por distancia.");
  Serial.println("Coloca el objeto: la ronda empieza en 3 segundos.");
  delay(3000);  // tiempo para apartar la mano
}

void loop() {
  rondaDeMediciones("CERCA", 10);
  delay(500);
  rondaDeMediciones("MEDIA", 20);
  delay(500);
  rondaDeMediciones("LEJOS", 30);
  Serial.println("Copia la tabla y busca la mediana de cada grupo.");
  Serial.println("Siguiente ronda en 30 segundos...");
  delay(30000);  // tiempo de copiar con calma
}
```

2. 🟢 **Lo nuevo, en dos pedazos:**

   - `rondaDeMediciones(nombre, realCm)` es una función con **dos parámetros**: un texto y la distancia real de la marca. El `for` interior dispara `DISPAROS` (5) mediciones seguidas con 150 ms de pausa — ese descanso evita que un eco rezagado se meta en la medición siguiente (los disparos demasiado rápidos confunden a los módulos de este tipo).
   - `const char *nombre` es la manera de recibir un texto como parámetro; no profundizaremos en el asterisco todavía — piénsalo como "aquí va una etiqueta". Y ojo con la **mayúscula inicial**: `"CERCA"` es el texto que verás en el monitor, mientras `DISPAROS` con mayúsculas es una constante del programa. Dos mundos distintos que se parecen: clásico de C.

3. 🟢 **Predice el cuadro completo.** Antes de cargar: ¿qué tipo de tirador esperas que sea tu sensor — Camila (las dos cosas), Ana, Beto? ¿Creen tus lecturas de la Lección 45 que la dispersión será menor de 1 cm, entre 1 y 3, o mayor? Escribe tu apuesta.

4. 🟡 Tu padre conecta el USB, sube el sketch y abre el monitor a 9600 baudios. La secuencia de arranque da **3 segundos de margen**: coloca el libro en la marca de 10 cm y quita la mano antes de que empiece.

## El experimento: el retrato completo del tirador

5. 🟢 **Ronda 1 — copia fiel.** Copia en el cuaderno las cinco lecturas de CERCA, las cinco de MEDIA y las cinco de LEJOS, tal como salen (incluidos los SIN ECO, si aparecen: **son datos también**). El monitor se detiene 30 segundos entre rondas justamente para que copies sin pánico; si no te alcanza, pulsa el botón RESET de la placa y la ronda vuelve a empezar.

6. 🟢 **La mediana, a mano y con orden.** Para cada grupo de cinco: ordénalos de menor a mayor (¡los SIN ECO se van de la lista, pero anótalos aparte como "fallas del tirador"!) y toma **el tercero** — con cinco valores ordenados, el del medio es el tercero. Completa tu tabla estrella:

   | Marca | Lecturas (cm) | Fallas | Mediana | ¿Preciso? | ¿Exacto? |
   |---|---|---|---|---|---|
   | 10 cm | ___ ___ ___ ___ ___ | ___ | ___ | ___ | ___ |
   | 20 cm | ___ ___ ___ ___ ___ | ___ | ___ | ___ | ___ |
   | 30 cm | ___ ___ ___ ___ ___ | ___ | ___ | ___ | ___ |

   Para las dos últimas columnas usa la regla del básquet: precisión = lecturas juntas (rango menor a ~1 cm entre la mayor y la menor es excelente); exactitud = mediana a menos de ~1 cm de la marca. ¿Quién resultó ser tu sensor: Camila, Ana, Beto…?

7. 🟢 **Ronda 2 — cambia UNA sola cosa: el material.** Vuelve a poner el objeto en la marca de 20 cm, pero ahora en vez del libro pon la **toalla doblada** (que quede igual de alta y ancha: solo cambia el material). Pulsa RESET y copia la ronda de MEDIA. Compara: la toalla absorbe parte del sonido (Lección 44 te dio el anticipo) y suele aumentar las fallas y la dispersión. Anota: "material blando → ___ fallas, mediana ___".

8. 🟢 **Ronda 3 — cambia OTRA sola cosa: el ángulo.** Ahora el libro duro, pero **inclinado unos 45°** como un espejo desviado. Pulsa RESET y copia otra vez la ronda de MEDIA. El eco de un plano inclinado se refleja hacia otro lado — como la luz en un espejo en ángulo (Lección 25) — y al cilindro R puede llegar muy poquito. Este experimento explica un misterio de la vida real: por qué a los sensores de autos estacionarios "les cuesta" los postes redondos y las superficies en diagonal.

9. 🟢 **El informe del tirador.** Cierra con un párrafo en el cuaderno con tus tres hallazgos numerados: (1) qué tan preciso y exacto es tu sensor con objeto duro y frontal; (2) qué le hace un material blando; (3) qué le hace un ángulo. Ese informe es la evidencia que la Lección 49 usará para decidir cuándo confiar y cuándo frenar.

10. 🟢 **Cierre.** Monitor cerrado, USB fuera con el adulto.

## Si no funciona

| Síntoma | Qué revisar | Acción |
|---|---|---|
| No me da tiempo a copiar | ¿Conoces el botón RESET? | Pulsa RESET: la ronda completa se repite desde el principio; el de 30 s es solo un colchón |
| Muchos SIN ECO con el libro duro | ¿La mano se quedó frente al sensor? | Aparta la mano en los 3 s de arranque; el "objeto" debe ser el único frente a los cilindros |
| La mediana me sale rara | ¿Ordenaste antes de elegir el tercero? | Mediana = tercero de cinco **ordenados**; sin ordenar, cualquier posición vale |
| La toalla da lecturas normales | ¿Tu toalla es delgada o muy tensa? | Dóblala más: debe verse y sentirse como una muralla blanda; algunas telas densas rebotan igual |
| El libro inclinado da normal | ¿Inclinado hacia dónde? | Inclínalo de modo que el eco se desvíe *hacia un costado*, no hacia arriba ni hacia el sensor |

## Desafío: promedio contra mediana

Con tus datos de la ronda 1, calcula el **promedio** y la **mediana** de cada grupo. ¿En cuál grupo se diferencian más? Busca en tus lecturas si hay un valor atípico (**outlier**) que explique la diferencia. Escribe la conclusión en una frase: "cuando hay valores atípicos, la mediana es ___ que el promedio". Esa frase la aplicará tu robot cada vez que un eco se pierda.

## Lecturas y videos para explorar

- [Velocidad, frecuencia y longitud de onda del sonido](https://openstax.org/books/physics/pages/14-1-speed-of-sound-frequency-and-wavelength) — Inglés; libro abierto; 12 min. Aprenderás velocidad, frecuencia y longitud de onda del sonido. Esencial.
- [Biblioteca Servo](https://docs.arduino.cc/libraries/servo/) — Inglés; referencia oficial Arduino; 10 min. Aprenderás biblioteca servo. Opcional.

## Referencias técnicas de la clase

- [HW-009 en el diccionario de hardware](../../docs/hardware/HW-009-ultrasonico.md): errores frecuentes del sensor (objetos blandos, inclinados, timeout como 0 cm).
- [Hoja de datos del módulo HC-SR04 (SparkFun)](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf): alcance útil y comportamiento con superficies difíciles.
- [Calibración y error en la guía de sensores del curso](../../docs/reference/sensores.md): por qué se mide varias veces y se conserva el dato original.

## Cuéntale a papá

Cuéntale la fábrica de tiradores (Ana, Beto, Camila, Dani) y muéstrale tu tabla estrella: qué tan preciso y exacto resultó tu sensor. Explícale por qué la mediana es más lista que el promedio cuando hay lecturas locas, con el ejemplo del 75,0. Y cuéntale el hallazgo del libro inclinado: el eco que se va de lado como luz en un espejo. Marca la casilla 46 en [PROGRESS.md](../../PROGRESS.md).

El sensor ya mide con criterio. Pero está clavado mirando siempre al frente… hasta ahora: en la [Lección 47](47-un-servo-apunta-el-sensor.md) PX-32 estrena cuello — un servo que apunta el sensor hacia donde interese.
