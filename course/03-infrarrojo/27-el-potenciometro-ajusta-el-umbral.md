# Lección 27 — El potenciómetro ajusta el umbral

## El tornillo que mueve la meta

En la Lección 26 mediste que tus dos sensores encienden a distancias distintas: cada uno salió de fábrica con su propio umbral. Para que PX-32 siga una mano con los dos sensores trabajando en equipo, ambos necesitan "coincidir" más o menos. Hoy los pones de acuerdo.

El protagonista es el cuadrito azul con tornillo que identificaste en la Lección 24: el **potenciómetro**. Por dentro es una resistencia ajustable: una pista de material resistivo y un **cursor** que se desliza por ella al girar el tornillo. Según dónde quede el cursor, el módulo entrega un voltaje distinto hacia la entrada de umbral del LM393. Girar el tornillo no cambia la luz ni el receptor: cambia la línea que el árbitro usa para decidir. Es la barra del salto alto: el atleta (la señal del receptor) salta igual, pero si subes o bajas la barra, el resultado cambia.

Ajustar esa barra con un objetivo concreto se llama **calibrar**: comparar la respuesta del instrumento con una situación conocida y corregirla. Es una de las ideas más útiles de toda la ciencia y la vas a usar muchas veces en este curso. Hoy el objetivo viene del manual de OSOYOO: detectar una mano o un cartón a unos **10 cm**, que es la distancia de trabajo del seguimiento de objetos.

Dos advertencias serias antes de tocar el tornillo. Primera: es pequeño y delicado; se gira con la yema del dedo en pasos chiquitos —menos de un octavo de vuelta por intento— y nunca se fuerza hasta el tope, porque un potenciómetro forzado en su extremo puede dejar de ajustar bien. Segunda: cada giro mueve bastante la frontera; si das vueltas enteras, te pasas de largo y te pierdes. Pasitos y observar.

## Lo que necesitas

- PX-32 con sus dos sensores montados y conectados.
- El cartón blanco y la regla.
- Un marcador fino de punta (o esmalte de uñas, o una etiqueta pequeñita pegada).
- Tu cuaderno con los números de la Lección 26.
- Cable USB, computador y un adulto presente.

Estado inicial: robot apagado y sin baterías. Ningún movimiento en esta clase: solo se ajustan sensores.

🟡 El adulto conecta el USB al empezar y lo retira al final. Si el tornillo opusiera resistencia o no girara, se detiene el ajuste y el adulto lo revisa: no se fuerza.

## Calibra ambos sensores a 10 centímetros

1. 🟢 **Marca la posición inicial.** Sin girar nada, haz un punto con el marcador sobre el tornillo y otro sobre la plaquita alineado con el primero, en cada sensor. Esa pareja de puntos es tu foto de "cómo venía de fábrica": si algún día quieres volver, los alineas de nuevo. Regla del cuaderno: toda posición de partida se marca antes de ajustar.

2. 🟢 **Parte de tu evidencia.** Copia de la Lección 26 la distancia de encendido actual de cada sensor. Son tus "antes" para comparar el "después".

3. 🟡 **Energiza.** El adulto conecta el USB. Comprueba el LED de alimentación en ambos módulos.

4. 🟢 **Sensor izquierdo: apunta a la meta.** Sostén el cartón blanco plano a 10 cm exactos, medidos con la regla frente a las cápsulas. Si el LED de señal no se enciende, gira el tornillo un pasito (menos de un octavo de vuelta) en un sentido y observa el LED. Si tampoco, otro pasito del mismo lado. Detente apenas encienda a los 10 cm. Si en cambio encendía desde el principio, salta al paso 5.

5. 🟢 **Verifica que no se pase.** Aleja el cartón a 15 cm: el LED debe apagarse. Si sigue encendido, el umbral quedó demasiado sensible: gira pasitos en sentido contrario hasta que a 10 cm encienda y a 15 cm no. La calibración es una ventana, no solo una frontera: importa que se abra y que se cierre donde corresponde.

6. 🟢 **Sensor derecho: repite todo.** Mismos pasos, mismo cartón, misma regla de 10 y 15 cm. Al terminar, los dos módulos deberían comportarse casi igual frente al mismo blanco.

7. 🟢 **Prueba de sensibilidad.** Con el cartón, y ya lograda la ventana de 10/15, gira el tornillo izquierdo un solo pasito extra y mide de nuevo la distancia de encendido. Anota cuánto se movió la frontera con ese pasito. Esa es la **sensibilidad** del ajuste: si un pasito mueve la frontera muchos centímetros, ya sabes que los ajustes se hacen con paciencia de relojero. Vuelve a dejarlo en 10 cm.

8. 🟢 **Prueba final con mano.** Repite la ventana con tu propia mano abierta en vez del cartón: a 10 cm enciende, a 15 cm no. La mano refleja algo distinto que el cartón; si con la mano la ventana no cierra exactamente igual, anótalo: para el hito de la Lección 30 usaremos la mano, y saber esto evita sorpresas.

9. 🟢 **Registra la calibración.** Escribe en el cuaderno: "Ambos sensores calibrados a 10 cm, encienden ≤10 y liberan ≥15, luz de la sala (encendida/apagada), fecha ___". La calibración sin condiciones anotadas es media calibración. Los puntos del marcador ya no coincidirán con la posición final: está bien; sirven para volver atrás si algo sale mal, y la nueva calibración es la que manda.

10. 🟡 **Cierre.** El adulto retira el USB.

La calibración está lograda cuando ambos sensores pasan la prueba de la ventana (encienden a 10, liberan a 15) al menos dos veces seguidas, y tu cuaderno tiene el registro con condiciones y fecha.

> **[PENDIENTE VISUAL]**
> - **Tipo:** fotografía macro con anotaciones del potenciómetro.
> - **Objetivo:** mostrar cómo marcar la posición inicial y en qué sentido girar con pasos pequeños.
> - **Descripción:** primer plano del cuadrito azul del módulo con el tornillo visible; un punto de marcador sobre el tornillo y una flecha de referencia sobre la plaquita; junto a la foto, un diagrama circular indicando "pasito" como un arco de menos de 45 grados.
> - **Elementos que deben señalarse:** tornillo de ajuste, punto de marcador, flecha de referencia, arco del "pasito", rótulo de 10 cm con regla y cartón.
> - **Fuente técnica:** manual OSOYOO, https://osoyoo.com/manual/2021006600-2026.pdf, página 42, ajuste del potenciómetro con objeto a unos 10 cm.
> - **Texto alternativo sugerido:** "Primer plano del potenciómetro del sensor con la marca de posición inicial y la indicación de giro en pasos pequeños".

## Desafío: la ventana a tu medida

Vuelve a la posición marcada y calibra el sensor izquierdo para una ventana distinta: que encienda a 20 cm y libere a 25. Después regrésalo a 10/15. Con dos calibraciones en el cuaderno, responde: ¿para qué serviría en un robot una ventana corta y para qué una larga?

## Si algo no cuadra

| Síntoma | Qué revisar | Acción |
|---|---|---|
| Giro y no pasa nada | ¿Estás girando el tornillo del mismo módulo que observas? | Sigue el cable y confirma cuál sensor miras; prueba el otro sentido de giro |
| Ahora detecta a medio metro | ¿Te pasaste de vueltas en un solo sentido? | Regresa pasito a pasito; el objetivo es la ventana 10/15, no "detectar lo máximo" |
| Enciende a 10 pero no libera a 15 | ¿Hay una pared o tu cuerpo de fondo? | Despeja el frente del sensor y repite; el fondo también refleja |
| El LED de señal enciende con la sala en pleno sol | ¿El ruido ambiente es fuerte? | Repite la calibración con la luz que planeas usar en el hito y anótalo como condición |
| El tornillo no gira más | ¿Llegó a su tope mecánico? | No lo fuerces: retrocede pasitos; si quedó inservible, el adulto revisa el módulo |

## Lecturas y videos para explorar

- [El espectro electromagnético y el infrarrojo](https://science.nasa.gov/ems/07_infraredwaves/) — Inglés; lectura NASA; 8 min. Aprenderás el espectro electromagnético y el infrarrojo. Esencial.
- [Sensores de PX-32](../../docs/reference/sensores.md) — Español; referencia interna; 6 min. Aprenderás sensores de px-32. Opcional.

La sección de calibración de la referencia interna resume tu método de hoy: condiciones anotadas, repeticiones y una variable a la vez.

## Referencias técnicas de la clase

- [Manual oficial de OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), página 42, procedimiento de ajuste del potenciómetro con objeto a unos 10 cm.
- [Hoja de datos LM393 de Texas Instruments](https://www.ti.com/lit/ds/symlink/lm193.pdf), entradas de referencia del comparador.
- [Ficha HW-008 del repositorio](../../docs/hardware/HW-008-ir-obstaculos.md), errores frecuentes de calibración.

## Cuéntale a papá

Explícale qué es calibrar usando la analogía de la barra del salto alto, y muéstrale las marcas del marcador que permiten volver a la posición de fábrica. Cuéntale qué ventana elegiste (10 y 15 cm) y por qué el robot del hito necesita que ambos sensores coincidan. Pregúntale qué instrumentos de la casa se calibran (pistas: la báscula del baño, la balanza de cocina, el termostato).

El sensor ya decide a la distancia correcta… pero la Mega todavía no sabe nada de eso. El veredicto viaja por el cable OUT hasta el pin D3. En la [Lección 28](28-leer-un-sensor-ir-por-un-pin-digital.md) escribes tu primer programa que escucha un pin.
