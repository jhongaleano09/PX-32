# Lección 20 — Vectores para mover PX-32

## Cuatro giros construyen un movimiento

Un **vector** representa magnitud y dirección. Las fuerzas diagonales de las cuatro ruedas se suman sobre el chasis, pero el programa no escribe fuerzas directamente: ordena a cada motor un sentido y una potencia PWM.

En el sketch, `+1`, `-1` y `0` significan avance lógico, retroceso lógico y STOP para un motor. No son velocidades ni coordenadas. La función `mover()` recibe cuatro signos en este orden fijo:

```text
frontal derecho, frontal izquierdo, trasero derecho, trasero izquierdo
```

De esa combinación nacen seis movimientos:

| Función | FD | FI | TD | TI |
|---|---:|---:|---:|---:|
| `avanzar()` | +1 | +1 | +1 | +1 |
| `retroceder()` | -1 | -1 | -1 | -1 |
| `desplazarDerecha()` | -1 | +1 | +1 | -1 |
| `desplazarIzquierda()` | +1 | -1 | -1 | +1 |
| `girarHorario()` | -1 | +1 | -1 | +1 |
| `girarAntihorario()` | +1 | -1 | +1 | -1 |

Los patrones coinciden con las posiciones 1 a 4 de OSOYOO después de traducirlas al orden del programa. **Giro horario** significa visto desde arriba.

## Dos pruebas, dos espacios

Prepara:

- PX-32, primero sobre los dos soportes rígidos.
- Computador con Arduino IDE 2, cable USB y [20-vectores-para-mover-px-32.ino](../../code/educational/20-vectores-para-mover-px-32/20-vectores-para-mover-px-32.ino).
- Las cuatro tarjetas de conectores y las flechas de la Lección 19.
- Baterías verificadas bajo control adulto.
- Para la segunda prueba, piso horizontal, seco y liso con al menos 2 m libres en cada dirección, sin escaleras, mascotas, pies, cables ni objetos frágiles.
- Dos marcas de cinta en el piso, colocadas por el adulto, para recordar posición inicial y frente; no pegues cinta a las ruedas.

Solo continúa si la [Lección 18](18-cuatro-motores-cuatro-identidades.md) confirmó las cuatro posiciones y la [Lección 19](19-ruedas-mecanum-y-fuerzas-diagonales.md) confirmó el patrón X.

🔴 El adulto retira baterías y USB, apaga interruptores y comprueba que el robot no conserva una prueba activa. Si el mapa o la X no fueron validados, no energiza esta clase.

## Lee el programa como un mapa de movimiento

1. 🟢 Abre el `.ino` y compáralo con el bloque completo:

```cpp
// Curso PX-32 - Leccion 20: seis movimientos Mecanum.
// El sketch queda detenido hasta cambiar EJECUTAR_PRUEBA a true.
const bool EJECUTAR_PRUEBA = false;

// false: prueba los seis patrones con las ruedas elevadas.
// true: prueba solo avance y lateral derecho sobre piso despejado.
const bool PRUEBA_EN_SUELO = false;

const byte POTENCIA_PWM = 100;

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
  controlarMotor(PWM_BK1, BK1_IN1, BK1_IN2, frontalDerecho, POTENCIA_PWM);
  controlarMotor(PWM_BK3, BK3_IN3, BK3_IN4, frontalIzquierdo, POTENCIA_PWM);
  controlarMotor(PWM_AK1, AK1_IN1, AK1_IN2, traseroDerecho, POTENCIA_PWM);
  controlarMotor(PWM_AK3, AK3_IN3, AK3_IN4, traseroIzquierdo, POTENCIA_PWM);
}

void detenerTodos() {
  mover(0, 0, 0, 0);
}

void avanzar() {
  mover(+1, +1, +1, +1);
}

void retroceder() {
  mover(-1, -1, -1, -1);
}

void desplazarDerecha() {
  mover(-1, +1, +1, -1);
}

void desplazarIzquierda() {
  mover(+1, -1, -1, +1);
}

void girarHorario() {
  mover(-1, +1, -1, +1);
}

void girarAntihorario() {
  mover(+1, -1, +1, -1);
}

void esperarYDetener() {
  delay(500);
  detenerTodos();
  delay(1200);
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

void setup() {
  prepararMotores();

  if (!EJECUTAR_PRUEBA) {
    return;
  }

  // Da tiempo para retirar el USB y, despues, energizar desde baterias.
  delay(15000);

  if (PRUEBA_EN_SUELO) {
    avanzar();
    esperarYDetener();
    desplazarDerecha();
    esperarYDetener();
  } else {
    avanzar();
    esperarYDetener();
    retroceder();
    esperarYDetener();
    desplazarDerecha();
    esperarYDetener();
    desplazarIzquierda();
    esperarYDetener();
    girarHorario();
    esperarYDetener();
    girarAntihorario();
    esperarYDetener();
  }

  detenerTodos();
}

void loop() {
  detenerTodos();
}
```

2. 🟢 Sigue una llamada completa: `desplazarDerecha()` entrega cuatro signos a `mover()`; `mover()` asigna uno a cada esquina; `controlarMotor()` convierte cada signo en `HIGH/LOW`, `LOW/HIGH` o PWM `0`.

3. 🟢 Observa que STOP no depende de recordar ocho pines: `detenerTodos()` llama `mover(0, 0, 0, 0)`. Cada cero toma la rama final de `controlarMotor()`.

4. 🟢 Explica las dos banderas. `EJECUTAR_PRUEBA` autoriza cualquier movimiento. `PRUEBA_EN_SUELO` elige entre seis patrones elevados o solo dos movimientos breves sobre el piso. Con ambas en `false`, nada se mueve.

> **[PENDIENTE VISUAL]**
> - **Tipo:** matriz de seis movimientos con flechas.
> - **Objetivo:** conectar cada patrón de signos del código con giros de ruedas, suma de fuerzas y movimiento del chasis.
> - **Descripción:** seis miniaturas cenitales; cada una muestra flechas de giro en las cuatro ruedas, fuerzas diagonales semitransparentes y un vector resultante grande.
> - **Elementos que deben señalarse:** orden FD/FI/TD/TI, signos +1/-1, avance, retroceso, lateral derecho/izquierdo, giro horario/antihorario y STOP entre movimientos.
> - **Fuente técnica:** manual OSOYOO, https://osoyoo.com/manual/2021006600-2026.pdf, página 21; guía Model Y, https://osoyoo.com/2022/02/25/osoyoo-model-y-4-channel-motor-driver/.
> - **Texto alternativo sugerido:** “Seis vistas superiores relacionan patrones de giro de cuatro ruedas Mecanum con el vector resultante del robot”.

## Primera fase: valida patrones con las ruedas elevadas

5. 🟢 Deja `PRUEBA_EN_SUELO = false` y cambia únicamente `EJECUTAR_PRUEBA = true`.

6. 🟡 Sin baterías, conecta USB, elige Mega y puerto, verifica y sube. Retira el USB cuando la carga termine.

7. 🟢 Recorre en voz alta las seis funciones de la rama `else`. Cada una mueve durante 500 ms y queda seguida por 1200 ms de STOP.

8. 🔴 El adulto instala las celdas y enciende el robot sobre soportes. Mantiene una mano cerca del interruptor, nunca cerca de las ruedas.

9. 🟢 Compara los giros observados con la tabla de signos. En el aire no verás trasladarse el chasis; la evidencia es que cada rueda sigue el sentido esperado y que las cuatro se detienen entre patrones.

10. 🔴 Ante una rueda inesperada, falta de pausa, vibración del soporte, zumbido, calor u olor, el adulto apaga y la segunda fase queda cancelada.

## Segunda fase: deja que las fuerzas lleguen al piso

11. 🔴 El adulto apaga, retira las celdas y baja el robot. Cambia `PRUEBA_EN_SUELO = true`; conserva `EJECUTAR_PRUEBA = true`. Conecta solo USB, verifica, sube y vuelve a retirarlo.

12. 🟡 Despejen al menos 2 m alrededor. Todos se colocan detrás de la línea inicial y fuera de la trayectoria. Predice: avance breve, STOP, desplazamiento a la derecha, STOP.

13. 🔴 El adulto pone PX-32 sobre la marca inicial y enciende. Nadie intenta corregir su trayectoria con el pie o la mano. El programa da quince segundos para apartarse; no reduzcas esa espera.

14. 🟢 Observa el **chasis**, no una rueda aislada. Primero debería trasladarse hacia su frente y luego hacia su derecha sin una rotación dominante. Desviaciones pequeñas son posibles por fricción, carga y diferencias entre motores.

15. 🔴 Si el robot gira en lugar de trasladarse, va hacia otro lado, sale del área, no se detiene o amenaza un borde, el adulto corta energía. No “compenses” cambiando signos hasta revisar mapa de motores y patrón X.

16. 🔴 Al terminar, el adulto apaga y retira las celdas. Cambia las dos banderas a `false`, conecta únicamente USB y sube la versión neutral. Comprueba en el código que un encendido futuro no autoriza movimiento.

El hito está completo cuando relacionas al menos un patrón con sus cuatro giros, su suma de fuerzas, el movimiento observado y el STOP posterior.

## Diagnóstico por geometría, código o potencia

| Síntoma | Primera pregunta | Acción segura |
|---|---|---|
| Avanza en diagonal | ¿Una rueda no giró o el piso ofrece fricción desigual? | Vuelve a soportes; prueba identidad antes de modificar signos |
| “Derecha” produce izquierda | ¿Mirabas desde atrás y la X física coincide con la página 21? | Apaga y verifica orientación y orden FD/FI/TD/TI |
| El lateral se convierte en giro | ¿El patrón cargado es `-1,+1,+1,-1`? | Compara la función completa y el mapa de conectores |
| Un giro horario ocurre al revés | ¿Se observó desde arriba y los sentidos individuales coinciden? | Nombra el punto de vista; luego revisa patrón sin energía |
| No arranca en el piso pero sí elevado | La carga y el rozamiento aumentaron | No subas PWM de inmediato; revisa batería, rodillos y superficie |
| Reinicia o pierde fuerza al mover cuatro motores | Puede existir caída de alimentación | Apaga; el adulto revisa celdas, conectores y ruta de potencia |
| No aparece STOP | Es un fallo de seguridad | Corta energía y restaura `esperarYDetener()` y `loop()` antes de otra prueba |

## Lecturas y videos para explorar

- [Vectores: introducción — qué es un vector y sus características](https://www.youtube.com/watch?v=IrTeyyzerjI) — Español; video; 12 min.
**Por qué este recurso:** confirma con ejemplos claros la idea de magnitud y dirección que aplica hoy a cada motor: el signo `+1` o `-1` es la dirección, y el PWM es la magnitud.

- [Adición de Vectores (PhET)](https://phet.colorado.edu/sims/html/vector-addition/latest/vector-addition_es.html) — Español; simulador interactivo; 10-15 min.
**Por qué este recurso:** profundiza permitiendo arrastrar flechas y ver cómo se suman sus componentes, igual que las fuerzas diagonales de tus cuatro ruedas.

- [Mecanum TeleOp (Game Manual 0)](https://gm0.org/en/latest/docs/software/tutorials/mecanum-drive.html) — Inglés técnico sencillo; lectura con diagramas; ~15 min.
**Por qué este recurso:** estimula porque muestra la tabla real que usan los equipos de robótica competitiva para combinar giros de ruedas y obtener cualquier movimiento; el inglés es accesible y muy visual.

Usa la simulación y los diagramas para comprobar cada patrón de signos de `mover()`: la fuente sirve para desafiar tu memoria, no solo para confirmar que acertaste.

## Referencias técnicas de la clase

- [Manual oficial de OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), páginas 21 y 24 a 25, patrones Mecanum, secuencia de prueba y diagnóstico del cable de seis posiciones.
- [Guía oficial del Model Y](https://osoyoo.com/2022/02/25/osoyoo-model-y-4-channel-motor-driver/), posiciones BK1/BK3/AK1/AK3, sentidos y PWM.
- [Referencia del lenguaje Arduino](https://docs.arduino.cc/language-reference/), funciones, parámetros, `if`/`else`, `digitalWrite()` y `analogWrite()`.

## Cuéntale a papá

Elige `desplazarDerecha()` y recórrela desde los cuatro signos hasta el movimiento observado. Luego explica por qué STOP aparece al iniciar, entre movimientos, al terminar y dentro de `loop()`.

Has completado el bloque de movimiento. La [Lección 21](../03-infrarrojo/21-la-luz-transporta-energia.md) dejará las ruedas detenidas para investigar cómo la luz puede transportar información hasta un sensor.
