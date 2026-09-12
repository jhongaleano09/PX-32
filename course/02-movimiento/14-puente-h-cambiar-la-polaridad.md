# Lección 14 — Puente H: cambiar la polaridad

## Cuatro interruptores que rodean al motor

Un motor DC cambia de sentido cuando cambia el sentido de la corriente. Podrías invertir físicamente sus dos cables cada vez, pero sería lento, dañaría conectores y no permitiría que un programa condujera el robot. El **puente H** hace esa inversión electrónicamente.

Su nombre viene del dibujo: el motor ocupa la barra central de una H y cuatro interruptores electrónicos forman los lados. Al cerrar un par diagonal, la corriente cruza el motor en un sentido. Al cerrar el otro par, lo cruza al contrario. En Model Y, esos interruptores están dentro de los circuitos de control; no debes buscarlos como cuatro palancas visibles.

Cada canal del Model Y usa dos entradas de dirección. OSOYOO documenta esta convención:

| Primera entrada | Segunda entrada | Acción documentada |
|---:|---:|---|
| `HIGH` | `LOW` | adelante |
| `LOW` | `HIGH` | atrás |

La familia de driver PT5126 usada por Model Y también define los dos estados iguales:

| Entradas | Estado del driver | Qué significa para la clase |
|---|---|---|
| `LOW`, `LOW` | espera o alta impedancia | el canal no impulsa el motor |
| `HIGH`, `HIGH` | freno | ambos terminales quedan al mismo nivel y el motor se opone al giro |

Por tanto, `HIGH/HIGH` **no es un estado prohibido** en este driver: es frenado. Aun así, el curso usará una parada más conservadora y fácil de reconocer: primero pondrá PWM en `0` y luego ambas entradas en `LOW`. No vamos a experimentar todavía con la diferencia entre dejar rodar y frenar.

## Construye el puente sobre papel

Prepara:

- Una hoja con una H grande y un círculo en el centro que diga `MOTOR`.
- Cuatro monedas o fichas para representar los interruptores.
- Dos tarjetas `HIGH` y dos tarjetas `LOW`.
- Lápiz rojo para la corriente y lápiz azul para el sentido del eje.
- El robot apagado como referencia visual; no se manipulará su cableado.
- El mapa de pines de la [Lección 13](13-por-que-existe-el-driver-model-y.md).

🔴 El adulto confirma baterías fuera, USB desconectado e interruptores apagados. La tabla se probará con fichas, no con energía real.

## Haz que la tabla explique el giro

1. 🟢 En tu H, marca los cuatro extremos como `+`, `-`, `+` y `-` de manera que puedas trazar dos diagonales alternativas. Recuerda: es un modelo de conmutación, no el esquema exacto del Model Y.

2. 🟢 Coloca fichas sobre una diagonal y dibuja una flecha roja que atraviese el motor de izquierda a derecha. Nombra ese resultado `sentido A` antes de llamarlo “adelante”: el giro físico también depende de cómo estén montados los cables y la rueda.

3. 🟢 Cambia únicamente a la otra diagonal. La flecha roja atraviesa ahora el motor de derecha a izquierda; la flecha azul del eje también debe invertirse. Acabas de representar el trabajo de `HIGH/LOW` frente a `LOW/HIGH`.

4. 🟢 Elige el canal `AK1`. Copia sus nombres reales: `D11` habilita/PWM, `D5` llega a `IN1` y `D6` a `IN2`. Completa:

| D11/PWM | D5/IN1 | D6/IN2 | Predicción |
|---:|---:|---:|---|
| `0` | cualquiera | cualquiera | deshabilitado por el programa del curso |
| activo | `LOW` | `LOW` | espera, sin impulso |
| activo | `HIGH` | `LOW` | adelante según OSOYOO |
| activo | `LOW` | `HIGH` | atrás según OSOYOO |
| activo | `HIGH` | `HIGH` | freno |

`cualquiera` significa que el valor de dirección no manda mientras la habilitación esté apagada. En código suele escribirse `X` en una tabla de verdad.

5. 🟢 Representa con las tarjetas las cinco filas. En cada una di primero el estado de habilitación, después las dos entradas y solo al final la acción. Ese orden evita confundir `ENA` con `IN1`.

6. 🟢 Busca en el mapa los tres pines equivalentes para `BK1`: D9, D22 y D24. Sin rehacer toda la tabla, explica qué nombres cambian y qué lógica permanece igual.

7. 🟢 Predice qué secuencia es más suave para invertir un motor que ya gira: `adelante -> atrás` inmediatamente, o `adelante -> STOP -> espera -> atrás`. Elige la segunda y explica que da tiempo a perder velocidad antes de aplicar par contrario.

8. 🟢 La misión termina cuando puedes cubrir los rótulos de “acción”, reconstruirlos a partir de las entradas y corregir esta frase: “Los dos HIGH siempre son un cortocircuito”. En el PT5126 corresponden al estado de freno definido por el fabricante.

> **[PENDIENTE VISUAL]**
> - **Tipo:** diagrama conceptual animable de puente H.
> - **Objetivo:** relacionar las combinaciones `HIGH/LOW` y `LOW/HIGH` con dos recorridos opuestos de corriente, sin sugerir que el niño debe construir el circuito.
> - **Descripción:** tres paneles: diagonal A activa y giro A; todas las ramas sin impulsar y STOP; diagonal B activa y giro B. Un recuadro aparte muestra `HIGH/HIGH = freno` según la tabla del driver.
> - **Elementos que deben señalarse:** cuatro conmutadores, motor, polaridad, flechas de corriente, `IN1`, `IN2`, habilitación/PWM, espera y freno.
> - **Fuente técnica:** OSOYOO Model Y, https://osoyoo.com/2022/02/25/osoyoo-model-y-4-channel-motor-driver/; datasheet oficial PT5126A, https://www.princeton.com.tw/LinkClick.aspx?fileticket=n1QmI7KLyEk%3D&language=en-US&mid=5406&portalid=0&tabid=3542, tabla funcional.
> - **Texto alternativo sugerido:** “Un puente H cambia el recorrido de la corriente por el motor al activar uno u otro par diagonal de interruptores”.

## Errores que tu modelo debe detectar

| Confusión | Corrección |
|---|---|
| Cambiar `ENA` para invertir | `ENA` habilita o modula; las dos entradas `IN` establecen el sentido |
| Usar dos `HIGH` como giro | En el driver documentado, `HIGH/HIGH` es freno |
| Afirmar que `LOW/LOW` y PWM `0` son idénticos internamente | Ambos evitan impulso en nuestra práctica, pero actúan en puntos distintos del control |
| Llamar “adelante” a cualquier giro de un motor suelto | “Adelante” depende del conector, cableado y posición de la rueda |
| Invertir sin pausa | Aplica par contrario mientras todavía hay movimiento; el curso siempre detiene y espera |

## Lecturas y videos para explorar

- [H Bridge Motor Control Basics Explained](https://www.youtube.com/watch?v=YYMsS50x1UY) — Inglés sencillo, con muchos dibujos y poco texto hablado; video; 2 min.
**Por qué este recurso:** confirma en dos minutos el dibujo de la H con cuatro interruptores que construiste en papel; el inglés es muy accesible porque casi todo se ve, no se escucha.

- [Explicación del Puente H con transistores](https://www.youtube.com/watch?v=OuaLi_bBR9o) — Español; video; 8 min.
**Por qué este recurso:** profundiza en cómo cuatro interruptores electrónicos invierten la polaridad, igual que tus fichas sobre la H dibujada.

- [Control de motores con Arduino](https://wiki.bricolabs.cc/es/guias/control_de_motores) — Español; lectura con esquemas; ~12 min.
**Por qué este recurso:** confirma el puente H con diagramas paso a paso y explica por qué `LOW/LOW` deja el motor en espera, como en tu tabla de la lección.

Busca en estos recursos una imagen del puente H y compárala con tu hoja: las dos diagonales y el motor al centro deben coincidir.

## Referencias técnicas de la clase

- [Guía oficial del Model Y](https://osoyoo.com/2022/02/25/osoyoo-model-y-4-channel-motor-driver/), tabla `IN1/IN2`, canales y PWM.
- [Datasheet oficial PT5126A](https://www.princeton.com.tw/LinkClick.aspx?fileticket=n1QmI7KLyEk%3D&language=en-US&mid=5406&portalid=0&tabid=3542), página 5, estados espera, avance, retroceso y freno de la familia de driver indicada por OSOYOO.
- [Manual oficial de OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), página 13, conexiones de cada entrada del Model Y.

## Cuéntale a papá

Pon las tarjetas en `HIGH/LOW`, invierte a `LOW/HIGH` y narra qué cambia físicamente. Después muéstrale la fila de freno y explica por qué corregiste la idea de que era una combinación prohibida.

La [Lección 15](15-primera-prueba-de-un-motor.md) llevará esta tabla al motor trasero derecho con un pulso breve, ruedas elevadas y un programa que arranca detenido.
