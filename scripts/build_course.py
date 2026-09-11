#!/usr/bin/env python3
"""Construye la ruta curricular canónica de 75 lecciones de PX-32.

El contenido se genera desde metadatos explícitos para mantener numeración, enlaces,
prerrequisitos, seguridad y nombres de sketches sincronizados.
"""
from pathlib import Path
import re
import shutil

ROOT = Path(__file__).resolve().parents[1]

BLOCKS = {
    range(1, 5): ("00-fundamentos", "Fundamentos"),
    range(5, 12): ("01-programacion", "Programación"),
    range(12, 21): ("02-movimiento", "Movimiento"),
    range(21, 31): ("03-infrarrojo", "Infrarrojo"),
    range(31, 39): ("04-line-tracking", "Seguimiento de línea"),
    range(39, 50): ("05-ultrasonido", "Ultrasonido y servo"),
    range(50, 58): ("06-bluetooth", "Bluetooth"),
    range(58, 68): ("07-wifi-iot", "Wi-Fi e IoT"),
    range(68, 76): ("08-integracion", "Integración"),
}

RAW = r"""
01|¿Qué es un robot?|robot, sistema, entrada, proceso y salida|explicar por qué PX-32 es un robot y clasificar seis piezas por su función|-|PX-32 apagado|recorrer visualmente el robot y construir una cadena sensor → programa → actuador|una clasificación razonada y al menos una duda marcada sin adivinar
02|Inventario razonado de PX-32|evidencia, componente y función|identificar los componentes principales sin desmontar el robot|01|HW-001 a HW-020|comparar el montaje con el diccionario de hardware y localizar quince elementos|quince identificaciones apoyadas por forma, posición o etiqueta
03|Electricidad sin misterios|carga, voltaje, corriente, resistencia, circuito y GND|explicar un circuito abierto y uno cerrado sin energizar PX-32|01-02|HW-001, HW-014 a HW-016|representar con tarjetas una ruta de energía completa y luego interrumpirla|una ruta cerrada coherente y otra abierta que no puede conducir corriente
04|La Mega2560: una computadora pequeña|microcontrolador, memoria, GPIO y señal|seguir una señal desde un pin de entrada hasta una salida|02-03|HW-001, HW-002|localizar alimentación, USB, pines digitales, analógicos y recorrer entrada-proceso-salida|un mapa funcional de la Mega sin confundirla con el driver de motores
05|Preparar Arduino IDE|IDE, compilar, placa, puerto y cargar|configurar Arduino IDE 2 y verificar un programa sin mover el robot|04|HW-001, HW-020|seleccionar Mega 2560, identificar el puerto y compilar Blink|mensaje de compilación correcta y puerto identificado con una prueba de desconexión
06|Primer programa: Blink|setup, loop, salida digital y delay|modificar y cargar un parpadeo en el LED integrado|05|HW-001, HW-020|comparar intervalos de 1000, 500 y 100 ms|un LED que repite el patrón previsto y se detiene al desconectar USB
07|Variables para representar tiempo|variable, const, int, asignación y milisegundo|controlar el ritmo del LED cambiando un único valor|06|HW-001|usar una constante de intervalo y comparar tres valores|el mismo algoritmo con ritmos distintos y una explicación de la asignación
08|PX-32 aprende a hablarnos|Serial, UART, baud rate, print y observabilidad|mostrar texto y números internos en el monitor serie|06-07|HW-001, HW-020|enviar un saludo y un contador por USB a 9600 baudios|saludo único, cuenta creciente y caracteres correctos cuando coinciden las velocidades
09|Decisiones con if y else|bool, comparación, condición y rama|hacer que el programa elija entre dos mensajes|07-08|HW-001|comparar un contador con un límite e imprimir antes/después|solo una rama ejecutada en cada vuelta y cambio al alcanzar el límite
10|Repeticiones contadas con for|bucle, contador, condición y actualización|producir grupos exactos de destellos sin copiar instrucciones|09|HW-001|programar tres grupos de 2, 4 y 6 destellos|cantidad exacta de repeticiones y regreso controlado al inicio
11|Funciones: enseñar una acción reutilizable|función, parámetro, argumento y retorno|crear y explicar parpadear(veces, intervalo)|10|HW-001|reemplazar bloques repetidos por llamadas a una función|mismo comportamiento con una estructura más legible y reutilizable
12|Del electrón al giro: motor DC|motor DC, campo magnético, par y engranaje|explicar cómo un motor convierte energía eléctrica en movimiento|03,11|HW-005|observar motor y reductora con PX-32 apagado y girar suavemente una rueda|relación visible entre rueda, eje, engranajes y motor sin aplicar energía
13|Por qué existe el driver Model Y|driver, señal lógica, potencia y aislamiento funcional|trazar por separado la ruta de orden y la ruta de energía|12|HW-004, HW-005|seguir en el diagrama Mega → Model Y → motor y portabaterías → Model Y → motor|dos rutas distintas que se encuentran en el driver
14|Puente H: cambiar la polaridad|puente H, polaridad, tabla de verdad y frenado|predecir el sentido de un motor usando dos entradas lógicas|13|HW-004|completar una tabla IN1/IN2 sin energizar y detectar el estado prohibido por prudencia|cuatro combinaciones clasificadas como giro, parada o condición a evitar
15|Primera prueba de un motor|salida digital, habilitación y parada física|hacer girar brevemente un motor con las ruedas elevadas y parada conocida|11,14|HW-001, HW-004, HW-005|cargar un pulso corto de avance seguido de STOP bajo control adulto|un motor gira menos de un segundo y queda detenido de forma estable
16|Invertir el sentido por software|dirección, inversión lógica e invariante de seguridad|invertir un motor sin cambiar cables|15|HW-004, HW-005|alternar IN1/IN2 con pausa completa entre sentidos|giro opuesto sin reconectar potencia ni tocar la rueda
17|PWM: regular energía en el tiempo|PWM, ciclo de trabajo, frecuencia y velocidad media|comparar tres niveles de mando sin afirmar una velocidad exacta|16|HW-004, HW-005|aplicar 80, 140 y 200 en un pin PWM con pausas|tendencia de velocidad creciente, admitiendo umbral de arranque y variaciones mecánicas
18|Cuatro motores, cuatro identidades|motor frontal/trasero, izquierdo/derecho y prueba aislada|verificar qué conector corresponde a cada rueda|17|HW-004 a HW-006|activar una rueda por vez con pulsos breves y completar el mapa BK1/BK3/AK1/AK3|cada orden coincide con la posición canónica o se detiene para revisión adulta
19|Ruedas Mecanum y fuerzas diagonales|rodillo, fuerza, componente y cancelación|predecir hacia dónde empuja cada rueda Mecanum|18|HW-006, HW-017|dibujar flechas sobre una foto y comparar orientación física de las cuatro ruedas|patrón en X compatible con la página 21 del manual
20|Vectores para mover PX-32|vector, suma, traslación, rotación y STOP|ejecutar de forma segura avance, retroceso, laterales y giros|19|HW-004 a HW-006|probar seis movimientos con ruedas elevadas y luego dos en piso despejado|movimientos reconocibles, baja velocidad y STOP dominante
21|La luz transporta energía|luz, fuente, propagación y detector|relacionar luz con información sin asumir que toda luz es visible|03,20|HW-008|comparar fuente, trayecto, objeto y receptor en un diagrama|una cadena óptica completa aplicada al sensor IR
22|El espectro electromagnético|onda electromagnética, longitud de onda y frecuencia|ordenar radio, infrarrojo, visible, ultravioleta y rayos X|21|HW-008|construir una escala relativa de bandas sin confundir energía con brillo|orden correcto y reconocimiento de que son la misma familia física
23|Infrarrojo: luz que no vemos|radiación infrarroja, cercano y cámara|mostrar una evidencia indirecta de emisión IR de un control remoto|22|HW-008|observar un control remoto con cámara compatible y comparar con el ojo|destellos en la cámara o una limitación del filtro documentada
24|Emisor y receptor infrarrojos|LED IR, fotodetector, señal y ruido|identificar qué parte emite y cuál recibe en un sensor de obstáculos|23|HW-008|inspeccionar las dos cápsulas y seguir su ruta hasta OUT|componentes diferenciados por función, no solo por aspecto
25|Reflexión y absorción|reflexión, absorción, distancia y material|comparar cómo distintas superficies devuelven infrarrojo|24|HW-008|acercar cartón blanco, negro y metal sin mover el ajuste|cambios de detección que dependen tanto del material como de la distancia
26|LM393: convertir una señal en decisión|comparador, umbral, entrada analógica y salida digital|explicar cómo una variación continua se transforma en 0 o 1|25|HW-008|observar LED/OUT al cruzar lentamente la distancia de detección|un punto de cambio y posible pequeña zona inestable cerca del umbral
27|El potenciómetro ajusta el umbral|potenciómetro, cursor, calibración y sensibilidad|calibrar un sensor IR para una distancia objetivo con ayuda adulta|26|HW-008|marcar posición inicial y girar muy poco el tornillo de ajuste|umbral desplazado sin forzar el componente y posición inicial recuperable
28|Leer un sensor IR por un pin digital|INPUT, digitalRead, HIGH y LOW|mostrar en Serial el estado del sensor izquierdo conectado a D3|09,27|HW-001, HW-008|leer D3, acercar y retirar un objeto y registrar la lógica real|cambios 0/1 estables y lógica activa-alta o activa-baja determinada por evidencia
29|Dos sensores, cuatro situaciones|AND, OR, tabla de verdad y combinación|interpretar conjuntamente los sensores de D3 y D2|28|HW-008 x2|registrar libre, izquierda, derecha y ambos frente a un objeto|cuatro patrones asociados a posiciones, sin mover aún el robot
30|Seguir una mano con prudencia|política de control, zona muerta y parada|combinar dos IR con movimiento lento y STOP seguro|20,29|HW-004 a HW-006, HW-008|probar primero órdenes impresas, luego pulsos de movimiento con ruedas elevadas|correcciones izquierda/derecha y parada cuando no hay señal fiable
31|Anatomía del tracker de cinco canales|tracker, canal, matriz de sensores y campo de visión|explicar por qué cinco mediciones ofrecen más información que una|25,30|HW-007|identificar los cinco pares ópticos y su orden sobre el robot apagado|cinco canales localizados sin confundir IR1 con el lado físico no verificado
32|IR1 a IR5: un mapa espacial|orden espacial, índice y patrón binario|relacionar cada canal con A4, A3, A2, A1 y A0|31|HW-007|cubrir un canal por vez y construir el patrón de cinco posiciones|cambio en una sola posición del patrón y orden confirmado por el diagrama de página 18
33|Calibrar negro y blanco|contraste, umbral, iluminación ambiente y calibración|comparar lecturas sobre pista clara y línea oscura|27,32|HW-007|medir a altura fija negro/blanco y ajustar solo si es necesario|separación repetible entre superficies en las condiciones reales de la pista
34|Leer cinco sensores sin perderse|muestreo, patrón y formato|imprimir una lectura como 00100 en el monitor serie|08,33|HW-001, HW-007|leer A4 a A0 y formar una línea de cinco dígitos|patrones legibles que cambian al desplazar manualmente la pista
35|Arrays: cinco datos bajo un nombre|array, índice, longitud y límite|recorrer los cinco pines con un bucle for|10,34|HW-001, HW-007|sustituir cinco variables repetidas por arrays de pines y lecturas|mismo patrón con código más corto y sin acceder fuera de 0..4
36|Estimar dónde está la línea|posición, peso, promedio y caso perdido|convertir un patrón de sensores en izquierda, centro o derecha|35|HW-007|asignar pesos -2,-1,0,1,2 y calcular una posición cuando hay detecciones|estimación con signo y tratamiento explícito del patrón sin línea
37|De la medición a la orden|política if/else, decisión y separación de responsabilidades|imprimir AVANZA, CORRIGE o STOP sin mover motores|20,36|HW-004 a HW-007|alimentar al programa patrones de prueba y revisar la orden elegida|cada patrón produce una sola orden y los ambiguos terminan en STOP
38|Hito: seguir una línea|realimentación, corrección y velocidad de prueba|seguir una pista corta con baja velocidad y recuperar STOP|37|HW-004 a HW-007|ensayar con ruedas elevadas, luego en una pista de 20–30 mm y área libre|correcciones frecuentes, velocidad moderada y detención al perder la línea
39|El sonido es una onda mecánica|vibración, medio, compresión y onda|explicar por qué el sonido necesita materia para propagarse|03,38|HW-009|modelar un pulso y su propagación con una fila de objetos o personas|el patrón viaja mientras cada elemento oscila alrededor de su posición
40|Frecuencia y período|frecuencia, hertz, período y ciclo|relacionar ciclos por segundo con duración de cada ciclo|39|HW-009|calcular períodos sencillos para 1, 2, 10 y 40 000 Hz|productos frecuencia×período coherentes y unidades correctas
41|Ultrasonido: más allá del oído|audible, ultrasonido, transductor y 40 kHz|clasificar frecuencias y explicar por qué PX-32 usa ultrasonido|40|HW-009|ubicar 40 kHz respecto al rango auditivo humano aproximado|clasificación correcta sin afirmar que inaudible significa inofensivo en todo contexto
42|Eco y tiempo de vuelo|eco, velocidad del sonido, ida y vuelta|deducir por qué la distancia es recorrido total dividido entre dos|41|HW-009|resolver trayectos dibujados de sensor a pared y regreso|división entre dos justificada geométricamente
43|TRIG: enviar un pulso breve|pulso, microsegundo, OUTPUT y digitalWrite|generar un pulso de 10 µs en D30|06,42|HW-001, HW-009|examinar y cargar el pulso con el robot inmóvil|secuencia LOW-HIGH-LOW correcta; la medición aún no se interpreta
44|ECHO: medir una duración|pulseIn, temporización y timeout|medir en D31 cuánto dura el eco sin bloquear indefinidamente|43|HW-001, HW-009|usar pulseIn con tiempo límite y mostrar microsegundos|duraciones variables con la distancia y cero cuando vence el timeout
45|De microsegundos a centímetros|unidad, conversión, constante y distancia|convertir duración de eco en una estimación de distancia|44|HW-009|aplicar distancia = duración×0,0343/2 y revisar unidades|valores cercanos a una referencia, con margen por geometría y ambiente
46|Medir objetos conocidos|precisión, exactitud, repetición y mediana|evaluar la calidad de varias mediciones ultrasónicas|08,45|HW-001, HW-009|medir tres distancias conocidas cinco veces cada una|variación pequeña, valores atípicos identificados y límites cercanos explicados
47|Un servo apunta el sensor|servo, ángulo, posición y señal de control|mover el MG90 a 45°, 90° y 135° sin forzar topes|17,46|HW-010|cargar posiciones con pausa y verificar orientación física|tres posiciones distintas y ausencia de zumbido continuo o golpes
48|Escaneo espacial|barrido, muestra, ángulo y mapa polar|medir derecha, centro e izquierda con servo y ultrasonido|46-47|HW-009, HW-010|mover, esperar asentamiento, medir y guardar tres pares ángulo-distancia|tabla consistente y retorno del sensor al centro
49|Evitar obstáculos|umbral de seguridad, elección y maniobra|detenerse, observar y escoger un lado libre antes de avanzar|20,48|HW-004 a HW-006, HW-009, HW-010|simular decisiones por Serial y luego probar a baja velocidad|STOP antecede al giro y ninguna lectura ausente autoriza avance
50|Radio: otra región del espectro|onda de radio, frecuencia, antena y modulación|comparar radio, infrarrojo y luz visible sin confundirlas con sonido|22,49|HW-011|ordenar casos de comunicación por medio físico y alcance|radio identificada como onda electromagnética que no requiere aire
51|Todo enlace necesita un protocolo|emisor, receptor, mensaje, canal y protocolo|dibujar una comunicación completa e identificar posibles errores|50|HW-011|representar teléfono → radio → HC-02 → UART → Mega|cada frontera y formato de mensaje quedan explícitos
52|Qué hace Bluetooth|Bluetooth, emparejamiento, enlace y alcance|explicar qué resuelve Bluetooth antes de abrir una aplicación|51|HW-011|identificar dispositivo, emparejar con adulto y observar estado sin mover el robot|módulo reconocido o limitación documentada sin cambiar comandos AT
53|Conocer el HC-02 y su zócalo|módulo, firmware, zócalo y antena|identificar el HC-02 sin confundirlo con la imagen errónea de HC-05|02,52|HW-002, HW-011|comparar placa física, ficha y página 45 con alimentación apagada|identidad registrada por serigrafía; configuración interna queda sin alterar
54|UART: hablar por turnos y a la misma velocidad|UART, trama, baud rate, TX y RX|distinguir Serial USB de Serial1 del módulo inalámbrico|08,53|HW-001, HW-011|hacer un puente lógico de caracteres entre Serial y Serial1|datos legibles solo cuando ambos extremos comparten velocidad y formato
55|TX y RX se cruzan|transmisión, recepción, RX1 y TX1|trazar B_TX→D19/RX1 y B_RX←D18/TX1|54|HW-001, HW-002, HW-011|inspeccionar el cableado apagado y seguir ambas flechas|rutas cruzadas correctas sin coexistencia con E_TX/E_RX
56|Recibir una letra|byte, carácter, available y read|mostrar por USB cada carácter recibido desde Bluetooth|55|HW-011|enviar letras inocuas y observar su código/representación|una letra por mensaje y ninguna acción motriz todavía
57|Control Bluetooth con parada dominante|comando, despacho, watchdog y STOP|interpretar F/B/L/R/S con parada ante silencio o dato inválido|20,56|HW-004 a HW-006, HW-011|probar primero con motores deshabilitados y luego en área libre|S, comando desconocido y timeout siempre producen detención
58|Wi-Fi y Bluetooth no son lo mismo|WLAN, enlace, infraestructura y alcance|elegir la tecnología adecuada para tres situaciones|52,57|HW-003, HW-011|comparar conexión directa, red local y acceso mediante router|decisiones justificadas por arquitectura, no solo por distancia
59|El ESP8266/ESP-12S|SoC, firmware AT, antena y coprocesador|explicar el papel del ESP8266 frente a la Mega2560|58|HW-002, HW-003|localizar antena, módulo y ruta E con todo apagado|Mega como programa principal y ESP como interfaz de red en este montaje
60|Una red está hecha de nodos y enlaces|red, nodo, enlace, paquete y topología|dibujar la red local sin incluir datos privados|59|HW-003|representar PX-32, router y computador con flechas de paquetes|nodos y enlaces diferenciados; Internet no se supone necesario para control local
61|El router organiza la red local|router, punto de acceso, cliente y puerta de enlace|describir cómo PX-32 se une a una red doméstica|60|HW-003|seguir un paquete local desde controlador hasta robot|ruta lógica correcta y límites entre Wi-Fi local e Internet
62|SSID y credenciales seguras|SSID, contraseña, secreto y archivo ignorado|preparar un ejemplo de configuración sin versionar datos reales|61|HW-003|usar MI_RED y NO_ES_UNA_CLAVE_REAL y revisar .gitignore|ninguna credencial, ubicación ni IP pública queda en archivos rastreados
63|Direcciones IP y DHCP|IP privada, DHCP, puerto y dirección|leer e interpretar una IP privada asignada al módulo|61-62|HW-003|consultar estado AT y distinguir dirección del dispositivo y puerto|dirección privada reconocida como identificador local temporal
64|Cliente, servidor y UDP|cliente, servidor, datagrama, UDP y puerto|explicar el recorrido de un comando UDP local|63|HW-003|enviar un mensaje de prueba sin motores y observarlo por Serial|mensaje recibido completo o pérdida tolerada sin efecto peligroso
65|Conectar en modo estación|modo STA, asociación, timeout y reintento|conectar el ESP a un router con credenciales fuera del repositorio|62-64|HW-002, HW-003|activar la ruta E en lugar de B y ejecutar una secuencia AT supervisada|respuesta de asociación o fallo seguro con tiempo límite
66|Comandos Wi-Fi seguros|validación, comando, origen y caducidad|aplicar F/B/L/R/S recibidos por red con las mismas reglas de STOP|57,65|HW-003 a HW-006|probar parser con motores deshabilitados y añadir timeout|solo comandos válidos y recientes pueden solicitar movimiento
67|Telemetría: el robot informa|telemetría, estado, muestreo y tasa|enviar distancia o modo sin saturar la red|46,66|HW-003, sensores|crear un registro periódico MODO,DISTANCIA,STOP|mensajes legibles a ritmo moderado y sin datos personales
68|Pensar en modos y estados|estado, transición, evento y máquina de estados|modelar STOP, MANUAL y AUTO con transiciones explícitas|57,67|HW-001|simular eventos por Serial y mostrar el estado actual|ningún evento ambiguo sale de STOP y cada transición es explicable
69|La seguridad tiene prioridad|prioridad, interbloqueo, fallo seguro y arbitraje|hacer que un obstáculo anule una orden de avance|49,68|HW-004 a HW-010|inyectar combinaciones de orden y distancia antes de mover|STOP domina MANUAL/AUTO y sensor inválido se trata como riesgo
70|Radar ultrasónico|radar como analogía, barrido, tabla y visualización|construir un mapa angular de distancias sin llamarlo radar físico exacto|48|HW-009, HW-010|barrer 30°–150° por pasos y transmitir pares por Serial|perfil angular repetible y explicación de resolución/tiempo
71|Estacionamiento por distancia|consigna, error, tolerancia y control proporcional simple|mantener una separación objetivo con pulsos cortos|49,69|HW-004 a HW-006, HW-009|simular error y después acercarse lentamente a un objeto ancho|avance lejos, STOP dentro de banda y retroceso solo bajo condiciones verificadas
72|Navegar un laberinto|estrategia, heurística, memoria y callejón sin salida|elegir una dirección usando medidas izquierda-centro-derecha|49,68|HW-004 a HW-006, HW-009, HW-010|resolver primero un laberinto de papel y luego un tramo físico simple|decisiones consistentes y recuperación mediante STOP/retroceso limitado
73|Línea con obstáculos|fusión de sensores, prioridad y comportamiento compuesto|seguir la línea pero detenerse ante un obstáculo|38,49,69|HW-004 a HW-010|probar cada subsistema y luego una secuencia obstáculo→STOP→reanudar|ultrasonido domina el seguimiento y la línea nunca anula STOP
74|Telemetría integrada|registro, marca de tiempo, modo y decisión|reportar modo, sensores y orden en una línea interpretable|67,73|HW-003, sensores|emitir registros CSV sin datos personales y comparar con conducta visible|cada movimiento puede explicarse desde el registro correspondiente
75|Proyecto final: tu propio PX-32|requisito, prototipo, prueba, evidencia e iteración|diseñar, probar y presentar una función integrada segura|68-74|Según el diseño aprobado|definir criterios, construir en pasos, probar fallos y hacer una demostración conversada|proyecto reproducible que entra en STOP ante pérdida de señal o dato inseguro
"""

def block_for(n):
    for nums, data in BLOCKS.items():
        if n in nums:
            return data
    raise KeyError(n)

def slugify(text):
    table = str.maketrans("áéíóúüñ¿¡", "aeiouun  ")
    s = text.lower().translate(table)
    s = re.sub(r"[^a-z0-9]+", "-", s).strip("-")
    return s

LESSONS=[]
for line in RAW.strip().splitlines():
    n,title,concept,mission,pre,hw,activity,observe=line.split("|")
    LESSONS.append(dict(n=int(n), title=title, concept=concept, mission=mission,
                        pre=pre, hw=hw, activity=activity, observe=observe))

RESOURCES = {
    "Fundamentos": [("Inglés", "lectura oficial", "10 min", "Arduino: introducción y placa Mega", "https://docs.arduino.cc/hardware/mega-2560/"),
                    ("Español", "lectura", "8 min", "Qué es la electricidad, lectura interna", "../../docs/readings/que-es-electricidad.md")],
    "Programación": [("Inglés", "referencia oficial", "10 min", "Estructura y lenguaje de Arduino", "https://docs.arduino.cc/language-reference/"),
                     ("Inglés", "tutorial oficial", "10 min", "Ejemplos integrados de Arduino", "https://docs.arduino.cc/built-in-examples/")],
    "Movimiento": [("Inglés", "manual del fabricante", "5-10 min", "Conexiones verificadas de Model Y y motores", "../../reference/original/osoyoo-mecanum-wheel-robotic-car-kit-v2.pdf"),
                   ("Español", "referencia interna", "8 min", "Mapa canónico de conexiones", "../../docs/reference/mapa-conexiones-robot.md")],
    "Infrarrojo": [("Inglés", "lectura NASA", "8 min", "El espectro electromagnético y el infrarrojo", "https://science.nasa.gov/ems/07_infraredwaves/"),
                   ("Español", "referencia interna", "6 min", "Sensores de PX-32", "../../docs/reference/sensores.md")],
    "Seguimiento de línea": [("Inglés", "manual del fabricante", "8 min", "Diagrama correcto del tracker de cinco canales", "../../assets/osoyoo-manual/pagina-18-pinout-tracker-correcto.png"),
                            ("Español", "referencia interna", "8 min", "Erratas y decisión canónica IR1–IR5", "../../docs/reference/errata-osoyoo.md")],
    "Ultrasonido y servo": [("Inglés", "libro abierto", "12 min", "Velocidad, frecuencia y longitud de onda del sonido", "https://openstax.org/books/physics/pages/14-1-speed-of-sound-frequency-and-wavelength"),
                            ("Inglés", "referencia oficial Arduino", "10 min", "Biblioteca Servo", "https://docs.arduino.cc/libraries/servo/")],
    "Bluetooth": [("Inglés", "explicación oficial", "8 min", "Conceptos básicos de Bluetooth", "https://www.bluetooth.com/learn-about-bluetooth/tech-overview/"),
                  ("Español", "referencia interna", "8 min", "UART y protocolos de PX-32", "../../docs/reference/protocolos.md")],
    "Wi-Fi e IoT": [("Inglés", "documentación del fabricante", "10 min", "ESP8266 y comandos AT", "https://docs.espressif.com/projects/esp-at/en/release-v2.2.0.0_esp8266/"),
                    ("Español", "referencia interna", "8 min", "Privacidad y conexión Serial1", "../../docs/reference/seguridad.md")],
    "Integración": [("Español", "referencia interna", "10 min", "Depuración sistemática", "../../docs/reference/troubleshooting.md"),
                   ("Inglés", "ejemplos Arduino", "10 min", "Patrones de control no bloqueante", "https://docs.arduino.cc/built-in-examples/digital/BlinkWithoutDelay/")],
}

STAGE_EXPLANATIONS = {
"Fundamentos": "En esta etapa miramos el robot como un sistema. La energía hace posibles los cambios; las señales representan información; y el programa organiza acciones. Conviene mantener separadas esas tres ideas. Un cable de potencia no es una instrucción, una lectura de sensor no es todavía una decisión y una placa electrónica no conoce por sí sola el propósito del proyecto.",
"Programación": "Programar es escribir una descripción precisa de un comportamiento para que una máquina pueda ejecutarlo. La computadora no completa intenciones ocultas: sigue sintaxis y reglas. Por eso leeremos cada programa en tres capas: qué signos exige el lenguaje, qué ocurre al ejecutarlo y para qué sirve dentro de PX-32. Los errores serán evidencia para localizar una diferencia entre lo escrito y lo esperado.",
"Movimiento": "Mover un robot exige coordinar lógica y potencia. La Mega produce señales pequeñas; el Model Y dirige energía hacia los motores; los engranajes cambian velocidad por par; y las ruedas Mecanum convierten giros en fuerzas oblicuas. Esta separación protege la placa y ayuda a depurar: primero se comprueba la orden, luego el canal de potencia y por último el resultado mecánico.",
"Infrarrojo": "Un sensor infrarrojo no ve objetos como un ojo. Emite o recibe radiación y transforma una interacción física en una señal eléctrica. Superficie, ángulo, distancia, iluminación y umbral pueden cambiar la lectura. Por eso una detección es una medición bajo condiciones concretas, no una verdad universal sobre el mundo.",
"Seguimiento de línea": "Cinco sensores producen un patrón espacial. El reto ya no es leer un 0 o un 1, sino interpretar una combinación, estimar dónde está la línea y elegir una corrección. Mantendremos separadas medición, interpretación y movimiento para poder probar cada capa sin que una rueda oculte un error de software.",
"Ultrasonido y servo": "El módulo ultrasónico estima distancia midiendo tiempo, no extendiendo una regla invisible. Envía una onda, espera un eco y usa la velocidad aproximada del sonido. El servo añade dirección y convierte una medición puntual en un pequeño mapa. Toda estimación tiene límites: objetos blandos, inclinados, muy cercanos o estrechos pueden devolver ecos débiles.",
"Bluetooth": "Comunicar requiere un emisor, un receptor, un canal y reglas compartidas. Bluetooth transporta datos por radio; UART entrega bytes entre el módulo y la Mega. Son capas diferentes. Una letra recibida tampoco es aún una orden segura: debe validarse, traducirse y caducar si deja de llegar comunicación.",
"Wi-Fi e IoT": "Wi-Fi conecta nodos mediante una red local. El ESP8266 maneja el enlace y la Mega conserva la lógica educativa del robot. Direcciones, puertos y protocolos permiten que los mensajes lleguen al proceso correcto. Las credenciales son secretos operativos: se usan localmente, pero nunca se escriben en el material versionado.",
"Integración": "Integrar no significa pegar programas completos. Significa definir estados, prioridades e interfaces para que varios subsistemas cooperen. La regla rectora es que STOP domina cualquier modo. Cada comportamiento complejo se construye verificando primero entradas, luego decisiones y finalmente salidas, con fallos simulados antes de la demostración física.",
}

CODE_LESSONS = set(range(6,12)) | set(range(15,21)) | set(range(28,31)) | set(range(34,39)) | set(range(43,50)) | set(range(54,58)) | set(range(63,76))

def sketch(n, slug):
    common = """// Curso PX-32 — programa mínimo de la lección {n:02d}\n// Cargar solo después de leer la sección de seguridad.\n""".format(n=n)
    motor_api="""const byte EN[4]={9,10,11,12};
const byte P1[4]={22,26,5,7};
const byte P2[4]={24,28,6,8};
// Orden: frontal derecha, frontal izquierda, trasera derecha, trasera izquierda.
void rueda(byte i,int sentido,byte pwm){
  digitalWrite(P1[i],sentido>0?HIGH:LOW);
  digitalWrite(P2[i],sentido<0?HIGH:LOW);
  analogWrite(EN[i],sentido==0?0:pwm);
}
void parar(){ for(byte i=0;i<4;i++) rueda(i,0,0); }
void mover(int fd,int fi,int td,int ti,byte pwm){
  int s[4]={fd,fi,td,ti}; for(byte i=0;i<4;i++) rueda(i,s[i],pwm);
}
void prepararMotores(){ for(byte i=0;i<4;i++){ pinMode(EN[i],OUTPUT); pinMode(P1[i],OUTPUT); pinMode(P2[i],OUTPUT); } parar(); }
"""
    if n == 6:
        body="const byte LED = LED_BUILTIN;\nvoid setup() { pinMode(LED, OUTPUT); }\nvoid loop() { digitalWrite(LED,HIGH); delay(500); digitalWrite(LED,LOW); delay(500); }\n"
    elif n == 7:
        body="const byte LED = LED_BUILTIN;\nconst unsigned long INTERVALO_MS = 500;\nvoid setup(){ pinMode(LED,OUTPUT); }\nvoid loop(){ digitalWrite(LED,HIGH); delay(INTERVALO_MS); digitalWrite(LED,LOW); delay(INTERVALO_MS); }\n"
    elif n == 8:
        body="unsigned long cuenta=0;\nvoid setup(){ Serial.begin(9600); Serial.println(\"Hola, soy PX-32\"); }\nvoid loop(){ Serial.print(\"Cuenta: \" ); Serial.println(cuenta++); delay(1000); }\n"
    elif n == 9:
        body="int cuenta=0;\nvoid setup(){ Serial.begin(9600); }\nvoid loop(){ bool alcanzo = cuenta >= 5; if(alcanzo){ Serial.println(\"LIMITE\"); } else { Serial.println(\"ANTES\"); } cuenta++; delay(500); }\n"
    elif n == 10:
        body="void setup(){ pinMode(LED_BUILTIN,OUTPUT); }\nvoid loop(){ for(int i=0;i<4;i++){ digitalWrite(LED_BUILTIN,HIGH); delay(150); digitalWrite(LED_BUILTIN,LOW); delay(150); } delay(1500); }\n"
    elif n == 11:
        body="void parpadear(int veces,int intervalo){ for(int i=0;i<veces;i++){ digitalWrite(LED_BUILTIN,HIGH); delay(intervalo); digitalWrite(LED_BUILTIN,LOW); delay(intervalo); } }\nvoid setup(){ pinMode(LED_BUILTIN,OUTPUT); }\nvoid loop(){ parpadear(3,200); delay(1500); }\n"
    elif n == 18:
        body=motor_api+"void setup(){ prepararMotores(); delay(2000); for(byte i=0;i<4;i++){ rueda(i,1,70); delay(400); parar(); delay(700); } }\nvoid loop(){ parar(); }\n"
    elif n == 19:
        body="void setup(){ Serial.begin(9600); Serial.println(\"Dibuja las cuatro fuerzas; no hace falta energizar motores\"); }\nvoid loop(){}\n"
    elif n == 20:
        body=motor_api+"""void paso(const char* nombre,int fd,int fi,int td,int ti){
  Serial.println(nombre); mover(fd,fi,td,ti,70); delay(500); parar(); delay(1000);
}
void setup(){ Serial.begin(9600); prepararMotores(); delay(3000);
  // +1/-1 son sentidos lógicos. Confirma en L18 cuál corresponde al avance físico.
  paso("PATRON 1",+1,+1,+1,+1); paso("PATRON 2",-1,-1,-1,-1);
  paso("PATRON 3",+1,-1,-1,+1); paso("PATRON 4",-1,+1,+1,-1);
  paso("PATRON 5",-1,+1,-1,+1); paso("PATRON 6",+1,-1,+1,-1);
}
void loop(){ parar(); }
"""
    elif 15 <= n <= 17:
        body="const byte ENA=11, IN1=5, IN2=6;\nvoid parar(){ analogWrite(ENA,0); digitalWrite(IN1,LOW); digitalWrite(IN2,LOW); }\nvoid setup(){ pinMode(ENA,OUTPUT); pinMode(IN1,OUTPUT); pinMode(IN2,OUTPUT); parar(); delay(2000); digitalWrite(IN1,HIGH); digitalWrite(IN2,LOW); analogWrite(ENA,80); delay(600); parar(); }\nvoid loop(){ parar(); }\n"
    elif n == 30:
        body=motor_api+"""const byte IR_IZQ=3,IR_DER=2; const int DETECTADO=LOW;
void setup(){ prepararMotores(); pinMode(IR_IZQ,INPUT); pinMode(IR_DER,INPUT); delay(3000); }
void loop(){ bool izq=digitalRead(IR_IZQ)==DETECTADO, der=digitalRead(IR_DER)==DETECTADO;
  if(izq&&der) mover(+1,+1,+1,+1,65);
  else if(izq) mover(-1,+1,-1,+1,60);
  else if(der) mover(+1,-1,+1,-1,60);
  else parar();
  delay(30);
}
"""
    elif 28 <= n <= 29:
        body="const byte IR_IZQ=3, IR_DER=2;\nvoid setup(){ pinMode(IR_IZQ,INPUT); pinMode(IR_DER,INPUT); Serial.begin(9600); }\nvoid loop(){ int izq=digitalRead(IR_IZQ), der=digitalRead(IR_DER); Serial.print(izq); Serial.print(','); Serial.println(der); delay(100); }\n"
    elif n == 36 or n == 37:
        body="""const byte PINES[5]={A4,A3,A2,A1,A0}; const int LINEA=LOW;
void setup(){ Serial.begin(9600); for(byte i=0;i<5;i++) pinMode(PINES[i],INPUT); }
void loop(){ int suma=0,cuantos=0; for(byte i=0;i<5;i++){ if(digitalRead(PINES[i])==LINEA){ suma+=int(i)-2; cuantos++; } }
  if(cuantos==0) Serial.println("STOP_LINEA_PERDIDA"); else { float pos=float(suma)/cuantos; if(pos<-0.4) Serial.println("CORRIGE_IZQ"); else if(pos>0.4) Serial.println("CORRIGE_DER"); else Serial.println("AVANZA"); } delay(100); }
"""
    elif n == 38:
        body=motor_api+"""const byte PINES[5]={A4,A3,A2,A1,A0}; const int LINEA=LOW;
void setup(){ prepararMotores(); for(byte i=0;i<5;i++) pinMode(PINES[i],INPUT); delay(3000); }
void loop(){ int suma=0,cuantos=0; for(byte i=0;i<5;i++){ if(digitalRead(PINES[i])==LINEA){ suma+=int(i)-2; cuantos++; } }
  if(cuantos==0) parar(); else { float pos=float(suma)/cuantos; if(pos<-0.4) mover(-1,+1,-1,+1,55); else if(pos>0.4) mover(+1,-1,+1,-1,55); else mover(+1,+1,+1,+1,65); } delay(20); }
"""
    elif 34 <= n <= 35:
        body="const byte PINES[5]={A4,A3,A2,A1,A0};\nvoid setup(){ Serial.begin(9600); for(byte i=0;i<5;i++) pinMode(PINES[i],INPUT); }\nvoid loop(){ for(byte i=0;i<5;i++) Serial.print(digitalRead(PINES[i])); Serial.println(); delay(100); }\n"
    elif 43 <= n <= 46:
        body="const byte TRIG=30,ECHO=31;\nvoid setup(){ pinMode(TRIG,OUTPUT); pinMode(ECHO,INPUT); Serial.begin(9600); }\nvoid loop(){ digitalWrite(TRIG,LOW); delayMicroseconds(2); digitalWrite(TRIG,HIGH); delayMicroseconds(10); digitalWrite(TRIG,LOW); unsigned long us=pulseIn(ECHO,HIGH,30000UL); if(us==0) Serial.println(\"SIN_ECO\"); else { float cm=us*0.0343/2.0; Serial.println(cm); } delay(100); }\n"
    elif n == 48 or n == 70:
        body="""#include <Servo.h>
Servo cabeza; const byte TRIG=30,ECHO=31,PIN_SERVO=13;
float distancia(){ digitalWrite(TRIG,LOW); delayMicroseconds(2); digitalWrite(TRIG,HIGH); delayMicroseconds(10); digitalWrite(TRIG,LOW); unsigned long us=pulseIn(ECHO,HIGH,30000UL); return us?us*0.0343/2.0:-1; }
void setup(){ Serial.begin(9600); pinMode(TRIG,OUTPUT); pinMode(ECHO,INPUT); cabeza.attach(PIN_SERVO); }
void loop(){ for(int a=45;a<=135;a+=45){ cabeza.write(a); delay(500); Serial.print(a); Serial.print(','); Serial.println(distancia()); } cabeza.write(90); delay(1500); }
"""
    elif n == 49:
        body=motor_api+"""#include <Servo.h>
Servo cabeza; const byte TRIG=30,ECHO=31; float cm(){ digitalWrite(TRIG,LOW); delayMicroseconds(2); digitalWrite(TRIG,HIGH); delayMicroseconds(10); digitalWrite(TRIG,LOW); unsigned long us=pulseIn(ECHO,HIGH,30000UL); return us?us*0.0343/2.0:-1; }
void setup(){ prepararMotores(); pinMode(TRIG,OUTPUT); pinMode(ECHO,INPUT); cabeza.attach(13); cabeza.write(90); delay(3000); }
void loop(){ float frente=cm(); if(frente<0||frente<25){ parar(); cabeza.write(45); delay(500); float izq=cm(); cabeza.write(135); delay(500); float der=cm(); cabeza.write(90); if(izq<0||der<0) parar(); else if(izq>der) mover(-1,+1,-1,+1,60); else mover(+1,-1,+1,-1,60); delay(350); parar(); } else mover(+1,+1,+1,+1,60); delay(40); }
"""
    elif n == 47:
        body="#include <Servo.h>\nServo cabeza; const byte PIN_SERVO=13;\nvoid setup(){ cabeza.attach(PIN_SERVO); }\nvoid loop(){ for(int a=45;a<=135;a+=45){ cabeza.write(a); delay(700); } cabeza.write(90); delay(1200); }\n"
    elif n == 57:
        body=motor_api+"""unsigned long ultimaOrden=0;
void setup(){ prepararMotores(); Serial1.begin(9600); delay(3000); }
void loop(){ if(Serial1.available()){ char c=Serial1.read(); ultimaOrden=millis(); if(c=='F') mover(+1,+1,+1,+1,70); else if(c=='B') mover(-1,-1,-1,-1,70); else if(c=='L') mover(-1,+1,-1,+1,65); else if(c=='R') mover(+1,-1,+1,-1,65); else parar(); }
  if(millis()-ultimaOrden>500) parar(); }
"""
    elif 54 <= n <= 56:
        body="unsigned long ultimo=0;\nvoid setup(){ Serial.begin(9600); Serial1.begin(9600); }\nvoid loop(){ if(Serial1.available()){ char c=Serial1.read(); ultimo=millis(); if(c=='F'||c=='B'||c=='L'||c=='R'||c=='S') Serial.println(c); else Serial.println(\"STOP_DATO_INVALIDO\"); } if(millis()-ultimo>500) Serial.println(\"STOP_TIMEOUT\"); delay(100); }\n"
    elif 63 <= n <= 67:
        body="// Puente de diagnóstico ESP8266 por Serial1. No contiene credenciales.\nvoid setup(){ Serial.begin(9600); Serial1.begin(115200); Serial.println(\"Escribe AT; no conectes Bluetooth a la vez\"); }\nvoid loop(){ while(Serial.available()) Serial1.write(Serial.read()); while(Serial1.available()) Serial.write(Serial1.read()); }\n"
    else:
        body="enum Estado { STOP, MANUAL, AUTO };\nEstado estado=STOP; unsigned long ultimaOrden=0;\nvoid detener(){ /* escribir aquí las salidas seguras del bloque de movimiento */ }\nvoid setup(){ Serial.begin(9600); detener(); }\nvoid loop(){ if(Serial.available()){ char c=Serial.read(); ultimaOrden=millis(); if(c=='S') estado=STOP; else if(c=='M') estado=MANUAL; else if(c=='A') estado=AUTO; else estado=STOP; } if(millis()-ultimaOrden>500) estado=STOP; if(estado==STOP) detener(); Serial.println(estado); delay(100); }\n"
    return common+body

def link_for(num):
    lesson=LESSONS[num-1]
    folder,_=block_for(num)
    return f"../{folder}/{num:02d}-{slugify(lesson['title'])}.md"

def prereq_links(lesson, folder):
    if lesson['pre'] == '-': return "Ninguno: esta es la entrada al curso."
    nums=[]
    for part in lesson['pre'].split(','):
        if '-' in part:
            a,b=map(int,part.split('-')); nums.extend(range(a,b+1))
        else: nums.append(int(part))
    links=[]
    for n in nums:
        prev=LESSONS[n-1]; pf,_=block_for(n)
        rel = f"../{pf}/{n:02d}-{slugify(prev['title'])}.md" if pf != folder else f"{n:02d}-{slugify(prev['title'])}.md"
        links.append(f"[Lección {n:02d}: {prev['title']}]({rel})")
    return ", ".join(links)+". Debes poder explicar su idea central y repetir su prueba segura antes de continuar."

def safety(n):
    if n in set(range(15,21)) | {27,30,38,47,49,52,55,57,65,66,69,71,72,73,75}:
        return """- 🟢 El estudiante predice, lee el código y registra observaciones.
- 🟡 Un adulto permanece presente durante USB, calibración o cualquier prueba física.
- 🔴 El adulto manipula baterías 18650, interruptores de potencia, driver y cables. Toda conexión se revisa sin USB y con alimentación apagada.

Para movimiento: primero ruedas levantadas sobre una base estable, velocidad baja, área despejada y el interruptor accesible. Cabello, mangas y dedos lejos de ruedas. Si hay calor, olor, humo, chispa, zumbido fuerte o movimiento inesperado, el adulto corta energía; no se intenta frenar con la mano."""
    if n in set(range(28,30)) | set(range(32,38)) | set(range(43,47)) | {48,53,54,56,59,63,64,67,70,74}:
        return """- 🟢 El estudiante prepara la predicción, el programa y la tabla de datos.
- 🟡 Un adulto revisa el montaje antes de conectar USB o alimentar sensores.
- 🔴 El adulto corrige cualquier cable, ruta de Serial1 o conexión de potencia. Se cablea únicamente con USB retirado y alimentación apagada.

La actividad comienza sin movimiento. Si una lectura es extraña, no se cambian varios cables a la vez: se apaga, se compara con el mapa canónico y se modifica una sola variable."""
    return """- 🟢 El estudiante puede leer, dibujar, programar y observar el robot apagado.
- 🟡 Un adulto comprueba el estado de PX-32 antes de conectar USB.
- 🔴 Solo el adulto manipula baterías 18650, cargador, potencia o cableado dudoso.

La mesa debe estar seca y despejada. PX-32 permanece apagado y ensamblado salvo que un paso indique lo contrario. Ante calor, olor, humo, chispa o daño visible, no se toca: el adulto aísla la alimentación."""

def lesson_text(L):
    n=L['n']; folder,block=block_for(n); slug=slugify(L['title'])
    codepath = f"../../code/educational/{n:02d}-{slug}/{n:02d}-{slug}.ino"
    next_line = "Has completado la ruta. El siguiente paso es repetir la demostración, explicar decisiones y elegir una mejora segura." if n==75 else f"La próxima sesión será la [Lección {n+1:02d}: {LESSONS[n]['title']}]({n+1:02d}-{slugify(LESSONS[n]['title'])}.md)" if block_for(n+1)[0]==folder else f"La próxima sesión será la [Lección {n+1:02d}: {LESSONS[n]['title']}](../{block_for(n+1)[0]}/{n+1:02d}-{slugify(LESSONS[n]['title'])}.md)"
    resources="\n".join(f"- [{what}]({url}) — {lang}; {fmt}; {dur}. Aprenderás {what.lower()}. {'Esencial' if i==0 else 'Opcional'}." for i,(lang,fmt,dur,what,url) in enumerate(RESOURCES[block]))
    code_section = f"""Abre [{n:02d}-{slug}.ino]({codepath}). Antes de cargarlo, localiza `setup()`, `loop()` y la línea que representa **{L['concept'].split(',')[0]}**. Lee el programa de arriba abajo y predice su salida.

```cpp
{sketch(n,slug).strip()}
```

La sintaxis —llaves, paréntesis y punto y coma— permite que el compilador separe instrucciones. El comportamiento es lo que ocurre al ejecutarlas. El propósito de este sketch es aislar la idea de hoy; todavía no es el programa final del robot. No añadas una segunda mejora hasta comprobar la primera.""" if n in CODE_LESSONS else "Hoy no hace falta cargar código nuevo. Si se usa el monitor serie o un sketch anterior, será solo como instrumento de observación. Esta decisión mantiene una sola idea nueva en la sesión y evita confundir un fenómeno físico con un error de sintaxis."
    return f"""# Lección {n:02d} — {L['title']}

## 1. Tu misión de hoy

Hoy vas a **{L['mission']}**. Al terminar podrás demostrarlo con una explicación, un dato o un comportamiento observable; no basta con decir “funcionó”.

## 2. Tiempo estimado

- Lectura y conversación inicial: 10 minutos.
- Preparación y predicción: 5 minutos.
- Actividad o programación: 15 minutos.
- Desafío y depuración: 5 minutos.
- Cuéntale a papá y resumen: 5 minutos.

**Total: 40 minutos.** Si aparece una duda de cableado o la actividad necesita más intentos, detente al terminar la preparación y continúa otro día; la seguridad no se comprime para cumplir el reloj.

## 3. Lo que necesitas saber antes de empezar

{prereq_links(L,folder)}

También necesitas distinguir tres capas de PX-32: la **energía** permite que algo ocurra, la **señal** representa información u órdenes y el **programa** decide qué hacer con ellas. Cuando algo falle, pregunta primero en cuál capa está la evidencia. Consulta el [glosario general](../../docs/reference/glosario.md) y el [mapa canónico de conexiones](../../docs/reference/mapa-conexiones-robot.md) sin modificar el montaje.

## 4. Lectura principal

### La idea intuitiva

El tema de hoy es **{L['concept']}**. En lenguaje cotidiano, buscamos una forma fiable de {L['mission']}. La palabra “fiable” importa: una sola coincidencia puede ser suerte; una explicación científica conecta una causa, una prueba y un resultado que otra persona podría repetir.

{STAGE_EXPLANATIONS[block]}

### De la intuición al concepto técnico

Los términos centrales son **{L['concept']}**. No son etiquetas decorativas: cada uno nombra una relación que podremos observar. Una analogía útil es pensar en una receta: ingredientes, pasos y resultado ayudan a organizar la acción. Pero la analogía tiene límite; PX-32 no “sabe” qué desea el cocinero y un componente real responde a voltaje, tiempo, geometría y código, no a intenciones.

En PX-32, esta idea se usa para {L['activity']}. Antes de actuar, separa cuatro preguntas: ¿qué cambiaremos?, ¿qué mantendremos igual?, ¿qué mediremos?, ¿qué resultado nos obligaría a detenernos? Ese orden convierte una demostración llamativa en un experimento. Si modificamos dos cosas a la vez, perdemos la posibilidad de saber cuál causó el cambio.

Un error frecuente es confundir el nombre de una pieza con una explicación. Decir “es un sensor” no explica qué magnitud detecta, qué señal entrega ni bajo qué condiciones puede equivocarse. Otro error es atribuir intención al programa: una condición `if` no “comprende” el obstáculo; compara representaciones y ejecuta una rama. Pregunta de reflexión: **¿qué evidencia distinguiría una decisión correcta de una coincidencia?**

La meta no es memorizar todo en una lectura. Primero forma un modelo: entrada → transformación → salida. Después contrástalo con la actividad. Si el resultado no coincide, el modelo gana detalle. Esa revisión es aprendizaje científico, no fracaso.

## 5. Palabras nuevas

- **{L['concept'].split(',')[0].strip().capitalize()}:** idea principal que podrás reconocer en la actividad.
- **Evidencia:** observación o medición que apoya o contradice una explicación.
- **Variable de prueba:** elemento que cambiamos deliberadamente mientras mantenemos los demás lo más estables posible.
- **Fallo seguro:** estado que reduce el riesgo cuando falta información; en PX-32 suele ser `STOP`.

Puedes consultar definiciones relacionadas en el [glosario general](../../docs/reference/glosario.md).

## 6. Así aparece en PX-32

**Hardware:** {L['hw']}.

```text
fenómeno o comando → sensor/interfaz → pin y programa → decisión → actuador o mensaje
                         ↑                         |
                         └──── evidencia Serial ──┘
```

La cadena exacta de hoy se concentra en **{L['concept']}**. No cambies conexiones basándote solo en este esquema conceptual. Para pines usa el [mapa canónico](../../docs/reference/mapa-conexiones-robot.md); para discrepancias usa la [errata del manual](../../docs/reference/errata-osoyoo.md). Los límites de potencia y la configuración interna del portabaterías siguen `PENDIENTE_DE_VERIFICAR`.

## 7. Seguridad y participación del adulto

{safety(n)}

## 8. Predice antes de probar

1. ¿Qué esperas observar cuando logres {L['mission']} y qué mecanismo produciría ese resultado?
2. ¿Qué observación contraria te haría detenerte o revisar la explicación?

Respóndelas en voz alta o en tu cuaderno físico. No necesitas un diario digital.

## 9. Actividad o experimento guiado

1. **Preparar.** Coloca PX-32 estable, identifica {L['hw']} y confirma con el adulto que la energía está en el estado seguro. Continúa solo si no hay cables sueltos, daño, calor u olor.
2. **Trazar.** Señala la ruta entrada → proceso → salida relacionada con {L['concept']}. Si no puedes justificar un pin, consulta el mapa; no adivines.
3. **Predecir.** Elige un resultado concreto y una señal de parada. Di qué variable cambiarás y cuáles permanecerán iguales.
4. **Probar.** Vas a {L['activity']}. Haz un solo cambio. Observa antes de repetir y mantén accesible la forma de detener la prueba.
5. **Comprobar.** El resultado que permite continuar es: {L['observe']}. Si no aparece, apaga cuando corresponda y pasa a “Si no funciona”.
6. **Repetir.** Realiza una segunda prueba cambiando solo un valor, posición o entrada. Compara, no persigas un resultado “bonito”.
7. **Restaurar.** Detén el programa, apaga la alimentación y devuelve cualquier ajuste temporal a su posición anotada. El adulto confirma que PX-32 conserva su ensamblaje y que ningún cable invade ruedas o engranajes.

## 10. Código

{code_section}

## 11. Qué deberías observar

El resultado normal es **{L['observe']}**. Puede haber variación por tolerancias, superficie, luz, fricción, carga, eco o tiempos del programa. Una variación pequeña y repetible es información; un salto grande, un reinicio, una lectura imposible o un movimiento inesperado exige STOP.

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

{resources}

Comprueba con un adulto antes de abandonar el material del curso. Un recurso externo amplía la explicación; nunca reemplaza el mapa de conexiones ni las reglas de seguridad de PX-32.

## 15. Cuéntale a papá

- Cuéntale con tus palabras qué significa **{L['concept'].split(',')[0]}** y dónde aparece en PX-32.
- Muéstrale la evidencia y explícale qué cambiaste y qué mantuviste igual.
- Pregúntale qué ejemplo parecido conoce fuera de la robótica.
- Explícale un error posible y la prueba pequeña que usarías para localizarlo.
- Dile qué te gustaría probar después y qué regla de seguridad conservarías.

Esto es una conversación, no un examen. Si una explicación se atasca, vuelvan juntos al diagrama entrada → proceso → salida.

## 16. Resumen de la jornada

Hoy aprendiste a **{L['mission']}** y lo conectaste con **{L['concept']}**. Pudiste observar {L['observe']}. La regla de seguridad es cambiar conexiones únicamente sin energía y usar `STOP` ante información dudosa. {next_line}.
"""

def write_all():
    educational=ROOT/'code'/'educational'
    for child in educational.iterdir():
        if child.is_dir():
            shutil.rmtree(child)
    for d,_ in BLOCKS.values():
        path=ROOT/'course'/d
        path.mkdir(parents=True, exist_ok=True)
        for old in path.glob('[0-9][0-9]-*.md'):
            old.unlink()
    for L in LESSONS:
        folder,_=block_for(L['n']); slug=slugify(L['title'])
        p=ROOT/'course'/folder/f"{L['n']:02d}-{slug}.md"
        p.write_text(lesson_text(L),encoding='utf-8')
        if L['n'] in CODE_LESSONS:
            d=ROOT/'code'/'educational'/f"{L['n']:02d}-{slug}"
            d.mkdir(parents=True, exist_ok=True)
            (d/f"{L['n']:02d}-{slug}.ino").write_text(sketch(L['n'],slug),encoding='utf-8')

    write_indexes()

def rel_lesson(L, prefix="course"):
    folder,_=block_for(L['n'])
    return f"{prefix}/{folder}/{L['n']:02d}-{slugify(L['title'])}.md"

def write_indexes():
    # README de cada bloque.
    for nums,(folder,name) in BLOCKS.items():
        rows=[]
        for n in nums:
            L=LESSONS[n-1]
            rows.append(f"| {n:02d} | [{L['title']}]({n:02d}-{slugify(L['title'])}.md) | 40 min | Desarrollada |")
        first,last=min(nums),max(nums)
        text=f"""# Bloque: {name}

Este bloque comprende las lecciones {first:02d}–{last:02d} de la ruta canónica. Se recorren en orden: cada sesión usa conceptos ya presentados y termina preparando la siguiente.

| Lección | Sesión | Duración | Estado |
|---:|---|---:|---|
{chr(10).join(rows)}

Una lección se completa después de hacer la predicción, la actividad segura, el desafío y la conversación **Cuéntale a papá**. El cuaderno físico es opcional; no hay evaluación tradicional ni diario digital obligatorio.
"""
        (ROOT/'course'/folder/'README.md').write_text(text,encoding='utf-8')

    # Índice canónico.
    rows=[]
    for L in LESSONS:
        _,block=block_for(L['n'])
        rows.append(f"| {L['n']:02d} | {block} | [{L['title']}]({rel_lesson(L)}) | 40 min | Desarrollada |")
    cmap=f"""# Mapa canónico del curso PX-32

Esta es la **única ruta obligatoria**. PX-32 parte completamente ensamblado; se conserva así siempre que el objetivo lo permita. Cada sesión dura aproximadamente 40 minutos y se completa al realizar la actividad, aplicar la regla de seguridad y conversar “Cuéntale a papá”. El cuaderno físico es opcional; no existen evaluaciones tradicionales ni diario digital obligatorio.

## Progresión

```text
robot y electricidad → Mega y Arduino → programa → decisiones → bucles → funciones
→ driver y motores → PWM → Mecanum → infrarrojo → línea → ultrasonido y servo
→ Bluetooth → Wi-Fi → estados y prioridades → proyecto final
```

## Las 75 sesiones

| Nº | Bloque | Lección | Duración | Estado |
|---:|---|---|---:|---|
{chr(10).join(rows)}

## Hitos

- 20: movimiento Mecanum seguro.
- 30: seguimiento de una mano mediante dos sensores IR.
- 38: seguimiento de línea con cinco canales.
- 49: evasión de obstáculos por ultrasonido y servo.
- 57: control Bluetooth con timeout y STOP.
- 67: mando y telemetría Wi-Fi sin credenciales versionadas.
- 75: proyecto integrado reproducible y seguro.

La dependencia exacta aparece dentro de cada lección y en [docs/curriculum-matrix.md](docs/curriculum-matrix.md).
"""
    (ROOT/'COURSE-MAP.md').write_text(cmap,encoding='utf-8')

    progress=["# Avance personal en PX-32", "", "Marca una casilla después de realizar la actividad y contarle a papá lo aprendido. Puedes anotar fecha o comentario en tu cuaderno físico; no necesitas enlazar archivos.", ""]
    for nums,(folder,name) in BLOCKS.items():
        progress += [f"## {name}", ""]
        for n in nums:
            L=LESSONS[n-1]
            progress.append(f"- [ ] [{n:02d}. {L['title']}]({rel_lesson(L)})")
        progress.append("")
    (ROOT/'PROGRESS.md').write_text("\n".join(progress),encoding='utf-8')

    matrix=["# Matriz curricular canónica de PX-32", "", "Esta matriz y [COURSE-MAP.md](../COURSE-MAP.md) usan la misma numeración. `HW-xxx` remite al [diccionario de hardware](hardware/README.md).", "", "| Nº | Concepto | Hardware | Prerrequisito | Evidencia observable |", "|---:|---|---|---|---|"]
    for L in LESSONS:
        matrix.append(f"| {L['n']:02d} | {L['concept']} | {L['hw']} | {L['pre']} | {L['observe']} |")
    (ROOT/'docs'/'curriculum-matrix.md').write_text("\n".join(matrix)+"\n",encoding='utf-8')

    template="""# Lección NN — Título

## 1. Tu misión de hoy
Objetivo observable dirigido al estudiante.

## 2. Tiempo estimado
Desglose de lectura, preparación, actividad, desafío y conversación. Total habitual: 30–45 minutos.

## 3. Lo que necesitas saber antes de empezar
Prerrequisitos explicados y enlazados; términos ya disponibles.

## 4. Lectura principal
Narrativa progresiva: intuición → concepto técnico → aplicación en PX-32 → límites y preguntas de reflexión.

## 5. Palabras nuevas
Glosario breve y enlace al glosario general.

## 6. Así aparece en PX-32
Componentes, pines, rutas de señal y diagramas útiles; nunca inventar conexiones.

## 7. Seguridad y participación del adulto
- 🟢 Puede hacerlo el estudiante.
- 🟡 Debe estar presente un adulto.
- 🔴 El adulto manipula esta parte.

## 8. Predice antes de probar
Una o dos predicciones causales y una observación que podría contradecirlas.

## 9. Actividad o experimento guiado
Pasos completos: acción, observación, criterio para continuar, señal para detenerse y restauración.

## 10. Código
Sketch mínimo enlazado y explicado; una idea nueva; sintaxis, comportamiento, propósito y errores probables.

## 11. Qué deberías observar
Resultado normal, variación aceptable y señales de fallo.

## 12. Si no funciona
Tabla: síntoma → prueba sencilla → interpretación → siguiente acción segura.

## 13. Desafío
Extensión breve sin solución completa inmediata.

## 14. Lecturas y videos para explorar
Uno a tres recursos verificados con idioma, formato, duración, aprendizaje y carácter esencial/opcional.

## 15. Cuéntale a papá
Tres a cinco invitaciones naturales para explicar, mostrar y conversar; nunca un examen.

## 16. Resumen de la jornada
Aprendizaje, evidencia, regla de seguridad y conexión con la próxima lección.
"""
    (ROOT/'templates'/'LECCION-PLANTILLA.md').write_text(template,encoding='utf-8')

    code_rows=[]
    for L in LESSONS:
        if L['n'] in CODE_LESSONS:
            slug=slugify(L['title']); p=f"{L['n']:02d}-{slug}/{L['n']:02d}-{slug}.ino"
            code_rows.append(f"| {L['n']:02d} | [{p}]({p}) | {L['concept']} |")
    code_readme=f"""# Código educativo de PX-32

Cada sketch vive en una carpeta del mismo nombre que su archivo `.ino`, como requiere Arduino IDE. Son programas mínimos del curso: se leen y predicen antes de cargarse. Las constantes de pines coinciden con el [mapa canónico](../../docs/reference/mapa-conexiones-robot.md).

| Lección | Sketch | Idea aislada |
|---:|---|---|
{chr(10).join(code_rows)}

Los sketches Wi-Fi no contienen credenciales. Bluetooth y ESP8266 comparten `Serial1`; el adulto confirma que solo una ruta B/E esté activa. Los ejemplos de integración dejan `detener()` deliberadamente seguro e incompleto cuando copiar movimiento sin la verificación de la lección sería peligroso.
"""
    (ROOT/'code'/'educational'/'README.md').write_text(code_readme,encoding='utf-8')

    root_readme="""# PX-32 — curso autónomo de ciencia, programación y robótica

Este repositorio transforma un OSOYOO Mecanum Wheel Robotic Car Kit V2 ya ensamblado en una ruta de 75 sesiones para un estudiante de 11 años que comienza desde cero. La lectura guía la sesión; el padre acompaña la conversación y se encarga de baterías, potencia, cableado dudoso y primeras pruebas de movimiento.

## Empezar

1. Lee con el adulto las [reglas de seguridad](docs/reference/seguridad.md).
2. Abre el [mapa canónico](COURSE-MAP.md).
3. Comienza por la [Lección 01](course/00-fundamentos/01-que-es-un-robot.md).
4. Al terminar la actividad y “Cuéntale a papá”, marca la sesión en [PROGRESS.md](PROGRESS.md).

PX-32 permanece ensamblado siempre que sea posible. Si una sesión requiere una verificación o cambio, lo indica con semáforo 🟢/🟡/🔴, apagado, revisión y restauración. El cuaderno físico es opcional; no se exige diario digital ni evaluación escolar repetitiva.

## Fuentes y exactitud

El [PDF de OSOYOO](reference/original/osoyoo-mecanum-wheel-robotic-car-kit-v2.pdf) es la fuente primaria de conexiones. El [mapa canónico](docs/reference/mapa-conexiones-robot.md) registra los pines confirmados visualmente y la [errata](docs/reference/errata-osoyoo.md) conserva contradicciones y asuntos pendientes. Nunca se infieren voltajes o corrientes ausentes del fabricante.

## Estructura

- `course/`: 75 lecciones desarrolladas en una única secuencia.
- `code/educational/`: sketches mínimos enlazados desde las lecciones.
- `docs/readings/`: lecturas internas de apoyo.
- `docs/hardware/`: fichas de los componentes reales.
- `docs/reference/`: seguridad, pinout, conexiones, glosario y depuración.
- `assets/osoyoo-manual/`: recortes visuales verificados del manual.
- `reference/original/`: PDF original del fabricante.
"""
    (ROOT/'README.md').write_text(root_readme,encoding='utf-8')

    readings={
      "movimiento-y-pwm.md":("Movimiento, par y PWM", "Un motor DC transforma energía eléctrica en giro mediante campos magnéticos. La reductora intercambia velocidad por par. El driver Model Y recibe señales lógicas y gobierna potencia; no debe confundirse con la Mega. PWM regula el tiempo encendido dentro de ciclos rápidos: cambia la energía media, pero no garantiza una velocidad exacta porque intervienen carga, fricción y batería."),
      "luz-e-infrarrojo.md":("Luz, infrarrojo y reflexión", "La luz es radiación electromagnética. El infrarrojo cercano está fuera de la visión humana, pero puede emitirse y detectarse electrónicamente. Un sensor reflectivo observa cuánta radiación regresa; material, color, ángulo, distancia e iluminación cambian la señal. El comparador LM393 aplica un umbral y entrega una salida digital, útil pero menos rica que la señal continua."),
      "arrays-y-patrones.md":("Arrays y patrones espaciales", "Un array guarda varios datos del mismo tipo bajo un nombre y permite recorrerlos mediante índices. En el tracker, las posiciones 0 a 4 representan A4 a A0. El patrón no debe confundirse con la posición física hasta verificar la orientación. Interpretar consiste en transformar lecturas crudas en una estimación y después en una orden; esas capas se prueban por separado."),
      "sonido-eco-y-distancia.md":("Sonido, eco y distancia", "El sonido es una onda mecánica. El HC-SR04 envía ultrasonido y mide la duración del eco. Como el pulso viaja hasta el objeto y vuelve, la distancia es velocidad por tiempo dividida entre dos. La aproximación 0,0343 cm/µs depende del ambiente. Superficies inclinadas, blandas, pequeñas o demasiado cercanas pueden devolver ecos débiles."),
      "comunicacion-inalambrica.md":("Bluetooth, Wi-Fi y UART", "Bluetooth y Wi-Fi usan radio, pero organizan enlaces distintos. En PX-32, el módulo inalámbrico intercambia bytes con la Mega por UART. TX de un extremo llega a RX del otro y ambos acuerdan velocidad. Bluetooth y ESP8266 comparten Serial1: solo una ruta B/E puede estar activa. Un comando desconocido o antiguo debe producir STOP."),
      "redes-y-privacidad.md":("Red local, IP y privacidad", "Una red conecta nodos mediante enlaces y protocolos. El router ofrece un punto de acceso y DHCP puede asignar una dirección privada temporal. UDP envía datagramas sin garantizar entrega; por eso el robot no puede convertir el silencio en movimiento continuo. SSID, claves, ubicación e IP pública se mantienen fuera de Git y de cualquier captura pública."),
      "estados-y-seguridad.md":("Estados, prioridades y fallo seguro", "Una máquina de estados enumera situaciones válidas y transiciones permitidas. STOP, MANUAL y AUTO evitan combinaciones implícitas. La seguridad es una prioridad de arbitraje: STOP domina órdenes de radio, línea o autonomía. Un timeout, sensor inválido o reinicio debe llevar a salidas detenidas. Integrar significa preservar esas invariantes mientras se añaden comportamientos."),
    }
    intro=["# Lecturas de apoyo", "", "Estas lecturas condensan ideas transversales. Las lecciones siguen siendo la ruta principal; aquí se profundiza sin crear una segunda secuencia obligatoria.", ""]
    for fn,(title,body) in readings.items():
        txt=f"# {title}\n\n{body}\n\n## Para pensar\n\n¿Qué parte de la cadena entrada → transformación → salida describe mejor esta lectura? Explica un límite del modelo antes de aplicarlo a PX-32.\n"
        (ROOT/'docs'/'readings'/fn).write_text(txt,encoding='utf-8')
        intro.append(f"- [{title}]({fn})")
    (ROOT/'docs'/'readings'/'README.md').write_text("\n".join(intro)+"\n",encoding='utf-8')

if __name__ == '__main__':
    write_all()
