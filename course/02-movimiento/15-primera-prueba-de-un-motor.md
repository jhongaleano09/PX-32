# Lección 15 — Primera prueba de un motor

## Un giro de medio segundo, no una carrera

Hasta ahora todo el bloque ha ocurrido sin energía. La primera prueba activa será deliberadamente pequeña: solo el motor **AK1**, ubicado en la esquina trasera derecha, girará durante medio segundo. Los otros tres canales quedarán deshabilitados.

El programa tendrá tres barreras de seguridad:

1. comienza con `EJECUTAR_PRUEBA = false`;
2. configura y detiene los cuatro canales antes de cualquier movimiento;
3. espera quince segundos, aplica PWM `100` durante 500 ms y vuelve a `detenerTodos()`.

El número `100` no significa 100 % ni 100 revoluciones. `analogWrite()` usa aquí una escala de 0 a 255. Es un mando moderado para una prueba corta; la velocidad real depende también de batería, rozamiento, carga y del motor concreto.

## Todo lo que debe estar listo

- PX-32 ensamblado.
- Dos soportes rígidos de la misma altura que sostengan el **chasis**, no las ruedas; las cuatro ruedas deben quedar al menos 2 cm sobre la mesa.
- Computador con Arduino IDE 2 y cable USB de datos.
- El archivo [15-primera-prueba-de-un-motor.ino](../../code/educational/15-primera-prueba-de-un-motor/15-primera-prueba-de-un-motor.ino).
- Las dos celdas 18650 y su cargador compatible, manipulados únicamente por el adulto.
- El mapa [AK1 -> motor trasero derecho](../../docs/reference/mapa-conexiones-robot.md#motores).
- Área despejada, cabello recogido, mangas y cordones lejos de las ruedas.

Necesitas recordar de la [Lección 14](14-puente-h-cambiar-la-polaridad.md) que `HIGH/LOW` establece un sentido y PWM habilita el canal.

🔴 Tu padre retira las celdas, desconecta el USB y apaga los interruptores. Después comprueba que los soportes son estables, que ninguna rueda los toca y que el interruptor queda accesible. Si el robot se bambolea, no se programa todavía.

## Lee el programa antes de permitir movimiento

1. 🟢 Abre el `.ino` y compáralo línea por línea con este bloque completo:

```cpp
// Curso PX-32 - Leccion 15: primera prueba del motor AK1.
// El sketch queda detenido hasta cambiar EJECUTAR_PRUEBA a true.
const bool EJECUTAR_PRUEBA = false;

// Model Y, zona B: motores delanteros.
const byte PWM_BK1 = 9;
const byte BK1_IN1 = 22;
const byte BK1_IN2 = 24;
const byte PWM_BK3 = 10;
const byte BK3_IN3 = 26;
const byte BK3_IN4 = 28;

// Model Y, zona A: motores traseros.
const byte PWM_AK1 = 11;
const byte AK1_IN1 = 5;
const byte AK1_IN2 = 6;
const byte PWM_AK3 = 12;
const byte AK3_IN3 = 7;
const byte AK3_IN4 = 8;

void detenerTodos() {
  // Primero se deshabilita la potencia de los cuatro canales.
  analogWrite(PWM_BK1, 0);
  analogWrite(PWM_BK3, 0);
  analogWrite(PWM_AK1, 0);
  analogWrite(PWM_AK3, 0);

  // Luego las entradas de direccion quedan en LOW.
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

void setup() {
  prepararMotores();

  if (!EJECUTAR_PRUEBA) {
    return;
  }

  // Da tiempo para retirar el USB y, despues, energizar desde baterias.
  delay(15000);
  girarAK1Adelante(100);
  delay(500);
  detenerTodos();
}

void loop() {
  detenerTodos();
}
```

2. 🟢 Localiza los tres nombres de AK1. `PWM_AK1 = 11` controla habilitación/potencia media; `AK1_IN1 = 5` y `AK1_IN2 = 6` establecen dirección. Confirma esos números en el mapa, no por memoria.

3. 🟢 Lee `detenerTodos()` de arriba abajo. Primero escribe `0` en las cuatro habilitaciones; después deja las ocho entradas en `LOW`. Aunque solo probaremos AK1, el programa da un estado conocido a todos los canales.

4. 🟢 Explica la barrera `if (!EJECUTAR_PRUEBA)`. El signo `!` significa “no”: mientras la constante sea `false`, la condición es verdadera y `return` termina `setup()` antes del pulso.

5. 🟢 Predice la secuencia con `true`: quince segundos sin giro, AK1 durante medio segundo y luego silencio. Señala qué función mantiene la parada dentro de `loop()`.

> **[PENDIENTE VISUAL]**
> - **Tipo:** fotografía superior anotada.
> - **Objetivo:** permitir que el niño identifique sin duda el motor AK1 antes de la primera energización.
> - **Descripción:** PX-32 visto desde arriba con el frente marcado; resaltar la esquina trasera derecha, el conector AK1 del Model Y y la ruta D11/D5/D6.
> - **Elementos que deben señalarse:** frente, derecha del robot, motor trasero derecho, AK1, D11 PWM, D5 IN1, D6 IN2 y zona segura de soportes bajo el chasis.
> - **Fuente técnica:** manual OSOYOO, https://osoyoo.com/manual/2021006600-2026.pdf, páginas 7 y 13.
> - **Texto alternativo sugerido:** “Vista superior de PX-32 con el motor trasero derecho y su conector AK1 destacados”.

## Autoriza una sola prueba

6. 🟢 Cambia únicamente la línea de autorización a `const bool EJECUTAR_PRUEBA = true;`.

7. 🟡 Con el adulto presente y las baterías todavía fuera, conecta solo el USB. En Arduino IDE verifica `Arduino Mega or Mega 2560`, selecciona el puerto que aparece al conectar y pulsa **Verificar**. Continúa únicamente si termina sin errores.

8. 🟡 Pulsa **Subir** y espera el mensaje de carga completada. Retira el USB. El programa quedó guardado en la memoria flash de la Mega y se ejecutará de nuevo cuando reciba energía.

9. 🔴 Con el robot ya elevado, tu padre revisa polaridad y estado de las celdas, las instala y enciende los interruptores documentados del portabaterías y del shield. Nadie toca el robot. La espera de quince segundos existe para separar la carga por USB de la prueba con baterías; no la reduzcas.

10. 🟢 Observa únicamente la rueda trasera derecha. El criterio de éxito es: empieza después de la espera, gira cerca de medio segundo y se detiene; las otras tres permanecen quietas.

11. 🔴 Si gira otra rueda, el robot se desplaza sobre los soportes, hay zumbido sin giro, reinicio, calor, olor o cables que se acercan a una rueda, tu padre apaga de inmediato. No detengas la rueda con la mano.

12. 🔴 Aunque la prueba salga bien, tu padre apaga y retira las celdas. Conecta de nuevo solo el USB, restaura `EJECUTAR_PRUEBA = false`, verifica y sube. Así un encendido futuro comienza detenido.

La misión termina cuando puedes nombrar AK1, sus tres pines, la duración del pulso y las tres instrucciones que impiden que se repita.

## Diagnóstico de esta prueba concreta

| Síntoma | Revisión pequeña y segura |
|---|---|
| Ninguna rueda gira | Confirma que se subió la versión con `EJECUTAR_PRUEBA = true`; luego el adulto revisa interruptores y carga de baterías |
| Gira una rueda distinta | No cambies el código para “compensar”; compara el conector físico con `AK1 -> trasero derecho` |
| Giran varias ruedas | Apaga; verifica que las otras tres llamadas `analogWrite(..., 0)` estén presentes y que no se cargó otro sketch |
| AK1 zumba pero no arranca | Apaga sin esperar; puede existir un umbral de arranque, roce o batería baja. No aumentes PWM hasta revisar mecánica y alimentación |
| Gira y no se detiene | Apaga; comprueba `delay(500); detenerTodos();` y que `loop()` solo llame a `detenerTodos()` |
| Arduino IDE muestra un error | Lee la primera línea útil: revisa punto y coma, llaves, nombre de constante y placa seleccionada |

## Lecturas y videos para explorar

- [Crea tu PRIMER PROGRAMA con ARDUINO IDE](https://www.youtube.com/watch?v=wsAVDgyDhsQ) — Español; video; 14 min (verlo por partes).
**Por qué este recurso:** confirma el flujo que harás hoy — seleccionar la placa, elegir el puerto, Verificar y Subir — antes de tocar el robot; divídelo en dos partes si lo prefieres.

- [Upload your first code to Arduino Uno](https://www.youtube.com/watch?v=y5znFDmY5V4) — Inglés muy sencillo; video; 5 min.
**Por qué este recurso:** estimula porque muestra en pantalla real el botón de Subir y la carga terminada; el inglés es elemental y casi todo se entiende viendo.

- [Tutorial de uso del módulo L298N](https://naylampmechatronics.com/blog/11_tutorial-de-uso-del-modulo-l298n.html) — Español; lectura con fotos; ~10 min.
**Por qué este recurso:** profundiza en un driver de motores real: puente H, bornes de motor y control por ENA/IN, la misma anatomía del Model Y que usarás en la prueba.

Compara cada recurso con el paso que estás a punto de dar: placa, puerto, Verificar, Subir y solo después, baterías.

## Referencias técnicas de la clase

- [Guía oficial del Model Y](https://osoyoo.com/2022/02/25/osoyoo-model-y-4-channel-motor-driver/), AK1, entradas, PWM y ejemplo de parada.
- [Pinout oficial de Arduino Mega 2560](https://docs.arduino.cc/resources/pinouts/A000067-full-pinout.pdf), D5, D6 y D11 con capacidad PWM de la placa oficial.
- [Referencia del lenguaje Arduino](https://docs.arduino.cc/language-reference/), `pinMode()`, `digitalWrite()`, `analogWrite()` y `delay()`.

## Cuéntale a papá

Sin volver a encender, señala el motor que giró y recorre `D11/D5/D6 -> AK1 -> motor trasero derecho`. Después explícale por qué dejar `EJECUTAR_PRUEBA` en `false` es parte del resultado, no una tarea de limpieza.

La [Lección 16](16-invertir-el-sentido-por-software.md) usará el mismo motor y los mismos cables, pero intercambiará `HIGH` y `LOW` después de una parada completa.
