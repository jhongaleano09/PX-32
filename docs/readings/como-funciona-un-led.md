# ¿Cómo funciona un LED?

LED significa diodo emisor de luz. Un diodo permite corriente principalmente en una dirección. En un material semiconductor especial, parte de la energía eléctrica se libera como fotones: partículas de luz.

## Polaridad

Un LED tiene ánodo y cátodo. Si se invierte, normalmente no enciende; si se supera su voltaje inverso o corriente permitida, puede dañarse.

## Por qué hace falta limitar corriente

Una vez que conduce, un LED puede dejar pasar demasiada corriente si no existe resistencia o controlador. El LED integrado de la Mega ya forma parte de un circuito diseñado. Los faros del kit parecen ser módulos/cableados preparados, pero su resistencia interna no está documentada: no deben usarse como si fueran LEDs sueltos.

## Blink no “envía luz” desde el código

`digitalWrite(HIGH)` cambia el estado de un pin. La corriente atraviesa el circuito del LED y el semiconductor produce luz. El código representa la decisión; la física produce el resultado.

## Frecuencia visible

A 1 Hz distinguimos cada encendido. A frecuencias altas, nuestra visión integra destellos y puede parecer luz continua. Esto permite preguntar: ¿el LED está realmente siempre encendido o parpadea demasiado rápido para verlo?
