# Lección 11 — Funciones: enseñar una acción reutilizable

## Una acción merece un nombre

El `for` de la clase anterior sabe producir un grupo de destellos. Si un programa grande necesitara ese grupo en varios lugares, copiar todo el bucle haría el código largo y difícil de corregir. Una **función** reúne instrucciones bajo un nombre:

```cpp
parpadear(3, 200);
```

Esa llamada dice qué hacer y aporta dos datos. En la definición de la función se llaman **parámetros**: `veces` e `intervaloMs` son nombres que recibirán valores. En la llamada, `3` y `200` son **argumentos**: los valores concretos enviados esta vez.

No todas las funciones entregan una respuesta. La palabra `void` antes de `parpadear` indica que realiza una acción, pero no retorna un valor al lugar desde donde fue llamada. Para aprender la otra posibilidad construiremos `duracionGrupoMs()`: calculará cuánto dura un grupo y usará `return` para devolver el resultado.

En Scratch, crear “Mis bloques” permite nombrar una secuencia y darle entradas. Aquí la idea es parecida, pero C++ exige declarar el tipo de cada parámetro y el tipo de dato que la función devuelve.

## Lo que necesitas tener listo

Debes comprender el recorrido del contador en un `for` de la [Lección 10](10-repeticiones-contadas-con-for.md) y saber abrir el monitor serie. Prepara:

- PX-32 ensamblado, apagado y sin USB.
- Computador con Arduino IDE 2 y cable USB de datos.
- El archivo [11-funciones-ensenar-una-accion-reutilizable.ino](../../code/educational/11-funciones-ensenar-una-accion-reutilizable/11-funciones-ensenar-una-accion-reutilizable.ino).
- Dos tarjetas con los rótulos `PARÁMETROS` y `ARGUMENTOS`.
- Un adulto para aislar las baterías y el servo S1.

🔴 Con toda fuente desconectada, tu padre retira las baterías 18650 y desconecta el conector del servo S1 sujetando la carcasa plástica. La señal D13 del LED integrado también llega a S1. Registren la orientación para restaurarlo al cerrar. Si no pueden asegurar este estado, compila y simula el código sin subirlo.

## Dos funciones con trabajos distintos

1. 🟢 Abre el `.ino` y compáralo cuidadosamente con el bloque completo:

```cpp
// Curso PX-32 — Lección 11: funciones con parámetros y retorno.
void parpadear(int veces, unsigned long intervaloMs) {
  for (int contador = 0; contador < veces; contador = contador + 1) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(intervaloMs);

    digitalWrite(LED_BUILTIN, LOW);
    delay(intervaloMs);
  }
}

unsigned long duracionGrupoMs(int veces, unsigned long intervaloMs) {
  return veces * intervaloMs * 2;
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  const int VECES = 3;
  const unsigned long INTERVALO_MS = 200;

  Serial.print("Duracion calculada del grupo: ");
  Serial.print(duracionGrupoMs(VECES, INTERVALO_MS));
  Serial.println(" ms");

  parpadear(VECES, INTERVALO_MS);
  delay(1500);
}
```

2. 🟢 Coloca la tarjeta `PARÁMETROS` junto a la definición:

```cpp
void parpadear(int veces, unsigned long intervaloMs)
```

Dentro de esa función, `veces` ocupa el lugar que antes tenía la constante `DESTELLOS`, e `intervaloMs` ocupa el lugar del tiempo fijo. Los nombres solo existen dentro de la función que los declara.

3. 🟢 Coloca `ARGUMENTOS` junto a la llamada:

```cpp
parpadear(VECES, INTERVALO_MS);
```

En cada vuelta, los valores 3 y 200 de esas constantes llegan a los parámetros. La función produce tres destellos con 200 ms encendido y 200 ms apagado.

4. 🟢 Examina la segunda definición. Como comienza con `unsigned long`, promete devolver un entero de ese tipo. `return veces * intervaloMs * 2;` calcula encendido más apagado para cada destello y entrega el resultado. Con 3 y 200 retorna 1200 ms.

5. 🟢 Sigue el dato devuelto hasta esta llamada dentro de `Serial.print(...)`:

```cpp
duracionGrupoMs(VECES, INTERVALO_MS)
```

El monitor debe mostrar `Duracion calculada del grupo: 1200 ms`. `return` no imprime por sí mismo: entrega el número y `Serial.print` lo hace visible.

> **[PENDIENTE VISUAL]**
> - **Tipo:** diagrama de llamada y retorno.
> - **Objetivo:** diferenciar parámetros, argumentos, una función `void` y una función que devuelve un valor.
> - **Descripción:** dos recorridos paralelos: `parpadear(3, 200)` lleva argumentos a parámetros y termina en tres pulsos de LED sin flecha de regreso; `duracionGrupoMs(3, 200)` lleva los mismos argumentos, calcula 1200 y devuelve una flecha hacia `Serial.print`.
> - **Elementos que deben señalarse:** nombre de función, tipos, parámetros, argumentos, `void`, `unsigned long`, `return`, llamada y efectos luz/texto.
> - **Fuente técnica:** referencia oficial del lenguaje Arduino, https://docs.arduino.cc/language-reference/, sección Functions; proceso de sketch, https://docs.arduino.cc/arduino-cli/sketch-build-process.
> - **Texto alternativo sugerido:** “Una función void usa tres y doscientos para parpadear; otra función devuelve mil doscientos al monitor serie”.

## Prueba que el nombre se puede reutilizar

6. 🟢 Antes de conectar, predice tres observaciones: el número impreso, la cantidad de destellos y el tiempo aproximado de cada estado. Separa la duración del grupo —1200 ms— de la pausa entre grupos —1500 ms—.

7. 🟡 Con el adulto presente, confirma batería retirada y servo S1 desconectado. Conecta únicamente el USB, elige Mega y puerto, verifica y sube.

8. 🟢 Abre el monitor serie a 9600 baudios y observa el LED `L`. Cada línea debe anunciar 1200 ms, seguida por tres destellos y una pausa larga. Si el texto y la luz no coinciden, compara los argumentos de las dos llamadas antes de culpar al hardware.

9. 🟢 Retira el USB. Cambia solamente `VECES` de 3 a 5. Calcula antes: 5 × 200 × 2 = 2000 ms. Verifica, sube y comprueba cinco destellos y el número 2000.

10. 🟢 Retira el USB y restaura `VECES = 3`. Cambia solamente `INTERVALO_MS` de 200 a 400. Debes seguir viendo tres destellos, ahora más lentos, y una duración calculada de 2400 ms. Así compruebas que cada parámetro controla una característica diferente.

11. 🟢 Prueba mentalmente qué pasaría si escribieras `parpadear(INTERVALO_MS, VECES)`. Los tipos permiten convertir esos números, así que podría compilar, pero intentaría hacer 400 destellos de 3 ms en la última variante. El orden de los argumentos es parte del contrato de la función.

12. 🟢 La misión está completa cuando puedes explicar por qué las dos funciones aceptan los mismos datos pero una produce luz y la otra entrega un número.

## El puente hacia el movimiento

En las próximas lecciones aparecerán funciones como `detener()` o `avanzar(velocidad)`. Nombrarlas no vuelve seguro al robot por sí solo, pero permite revisar una vez las instrucciones de cada acción y llamar la misma versión desde distintas decisiones. Parámetros claros evitarán copiar bloques enteros para cada motor.

Antes de llegar allí, deja el hardware neutral:

13. 🟡 Sube `Archivo > Ejemplos > 01.Basics > BareMinimum`. Así D13 deja de producir el patrón antes de reconectar el servo.

14. 🟡 Cierra el monitor y retira el USB. 🔴 Tu padre restaura el conector del servo S1 según la orientación registrada. PX-32 queda ensamblado, apagado y sin baterías.

## Si la función no cumple su contrato

| Síntoma | Pregunta precisa |
|---|---|
| El monitor calcula 1200, pero hay otra cantidad de destellos | ¿Las llamadas a `duracionGrupoMs` y `parpadear` reciben los mismos argumentos? |
| El compilador dice que faltan argumentos | ¿La llamada entrega dos valores separados por coma, en el orden `veces, intervaloMs`? |
| Error `was not declared in this scope` | ¿Intentaste usar un parámetro fuera de la función donde fue declarado? |
| Error sobre `return` o falta de valor | ¿`duracionGrupoMs` devuelve un `unsigned long` en todas sus rutas? ¿Escribiste la instrucción `return` completa? |
| El grupo parece una luz continua | Un intervalo de pocos milisegundos puede ser demasiado rápido para distinguirlo; vuelve a 200 ms |
| El programa compila pero tarda muchísimo | Revisa si intercambiaste los argumentos; el primero es cantidad y el segundo, milisegundos |
| El servo se mueve o zumba | Retira el USB y deja que el adulto revise S1; no continúes con otra carga |

## Lecturas y videos para explorar

- [Estructura y lenguaje de Arduino](https://docs.arduino.cc/language-reference/) — Inglés; referencia oficial; 10 min. Aprenderás estructura y lenguaje de arduino. Esencial.
- [Ejemplos integrados de Arduino](https://docs.arduino.cc/built-in-examples/) — Inglés; tutorial oficial; 10 min. Aprenderás ejemplos integrados de arduino. Opcional.

Cuando encuentres una función nueva, identifica su nombre, qué argumentos recibe, qué efecto produce y si entrega un valor utilizable.

## Referencias técnicas de la clase

- [Referencia del lenguaje Arduino](https://docs.arduino.cc/language-reference/), funciones, tipos, variables y `return`.
- [Proceso de construcción de un sketch](https://docs.arduino.cc/arduino-cli/sketch-build-process), generación de prototipos y compilación de archivos `.ino`.
- [Pinout oficial de Arduino Mega 2560](https://docs.arduino.cc/resources/pinouts/A000067-full-pinout.pdf), D13 y `LED_BUILTIN`.
- [Manual oficial de OSOYOO](https://osoyoo.com/manual/2021006600-2026.pdf), páginas 13 y 17, ruta compartida D13/S1.

## Cuéntale a papá

Usa las dos tarjetas para explicarle la diferencia entre parámetros y argumentos. Luego señala `void` y `return`: ¿qué función actúa sin devolver un dato?, ¿qué función entrega 1200?, ¿qué instrucción hace visible ese resultado? Termina contando cómo una función bien nombrada puede preparar el control de motores sin copiar instrucciones.

La [Lección 12](../02-movimiento/12-del-electron-al-giro-motor-dc.md) deja el código por un momento para observar cómo un motor convierte energía eléctrica en giro.
