# Mapa del curso PX-32

## Dónde estoy

Marca la casilla de la misión actual en [PROGRESS.md](PROGRESS.md). Una lección se considera terminada solo cuando se hizo su predicción, experimento, observación, desafío, quiz y registro de bitácora.

```text
EXPLORADOR -> CONSTRUCTOR -> PROGRAMADOR -> TÉCNICO DE SENSORES
           -> NAVEGADOR -> COMUNICADOR -> INGENIERO DE PX-32
```

## Ruta completa

| Bloque | Misiones | Hito |
|---|---|---|
| A. Fundamentos | 01 laboratorio; 02 inventario; 03 electricidad; 04 Mega2560 | Reconocer y cuidar el sistema |
| B. Programación | 05 Arduino IDE; 06 Blink; 07 variables y tiempo; 08 monitor serial; 09 decisiones; 10 bucles; 11 funciones | PX-32 ejecuta y explica programas pequeños |
| C. Movimiento | 12 motor DC; 13 Model Y; 14 puente H; 15 primer motor; 16 dirección; 17 PWM; 18 cuatro motores; 19 Mecanum; 20 vectores | HITO 1: movimiento completo |
| D. Infrarrojo | 21 luz; 22 espectro; 23 IR; 24 emisor/receptor; 25 reflexión; 26 LM393; 27 potenciómetro; 28 un sensor; 29 dos sensores | HITO 2: seguir una mano |
| E. Línea | 30 tracker de cinco canales; 31 IR1-IR5; 32 calibración; 33 cinco lecturas; 34 posición; 35 decisiones; 36 control | HITO 3: seguir una línea |
| F. Ultrasonido | 37 sonido; 38 frecuencia; 39 ultrasonido; 40 eco; 41 TRIG; 42 ECHO; 43 microsegundos; 44 distancia; 45 centímetros; 46 servo; 47 ángulos; 48 escaneo; 49 decisión | HITO 4: evitar obstáculos |
| G. Bluetooth | 50 ondas de radio; 51 comunicación; 52 Bluetooth; 53 HC-02; 54 UART; 55 TX/RX; 56 recibir una letra; 57 comandos F/B/L/R/S | HITO 5: control Bluetooth |
| H. Wi-Fi e IoT | 58 Wi-Fi vs Bluetooth; 59 ESP8266; 60 red; 61 router; 62 SSID; 63 IP; 64 cliente/servidor; 65 conexión; 66 comandos; 67 telemetría | HITO 6: control Wi-Fi |
| I. Integración | 68 modos; 69 sensor + movimiento; 70 radar; 71 estacionamiento; 72 laberinto; 73 línea + obstáculos; 74 telemetría; 75 proyecto libre | HITO FINAL: PX-32 integrado |

Los seis proyectos del manual OSOYOO aparecen como hitos y no como primeras experiencias. Cada subsistema se observa y prueba por separado antes de combinarlo.

## Niveles y requisitos

| Nivel | Insignia | Requisitos objetivos |
|---|---|---|
| 0 | Explorador | Identifica 15 componentes, diferencia sensor/actuador y aplica las cinco reglas críticas de seguridad |
| 1 | Constructor | Monta o inspecciona PX-32 con un adulto, sigue un diagrama y documenta una conexión sin energizar |
| 2 | Programador | Escribe Blink, usa variables, `if`, bucles, funciones y explica `setup()`/`loop()` |
| 3 | Técnico de sensores | Lee por Serial IR, tracker y ultrasonido; calibra y distingue medición de decisión |
| 4 | Navegador | Controla motores y Mecanum; completa línea y evasión con pruebas aisladas |
| 5 | Comunicador | Explica UART, recibe comandos Bluetooth y usa Wi-Fi sin publicar credenciales |
| 6 | Ingeniero de PX-32 | Integra dos o más subsistemas, usa una bitácora de fallos y presenta su propio proyecto |

## Qué ya aprendí y qué viene después

Al terminar cada lección, responde:

1. ¿Qué puedo explicar sin mirar el texto?
2. ¿Qué medí u observé realmente?
3. ¿Qué cambió entre mi predicción y el resultado?
4. ¿Qué pieza anterior necesita la próxima misión?

La columna `Prerrequisito` de la [matriz curricular](docs/curriculum-matrix.md) muestra las dependencias exactas.

## Proyectos disponibles por etapa

| Después de | Proyectos posibles |
|---|---|
| Lección 08 | SOS luminoso, metrónomo LED, contador Serial |
| Hito 1 | pista Mecanum, precisión lateral, coreografía |
| Hito 2 | seguidor de mano, alarma IR |
| Hito 3 | circuito de línea, desafío de calibración |
| Hito 4 | radar con servo, estacionamiento, laberinto |
| Hito 5 | control Bluetooth, robot por comandos |
| Hito 6 | telemetría Wi-Fi, panel de control local |
| Hito final | robot multimodo, línea + obstáculos |
