# Lección 17 — PWM: regular energía en el tiempo

## Encendido y apagado demasiado rápidos para contarlos

Un pin digital solo tiene dos estados eléctricos, pero `analogWrite()` puede producir **PWM**: pulsos que alternan rápidamente entre encendido y apagado. La fracción de cada ciclo que permanece encendido se llama **ciclo de trabajo**.

En la Mega 2560, `analogWrite(pin, valor)` usa valores de 0 a 255. En esta prueba:

| Valor | Fracción aproximada encendida | Lo que no significa |
|---:|---:|---|
| 100 | 39 % | 39 % de la velocidad máxima |
| 160 | 63 % | 160 revoluciones por minuto |
| 220 | 86 % | una velocidad garantizada |

El motor y la reductora responden a la energía recibida a lo largo del tiempo. Lo normal es observar una tendencia de giro mayor al aumentar PWM, pero el resultado no es lineal: existe rozamiento, la batería cambia, las ruedas tienen carga y un valor bajo puede no superar el **umbral de arranque**.

## Diseña la comparación

Prepara:

- PX-32 sobre los dos soportes rígidos ya comprobados.
- Computador, Arduino IDE 2 y cable USB de datos.
- [17-pwm-regular-energia-en-el-tiempo.ino](../../code/educational/17-pwm-regular-energia-en-el-tiempo/17-pwm-regular-energia-en-el-tiempo.ino).
- Tres tarjetas grandes: `100`, `160` y `220`.
- Una tabla en papel con columnas `valor`, `¿arrancó?`, `comparación visual/sonora` y `anomalía`.
- Baterías verificadas y adulto responsable de la potencia.

La dirección de AK1 permanecerá fija en D5 `HIGH` y D6 `LOW`. La única variable deliberada será el valor enviado a D11.

🔴 El adulto retira celdas y USB, apaga interruptores y revisa que la rueda AK1 gire libre de cables. Nadie toca una rueda durante la prueba.

## El experimento está escrito en una función

1. 🟢 Abre el archivo y compáralo con el bloque completo:

```cpp
// Curso PX-32 - Leccion 17: comparar tres niveles PWM en AK1.
// El sketch queda detenido hasta cambiar EJECUTAR_PRUEBA a true.
const bool EJECUTAR_PRUEBA = false;

const byte PWM_BK1 = 9;
const byte BK1_IN1 = 22;
const byte BK1_IN2 = 24;
const byte PWM_BK3 = 10;
const byte BK3_IN3 = 26;
const byte BK3_IN4 = 28;
const byte PWM_AK1 = 11;
const byte AK1_IN1 = 5;
const byte AK1_IN2 = 6;
const byte PWM_AK3 = 12;
const byte AK3_IN3 = 7;
const byte AK3_IN4 = 8;

void detenerTodos() {
  analogWrite(PWM_BK1, 0);
  analogWrite(PWM_BK3, 0);
  analogWrite(PWM_AK1, 0);
  analogWrite(PWM_AK3, 0);

  digitalWrite(BK1_IN1, LOW);
  digitalWrite(BK1_IN2, LOW);
  digitalWrite(BK3_IN3, LOW);
  digitalWrite(BK3_IN4, LOW);
  digitalWrite(AK1_IN1, LOW);
  digitalWrite(AK1_IN2, LOW);
  digitalWrite(AK3_IN3, LOW);
  digitalWrite(AK3_IN4, LOW);
}

void prepararMotores() {
  pinMode(PWM_BK1, OUTPUT);
  pinMode(PWM_BK3, OUTPUT);
  pinMode(PWM_AK1, OUTPUT);
  pinMode(PWM_AK3, OUTPUT);
  pinMode(BK1_IN1, OUTPUT);
  pinMode(BK1_IN2, OUTPUT);
  pinMode(BK3_IN3, OUTPUT);
  pinMode(BK3_IN4, OUTPUT);
  pinMode(AK1_IN1, OUTPUT);
  pinMode(AK1_IN2, OUTPUT);
  pinMode(AK3_IN3, OUTPUT);
  pinMode(AK3_IN4, OUTPUT);
  detenerTodos();
}

void probarNivel(byte potenciaPwm) {
  digitalWrite(AK1_IN1, HIGH);
  digitalWrite(AK1_IN2, LOW);
  analogWrite(PWM_AK1, potenciaPwm);
  delay(700);
  detenerTodos();
  delay(1200);
}

void setup() {
  prepararMotores();

  if (!EJECUTAR_PRUEBA) {
    return;
  }

  // Da tiempo para retirar el USB y, despues, energizar desde baterias.
  delay(15000);
  probarNivel(100);
  probarNivel(160);
  probarNivel(220);
  detenerTodos();
}

void loop() {
  detenerTodos();
}
```

2. 🟢 Lee `probarNivel(byte potenciaPwm)`. El **parámetro** recibe un valor diferente en cada llamada, pero el sentido y los tiempos permanecen iguales. Esta es la comparación justa que preparaste en la Lección 11.

3. 🟢 Calcula aproximadamente cada ciclo de trabajo: divide 100, 160 y 220 entre 255. No necesitas contar pulsos; el cálculo representa la proporción de tiempo encendido.

4. 🟢 Predice un orden, no tres velocidades exactas. Escribe, por ejemplo: “Espero que 220 produzca más giro observable que 160 y 100, salvo que 100 quede bajo el umbral de arranque”.

> **[PENDIENTE VISUAL]**
> - **Tipo:** diagrama temporal comparativo.
> - **Objetivo:** ver que PWM cambia la proporción encendido/apagado sin convertir el pin en una salida analógica continua.
> - **Descripción:** tres líneas con ciclos del mismo ancho; áreas HIGH sombreadas para 100/255, 160/255 y 220/255, alineadas con tres ruedas que muestran aumento de giro esperado, no una escala exacta de rpm.
> - **Elementos que deben señalarse:** HIGH, LOW, período, ciclo de trabajo, 100, 160, 220, energía media y advertencia “no equivale directamente a velocidad”.
> - **Fuente técnica:** referencia `analogWrite()` de Arduino, https://docs.arduino.cc/language-reference/en/functions/analog-io/analogWrite/; conceptos Arduino Engineering Kit, https://aek.arduino.cc/chapter/concepts, sección PWM.
> - **Texto alternativo sugerido:** “Tres señales PWM muestran porciones encendidas cada vez mayores dentro de ciclos iguales”.

## Observa tres pulsos comparables

5. 🟢 Cambia solamente `EJECUTAR_PRUEBA` a `true`.

6. 🟡 Con baterías fuera, conecta USB, confirma Mega y puerto, verifica y sube. Retira el USB después del mensaje de carga completada.

7. 🟢 Ensaya sin energía: el adulto señala una tarjeta cada 700 ms y deja 1200 ms sin tarjeta. Debes poder anticipar `100 -> pausa -> 160 -> pausa -> 220 -> pausa`.

8. 🔴 El adulto instala las celdas, confirma que PX-32 sigue estable y enciende. Después de quince segundos comienza el primer nivel. Mantén manos, tarjetas y rostro fuera del volumen de las ruedas.

9. 🟢 Levanta la tarjeta correspondiente al escuchar o ver cada pulso y llena la tabla. Compara desenfoque visual, sonido y capacidad de arrancar; no toques la rueda y no inventes rpm.

10. 🔴 Si un nivel produce zumbido continuo sin giro, una rueda trabada, vibración que mueve el soporte, calor, olor o reinicio, el adulto apaga de inmediato. Un motor detenido puede exigir mucha corriente; no esperes al nivel siguiente “a ver si mejora”.

11. 🟢 Si los tres niveles completan la secuencia, busca una **tendencia**, no una igualdad perfecta. `220` debería parecer mayor que `100`; pequeñas diferencias o un primer nivel que apenas arranca son datos sobre el sistema real.

12. 🔴 El adulto apaga y retira las baterías. Con USB como única fuente, restaura `EJECUTAR_PRUEBA = false`, verifica y carga la versión neutral.

La actividad está completa cuando puedes explicar por qué aumentó la proporción HIGH, qué observaste realmente y por qué eso no permite afirmar una velocidad exacta.

## Interpreta antes de corregir

| Resultado | Interpretación razonable | Próximo paso seguro |
|---|---|---|
| 100 no arranca; 160 y 220 sí | 100 puede estar bajo el umbral de arranque en estas condiciones | Registra el umbral aproximado; no declares el motor defectuoso |
| Los tres parecen iguales | La observación visual puede no tener resolución suficiente o el driver puede estar saturando la respuesta | Repite solo otro día con una marca visual segura diseñada por el adulto; no alargues pulsos ahora |
| El orden parece invertido | Batería, roce o observación pueden haber cambiado | Revisa que las llamadas sean 100, 160 y 220 y que nada toque AK1 |
| Una pausa desaparece | Falta `detenerTodos()` o `delay(1200)` dentro de `probarNivel()` | No energices de nuevo hasta restaurar ambas líneas |
| Otra rueda gira | La parada de todos los canales o el sketch cargado no coincide | Apaga, compara el archivo y revisa pines sin energía |

## Lecturas y videos para explorar

- [Señal PWM con Arduino y analogWrite](https://programarfacil.com/blog/arduino-blog/pwm-con-arduino-analogico/) — Español; lectura; ~12 min.
**Por qué este recurso:** profundiza en `analogWrite()` y el ciclo de trabajo con ejemplos en LED y motor; es la misma función y la misma escala 0–255 que probaste hoy.

- [Modulación por ancho de pulsos PWM](https://cursos.mcielectronics.cl/2019/06/18/modulacion-por-ancho-de-pulsos/) — Español; lectura con gráficas; ~10 min.
**Por qué este recurso:** confirma con gráficas qué significa la fracción encendida de cada ciclo y por qué el resultado no es una velocidad garantizada.

- [Salida PWM Arduino #018](https://www.youtube.com/watch?v=EZT7dXO9_MA) — Español; video; 14 min (verlo por partes).
**Por qué este recurso:** estimula porque muestra la señal PWM en un osciloscopio: verás los pulsos que hoy solo imaginaste; como dura 14 min, míralo en dos partes.

Revisa tu tabla con estos recursos a la mano: valor PWM ordenado, proporción encendida y lo que observaste son tres datos distintos.

## Referencias técnicas de la clase

- [Referencia `analogWrite()` de Arduino](https://docs.arduino.cc/language-reference/en/functions/analog-io/analogWrite/), uso de valores PWM.
- [Arduino Mega 2560 Rev3](https://docs.arduino.cc/hardware/mega-2560/), 15 salidas PWM; el pinout oficial identifica D9 a D12 como PWM.
- [Guía oficial del Model Y](https://osoyoo.com/2022/02/25/osoyoo-model-y-4-channel-motor-driver/), pines de velocidad y rango de ejemplo 0 a 255.

## Cuéntale a papá

Muéstrale tu tabla y evita la frase “fue al 63 % de velocidad”. Di qué porcentaje del ciclo representa 160, qué cambió en la observación y qué factores impiden convertirlo directamente en rpm.

En la [Lección 18](18-cuatro-motores-cuatro-identidades.md) conservarás una sola potencia y usarás pulsos breves para comprobar la identidad de las cuatro esquinas.
