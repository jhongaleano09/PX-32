# Lección 06 - Primer programa: Blink

## Misión

Hacer parpadear el LED integrado de la Mega, predecir tres ritmos y construir una señal SOS.

## Antes de tocar a PX-32

Lee [¿Cómo funciona un LED?](../../docs/readings/como-funciona-un-led.md).

Arduino organiza el programa alrededor de dos funciones:

- `setup()` se ejecuta una vez después de encender o reiniciar;
- `loop()` se repite mientras la placa tenga energía.

Antes de controlar un pin debemos definir si será entrada o salida con `pinMode`. `digitalWrite` ordena HIGH o LOW. `delay` pausa el programa en milisegundos.

## La pregunta

¿Cómo cambia el ritmo visible si reducimos el tiempo de espera sin cambiar el circuito?

## Nuestra predicción

Ordena de más lento a más rápido: 100 ms, 500 ms, 1000 ms. Predice cuál será fácil de contar durante diez segundos.

## Conceptos nuevos

Comentario, función, `setup`, `loop`, `pinMode`, `digitalWrite`, HIGH, LOW y `delay`.

## Hardware utilizado

- Mega2560 sola.
- Cable USB de datos.
- LED integrado en D13.

## Conexiones

USB computador -> Mega. Ninguna batería. Ningún servo conectado a D13.

## Seguridad

**Nivel amarillo por preparación, verde durante código.** Confirmar la misma placa aislada de la Lección 05. D13 comparte ruta con el servo en PX-32 ensamblado.

## Experimento

1. Abre [06-blink-px32.ino](../../code/educational/06-blink-px32/06-blink-px32.ino).
2. Lee el programa de arriba abajo sin cargarlo.
3. Pulsa Verify y luego Upload.
4. Cuenta ciclos completos durante diez segundos.
5. Cambia ambos `delay(1000)` a `delay(500)`, predice, verifica y carga.
6. Repite con `100`.
7. Registra el resultado de cada versión.

## Código

```cpp
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
```

## Código explicado

Las llaves delimitan un bloque. El punto y coma termina una instrucción. `LED_BUILTIN` es un nombre definido para el pin del LED integrado. HIGH y LOW no significan universalmente encendido/apagado, pero en este circuito producen esos estados.

Un ciclo con 1000 ms encendido y 1000 ms apagado tarda 2000 ms: dos segundos. La frecuencia del ciclo es 0.5 Hz.

## Antes de ejecutar

¿Cuántos ciclos completos predices en diez segundos con 1000/1000 ms? ¿Y con 500/500 ms?

## Resultado esperado

Aproximadamente 5 y 10 ciclos, respectivamente. Con 100/100 ms esperaríamos cerca de 50, difíciles de contar a ojo. La carga y pequeñas diferencias de observación no cambian el razonamiento principal.

## Observaciones

| ON ms | OFF ms | Ciclo total | Ciclos predichos/10 s | Observados |
|---:|---:|---:|---:|---:|
| 1000 | 1000 | 2000 ms | 5 | |
| 500 | 500 | 1000 ms | 10 | |
| 100 | 100 | 200 ms | 50 | |

## Cambia una cosa

Usa 100 ms encendido y 900 ms apagado. El período sigue siendo un segundo, pero cambia el porcentaje de tiempo encendido.

## ¿Qué ocurrió?

Compara frecuencia y ciclo de trabajo. Un ciclo por segundo no obliga a estar medio segundo encendido.

## Desafío: SOS

Abre [06-sos-px32.ino](../../code/educational/06-sos-px32/06-sos-px32.ino) solo después de diseñar en papel: tres pulsos cortos, tres largos y tres cortos. Decide el espacio entre señales y entre mensajes.

## Depuración

- No enciende: confirmar Upload exitoso y mirar el LED `L`, no RX/TX.
- Parpadeo distinto: verificar que cambiaste ambos `delay` o explicar la asimetría.
- Error de compilación: buscar primera línea marcada, llaves y `;`.
- Servo se mueve: apagar, retirar USB y revisar aislamiento de D13 antes de continuar.

## Quiz

1. ¿Cuántas veces corre `setup()` tras un reset?
2. ¿Qué bloque se repite?
3. ¿Qué unidad usa `delay()`?
4. ¿Cuánto dura un ciclo de 500 ms HIGH + 500 ms LOW?
5. ¿Qué hace `pinMode(..., OUTPUT)`?
6. ¿Por qué Blink se hace con el servo aislado?

Respuestas: [Solución 06](../../solutions/06-primer-programa-blink.md).

## Bitácora

Guardar predicciones, tabla, versión de SOS y un error encontrado con su causa demostrada.

## Lo que ya sabemos

Ya distinguimos compilar, cargar y ejecutar, y controlamos una salida digital.

## Próxima misión

Reemplazaremos números repetidos por variables con significado.

## Fuentes

**Arduino:** ejemplo integrado Blink y [Built-in Examples](https://docs.arduino.cc/built-in-examples). **CURSO PX-32:** variaciones, cálculo y SOS.
