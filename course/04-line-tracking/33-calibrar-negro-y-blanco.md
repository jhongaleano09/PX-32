# Lección 33 — Calibrar negro y blanco

## El mismo árbitro, una nueva cancha

En la Lección 26 conociste al árbitro silbador: el comparador LM393 que convierte una señal suave en un veredicto seco. En la Lección 27 moviste su barra con el potenciómetro de los sensores de mano. Pues bien: cada canal del tracker tiene dentro el mismo tipo de árbitro, y la placa completa tiene un potenciómetro que hoy vas a girar.

La pregunta que resuelve la calibración es antigua: ¿dónde queda la frontera entre "esto es negro" y "esto es blanco"? Pensemos en lo que ya sabemos de la Lección 25: el blanco refleja mucha luz infrarroja de vuelta y el negro absorbe casi toda. Pero "casi toda" no es "toda": una cartulina negra reflectante, un piso claro apagado o una sombra fuerte corren la frontera de lugar. El comparador no mide "negro": mide "menos reflexión que el umbral". El umbral lo pone el potenciómetro, y **tu piso real manda**: calibrar en la mesa con luz cálida y correr el hito en un pasillo con otra luz es la receta del desastre.

El manual del fabricante describe el objetivo exacto de la calibración con los indicadores de la propia placa: **el LED de señal de un canal se enciende cuando ese canal está sobre negro y se apaga cuando está sobre blanco**. Hoy buscaremos ese comportamiento en los cinco canales, con tu tira de prueba y tu luz.

## Tu pista de práctica

El hito de la Lección 38 usará una línea negra de entre 20 y 30 mm de ancho sobre piso claro — lo recomienda el propio fabricante para su proyecto de seguimiento. Calibrar con la misma geometría que la prueba final no es casualidad: es controlar la variable (Lección 01).

Construye ahora tu tira de calibración:

- Un rectángulo de cartulina o papel negro opaco de **25 mm de ancho** (el punto medio de la ventana recomendada de 20 a 30 mm) por unos 15 cm de largo. Mídelo con regla y recorta con tijeras; pide ayuda si la tijera no coopera.
- Una hoja o cartulina blanca como piso de práctica, al menos del tamaño de una hoja de carta.
- La tira debe ser **mate**, no brillante: un papel muy satinado refleja como un espejo aunque sea negro y confunde al sensor (¿recuerdas la Lección 25? la reflexión no solo depende del color).

🟢 La construcción de la tira es toda tuya. 🟡 La conexión del USB la hace el adulto. 🔴 Las baterías siguen guardadas: hoy no hacen falta.

## El experimento del umbral

1. 🟢 **Prepara la pista.** Pon la hoja blanca sobre la mesa y la tira negra en el centro, bien apoyada y sin arrugas. Acerca PX-32 apagado y ubícalo de pie junto a la pista, con el frente hacia ella.

2. 🟡 **Energía lógica.** El adulto conecta el cable USB. La Mega despierta, su 5V alimenta el shield y de ahí el tracker: la placa enciende sus LED. Sin baterías, ningún motor puede girar: la única energía del día es la del USB, la misma que usaste para leer sensores en la Lección 28. No te preocupes por distinguir ahora cuál LED es de alimentación y cuáles son de señal: lo que observarás en el siguiente paso es cuál LED **cambia** al mover la tira, y eso no necesita etiquetas.

3. 🟢 **Primera lectura, sin tocar nada.** Sostén PX-32 con las dos manos por los costados del chasis —jamás por los cables ni por el tracker— y deslízalo suavemente hasta que el canal central (IR3, tu dibujo de la Lección 31) quede flotando sobre la tira negra, a la altura normal de trabajo. Observa los LED de señal de la placa: el del canal central debería encenderse sobre el negro. Desliza hasta el blanco: debería apagarse. Anota qué ves, sea lo que sea: esto es tu línea base.

4. 🟢 **Ajusta en pasitos.** Si sobre el negro no enciende, o sobre el blanco no se apaga, llegó la hora del tornillo azul. Gíralo con la yema del dedo (o un destornillador pequeño de punta en estrella si el tornillo resiste) en **pasitos de menos de un octavo de vuelta**, exactamente como en la Lección 27, y observa los LED después de cada pasito. Nunca fuerces el tope del potenciómetro: es el mismo componente delicado de entonces. La meta del fabricante, recuerda, es simple y doble: negro → encendido, blanco → apagado.

5. 🟢 **Recorre los cinco canales.** Logrado el equilibrio en el centro, desliza el robot de modo que la tira pase bajo IR1, luego IR2, y así hasta IR5. Cada canal, a su turno sobre el negro, debe encender su LED; al volver al blanco, apagarse. Con un solo potenciómetro para los cinco, la calibración es un prometido de equipo: ajustas hasta que **todos** cumplan, no solo tu favorito. Si un canal se resiste, puede haber algo físico: suciedad en su lente, una sombra particular o una tira más angosta que su campo de visión.

6. 🟢 **Prueba el secuestro de la luz.** Sin mover el robot del blanco, tapa la luz de la sala con tu cuerpo y observa: ¿cambian los LED? Acércate a una ventana o a una lámpara: ¿ahora? La iluminación ambiente es ruido (Lección 25) y la calibración vale para las condiciones donde la hiciste. Anota en el cuaderno: "calibrado con [la luz que había]".

7. 🟢 **La frontera viva.** Para terminar, desliza el robot MUY despacio sobre el borde de la tira, del blanco al negro. Observa el LED: existe una franja diminuta donde el veredicto cambia de un lado al otro y puede titilar. Ahí está el umbral físico, la "barra del salto alto" de la Lección 27, ahora bajo tu robot.

> **[PENDIENTE VISUAL]**
> - **Tipo:** fotografía cenital de la calibración con anotaciones.
> - **Objetivo:** mostrar la posición de sostén del robot, la tira de 25 mm y el LED de señal encendido sobre el negro.
> - **Descripción:** manos sosteniendo el chasis por los costados sobre la pista blanca con tira negra; zoom insertado del tracker con el LED del canal central iluminado; cota de 25 mm sobre la tira; flecha señalando el potenciómetro azul.
> - **Elementos que deben señalarse:** tira negra de 25 mm, canal IR3 sobre la tira, LED de señal encendido, potenciómetro, forma correcta de sostener el chasis.
> - **Fuente técnica:** manual OSOYOO, https://osoyoo.com/manual/2021006600-2026.pdf, páginas 34–38, ajuste de sensibilidad del tracker y ancho de pista de 20–30 mm.
> - **Texto alternativo sugerido:** "Robot sostenido sobre una pista blanca con tira negra de 25 mm mientras el LED del canal central del tracker se enciende".

## Cierre de la sesión

8. 🟢 **Guarda el estado.** Al terminar, el adulto desconecta el USB. El potenciómetro queda donde lo dejaste: es tu calibración. Guarda la tira de papel: la usarás en las próximas tres lecciones como pista de pruebas en la mesa.

9. 🟢 **Anota la ley visual.** En el cuaderno, con fecha: "Sobre negro, el LED de señal ____. Sobre blanco, ____". Esa ley de LED es la versión visible de lo que la Lección 34 medirá con números: qué valor (`0` o `1`) entrega cada canal al ponerse sobre negro.

## Desafío: la tira que no puede

Busca por casa tres "negros" distintos: un jean, una funda de cuero, un cartón café oscuro, la pantalla apagada del televisor. Pasa el canal central sobre cada uno con el robot en USB: ¿encienden el LED? Clasifícalos en "suficientemente negro para mi calibración" y "demasiado claro". Estás descubriendo que negro y blanco no son propiedades absolutas de los objetos, sino de cuánta luz devuelven comparada con tu umbral.

## Si no funciona

| Síntoma | Qué revisar | Acción |
|---|---|---|
| Ningún LED responde en ninguna superficie | ¿El LED de alimentación del tracker encendió con el USB? | Si no: 🔴 llama al adulto a revisar el conector de siete pines (Lección 32); si sí: sigue ajustando, el umbral puede estar muy lejos |
| Enciende sobre blanco Y sobre negro | Umbral demasiado sensible | Gira pasitos hacia el lado que apaga sobre el blanco y verifica de nuevo el negro |
| No enciende ni sobre la tira | ¿La tira es brillante o muy angosta? | Usa cartulina negra mate de 25 mm; prueba también a diferentes alturas sosteniendo el robot |
| Un solo canal no coopera | ¿Suciedad o sombra sobre ese canal? | Límpiate el dedo y pasa suavemente sobre las lentes del canal; repite bajo luz pareja |
| Los LED titilan en medio del borde | ¿Estás en la franja del umbral? | Es normal: ahí el veredicto cambia; muévete unos milímetros hacia un lado u otro |
| La calibración que servía anoche hoy no sirve | ¿Cambió la luz ambiente? | Recalibra con la luz actual y anótalo; la calibración pertenece a sus condiciones |

## Lecturas y videos para explorar

- [Diagrama correcto del tracker de cinco canales](../../assets/osoyoo-manual/pagina-18-pinout-tracker-correcto.png) — Inglés; manual del fabricante; 8 min. Aprenderás diagrama correcto del tracker de cinco canales. Esencial.
- [Erratas y decisión canónica IR1–IR5](../../docs/reference/errata-osoyoo.md) — Español; referencia interna; 8 min. Aprenderás erratas y decisión canónica ir1–ir5. Opcional.

Los LED ya te cuentan la historia del negro y el blanco. En la [Lección 34](34-leer-cinco-sensores-sin-perderse.md) le enseñarás a la Mega a escucharla también, imprimiendo el patrón de cinco dígitos en el monitor serie.

## Referencias técnicas de la clase

- [Manual oficial de OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), páginas 34–38: ajuste de sensibilidad del tracker (LED de señal encendido sobre negro, apagado sobre blanco) y ancho de pista recomendado de 20–30 mm.
- [Lección 27](../03-infrarrojo/27-el-potenciometro-ajusta-el-umbral.md): técnica de ajuste en pasitos y funcionamiento del potenciómetro.
- [Lección 26](../03-infrarrojo/26-lm393-convertir-una-senal-en-decision.md): el comparador y el umbral como barra de salto alto.

## Cuéntale a papá

Muéstrale la calibración en vivo: el robot sobre la tira, el LED encendiendo y apagando. Explícale por qué la calibración depende de la luz de la habitación y qué le pasaría al robot si corre el hito en otro ambiente sin recalibrar. Cuéntale cuál de los tres "negros" del desafío resultó ser negro de verdad para el sensor. Marca la sesión en [PROGRESS.md](../../PROGRESS.md).

Con el umbral ajustado, el tracker está listo para hablar con la Mega: en la [Lección 34](34-leer-cinco-sensores-sin-perderse.md) aparecerá el primer programa del bloque y una sorpresa: descubrirás por fin de qué lado físico está IR1.
