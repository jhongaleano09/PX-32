# HW-010 - Microservo OSOYOO MG90

**Estado:** VERIFICADO_PDF como MG90 en inventario y tablas de pp. 26 y 29. El texto menciona tornillos de un kit SG90; eso no cambia el modelo inventariado.

## ¿Qué es y para qué sirve?

Es un actuador que busca una posición angular ordenada. En PX-32 gira el sensor ultrasónico para mirar a varios lados.

## ¿Dónde está?

En el frente del chasis superior, bajo el soporte ultrasónico.

## Fenómeno y funcionamiento

Un motor pequeño mueve engranajes; un sensor interno compara el ángulo real con el solicitado y un controlador corrige el error. La orden llega como pulsos repetidos cuyo ancho representa la posición.

## Componentes importantes

Motor, reductora, eje, electrónica de control, sensor de posición y cable de tres conductores.

## Pines

| Cable servo | Model Y | Ruta |
|---|---|---|
| Naranja, señal | S1 | D13 desde shield |
| Rojo, VCC | 5V | Alimentación |
| Marrón, GND | GND | Referencia |

## Alimentación

Usar la conexión del Model Y indicada por OSOYOO. Un servo puede pedir picos de corriente; no alimentarlo desde un GPIO.

## Experimento mínimo

Con ruedas levantadas y motores detenidos, ordenar 90° primero; luego 45° y 135°. Observar sin forzar el brazo contra topes.

## Errores frecuentes

Conector invertido, usar el color como única evidencia si el cable difiere, montar el sensor descentrado, bloquear el eje o usar D13 simultáneamente para Blink mientras el servo está activo.

## Preguntas

1. ¿Cómo sabe un servo cuándo detenerse?
2. ¿Por qué una orden de posición no es igual a encender un motor DC?
3. ¿Para qué sirve mirar a izquierda y derecha?

## Proyectos

Radar ultrasónico, evasión y cartografía simple.

## Fuente

Manual OSOYOO, pp. 16-17, 26-29, 31-33.
