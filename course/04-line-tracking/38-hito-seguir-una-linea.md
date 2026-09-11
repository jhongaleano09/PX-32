# Lección 38 — Hito: seguir una línea

## El día que PX-32 lee el piso

Hoy se junta todo. La física de la reflexión (Lección 25), el mapa de canales (32), el umbral calibrado para tu luz (33), el patrón (34), el array (35), la posición con signo (36) y la política con su STOP dominante (37). El cuarto empleo de la cadena entra hoy: el piloto. PX-32 va a seguir una línea negra pintada en el piso, corrigiendo su rumbo solo, cientos de veces por segundo. Es el hito 38 del curso.

Pero antes de la gloria, la honestidad del método: **el robot no "entiende" la línea**. Lo que hace, veinte veces por segundo, es esto: toma una foto del piso, calcula un número con signo, lo pasa por la tabla de la Lección 37 y ejecuta una de cinco órdenes. Foto, número, orden. Foto, número, orden. Que ese bucle tan simple produzca un robot que serpentea con gracia por una pista es una de las bellezas de la **realimentación**: corregir en función del resultado propio, una y otra vez, sin planear el futuro — solo reaccionar al presente.

Y la velocidad es parte del contrato. Un seguidor rápido se sale en la primera curva porque el bucle foto-número-orden no le alcanza para reaccionar; un seguidor moderado corrige a tiempo. Por eso hoy avanzamos a 65 de 255 de potencia y corregimos a 55: menos de un tercio de la fuerza de los motores. La prisa es enemiga del hito.

La sesión tiene tres fases, como el hito de la mano (Lección 30): primero el robot solo habla (USB), luego camina en el aire (soportes) y solo al final toca el piso. Cada fase protege a la siguiente.

## Lo que necesitas

- PX-32 con el tracker calibrado con la luz de la pista (Lección 33) y la tabla de siete patrones de la Lección 37 en el cuaderno.
- Computador con Arduino IDE 2 y cable USB.
- El sketch [38-hito-seguir-una-linea.ino](../../code/educational/38-hito-seguir-una-linea/38-hito-seguir-una-linea.ino).
- Los dos soportes rígidos de la Lección 20.
- Baterías 18650 verificadas, bajo control del adulto.
- Para la pista: cinta negra mate de enmascarar de 25 mm (o cartulina negra cortada en tiras de 25 mm) y un piso claro, liso y seco. Necesitarás unos 3–4 metros de línea.
- Un área despejada de al menos 2 m alrededor de la pista, sin escalones, mascotas, cables ni objetos frágiles.
- Tu cuaderno con el lápiz: hoy se toman decisiones de ingeniería y se anotan.

🟢 La programación, la pista y las observaciones son tuyas. 🟡 El adulto presencia el USB, la calibración y los soportes. 🔴 Baterías, interruptor y energía son del adulto: él instala las celdas, enciende, mantiene la mano cerca del interruptor y corta ante cualquier anomalía. Nadie frena ruedas con la mano.

## El programa, por dentro

1. 🟢 Abre el `.ino` y recórrelo completo; debe ser idéntico a este bloque:

```cpp
// Curso PX-32 - Leccion 38: hito de seguimiento de linea.
// Con MOTOR_ACTIVO en false el programa solo imprime la orden.
// La evidencia de tu cuaderno (Leccion 34) decide hacia donde
// girar cuando la linea corre hacia IR1.

const bool MOTOR_ACTIVO = false;

// Escribe true si IR1 quedo a tu IZQUIERDA mirando a PX-32
// desde atras (Leccion 34, paso 12). Si quedo a la derecha,
// cambia a false.
const bool IR1_DEL_LADO_IZQUIERDO = true;

const byte POTENCIA_AVANCE = 65;
const byte POTENCIA_GIRO = 55;
const float TOLERANCIA = 0.4;

// Orden de los motores: frontal derecho, frontal izquierdo,
// trasero derecho, trasero izquierdo (Leccion 20).
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

const int PINES[5] = { A4, A3, A2, A1, A0 };

// Ley de tu cuaderno (Leccion 34): que imprime un canal sobre negro.
const int LECTURA_SOBRE_NEGRO = LOW;

int cuantosVenLinea;

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

void girarHaciaElLadoDeIR1() {
  if (IR1_DEL_LADO_IZQUIERDO) {
    girarHaciaLaIzquierda();
  } else {
    girarHaciaLaDerecha();
  }
}

void girarHaciaElLadoDeIR5() {
  if (IR1_DEL_LADO_IZQUIERDO) {
    girarHaciaLaDerecha();
  } else {
    girarHaciaLaIzquierda();
  }
}

void imprimirPatron() {
  for (int i = 0; i < 5; i++) {
    Serial.print(digitalRead(PINES[i]));
  }
}

float estimarPosicion() {
  int sumaDePesos = 0;
  cuantosVenLinea = 0;

  for (int i = 0; i < 5; i++) {
    if (digitalRead(PINES[i]) == LECTURA_SOBRE_NEGRO) {
      sumaDePesos = sumaDePesos + (i - 2);
      cuantosVenLinea = cuantosVenLinea + 1;
    }
  }

  if (cuantosVenLinea == 0) {
    return 0;
  }

  return float(sumaDePesos) / cuantosVenLinea;
}

void elegirOrdenYEjecutar(float posicion) {
  if (cuantosVenLinea == 0) {
    Serial.println(" -> STOP: linea perdida");
    detenerTodos();
  } else if (cuantosVenLinea == 5) {
    Serial.println(" -> STOP: patron ambiguo");
    detenerTodos();
  } else if (posicion < -TOLERANCIA) {
    Serial.println(" -> CORRIGE hacia IR1");
    if (MOTOR_ACTIVO) {
      girarHaciaElLadoDeIR1();
    } else {
      detenerTodos();
    }
  } else if (posicion > TOLERANCIA) {
    Serial.println(" -> CORRIGE hacia IR5");
    if (MOTOR_ACTIVO) {
      girarHaciaElLadoDeIR5();
    } else {
      detenerTodos();
    }
  } else {
    Serial.println(" -> AVANZA");
    if (MOTOR_ACTIVO) {
      avanzar();
    } else {
      detenerTodos();
    }
  }
}

void setup() {
  prepararMotores();
  for (int i = 0; i < 5; i++) {
    pinMode(PINES[i], INPUT);
  }
  Serial.begin(9600);

  if (MOTOR_ACTIVO) {
    Serial.println("MODO: SEGUIMIENTO ACTIVO");
  } else {
    Serial.println("MODO: SOLO IMPRIMIR");
  }

  if (IR1_DEL_LADO_IZQUIERDO) {
    Serial.println("IR1 al lado IZQUIERDO (segun tu cuaderno)");
  } else {
    Serial.println("IR1 al lado DERECHO (segun tu cuaderno)");
  }

  // Tres segundos de calma antes de empezar.
  delay(3000);
}

void loop() {
  imprimirPatron();
  float posicion = estimarPosicion();
  elegirOrdenYEjecutar(posicion);
  delay(50);
}
```

2. 🟢 **Lo conocido, todo.** Los pines y las funciones de motores son los de las Lecciones 20 y 30; el bloque del tracker es el de la Lección 37 con un solo cambio de nombre: `elegirOrden()` ahora se llama `elegirOrdenYEjecutar()` porque, además de imprimir, ejecuta. La cadena explorador → navegante → piloto está completa.

3. 🟢 **Tu evidencia, codificada.** Busca `IR1_DEL_LADO_IZQUIERDO`: esa constante es tu paso 12 de la Lección 34 convertido en decisión de software. Si escribiste que IR1 queda a tu izquierda viendo el robot desde atrás, déjala en `true`; si quedó a la derecha, `false`. Gracias a ella, `CORRIGE hacia IR1` sabe a qué ruedas girar. El robot obedece a tu medición, no a la suerte de fábrica.

4. 🟢 **La bandera de permiso.** `MOTOR_ACTIVO` funciona como en la Lección 30: mientras esté en `false`, las correcciones y avances se imprimen pero la única orden que llega a los motores es `detenerTodos()`. La primera línea del monitor te dice el modo; la segunda, el lado asumido de IR1. Léelas **siempre** antes de dar por buena una carga.

5. 🟢 **El ritmo del piloto.** `delay(50)`: veinte bucles foto-número-orden por segundo. Es el `delay(200)` de las clases de mesa acelerado para el piso: a velocidad de robot, medio segundo de reacción es una eternidad. Y aun así avanzamos despacio: el bucle rápido compensa, no sustituye, la prudencia.

6. 🟢 **Las dos potencias.** Avanzar a 65 y corregir a 55: girar un poco más suave que avanzar evita pasarse de largo en cada corrección. El manual del fabricante da el mismo consejo para su demo: si el robot no arranca o se sale, se ajustan las potencias de a poco, en pasos de 10.

7. 🟢 **Predice el ensayo completo.** Antes de la fase A, escribe en el cuaderno qué orden imprimirá el programa (y qué harán las ruedas en las fases B y C) cuando: la línea esté centrada, se corra hacia IR1, se corra hacia IR5, y cuando el robot llegue al final de la pista y la pierda.

## Fase A: el robot solo habla (USB)

8. 🟡 El adulto conecta el USB. Verifica que `MOTOR_ACTIVO` esté en `false`, las dos constantes de tu evidencia (`IR1_DEL_LADO_IZQUIERDO` y `LECTURA_SOBRE_NEGRO`), sube el sketch y abre el monitor a 9600 baudios. Deben aparecer "MODO: SOLO IMPRIMIR" y el lado de IR1: tu comprobante antes de tocar nada.

9. 🟢 Desliza la tira de 25 mm bajo la fila como en la Lección 37 y repasa las órdenes: `AVANZA` al centro, `CORRIGE hacia IR1` e `IR5` a los costados, `STOP` sin línea y con la tira ancha. Ninguna rueda debe moverse: no hay baterías ni permiso. Si alguna orden sale al revés, **corrígelo aquí**, en la pantalla, donde los errores son gratis.

## Fase B: ruedas levantadas

10. 🟡 Con el robot apagado y sin baterías, cambia únicamente `MOTOR_ACTIVO = false` por `MOTOR_ACTIVO = true`, conecta solo el USB, sube y verifica las dos líneas del monitor ("MODO: SEGUIMIENTO ACTIVO" y tu lado de IR1). Cierra el monitor: en esta fase la evidencia son las ruedas.

11. 🔴 El adulto retira el USB, instala las celdas y enciende el robot sobre los dos soportes, con una mano junto al interruptor y lejos de las ruedas. Respeta los tres segundos de calma del `setup()`: la tira no debe estar bajo el tracker al encender, para no estrenar el programa con una orden involuntaria.

12. 🟢 **Corrección hacia su línea.** Coloca la tira bajo el extremo IR1 (tu marca de cinta): el robot debe pivotar **hacia el lado de la tira** — hacia donde está la línea, nunca alejándose. Verifica el sentido de las ruedas con la tabla de la Lección 20: para girar hacia un lado, las ruedas de ese lado giran hacia **atrás** y las del lado opuesto hacia **adelante**, como un tanque que gira sobre sí mismo. Repite con la tira en el extremo IR5. Si girara al revés, deténganse: revisa la constante del lado de IR1 contra tu cuaderno.

13. 🟢 **La parada dominante, en vivo.** Retira la tira por completo: las cuatro ruedas se detienen en un instante (el `delay(50)` es el techo). Practica esta maniobra tres veces: es el freno de emergencia del piso.

14. 🔴 Ante una rueda inesperada, ausencia de STOP, zumbido, calor u olor, el adulto corta energía y la fase de piso queda cancelada hasta revisar.

## Fase C: en la pista

15. 🟢 **Construye la pista.** En el piso claro y despejado, tiende la línea negra de 25 mm: primero un tramo recto de medio metro, luego una curva amplia y suave (radio grande, como una rotonda), y de vuelta al recto. El fabricante lo advierte: las curvas muy cerradas tiran al robot fuera de la pista. Deja al menos un metro libre a los costados. Nada de escaleras cerca.

16. 🟢 **Recalibra para la pista.** Con el robot apagado junto a la línea, y el adulto presente 🟡, verifica con la Lección 33 que los LED enciendan sobre la cinta y se apaguen sobre el piso de la pista, con la luz de la habitación real. La calibración de la mesa no siempre sirve en el piso: la altura y la reflexión del suelo son otras.

17. 🔴 Solo si la fase B fue limpia: el adulto apaga, baja el robot y lo coloca con el tracker sobre el inicio de la línea, el centro del frente mirando la cinta. Enciende, respeta los tres segundos y aléjense del frente.

18. 🟢 **Observa cómo trabaja la realimentación.** El robot avanza por el recto con correcciones diminutas — apenas oirás los motores alternarse — y en la curva corrige hacia la línea una y otra vez: `CORRIGE`, `AVANZA`, `CORRIGE`… veinte veces por segundo. No planea la curva: la responde. Camina junto a él (nunca delante) y escucha el ritmo: ese traqueteo de correcciones es el bucle funcionando.

19. 🟢 **La salida honesta.** Al final de la línea, la pista se acaba: el patrón queda sin testigos y el robot debe detenerse solo con `STOP: linea perdida`. Si el robot se sale por un costado antes del final, no lo persigas: el adulto corta energía 🔴, y revisen la tabla de abajo antes de reintentar.

20. 🔴 Al terminar, el adulto apaga y retira las celdas. Ustedes devuelven `MOTOR_ACTIVO = false`, conectan solo USB, suben la versión neutral y comprueban "MODO: SOLO IMPRIMIR". Un PX-32 guardado no debería poder moverse aunque se encienda por accidente.

El hito está completo cuando viviste las tres fases en orden, el robot recorrió la pista con la línea bajo el frente en todo momento, se detuvo solo al perderla, y puedes explicar el bucle completo — foto, número, orden — señalando cada función del sketch.

> **[PENDIENTE VISUAL]**
> - **Tipo:** secuencia cenital de la corrección sobre la pista.
> - **Objetivo:** mostrar el bucle de realimentación corrigiendo el rumbo en la curva.
> - **Descripción:** cuatro viñetas vistas desde arriba del robot sobre una pista con curva suave: línea centrada bajo el frente con flecha recta (AVANZA), línea desviada hacia un costado con flecha curva (CORRIGE hacia ese lado), robot realineado, y final de pista con robot detenido y rótulo STOP; debajo de cada viñeta, el patrón de cinco dígitos y la orden correspondientes.
> - **Elementos que deben señalarse:** posición de la línea respecto del frente del robot en cada viñeta, flechas de movimiento, patrones y órdenes, rótulo STOP al perder la línea.
> - **Fuente técnica:** manual OSOYOO, https://osoyoo.com/manual/2021006600-2026.pdf, páginas 34–38, comportamiento del coche seguidor sobre pista negra de 20–30 mm.
> - **Texto alternativo sugerido:** "Cuatro vistas superiores del robot corrigiendo su rumbo en una curva de la pista y deteniéndose al final de la línea".

## Desafío: el radio mínimo

Con la sesión terminada y el robot guardado, queda el experimento de pizarra: construye en un papel una pista de prueba con tres curvas de radios distintos (amplia, media, cerrada) y predice cuál perderá el robot primero. Si hay tiempo y batería otro día, contrúyelas en el piso y compruébalo — de a una variable a la vez, como siempre. Anota el radio aproximado donde falló y qué patrón imprimía el monitor justo antes de perderse (pide a tu padre que lea el monitor en voz alta mientras tú observas el robot). Ese número, en tu cuaderno, es ingeniería de verdad: el límite de tu diseño, medido por ti.

## Si no funciona

| Síntoma | Qué revisar | Acción |
|---|---|---|
| No parte en la fase B/C | ¿"MODO: SEGUIMIENTO ACTIVO" apareció al cargar? ¿Celdas con carga? | Verifica la bandera antes de retirar el USB; si las celdas van bajas, el adulto las cambia por cargadas, o suben las potencias de a 10 (consejo del propio manual) |
| Corrige hacia el lado contrario | ¿`IR1_DEL_LADO_IZQUIERDO` coincide con tu cuaderno de la Lección 34? | Repite la verificación con la marca de cinta; corrige la constante y vuelve a la fase B, nunca cambies signos de motores a ciegas |
| Se sale en las curvas | ¿Curvas muy cerradas, velocidad alta o tolerancia ancha? | Ensancha la curva; prueba `POTENCIA_AVANCE` 65→55 o `TOLERANCIA` 0.4→0.3, **un cambio a la vez**, y anota el efecto |
| Avanza zigzagueando en el recto | ¿Correcciones demasiado bruscas para el error? | Prueba `TOLERANCIA` 0.4→0.5 o potencia de giro 55→45; de a un cambio por intento |
| No se detiene al acabar la línea | ¿El piso del final también es oscuro o refleja sombras? | Alarga el final con piso claro; si persiste, es fallo de seguridad: corta energía y revisa la rama `STOP` cargada |
| Las órdenes están al revés desde la fase A | ¿`LECTURA_SOBRE_NEGRO` contradice tu ley de la Lección 34? | Corrígela en la fase A antes de cualquier batería |
| Titubea, reinicia o pierde fuerza | ¿Celdas gastadas o conectores flojos? | 🔴 El adulto corta energía y revisa la ruta de potencia (Lección 03 del bloque de movimiento) antes de reintentar |

## Lecturas y videos para explorar

- [Diagrama correcto del tracker de cinco canales](../../assets/osoyoo-manual/pagina-18-pinout-tracker-correcto.png) — Inglés; manual del fabricante; 8 min. Aprenderás diagrama correcto del tracker de cinco canales. Esencial.
- [Erratas y decisión canónica IR1–IR5](../../docs/reference/errata-osoyoo.md) — Español; referencia interna; 8 min. Aprenderás erratas y decisión canónica ir1–ir5. Opcional.

Con el hito cumplido, PX-32 ya no solo siente: persigue. El bucle foto-número-orden que dejaste andando es el mismo esqueleto que usarán los próximos bloques con otros sensores.

## Referencias técnicas de la clase

- [Manual oficial de OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), páginas 34–38: proyecto de seguimiento de línea del fabricante, pista negra de 20–30 mm sobre piso claro, curvas no demasiado cerradas y ajuste de potencias en pasos pequeños.
- [Guía oficial del Model Y](https://osoyoo.com/2022/02/25/osoyoo-model-y-4-channel-motor-driver/), pines de habilitación y dirección reutilizados de las Lecciones 20 y 30.
- [Referencia del lenguaje Arduino](https://docs.arduino.cc/language-reference/), `if...else`, `digitalRead()`, `analogWrite()`, funciones con retorno y `delay()`.

## Cuéntale a papá

Piloteen juntos la fase final y luego explícale el bucle con tus palabras: foto, número, orden — y por qué un robot que corrige veinte veces por segundo parece inteligente sin saber nada del futuro. Muéstrale en el sketch la constante `IR1_DEL_LADO_IZQUIERDO` y cuéntale que esa línea de código existe gracias a un experimento que hiciste tú con una tira de papel. Cuéntale qué ajustaste (potencia, tolerancia) y qué efecto tuvo cada cambio. Marca el hito 38 en [PROGRESS.md](../../PROGRESS.md): PX-32 ya sigue una línea solo, y con seguridad.

Con el bloque de línea completo, el curso cambia de sentido — literalmente: en la [Lección 39](../05-ultrasonido/39-el-sonido-es-una-onda-mecanica.md) PX-32 aprenderá a escuchar ecos que nadie puede oír, para medir distancias con sonido.
