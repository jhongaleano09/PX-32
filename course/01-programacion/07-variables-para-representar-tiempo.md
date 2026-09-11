# Lección 07 — Variables para representar tiempo

## ¿Qué explica mejor el programa: `500` o `intervaloMs`?

En el Blink anterior, el número `500` aparecía dos veces. Tú sabías que significaba medio segundo porque acababas de escribirlo, pero otra persona tendría que investigar. Además, para cambiar el ritmo debía encontrar ambos números y modificarlos sin olvidar ninguno.

Un nombre puede conservar la intención. En vez de repetir `500`, el programa puede declarar:

```cpp
int intervaloMs = 500;
```

`int` indica que guardaremos un número entero. `intervaloMs` es el nombre elegido. El signo `=` **asigna** el valor de la derecha al espacio nombrado a la izquierda. Aquí no pregunta si dos cosas son iguales; hace que `intervaloMs` comience valiendo 500.

Una **variable** es un dato con nombre cuyo valor podría cambiar. Una **constante** también tiene nombre, pero el programa promete no reasignarla. Usaremos una constante para el pin físico —no queremos que el LED salte de D13 a otro pin durante la ejecución— y una variable para el intervalo que vamos a probar.

En Scratch ya viste variables como marcadores o vidas. La diferencia es que C++ exige declarar qué clase de dato guardarás y escribir cada signo con precisión.

## Preparativos para una comparación justa

Necesitas comprender `setup()`, `loop()`, `digitalWrite()` y `delay()` de la [Lección 06](06-primer-programa-blink.md). Prepara:

- PX-32 ensamblado, apagado y sin USB.
- Computador con Arduino IDE 2 y cable USB de datos.
- El archivo [07-variables-para-representar-tiempo.ino](../../code/educational/07-variables-para-representar-tiempo/07-variables-para-representar-tiempo.ino).
- Una hoja pequeña con tres columnas tituladas `200`, `500` y `1000`, y un lápiz.
- Un adulto para aislar la alimentación y el servo S1.

🔴 Antes de conectar USB, tu padre retira las baterías 18650 y desconecta el conector del servo S1 con todo apagado, sujetando su carcasa plástica. D13 se comparte entre `LED_BUILTIN` y la señal del servo. Registren la orientación para restaurarlo después. Si el aislamiento no puede comprobarse, trabaja con el código y el botón Verificar, sin subirlo.

## Lee el sketch como un mapa de nombres

1. 🟢 Abre el `.ino` y comprueba este contenido:

```cpp
// Curso PX-32 — Lección 07: una variable representa el tiempo.
const int PIN_LED = LED_BUILTIN;
int intervaloMs = 500;

void setup() {
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  digitalWrite(PIN_LED, HIGH);
  delay(intervaloMs);

  digitalWrite(PIN_LED, LOW);
  delay(intervaloMs);
}
```

2. 🟢 Señala las dos declaraciones, antes de `setup()`:

- `const int PIN_LED = LED_BUILTIN;` crea una constante entera. `const` impide que el código le asigne otro valor después.
- `int intervaloMs = 500;` crea una variable entera e inicializa su valor. El sufijo `Ms` recuerda la unidad: milisegundos.

Ambos nombres pueden usarse desde `setup()` y `loop()` porque están declarados fuera de esas funciones. Se llaman datos de alcance global. Hoy importa su utilidad: cada parte del sketch ve el mismo nombre.

3. 🟢 Busca cuántas veces aparece `intervaloMs`. La declaración da el valor una vez; las dos llamadas a `delay()` lo consultan. El código no guarda dos copias independientes de 500.

4. 🟢 Predice el efecto de cambiar solamente la línea de declaración a `int intervaloMs = 200;`. Las dos pausas deberían acortarse juntas. Predice también qué ocurriría si escribieras `intervaloMS` con `S` mayúscula en un solo `delay`: C++ distingue mayúsculas y minúsculas y no encontraría ese nombre.

## Tres pruebas, una sola variable experimental

5. 🟡 Con el adulto presente, comprueba de nuevo que batería y servo S1 estén desconectados. Conecta únicamente el USB. Selecciona `Arduino Mega or Mega 2560` y el puerto identificado en la Lección 05.

6. 🟢 Mantén `intervaloMs = 500`, verifica y sube el sketch. Observa cuatro ciclos. En la columna `500`, dibuja una barra que represente cuánto dura una vuelta completa: 500 ms encendido más 500 ms apagado, es decir, 1000 ms.

7. 🟢 Retira el USB. Cambia **solo** el valor inicial de `intervaloMs` a `200`; no cambies los dos `delay()`. Verifica, vuelve a conectar y sube. La vuelta completa ahora tarda 400 ms. Marca si el ritmo se ve más rápido o más lento que antes.

8. 🟢 Retira el USB y repite con `1000`. Cada estado dura un segundo y el ciclo, dos. Anota la comparación en la tercera columna.

| Valor de `intervaloMs` | Encendido | Apagado | Ciclo completo |
|---:|---:|---:|---:|
| 200 | 200 ms | 200 ms | 400 ms |
| 500 | 500 ms | 500 ms | 1000 ms |
| 1000 | 1000 ms | 1000 ms | 2000 ms |

Esta tabla no es una orden para memorizar. Sirve para comprobar que el nombre conserva la unidad y que el mismo algoritmo puede trabajar con distintos datos.

9. 🟢 Vuelve a `500` y prueba un error deliberado **solo con el USB retirado**: borra el punto y coma de `int intervaloMs = 500;` y pulsa Verificar. Busca en la consola la primera línea que apunte cerca de la declaración. Restaura el punto y coma y verifica de nuevo. No pulses Subir mientras el código tenga errores.

10. 🟢 Explica el resultado con esta estructura: “cambié el valor asignado a…, mantuve iguales…, y por eso ambos `delay()`…”. Si dices solo “lo hice más rápido”, falta nombrar el mecanismo.

> **[PENDIENTE VISUAL]**
> - **Tipo:** ilustración conceptual con fragmento de código y línea de tiempo.
> - **Objetivo:** mostrar que una declaración alimenta dos usos del mismo valor y que la unidad determina el ritmo observable.
> - **Descripción:** `int intervaloMs = 500;` arriba, dos flechas hacia los dos `delay(intervaloMs)`, y debajo una línea de tiempo de 500 ms encendido + 500 ms apagado. Añadir versiones pequeñas de 200 y 1000 ms para comparar, sin representar espacios de memoria como cajas físicas literales.
> - **Elementos que deben señalarse:** tipo `int`, nombre, operador de asignación, valor inicial, unidad `ms`, dos usos y duración del ciclo.
> - **Fuente técnica:** referencia oficial del lenguaje Arduino, https://docs.arduino.cc/language-reference/, secciones Variables, `const` y `delay()`.
> - **Texto alternativo sugerido:** “La variable intervaloMs declarada una vez entrega el mismo valor a dos pausas que controlan encendido y apagado”.

## Cierra la práctica sin dejar el servo bajo Blink

11. 🟡 Sube `Archivo > Ejemplos > 01.Basics > BareMinimum` para que D13 no quede configurado como salida al terminar.

12. 🟡 Retira el USB. 🔴 Solo entonces tu padre restaura el conector del servo S1 con la orientación registrada. PX-32 queda apagado, ensamblado y sin baterías.

El criterio de éxito no es haber probado tres números: es poder cambiar una sola asignación, predecir los dos intervalos y explicar por qué ambos cambian.

## Errores que esta clase puede revelar

| Síntoma | Pista específica |
|---|---|
| `'intervaloMS' was not declared in this scope` | Compara letra por letra; `intervaloMs` e `intervaloMS` son nombres distintos |
| `expected ',' or ';'` | Revisa el final de la declaración y también la línea inmediatamente anterior |
| Cambia solo la luz encendida, no la apagada | Probablemente quedó un número literal en uno de los `delay`; ambos deben usar el nombre |
| `PIN_LED` cambia durante el código | La constante no debe recibir otra asignación; su trabajo es representar una conexión fija |
| Un valor negativo o enorme produce algo extraño | Detén la prueba y vuelve a 200, 500 o 1000; esta actividad usa enteros positivos pequeños compatibles con `delay()` |
| El servo reacciona | Desconecta USB; el adulto revisa el aislamiento de S1 antes de continuar |

## Lecturas y videos para explorar

- [Estructura y lenguaje de Arduino](https://docs.arduino.cc/language-reference/) — Inglés; referencia oficial; 10 min. Aprenderás estructura y lenguaje de arduino. Esencial.
- [Ejemplos integrados de Arduino](https://docs.arduino.cc/built-in-examples/) — Inglés; tutorial oficial; 10 min. Aprenderás ejemplos integrados de arduino. Opcional.

Al explorar, busca ejemplos donde un nombre exprese una unidad o una conexión. Un buen nombre reduce las preguntas que el lector debe resolver.

## Referencias técnicas de la clase

- [Referencia del lenguaje Arduino](https://docs.arduino.cc/language-reference/), variables, constantes, `int` y `delay()`.
- [Proceso de construcción de sketches](https://docs.arduino.cc/arduino-cli/sketch-build-process), alcance y prototipos añadidos durante la preparación de `.ino`.
- [Pinout oficial de la Mega 2560](https://docs.arduino.cc/resources/pinouts/A000067-full-pinout.pdf), D13 y `LED_BUILTIN`.
- [Manual oficial de OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), páginas 13 y 17, señal S1 conectada a D13.

## Cuéntale a papá

Enséñale las tres columnas y explica la diferencia entre el nombre, el valor y la unidad. Después responde: ¿por qué `=` asigna en esta línea?, ¿por qué `PIN_LED` es constante?, ¿qué error evitamos al escribir `intervaloMs` en los dos `delay()`?

En la [Lección 08](08-px-32-aprende-a-hablarnos.md), una variable sí cambiará mientras el programa se ejecuta y podrás verla crecer en el monitor serie.
