# Lección 13 — Por qué existe el driver Model Y

## Dos caminos llegan al mismo motor

Imagina que la Mega dice “gira”, pero no hay energía capaz de mover la rueda. La orden existe y el movimiento no. Ahora imagina lo contrario: hay baterías, pero ninguna señal decide hacia dónde debe circular la corriente. Hay energía y tampoco hay control.

PX-32 resuelve ese encuentro con la placa azul **OSOYOO Model Y V2.0**. Es un **driver de motores**: recibe señales lógicas desde la Mega y conmuta una ruta de potencia hacia los motores. La Mega decide; el Model Y entrega y dirige la energía que necesita el actuador.

Esto es una **separación funcional**, no un aislamiento eléctrico. Las dos partes del sistema comparten conexiones y referencia; el driver no es una pared mágica. Además, OSOYOO aclara que `VOUT` está conectado directamente a `VIN`, sin un regulador entre ambos. Por eso nunca debes suponer que `VOUT` “reduce” el voltaje.

La placa Model Y ofrece cuatro canales independientes usados por PX-32:

| Canal | Motor del robot | Habilitación/PWM | Dirección |
|---|---|---:|---|
| BK1 | Frontal derecho | D9 | D22 y D24 |
| BK3 | Frontal izquierdo | D10 | D26 y D28 |
| AK1 | Trasero derecho | D11 | D5 y D6 |
| AK3 | Trasero izquierdo | D12 | D7 y D8 |

Las salidas con número `K2` o `K4` que aparecen en la placa repiten el canal vecino; el kit conecta sus cuatro motores a `BK1`, `BK3`, `AK1` y `AK3`.

## Materiales para seguir las rutas

- PX-32 ensamblado, sin USB y sin baterías.
- El manual OSOYOO abierto en las páginas 13 y 15.
- Dos hilos, cintas o lápices de colores distintos: uno para **orden** y otro para **energía**.
- Una hoja para copiar solamente nombres y flechas, no el dibujo completo.
- Una linterna para leer las serigrafías `M_A`, `M_B`, `VIN` y `VOUT`.
- Un adulto para confirmar el estado sin energía; no se desconectará ningún cable.

Debes poder localizar motor, reductora y rueda como en la [Lección 12](12-del-electron-al-giro-motor-dc.md).

🔴 Tu padre retira las celdas y el USB, apaga los interruptores y comprueba que no haya herramientas metálicas sobre las placas. Esta clase es una investigación visual: no energices nada.

## Rastrea una orden

1. 🟢 Orienta el frente del robot hacia adelante usando la barrera de los faros. Busca la Mega 2560 en el nivel superior y el Model Y azul en el nivel inferior, entre los motores.

2. 🟢 En la página 13 del manual encuentra el grupo `M_A`. Sigue con el primer color `D11 -> M_A ENA`, `D5 -> IN1` y `D6 -> IN2`. Esas tres señales controlan el canal `AK1`.

3. 🟢 Localiza visualmente el cable de seis posiciones de la zona `M_A`. No lo retires. Sigue su recorrido desde el shield superior hasta la cabecera del Model Y. El color de un hilo ayuda a seguirlo, pero la prueba es la etiqueta de cada extremo.

4. 🟢 Desde `M_A` continúa hasta el conector `AK1`, que según el manual pertenece al motor trasero derecho. Acabas de recorrer la ruta de una orden:

```text
programa -> pines D11, D5 y D6 -> Model Y, canal AK1 -> motor trasero derecho
```

## Rastrea la energía sin confundirla con la señal

5. 🟢 Cambia al segundo color. En la página 15 encuentra `battery box -> VIN` del Model Y. Después sigue desde la placa hacia el motor conectado a `AK1`.

6. 🟢 Observa también `VOUT -> VIN` del UART WiFi Shield. Esta rama alimenta otra parte del robot, pero no reemplaza los tres pines de control. Copia en tu hoja:

```text
portabaterías -> VIN del Model Y -> etapa de potencia -> AK1 -> motor
                         |
                         +-> VOUT -> VIN del shield
```

7. 🟢 Coloca los dos colores junto al Model Y. Ambos caminos llegan a la misma placa por lugares diferentes: uno lleva información; el otro, energía. Explica qué pasaría si faltara cada uno.

8. 🟢 Repite el rastreo de señales para `BK1`: D9, D22 y D24. No necesitas seguir todas las rutas físicamente; la meta es demostrar que sabes leer el mapa sin adivinar por colores.

9. 🟢 Busca en la placa las letras `AOUT`, `BOUT`, `VIN` y `VOUT`. Si la serigrafía queda oculta por el chasis o los cables, usa la fotografía del manual; no dobles un cable para “ver mejor”.

La actividad termina cuando tu hoja contiene dos rutas completas, cada una con origen, paso por el Model Y y destino, y puedes explicar por qué una señal de la Mega no alimenta directamente el motor.

> **[PENDIENTE VISUAL]**
> - **Tipo:** fotografía anotada en dos colores.
> - **Objetivo:** diferenciar físicamente el camino de control y el camino de potencia en PX-32.
> - **Descripción:** vista superior con el chasis abierto como en el manual; flechas azules parten de D11, D5 y D6 hacia `M_A`, y flechas naranjas parten del portabaterías hacia `VIN`, cruzan el Model Y y terminan en `AK1`.
> - **Elementos que deben señalarse:** Mega 2560, UART WiFi Shield, cable de seis posiciones `M_A`, `ENA`, `IN1`, `IN2`, `VIN`, `VOUT`, `AK1` y motor trasero derecho.
> - **Fuente técnica:** manual OSOYOO, https://osoyoo.com/manual/2021006600-2026.pdf, páginas 13 y 15; descripción oficial del Model Y, https://osoyoo.com/2022/02/25/osoyoo-model-y-4-channel-motor-driver/.
> - **Texto alternativo sugerido:** “Dos rutas de distinto color llegan al Model Y: una lleva órdenes desde la Mega y otra lleva energía desde las baterías”.

## Dudas que esta placa suele provocar

- **“¿M_A significa motor izquierdo?”** No. Es el nombre de una zona del driver; en este montaje controla `AK1` y `AK3`, los dos motores traseros.
- **“¿ENA es energía?”** No. Es la entrada de habilitación y PWM del primer canal de cada zona.
- **“¿VOUT es una salida regulada?”** OSOYOO dice que está unida directamente a `VIN`; no la trates como una salida de voltaje reducido.
- **“¿Los K2 y K4 son otros motores independientes?”** En Model Y V2.0 están sincronizados con K1 y K3 del mismo par. PX-32 usa los cuatro conectores K1/K3 documentados.
- **“¿Puedo comprobar un cable tirando de él?”** No. OSOYOO advierte sujetar la carcasa plástica del conector, y cualquier retiro corresponde al adulto con toda fuente desconectada.

## Lecturas y videos para explorar

- [Cómo usar el driver controlador de motores L298N](https://www.youtube.com/watch?v=0bxqxp9EkVI) — Español; video; 17 min (verlo por partes).
**Por qué este recurso:** profundiza en la idea central de la lección con otro driver distinto al Model Y pero con el mismo trabajo: recibir órdenes de un lado y gobernar la potencia del otro; divídelo en dos partes.

- [Motor DC con Arduino y driver L298N o L293D](https://programarfacil.com/electronica/motor-dc/) — Español; lectura; ~12 min.
**Por qué este recurso:** confirma por qué los pines de la placa no pueden alimentar un motor y por qué existe el intermediario, exactamente la separación entre señal y energía que rastrea esta clase.

- [¿Qué es un motor shield?](https://pasionelectronica.com/que-es-un-motor-shield/) — Español; lectura; ~5 min.
**Por qué este recurso:** estimula la curiosidad al mostrar placas que se montan sobre Arduino como un sándwich para controlar cuatro motores; te ayuda a imaginar variantes del Model Y.

Mientras exploras, usa tus dos colores: cada flecha de cada recurso debería responder «¿esto lleva una orden o transporta potencia?».

## Referencias técnicas de la clase

- [OSOYOO Model Y H-Bridge 4-Channel Motor Driver](https://osoyoo.com/2022/02/25/osoyoo-model-y-4-channel-motor-driver/), canales, entradas, PWM y conexión directa entre `VIN` y `VOUT`.
- [Manual oficial de OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), páginas 13 y 15, cableado de control y alimentación.
- [Pinout oficial de Arduino Mega 2560](https://docs.arduino.cc/resources/pinouts/A000067-full-pinout.pdf), pines PWM y límite de corriente de los GPIO de la placa oficial.

## Cuéntale a papá

Usa tus dos colores para narrar qué viaja por cada ruta. Luego pregúntale: si el motor no gira, ¿qué observación separaría un problema de señal de uno de potencia? No hace falta resolver una avería; basta con formular una prueba segura.

En la [Lección 14](14-puente-h-cambiar-la-polaridad.md) abrirás conceptualmente el Model Y para descubrir cómo dos entradas deciden el sentido del giro.
