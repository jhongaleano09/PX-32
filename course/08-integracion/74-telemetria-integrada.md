# Lección 74 — Telemetría integrada

## 1. Tu misión de hoy

Hoy vas a **reportar modo, sensores y orden en una línea interpretable**. Al terminar podrás demostrarlo con una explicación, un dato o un comportamiento observable; no basta con decir “funcionó”.

## 2. Tiempo estimado

- Lectura y conversación inicial: 10 minutos.
- Preparación y predicción: 5 minutos.
- Actividad o programación: 15 minutos.
- Desafío y depuración: 5 minutos.
- Cuéntale a papá y resumen: 5 minutos.

**Total: 40 minutos.** Si aparece una duda de cableado o la actividad necesita más intentos, detente al terminar la preparación y continúa otro día; la seguridad no se comprime para cumplir el reloj.

## 3. Lo que necesitas saber antes de empezar

[Lección 67: Telemetría: el robot informa](../07-wifi-iot/67-telemetria-el-robot-informa.md), [Lección 73: Línea con obstáculos](73-linea-con-obstaculos.md). Debes poder explicar su idea central y repetir su prueba segura antes de continuar.

También necesitas distinguir tres capas de PX-32: la **energía** permite que algo ocurra, la **señal** representa información u órdenes y el **programa** decide qué hacer con ellas. Cuando algo falle, pregunta primero en cuál capa está la evidencia. Consulta el [glosario general](../../docs/reference/glosario.md) y el [mapa canónico de conexiones](../../docs/reference/mapa-conexiones-robot.md) sin modificar el montaje.

## 4. Lectura principal

### La idea intuitiva

El tema de hoy es **registro, marca de tiempo, modo y decisión**. En lenguaje cotidiano, buscamos una forma fiable de reportar modo, sensores y orden en una línea interpretable. La palabra “fiable” importa: una sola coincidencia puede ser suerte; una explicación científica conecta una causa, una prueba y un resultado que otra persona podría repetir.

Integrar no significa pegar programas completos. Significa definir estados, prioridades e interfaces para que varios subsistemas cooperen. La regla rectora es que STOP domina cualquier modo. Cada comportamiento complejo se construye verificando primero entradas, luego decisiones y finalmente salidas, con fallos simulados antes de la demostración física.

### De la intuición al concepto técnico

Los términos centrales son **registro, marca de tiempo, modo y decisión**. No son etiquetas decorativas: cada uno nombra una relación que podremos observar. Una analogía útil es pensar en una receta: ingredientes, pasos y resultado ayudan a organizar la acción. Pero la analogía tiene límite; PX-32 no “sabe” qué desea el cocinero y un componente real responde a voltaje, tiempo, geometría y código, no a intenciones.

En PX-32, esta idea se usa para emitir registros CSV sin datos personales y comparar con conducta visible. Antes de actuar, separa cuatro preguntas: ¿qué cambiaremos?, ¿qué mantendremos igual?, ¿qué mediremos?, ¿qué resultado nos obligaría a detenernos? Ese orden convierte una demostración llamativa en un experimento. Si modificamos dos cosas a la vez, perdemos la posibilidad de saber cuál causó el cambio.

Un error frecuente es confundir el nombre de una pieza con una explicación. Decir “es un sensor” no explica qué magnitud detecta, qué señal entrega ni bajo qué condiciones puede equivocarse. Otro error es atribuir intención al programa: una condición `if` no “comprende” el obstáculo; compara representaciones y ejecuta una rama. Pregunta de reflexión: **¿qué evidencia distinguiría una decisión correcta de una coincidencia?**

La meta no es memorizar todo en una lectura. Primero forma un modelo: entrada → transformación → salida. Después contrástalo con la actividad. Si el resultado no coincide, el modelo gana detalle. Esa revisión es aprendizaje científico, no fracaso.

## 5. Palabras nuevas

- **Registro:** idea principal que podrás reconocer en la actividad.
- **Evidencia:** observación o medición que apoya o contradice una explicación.
- **Variable de prueba:** elemento que cambiamos deliberadamente mientras mantenemos los demás lo más estables posible.
- **Fallo seguro:** estado que reduce el riesgo cuando falta información; en PX-32 suele ser `STOP`.

Puedes consultar definiciones relacionadas en el [glosario general](../../docs/reference/glosario.md).

## 6. Así aparece en PX-32

**Hardware:** HW-003, sensores.

```text
fenómeno o comando → sensor/interfaz → pin y programa → decisión → actuador o mensaje
                         ↑                         |
                         └──── evidencia Serial ──┘
```

La cadena exacta de hoy se concentra en **registro, marca de tiempo, modo y decisión**. No cambies conexiones basándote solo en este esquema conceptual. Para pines usa el [mapa canónico](../../docs/reference/mapa-conexiones-robot.md); para discrepancias usa la [errata del manual](../../docs/reference/errata-osoyoo.md). Los límites de potencia y la configuración interna del portabaterías siguen `PENDIENTE_DE_VERIFICAR`.

## 7. Seguridad y participación del adulto

- 🟢 El estudiante prepara la predicción, el programa y la tabla de datos.
- 🟡 Un adulto revisa el montaje antes de conectar USB o alimentar sensores.
- 🔴 El adulto corrige cualquier cable, ruta de Serial1 o conexión de potencia. Se cablea únicamente con USB retirado y alimentación apagada.

La actividad comienza sin movimiento. Si una lectura es extraña, no se cambian varios cables a la vez: se apaga, se compara con el mapa canónico y se modifica una sola variable.

## 8. Predice antes de probar

1. ¿Qué esperas observar cuando logres reportar modo, sensores y orden en una línea interpretable y qué mecanismo produciría ese resultado?
2. ¿Qué observación contraria te haría detenerte o revisar la explicación?

Respóndelas en voz alta o en tu cuaderno físico. No necesitas un diario digital.

## 9. Actividad o experimento guiado

1. **Preparar.** Coloca PX-32 estable, identifica HW-003, sensores y confirma con el adulto que la energía está en el estado seguro. Continúa solo si no hay cables sueltos, daño, calor u olor.
2. **Trazar.** Señala la ruta entrada → proceso → salida relacionada con registro, marca de tiempo, modo y decisión. Si no puedes justificar un pin, consulta el mapa; no adivines.
3. **Predecir.** Elige un resultado concreto y una señal de parada. Di qué variable cambiarás y cuáles permanecerán iguales.
4. **Probar.** Vas a emitir registros CSV sin datos personales y comparar con conducta visible. Haz un solo cambio. Observa antes de repetir y mantén accesible la forma de detener la prueba.
5. **Comprobar.** El resultado que permite continuar es: cada movimiento puede explicarse desde el registro correspondiente. Si no aparece, apaga cuando corresponda y pasa a “Si no funciona”.
6. **Repetir.** Realiza una segunda prueba cambiando solo un valor, posición o entrada. Compara, no persigas un resultado “bonito”.
7. **Restaurar.** Detén el programa, apaga la alimentación y devuelve cualquier ajuste temporal a su posición anotada. El adulto confirma que PX-32 conserva su ensamblaje y que ningún cable invade ruedas o engranajes.

## 10. Código

Abre [74-telemetria-integrada.ino](../../code/educational/74-telemetria-integrada/74-telemetria-integrada.ino). Antes de cargarlo, localiza `setup()`, `loop()` y la línea que representa **registro**. Lee el programa de arriba abajo y predice su salida.

```cpp
// Curso PX-32 — programa mínimo de la lección 74
// Cargar solo después de leer la sección de seguridad.
enum Estado { STOP, MANUAL, AUTO };
Estado estado=STOP; unsigned long ultimaOrden=0;
void detener(){ /* escribir aquí las salidas seguras del bloque de movimiento */ }
void setup(){ Serial.begin(9600); detener(); }
void loop(){ if(Serial.available()){ char c=Serial.read(); ultimaOrden=millis(); if(c=='S') estado=STOP; else if(c=='M') estado=MANUAL; else if(c=='A') estado=AUTO; else estado=STOP; } if(millis()-ultimaOrden>500) estado=STOP; if(estado==STOP) detener(); Serial.println(estado); delay(100); }
```

La sintaxis —llaves, paréntesis y punto y coma— permite que el compilador separe instrucciones. El comportamiento es lo que ocurre al ejecutarlas. El propósito de este sketch es aislar la idea de hoy; todavía no es el programa final del robot. No añadas una segunda mejora hasta comprobar la primera.

## 11. Qué deberías observar

El resultado normal es **cada movimiento puede explicarse desde el registro correspondiente**. Puede haber variación por tolerancias, superficie, luz, fricción, carga, eco o tiempos del programa. Una variación pequeña y repetible es información; un salto grande, un reinicio, una lectura imposible o un movimiento inesperado exige STOP.

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

- [Depuración sistemática](../../docs/reference/troubleshooting.md) — Español; referencia interna; 10 min. Aprenderás depuración sistemática. Esencial.
- [Patrones de control no bloqueante](https://docs.arduino.cc/built-in-examples/digital/BlinkWithoutDelay/) — Inglés; ejemplos Arduino; 10 min. Aprenderás patrones de control no bloqueante. Opcional.

Comprueba con un adulto antes de abandonar el material del curso. Un recurso externo amplía la explicación; nunca reemplaza el mapa de conexiones ni las reglas de seguridad de PX-32.

## 15. Cuéntale a papá

- Cuéntale con tus palabras qué significa **registro** y dónde aparece en PX-32.
- Muéstrale la evidencia y explícale qué cambiaste y qué mantuviste igual.
- Pregúntale qué ejemplo parecido conoce fuera de la robótica.
- Explícale un error posible y la prueba pequeña que usarías para localizarlo.
- Dile qué te gustaría probar después y qué regla de seguridad conservarías.

Esto es una conversación, no un examen. Si una explicación se atasca, vuelvan juntos al diagrama entrada → proceso → salida.

## 16. Resumen de la jornada

Hoy aprendiste a **reportar modo, sensores y orden en una línea interpretable** y lo conectaste con **registro, marca de tiempo, modo y decisión**. Pudiste observar cada movimiento puede explicarse desde el registro correspondiente. La regla de seguridad es cambiar conexiones únicamente sin energía y usar `STOP` ante información dudosa. La próxima sesión será la [Lección 75: Proyecto final: tu propio PX-32](75-proyecto-final-tu-propio-px-32.md).
