# Lección 12 — Del electrón al giro: motor DC

## La rueda no es el motor

Mira una esquina de PX-32. Lo más visible es la rueda azul y negra, pero detrás hay una caja amarilla y, pegado a ella, un cilindro metálico. ¿Cuál de esas tres piezas crea el giro?

El cilindro es el **motor DC**. Las letras DC significan *direct current*, o corriente continua: la corriente conserva un sentido mientras la fuente mantenga la misma polaridad. Dentro del motor hay una parte fija, el **estator**, y una parte que gira, el **rotor**. La corriente que atraviesa las bobinas produce un campo magnético; su interacción con los imanes ejerce una fuerza giratoria llamada **par** o *torque*.

El motor puede girar con rapidez, pero una rueda de robot necesita fuerza para arrancar y vencer el roce. La caja amarilla es la **reductora**: un tren de engranajes disminuye la velocidad de salida y aumenta el par disponible. No crea energía; parte se pierde en rozamiento, sonido y calor.

La cadena mecánica de PX-32 es esta:

```text
rotor del motor -> engranajes de la reductora -> eje blanco -> rueda
```

Cuando más adelante cambies el sentido de la corriente, cambiará el sentido del par y, por tanto, el giro del eje. Hoy no hace falta aplicar energía: primero vas a reconocer la máquina que deseas controlar.

## Prepara una inspección sin desmontar

Necesitas:

- PX-32 ensamblado.
- Una hoja y un lápiz.
- Una linterna pequeña o la del teléfono, sin apoyar el teléfono sobre el robot.
- El [mapa canónico de conexiones](../../docs/reference/mapa-conexiones-robot.md) abierto como consulta.
- Un adulto para confirmar que no hay ninguna fuente conectada.

Debes recordar de la [Lección 03](../00-fundamentos/03-electricidad-sin-misterios.md) que la corriente necesita un circuito cerrado. También usarás la idea de función de la [Lección 11](../01-programacion/11-funciones-ensenar-una-accion-reutilizable.md): cada pieza de esta cadena tiene un trabajo distinto.

🔴 Detente y llama a tu padre. Él retira las dos celdas 18650, desconecta el USB y comprueba que los interruptores estén apagados. No continúes si queda una fuente conectada.

## Sigue el movimiento con los ojos y los dedos

1. 🟢 Coloca el robot sobre la mesa, con la barrera que lleva los dos faros apuntando lejos de ti. Ese será el **frente**. En tu hoja dibuja un rectángulo y marca `frente`, `atrás`, `izquierda` y `derecha`.

2. 🟢 Ilumina la esquina trasera derecha. Reconoce, desde afuera hacia adentro, la rueda Mecanum, el eje/acople blanco, la caja amarilla y el cilindro metálico. No necesitas retirar ninguna pieza.

3. 🟢 Dibuja esas cuatro partes en fila y únelas con flechas. Sobre la caja amarilla escribe `reductora`; sobre el cilindro, `motor DC`. Si solo escribes “motor” sobre todo el conjunto, todavía faltan dos funciones diferentes.

4. 🟢 Haz girar con un dedo uno de los pequeños rodillos negros de la rueda. Debe rotar alrededor de su propio eje sin hacer girar toda la rueda. Esta libertad será importante para el movimiento lateral.

5. 🟡 Con el adulto observando, intenta mover la rueda completa apenas unos grados, muy despacio y desde el borde. La reductora puede ofrecer bastante resistencia. **No la fuerces**: si no cede con una presión suave, detente. La resistencia también es una observación válida.

6. 🟢 Señala la ruta que seguiría la energía, sin afirmar que puedes verla: electricidad en las bobinas, campo magnético, par en el rotor, engranajes, eje y rueda. Después señala la ruta contraria de tu prueba manual. Mover la rueda desde afuera intenta hacer trabajar la reductora “al revés”, por eso puede sentirse difícil.

7. 🟢 Compara visualmente las otras tres esquinas. Debes encontrar cuatro conjuntos equivalentes, uno por rueda. Busca un cable roto, un acople salido o una rueda floja, pero no tires de los cables ni aprietes tornillos.

8. 🟢 Completa esta frase con tus propias palabras: “La rueda toca el suelo, la reductora cambia ___ por ___ y el motor convierte energía eléctrica en ___”. La respuesta debe distinguir movimiento, velocidad y par.

La misión está completa cuando puedes apuntar a motor, reductora, eje y rueda en cualquier esquina y explicar qué transmite cada unión.

> **[PENDIENTE VISUAL]**
> - **Tipo:** corte lateral ilustrado del motor con reductora.
> - **Objetivo:** mostrar cómo un campo magnético termina produciendo el giro lento y con mayor par de la rueda.
> - **Descripción:** vista en capas del cilindro metálico, rotor y estator, piñón pequeño, tren de engranajes dentro de la carcasa amarilla, eje blanco y rueda; dos flechas separan el recorrido de energía del recorrido mecánico.
> - **Elementos que deben señalarse:** bobina, imanes, rotor, estator, par, engranaje conductor, engranajes de reducción, eje y rueda.
> - **Fuente técnica:** Arduino Engineering Kit, sección “3.1 DC Motors”, https://aek.arduino.cc/chapter/concepts; manual OSOYOO, https://osoyoo.com/manual/2021006600-2026.pdf, páginas 4 a 7.
> - **Texto alternativo sugerido:** “Corte de un motor DC unido a una reductora amarilla que transmite el giro a la rueda de PX-32”.

## Si algo no coincide

| Observación | Qué significa | Qué hacer |
|---|---|---|
| Un rodillo pequeño no gira libremente | Puede estar trabado o rozando | No lo fuerces; el adulto inspecciona suciedad o montaje |
| La rueda completa no cede a una presión suave | La reducción puede impedir que se mueva fácilmente desde la salida | Registra “no se dejó mover” y continúa sin forzar |
| El eje blanco gira dentro de la rueda | El acople o la fijación puede estar flojo | No energices el robot; el adulto revisa la unión |
| Falta una pieza o hay un cable pellizcado | La cadena no coincide con el montaje esperado | Compara con las páginas 4 a 7 del manual y detén el bloque activo |
| Aparece calor, olor o una celda instalada | No es una inspección sin energía | Aléjate y deja que el adulto aísle la fuente |

## Una predicción para la próxima clase

La Mega 2560 puede ordenar `HIGH` y `LOW`, pero un motor necesita una ruta de potencia. Dibuja dónde colocarías una pieza intermediaria entre la placa y el motor. En la siguiente lección comprobarás si tu dibujo coincide con el Model Y.

## Lecturas y videos para explorar

- [Conexiones verificadas de Model Y y motores](../../reference/original/osoyoo-mecanum-wheel-robotic-car-kit-v2.pdf) — Inglés; manual del fabricante; 5-10 min. Aprenderás conexiones verificadas de model y y motores. Esencial.
- [Mapa canónico de conexiones](../../docs/reference/mapa-conexiones-robot.md) — Español; referencia interna; 8 min. Aprenderás mapa canónico de conexiones. Opcional.

Vuelve a mirar una esquina del robot después de explorar los recursos: ahora cada carcasa debería representar una función, no solo una forma.

## Referencias técnicas de la clase

- [Conceptos del Arduino Engineering Kit](https://aek.arduino.cc/chapter/concepts), sección 3.1 sobre motores DC, rotor, estator, par, inversión y driver.
- [Manual oficial de OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), páginas 4 a 7 y 19 a 21, montaje de motores y ruedas.
- [Ficha HW-005](../../docs/hardware/HW-005-motores-dc.md), hechos confirmados y especificaciones aún desconocidas de los motores del kit.

## Cuéntale a papá

Señala una esquina real de PX-32 y explícale el viaje desde la bobina hasta el suelo. Luego responde: ¿por qué una reductora que entrega más par no está creando energía? Si la rueda no se dejó mover, cuenta por qué detenerte fue mejor evidencia que forzarla.

La [Lección 13](13-por-que-existe-el-driver-model-y.md) presenta la pieza que recibe una orden pequeña y gobierna la energía de esos cuatro motores.
