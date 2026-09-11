# ¿Qué es la electricidad?

La materia contiene partículas con carga eléctrica. Cuando existe una diferencia de energía eléctrica entre dos puntos y un camino conductor completo, las cargas del material responden y aparece corriente.

## Tres ideas distintas

**Voltaje** compara dos puntos. Es una diferencia de potencial, como una diferencia de altura que puede impulsar algo cuesta abajo.

**Corriente** expresa cuánto flujo de carga atraviesa una sección por unidad de tiempo.

**Resistencia** describe cuánto se opone un camino a ese flujo. Un conductor real no es un tubo vacío: sus átomos interactúan con las cargas y parte de la energía puede transformarse en calor.

## Energía e información

En PX-32 la electricidad cumple dos trabajos:

- transportar energía para LEDs, servo y motores;
- representar información como HIGH/LOW, pulsos o caracteres UART.

Una señal que representa “avanza” no tiene potencia suficiente para mover el robot. El Model Y usa esa información para controlar una fuente de energía mayor.

## Un circuito es una ruta

Si la ruta está abierta, no hay corriente sostenida. Si se unen directamente dos puntos que no deben unirse, aparece un cortocircuito: la resistencia puede ser tan baja que la corriente produzca calor y daño.

## Pregunta para la bitácora

¿Qué partes de PX-32 llevan principalmente información y cuáles llevan principalmente energía?
