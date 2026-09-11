# Sensores de PX-32

Un sensor no “sabe” qué hay en el mundo. Transforma un fenómeno físico en una señal. El programa interpreta esa señal usando un modelo y sus limitaciones.

| Sensor | Fenómeno | Señal hacia Mega | Informa | No informa directamente |
|---|---|---|---|---|
| IR de obstáculos x2 | Reflexión infrarroja | Digital en D3/D2 | Superó o no un umbral | Distancia exacta |
| Tracker 5 canales | Reflexión infrarroja | Cinco estados en A4-A0 | Patrón espacial bajo el frente | Color universal o coordenada perfecta |
| Ultrasónico | Tiempo de vuelo de sonido | Pulso ECHO en D31 | Tiempo relacionado con distancia | Material o identidad del objeto |
| Voltímetro | Voltaje eléctrico | Display local | Lectura aproximada de tensión | Capacidad exacta restante |

## Cadena de medición

```text
PROPIEDAD FÍSICA -> TRANSDUCTOR -> ACONDICIONAMIENTO
                  -> SEÑAL -> LECTURA -> NÚMERO/ESTADO -> INTERPRETACIÓN
```

## Calibración

Calibrar es comparar la respuesta con situaciones conocidas y elegir parámetros útiles. No convierte el sensor en perfecto. Se deben registrar superficie, luz ambiente, distancia, altura, voltaje y repetición cuando influyan.

## Error e incertidumbre

Dos lecturas pueden variar aunque nada parezca cambiar. Por eso:

- se mide varias veces;
- se prueba una variable a la vez;
- se conserva el dato original;
- se distingue “no hubo eco” de “distancia cero”;
- se documentan falsos positivos y falsos negativos.

## Regla de integración

Antes de que un sensor mueva motores, debe mostrar datos comprensibles en Serial. Después el programa imprime la decisión sin actuar. Solo al final se habilita el movimiento.

## Fuente y alcance

Hardware y pinouts: manual OSOYOO, pp. 18, 29, 35 y 40. Explicación de medición: curso PX-32.
