# Evaluación del bloque inicial - Nivel 0 Explorador

No abras la solución hasta terminar. Explica razonamiento, no solo la letra elegida.

## 1. Clasificación

Para cada pieza escribe `sensor`, `actuador`, `procesamiento/comunicación`, `potencia` o `estructura`: Mega2560, MG90, tracker, Model Y, chasis, ultrasónico y portabaterías.

## 2. Cadena física

Completa:

```text
distancia -> ______ -> pulso ECHO -> ______ -> decisión -> ______ -> motor
```

## 3. Seguridad

Encuentra cuatro errores en esta escena: “PX-32 está encendido sobre la mesa; una persona retira un conector tirando de los cables mientras una rueda gira y hay un tornillo suelto sobre la Mega”.

## 4. Memoria

Después de cargar un contador, desconectamos USB y volvemos a encender más tarde. ¿Permanece el programa? ¿Permanece el valor anterior de una variable `int` ordinaria? Explica.

## 5. Predicción de código

¿Cuántos ciclos completos caben idealmente en 12 segundos?

```cpp
digitalWrite(LED_BUILTIN, HIGH);
delay(250);
digitalWrite(LED_BUILTIN, LOW);
delay(750);
```

## 6. Diagnóstico

El LED enciende por USB, pero Upload falla. Escribe tres hipótesis que el encendido por sí solo no descarta.

## 7. Serial

Escribe código que muestre:

```text
Hola, soy PX-32
Prueba: 0
Prueba: 1
...
```

con una nueva línea por segundo.

## 8. Explicación final

En 100-180 palabras explica la diferencia entre código fuente, compilar, cargar y ejecutar.

## Criterio para Nivel 0

- 80% de respuestas correctas.
- Cinco reglas de seguridad explicadas sin ayuda.
- Cadena entrada-proceso-salida correcta.
- Una predicción registrada antes de probar.

Solución: [bloque-a-evaluacion.md](../solutions/bloque-a-evaluacion.md).
