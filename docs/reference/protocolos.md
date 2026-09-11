# Protocolos de comunicación

## Qué significa “protocolo”

Un protocolo es un acuerdo: qué representa cada señal, quién habla, cuándo lo hace y cómo se detectan errores. Tener cables conectados no basta; ambos extremos deben compartir reglas.

## Digital simple

Una línea representa estados como HIGH y LOW. Los IR de obstáculos y los cinco canales del tracker usan este modelo en el curso. La ventaja es que decidir resulta fácil; la desventaja es perder detalle sobre la intensidad original.

## PWM

PWM no es un voltaje analógico continuo. Alterna HIGH y LOW con rapidez. El porcentaje de tiempo en HIGH se llama ciclo de trabajo. PX-32 lo usa para modular motores y genera pulsos de control para el servo, aunque ambos usos no son idénticos.

## UART

UART transmite bits en serie sin una línea de reloj compartida. Requiere:

- TX de un equipo hacia RX del otro.
- GND común.
- Mismo baud rate y formato.

PX-32 mantiene `Serial` para USB y usa `Serial1` (`D18/TX1`, `D19/RX1`) para Bluetooth o ESP.

## Wi-Fi, IP y UDP

Wi-Fi crea el enlace de red por radio. IP identifica dispositivos lógicamente. UDP envía datagramas sin establecer una conversación confiable: es rápido, pero un paquete puede perderse o llegar fuera de orden. Por eso todo control remoto debe incluir un comando de parada y un comportamiento seguro ante silencio.

## I2C y SPI

No son necesarios para los seis hitos originales, pero aparecen en expansiones. I2C comparte SDA/SCL entre varios dispositivos con direcciones. SPI usa reloj y líneas de datos separadas, normalmente con una selección por dispositivo.

## Preguntas de diagnóstico

1. ¿Hay GND común?
2. ¿TX llega a RX?
3. ¿Coincide el baud rate?
4. ¿El programa escucha el puerto correcto?
5. ¿Bluetooth y ESP intentan usar Serial1 a la vez?

## Fuente y alcance

Conexiones del kit: manual OSOYOO, pp. 45, 51-53 y 55-61. La explicación de protocolos es material pedagógico del curso PX-32.
