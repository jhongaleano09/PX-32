# Matriz curricular canónica de PX-32

Esta matriz y [COURSE-MAP.md](../COURSE-MAP.md) usan la misma numeración. `HW-xxx` remite al [diccionario de hardware](hardware/README.md).

| Nº | Concepto | Hardware | Prerrequisito | Evidencia observable |
|---:|---|---|---|---|
| 01 | robot, sistema, entrada, proceso y salida | PX-32 apagado | - | una clasificación razonada y al menos una duda marcada sin adivinar |
| 02 | evidencia, componente y función | HW-001 a HW-020 | 01 | quince identificaciones apoyadas por forma, posición o etiqueta |
| 03 | carga, voltaje, corriente, resistencia, circuito y GND | HW-001, HW-014 a HW-016 | 01-02 | una ruta cerrada coherente y otra abierta que no puede conducir corriente |
| 04 | microcontrolador, memoria, GPIO y señal | HW-001, HW-002 | 02-03 | un mapa funcional de la Mega sin confundirla con el driver de motores |
| 05 | IDE, compilar, placa, puerto y cargar | HW-001, HW-020 | 04 | mensaje de compilación correcta y puerto identificado con una prueba de desconexión |
| 06 | setup, loop, salida digital y delay | HW-001, HW-020 | 05 | un LED que repite el patrón previsto y se detiene al desconectar USB |
| 07 | variable, const, int, asignación y milisegundo | HW-001 | 06 | el mismo algoritmo con ritmos distintos y una explicación de la asignación |
| 08 | Serial, UART, baud rate, print y observabilidad | HW-001, HW-020 | 06-07 | saludo único, cuenta creciente y caracteres correctos cuando coinciden las velocidades |
| 09 | bool, comparación, condición y rama | HW-001 | 07-08 | solo una rama ejecutada en cada vuelta y cambio al alcanzar el límite |
| 10 | bucle, contador, condición y actualización | HW-001 | 09 | cantidad exacta de repeticiones y regreso controlado al inicio |
| 11 | función, parámetro, argumento y retorno | HW-001 | 10 | mismo comportamiento con una estructura más legible y reutilizable |
| 12 | motor DC, campo magnético, par y engranaje | HW-005 | 03,11 | relación visible entre rueda, eje, engranajes y motor sin aplicar energía |
| 13 | driver, señal lógica, potencia y aislamiento funcional | HW-004, HW-005 | 12 | dos rutas distintas que se encuentran en el driver |
| 14 | puente H, polaridad, tabla de verdad y frenado | HW-004 | 13 | cuatro combinaciones clasificadas como giro, parada o condición a evitar |
| 15 | salida digital, habilitación y parada física | HW-001, HW-004, HW-005 | 11,14 | un motor gira menos de un segundo y queda detenido de forma estable |
| 16 | dirección, inversión lógica e invariante de seguridad | HW-004, HW-005 | 15 | giro opuesto sin reconectar potencia ni tocar la rueda |
| 17 | PWM, ciclo de trabajo, frecuencia y velocidad media | HW-004, HW-005 | 16 | tendencia de velocidad creciente, admitiendo umbral de arranque y variaciones mecánicas |
| 18 | motor frontal/trasero, izquierdo/derecho y prueba aislada | HW-004 a HW-006 | 17 | cada orden coincide con la posición canónica o se detiene para revisión adulta |
| 19 | rodillo, fuerza, componente y cancelación | HW-006, HW-017 | 18 | patrón en X compatible con la página 21 del manual |
| 20 | vector, suma, traslación, rotación y STOP | HW-004 a HW-006 | 19 | movimientos reconocibles, baja velocidad y STOP dominante |
| 21 | luz, fuente, propagación y detector | HW-008 | 03,20 | una cadena óptica completa aplicada al sensor IR |
| 22 | onda electromagnética, longitud de onda y frecuencia | HW-008 | 21 | orden correcto y reconocimiento de que son la misma familia física |
| 23 | radiación infrarroja, cercano y cámara | HW-008 | 22 | destellos en la cámara o una limitación del filtro documentada |
| 24 | LED IR, fotodetector, señal y ruido | HW-008 | 23 | componentes diferenciados por función, no solo por aspecto |
| 25 | reflexión, absorción, distancia y material | HW-008 | 24 | cambios de detección que dependen tanto del material como de la distancia |
| 26 | comparador, umbral, entrada analógica y salida digital | HW-008 | 25 | un punto de cambio y posible pequeña zona inestable cerca del umbral |
| 27 | potenciómetro, cursor, calibración y sensibilidad | HW-008 | 26 | umbral desplazado sin forzar el componente y posición inicial recuperable |
| 28 | INPUT, digitalRead, HIGH y LOW | HW-001, HW-008 | 09,27 | cambios 0/1 estables y lógica activa-alta o activa-baja determinada por evidencia |
| 29 | AND, OR, tabla de verdad y combinación | HW-008 x2 | 28 | cuatro patrones asociados a posiciones, sin mover aún el robot |
| 30 | política de control, zona muerta y parada | HW-004 a HW-006, HW-008 | 20,29 | correcciones izquierda/derecha y parada cuando no hay señal fiable |
| 31 | tracker, canal, matriz de sensores y campo de visión | HW-007 | 25,30 | cinco canales localizados sin confundir IR1 con el lado físico no verificado |
| 32 | orden espacial, índice y patrón binario | HW-007 | 31 | cambio en una sola posición del patrón y orden confirmado por el diagrama de página 18 |
| 33 | contraste, umbral, iluminación ambiente y calibración | HW-007 | 27,32 | separación repetible entre superficies en las condiciones reales de la pista |
| 34 | muestreo, patrón y formato | HW-001, HW-007 | 08,33 | patrones legibles que cambian al desplazar manualmente la pista |
| 35 | array, índice, longitud y límite | HW-001, HW-007 | 10,34 | mismo patrón con código más corto y sin acceder fuera de 0..4 |
| 36 | posición, peso, promedio y caso perdido | HW-007 | 35 | estimación con signo y tratamiento explícito del patrón sin línea |
| 37 | política if/else, decisión y separación de responsabilidades | HW-004 a HW-007 | 20,36 | cada patrón produce una sola orden y los ambiguos terminan en STOP |
| 38 | realimentación, corrección y velocidad de prueba | HW-004 a HW-007 | 37 | correcciones frecuentes, velocidad moderada y detención al perder la línea |
| 39 | vibración, medio, compresión y onda | HW-009 | 03,38 | el patrón viaja mientras cada elemento oscila alrededor de su posición |
| 40 | frecuencia, hertz, período y ciclo | HW-009 | 39 | productos frecuencia×período coherentes y unidades correctas |
| 41 | audible, ultrasonido, transductor y 40 kHz | HW-009 | 40 | clasificación correcta sin afirmar que inaudible significa inofensivo en todo contexto |
| 42 | eco, velocidad del sonido, ida y vuelta | HW-009 | 41 | división entre dos justificada geométricamente |
| 43 | pulso, microsegundo, OUTPUT y digitalWrite | HW-001, HW-009 | 06,42 | secuencia LOW-HIGH-LOW correcta; la medición aún no se interpreta |
| 44 | pulseIn, temporización y timeout | HW-001, HW-009 | 43 | duraciones variables con la distancia y cero cuando vence el timeout |
| 45 | unidad, conversión, constante y distancia | HW-009 | 44 | valores cercanos a una referencia, con margen por geometría y ambiente |
| 46 | precisión, exactitud, repetición y mediana | HW-001, HW-009 | 08,45 | variación pequeña, valores atípicos identificados y límites cercanos explicados |
| 47 | servo, ángulo, posición y señal de control | HW-010 | 17,46 | tres posiciones distintas y ausencia de zumbido continuo o golpes |
| 48 | barrido, muestra, ángulo y mapa polar | HW-009, HW-010 | 46-47 | tabla consistente y retorno del sensor al centro |
| 49 | umbral de seguridad, elección y maniobra | HW-004 a HW-006, HW-009, HW-010 | 20,48 | STOP antecede al giro y ninguna lectura ausente autoriza avance |
| 50 | onda de radio, frecuencia, antena y modulación | HW-011 | 22,49 | radio identificada como onda electromagnética que no requiere aire |
| 51 | emisor, receptor, mensaje, canal y protocolo | HW-011 | 50 | cada frontera y formato de mensaje quedan explícitos |
| 52 | Bluetooth, emparejamiento, enlace y alcance | HW-011 | 51 | módulo reconocido o limitación documentada sin cambiar comandos AT |
| 53 | módulo, firmware, zócalo y antena | HW-002, HW-011 | 02,52 | identidad registrada por serigrafía; configuración interna queda sin alterar |
| 54 | UART, trama, baud rate, TX y RX | HW-001, HW-011 | 08,53 | datos legibles solo cuando ambos extremos comparten velocidad y formato |
| 55 | transmisión, recepción, RX1 y TX1 | HW-001, HW-002, HW-011 | 54 | rutas cruzadas correctas sin coexistencia con E_TX/E_RX |
| 56 | byte, carácter, available y read | HW-011 | 55 | una letra por mensaje y ninguna acción motriz todavía |
| 57 | comando, despacho, watchdog y STOP | HW-004 a HW-006, HW-011 | 20,56 | S, comando desconocido y timeout siempre producen detención |
| 58 | WLAN, enlace, infraestructura y alcance | HW-003, HW-011 | 52,57 | decisiones justificadas por arquitectura, no solo por distancia |
| 59 | SoC, firmware AT, antena y coprocesador | HW-002, HW-003 | 58 | Mega como programa principal y ESP como interfaz de red en este montaje |
| 60 | red, nodo, enlace, paquete y topología | HW-003 | 59 | nodos y enlaces diferenciados; Internet no se supone necesario para control local |
| 61 | router, punto de acceso, cliente y puerta de enlace | HW-003 | 60 | ruta lógica correcta y límites entre Wi-Fi local e Internet |
| 62 | SSID, contraseña, secreto y archivo ignorado | HW-003 | 61 | ninguna credencial, ubicación ni IP pública queda en archivos rastreados |
| 63 | IP privada, DHCP, puerto y dirección | HW-003 | 61-62 | dirección privada reconocida como identificador local temporal |
| 64 | cliente, servidor, datagrama, UDP y puerto | HW-003 | 63 | mensaje recibido completo o pérdida tolerada sin efecto peligroso |
| 65 | modo STA, asociación, timeout y reintento | HW-002, HW-003 | 62-64 | respuesta de asociación o fallo seguro con tiempo límite |
| 66 | validación, comando, origen y caducidad | HW-003 a HW-006 | 57,65 | solo comandos válidos y recientes pueden solicitar movimiento |
| 67 | telemetría, estado, muestreo y tasa | HW-003, sensores | 46,66 | mensajes legibles a ritmo moderado y sin datos personales |
| 68 | estado, transición, evento y máquina de estados | HW-001 | 57,67 | ningún evento ambiguo sale de STOP y cada transición es explicable |
| 69 | prioridad, interbloqueo, fallo seguro y arbitraje | HW-004 a HW-010 | 49,68 | STOP domina MANUAL/AUTO y sensor inválido se trata como riesgo |
| 70 | radar como analogía, barrido, tabla y visualización | HW-009, HW-010 | 48 | perfil angular repetible y explicación de resolución/tiempo |
| 71 | consigna, error, tolerancia y control proporcional simple | HW-004 a HW-006, HW-009 | 49,69 | avance lejos, STOP dentro de banda y retroceso solo bajo condiciones verificadas |
| 72 | estrategia, heurística, memoria y callejón sin salida | HW-004 a HW-006, HW-009, HW-010 | 49,68 | decisiones consistentes y recuperación mediante STOP/retroceso limitado |
| 73 | fusión de sensores, prioridad y comportamiento compuesto | HW-004 a HW-010 | 38,49,69 | ultrasonido domina el seguimiento y la línea nunca anula STOP |
| 74 | registro, marca de tiempo, modo y decisión | HW-003, sensores | 67,73 | cada movimiento puede explicarse desde el registro correspondiente |
| 75 | requisito, prototipo, prueba, evidencia e iteración | Según el diseño aprobado | 68-74 | proyecto reproducible que entra en STOP ante pérdida de señal o dato inseguro |
