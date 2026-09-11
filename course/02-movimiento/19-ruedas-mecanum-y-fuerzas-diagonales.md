# Lección 19 — Ruedas Mecanum y fuerzas diagonales

## Una rueda que no empuja solo hacia adelante

Una rueda común rueda en la dirección en que apunta. Una rueda Mecanum añade pequeños rodillos inclinados alrededor de su borde. Cada rodillo puede girar libremente, de modo que la fuerza en el contacto con el piso se orienta en diagonal.

Una sola rueda produciría componentes en dos direcciones: una **longitudinal**, hacia el frente o atrás del chasis, y otra **lateral**, hacia un costado. Una componente es la parte de una fuerza que analizamos sobre un eje elegido. En el robot completo, algunas componentes se suman y otras se cancelan.

La orientación importa tanto como el giro. OSOYOO especifica dos tipos de rueda: vistas desde arriba, las cuatro deben formar un patrón en X. En el diagrama del manual, las posiciones son:

```text
           FRENTE
       1           2

       3           4
            ATRÁS
```

La posición 1 es frontal izquierda; 2, frontal derecha; 3, trasera izquierda; 4, trasera derecha. Las ruedas 1 y 4 comparten una inclinación, y 2 y 3 la inclinación opuesta.

## Prepara un laboratorio de flechas

- PX-32 totalmente apagado, sin USB y sin celdas.
- Manual OSOYOO abierto en la página 21.
- Hoja, lápiz, regla y dos colores.
- Cuatro flechas de papel que puedas girar sobre la mesa.
- Una linterna para ver la inclinación de los rodillos.
- Un adulto para confirmar el estado seguro; no hace falta computador ni código.

Debes conservar el mapa de posiciones de la [Lección 18](18-cuatro-motores-cuatro-identidades.md). Aquí los números del dibujo de OSOYOO y los conectores se relacionan así:

| Posición OSOYOO | Esquina | Conector |
|---:|---|---|
| 1 | frontal izquierda | BK3 |
| 2 | frontal derecha | BK1 |
| 3 | trasera izquierda | AK3 |
| 4 | trasera derecha | AK1 |

🔴 El adulto retira fuentes y comprueba que no haya una carga activa de los sketches anteriores. Esta actividad no necesita energizar ni hacer girar motores.

## Comprueba la X antes de dibujar fuerzas

1. 🟢 Colócate detrás de PX-32 y marca el frente en tu hoja. Copia las cuatro posiciones sin girar el robot durante la actividad.

2. 🟢 Mira la banda central de los rodillos en la rueda 1. Traza en tu dibujo una línea con la misma inclinación. Repite con las ruedas 2, 3 y 4.

3. 🟢 Compara tu dibujo con la fotografía y el esquema de la página 21. Las inclinaciones opuestas deben formar una X imaginaria hacia el centro. No basta con que las cuatro ruedas “se vean parecidas”.

4. 🟢 Haz girar suavemente **un rodillo pequeño**, no la rueda completa, para comprobar que su eje está inclinado y que puede rodar. Si está trabado, no lo fuerces.

> **[PENDIENTE VISUAL]**
> - **Tipo:** fotografía cenital anotada y ampliaciones de rodillo.
> - **Objetivo:** comprobar el patrón X y distinguir giro de rueda, giro de rodillo y dirección de fuerza.
> - **Descripción:** vista superior de PX-32 con posiciones 1 a 4; ampliación de una rueda de cada orientación, línea sobre el eje del rodillo y flechas descompuestas en componente longitudinal y lateral.
> - **Elementos que deben señalarse:** frente, posiciones 1-4, BK3/BK1/AK3/AK1, patrón X, eje de rodillo, fuerza diagonal y sus dos componentes.
> - **Fuente técnica:** manual OSOYOO, https://osoyoo.com/manual/2021006600-2026.pdf, página 21.
> - **Texto alternativo sugerido:** “Cuatro ruedas Mecanum vistas desde arriba forman una X y una fuerza diagonal se separa en componentes frontal y lateral”.

## Suma fuerzas sin mover el robot

5. 🟢 En el esquema de OSOYOO identifica las flechas diagonales de las cuatro ruedas para avance. Cópialas con el primer color. No deduzcas su punta solo por la inclinación del rodillo: también depende del sentido de giro.

6. 🟢 Con el segundo color separa cada flecha diagonal en una parte hacia adelante y otra hacia un lado. Esto es una **descomposición**: dos flechas perpendiculares representan juntas el mismo efecto diagonal.

7. 🟢 Junta tus cuatro flechas de papel como si todos los motores avanzaran. Las componentes laterales de izquierda y derecha apuntan en sentidos opuestos y se cancelan aproximadamente; las cuatro longitudinales apuntan hacia adelante y se suman.

8. 🟢 Representa ahora un desplazamiento a la derecha siguiendo la tabla de la página 21: ruedas 1 y 4 hacia adelante; 2 y 3 hacia atrás. Las componentes longitudinales se oponen y las laterales se suman hacia la derecha.

9. 🟢 Explica por qué “rueda hacia adelante” y “robot hacia adelante” no son sinónimos. En un desplazamiento lateral, dos ruedas reciben avance y dos retroceso, pero el chasis completo no debe rotar ni avanzar de forma dominante.

10. 🟢 La misión termina cuando puedes reconstruir con flechas un avance y un lateral, y cuando la orientación física de las cuatro ruedas coincide con el patrón X. Si no coincide, la siguiente lección activa queda suspendida.

## Lo que puede engañar a tus ojos

- **Mirar desde el frente:** invierte tu percepción de derecha e izquierda. Vuelve detrás del robot.
- **Seguir el dibujo de la banda de goma:** observa el eje del rodillo completo, no una mancha o reflejo.
- **Confundir rodillo con rueda:** el rodillo gira sobre un eje diagonal; la rueda completa gira sobre el eje del motor.
- **Asignar una fuerza solo por inclinación:** el sentido de giro también determina hacia dónde apunta.
- **Esperar cancelación perfecta:** diferencias entre motores, peso, fricción y piso pueden dejar una desviación real.

Esta lección no necesita un `.ino`. Cargar un programa que solo imprimiera una frase no ayudaría a comprender la geometría; el experimento central está en el robot apagado y en las flechas.

## Lecturas y videos para explorar

- [Conexiones verificadas de Model Y y motores](../../reference/original/osoyoo-mecanum-wheel-robotic-car-kit-v2.pdf) — Inglés; manual del fabricante; 5-10 min. Aprenderás conexiones verificadas de model y y motores. Esencial.
- [Mapa canónico de conexiones](../../docs/reference/mapa-conexiones-robot.md) — Español; referencia interna; 8 min. Aprenderás mapa canónico de conexiones. Opcional.

Vuelve especialmente a la página 21: separa lo que muestra la fotografía sobre montaje de lo que explica el esquema sobre fuerzas.

## Referencias técnicas de la clase

- [Manual oficial de OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), páginas 19 a 21, tipos de rueda, patrón X y tabla de actuación.
- [Ficha HW-006](../../docs/hardware/HW-006-ruedas-mecanum.md), orientación confirmada de las ruedas del kit.
- [Manual limpio del proyecto](../../reference/osoyoo-manual.md#ruedas-mecanum-pp-19-22), síntesis verificable y recorte visual seleccionado.

## Cuéntale a papá

Con cuatro flechas de papel, demuestra primero avance y luego desplazamiento lateral. Dile cuáles componentes se suman y cuáles se cancelan, y señala una causa real por la que la cancelación podría no ser perfecta.

En la [Lección 20](20-vectores-para-mover-px-32.md) esos patrones de flechas se convertirán en funciones que coordinan los cuatro motores y vuelven siempre a STOP.
