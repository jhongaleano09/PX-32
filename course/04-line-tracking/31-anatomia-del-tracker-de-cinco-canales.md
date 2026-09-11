# Lección 31 — Anatomía del tracker de cinco canales

## Un sensor que solo sabe decir sí o no

En el bloque de infrarrojo PX-32 aprendió a seguir tu mano con dos sensores que miran hacia adelante. Funcionó, pero con una limitación que quizá notaste: cada sensor solo sabía dos cosas, "veo algo" o "no veo nada". Con esa información el robot puede acercarse o girar, pero nunca sabe *dónde* está exactamente lo que busca.

Hoy empieza un reto nuevo: PX-32 va a seguir una **línea negra pintada en el piso**. Y para eso necesita algo más que sí y no. Imagina jugar a mantener el equilibrio sobre una viga mirando por un solo agujero: sabrías si hay viga o no bajo ese punto, pero no hacia qué lado caerte. Con cinco agujeros en fila, uno al lado del otro, sabrías exactamente dónde está la viga y hacia dónde corregir.

Eso es exactamente lo que tiene PX-32 bajo el frente del chasis: **cinco sensores infrarrojos en fila**, mirando al piso. El fabricante lo llama *tracker de cinco canales* (HW-007), y durante las próximas ocho lecciones va a convertirse en el ojo con el que PX-32 lee el piso.

## Cinco preguntas sí/no son mucho más que una

Piensa en lo que ya sabes de la Lección 25: un par infrarrojo emite luz invisible y mide cuánta regresa. Sobre una superficie blanca vuelve mucha; sobre una negra, casi nada, porque el negro absorbe. Cada uno de los cinco pares del tracker hace esa misma pregunta de reflexión, pero cada uno la hace **en su propio punto del piso**, un poquito más a un lado que el anterior.

Un **canal** es cada par emisor-receptor con su propio circuito: cinco canales, cinco mediciones independientes al mismo tiempo. Y una fila de sensores iguales trabajando juntos tiene nombre técnico: una **matriz de sensores**. No es una pantalla ni un tablero de ajedrez: es simplemente "varios sensores del mismo tipo ordenados en línea" para cubrir un frente completo.

¿Por qué cinco y no uno? Haz la cuenta de la información:

- Con **un** sensor: "hay negro debajo" o "no hay negro". Si el robot se desvía, no sabes hacia dónde.
- Con **tres**: negro al centro, negro a la izquierda, negro a la derecha. Ya hay dirección.
- Con **cinco**: dirección **y** también cuánto. Negro solo en el extremo no es lo mismo que negro en el extremo y su vecino: uno dice "me estoy saliendo", el otro dice "ya me salí bastante". El robot puede corregir suave o fuerte.

Cada canal además no ve un punto infinitamente pequeño: la luz infrarroja sale en un cono y regresa en un cono. Ese cono que ilumina y escucha cada sensor es su **campo de visión**. Como el tracker va montado a una altura fija bajo el chasis, cada canal ve un círculo pequeño del piso, y los cinco círculos forman una franja bajo el frente del robot. El ancho de la línea del hito final (entre 20 y 30 mm, según el fabricante) está elegido para que la tape al menos un círculo completo, pero no a los cinco a la vez.

## Lo que necesitas

- PX-32 ensamblado, **apagado, sin baterías y sin USB**. Hoy no hay energía de ningún tipo: es una clase de pura observación.
- Buena iluminación sobre la mesa (la necesitarás para ver debajo del chasis).
- Un trocito de cinta adhesiva o de mascarilla, para marcar un canal.
- Tu cuaderno y lápiz.
- La ficha [HW-007: tracker de cinco canales](../../docs/hardware/HW-007-ir-tracker-5ch.md) a mano, para consultar.

🟢 Toda la clase la puedes hacer tú: hoy PX-32 es un objeto de museo y nadie corre ningún riesgo. Solo pide ayuda a un adulto si la mesa está incómoda para agacharte a mirar.

## La expedición bajo el chasis

1. 🟢 **Posiciona el robot.** Coloca PX-32 en el borde de la mesa con el frente sobresaliendo un poco, de modo que puedas agacharte y ver por debajo sin levantarlo. Nunca lo voltees sobre el techo ni lo apoyes sobre los sensores: los cables y las ruedas Mecanum no deben cargar el peso.

2. 🟢 **Encuentra el tracker.** Mira debajo del frente del chasis. Vas a ver una placa horizontal que mira al piso, con una fila de componentes hacia abajo. Esa placa es HW-007. Está fijada al chasis inferior con tornillos y separadores plásticos (tubitos que mantienen la placa a una altura fija del piso). No intentes desmontarla: esa altura es parte de la calibración.

3. 🟢 **Cuenta los ojos.** En el borde de la placa que mira al piso encontrarás cinco pares repetidos: en cada par, un LED emisor de infrarrojo (invisible para ti, Lección 24) junto a su receptor. Cuenta los cinco con el dedo, de un extremo de la fila al otro. Cada par es **un canal**, con su nombre serigrafiado o asociado: IR1, IR2, IR3, IR4, IR5.

> **[PENDIENTE VISUAL]**
> - **Tipo:** fotografía anotada del tracker montado en PX-32.
> - **Objetivo:** que el niño localice la placa, los cinco canales, el conector de siete pines y el potenciómetro sin ayuda.
> - **Descripción:** fotografía en picada del frente inferior del chasis con el tracker visible; las cinco posiciones de canal numeradas IR1 a IR5 sobre la imagen; flecha hacia el conector de 7 pines y hacia el potenciómetro azul; línea punteada indicando la altura fija entre placa y piso.
> - **Elementos que deben señalarse:** canales IR1–IR5, conector de siete cables, potenciómetro, chasis, sentido "hacia el piso".
> - **Fuente técnica:** manual OSOYOO, https://osoyoo.com/manual/2021006600-2026.pdf, páginas 16–18, montaje del módulo tracker en el chasis inferior.
> - **Texto alternativo sugerido:** "Vista inferior del frente de PX-32 con la placa tracker y sus cinco canales IR1 a IR5 señalados".

4. 🟢 **Marca el extremo IR1.** Busca en la placa la serigrafía que identifica los pines (letras pequeñas impresas). Uno de los extremos de la fila es IR1 y el otro es IR5. Con el robot apagado, pega el trocito de cinta en el chasis, justo al lado del canal IR1. Esta marca te ahorrá confusiones en las próximas lecciones: cuando el robot esté en movimiento no habrá tiempo de adivinar cuál canal es cuál.

5. 🟢 **Encuentra el cerebro del umbral.** En la placa del tracker hay un componente que ya conoces de la Lección 27: un **potenciómetro** azul con tornillo (en el tracker hay uno que ajusta la sensibilidad del conjunto). No lo toques hoy: lo calibraremos en la Lección 33. Solo confírmalo con la vista.

6. 🟢 **Sigue el cable.** Del extremo de la placa sale un conector de siete cables que sube hacia el shield. Pon el dedo sobre el conector del tracker y sigue el cable con la mirada hasta el shield de la Mega. Son siete porque son cinco canales más la alimentación (VCC y GND). No desconectes nada: en la próxima lección verificaremos este cable con lupa.

7. 🟢 **Dibuja tu mapa.** En el cuaderno, dibuja el frente de PX-32 visto desde abajo: una fila de cinco círculos. Escribe IR1 bajo el círculo de tu marca de cinta, IR5 en el otro extremo, y numera los del medio. Este dibujo es el plano que usaremos durante todo el bloque.

## La pregunta incómoda de la clase

Mira tu dibujo y respóndete con honestidad: ¿IR1 quedó a tu izquierda o a tu derecha cuando miras a PX-32 desde atrás, como su piloto?

Si no puedes responder con seguridad, estás en buena compañía: el diagrama del fabricante muestra el módulo por separado, no montado en el robot, y no indica qué extremo queda hacia el lado izquierdo del chasis. El curso no va a inventar la respuesta. Hasta que la midamos con evidencia en la Lección 34, llamaremos a los lados **extremo IR1** y **extremo IR5**, sin izquierda ni derecha. No es un rodeo: es la diferencia entre saber y suponer.

## Desafío: la línea entre dos ojos

Sin encender nada, desliza un lápiz (o el dedo) lentamente bajo la fila de canales, de un extremo al otro, y estima: ¿cuántos canales cubre el lápiz a la vez si su grueso es parecido al de un lápiz? ¿Y si usaras algo tan angosto como un palillo? Escribe tu estimación. En la Lección 36 la responderemos con números: los canales que ven negro a la vez son los que nos dirán dónde está la línea exactamente.

## Si no funciona

| Síntoma | Qué revisar | Acción |
|---|---|---|
| No encuentro ninguna placa bajo el frente | ¿Estás mirando el frente o la parte trasera del chasis? | El tracker está en el frente inferior; sigue la fila de ruedas delanteras hacia abajo |
| Veo menos de cinco canales | ¿Algún par queda oculto detrás de un soporte o cable? | Mira con linterna lateral; no muevas cables para ver mejor, pide ayuda al adulto |
| No encuentro la serigrafía IR1–IR5 | ¿Las letras son diminutas o están en el conector? | Usa el diagrama de la Lección 32; la marca de cinta puede ir en el canal del extremo que tú definas como IR1 mientras lo verifiques |
| El conector de siete cables está suelto o a medio conectar | No lo presiones con energía | 🔴 Detente y llama a tu padre: un conector mal sentado se revisa con calma y sin forzar |

## Lecturas y videos para explorar

- [Diagrama correcto del tracker de cinco canales](../../assets/osoyoo-manual/pagina-18-pinout-tracker-correcto.png) — Inglés; manual del fabricante; 8 min. Aprenderás diagrama correcto del tracker de cinco canales. Esencial.
- [Erratas y decisión canónica IR1–IR5](../../docs/reference/errata-osoyoo.md) — Español; referencia interna; 8 min. Aprenderás erratas y decisión canónica ir1–ir5. Opcional.

Hoy viste el tracker por fuera; el diagrama del fabricante te espera para la próxima clase, donde descubrirás que ese mismo diagrama corrige un error del texto del manual.

## Referencias técnicas de la clase

- [Manual oficial de OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), páginas 16–18: montaje del módulo tracker en el chasis inferior con tornillos y separadores plásticos, y vista del módulo.
- [Ficha HW-007 del repositorio](../../docs/hardware/HW-007-ir-tracker-5ch.md), componentes y función del tracker de cinco canales.
- Física de reflexión y absorción infrarroja aplicada: [Lección 25](../03-infrarrojo/25-reflexion-y-absorcion.md).

## Cuéntale a papá

Muéstrale el dibujo de tu mapa del frente y explícale por qué cinco canales dan más información que uno solo — la comparación de la viga y los agujeros puede ayudarte. Señala en el robot real tu marca de cinta y dile qué vamos a verificar con ella más adelante: si IR1 queda a la izquierda o a la derecha. Pregúntale si él habría marcado el canal de otra forma. Marca la sesión en [PROGRESS.md](../../PROGRESS.md).

En la [Lección 32](32-ir1-a-ir5-un-mapa-espacial.md) convertiremos tu dibujo en un mapa eléctrico: cada canal viajará por un cable hasta un pin con nombre de la Mega. Y descubrirás que el manual del fabricante se contradice a sí mismo.
