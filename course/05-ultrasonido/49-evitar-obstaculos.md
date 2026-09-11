# Lección 49 — Evitar obstáculos

## El hito: PX-32 conduce, frena y decide solo

Todo el bloque ha sido un entrenamiento en cámara lenta para esta sesión. La física del sonido (39–42), el grito y el cronómetro (43–44), los centímetros (45), la desconfianza estadística (46), el cuello (47) y el mapa (48). Hoy se une todo en el comportamiento más espectacular del curso hasta ahora: **PX-32 avanza solo, detecta un obstáculo, se detiene, mira a ambos lados y esquiva hacia donde hay espacio.** Es el hito 49, y el manual del fabricante trae exactamente esta demo como su "Lección 2" — nosotros la construiremos con la política de seguridad de este curso, que es más estricta que la del fabricante.

Porque un robot que decide no es un robot que improvisa. El de hoy sigue una **política** — un puñado de reglas pensadas antes de encender nada, exactamente como la tabla de siete patrones de la Lección 37. Las reglas son estas:

1. **STOP primero.** ¿Frente bloqueado, lectura no fiable (-1), o los dos lados bloqueados? La única respuesta válida es ruedas detenidas. Ninguna lectura ausente autoriza avanzar: para un robot, "no sé qué hay adelante" se trata igual que "hay algo adelante".
2. **Después mirar.** Con el robot ya detenido, la cabeza barre 45 y 135 (la rutina exacta de la Lección 48).
3. **Girar solo con evidencia.** Se gira hacia el lado con más espacio, y únicamente si ese lado supera la distancia segura. Si ambos lados están bloqueados o sus lecturas no son fiables… se queda en STOP y espera a que un humano decida.
4. **Nunca correr.** Potencia 60 de 255, giros breves de 350 ms, y siempre re-medir después de cada maniobra.

Fíjate en la regla 1, porque es la que separa un juguete de un robot: el fabricante advierte en su solución de problemas que su demo puede comportarse raro si el sensor está mal conectado. Nuestra respuesta a eso no es "ojalá no pase", sino una política que convierte cualquier lectura sospechosa en **freno**. Un sensor flojo, un cable suelto, un eco que se pierde: todo termina en el mismo lugar seguro — parado.

## Lo que necesitas

- PX-32 ensamblado, servo alineado al frente en 90° (Lección 47), sensor verificado (Lecciones 43–46).
- Tu cuaderno con el dato del ángulo 45° ("45 apunta hacia mi ___"): hoy ese apunte se convierte en una constante del programa.
- Computador con Arduino IDE 2, cable USB y **baterías 18650 con carga** (adulto).
- El sketch [49-evitar-obstaculos.ino](../../code/educational/49-evitar-obstaculos/49-evitar-obstaculos.ino).
- Los dos soportes rígidos de la Lección 20 (fase B).
- Un obstáculo grande y blando para la pista: una caja de cartón, una almohada firme o similar, de al menos 30 cm de frente. **Nada de sillas, mesas ni nada que pueda voltearse.**
- Un piso despejado de al menos 2 m al frente del robot, sin escalones, mascotas, cables ni cosas frágiles.

🟢 Programar, predecir y observar es tuyo. 🟡 El adulto presencia el USB y la calibración de constantes. 🔴 Baterías, interruptor, arranque en piso y corte de emergencia: el adulto, con la mano cerca del interruptor siempre.

## El programa: la política hecha código

1. 🟢 Abre el `.ino` y verifica que coincida con este bloque:

```cpp
// Curso PX-32 - Leccion 49: evitar obstaculos (hito del bloque).
// Politica: STOP primero, mirar los dos lados y girar solo
// con evidencia. Ninguna lectura no fiable autoriza avanzar.

#include <Servo.h>

// FASE A: false -> solo imprime las decisiones.
// FASE B y C: true -> las ejecuta con los motores.
const bool MOTOR_ACTIVO = false;

// Tu evidencia de la Leccion 48: con el sensor mirando al frente,
// el angulo 45 apunta hacia TU izquierda? (true o false)
const bool GRADOS_45_MIRA_A_TU_IZQUIERDA = true;

const float DISTANCIA_SEGURA_CM = 25.0;
const byte POTENCIA_AVANCE = 60;
const byte POTENCIA_GIRO = 55;

// Orden de los motores: frontal derecho, frontal izquierdo,
// trasero derecho, trasero izquierdo (Lecciones 20 y 38).
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

const byte TRIG = 30;
const byte ECHO = 31;
const byte PIN_SERVO = 13;
const unsigned long TIMEOUT_US = 30000UL;
const float SONIDO_CM_POR_US = 0.0343;

Servo cabeza;

void controlarMotor(
  byte pinPwm,
  byte pin1,
  byte pin2,
  int sentido,
  byte potenciaPwm
) {
  if (sentido > 0) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    analogWrite(pinPwm, potenciaPwm);
  } else if (sentido < 0) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    analogWrite(pinPwm, potenciaPwm);
  } else {
    analogWrite(pinPwm, 0);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }
}

void moverConPotencia(
  int frontalDerecho,
  int frontalIzquierdo,
  int traseroDerecho,
  int traseroIzquierdo,
  byte potenciaPwm
) {
  controlarMotor(PWM_BK1, BK1_IN1, BK1_IN2, frontalDerecho, potenciaPwm);
  controlarMotor(PWM_BK3, BK3_IN3, BK3_IN4, frontalIzquierdo, potenciaPwm);
  controlarMotor(PWM_AK1, AK1_IN1, AK1_IN2, traseroDerecho, potenciaPwm);
  controlarMotor(PWM_AK3, AK3_IN3, AK3_IN4, traseroIzquierdo, potenciaPwm);
}

void detenerTodos() {
  moverConPotencia(0, 0, 0, 0, 0);
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

void avanzar() {
  moverConPotencia(+1, +1, +1, +1, POTENCIA_AVANCE);
}

void girarHaciaLaIzquierda() {
  moverConPotencia(+1, -1, +1, -1, POTENCIA_GIRO);
}

void girarHaciaLaDerecha() {
  moverConPotencia(-1, +1, -1, +1, POTENCIA_GIRO);
}

void girarHaciaElLadoDe45() {
  if (GRADOS_45_MIRA_A_TU_IZQUIERDA) {
    girarHaciaLaIzquierda();
  } else {
    girarHaciaLaDerecha();
  }
}

void girarHaciaElLadoDe135() {
  if (GRADOS_45_MIRA_A_TU_IZQUIERDA) {
    girarHaciaLaDerecha();
  } else {
    girarHaciaLaIzquierda();
  }
}

float medirDistanciaCm() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  unsigned long us = pulseIn(ECHO, HIGH, TIMEOUT_US);

  if (us == 0 || us > 23200UL) {
    return -1.0;  // lectura no fiable: se trata como riesgo
  }

  return us * SONIDO_CM_POR_US / 2.0;
}

void setup() {
  prepararMotores();
  pinMode(TRIG, OUTPUT);
  digitalWrite(TRIG, LOW);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);
  cabeza.attach(PIN_SERVO);
  cabeza.write(90);  // alineacion: sensor mirando al frente
  delay(1000);

  if (MOTOR_ACTIVO) {
    Serial.println("MODO: EVASION ACTIVA");
  } else {
    Serial.println("MODO: SOLO IMPRIMIR");
  }

  if (GRADOS_45_MIRA_A_TU_IZQUIERDA) {
    Serial.println("angulo 45 mira a la IZQUIERDA (segun tu cuaderno)");
  } else {
    Serial.println("angulo 45 mira a la DERECHA (segun tu cuaderno)");
  }

  delay(3000);  // tres segundos de calma antes de empezar
}

void loop() {
  float frente = medirDistanciaCm();

  if (frente < 0 || frente < DISTANCIA_SEGURA_CM) {
    // 1) STOP: siempre antes que cualquier maniobra.
    detenerTodos();
    Serial.println("STOP: obstaculo o lectura no fiable");

    // 2) Mirar los dos lados con la cabeza.
    cabeza.write(45);
    delay(500);
    float lado45 = medirDistanciaCm();

    cabeza.write(135);
    delay(500);
    float lado135 = medirDistanciaCm();

    cabeza.write(90);
    delay(300);

    Serial.print("angulo 45: ");
    if (lado45 < 0) {
      Serial.println("no fiable");
    } else {
      Serial.print(lado45, 1);
      Serial.println(" cm");
    }

    Serial.print("angulo 135: ");
    if (lado135 < 0) {
      Serial.println("no fiable");
    } else {
      Serial.print(lado135, 1);
      Serial.println(" cm");
    }

    // 3) Elegir con evidencia: lado libre y fiable, o nada.
    bool libre45 = (lado45 >= DISTANCIA_SEGURA_CM);
    bool libre135 = (lado135 >= DISTANCIA_SEGURA_CM);

    if (!libre45 && !libre135) {
      Serial.println("AMBOS LADOS BLOQUEADOS: me quedo en STOP");
    } else if (libre45 && (!libre135 || lado45 >= lado135)) {
      Serial.println("GIRO hacia el lado del angulo 45");
      if (MOTOR_ACTIVO) {
        girarHaciaElLadoDe45();
        delay(350);
        detenerTodos();
      }
    } else {
      Serial.println("GIRO hacia el lado del angulo 135");
      if (MOTOR_ACTIVO) {
        girarHaciaElLadoDe135();
        delay(350);
        detenerTodos();
      }
    }
  } else {
    Serial.println("LIBRE: avanzar");
    if (MOTOR_ACTIVO) {
      avanzar();
    }
  }

  delay(40);
}
```

2. 🟢 **Lo conocido, todo.** El bloque de motores (pines, `controlarMotor`, `moverConPotencia`, `detenerTodos`, `prepararMotores`, `avanzar`, giros) es **literalmente el de las Lecciones 20 y 38**: no hay una sola línea nueva. `medirDistanciaCm()` es la de la Lección 48. El corazón nuevo cabe en una frase: el `loop()` es la **política de los cuatro pasos** convertida en `if`.

3. 🟢 **Tu cuaderno, codificado (otra vez).** Busca `GRADOS_45_MIRA_A_TU_IZQUIERDA`: es tu observación de la Lección 47 convertida en decisión. Gracias a ella, "girar hacia el lado del 45" sabe si eso significa ruedas a la izquierda o a la derecha. Como `IR1_DEL_LADO_IZQUIERDO` en la Lección 38: el robot obedece a tu evidencia, no a la suerte de fábrica. Si tu cuaderno dice que 45 mira a tu **derecha**, cámbiala a `false` antes de cargar nada.

4. 🟢 **La bandera de permiso.** `MOTOR_ACTIVO` funciona igual que en las Lecciones 30 y 38: en `false`, el programa **piensa en voz alta** —imprime cada decisión— pero la única orden que llega a los motores es `detenerTodos()`. Las dos primeras líneas del monitor te dicen el modo y el lado asumido del 45: léelas **siempre** antes de dar por buena una carga.

5. 🟢 **Sigue la lógica de elección.** `libre45` y `libre135` son `bool` (Lección 09): solo pueden ser `true` o `false`. Para ser "libre" hay que ser fiable **y** superar 25 cm — compara con `>=`: una pared a exactamente 25,0 cm cuenta como libre. La línea clave de la elección es `libre45 && (!libre135 || lado45 >= lado135)`: "el 45 está libre, y además el 135 no lo está o el 45 tiene tanto espacio como él". Con paréntesis, una condición larga se lee como tú hablas. Y en la fase de giro: `delay(350)` y **STOP de nuevo** — el giro es un mordisco corto, no una maniobra a ciegas; después de cada mordisco el bucle vuelve a medir.

6. 🟢 **Predice el ensayo completo.** Antes de la fase A, escribe qué imprimirá el programa (y qué harán las ruedas en B y C) en estos cuatro escenarios: (a) frente despejado, (b) obstáculo a 20 cm y espacio a un solo lado, (c) obstáculo y **ambos** lados con libros a 20 cm, (d) sensor tapado con la mano (lectura no fiable… o 4 cm de mano: ambas respuestas frenan, ¿por qué?).

## Fase A: el robot solo piensa (USB)

7. 🟡 El adulto conecta el USB. Verifica juntas: `MOTOR_ACTIVO` en `false`, la constante del lado del 45 según el cuaderno. Sube el sketch, monitor a 9600. Deben aparecer "MODO: SOLO IMPRIMIR" y el lado del 45: tu comprobante.

8. 🟢 **Interroga la política sin riesgo.** Pon tu mano a 10 cm del sensor: el monitor debe dictar `STOP`, las dos lecturas laterales, y su decisión (`GIRO…` o `AMBOS LADOS BLOQUEADOS`). Coloca libros a los costados según los escenarios (b) y (c) de tu predicción y verifica cada respuesta. Ninguna rueda debe girar. Si alguna decisión sale al revés, **corrígela aquí**, en la pantalla, donde los errores son gratis — igual que en las lecciones 30 y 38.

## Fase B: ruedas levantadas

9. 🟡 Apagado y sin baterías, cambien únicamente `MOTOR_ACTIVO = false` por `true`. Solo USB, sube, verifica las dos líneas del monitor. Cierra el monitor: la evidencia ahora son las ruedas y la cabeza.

10. 🔴 El adulto retira el USB, instala las celdas y enciende el robot **sobre los dos soportes**, mano junto al interruptor. Respeta los tres segundos de calma.

11. 🟢 **Verifica la coreografía completa en el aire.** Mano a 10 cm frente al sensor: STOP inmediato (regla 1), la cabeza barre ambos lados, y las ruedas giran en el sentido de la decisión **solo 350 ms** y vuelven a frenar. Retira la mano: avance continuo y tranquilo (la cabeza al frente). Tapa el sensor con la palma: STOP y barrido — la mano a centímetros es "no fiable" por la zona ciega de la Lección 45 o una lectura cortísima; ambas cosas frenan. Practica el freno tres veces: es tu actuación estrella de seguridad.

12. 🔴 Ante una rueda inesperada, ausencia de STOP, zumbido, calor u olor: el adulto corta energía y la fase de piso queda cancelada hasta revisar.

## Fase C: en el piso

13. 🔴 Solo si la fase B fue limpia: el adulto apaga, baja el robot y lo coloca a al menos 1,5 m del obstáculo, sensor al frente, área despejada, nadie delante. Enciende, respeta los tres segundos, y aléjense del frente del robot.

14. 🟢 **Observa el hito con calma.** El robot avanza despacio hacia la caja; al llegar al umbral (25 cm) se detiene, **mira** izquierda y derecha, y esquiva hacia el lado con espacio con un giro corto; después vuelve a medir y sigue. Camina junto a él (nunca delante) y narra lo que hace en voz alta: "mide… frena… escanea… decide". Ese relato ES el bucle del programa.

15. 🟢 **El caso honrado.** Si el robot queda encerrado o ambos lados dan lecturas no fiables, debe quedarse en STOP sin luchar. No es un fracaso: es la regla 3 funcionando — un robot que sabe quedarse quieto es mejor robot que uno que improvisa.

16. 🔴 Al terminar, el adulto apaga y retira las celdas. Ustedes devuelven `MOTOR_ACTIVO = false`, conectan solo USB, suben la versión neutral y comprueban "MODO: SOLO IMPRIMIR". Un PX-32 guardado no debería poder moverse aunque se encienda por accidente.

El hito está completo cuando viviste las tres fases en orden, el robot esquivó al menos una vez hacia el lado correcto, se detuvo ante la caja y ante la falta de eco fiable, y puedes explicar el bucle completo — medir, frenar, escanea, decidir — señalando cada parte del sketch.

> **[PENDIENTE VISUAL]**
> - **Tipo:** diagrama de flujo de la política de decisión.
> - **Objetivo:** que el niño vea la política de los cuatro pasos como un mapa de caminos con una sola salida peligrosa controlada: STOP.
> - **Descripción:** diagrama de flujo vertical: "medir frente" → rombo "¿fiable y >= 25 cm?" → sí: "AVANZAR (vuelve a medir)"; no: "STOP" → "escanear 45 y 135" → rombo "¿algún lado libre y fiable?" → sí: "giro corto 350 ms hacia ese lado → vuelve a medir"; no: "me quedo en STOP".
> - **Elementos que deben señalarse:** las dos salidas hacia STOP (frente no seguro y lados no seguros), la flecha de retorno a "medir" tras cada acción, los rótulos de fase (A: solo imprime, B/C: ejecuta).
> - **Fuente técnica:** política del curso sobre la demo de evasión del manual OSOYOO, https://osoyoo.com/manual/2021006600-2026.pdf, pp. 26–33.
> - **Texto alternativo sugerido:** "Diagrama de flujo de la evasión de obstáculos: medir, frenar, escanear ambos lados, girar solo con evidencia o quedarse en STOP".

## Desafío: el probador de políticas

De pizarra, con el robot ya guardado: tu hermano o tu padre te dicta un escenario ("frente a 40 cm, izquierda a 10, derecha a 80") y tú respondes como el robot ("LIBRE avanzo… no: frente bloqueado… STOP… escano… giro hacia la derecha") señalando la rama del `if` en el sketch que se ejecuta. Cinco rondas. Si quieres la versión con código, sube `DISTANCIA_SEGURA_CM` a 40 en fase A y descubre cuánto antes empieza a frenar el robot — un número, todo un carácter.

## Si no funciona

| Síntoma | Qué revisar | Acción |
|---|---|---|
| No pasa de "MODO: SOLO IMPRIMIR" a moverse | ¿Olvidaron `MOTOR_ACTIVO = true` para la fase B? | Es la bandera, no el hardware; cámbienla y suban de nuevo |
| Frena pero gira hacia el lado bloqueado | ¿`GRADOS_45_MIRA_A_TU_IZQUIERDA` coincide con tu cuaderno? | Verifica desde atrás del robot; corrige la constante y vuelve a la fase A, nunca cambies signos de motor a ciegas |
| Nunca frena: choca contra la caja | ¿Cables Trig/Echo bien en D30/D31? ¿Objeto blando o inclinado? | El manual del fabricante da la misma pista para su demo: revisar la conexión del sensor; prueba con caja grande y plana, de frente |
| Se detiene aunque el frente está despejado | ¿Suelo, zócalo o sombra delante? ¿Lectura no fiable repetida? | Sube el sensor de dudas: apunta el frente al aire libre; si sigue en STOP, fase A con el monitor para ver la lectura exacta |
| Gira sin parar en circulitos | ¿Los lados alternan libre/bloqueado muy rápido? | Normal cerca de esquinas: cada giro es de 350 ms y re-mide; aleja el robot de las paredes o ensancha el espacio |
| Titubea, reinicia o pierde fuerza | ¿Celdas gastadas o conectores flojos? | 🔴 El adulto corta energía y revisa la ruta de potencia (baterías → portabaterías → VIN del Model Y, según el [mapa de conexiones](../../docs/reference/mapa-conexiones-robot.md)) antes de reintentar |
| La cabeza no barre al frenar | ¿El servo centrado en 90° al encender? | Repite la alineación de la Lección 47: soporte al frente con todo apagado |

## Lecturas y videos para explorar

- [Velocidad, frecuencia y longitud de onda del sonido](https://openstax.org/books/physics/pages/14-1-speed-of-sound-frequency-and-wavelength) — Inglés; libro abierto; 12 min. Aprenderás velocidad, frecuencia y longitud de onda del sonido. Esencial.
- [Biblioteca Servo](https://docs.arduino.cc/libraries/servo/) — Inglés; referencia oficial Arduino; 10 min. Aprenderás biblioteca servo. Opcional.

## Referencias técnicas de la clase

- [Manual OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), pp. 26–33: demo de evasión del fabricante (barrido 45/90/135 antes de decidir), alineación del servo y solución de problemas de conexión del sensor (VCC→5V, TRIG→D30, ECHO→D31, GND→GND).
- [Mapa canónico de conexiones](../../docs/reference/mapa-conexiones-robot.md): sensor, servo y motores.
- [Referencia del lenguaje Arduino](https://docs.arduino.cc/language-reference/): `bool`, operadores lógicos `&&`/`||`, `if...else` y `analogWrite()`.
- [Guía de sensores del curso](../../docs/reference/sensores.md): regla de integración — Serial primero, decisión impresa después, movimiento al final.

## Cuéntale a papá

Piloteen juntos la fase final y luego explícale la política con tus palabras: frenar primero, mirar después, girar solo con evidencia — y por qué un robot que se queda quieto cuando no entiende es más seguro que uno valiente. Muéstrale en el sketch la constante `GRADOS_45_MIRA_A_TU_IZQUIERDA` y cuéntale que esa línea existe gracias a tu cuaderno, igual que la del lado de IR1 en la Lección 38. Marca el **hito 49** en [PROGRESS.md](../../PROGRESS.md): PX-32 ya ve con sonido, decide y esquiva.

Y un cambio de sentido se avecina: el sonido necesitaba aire para viajar (Lección 39), pero en la [Lección 50](../06-bluetooth/50-radio-otra-region-del-espectro.md) PX-32 estrenará ondas que cruzan el vacío sin problema — la radio, prima de la luz que ya usaste para seguir líneas. Bienvenido al bloque de Bluetooth.
