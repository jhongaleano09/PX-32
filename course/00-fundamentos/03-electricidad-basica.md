# Lección 03 - Electricidad básica sin riesgos

## Misión

Distinguir voltaje, corriente, resistencia, GND y circuito cerrado antes de conectar energía a PX-32.

## Antes de tocar a PX-32

Lee [¿Qué es la electricidad?](../../docs/readings/que-es-electricidad.md) y [Baterías: energía con reglas](../../docs/readings/baterias.md).

El voltaje es una diferencia entre puntos. La corriente describe flujo de carga por un camino. La resistencia se opone al flujo. Ninguno de estos conceptos es sinónimo de “cantidad de electricidad”.

Un circuito necesita ida y retorno. GND ofrece una referencia común, pero no es un agujero donde desaparecen electrones. VCC suele nombrar una alimentación positiva para un circuito; VIN indica una entrada de alimentación y no debe intercambiarse con 5V.

## La pregunta

¿Puede existir una señal útil entre dos módulos si no comparten una referencia eléctrica?

## Nuestra predicción

Dibuja una batería, un interruptor y una lámpara en un circuito cerrado. Después abre el interruptor y marca dónde esperas que deje de haber corriente.

## Conceptos nuevos

Voltaje, corriente, resistencia, circuito, GND, VCC, VIN, 3.3 V, 5 V y cortocircuito.

## Hardware utilizado

- [HW-014 portabaterías](../../docs/hardware/HW-014-portabaterias.md), sin celdas si el adulto decide mostrarlo.
- [HW-015 baterías](../../docs/hardware/HW-015-baterias-18650.md), solo observación adulta.
- [HW-018 cables](../../docs/hardware/HW-018-cables.md).

## Conexiones

Ninguna conexión real. Todos los circuitos se dibujan en papel.

## Seguridad

**Nivel rojo para baterías; verde para dibujos.** El estudiante no une terminales ni mide corriente. Nunca conectar directamente `+` con `-`, ni 5V con GND.

## Experimento PX-32: circuito de papel

1. Recorta cuatro tarjetas: `FUENTE`, `INTERRUPTOR`, `CARGA`, `RETORNO`.
2. Ordénalas en un ciclo y une con flechas.
3. Retira `RETORNO`: explica por qué el camino ya no está completo.
4. Añade una tarjeta `SEÑAL` entre Mega y Model Y.
5. Dibuja por separado la ruta de potencia batería->Model Y->motor->retorno.
6. Explica por qué señal y potencia cooperan sin ser lo mismo.

## Antes de ejecutar

¿Un motor debería conectarse directamente entre un pin GPIO y GND? Escribe tu respuesta antes de leer el resultado esperado.

## Resultado esperado

No. Un GPIO representa/controla información y admite poca corriente. Un motor exige potencia, tiene picos de arranque y produce interferencia. El Model Y es el intermediario.

## Observaciones

| Ruta | Lleva principalmente | Fuente | Destino |
|---|---|---|---|
| Mega -> Model Y | información | GPIO | entrada driver |
| Baterías -> Model Y -> motor | energía | celdas | motor |

## Cambia una cosa

En el dibujo, cambia una etiqueta 5V por VIN. ¿Sigue siendo inequívoco? Explica por qué nombres parecidos no prueban equivalencia.

## ¿Qué ocurrió?

Escribe dos preguntas que siempre debes responder antes de unir pines: “¿qué voltaje?” y “¿en qué dirección fluye la señal o energía?”.

## Desafío

Explica con tus palabras por qué GND debe ser común entre un sensor y la Mega para que HIGH/LOW tengan una referencia compartida.

## Depuración

Si la analogía del agua causa confusión, abandónala. Usa definiciones: voltaje entre puntos, corriente por una rama, resistencia del camino. Una analogía ayuda; no reemplaza la física.

## Quiz

1. ¿Entre cuántos puntos se define un voltaje?
2. ¿Qué mide la corriente?
3. ¿Por qué un cortocircuito puede calentarse?
4. ¿Es VIN sinónimo universal de 5V?
5. ¿Qué componente entrega potencia a los motores?
6. ¿Quién manipula las 18650?

Respuestas: [Solución 03](../../solutions/03-electricidad-basica.md).

## Bitácora

Guardar ambos diagramas, la predicción sobre GPIO y una regla de seguridad escrita con palabras propias.

## Lo que ya sabemos

PX-32 combina rutas de información y energía dentro de un mismo sistema.

## Próxima misión

Abriremos la caja conceptual del cerebro: procesador, memoria, pines y reloj.

## Fuentes

**OSOYOO:** ruta de potencia pp. 14-15. **CURSO PX-32:** explicación y experimento.
