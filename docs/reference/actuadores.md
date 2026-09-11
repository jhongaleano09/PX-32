# Actuadores de PX-32

Un actuador transforma una orden y energía en un cambio físico.

| Actuador | Orden | Energía/potencia | Resultado |
|---|---|---|---|
| Motor DC x4 | Dirección + habilitación/PWM | Model Y y baterías | Giro continuo |
| Servo MG90 | Pulsos de posición en D13/S1 | 5 V desde Model Y | Ángulo objetivo |
| LED delantero x2 | En el manual, conexión directa a VCC/GND | 3.3 V o 5 V del shield | Luz visible |
| LED integrado | `digitalWrite(LED_BUILTIN, ...)` | Placa Mega | Luz de diagnóstico |

## Motor DC frente a servo

Un motor DC recibe polaridad y potencia; por sí solo no sabe su posición. El servo integra motor, engranajes, sensor y controlador, de modo que intenta alcanzar un ángulo. En ambos casos un atasco puede elevar corriente.

## Por qué existe el driver

El microcontrolador representa decisiones con señales pequeñas. El driver conmuta la corriente de los motores y protege la separación funcional entre lógica y potencia. Esto no vuelve indestructible al sistema: un motor bloqueado, polaridad incorrecta o alimentación fuera de rango sigue siendo peligroso.

## Prueba escalonada

1. Imprimir la orden sin actuar.
2. Verificar pinout con energía retirada.
3. Probar un actuador a baja exigencia.
4. Usar ruedas levantadas cuando hay motores.
5. Añadir un segundo actuador.
6. Probar el conjunto en el suelo despejado.

## Fuente y alcance

Conexiones: manual OSOYOO, pp. 13, 16-17 y 19-24. Estrategia de prueba: curso PX-32.
