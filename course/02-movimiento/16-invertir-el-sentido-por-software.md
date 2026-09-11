# Lección 16 — Invertir el sentido por software

## La misma rueda, dos recorridos de corriente

En la prueba anterior, AK1 recibió `HIGH` en D5 y `LOW` en D6. Para invertir el giro no hace falta tocar el conector: el programa puede pedir `LOW` en D5 y `HIGH` en D6.

Hay una condición importante entre ambos sentidos: **detener primero**. Cambiar de avance a retroceso mientras el rotor todavía gira aplica un par contrario brusco. El sketch separa los pulsos con 1200 ms de parada.

La palabra **invariante** nombra una regla que debe mantenerse aunque cambie el sentido: antes, entre y después de los movimientos, los cuatro motores tienen una ruta conocida hacia `detenerTodos()`.

## Monta el puesto de observación

Necesitas los mismos soportes rígidos de la [Lección 15](15-primera-prueba-de-un-motor.md), PX-32, computador, cable USB, baterías bajo control adulto y el archivo [16-invertir-el-sentido-por-software.ino](../../code/educational/16-invertir-el-sentido-por-software/16-invertir-el-sentido-por-software.ino).

Añade dos tarjetas con flechas opuestas. Colócalas en la mesa junto a la rueda AK1, sin pegarlas al robot. No necesitas saber aún cuál flecha corresponde al avance del chasis: solo comprobarás que los dos giros son opuestos.

🔴 Tu padre deja el robot sin USB, sin celdas y con los interruptores apagados. Revisa que las cuatro ruedas queden libres y que los soportes no puedan volcar.

## Encuentra la inversión dentro del código

1. 🟢 Abre el `.ino` y confirma que coincide con el programa completo:

```cpp
// Curso PX-32 - Leccion 16: invertir el motor AK1 por software.
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

void girarAK1Adelante(byte potenciaPwm) {
  digitalWrite(AK1_IN1, HIGH);
  digitalWrite(AK1_IN2, LOW);
  analogWrite(PWM_AK1, potenciaPwm);
}

void girarAK1Atras(byte potenciaPwm) {
  digitalWrite(AK1_IN1, LOW);
  digitalWrite(AK1_IN2, HIGH);
  analogWrite(PWM_AK1, potenciaPwm);
}

void setup() {
  prepararMotores();

  if (!EJECUTAR_PRUEBA) {
    return;
  }

  // Da tiempo para retirar el USB y, despues, energizar desde baterias.
  delay(15000);
  girarAK1Adelante(100);
  delay(500);

  // La pausa evita invertir mientras la rueda todavia gira.
  detenerTodos();
  delay(1200);

  girarAK1Atras(100);
  delay(500);
  detenerTodos();
}

void loop() {
  detenerTodos();
}
```

2. 🟢 Pon un dedo sobre las líneas de `girarAK1Adelante()` y otro sobre las de `girarAK1Atras()`, sin tocar el robot. La habilitación D11 y el valor PWM `100` no cambian. Solo se intercambian los estados de D5 y D6.

3. 🟢 Lee la secuencia de `setup()` como si fueran fotogramas:

```text
STOP -> espera 15 s -> sentido 1 durante 0,5 s -> STOP durante 1,2 s
     -> sentido 2 durante 0,5 s -> STOP permanente
```

4. 🟢 Antes de energizar, señala cuál de tus tarjetas usarás para el primer pulso y cuál para el segundo. El criterio no es “derecha” o “izquierda” desde tu posición, sino que ambos sentidos sean opuestos al mirar la misma rueda desde el mismo lugar.

> **[PENDIENTE VISUAL]**
> - **Tipo:** secuencia de cuatro fotogramas.
> - **Objetivo:** hacer visible que la inversión ocurre después de una parada, sin cambiar cables.
> - **Descripción:** acercamiento a AK1 en cuatro estados: D5 HIGH/D6 LOW, PWM 0 con rueda detenida, pausa de 1200 ms y D5 LOW/D6 HIGH; flechas del borde de la rueda cambian de dirección.
> - **Elementos que deben señalarse:** D5, D6, D11, `girarAK1Adelante()`, `detenerTodos()`, 1200 ms, `girarAK1Atras()` y sentidos opuestos.
> - **Fuente técnica:** guía del Model Y, https://osoyoo.com/2022/02/25/osoyoo-model-y-4-channel-motor-driver/; manual OSOYOO, https://osoyoo.com/manual/2021006600-2026.pdf, página 13.
> - **Texto alternativo sugerido:** “Cuatro momentos muestran a AK1 girando, detenido y girando en sentido contrario después de una pausa”.

## Ejecuta y compara

5. 🟢 Cambia solo `EJECUTAR_PRUEBA` a `true`.

6. 🟡 Con baterías fuera y el adulto presente, conecta USB, selecciona Mega y el puerto comprobado, verifica y sube. Si Arduino IDE no muestra carga completada, no pases al hardware.

7. 🟡 Retira el USB. Relee en voz alta el orden de los dos pulsos y muestra al adulto dónde está `detenerTodos()` entre ellos.

8. 🔴 Tu padre instala las celdas verificadas y enciende el robot ya elevado. Durante los quince segundos iniciales todos apartan manos, cabello, ropa y cables. Esa espera no se reduce.

9. 🟢 Mira AK1 desde una posición fija. Levanta una tarjeta durante el primer pulso, bájala durante la pausa y levanta la flecha contraria durante el segundo. Las otras ruedas deben permanecer inmóviles.

10. 🟢 La evidencia correcta tiene tres partes: dos giros opuestos, una parada visible entre ellos y parada estable al final. Si solo recuerdas que “se movió”, repite la explicación usando los estados de D5 y D6; no repitas aún la energización.

11. 🔴 Tu padre apaga y retira las celdas. Con USB como única fuente, restaura `EJECUTAR_PRUEBA = false`, verifica y sube la versión neutral.

## Si la película no tiene cuatro momentos

| Lo observado | Qué revisar antes de otra prueba |
|---|---|
| Los dos pulsos van en el mismo sentido | Compara las dos funciones: deben intercambiar exactamente `HIGH` y `LOW` |
| No existe una pausa clara | Confirma `detenerTodos(); delay(1200);` entre las llamadas |
| Solo funciona un sentido | Apaga; el adulto revisa el cable de seis posiciones M_A y el conector AK1, como indica OSOYOO para fallos de un solo sentido |
| La rueda cambia bruscamente sin detenerse | No repitas; confirma que se cargó este archivo y no una versión modificada sin pausa |
| Otra rueda se mueve | Verifica que las cuatro líneas PWM de `detenerTodos()` escriban `0` y que AK1 use D11/D5/D6 |
| Hay ruido fuerte, atasco, calor u olor | El adulto corta la energía; esto no se corrige aumentando el tiempo ni el PWM |

## Prueba mental: una sola modificación

Sin volver a encender, predice qué cambiaría si `delay(1200)` fuera `delay(2000)`. Los sentidos y la potencia serían iguales; solo aumentaría el intervalo neutral. Esta es una buena modificación experimental porque cambia una variable.

## Lecturas y videos para explorar

- [Conexiones verificadas de Model Y y motores](../../reference/original/osoyoo-mecanum-wheel-robotic-car-kit-v2.pdf) — Inglés; manual del fabricante; 5-10 min. Aprenderás conexiones verificadas de model y y motores. Esencial.
- [Mapa canónico de conexiones](../../docs/reference/mapa-conexiones-robot.md) — Español; referencia interna; 8 min. Aprenderás mapa canónico de conexiones. Opcional.

Busca la diferencia entre una tabla de conexiones —qué pin llega dónde— y una tabla lógica —qué combinación produce cada acción—.

## Referencias técnicas de la clase

- [Guía oficial del Model Y](https://osoyoo.com/2022/02/25/osoyoo-model-y-4-channel-motor-driver/), estados de avance y retroceso de AK1.
- [Datasheet oficial PT5126A](https://www.princeton.com.tw/LinkClick.aspx?fileticket=n1QmI7KLyEk%3D&language=en-US&mid=5406&portalid=0&tabid=3542), tabla funcional y protección frente a conmutación simultánea de la familia del driver.
- [Referencia del lenguaje Arduino](https://docs.arduino.cc/language-reference/), funciones, `digitalWrite()` y `delay()`.

## Cuéntale a papá

Usa las dos tarjetas para representar los pulsos y deja un espacio entre ellas para la pausa. Explícale qué cambió en el software, qué permaneció igual en el hardware y por qué “primero STOP” será una regla permanente.

En la [Lección 17](17-pwm-regular-energia-en-el-tiempo.md) conservarás el sentido y cambiarás cuánto tiempo permanece habilitado el canal dentro de cada ciclo rápido.
