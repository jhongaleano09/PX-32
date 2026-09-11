# Lección 14 — Puente H: cambiar la polaridad

## 1. Tu misión de hoy

Hoy vas a **predecir el sentido de un motor usando dos entradas lógicas**. Al terminar podrás demostrarlo con una explicación, un dato o un comportamiento observable; no basta con decir “funcionó”.

## 2. Tiempo estimado

- Lectura y conversación inicial: 10 minutos.
- Preparación y predicción: 5 minutos.
- Actividad o programación: 15 minutos.
- Desafío y depuración: 5 minutos.
- Cuéntale a papá y resumen: 5 minutos.

**Total: 40 minutos.** Si aparece una duda de cableado o la actividad necesita más intentos, detente al terminar la preparación y continúa otro día; la seguridad no se comprime para cumplir el reloj.

## 3. Lo que necesitas saber antes de empezar

[Lección 13: Por qué existe el driver Model Y](13-por-que-existe-el-driver-model-y.md). Debes poder explicar su idea central y repetir su prueba segura antes de continuar.

También necesitas distinguir tres capas de PX-32: la **energía** permite que algo ocurra, la **señal** representa información u órdenes y el **programa** decide qué hacer con ellas. Cuando algo falle, pregunta primero en cuál capa está la evidencia. Consulta el [glosario general](../../docs/reference/glosario.md) y el [mapa canónico de conexiones](../../docs/reference/mapa-conexiones-robot.md) sin modificar el montaje.

## 4. Lectura principal

### La idea intuitiva

El tema de hoy es **puente H, polaridad, tabla de verdad y frenado**. En lenguaje cotidiano, buscamos una forma fiable de predecir el sentido de un motor usando dos entradas lógicas. La palabra “fiable” importa: una sola coincidencia puede ser suerte; una explicación científica conecta una causa, una prueba y un resultado que otra persona podría repetir.

Mover un robot exige coordinar lógica y potencia. La Mega produce señales pequeñas; el Model Y dirige energía hacia los motores; los engranajes cambian velocidad por par; y las ruedas Mecanum convierten giros en fuerzas oblicuas. Esta separación protege la placa y ayuda a depurar: primero se comprueba la orden, luego el canal de potencia y por último el resultado mecánico.

### De la intuición al concepto técnico

Los términos centrales son **puente H, polaridad, tabla de verdad y frenado**. No son etiquetas decorativas: cada uno nombra una relación que podremos observar. Una analogía útil es pensar en una receta: ingredientes, pasos y resultado ayudan a organizar la acción. Pero la analogía tiene límite; PX-32 no “sabe” qué desea el cocinero y un componente real responde a voltaje, tiempo, geometría y código, no a intenciones.

En PX-32, esta idea se usa para completar una tabla IN1/IN2 sin energizar y detectar el estado prohibido por prudencia. Antes de actuar, separa cuatro preguntas: ¿qué cambiaremos?, ¿qué mantendremos igual?, ¿qué mediremos?, ¿qué resultado nos obligaría a detenernos? Ese orden convierte una demostración llamativa en un experimento. Si modificamos dos cosas a la vez, perdemos la posibilidad de saber cuál causó el cambio.

Un error frecuente es confundir el nombre de una pieza con una explicación. Decir “es un sensor” no explica qué magnitud detecta, qué señal entrega ni bajo qué condiciones puede equivocarse. Otro error es atribuir intención al programa: una condición `if` no “comprende” el obstáculo; compara representaciones y ejecuta una rama. Pregunta de reflexión: **¿qué evidencia distinguiría una decisión correcta de una coincidencia?**

La meta no es memorizar todo en una lectura. Primero forma un modelo: entrada → transformación → salida. Después contrástalo con la actividad. Si el resultado no coincide, el modelo gana detalle. Esa revisión es aprendizaje científico, no fracaso.

## 5. Palabras nuevas

- **Puente h:** idea principal que podrás reconocer en la actividad.
- **Evidencia:** observación o medición que apoya o contradice una explicación.
- **Variable de prueba:** elemento que cambiamos deliberadamente mientras mantenemos los demás lo más estables posible.
- **Fallo seguro:** estado que reduce el riesgo cuando falta información; en PX-32 suele ser `STOP`.

Puedes consultar definiciones relacionadas en el [glosario general](../../docs/reference/glosario.md).

## 6. Así aparece en PX-32

**Hardware:** HW-004.

```text
fenómeno o comando → sensor/interfaz → pin y programa → decisión → actuador o mensaje
                         ↑                         |
                         └──── evidencia Serial ──┘
```

La cadena exacta de hoy se concentra en **puente H, polaridad, tabla de verdad y frenado**. No cambies conexiones basándote solo en este esquema conceptual. Para pines usa el [mapa canónico](../../docs/reference/mapa-conexiones-robot.md); para discrepancias usa la [errata del manual](../../docs/reference/errata-osoyoo.md). Los límites de potencia y la configuración interna del portabaterías siguen `PENDIENTE_DE_VERIFICAR`.

## 7. Seguridad y participación del adulto

- 🟢 El estudiante puede leer, dibujar, programar y observar el robot apagado.
- 🟡 Un adulto comprueba el estado de PX-32 antes de conectar USB.
- 🔴 Solo el adulto manipula baterías 18650, cargador, potencia o cableado dudoso.

La mesa debe estar seca y despejada. PX-32 permanece apagado y ensamblado salvo que un paso indique lo contrario. Ante calor, olor, humo, chispa o daño visible, no se toca: el adulto aísla la alimentación.

## 8. Predice antes de probar

1. ¿Qué esperas observar cuando logres predecir el sentido de un motor usando dos entradas lógicas y qué mecanismo produciría ese resultado?
2. ¿Qué observación contraria te haría detenerte o revisar la explicación?

Respóndelas en voz alta o en tu cuaderno físico. No necesitas un diario digital.

## 9. Actividad o experimento guiado

1. **Preparar.** Coloca PX-32 estable, identifica HW-004 y confirma con el adulto que la energía está en el estado seguro. Continúa solo si no hay cables sueltos, daño, calor u olor.
2. **Trazar.** Señala la ruta entrada → proceso → salida relacionada con puente H, polaridad, tabla de verdad y frenado. Si no puedes justificar un pin, consulta el mapa; no adivines.
3. **Predecir.** Elige un resultado concreto y una señal de parada. Di qué variable cambiarás y cuáles permanecerán iguales.
4. **Probar.** Vas a completar una tabla IN1/IN2 sin energizar y detectar el estado prohibido por prudencia. Haz un solo cambio. Observa antes de repetir y mantén accesible la forma de detener la prueba.
5. **Comprobar.** El resultado que permite continuar es: cuatro combinaciones clasificadas como giro, parada o condición a evitar. Si no aparece, apaga cuando corresponda y pasa a “Si no funciona”.
6. **Repetir.** Realiza una segunda prueba cambiando solo un valor, posición o entrada. Compara, no persigas un resultado “bonito”.
7. **Restaurar.** Detén el programa, apaga la alimentación y devuelve cualquier ajuste temporal a su posición anotada. El adulto confirma que PX-32 conserva su ensamblaje y que ningún cable invade ruedas o engranajes.

## 10. Código

Hoy no hace falta cargar código nuevo. Si se usa el monitor serie o un sketch anterior, será solo como instrumento de observación. Esta decisión mantiene una sola idea nueva en la sesión y evita confundir un fenómeno físico con un error de sintaxis.

## 11. Qué deberías observar

El resultado normal es **cuatro combinaciones clasificadas como giro, parada o condición a evitar**. Puede haber variación por tolerancias, superficie, luz, fricción, carga, eco o tiempos del programa. Una variación pequeña y repetible es información; un salto grande, un reinicio, una lectura imposible o un movimiento inesperado exige STOP.

No concluyas “está dañado” por un solo dato. Tampoco concluyas “es seguro” porque funcionó una vez. Repite bajo las mismas condiciones y compara. En sensores, conserva una condición conocida; en código, observa Serial; en movimiento, vuelve primero a ruedas levantadas.

## 12. Si no funciona

| Síntoma | Prueba sencilla | Interpretación | Siguiente acción segura |
|---|---|---|---|
| No ocurre nada | Comprueba alimentación lógica, placa y programa esperado | Puede faltar energía o haberse elegido placa/puerto incorrectos | Detén, revisa una capa y vuelve a intentar |
| El dato no cambia | Cambia solo la entrada física prevista | El sensor, pin o lógica puede no coincidir | Imprime la lectura cruda y compárala con el mapa |
| El resultado es intermitente | Repite sin mover cables y observa el tiempo | Puede haber umbral, ruido o conexión inestable | Apaga; el adulto inspecciona conectores |
| Hay movimiento inesperado, calor u olor | No hagas otra prueba | Es una condición de riesgo, no un reto de software | El adulto corta energía y revisa antes de continuar |

El método es siempre **síntoma → prueba pequeña → interpretación → una acción**. Cambiar cinco cosas puede ocultar el problema y crear uno nuevo.

## 13. Desafío

Diseña una variante que cambie una sola condición de la actividad. Antes de ejecutarla, escribe una frase “Si…, entonces…, porque…”. Luego explica si el resultado apoya la predicción. No copies una solución completa: el valor del desafío está en elegir la variable y justificarla.

## 14. Lecturas y videos para explorar

- [Conexiones verificadas de Model Y y motores](../../reference/original/osoyoo-mecanum-wheel-robotic-car-kit-v2.pdf) — Inglés; manual del fabricante; 5-10 min. Aprenderás conexiones verificadas de model y y motores. Esencial.
- [Mapa canónico de conexiones](../../docs/reference/mapa-conexiones-robot.md) — Español; referencia interna; 8 min. Aprenderás mapa canónico de conexiones. Opcional.

Comprueba con un adulto antes de abandonar el material del curso. Un recurso externo amplía la explicación; nunca reemplaza el mapa de conexiones ni las reglas de seguridad de PX-32.

## 15. Cuéntale a papá

- Cuéntale con tus palabras qué significa **puente H** y dónde aparece en PX-32.
- Muéstrale la evidencia y explícale qué cambiaste y qué mantuviste igual.
- Pregúntale qué ejemplo parecido conoce fuera de la robótica.
- Explícale un error posible y la prueba pequeña que usarías para localizarlo.
- Dile qué te gustaría probar después y qué regla de seguridad conservarías.

Esto es una conversación, no un examen. Si una explicación se atasca, vuelvan juntos al diagrama entrada → proceso → salida.

## 16. Resumen de la jornada

Hoy aprendiste a **predecir el sentido de un motor usando dos entradas lógicas** y lo conectaste con **puente H, polaridad, tabla de verdad y frenado**. Pudiste observar cuatro combinaciones clasificadas como giro, parada o condición a evitar. La regla de seguridad es cambiar conexiones únicamente sin energía y usar `STOP` ante información dudosa. La próxima sesión será la [Lección 15: Primera prueba de un motor](15-primera-prueba-de-un-motor.md).
