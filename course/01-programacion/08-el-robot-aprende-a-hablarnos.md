# Lección 08 - El robot aprende a hablarnos

## Misión

Enviar texto y números desde la Mega al Serial Monitor para observar el estado interno de un programa.

## Antes de tocar a PX-32

Un LED solo muestra una pequeña cantidad de información. La comunicación serial envía bits uno después de otro. `Serial.begin(9600)` prepara el puerto con una velocidad acordada. El monitor debe usar el mismo baud rate.

`Serial.print()` escribe sin salto de línea automático. `Serial.println()` añade un final de línea, útil para separar registros.

Mostrar datos antes de mover motores será nuestra herramienta principal de depuración.

## La pregunta

¿Cómo podemos comprobar que una variable cambia aunque no esté conectada a un actuador?

## Nuestra predicción

Lee el programa contador y escribe las primeras cinco líneas que esperas ver.

## Conceptos nuevos

Serial, UART, baud rate, `Serial.begin`, `print`, `println`, contador y observabilidad.

## Hardware utilizado

Mega2560 sola y cable USB.

## Conexiones

USB -> Mega -> `Serial` -> Serial Monitor. Esta práctica no usa `Serial1` de Bluetooth/Wi-Fi.

## Seguridad

**Nivel verde.** Sin batería, motores ni servo. Mantener la preparación de banco.

## Experimento 1: saludo

1. Abre [08-hola-px32.ino](../../code/educational/08-hola-px32/08-hola-px32.ino).
2. Predice cuántas veces aparecerá el saludo.
3. Verifica, carga y abre Serial Monitor.
4. Configura `9600 baud`.
5. Pulsa RESET y observa.

```cpp
void setup() {
  Serial.begin(9600);
  Serial.println("Hola, soy PX-32");
}

void loop() {
}
```

El mensaje aparece una vez por inicio porque está en `setup()`.

## Experimento 2: contador

Abre [08-contador-px32.ino](../../code/educational/08-contador-px32/08-contador-px32.ino):

```cpp
int cuenta = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Hola, soy PX-32");
}

void loop() {
  Serial.print("Cuenta: ");
  Serial.println(cuenta);
  cuenta = cuenta + 1;
  delay(1000);
}
```

## Código explicado

Las comillas delimitan texto. `cuenta` sin comillas representa el número actual. `cuenta = cuenta + 1` primero calcula el lado derecho y guarda el resultado en la variable del lado izquierdo. No es una ecuación algebraica que deba ser verdadera para siempre; es una actualización.

## Antes de ejecutar

¿Qué aparece después de `Cuenta: 4`? ¿Qué ocurre si pulsas RESET? ¿Qué cambiaría si quitamos `delay(1000)`?

## Resultado esperado

El contador aumenta aproximadamente una vez por segundo. RESET vuelve a ejecutar el programa y `cuenta` comienza en 0. Sin `delay`, las líneas aparecen demasiado rápido y la variable aumenta muchas veces por segundo.

## Observaciones

| Prueba | Baud monitor | Delay | Primeros valores | Legibilidad |
|---|---:|---:|---|---|
| A | 9600 | 1000 ms | | |
| B | Otro | 1000 ms | | |
| C | 9600 | 100 ms | | |

## Cambia una cosa

Primero cambia solo el baud rate del monitor a un valor distinto. Después restáuralo y cambia solo el `delay` a 100 ms.

## ¿Qué ocurrió?

Con baud rate incompatible pueden aparecer caracteres ilegibles o nada útil. Con menos espera, el formato sigue siendo válido pero llega con más frecuencia.

## Desafío

Imprime una sola línea con este formato:

```text
PX-32 lleva 7 segundos despierto
```

No busques una función nueva: combina `print` y `println` con el contador.

## Depuración

- Monitor vacío: comprobar puerto, programa cargado y RESET.
- Caracteres extraños: igualar baud rate.
- Todo en una línea: usar `println` al final del registro.
- La cuenta no cambia: revisar la asignación y que esté dentro de `loop()`.
- Reinicia al mover un cable: detenerse; el montaje externo no corresponde a esta práctica.

## Quiz

1. ¿Qué acuerda `Serial.begin(9600)`?
2. ¿Diferencia entre `print` y `println`?
3. ¿Por qué el saludo aparece una vez?
4. ¿Qué hace `cuenta = cuenta + 1`?
5. ¿Qué ocurre con la variable al reiniciar?
6. ¿Por qué Serial será útil antes de mover motores?

Respuestas: [Solución 08](../../solutions/08-el-robot-aprende-a-hablarnos.md).

## Bitácora

Pegar las primeras diez líneas del contador, anotar la prueba de baud rate y explicar RESET con memoria flash/SRAM.

## Lo que ya sabemos

Podemos ejecutar, representar datos y observarlos sin añadir hardware.

## Próxima misión

Aprenderemos a tomar decisiones con comparaciones, `bool` e `if/else`.

## Fuentes

**Arduino:** entorno IDE y Serial Monitor. **CURSO PX-32:** saludo, contador y experimentos.
