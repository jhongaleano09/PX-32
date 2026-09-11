# Catálogo de proyectos de PX-32

`CON_HARDWARE_ACTUAL` indica si el proyecto puede realizarse con el inventario HW-001 a HW-020, sin contar materiales cotidianos para pista o cajas.

| Proyecto | Hardware clave | Prerrequisito | CON_HARDWARE_ACTUAL | Resultado medible |
|---|---|---|---|---|
| SOS luminoso | LED integrado | Lección 06 | SÍ | Patrón corto-largo-corto repetible |
| Metrónomo LED | LED integrado | Lección 07 | SÍ | Frecuencia calculada y observada |
| Pista Mecanum | Motores, ruedas, Model Y | Hito 1 | SÍ | Recorrido lateral/diagonal con error medido |
| Desafío de precisión lateral | Igual | Hito 1 | SÍ | Desplazamiento objetivo y desviación |
| Alarma de proximidad visual/Serial | IR o ultrasónico | Bloque IR/ultrasónico | SÍ | Umbral y falsos positivos registrados |
| Seguidor de mano | Dos IR + ultrasónico + motores | Hito 2 | SÍ | Sigue dirección y conserva distancia segura |
| Seguidor de línea | Tracker + motores | Hito 3 | SÍ | Completa pista sin salirse |
| Radar ultrasónico | Ultrasónico + servo + Serial | Lección 48 | SÍ | Tabla ángulo/distancia |
| Estacionamiento automático | Ultrasónico + motores | Hito 4 | SÍ | Se detiene dentro de una tolerancia |
| Robot que mantiene distancia | Ultrasónico + motores | Hito 4 | SÍ | Error respecto a distancia objetivo |
| Laberinto | Ultrasónico + servo + motores | Hito 4 | SÍ | Llega a salida o documenta estrategia |
| Control Bluetooth | HC-02 + motores | Hito 5 | SÍ | Responde a F/B/L/R/S y timeout |
| Telemetría Wi-Fi | ESP + sensor | Hito 6 | SÍ | Reporta medición y estado en red local |
| Robot multimodo | Todo lo necesario | Lección 68 | SÍ | Cambia STOP/MANUAL/AUTO de forma segura |
| Línea + obstáculos | Tracker + ultrasónico + motores | Lección 73 | SÍ | Prioriza obstáculo y recupera línea |
| Velocímetro real | Encoders | Nivel 4 | NO | Velocidad/distancia con realimentación |
| Control remoto físico | Segundo micro + joystick + botones | Nivel 5 | NO | X/Y se convierten en movimiento Mecanum |

## Regla de proyecto

Todo proyecto comienza con una pregunta y un criterio de éxito. Si combina dos subsistemas, cada uno debe haber pasado antes su experimento aislado.
