# Lección 32 — IR1 a IR5: un mapa espacial

## El manual se contradice a sí mismo

Hoy te toca ser detective de documentación. Ábrelo con cuidado, porque el caso es real.

Para que la Mega pueda escuchar a los cinco canales del tracker, cada uno necesita llegar a un pin propio. La lista oficial está en el manual de OSOYOO, y el curso la verificó contra los diagramas. Resultado: **el texto del manual está mal y el diagrama está bien**.

En la página 17, la lista de texto dice que los cinco canales se conectan a `A4, A3, A2, A3, A1`. Léela dos veces: hay un `A3` repetido y el `A0` no aparece. En la página 34, la lista del proyecto de seguimiento de línea dice `A4, A3, A2, A2, A1`: ahora el repetido es `A2`. Las dos listas de texto se contradicen entre sí, y además serían un desastre técnico: con `A3` repetido, dos canales distintos terminarían en el mismo pin y la Mega jamás podría distinguirlos.

El diagrama de la página 18 no comete ese error. Ahí cada cable sale del tracker y llega a un pin distinto: **IR1 a A4, IR2 a A3, IR3 a A2, IR4 a A1, IR5 a A0**, más la alimentación VCC a 5V y GND a GND. Los diagramas de las páginas siguientes coinciden con él. Esa es la tabla que este curso adoptó como **mapa canónico**, y la discrepancia quedó registrada formalmente como errata E-001 para que nadie la corrija en silencio.

¿Por qué dedicarle una clase entera a un error ajeno? Porque te acaba de suceder algo que le pasa a todos los ingenieros: dos fuentes dicen cosas distintas, y tocaría decidir. La regla que usamos es simple: **gana la fuente que se puede verificar por más caminos**. El diagrama coincide consigo mismo en dos páginas y es eléctricamente posible; el texto se contradice y es imposible. Cuando dos fuentes se pelean, no eliges la más bonita: eliges la que sobrevive a las preguntas.

## Un mapa, dos formas de nombrar

Fíjate en una propiedad curiosa de la tabla canónica. Los canales están ordenados en fila — IR1, IR2, IR3, IR4, IR5 — y sus pines también bajan en orden — A4, A3, A2, A1, A0. El mapa no es una ensalada: es una escalera. Si sabes dónde está un canal, sabes qué pin usa, sin memorizar nada.

| Canal | Orden en la fila | Pin en la Mega/shield |
|---|---|---|
| IR1 | extremo 1 | A4 |
| IR2 | interior 1 | A3 |
| IR3 | centro | A2 |
| IR4 | interior 2 | A1 |
| IR5 | extremo 2 | A0 |
| VCC | alimentación | 5V |
| GND | referencia | GND |

Dos detalles finos antes de tocar el robot:

- Los pines A0 a A4 son de la fila "analógica" de la Mega, pero recuerda de la Lección 28 que el tracker no entrega una medida suave: cada canal tiene su comparador que ya decidió negro-o-no-negro, y entrega un nivel digital `HIGH` o `LOW`. La Mega puede leer esos niveles digitales también en los pines analógicos: A0–A4 funcionan como entradas digitales perfectamente normales cuando se los usa así. La fila "analógica" es una fila de pines con doble talento.
- El orden de la fila física IR1→IR5 sí está garantizado por el diagrama y la serigrafía de la placa. Lo que **sigue sin estar verificado** es qué extremo de esa fila queda hacia la izquierda del robot montado. Por eso la tabla habla de "extremo 1" y "extremo 2", no de izquierda y derecha. La respuesta llegará con evidencia en la Lección 34.

## Lo que necesitas

- PX-32 ensamblado, **apagado, sin baterías y sin USB**. Sigue siendo observación sin energía.
- Tu cuaderno con el dibujo del frente de la Lección 31 y la marca de cinta en IR1.
- El [diagrama de la página 18 del manual](../../assets/osoyoo-manual/pagina-18-pinout-tracker-correcto.png), en pantalla o impreso.
- Buena luz y, si tienen, una linterna.

🟢 Puedes hacer toda la verificación tú. Solo si un conector está mal conectado o un cable suelto exige intervenir: 🔴 detente y llama a tu padre.

## Verifica el mapa cable por cable

1. 🟢 **Abre el diagrama** de la página 18 y tenlo al lado. Identifica los dos extremos: a la izquierda el tracker con sus siete pines etiquetados; a la derecha, la tira de pines del shield. Cada línea del dibujo es un cable real de tu robot.

2. 🟢 **Localiza el conector en el tracker.** Con PX-32 apagado, mira el extremo de la placa del tracker donde llega el cable de siete vías. Son siete pines en fila: dos de alimentación (GND y VCC) y cinco de señal (IR1 a IR5). La serigrafía de la placa —letras pequeñas impresas junto a cada pin— te dice cuál es cuál: léela con calma y emparéjala pin por pin con las etiquetas del diagrama, sin asumir que tu placa los ordena igual de izquierda a derecha que el dibujo.

3. 🟢 **Confirma la orientación del conector.** Un conector hembra de siete pines puede, en teoría, insertarse en cualquier orientación si se fuerza. Mira el conector del tracker y el del shield: ambos deben estar totalmente insertados y sin pines asomando. El manual conecta GND del tracker a GND del shield y VCC a 5V; si el conector estuviera volteado, la alimentación llegaría cruzada y el tracker no funcionaría. Hoy solo verificas que está bien sentado y alineado.

4. 🟢 **Sigue cada línea con el dedo**, primero en el diagrama y luego en el aire sobre el robot: IR1 viaja hasta la posición A4 del shield, IR2 hasta A3, IR3 hasta A2, IR4 hasta A1, IR5 hasta A0. No tires del cable para seguirlo: los cables se siguen con la mirada y se tocan con suavidad.

5. 🟢 **Completa tu mapa del cuaderno.** Debajo del dibujo de la Lección 31, agrega a cada canal su pin: `IR1 → A4`, `IR2 → A3`, `IR3 → A2`, `IR4 → A1`, `IR5 → A0`. Escribe también la fecha y la fuente: "verificado contra el diagrama de la p. 18". Tu cuaderno se está convirtiendo en tu propio manual, con la diferencia de que el tuyo ya pasó la prueba del detective.

6. 🟢 **La prueba del error.** Para cerrar, explica en voz alta con tus palabras qué estaba mal en la lista de texto del manual y por qué el diagrama gana la discusión. Si puedes explicárselo a tu padre esta noche, el concepto es tuyo.

> **[PENDIENTE VISUAL]**
> - **Tipo:** diagrama de conexión anotado del cable de siete pines.
> - **Objetivo:** mostrar la correspondencia tracker→shield con la errata del texto señalada para que el niño distinga fuente confiable de fuente defectuosa.
> - **Descripción:** reproducción limpia del conector de 7 vías del tracker y la tira de pines del shield unidos por siete líneas de colores; sobre la tabla resultante, una nota roja que muestre la lista errónea del texto (A4,A3,A2,A3,A1) tachada junto a la correcta del diagrama.
> - **Elementos que deben señalarse:** pines GND, VCC, IR1–IR5; pines A4–A0 del shield; tachado de la lista errónea.
> - **Fuente técnica:** manual OSOYOO, https://osoyoo.com/manual/2021006600-2026.pdf, páginas 17–18 y errata E-001 del repositorio.
> - **Texto alternativo sugerido:** "Diagrama del cable de siete pines que conecta IR1–IR5 con A4–A0, con la lista errónea del manual tachada".

## Desafío: el detective de otros manuales

La errata E-001 no es la única del manual: en el [registro de erratas](../../docs/reference/errata-osoyoo.md) hay más casos (voltímetros con nombre de placa equivocado, tornillos que no coinciden con el inventario). Lee dos de ellas y anota: ¿qué evidencia usó el curso para resolver cada una? Estás practicando la habilidad más silenciosa de la ingeniería: desconfiar con método.

## Si no funciona

| Síntoma | Qué revisar | Acción |
|---|---|---|
| No puedo leer la serigrafía del conector | ¿Las letras son mínusculas o están tapadas por el conector? | Usa linterna en ángulo; el diagrama de la p. 18 da el orden si tu placa no se deja leer |
| El conector parece a medias o torcido | ¿Algún pin metálico asoma fuera del plástico del conector? | 🔴 Detente y llama a tu padre: no fuerces el conector; se revisa con calma y sin energía |
| Un cable no llega donde dice el diagrama | ¿Estás siguiendo el cable correcto? El de siete vías es el único del tracker | Verifica contar siete cables; si el montaje real difiere del diagrama, regístralo como posible errata nueva y coméntalo con el adulto |
| Me pierdo entre A0 y A4 | ¿Estás leyendo el shield al revés? | Ubica primero el conector USB de la Mega como referencia de orientación (Lección 04) y cuenta los pines analógicos desde allí |

## Lecturas y videos para explorar

- [Diagrama correcto del tracker de cinco canales](../../assets/osoyoo-manual/pagina-18-pinout-tracker-correcto.png) — Inglés; manual del fabricante; 8 min. Aprenderás diagrama correcto del tracker de cinco canales. Esencial.
- [Erratas y decisión canónica IR1–IR5](../../docs/reference/errata-osoyoo.md) — Español; referencia interna; 8 min. Aprenderás erratas y decisión canónica ir1–ir5. Opcional.

Ya conoces el mapa completo del cableado. En la [Lección 33](33-calibrar-negro-y-blanco.md) le llegará energía por primera vez al tracker y ajustarás su potenciómetro para que distinga el negro del blanco exactamente en tu piso.

## Referencias técnicas de la clase

- [Manual oficial de OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), páginas 17–18: diagrama canónico del tracker (IR1→A4 … IR5→A0) y texto defectuoso de la lista.
- [Errata E-001 del repositorio](../../docs/reference/errata-osoyoo.md): evidencia y decisión canónica sobre la duplicación de pines en el texto del manual.
- [Mapa canónico de conexiones de PX-32](../../docs/reference/mapa-conexiones-robot.md), sección tracker de cinco canales.
- Uso de los pines A0–A5 como entradas digitales en la Mega 2560: [pinout oficial de Arduino](https://docs.arduino.cc/resources/pinouts/A000067-full-pinout.pdf).

## Cuéntale a papá

Cuéntale el caso del detective: dos listas del manual que se contradicen y un diagrama que salva el día. Explícale por qué un pin repetido habría sido un problema técnico y no solo una errata estética. Pregúntale si alguna vez le pasó en su trabajo que dos documentos dijeran cosas distintas y cómo decidió a quién creer. Marca la sesión en [PROGRESS.md](../../PROGRESS.md).

Con el mapa verificado, la [Lección 33](33-calibrar-negro-y-blanco.md) enciende el tracker por primera vez: los LED de la placa te dirán si ve negro o blanco, y tú ajustarás el umbral para tu piso real.
