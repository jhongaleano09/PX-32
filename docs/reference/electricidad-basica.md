# Electricidad básica para PX-32

## Una idea útil: empuje, flujo y oposición

Podemos usar una analogía con agua, sabiendo que no es perfecta:

- **Voltaje** se parece a una diferencia de presión entre dos puntos.
- **Corriente** se parece a cuánto flujo pasa por una sección.
- **Resistencia** se parece a una restricción del camino.

La electricidad real es movimiento y distribución de carga en un circuito. Siempre preguntamos “voltaje entre qué dos puntos” y “corriente por qué camino”.

## El circuito debe cerrarse

Para que exista corriente sostenida hace falta un camino completo. Un interruptor abierto interrumpe el camino; uno cerrado lo permite. Un cortocircuito crea un camino de resistencia muy baja y puede calentar cables, baterías o placas.

## GND no es magia

GND es la referencia común contra la cual medimos voltajes y normalmente el camino de retorno. Dos módulos que intercambian señales necesitan compartir una referencia, salvo que exista aislamiento diseñado.

## 3.3 V, 5 V y VIN no son intercambiables

Un módulo puede alimentarse a 5 V y usar lógica de 3.3 V internamente. `VIN` suele ser una entrada hacia un regulador y no significa “pin de 5 V”. Siempre se sigue el diagrama del componente exacto.

## Entrada, salida y potencia

Un GPIO está pensado para señales y corrientes pequeñas. Un motor pide mucha más corriente, especialmente al arrancar o bloquearse, y además genera ruido eléctrico. Por eso PX-32 usa el Model Y entre Mega y motores.

```text
Mega: decisión pequeña -> Model Y: conmutación de potencia -> motor: movimiento
```

## Digital y analógico

Una entrada digital decide entre dos regiones: LOW y HIGH. Una entrada analógica mide un voltaje dentro de un intervalo y el ADC lo convierte en un número. El tracker del kit llega a pines A0-A4, pero el manual usa sus salidas como estados de canal; estar en un pin `A` no obliga a usar `analogRead()`.

## Regla de oro

Conexiones siempre con USB retirado, baterías fuera o interruptores apagados según indique el adulto. Después se inspecciona polaridad, alineación y cables sueltos; solo entonces se energiza.

## Lectura relacionada

[Lección 03](../../course/00-fundamentos/03-electricidad-sin-misterios.md) y [alimentación de PX-32](alimentacion.md).
