# Lección 30 — Seguir una mano con prudencia

## El día que PX-32 te siga

Hoy es el hito del bloque de infrarrojo: PX-32 va a seguir tu mano. La pones al frente y avanza despacito; la mueves a la izquierda y gira hacia ella; la escondes y se detiene. El manual de OSOYOO describe exactamente ese comportamiento para su lección de seguimiento de objetos, y ya tienes todas las piezas para construirlo tú, con una diferencia importante: nuestro robot frena antes que el suyo.

La novedad conceptual de hoy es la **política de control**: el conjunto de reglas que traduce lecturas en acciones. No es un componente ni una instrucción: es el diseño de la decisión. La política de hoy tiene cuatro reglas, una por situación de la Lección 29:

- ambos detectan → avanzar lento;
- solo el izquierdo detecta → girar a la izquierda, hacia la mano;
- solo el derecho detecta → girar a la derecha;
- ninguno detecta → **ALTO**.

Fíjate en la última regla. Cuando el sensor no ve nada confiable, la acción más segura no es "seguir con lo último que hacía" ni "buscar": es detenerse. Esa decisión se llama **parada dominante** y es la misma filosofía del `STOP` que protegía los vectores de la Lección 20. Un robot que se detiene al dudar es un robot con el que se puede experimentar tranquilo.

La última regla también pone nombre a un hueco real: la **zona muerta**. Tu mano puede estar demasiado lejos (más allá de los 15 cm de tu calibración) o justo en el pequeño espacio central donde ningún cono la alcanza. En ambos casos los sensores callan y el robot frena. No es un defecto del programa: es la política correcta ante la falta de señal.

¿Y de dónde salen los movimientos? De tu propio trabajo: las funciones de la Lección 20 (`mover` con los signos +1/-1/0 sobre los cuatro motores) reaparecen completas, con `detenerTodos()` como red de seguridad. La novedad es una bandera al inicio, `MOTOR_ACTIVO`: mientras esté en `false`, el programa imprime la decisión pero jamás ordena un movimiento. Primero el robot aprende a decir; después, a hacer.

## Lo que necesitas

- PX-32 ensamblado con sensores calibrados a la ventana de 10/15 cm (Lección 27) y las cuatro situaciones comprobadas (Lección 29).
- Computador con Arduino IDE 2 y cable USB.
- El sketch [30-seguir-una-mano-con-prudencia.ino](../../code/educational/30-seguir-una-mano-con-prudencia/30-seguir-una-mano-con-prudencia.ino).
- Tu mano y la regla para mantener la distancia de trabajo.
- Para la fase de ruedas levantadas: los dos soportes rígidos de la Lección 20.
- Para la fase de piso: un área despejada de al menos 2 m, seca y lisa, sin escaleras, mascotas, cables ni objetos frágiles.
- Baterías 18650 verificadas, bajo control del adulto.
- Tu cuaderno con la ley de lecturas de la Lección 28.

🟢 Puedes leer, cargar y jugar la fase de solo-imprimir con la única energía del USB. 🔴 Las fases con baterías las abre y cierra el adulto: instala celdas, mantiene la mano cerca del interruptor y corte energía ante cualquier anomalía. Nadie frena ruedas con la mano.

## El programa, por dentro

1. 🟢 Abre el `.ino` y recórrelo completo; debe ser idéntico a este bloque:

```cpp
// Curso PX-32 - Leccion 30: seguir una mano con dos sensores IR.
// Con MOTOR_ACTIVO en false el programa solo imprime la decision:
// no ordena ningun movimiento.

const bool MOTOR_ACTIVO = false;
const byte POTENCIA_PRUEBA = 65;

// Orden: frontal derecho, frontal izquierdo, trasero derecho,
// trasero izquierdo.
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

const byte SENSOR_IR_IZQUIERDO = 3;
const byte SENSOR_IR_DERECHO = 2;

// Segun la evidencia de tu cuaderno en la Leccion 28: si tu modulo
// entrega HIGH al detectar, cambia LOW por HIGH en esta linea.
const int LECTURA_AL_DETECTAR = LOW;

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

void mover(
  int frontalDerecho,
  int frontalIzquierdo,
  int traseroDerecho,
  int traseroIzquierdo
) {
  controlarMotor(PWM_BK1, BK1_IN1, BK1_IN2, frontalDerecho, POTENCIA_PRUEBA);
  controlarMotor(PWM_BK3, BK3_IN3, BK3_IN4, frontalIzquierdo, POTENCIA_PRUEBA);
  controlarMotor(PWM_AK1, AK1_IN1, AK1_IN2, traseroDerecho, POTENCIA_PRUEBA);
  controlarMotor(PWM_AK3, AK3_IN3, AK3_IN4, traseroIzquierdo, POTENCIA_PRUEBA);
}

void detenerTodos() {
  mover(0, 0, 0, 0);
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

void ordenarAvance() {
  if (MOTOR_ACTIVO) {
    mover(+1, +1, +1, +1);
  } else {
    detenerTodos();
  }
}

void ordenarGiroIzquierda() {
  if (MOTOR_ACTIVO) {
    mover(+1, -1, +1, -1);
  } else {
    detenerTodos();
  }
}

void ordenarGiroDerecha() {
  if (MOTOR_ACTIVO) {
    mover(-1, +1, -1, +1);
  } else {
    detenerTodos();
  }
}

void setup() {
  prepararMotores();
  pinMode(SENSOR_IR_IZQUIERDO, INPUT);
  pinMode(SENSOR_IR_DERECHO, INPUT);
  Serial.begin(9600);

  if (MOTOR_ACTIVO) {
    Serial.println("MODO: MOVIMIENTO ACTIVO");
  } else {
    Serial.println("MODO: SOLO IMPRIMIR");
  }

  // Tres segundos de calma antes de escuchar los sensores.
  delay(3000);
}

void loop() {
  bool izquierdaDetecta =
      digitalRead(SENSOR_IR_IZQUIERDO) == LECTURA_AL_DETECTAR;
  bool derechaDetecta =
      digitalRead(SENSOR_IR_DERECHO) == LECTURA_AL_DETECTAR;

  if (izquierdaDetecta && derechaDetecta) {
    Serial.println("AVANZAR");
    ordenarAvance();
  } else if (izquierdaDetecta) {
    Serial.println("GIRAR A LA IZQUIERDA");
    ordenarGiroIzquierda();
  } else if (derechaDetecta) {
    Serial.println("GIRAR A LA DERECHA");
    ordenarGiroDerecha();
  } else {
    Serial.println("ALTO");
    detenerTodos();
  }

  delay(150);
}
```

2. 🟢 **Lo conocido.** Los pines de motores, `controlarMotor()`, `mover()` y `detenerTodos()` son los de la Lección 20, con su mismo orden FD/FI/TD/TI. Si allí validaste las identidades y el patrón de la X, hoy no hay nada nuevo de hardware que descubrir.

3. 🟢 **La bandera.** `MOTOR_ACTIVO` funciona como `EJECUTAR_PRUEBA` en la Lección 20: es el permiso. Cada función `ordenar...()` revisa el permiso antes de mover. En `false`, da igual lo que digan los sensores: la única orden que llega a los motores es `detenerTodos()`. La primera línea del monitor te dice en qué modo quedó cargado: léela siempre antes de dar por listo el programa.

4. 🟢 **La potencia.** `POTENCIA_PRUEBA = 65` sobre un máximo de 255: alrededor de un cuarto de la potencia PWM de la Lección 17. Un seguidor lento es un seguidor que te da tiempo de reaccionar.

5. 🟢 **La escalera de decisiones** es la tabla de verdad de la Lección 29 con músculo: misma estructura, pero ahora cada rama imprime su orden y la ejecuta. La rama `else` no imprime "ninguno": imprime **ALTO** y ejecuta `detenerTodos()`. Sin señal confiable, para. Esa es la parada dominante.

6. 🟢 **El giro correcto.** Repasa los signos con la tabla de la Lección 20: `mover(+1, -1, +1, -1)` gira antihorario visto desde arriba, es decir, hacia la izquierda del robot. Cuando solo el sensor izquierdo ve la mano, el robot gira hacia ese lado, hacia donde está la mano. Nunca al contrario.

7. 🟢 **Predice la sesión completa** antes de tocar el robot: escribe qué palabra aparecerá y qué harán las ruedas (nada en la fase A) para cada posición de tu mano.

## Fase A: el robot solo habla (USB)

8. 🟡 El adulto conecta el USB. Deja `MOTOR_ACTIVO = false`, sube el sketch y abre el monitor a 9600 baudios. La primera línea debe decir "MODO: SOLO IMPRIMIR": es tu comprobante del modo seguro.

9. 🟢 Repite el juego de las cuatro situaciones de la Lección 29, ahora leyendo las órdenes: AVANZAR, GIRAR A LA IZQUIERDA, GIRAR A LA DERECHA, ALTO. Ninguna rueda debe moverse ni un milímetro (ni hay baterías, ni permiso). Comprueba también la honestidad de la calibración: mano a 10 cm centrada → AVANZAR; mano a 30 cm → ALTO.

10. 🟢 Busca tu zona muerta con la regla: a qué distancia centrada la palabra pasa de AVANZAR a ALTO, y si existe un hueco central donde dos manos separadas no logran AMBOS. Anota los números. El robot que conoces sus silencios es más fácil de pilotear.

## Fase B: ruedas levantadas

11. 🟡 Con el robot apagado y sin baterías, cambia únicamente `MOTOR_ACTIVO = false` por `MOTOR_ACTIVO = true`, conecta solo el USB, verifica y sube. El monitor debe anunciar "MODO: MOVIMIENTO ACTIVO". Compruébalo y cierra el monitor: en esta fase ya no habrá pantalla, la evidencia serán las ruedas.

12. 🔴 El adulto retira el USB, instala las celdas y enciende el robot sobre los dos soportes, con una mano junto al interruptor y lejos de las ruedas. Respeta los tres segundos de calma del `setup()`: nadie debe tener la mano frente a los sensores al encender, para no estrenar el programa con una orden involuntaria.

13. 🟢 **Mano centrada a 10 cm**: las cuatro ruedas giran despacio hacia adelante, como en la Lección 20. Mira el chasis: no se traslada, está en soportes; tu evidencia es el sentido de las cuatro ruedas y su lentitud.

14. 🟢 **Mano a un costado**: el giro correspondiente. Verifica con la tabla de signos que las ruedas del lado que corresponde van hacia atrás (Lección 20: girar hacia la izquierda usa `+1, -1, +1, -1`). Recorre la mano de lado a lado despacio y observa las correcciones: izquierda, ambos, derecha… así corrige un seguidor.

15. 🟢 **La parada dominante en vivo**: retira la mano hacia arriba y a un lado, saliendo de los conos. Todo se detiene en un abrir y cerrar de ojos (el `delay(150)` es el margen máximo). Practica esta maniobra dos veces más: es tu freno de emergencia.

16. 🔴 Ante cualquier anomalía —una rueda inesperada, ausencia de STOP, zumbido, calor, olor— el adulto corta energía y la fase de piso queda cancelada hasta revisar.

## Fase C: en el piso (opcional, con el adulto al mando)

17. 🔴 Solo si la fase B fue limpia: el adulto apaga, baja el robot y lo coloca en el centro del área despejada. Enciende, respeta los tres segundos y aléjense del frente.

18. 🟢 Coloca tu mano a 10 cm frente al robot y camina hacia atrás despacio, manteniendo la distancia. El robot te sigue. Muévela a los lados para que corrija. Para detenerlo, sube la mano saliendo de los conos: nunca la retire hacia adelante ni dejes que el robot la alcance.

19. 🔴 Al terminar, el adulto apaga y retira las celdas. Ustedes vuelven a `MOTOR_ACTIVO = false`, conectan solo USB y suben la versión neutral, comprobando que el monitor anuncie "MODO: SOLO IMPRIMIR". Un PX-32 guardado no debería poder moverse aunque se encienda por accidente.

El hito está completo cuando viviste las tres fases en orden, tu cuaderno registra la zona muerta, y puedes explicar la política completa con sus cuatro reglas sin leer el código.

> **[PENDIENTE VISUAL]**
> - **Tipo:** secuencia cenital de la política de control.
> - **Objetivo:** mostrar las cuatro reglas de la política con la mano y el robot en cada caso.
> - **Descripción:** cuatro miniaturas vistas desde arriba: mano centrada con robot avanzando (flecha recta corta), mano a la izquierda con robot girando a la izquierda (flecha curva), mano a la derecha con giro a la derecha, mano ausente con robot detenido y rótulo ALTO; debajo de cada miniatura, la línea del código que la produce.
> - **Elementos que deben señalarse:** conos de detección, dirección de giro de las ruedas, flecha de movimiento, las palabras del monitor, rótulo de zona muerta en el caso sin mano.
> - **Fuente técnica:** manual OSOYOO, https://osoyoo.com/manual/2021006600-2026.pdf, página 43, comportamiento de seguimiento de objeto con dos sensores IR.
> - **Texto alternativo sugerido:** "Cuatro vistas superiores muestran al robot avanzando hacia la mano centrada, girando hacia el lado que la detecta y deteniéndose cuando no hay mano".

## Desafío: los secuestradores del seguidor

Sin tocar el código, encuentra el punto débil del seguidor: objetos de la sala que lo "secuestran" (una silla cercana, tu rodilla, la luz del sol). Haz una lista de tres secuestradores potenciales y propón para cada uno una regla de uso del robot que lo evite (por ejemplo, no jugar frente a la ventana soleada). Un buen piloto conoce las trampas de su vehículo.

## Si no funciona

| Síntoma | Qué revisar | Acción |
|---|---|---|
| Avanza sin haber mano (en fase A dice AVANZAR despejado) | ¿Umbral demasiado sensible o luz solar directa? | Recalibra la ventana 10/15 (Lección 27) y repite la fase A; el sol es ruido |
| Las palabras están al revés (NINGUNO con mano al frente) | ¿`LECTURA_AL_DETECTAR` contradice tu ley de la Lección 28? | Corrige la constante y repite la fase A antes de cualquier batería |
| Gira al lado contrario de la mano | ¿Mano en el cono del sensor equivocado o izquierda/derecha invertidos? | Párate detrás del robot; confirma con los LEDs de señal; no cambies signos sin evidencia |
| No se detiene al quitar la mano | ¿La mano sigue dentro de un cono (a los lados)? | Súbela saliendo de los conos; si persiste, es fallo de seguridad: corta energía y revisa la rama `else` cargada |
| En fase B no gira ninguna rueda | ¿Se comprobó "MODO: MOVIMIENTO ACTIVO" durante la carga, antes de retirar el USB? | Falta `MOTOR_ACTIVO = true`; repite la carga con la bandera corregida y verifica el aviso antes de desconectar |
| Se detiene a media persecución en el piso | ¿La mano salió de la distancia de calibración? | Mantén los 10 cm al retroceder; recuerda tu zona muerta anotada |
| Reinicia o pierde fuerza | ¿Celdas con poca carga o conectores flojos? | Apaga; el adulto revisa baterías y ruta de potencia antes de reintentar |

## Lecturas y videos para explorar

- [El espectro electromagnético y el infrarrojo](https://science.nasa.gov/ems/07_infraredwaves/) — Inglés; lectura NASA; 8 min. Aprenderás el espectro electromagnético y el infrarrojo. Esencial.
- [Sensores de PX-32](../../docs/reference/sensores.md) — Español; referencia interna; 6 min. Aprenderás sensores de px-32. Opcional.

Acabas de cumplir la regla de integración de la referencia: primero datos en Serial, luego decisiones impresas, y solo al final motores. Guárdala como método para todos los sensores que vienen.

## Referencias técnicas de la clase

- [Manual oficial de OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), páginas 42 y 43: calibración de los sensores a unos 10 cm y comportamiento de seguimiento (avanza con ambos, gira hacia el lado que detecta, se detiene sin objeto).
- [Guía oficial del Model Y](https://osoyoo.com/2022/02/25/osoyoo-model-y-4-channel-motor-driver/), pines de habilitación y dirección reutilizados de la Lección 20.
- [Referencia del lenguaje Arduino](https://docs.arduino.cc/language-reference/), `if...else`, `&&`, `digitalRead()` y `analogWrite()`.

## Cuéntale a papá

Piloteen juntos la fase final y luego explícale la política de control con sus cuatro reglas, señalando por qué "no hay señal" lleva a ALTO y no a "seguir como si nada". Cuéntale qué fue la zona muerta en sus números y cuáles secuestradores descubrió tu desafío. Marca el hito 30 en [PROGRESS.md](../../PROGRESS.md): PX-32 ya siente el mundo con luz invisible.

Con el bloque de infrarrojo completo, PX-32 cambia de mirada: en la [Lección 31](../04-line-tracking/31-anatomia-del-tracker-de-cinco-canales.md) conocerás el tracker de cinco canales, que usa esta misma física mirando al piso para no perder una línea negra de vista.
