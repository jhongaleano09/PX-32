# Lección 01 - Conocer nuestro laboratorio

## Misión

Explicar qué hace que PX-32 sea un robot y organizar un espacio de trabajo seguro.

## Antes de tocar a PX-32

Una máquina puede hacer algo útil sin ser un robot: una cuchara transmite fuerza, un reloj mide tiempo y una lámpara produce luz. En este curso llamaremos robot a un sistema que puede:

1. **percibir** algo del mundo;
2. **procesar** información siguiendo un programa;
3. **actuar** sobre el mundo.

PX-32 tiene sensores infrarrojos y ultrasónico para percibir, una Mega2560 para procesar y motores/servo/LEDs para actuar.

```text
ENTRADA -> PROCESAMIENTO -> SALIDA
sensor     Mega + programa  motor, servo o luz
```

Un robot no “entiende” como una persona por tener sensores. Cada sensor produce una señal limitada. El programa debe convertir esa señal en una decisión.

## La pregunta

¿Qué piezas permiten que PX-32 perciba, piense de forma programada y actúe?

## Nuestra predicción

Antes de abrir o mover nada, escribe tres piezas que esperas encontrar y clasifica cada una como sensor, procesamiento o actuador.

## Conceptos nuevos

Robot, sensor, actuador, entrada, procesamiento, salida y sistema.

## Hardware utilizado

PX-32 completo, apagado, más la [vista general del inventario](../../docs/hardware/README.md).

## Conexiones

No se modifica ninguna. Esta lección es de observación.

## Seguridad

**Nivel verde con supervisión cercana.** PX-32 debe estar apagado, sin USB y sin retirar ni insertar baterías. El adulto confirma el estado antes de empezar.

Preparen una mesa seca, iluminada y sin objetos metálicos sueltos. Recipiente pequeño para tornillos, cuaderno y lápiz. Nada de bebidas cerca.

## Experimento PX-32: mapa de funciones

1. Sin desmontar, observen PX-32 desde arriba, frente, lados y abajo.
2. Localicen algo que parezca “recibir” información del mundo.
3. Localicen algo que produzca movimiento.
4. Localicen la placa que ejecuta el programa.
5. Dibujen tres columnas: `PERCIBE`, `PROCESA`, `ACTÚA`.
6. Coloquen o escriban al menos dos piezas en cada columna. Una pieza puede quedar en `NO SÉ TODAVÍA`.
7. Tracen con flechas un ejemplo: obstáculo -> ultrasónico -> Mega -> Model Y -> motor.

## Antes de ejecutar

¿Cuál pieza crees que será más fácil de identificar? ¿Cuál podría parecer un sensor sin serlo?

## Resultado esperado

No existe una clasificación perfecta a primera vista. Deben aparecer, como mínimo:

- sensores: tracker, dos IR y ultrasónico;
- procesamiento/comunicación: Mega, shield, ESP y HC-02;
- actuadores: motores, servo, LEDs;
- energía/estructura: baterías, portabaterías, Model Y, chasis y cables.

El Model Y no “piensa”; ejecuta eléctricamente las órdenes de la Mega y entrega potencia.

## Observaciones

| Pieza | Nuestra clasificación | Evidencia visual | ¿Duda? |
|---|---|---|---|
| | | | |

## Cambia una cosa

Miren PX-32 desde abajo. ¿Cambia la clasificación de alguna pieza o solo mejora la evidencia?

## ¿Qué ocurrió?

Escriban una diferencia entre “lo que una pieza parece” y “lo que sabemos que hace”.

## Desafío

Explica PX-32 en una sola cadena de seis cajas, desde una mano colocada al frente hasta una rueda que gira.

## Depuración

Si no identifican una pieza, no adivinen ni la retiren. Comparen forma y posición con el [diccionario de hardware](../../docs/hardware/README.md). Marquen `PENDIENTE_DE_VERIFICAR`.

## Quiz

1. ¿Qué tres funciones mínimas usamos para describir un robot?
2. ¿Un sensor actúa directamente sobre el mundo o produce información?
3. ¿Por qué el Model Y no es el cerebro?
4. Clasifica: servo, tracker, Mega2560 y rueda.
5. ¿Qué debe hacerse antes de tocar conexiones?

Respuestas: [Solución 01](../../solutions/01-conocer-nuestro-laboratorio.md).

## Bitácora

Registrar pregunta, predicción, diagrama entrada-proceso-salida y una pieza que todavía genere duda.

## Lo que ya sabemos

Ya podemos mirar PX-32 como un sistema, no como una colección de piezas.

## Próxima misión

Convertiremos la observación en un inventario verificable, como haría un laboratorio real.

## Fuentes

**OSOYOO:** introducción y fotografías, manual pp. 1-4. **CURSO PX-32:** clasificación y experimento.
