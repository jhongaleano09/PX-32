# HW-005 - Motores DC con reductora

**Estado:** VERIFICADO_PDF, cuatro unidades; relación de reducción y voltaje nominal pendientes.

## ¿Qué son y para qué sirven?

Convierten energía eléctrica en giro. La caja amarilla contiene engranajes que reducen velocidad y aumentan el par disponible en las ruedas.

## ¿Dónde están?

Cuatro motores sujetos al chasis inferior, uno por rueda.

## Fenómeno y funcionamiento

La corriente en bobinas crea campos magnéticos que interactúan con imanes. Un conmutador interno mantiene el giro. La polaridad determina el sentido; la modulación de potencia modifica la velocidad media.

## Partes importantes

Motor metálico, reductora plástica, eje, cables y acople blanco.

## Conexiones

Cada motor llega a uno de BK1, BK3, AK1 o AK3 del Model Y. No se conecta a GPIO.

## Alimentación

Proviene de la etapa de potencia del Model Y. Corriente de arranque y voltaje nominal: `STATUS: PENDIENTE_DE_VERIFICAR`.

## Entrada y salida

Entra energía eléctrica con polaridad y potencia controladas; sale rotación con velocidad y par.

## Experimento mínimo

Con PX-32 apagado, girar suavemente una rueda y observar la resistencia de la reductora. La primera energización será de un motor con ruedas levantadas y supervisión adulta.

## Errores frecuentes

Motor en conector equivocado, eje/acople flojo, cables invertidos respecto al mapa o intentar detenerlo con la mano.

## Preguntas

1. ¿Qué gana y qué pierde una reductora?
2. ¿Por qué invertir polaridad cambia el giro?
3. ¿Por qué el arranque exige más corriente?

## Proyectos

Movimiento, línea, evasión, seguimiento y control remoto.

## Fuente

Manual OSOYOO, pp. 4-8, 13, 19-21.
