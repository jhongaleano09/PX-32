# Lección 07 - Variables, constantes y tiempo

## Misión

Usar nombres para representar datos y modificar el ritmo de PX-32 cambiando una sola línea.

## Antes de tocar a PX-32

Un número como `500` no explica por sí mismo si representa velocidad, milisegundos o cantidad de intentos. Una variable une un nombre, un tipo y un valor.

```cpp
int intervaloMs = 500;
```

`int` indica un número entero; `intervaloMs` expresa propósito y unidad; `500` es el valor inicial. Si un valor no debe cambiar durante la ejecución usamos `const`:

```cpp
const int pinLed = LED_BUILTIN;
```

El sufijo `Ms` no cambia el código, pero ayuda a humanos a evitar errores de unidades.

## La pregunta

¿Puede una sola variable controlar dos pausas y mantenerlas siempre iguales?

## Nuestra predicción

Predice qué ocurre si `intervaloMs` cambia de 500 a 250 sin modificar ninguna otra línea.

## Conceptos nuevos

Variable, constante, identificador, tipo `int`, asignación, unidad y reutilización.

## Hardware utilizado

La misma Mega aislada y cable USB de las lecciones 05-06.

## Conexiones

USB -> Mega. D13 solo para LED integrado, servo aislado.

## Seguridad

**Nivel verde** tras preparación adulta. No reconectar el robot todavía.

## Experimento

1. Abre [07-variable-tiempo.ino](../../code/educational/07-variable-tiempo/07-variable-tiempo.ino).
2. Localiza declaración, lectura y posible modificación.
3. Predice el período con `intervaloMs = 500`.
4. Verifica, carga y observa.
5. Cambia solo a 250 y repite.
6. Intenta describir el efecto sin decir “va más rápido”: usa período o ciclos por segundo.

## Código

```cpp
const int pinLed = LED_BUILTIN;
int intervaloMs = 500;

void setup() {
  pinMode(pinLed, OUTPUT);
}

void loop() {
  digitalWrite(pinLed, HIGH);
  delay(intervaloMs);
  digitalWrite(pinLed, LOW);
  delay(intervaloMs);
}
```

## Código explicado

Declaramos nombres antes de las funciones para que ambas puedan usarlos. `pinLed` es constante porque el cableado no cambia mientras corre el programa. `intervaloMs` es variable porque queremos experimentar con su valor.

Dos pausas de 500 ms producen un período de 1000 ms. Con 250 ms, el período es 500 ms y aparecen dos ciclos por segundo.

## Antes de ejecutar

¿Qué línea controla ambos tiempos? ¿Qué resultado demostraría que solo uno cambió?

## Resultado esperado

Al cambiar una declaración, ambas llamadas `delay(intervaloMs)` usan el nuevo valor. Esto reduce duplicación y hace el experimento menos propenso a inconsistencias.

## Observaciones

| intervaloMs | Período calculado | Frecuencia calculada | Observación |
|---:|---:|---:|---|
| 500 | 1000 ms | 1 Hz | |
| 250 | 500 ms | 2 Hz | |
| 1000 | 2000 ms | 0.5 Hz | |

## Cambia una cosa

Prueba `intervaloMs = 1000`. No cambies tipo, pin ni estructura.

## ¿Qué ocurrió?

Construye la regla: al duplicar el intervalo de cada fase, el período se duplica y la frecuencia se reduce a la mitad.

## Desafío

Crea dos variables, `encendidoMs` y `apagadoMs`, para obtener un destello corto cada segundo. Explica por qué ya no tienen que ser iguales.

## Depuración

- `intervaloMS` y `intervaloMs` son nombres distintos.
- Una variable debe declararse antes de usarse.
- Un valor negativo en `delay` no tiene sentido pedagógico; no lo pruebes.
- Si haces dos cambios a la vez, ya no sabes cuál causó el efecto.

## Quiz

1. ¿Qué tres partes tiene `int intervaloMs = 500;`?
2. ¿Qué expresa `const`?
3. ¿Por qué incluir la unidad en el nombre?
4. ¿Qué período produce 250 ms ON + 250 ms OFF?
5. ¿Qué ventaja tiene usar una variable dos veces?

Respuestas: [Solución 07](../../solutions/07-variables-y-tiempo.md).

## Bitácora

Registrar tabla y escribir una frase que distinga variable, valor y tipo.

## Lo que ya sabemos

El programa puede representar información con nombres, no solo ejecutar órdenes fijas.

## Próxima misión

Usaremos palabras y números para que PX-32 nos cuente qué ocurre dentro del programa.

## Fuentes

**CURSO PX-32:** explicación y experimento. La sintaxis corresponde a Arduino/C++ estándar.
