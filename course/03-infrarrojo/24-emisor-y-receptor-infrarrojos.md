# Lección 24 — Emisor y receptor infrarrojos

## Una linterna y un ojo montados en una plaquita

Un sensor de obstáculos suena a cosa mágica: "detecta objetos". Pero ya tienes todas las piezas para desenmascararlo. En la Lección 21 armaste la cadena fuente → viaje → superficie → rebote → detector. En la Lección 23 viste que existe luz que no ves y cámaras que sí la ven. Hoy abres el sensor de PX-32 y descubres que adentro vive una **linterna** y un **ojo** en miniatura.

La linterna es un **LED infrarrojo**: un diodo emisor como el LED que hiciste parpadear en el Blink, pero fabricado para emitir en ~940 nm en vez de color visible. El ojo es un **fotodetector**: un componente cuyo comportamiento eléctrico cambia según la cantidad de luz infrarroja que le llega. Los dos viven en cápsulas gemelas, una al lado de la otra, mirando hacia adelante.

¿Cómo saber cuál es cuál si parecen iguales? Hay dos pistas. La primera es el color de la cápsula: el receptor suele venir en cápsula oscura, casi negra, porque ese plástico filtra la luz visible y deja pasar principalmente infrarroja; el emisor suele venir transparente. La segunda pista es la que ya dominas: enciéndelo y míralo con la cámara que funcionó en la Lección 23. La cápsula que brille en la pantalla es la linterna. Hoy verificas las dos pistas con tu propio módulo.

Hay una palabra nueva importante: **ruido**. El ojo del sensor no solo recibe la luz de su propia linterna rebota. También le llega infrarrojo del sol, de las lámparas, de tu cuerpo calentito cerca del módulo. Todo eso es ruido: información que llega mezclada con la que nos interesa. La **señal** es la parte que sí significa algo para el experimento: la luz de nuestra linterna que regresa tras chocar con un objeto. Un sensor con mucho ruido se confunde; más adelante verás cómo el diseño y la calibración lo defienden.

Además de las cápsulas, el módulo tiene más residentes que irás conociendo: un chip negro rotulado **LM393** que convierte la señal en decisión (Lección 26), un cuadrito azul con tornillo que ajusta la sensibilidad (Lección 27), LED indicadores y tres pines de conexión.

## Lo que necesitas

- PX-32 ensamblado, con los dos sensores infrarrojos montados al frente.
- El teléfono con la cámara que vio el control remoto en la Lección 23.
- Tu cuaderno y lápiz.
- El [mapa canónico de conexiones](../../docs/reference/mapa-conexiones-robot.md) a la vista (impreso o en pantalla).
- Cable USB y un computador al cual conectarlo (solo para dar energía en la segunda parte; no se sube ningún programa hoy).
- Un adulto presente durante la conexión USB.

Estado inicial: PX-32 apagado, sin baterías y sin USB al empezar. Los sensores ya deben estar conectados según el manual; hoy no conectas nada nuevo, solo verificas.

## Primera parte: anatomía con el robot frío

1. 🟢 **Encuentra los módulos.** Ubica los dos sensores HW-008 en el frente del robot, uno a cada lado. Son las plaquitas pequeñas con las dos cápsulas gemelas hacia adelante. Señálalos con el dedo sin tocar los cables.

2. 🟢 **Identifica cada parte** en uno de los módulos, ayudándote con la lista: las dos cápsulas gemelas (linterna y ojo), el chip negro de muchas patas rotulado LM393, el cuadrito azul con tornillo (el potenciómetro), los LED indicadores y los tres pines del extremo con su cable de tres hilos.

3. 🟢 **Sigue el cable.** Recorre con el dedo, sin jalar, el cable de tres hilos del sensor izquierdo hasta el shield: debe terminar en los pines 5V, GND y **D3**. El del sensor derecho termina en 5V, GND y **D2**. Compara con el mapa canónico y con la página 40 del manual. Anota en el cuaderno la pareja de cada sensor: "izquierdo → D3, derecho → D2".

4. 🟢 **Verifica o detente.** Si algún cable no llega donde dice el mapa, no conectes energía. Marca la diferencia en el cuaderno y pásale el caso al adulto antes de la segunda parte.

5. 🟢 **Dibuja el módulo** de frente, rotulando: emisor, receptor, LM393, potenciómetro, LEDs, VCC, GND y OUT.

> **[PENDIENTE VISUAL]**
> - **Tipo:** fotografía anotada del módulo sensor IR.
> - **Objetivo:** permitir localizar cada componente del módulo antes de usarlo.
> - **Descripción:** primer plano del sensor HW-008 con flechas y rótulos sobre cada elemento; junto a él, el mismo módulo visto por la cámara del teléfono con la cápsula emisora brillando.
> - **Elementos que deben señalarse:** cápsula emisora, cápsula receptora (oscura), chip LM393, potenciómetro azul, LED de alimentación, LED de señal, pines VCC/GND/OUT.
> - **Fuente técnica:** manual OSOYOO, https://osoyoo.com/manual/2021006600-2026.pdf, página 40, conexión de los sensores IR.
> - **Texto alternativo sugerido:** "Primer plano del sensor infrarrojo con sus componentes rotulados y la vista de cámara que revela la cápsula emisora encendida".

## Segunda parte: ¿cuál cápsula es la linterna?

6. 🟡 **Energía lógica.** El adulto revisa que no haya baterías y conecta solo el cable USB. Observa el módulo: un LED de alimentación debe encenderse en cada sensor. Ese es tu comprobante de que el USB alimenta los sensores a través del shield. Si no se enciende, detente: el adulto revisa la conexión antes de continuar.

7. 🟢 **Mira con la cámara.** Apunta la cámara que funcionó en la Lección 23 a las cápsulas de un módulo, a unos 5 o 10 cm. Una de las dos debería verse iluminada (blanquecina o violácea, fija o con un parpadeo rápido): es el emisor haciendo su trabajo. La otra permanece oscura: es el receptor. Anota cuál brilló y de qué color era su cápsula. ¿Coincidió con la predicción de la cápsula transparente?

8. 🟢 **Prueba de detección.** Pon tu mano a unos 10 cm frente al módulo, abierta y plana. El LED de señal del sensor debe encenderse al detectar; al retirar la mano, se apaga. Con esto confirmas el circuito completo: linterna encendida, mano que refleja, ojo que recibe el rebote.

9. 🟢 **Repite en el otro módulo** los pasos 7 y 8. Anota si ambas cápsulas emisoras brillan por igual y si ambos detectan la mano. Si uno detecta mucho antes que otro, no lo arregles todavía: es exactamente el problema que resolverás en la Lección 27.

10. 🟡 **Cierre.** Avisa al adulto para retirar el USB. El robot vuelve a quedar apagado.

La lección está completa cuando puedes, señalando el módulo real: nombrar la linterna y el ojo, decir cuál brilló en la cámara, y explicar qué es señal y qué es ruido con un ejemplo (la mano que refleja es señal; el sol de la ventana es ruido).

## Desafío: el mapa del ruido

Con el USB conectado y el adulto presente, acércale al sensor una lámpara de la casa encendida desde un lado, sin poner nada frente al módulo. Observa si el LED de señal reacciona aunque no haya "objeto" frente a él. Anota tu conclusión: ¿qué tanto ruido infrarrojo hay en tu sala? Ese dato te servirá al calibrar.

## Si algo no cuadra

| Síntoma | Qué revisar | Acción |
|---|---|---|
| Ninguna cápsula brilla en la cámara | ¿Se encendió el LED de alimentación del módulo? | Si no, el USB no está alimentando el sensor: el adulto revisa el cable de tres hilos; si sí, prueba otra cámara |
| El LED de alimentación no enciende | ¿El cable de tres hilos está bien insertado en el shield? | El adulto verifica el mapa 5V/GND/OUT antes de repetir |
| El LED de señal está siempre encendido | ¿Hay algo frente al sensor o mucha luz directa? | Anótalo: en la Lección 27 ajustarás el potenciómetro; es el síntoma que el manual manda corregir |
| El LED de señal nunca enciende | ¿La mano está a unos 10 cm y frente a las cápsulas? | Acércala despacio; si tampoco así, el umbral quedó muy exigente (Lección 27) |

## Lecturas y videos para explorar

- [El espectro electromagnético y el infrarrojo](https://science.nasa.gov/ems/07_infraredwaves/) — Inglés; lectura NASA; 8 min. Aprenderás el espectro electromagnético y el infrarrojo. Esencial.
- [Sensores de PX-32](../../docs/reference/sensores.md) — Español; referencia interna; 6 min. Aprenderás sensores de px-32. Opcional.

La referencia interna resume qué informa y qué no informa cada sensor de PX-32; después de hoy sabes por qué el de obstáculos no mide distancias exactas: solo pregunta si regresó suficiente luz.

## Referencias técnicas de la clase

- [Manual oficial de OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), páginas 39 a 43 y conexión de la página 40: sensores izquierdo en D3 y derecho en D2, LEDs indicadores de alimentación y señal.
- [Ficha HW-008 del repositorio](../../docs/hardware/HW-008-ir-obstaculos.md), componentes y pines de los sensores de obstáculos.
- [NASA Science: infrarrojo cercano reflejado](https://science.nasa.gov/ems/08_nearinfraredwaves/), cómo se refleja el infrarrojo cercano y por qué interesa filtrar el visible.

## Cuéntale a papá

Llévalo al robot y preséntale las partes como quien presenta a un equipo: "esta es la linterna, este el ojo, este el árbitro que decidirá, este el tornillo de la sensibilidad". Explícale cómo supiste cuál cápsula es la linterna sin ver su luz, y dale un ejemplo de señal y otro de ruido para el sensor de la casa.

La linterna ya ilumina y el ojo ya recibe. En la [Lección 25](25-reflexion-y-absorcion.md) pondrás a prueba al conjunto con distintos materiales: blanco, negro, metal… y descubrirás que no todos los objetos "aparecen" igual ante el sensor.
