# Lección 21 — La luz transporta energía

## El calor que llega sin tocar nada

Extiende la palma frente a una lámpara encendida. Al poco tiempo sientes calor en la piel, aunque la lámpara no te toca y el aire apenas se movió. Algo viajó desde allí hasta aquí, y ese algo no fue solo "iluminación": fue energía.

La luz no sirve únicamente para ver. Es un mensajero que transporta energía de un lugar a otro. Cuando la luz de una fuente llega a una superficie, dos cosas pueden pasarle a esa energía: la superficie se queda con una parte y se calienta (**absorción**), y otra parte rebota de regreso (**reflexión**). El resto del viaje ocurre siempre igual: la luz sale de la **fuente**, **viaja** en línea recta y puede terminar en un **detector** preparado para recibirla.

Esa cadena de cuatro papeles es exactamente la que PX-32 usará para sentir el mundo sin tocarlo:

```text
fuente de luz → viaje en línea recta → superficie → parte que rebota → detector
```

Todavía no encenderemos el robot. Hoy construyes la idea con tus manos, una lámpara y una sombra, y al final la dibujas aplicada al sensor infrarrojo de PX-32. El detalle curioso —que la lámpara también emite luz que no puedes ver— llegará en la Lección 23.

## Lo que necesitas

- Una lámpara de mesa que caliente un poco (las de bulbo viejo, incandescentes o halógenas, son ideales; una linterna potente también sirve).
- Un libro o un cartón grueso.
- Tres tarjetas de cartulina rígida y un alfiler o la punta de un compás (para el desafío).
- Tu cuaderno y lápiz.
- PX-32 apagado, sin USB y sin baterías, sobre la mesa: solo lo mirarás al final.
- Un adulto que encienda y sostenga la lámpara.

🟡 El adulto maneja la lámpara encendida: las lámparas que calientan también queman si se tocan. PX-32 permanece apagado toda la clase, así que no hay riesgo eléctrico con el robot.

## Siente la energía y córtala con una sombra

1. 🟢 **Palma expuesta.** Pide al adulto encender la lámpara y apuntarla a tu palma desde unos 30 cm. Cuenta despacio hasta veinte y describe qué sientes. Anótalo en el cuaderno con tus palabras: "calor", "hormigueo", "calentón".

2. 🟢 **Predice antes de probar.** ¿Qué pasará con ese calor si el adulto interpone el libro entre la lámpara y tu mano, sin acercar ni alejar nada más? Escribe tu predicción antes de que ocurra.

3. 🟢 **Sombra.** El adulto coloca el libro en medio. Tu mano queda en sombra y el calor desaparece o baja muchísimo. Retira el libro: vuelve. Repite dos veces para confirmar.

4. 🟢 **Concluye con evidencia.** Lo que calentaba tu mano viajaba en línea recta desde la lámpara: por eso un objeto en medio lo bloquea y produce una sombra con borde. Si el calor "doblara esquinas", el libro no lo detendría. La sombra nítida es la firma de un viaje recto.

5. 🟢 **Mira el borde de la sombra** sobre la mesa. ¿Es nítido o difuminado? Acércalo en tu cuaderno: un borde definido confirma de nuevo el viaje en línea recta.

6. 🟢 **Reconoce los cuatro papeles** en lo que acabas de hacer: la lámpara es la fuente, el aire es el camino, tu piel es la superficie que absorbió, y tu piel además actuó de detector (sintió). En PX-32 esos papeles estarán repartidos: el emisor del sensor será la fuente, un objeto será la superficie, y el receptor del sensor será el detector.

## Aplica la cadena al sensor de PX-32

7. 🟢 Con el robot apagado, localiza al frente los dos módulos de sensores infrarrojos: son las plaquitas pequeñas con dos cápsulas gemelas, una a cada lado del frente. Son la pieza HW-008 del inventario de la Lección 02.

8. 🟢 Dibuja en tu cuaderno la cadena completa aplicada al robot: la cápsula **emisora** del módulo como fuente, la flecha de viaje por el aire, la **mano tuya como superficie** a unos centímetros, la flecha de rebote, y la cápsula **receptora** como detector. Rotula cada papel.

9. 🟢 Responde con el dibujo a la vista: ¿qué papel cumple el libro del experimento si lo pones frente al sensor de PX-32? (Bloquearía el viaje: ni iría ni volvería luz.)

> **[PENDIENTE VISUAL]**
> - **Tipo:** diagrama de la cadena óptica aplicada al robot.
> - **Objetivo:** fijar los cuatro papeles de la cadena (fuente, viaje, superficie, detector) sobre PX-32 antes de encenderlo.
> - **Descripción:** vista lateral del frente de PX-32 con el módulo sensor a la izquierda; una flecha continua sale de la cápsula emisora, viaja en línea recta hasta una mano dibujada al frente, y una flecha de retorno llega a la cápsula receptora; debajo, la misma cadena rotulada con los cuatro papeles.
> - **Elementos que deben señalarse:** cápsula emisora, flecha de ida, mano como superficie, flecha de rebote, cápsula receptora, y los rótulos fuente/viaje/superficie/detector.
> - **Fuente técnica:** manual OSOYOO, https://osoyoo.com/manual/2021006600-2026.pdf, páginas 39 a 43, sensores infrarrojos de obstáculos.
> - **Texto alternativo sugerido:** "Diagrama lateral que muestra el haz infrarrojo saliendo del emisor del sensor, rebotando en una mano y regresando al receptor del robot".

Puedes continuar cuando puedas nombrar los cuatro papeles de la cadena y explicar por qué la sombra demostró el viaje en línea recta. Si tu explicación se apoya solo en "porque sí", repite el paso 3 una vez más y observa con calma.

## Desafío: la prueba de las tres tarjetas

Haz un agujero pequeño en el centro de cada tarjeta. Coloca las tres paradas en fila frente a la linterna, a unos 10 cm entre ellas, y alinea los tres agujeros a la altura del haz: verás el punto de luz en la pared. Ahora desalinea una sola tarjeta, apenas un par de milímetros: el punto desaparece. Acabas de demostrar de nuevo que la luz viaja recto, esta vez dejándola pasar en vez de bloquearla. Escribe una frase "Si desalineo un agujero, entonces…, porque…".

## Si algo no cuadra

| Síntoma | Qué revisar | Acción |
|---|---|---|
| No siento casi calor | ¿La lámpara es de las que no calientan (tipo LED fría)? | Usa la sombra y el borde nítido como evidencia; pide otra lámpara para la parte del calor |
| El calor tarda en llegar | La energía se acumula poco a poco en la piel | Cuenta más despacio; no acerques la mano a la lámpara |
| La sombra tiene borde muy difuso | Fuente grande o muy cercana: cada punto ilumina desde un sitio distinto | Aleja un poco la lámpara y repite |
| El libro también se calienta y me confunde | El libro absorbió su parte de energía | Es correcto: absorción y reflexión ocurren a la vez |

## Lecturas y videos para explorar

- [El espectro electromagnético y el infrarrojo](https://science.nasa.gov/ems/07_infraredwaves/) — Inglés; lectura NASA; 8 min. Aprenderás el espectro electromagnético y el infrarrojo. Esencial.
- [Sensores de PX-32](../../docs/reference/sensores.md) — Español; referencia interna; 6 min. Aprenderás sensores de px-32. Opcional.

Cuando enciendas el equipo para la lectura, hazlo con un adulto cerca. La página de NASA muestra el infrarrojo como lo que sentirás en las próximas clases: energía que viaja y se puede detectar.

## Referencias técnicas de la clase

- [NASA Science: ondas infrarrojas](https://science.nasa.gov/ems/07_infraredwaves/), el infrarrojo como radiación que transporta energía y se percibe como calor.
- [NASA Science: introducción al espectro electromagnético](https://science.nasa.gov/ems/01_intro/), la luz como ondas de una misma familia.
- [Manual oficial de OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), páginas 39 a 43, sensores infrarrojos de obstáculos del kit.

## Cuéntale a papá

Muéstrale tu dibujo de la cadena aplicada al sensor y explícale quién es la fuente, qué viaja, quién rebota y quién detecta. Después recréale el momento de la sombra y explícale por qué demuestra que la luz viaja en línea recta. Para cerrar, pregúntale qué otros aparatos de la casa usan luz que viaja y rebota (pistas: el control del televisor, el sensor de la puerta del supermercado).

Lo que ves —los colores del arcoíris— es apenas una franja angosta de una familia mucho más grande. En la [Lección 22](22-el-espectro-electromagnetico.md) ordenarás toda la familia y descubrirás en qué región "escucha" PX-32.
