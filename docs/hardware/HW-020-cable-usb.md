# HW-020 - Cable USB de programación

**Estado:** el uso está VERIFICADO_PDF; que el cable venga incluido y que transporte datos debe verificarse físicamente.

## ¿Qué es y para qué sirve?

Une la Mega2560 al computador para alimentar la placa durante prácticas iniciales, cargar programas e intercambiar mensajes Serial.

## ¿Dónde está?

Es externo; se conecta al puerto USB tipo B de la Mega2560 y al MacBook o equipo Ubuntu, quizá mediante adaptador.

## Fenómeno y funcionamiento

Pares de conductores llevan alimentación y datos diferenciales. Un cable puede cargar y no incluir datos; por eso “enciende” no demuestra que sirva para programar.

## Conexiones

USB del computador -> cable -> USB de HW-001. En las primeras lecciones, batería y motores permanecen apagados.

## Entrada y salida

Lleva energía de 5 V desde el computador y datos en ambos sentidos mediante la interfaz USB-serial de la placa.

## Experimento mínimo

Conectar solo HW-001, observar si aparece un puerto nuevo al conectar y desaparece al desconectar.

## Errores frecuentes

Cable solo de carga, adaptador defectuoso, conector flojo o elegir un puerto antiguo en el IDE.

## Preguntas

1. ¿Por qué encender no prueba que existan datos?
2. ¿Qué puerto aparece y desaparece?
3. ¿Qué parte permanece en la placa al retirar USB?

## Proyectos

Todos los programas, depuración y monitor Serial.

## Fuente

Manual OSOYOO, pp. 22-24 y procedimientos de carga de las demás lecciones.
