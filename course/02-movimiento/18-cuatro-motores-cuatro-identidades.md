# Lección 18 — Cuatro motores, cuatro identidades

## “La rueda de atrás” ya no es suficiente

PX-32 tiene dos ruedas traseras y dos delanteras. Para coordinar un desplazamiento lateral, el programa necesita distinguir las cuatro sin ambigüedad. El manual les asigna un conector y tres señales a cada una:

| Orden de prueba | Posición mirando en el sentido de avance | Model Y | PWM | Entradas de dirección |
|---:|---|---|---:|---:|
| 1 | frontal derecha | BK1 | D9 | D22, D24 |
| 2 | frontal izquierda | BK3 | D10 | D26, D28 |
| 3 | trasera derecha | AK1 | D11 | D5, D6 |
| 4 | trasera izquierda | AK3 | D12 | D7, D8 |

**Derecha e izquierda pertenecen al robot**, no a la persona que lo mira. Si te colocas frente a PX-32, tu derecha queda enfrentada a su izquierda. Para evitar esa trampa, harás toda la actividad mirando desde atrás hacia el frente, como si fueras quien conduce.

## Prepara un mapa que pueda contradecirte

Necesitas:

- PX-32 y sus dos soportes rígidos, con las cuatro ruedas libres.
- Cuatro tarjetas: `BK1`, `BK3`, `AK1` y `AK3`.
- Una hoja con una vista superior del chasis y el frente marcado.
- Computador, Arduino IDE 2, cable USB y [18-cuatro-motores-cuatro-identidades.ino](../../code/educational/18-cuatro-motores-cuatro-identidades/18-cuatro-motores-cuatro-identidades.ino).
- El manual OSOYOO abierto en las páginas 7 y 13.
- Baterías verificadas y un adulto encargado de toda la potencia.

🔴 El adulto deja el robot sin celdas ni USB y con interruptores apagados. Comprueba soportes, cables alejados de ruedas y acceso inmediato al apagado.

## Predice el orden leyendo las llamadas

1. 🟢 Colócate detrás del robot. Pon cada tarjeta junto a la esquina que indica la tabla. Copia esos nombres en tu dibujo antes de abrir el programa.

2. 🟢 Compara el `.ino` con el bloque completo:

```cpp
// Curso PX-32 - Leccion 18: identificar los cuatro motores.
// El sketch queda detenido hasta cambiar EJECUTAR_PRUEBA a true.
const bool EJECUTAR_PRUEBA = false;

// Orden fisico confirmado por el manual OSOYOO.
const byte PWM_BK1 = 9;   // Frontal derecho
const byte BK1_IN1 = 22;
const byte BK1_IN2 = 24;
const byte PWM_BK3 = 10;  // Frontal izquierdo
const byte BK3_IN3 = 26;
const byte BK3_IN4 = 28;
const byte PWM_AK1 = 11;  // Trasero derecho
const byte AK1_IN1 = 5;
const byte AK1_IN2 = 6;
const byte PWM_AK3 = 12;  // Trasero izquierdo
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

void probarMotor(byte pinPwm, byte pin1, byte pin2) {
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  analogWrite(pinPwm, 100);
  delay(500);
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
  probarMotor(PWM_BK1, BK1_IN1, BK1_IN2);
  probarMotor(PWM_BK3, BK3_IN3, BK3_IN4);
  probarMotor(PWM_AK1, AK1_IN1, AK1_IN2);
  probarMotor(PWM_AK3, AK3_IN3, AK3_IN4);
  detenerTodos();
}

void loop() {
  detenerTodos();
}
```

3. 🟢 Observa que `probarMotor()` recibe tres parámetros. En cada llamada cambian el pin PWM y las dos entradas; la potencia `100`, el pulso de 500 ms y la pausa de 1200 ms permanecen iguales.

4. 🟢 Lee las cuatro llamadas de `setup()` y levanta las tarjetas en ese orden. Predice: `BK1 -> BK3 -> AK1 -> AK3`. Si no puedes señalar cada esquina sin girar el robot, corrige primero tu posición.

> **[PENDIENTE VISUAL]**
> - **Tipo:** plano cenital anotado.
> - **Objetivo:** fijar una orientación canónica para nombres, conectores y pines de los cuatro motores.
> - **Descripción:** PX-32 visto desde arriba, frente en la parte superior y una silueta del estudiante detrás; cada esquina une posición, conector y trío de pines.
> - **Elementos que deben señalarse:** frontal derecha BK1 D9/D22/D24; frontal izquierda BK3 D10/D26/D28; trasera derecha AK1 D11/D5/D6; trasera izquierda AK3 D12/D7/D8.
> - **Fuente técnica:** manual OSOYOO, https://osoyoo.com/manual/2021006600-2026.pdf, páginas 7 y 13; guía Model Y, https://osoyoo.com/2022/02/25/osoyoo-model-y-4-channel-motor-driver/.
> - **Texto alternativo sugerido:** “Plano superior de PX-32 que asigna un conector y tres pines a cada esquina”.

## Deja que el robot responda una esquina a la vez

5. 🟢 Cambia solo `EJECUTAR_PRUEBA` a `true`.

6. 🟡 Con baterías fuera, conecta USB, selecciona Mega y el puerto identificado, verifica y sube. Retira el USB al finalizar.

7. 🟢 Colócate otra vez detrás de PX-32 y ensaya el orden con las tarjetas. No sostengas ninguna tarjeta encima de una rueda.

8. 🔴 El adulto instala las celdas y energiza el robot elevado. Después de la espera de quince segundos, cada motor debe girar 500 ms y quedar separado del siguiente por una pausa clara.

9. 🟢 Señala en tu dibujo la esquina que realmente se mueve en cada pulso. Registra `coincide` o escribe la posición observada; no cambies los rótulos para hacer que el resultado parezca correcto.

10. 🔴 Si dos ruedas giran juntas, una posición no coincide, una rueda no se detiene o el soporte se mueve, el adulto apaga. No continúes la secuencia para reunir “más datos” si ya apareció un resultado inseguro.

11. 🟢 El mapa queda validado solo si los cuatro pulsos coinciden con la tabla en el orden exacto. Si el sentido de giro no parece avance, anótalo aparte: esta clase confirma **identidad**, no recalibra el cableado.

12. 🔴 El adulto apaga y retira baterías. Restaura `EJECUTAR_PRUEBA = false` y sube la versión neutral usando únicamente USB.

## Cuando el mapa y el robot discuten

| Resultado | Decisión |
|---|---|
| BK1 mueve una esquina distinta | Detén; compara la conexión física con la tabla de la página 7. Solo el adulto corrige cableado sin fuentes |
| K1 y K2 del mismo canal se mueven juntos | Es coherente con salidas sincronizadas del Model Y; PX-32 debería usar el K1 documentado para cada motor |
| Un pulso falta | Revisa la llamada y luego, sin energía, el conector correspondiente y el cable de seis posiciones de su zona |
| El orden es correcto pero un sentido está invertido | Regístralo; no intercambies cables durante esta clase. Contrasta la convención `IN1=HIGH, IN2=LOW` |
| Dos pulsos parecen uno largo | Verifica `detenerTodos(); delay(1200);` dentro de `probarMotor()` |

## Lecturas y videos para explorar

- [Carro 4x4 con Arduino](https://www.youtube.com/watch?v=2_2J0B-1PYE) — Español; video; 7 min.
**Por qué este recurso:** confirma con un carro real de cuatro motores la idea de esta lección: cada esquina es un motor independiente con su propio control.

- [Plataforma robótica 4x4 y puente H L298N](https://www.youtube.com/watch?v=GdO3Dt1IaFU) — Español; video; 15 min (verlo por partes).
**Por qué este recurso:** profundiza en cómo un solo driver gobierna cuatro motores y cómo el programa decide qué esquina se mueve; divídelo en dos partes.

- [Cómo armar y programar un auto robot (Smart Car 4WD) con Arduino](https://www.mechatronicstore.cl/como-armar-y-programar-un-auto-robot-smart-car-4wd-con-arduino/) — Español; lectura con fotos y código; ~12 min.
**Por qué este recurso:** estimula porque muestra un proyecto completo paso a paso — chasis, driver, pines y programa — con el que puedes comparar la tabla BK1/BK3/AK1/AK3 de PX-32.

Intenta reconstruir la tabla de las cuatro esquinas sin mirar y luego corrígela con estos recursos: recordar no sustituye verificar.

## Referencias técnicas de la clase

- [Manual oficial de OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), páginas 7 y 13, posición de motores y cableado Model Y.
- [Guía oficial del Model Y](https://osoyoo.com/2022/02/25/osoyoo-model-y-4-channel-motor-driver/), pares de salidas, control independiente y código de ejemplo.
- [Pinout oficial de Arduino Mega 2560](https://docs.arduino.cc/resources/pinouts/A000067-full-pinout.pdf), identificación de D5-D12 y D22-D28.

## Cuéntale a papá

Colócate detrás del robot y nombra las cuatro esquinas en menos de un minuto, pero justifica cada una con conector y pines. Si alguna no coincidió, muéstrale el registro sin proponer un recableado improvisado.

La [Lección 19](19-ruedas-mecanum-y-fuerzas-diagonales.md) cambia la pregunta: ya sabes cuál rueda gira; ahora descubrirás por qué sus rodillos empujan en diagonal.
