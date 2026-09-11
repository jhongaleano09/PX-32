# Lección 45 — De microsegundos a centímetros

## La fórmula que convierte tiempo en espacio

Tienes un número: 991 µs. Es el eco de tu mano a 17 cm. Y tienes una misión de detective: ¿qué operación convierte 991 en 17?

Ya casi toda la investigación está hecha. La Lección 42 te dio la geometría (el sonido viaja **ida y vuelta**, así que hay que dividir entre 2) y la velocidad (343 m/s en aire a unos 20 °C). La Lección 44 te dio la medición cruda en microsegundos. Hoy solo falta cuadrar las unidades y escribir la fórmula completa — y después, someterla a juicio: un instrumento no se cree por bonito; se **contrasta contra una regla**.

Primero, la velocidad traducida a nuestras unidades. La velocidad del sonido es 343 metros por segundo. Como 1 m = 100 cm y 1 s = 1 000 000 µs:

```text
343 m/s  =  34 300 cm / 1 000 000 us  =  0,0343 cm por microsegundo
```

Cada microsegundo que el sonido estuvo de viaje, avanzó 0,0343 cm. Ahora sí, la fórmula de la distancia, que de ahora en adelante vivirá en tus sketches:

```text
distancia_cm = eco_us x 0,0343 / 2
```

Compruébala con tu baliza de ayer: 991 µs × 0,0343 = 33,99 cm de recorrido… dividido entre 2 = **17,0 cm**. El número que salió es exactamente el que metiste. Y fíjate en el detalle elegante: la hoja de datos de los módulos tipo HC-SR04 da la receta equivalente `distancia = eco / 58` — y 1/58 ≈ 0,0172 ≈ 0,0343/2. Dos caminos (física y fabricante) que llegan al mismo lugar: eso, en ingeniería, es una buena señal.

Una honestidad final antes de medir: 0,0343 es la velocidad a unos 20 °C. Con aire más frío el sonido viaja un poco más lento y con aire más caliente, un poco más rápido; tu robot no mide la temperatura, así que su conversión hereda ese pequeño error. No es motivo para tirar la fórmula: es motivo para **no exigirle perfección** — y para entender de dónde saldrán las diferencias que verás hoy.

## Lo que necesitas

- PX-32 con el módulo verificado (Lecciones 43–44), sin baterías, sobre la mesa con el frente al borde.
- Computador con Arduino IDE 2 y cable USB.
- El sketch [45-de-microsegundos-a-centimetros.ino](../../code/educational/45-de-microsegundos-a-centimetros/45-de-microsegundos-a-centimetros.ino).
- Cinta métrica o regla, y tres marcas en la mesa con cinta: a **10, 20 y 30 cm** del frente de los cilindros del sensor (mide desde los cilindros, no desde el borde del chasis: la distancia que el sensor mide empieza en su cara).
- Un libro duro parado (la muralla de siempre).
- Tu cuaderno para la tabla de contraste.

🟢 Medir y calcular es tuyo. 🟡 Tu padre presencia el USB. 🔴 Cableado y energía, el adulto.

## El programa: la fórmula hecha función

1. 🟢 Abre el `.ino` y verifica que coincida con este bloque:

```cpp
// Curso PX-32 - Leccion 45: de microsegundos a centimetros.
// distancia_cm = eco_us x 0.0343 / 2  (343 m/s a ~20 grados C,
// dividido entre 2 porque el sonido va y vuelve).

const byte TRIG = 30;
const byte ECHO = 31;
const unsigned long TIMEOUT_US = 30000UL;

// Velocidad del sonido a ~20 grados C: 343 m/s = 0.0343 cm/us.
const float SONIDO_CM_POR_US = 0.0343;

unsigned long medirEcoEnUs() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  return pulseIn(ECHO, HIGH, TIMEOUT_US);
}

float distanciaEnCm(unsigned long ecoUs) {
  return ecoUs * SONIDO_CM_POR_US / 2.0;  // entre 2: ida y vuelta
}

void setup() {
  pinMode(TRIG, OUTPUT);
  digitalWrite(TRIG, LOW);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);
  Serial.println("Leccion 45: distancia estimada en cm.");
}

void loop() {
  unsigned long us = medirEcoEnUs();

  if (us == 0) {
    Serial.println("SIN ECO: nada fiable adelante");
  } else if (us > 23200UL) {
    Serial.println("ECO DEMORADO: fuera de alcance");
  } else {
    Serial.print(us);
    Serial.print(" us  ->  ");
    Serial.print(distanciaEnCm(us), 1);
    Serial.println(" cm");
  }

  delay(200);
}
```

2. 🟢 **Lo nuevo, reducido a dos piezas:**

   - `const float SONIDO_CM_POR_US = 0.0343;` — un número con decimales (`float`) y con **nombre**: escribir la velocidad con nombre, y no el 0,0343 suelto en medio de una cuenta, es lo que permite cambiarla un día (¿si midiéramos bajo el agua? otro valor, mismo programa) y explica qué significa.
   - `distanciaEnCm()` — una función con parámetro y retorno que encapsula la fórmula. Adiós a hacer la cuenta de cabeza: el robot ya "piensa" en centímetros. El `2.0` con decimal deja claro que la división conserva los decimales; en esta línea funcionaría igual con un `2` solo (el número de la izquierda ya trae decimales), pero `2.0` es el hábito que te protege de la trampa clásica de dividir **dos enteros**: para C++, `5 / 2` es `2` — sin decimales — mientras `5 / 2.0` es `2.5`.

3. 🟢 **Sigue el rastro de un número.** Elige mentalmente una medición y recórrela: el eco sale de `medirEcoEnUs()` como 991; entra a `distanciaEnCm(991)`; dentro se multiplica por 0,0343 (33,99 cm de viaje total) y se divide entre 2 (17,0 cm). El `Serial.print(cm, 1)` lo imprime con **un solo decimal**: suficiente para centímetros de robot; imprimir cinco decimales sería fingir una precisión que el sensor no tiene.

4. 🟢 **Predice la tabla completa antes de cargar.** Con la fórmula, calcula a mano qué imprimirá el monitor con el libro a 10, 20 y 30 cm (respuestas para verificar: ~10,0; ~20,0; ~30,0… con sus ecos de ~583, ~1166 y ~1749 µs — usa 58 µs/cm como atajo de control). Anota tus tres predicciones.

5. 🟡 Tu padre conecta el USB, verifica placa/puerto, sube el sketch y abre el monitor a 9600 baudios.

## El experimento: el robot contra la regla

6. 🟢 **Primera marca: 10 cm.** Coloca el libro parado justo en la cinta de 10 cm, bien de frente a los cilindros (no inclinado: la inclinación desvía el eco hacia otro lado, como un espejo en ángulo). Espera cinco lecturas y anota en tu tabla de contraste la **mediana aproximada** — el valor del medio cuando los ordenas. Repite lo mismo en 20 y en 30 cm.

   Tu tabla debe verse así (con **tus** números):

   | Marca real | Eco típico (µs) | Estimación del robot (cm) | Diferencia (cm) |
   |---|---|---|---|
   | 10 cm | ___ | ___ | ___ |
   | 20 cm | ___ | ___ | ___ |
   | 30 cm | ___ | ___ | ___ |

7. 🟢 **El veredicto.** ¿Las diferencias caben dentro de 1 o 2 cm? Si sí, el instrumento pasó el juicio: es **útil**, no perfecto. Si alguna difiere por más de eso, no lo arregles a ciegas: revisa dónde empezaste a medir la cinta (¿desde los cilindros o desde otro punto?), la inclinación del libro y la altura (el libro debe cubrir los dos cilindros). Cada corrección, **una a la vez**.

8. 🟢 **El caso incómodo de los 2 cm.** Acerca el libro lentamente hasta pegarlo casi a los cilindros. Verás que por debajo de unos 2 cm las lecturas se vuelven locas o desaparecen. ¿Recuerdas el alcance útil (2–400 cm) de la hoja de datos? Ahí está, en vivo: tan cerca, el eco regresa mientras el sensor todavía está gritando, y no puede distinguir una cosa de la otra. **El sensor tiene una zona ciega frontal**: conocer los puntos ciegos de un instrumento es tan importante como conocer sus aciertos.

9. 🟢 **Cierre.** USB fuera con el adulto. En el cuaderno, la tabla de contraste con veredicto y una frase: "PX-32 ya mide distancias en centímetros; su margen típico es de ___, su zona ciega está por debajo de ___ cm".

## Si no funciona

| Síntoma | Qué revisar | Acción |
|---|---|---|
| Todo da el doble de lo esperado | ¿Quitaste el `/ 2.0` o el `2.0` perdió el decimal? | Revisa `distanciaEnCm`: sin la división entre dos obtendrás el recorrido completo (Lección 42) |
| Diferencias de más de 2 cm en todas las marcas | ¿Desde dónde mediste las cintas? | Mide las marcas desde la cara de los cilindros; el sensor "nace" ahí |
| Una marca sale bien y otra mal | ¿El libro cubre ambos cilindros a esa distancia? | A 30 cm el cono del sensor se abre: usa un objeto más ancho o alinea mejor |
| Números con cinco decimales | ¿Olvidaste el `, 1` del `Serial.print`? | Añádelo; un decimal basta y sobra |
| Se me olvidó qué era 23 200 | ¿Revisaste la Lección 44? | Es el límite de ~400 cm de alcance útil: por encima, `ECO DEMORADO` |

## Desafío: el día de calibración del termómetro

Este desafío es de pizarra: si un día hace frío y la velocidad real del sonido bajara a 0,0335 cm/µs, ¿cuánto marcaría el robot para un objeto que en realidad está a 100 cm? (Cálculo: el eco real sería 100 × 2 / 0,0335 ≈ 5970 µs; el robot lo convertiría con su constante vieja: 5970 × 0,0343 / 2 ≈ **102,4 cm**.) Dos centímetros y medio de error solo por la temperatura: por eso los sensores serios de precisión miden también la temperatura del aire. PX-32 no lo hará; saber por qué se equivoca un poco lo hace igual de interesante.

## Lecturas y videos para explorar

- [Velocidad, frecuencia y longitud de onda del sonido](https://openstax.org/books/physics/pages/14-1-speed-of-sound-frequency-and-wavelength) — Inglés; libro abierto; 12 min. Aprenderás velocidad, frecuencia y longitud de onda del sonido. Esencial.
- [Biblioteca Servo](https://docs.arduino.cc/libraries/servo/) — Inglés; referencia oficial Arduino; 10 min. Aprenderás biblioteca servo. Opcional.

## Referencias técnicas de la clase

- [Hoja de datos del módulo HC-SR04 (SparkFun)](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf): fórmula del fabricante `eco/58` y rango útil 2–400 cm, equivalente a nuestra derivación física.
- [OpenStax Physics, sección 14.1](https://openstax.org/books/physics/pages/14-1-speed-of-sound-frequency-and-wavelength): 343 m/s a 20 °C y la dependencia con la temperatura.
- [`float` y aritmética con decimales](https://docs.arduino.cc/language-reference/en/variables/data-types/float/) en la referencia de Arduino.

## Cuéntale a papá

Enséñale la tabla de contraste y el veredicto: el robot midió con la regla al lado y las diferencias que quedaron. Explícale la zona ciega de los 2 cm y el error por temperatura del desafío. Pregúntale si preferiría un robot que mide "perfecto" pero no sabe cuándo falla, o uno que mide "casi" y conoce sus límites: la respuesta es la filosofía de todo este curso. Marca la casilla 45 en [PROGRESS.md](../../PROGRESS.md).

Medir una vez ya sabemos. Pero un buen científico desconfía de las mediciones únicas: en la [Lección 46](46-medir-objetos-conocidos.md) mediremos muchas veces y aprenderemos a leer la calidad de los números.
