# Hoja de ruta de expansiones para PX-32

## Regla de compra

No comprar para “tener más cosas”. Primero agotar el hardware existente. Una expansión se considera cuando abre un concepto que PX-32 todavía no puede enseñar bien y el estudiante alcanzó el nivel indicado.

Los precios no se incluyen en esta fase porque no se verificaron país, proveedor, calidad ni fecha. Se consultarán justo antes de una compra real.

| Componente opcional | Concepto nuevo | Proyecto que desbloquea | Dificultad | Cuándo | Compatibilidad/voltaje | Riesgos |
|---|---|---|---|---|---|---|
| Breadboard + resistencias + LEDs + pulsadores + potenciómetros | Circuitos discretos, pull-up, ADC | Laboratorio fuera del robot | Baja | Antes o durante Nivel 2 | Mega 5 V; elegir valores mediante cálculo | Cortos si se cablea energizado |
| Multímetro con protección adecuada | Medición real de V/R/continuidad | Diagnóstico sistemático | Media | Con adulto, desde Nivel 1 | Rangos adecuados al kit | Corriente mal medida puede crear corto |
| Joystick analógico | Dos ejes ADC, centro y zona muerta | Control Mecanum proporcional | Media | Nivel 3 | Verificar salida 0-5 V o adaptar | No exceder entrada ADC |
| Módulo de joystick + botones | ADC + entradas digitales | Menú y control manual | Media | Nivel 3 | Preferir 5 V compatible | Rebote de botones |
| OLED I2C | Bus, dirección, interfaz visual | Panel local de PX-32 | Media | Nivel 3 | Muchos módulos son 3.3-5 V; verificar | Dirección/tensión incorrectas |
| Buzzer | Frecuencia, tono y señalización | Alarmas y código musical | Baja | Nivel 2 | Activo/pasivo y corriente a verificar | Ruido; driver si requiere corriente |
| Encoders de rueda | Realimentación, pulsos, odometría | Velocidad y distancia reales | Alta | Nivel 4 | Pines de interrupción y nivel lógico | Montaje mecánico y cables móviles |
| IMU MPU6050 | Aceleración, giro, I2C, fusión | Orientación y giro medido | Alta | Nivel 4 | Chip 3.3 V; usar módulo con adaptación verificada | Interpretación/calibración |
| Temperatura/humedad | Magnitudes ambientales | Estación móvil | Baja-media | Nivel 3 | Depende del sensor | Condensación/precisión |
| Sensor ToF | Tiempo de vuelo óptico | Distancia estrecha y precisa | Media | Tras ultrasónico | Frecuentemente 2.8/3.3 V con breakout | Láser/clase y nivel lógico a verificar |
| Sensor de color | Espectro, calibración | Clasificar marcas de pista | Media | Tras IR | I2C y tensión según módulo | Luz ambiente |
| MicroSD | Almacenamiento, archivos, SPI | Registrador de telemetría | Media-alta | Nivel 5 | Módulo con adaptación a 5 V | Corrupción por retirar energía |
| RTC | Tiempo absoluto, respaldo | Registro de eventos con fecha | Media | Nivel 5 | I2C; batería tipo botón | Cuidado con celda y zona horaria |
| Segundo microcontrolador | Sistemas distribuidos | Control remoto físico | Alta | Nivel 5 | Elegir tras decidir radio/niveles | Dos fuentes y protocolos |

## Lo que no hay que comprar ahora

PX-32 ya tiene HC-02 Bluetooth y ESP8266/ESP-12S Wi-Fi. Comprar otro módulo inalámbrico antes de dominar ambos no desbloquea una idea nueva.

## Expansión especial: nuestro propio control remoto

### Arquitectura educativa

```text
JOYSTICK -> ADC -> (X,Y) -> zona muerta/escalado -> comando Mecanum
BOTONES  -> entradas digitales -----------------> modo/paro
                         |
                         v
             microcontrolador secundario
                         |
                  enlace inalámbrico
                         |
                         v
                 HC-02/ESP de PX-32
                         |
                Mega -> Model Y -> ruedas
```

### Orden de aprendizaje

1. Leer X/Y y mostrarlos por Serial.
2. Calibrar centro, extremos y zona muerta.
3. Convertir a comandos sin radio.
4. Añadir botón de parada.
5. Transmitir y confirmar recepción sin motores.
6. Aplicar comandos con ruedas levantadas.
7. Añadir control proporcional y pérdida segura de enlace.

### Decisión futura

No se selecciona todavía el microcontrolador secundario ni la radio. La elección dependerá de si se prioriza reutilizar Bluetooth, construir una red Wi-Fi o estudiar otro protocolo. Debe incluir niveles lógicos compatibles y una fuente segura independiente.
