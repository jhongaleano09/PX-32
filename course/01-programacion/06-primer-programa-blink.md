# Lección 06 — Primer programa: Blink

## Una instrucción que se vuelve luz

Hasta ahora el código vivía en la pantalla. Hoy una palabra escrita, `HIGH`, terminará convertida en luz sobre la Mega2560. Después `LOW` la apagará y `loop()` hará que la historia vuelva a empezar.

La placa tiene un LED integrado marcado con la letra `L`. En la Mega2560 oficial está conectado al pin digital 13, y Arduino ofrece el nombre `LED_BUILTIN` para referirse a él sin escribir el número. El LED ya forma parte de un circuito diseñado en la placa: no debes conectar un LED suelto.

Hay un detalle propio de PX-32 que impide tratar este ejemplo como cualquier Blink de Internet: D13 también llega al conector del servo S1. Si el servo permaneciera activo, el parpadeo podría enviarle pulsos que no fueron escritos para controlarlo. Primero se aísla ese actuador y solo después se carga el sketch.

## Preparación que no puedes saltarte

Debes haber identificado placa y puerto en la [Lección 05](05-preparar-arduino-ide.md). Reúne:

- PX-32 ensamblado, apagado y sin USB.
- Computador con Arduino IDE 2.
- Cable USB de datos.
- El archivo [06-primer-programa-blink.ino](../../code/educational/06-primer-programa-blink/06-primer-programa-blink.ino).
- La Mega2560, reconocible por su conector USB tipo B; el LED `L` puede quedar parcialmente oculto por el shield.
- Un teléfono para que el adulto fotografíe la orientación del conector del servo antes de retirarlo, si hace falta.

🔴 Detente y llama a tu padre. Con USB e interruptores apagados, él retira las baterías 18650 y desconecta el conector de tres hilos del servo en S1 sujetando la carcasa plástica, nunca los cables. Debe registrar su orientación para restaurarlo. Si S1 no puede identificarse con seguridad o el conector no sale sin fuerza, no energicen el robot: puedes leer y verificar el código sin subirlo.

## Cómo está organizado un sketch

Arduino necesita dos funciones:

- `setup()` se ejecuta una vez después de encender o reiniciar la placa. Allí prepararemos el pin como salida.
- `loop()` se ejecuta una y otra vez mientras la placa tenga energía. Allí construiremos el patrón de luz.

`pinMode(PIN_LED, OUTPUT);` configura D13 para producir una señal. `digitalWrite(PIN_LED, HIGH);` lleva la salida al estado lógico alto y, por el circuito particular del LED integrado, la luz se enciende. `LOW` la lleva al estado lógico bajo y la luz se apaga. HIGH no significa universalmente “encender”: ese efecto depende de cómo esté conectado el componente.

`delay(500);` detiene temporalmente la ejecución durante 500 milisegundos. Un milisegundo es una milésima de segundo, así que 500 ms equivalen a medio segundo.

## Experimento: predice, carga y cambia un intervalo

1. 🟢 Abre el archivo `.ino` de la clase en Arduino IDE. Si el IDE pregunta si debe colocarlo dentro de una carpeta con el mismo nombre, acepta. Un sketch principal y su carpeta comparten nombre.

2. 🟢 Comprueba que el programa se vea así. No lo comprimas en una sola línea: cada instrucción debe poder señalarse.

```cpp
// Curso PX-32 — Lección 06: primer Blink seguro.
const int PIN_LED = LED_BUILTIN;

void setup() {
  // D13 producirá la señal para el LED integrado.
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  digitalWrite(PIN_LED, HIGH);  // Enciende el LED L.
  delay(500);                   // Mantiene la luz medio segundo.

  digitalWrite(PIN_LED, LOW);   // Apaga el LED L.
  delay(500);                   // Mantiene la oscuridad medio segundo.
}
```

3. 🟢 Recorre el código con un dedo. El punto y coma termina una instrucción. Los paréntesis llevan datos a una función. Las llaves encierran las instrucciones que pertenecen a `setup()` o `loop()`.

4. 🟢 Predice el patrón completo antes de conectar: ¿cuánto dura encendido?, ¿cuánto dura apagado?, ¿cuánto tarda una vuelta completa de `loop()`? La respuesta esperada es medio segundo, medio segundo y un segundo en total.

5. 🟡 Con tu padre presente, revisa que las baterías y el servo sigan desconectados. Conecta únicamente el USB a la Mega. El LED de alimentación puede encenderse; todavía no es evidencia de que este sketch esté cargado.

6. 🟢 Selecciona `Arduino Mega or Mega 2560` y el puerto que identificaste por aparición y desaparición. Pulsa **Verificar**. Continúa cuando la consola termine sin errores.

7. 🟡 Pulsa **Subir** una sola vez. Durante la transferencia pueden parpadear luces de comunicación `TX` y `RX`; no son el LED `L` de tu experimento. Espera el mensaje de carga completada.

8. 🟢 Localiza `L` sin tocar las placas. Debe alternar aproximadamente medio segundo encendido y medio segundo apagado. Cuenta cuatro cambios y explica cuál línea produce cada estado. Si el shield oculta completamente el LED desde todos los lados, no retires ni inclines placas energizadas: desconecta el USB y pide al adulto decidir si la observación física puede hacerse con seguridad; la compilación correcta por sí sola no demuestra el parpadeo.

> **[PENDIENTE VISUAL]**
> - **Tipo:** fotografía anotada de la Mega2560 dentro de PX-32.
> - **Objetivo:** distinguir el LED integrado `L` de los indicadores `ON`, `TX` y `RX`, y mostrar por qué D13 exige aislar S1.
> - **Descripción:** vista superior orientada por el conector USB tipo B, con acercamientos del LED `L` y del conector de servo S1 en el Model Y; una línea punteada debe indicar que ambos comparten la señal D13 sin sugerir que comparten alimentación.
> - **Elementos que deben señalarse:** USB tipo B, LED `L`, indicadores `ON/TX/RX`, D13, S1 y conector del servo desconectado.
> - **Fuente técnica:** pinout oficial Arduino Mega 2560, https://docs.arduino.cc/resources/pinouts/A000067-full-pinout.pdf, páginas 1 y 3; manual OSOYOO, https://osoyoo.com/manual/2021006600-2026.pdf, páginas 13 y 17.
> - **Texto alternativo sugerido:** “Mega2560 orientada por el USB con los LEDs L, ON, TX y RX diferenciados, y la ruta D13 hacia el servo S1 indicada”.

### Cambia solo una cosa

9. 🟢 Desconecta el USB antes de editar. Cambia los dos valores `500` por `100`. Predice si el ciclo completo será más largo o más corto y luego conecta, verifica y sube otra vez. Deberías observar cinco ciclos completos por segundo aproximadamente.

10. 🟢 Repite con `1000` en ambos lugares. Ahora cada estado dura un segundo y una vuelta completa dura dos. Si cambiaste un solo `delay`, tendrás un patrón desigual; no es un daño, pero ya no es la comparación planeada.

11. 🟢 Considera la prueba exitosa si puedes hacer corresponder cada transición del LED con un `digitalWrite` y explicar por qué `loop()` reinicia la secuencia.

## Deja D13 en un estado seguro

El último Blink queda guardado en flash y volvería a ejecutarse al energizar la Mega. Antes de restaurar el servo:

12. 🟡 Abre `Archivo > Ejemplos > 01.Basics > BareMinimum`, confirma la misma placa y puerto, y súbelo. Ese sketch deja `setup()` y `loop()` sin instrucciones de control para D13.

13. 🟡 Retira el USB. 🔴 Tu padre comprueba que no hay ninguna fuente conectada y restaura el conector del servo en S1 usando la foto de orientación. Si encuentra resistencia, posición dudosa o cables dañados, no lo conecta.

El robot debe quedar ensamblado, apagado y sin baterías. El archivo de la clase permanece guardado en el computador aunque ya no sea el programa residente en la Mega.

## Si la luz no cuenta la misma historia que el código

| Síntoma | Qué revisar sin adivinar |
|---|---|
| Compila, pero no sube | Confirma el puerto por desconexión/reconexión, usa un cable de datos y cierra otras aplicaciones que tengan el puerto abierto |
| La carga termina, pero no ves parpadeo | Busca específicamente el LED `L`; `ON` indica alimentación y suele permanecer fijo |
| Parpadean `TX` y `RX` solo durante la carga | Es normal: muestran comunicación USB-serie, no el patrón de `loop()` |
| El patrón es desigual | Revisa si los dos valores de `delay` son iguales y si cada `digitalWrite` tiene su espera debajo |
| Aparece un error cerca de `}` o `;` | Usa autoformato y empareja cada llave; comprueba el punto y coma de la línea anterior |
| El servo se mueve, zumba o golpea | Desconecta el USB de inmediato; el aislamiento de S1 no quedó confirmado y solo el adulto debe revisarlo |
| Hay calor, olor o daño visible | No repitas; el adulto deja el equipo sin energía y revisa el montaje |

## Lecturas y videos para explorar

- [Estructura y lenguaje de Arduino](https://docs.arduino.cc/language-reference/) — Inglés; referencia oficial; 10 min. Aprenderás estructura y lenguaje de arduino. Esencial.
- [Ejemplos integrados de Arduino](https://docs.arduino.cc/built-in-examples/) — Inglés; tutorial oficial; 10 min. Aprenderás ejemplos integrados de arduino. Opcional.

Cuando abras Blink entre los ejemplos integrados, compara su estructura con la versión de PX-32 y busca la preparación especial que exige el servo compartido.

## Referencias técnicas de la clase

- [Arduino Mega 2560 Rev3](https://docs.arduino.cc/hardware/mega-2560/), placa y LED integrado.
- [Pinout oficial de la Mega 2560](https://docs.arduino.cc/resources/pinouts/A000067-full-pinout.pdf), `LED_BUILTIN` y D13.
- [Ejemplo integrado Blink](https://docs.arduino.cc/built-in-examples/basics/Blink/), estructura y comportamiento del ejemplo oficial.
- [Referencia del lenguaje Arduino](https://docs.arduino.cc/language-reference/), `pinMode`, `digitalWrite` y `delay`.
- [Manual oficial de OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), páginas 13 y 17, ruta D13/S1.

## Cuéntale a papá

Sin mirar el código, explícale qué ocurre primero en `setup()` y qué cuatro acciones se repiten en `loop()`. Muéstrale cuál LED observaste, por qué `ON` no servía como evidencia y qué hicieron para que D13 no enviara el patrón de Blink al servo.

En la [Lección 07](07-variables-para-representar-tiempo.md) reemplazarás los números repetidos por nombres que expresan qué representan.
