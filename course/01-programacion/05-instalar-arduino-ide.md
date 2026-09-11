# Lección 05 - Instalar Arduino IDE y reconocer la placa

## Misión

Instalar Arduino IDE 2 en macOS o Ubuntu, elegir `Arduino Mega or Mega 2560`, identificar el puerto y verificar un programa sin mover PX-32.

## Antes de tocar a PX-32

Arduino IDE cumple varias tareas diferentes:

- **editar:** escribir código fuente;
- **verificar/compilar:** comprobar reglas y traducir el código;
- **cargar/upload:** transferir el programa a la flash de la Mega;
- **monitorizar:** intercambiar texto por Serial.

Compilar con éxito no demuestra que el cable, el puerto o la placa estén bien seleccionados. Cargar añade esas pruebas.

## La pregunta

¿Cómo distingue el computador la placa correcta entre todos sus dispositivos?

## Nuestra predicción

Antes de conectar la Mega, mira la lista de puertos. Predice qué cambio verás al conectarla.

## Conceptos nuevos

IDE, código fuente, compilar, cargar, placa, procesador, puerto y monitor serial.

## Hardware utilizado

- [HW-001 Mega2560](../../docs/hardware/HW-001-mega2560.md).
- [HW-020 cable USB de datos](../../docs/hardware/HW-020-cable-usb.md).

## Conexiones

Solo `computador -> cable USB de datos -> Mega2560`. No se usa la alimentación por baterías ni se conecta un actuador.

## Seguridad

**Nivel amarillo durante la preparación y verde durante el uso del IDE.** Un adulto aísla la Mega del resto de PX-32 antes de conectar USB y confirma que no haya otra fuente activa.

## Preparación segura de la placa

Esta práctica usa **solo la Mega2560**, sin baterías, motores, servo ni Model Y energizados. La opción preferida es trabajar con HW-001 separada del robot. Si PX-32 ya está ensamblado, el adulto decide cómo aislarla sin doblar pines y fotografía toda conexión antes de retirar algo. No se carga Blink en un robot completo con el servo conectado a D13.

## Ruta A - macOS en el MacBook Air

1. Entra a [Arduino Software](https://www.arduino.cc/en/software) y descarga Arduino IDE 2 para la arquitectura del Mac indicada por la página.
2. Abre el archivo `.dmg` descargado.
3. Arrastra `Arduino IDE` a `Applications`.
4. Ábrelo desde Aplicaciones o Spotlight. Si macOS solicita confirmar una app descargada, verifica que provenga de Arduino.
5. Conecta la Mega por un cable USB de datos. En un MacBook Air puede hacer falta un adaptador USB-C fiable.

La guía oficial vigente describe el flujo DMG -> Applications -> abrir la aplicación: [Download and install Arduino IDE](https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE).

## Ruta B - Ubuntu Linux

1. Entra a [Arduino Software](https://www.arduino.cc/en/software) y descarga la AppImage Linux de 64 bits.
2. En el administrador de archivos, abre Propiedades -> Permisos y permite ejecutar como programa. Alternativa comprendida por el adulto:

   ```bash
   chmod +x Arduino-IDE_*.AppImage
   ```

3. Abre la AppImage.
4. Si aparece un error relacionado con `libfuse.so.2`, consulta la guía oficial; en versiones compatibles de Ubuntu puede requerirse `libfuse2`.
5. Conecta la Mega por USB.

No se ejecutan comandos con `sudo` solo por copiar una solución: primero se lee el error y se confirma el sistema.

## Elegir placa, procesador y puerto

1. Abre el selector de placa de Arduino IDE 2.
2. Si aparece una placa desconocida, elige `Select other board and port`.
3. Busca y selecciona `Arduino Mega or Mega 2560`, dentro del paquete Arduino AVR Boards.
4. Selecciona el puerto que aparece al conectar la placa. Ejemplos típicos: `/dev/cu.usbmodem...` en macOS o `/dev/ttyACM0` en Linux; el nombre real puede variar.
5. Si la versión del IDE muestra una opción `Processor`, selecciona `ATmega2560 (Mega 2560)`. En Arduino IDE 2 actual normalmente la selección de placa ya define el procesador.

Referencia: [Select board and port in Arduino IDE](https://support.arduino.cc/hc/en-us/articles/4406856349970-Select-board-and-port-in-Arduino-IDE).

## Experimento PX-32: identificar el puerto por diferencia

1. Con la Mega desconectada, abre el selector y anota los puertos.
2. Conecta el cable.
3. Espera unos segundos y abre otra vez la lista.
4. El puerto nuevo es el candidato.
5. Desconecta y comprueba que desaparece.
6. Conecta de nuevo, selecciónalo y abre Archivo -> Ejemplos -> 01.Basics -> Blink.
7. Pulsa **Verify**. Todavía no pulses Upload.

## Antes de ejecutar

Predice la diferencia entre un error al compilar y uno al cargar.

## Resultado esperado

Verify termina sin error. No cambia ningún LED por verificar: el programa aún no se transfirió. Un error de sintaxis aparece antes de necesitar puerto; un fallo de carga suele mencionar puerto, programador, conexión o placa.

## Observaciones

| Sistema | Placa elegida | Puerto antes | Puerto después | Verify |
|---|---|---|---|---|
| macOS/Ubuntu | | | | |

## Cambia una cosa

Con la Mega desconectada, vuelve a pulsar Verify. ¿Sigue compilando? No intentes Upload en esta prueba.

## ¿Qué ocurrió?

La compilación puede funcionar sin placa conectada porque ocurre en el computador. La carga necesita una ruta física hacia la Mega.

## Desafío

Explica estas cuatro palabras sin usar “hace funcionar”: editar, compilar, cargar y ejecutar.

## Depuración

- **No aparece puerto:** prueba otro cable de datos/puerto/adaptador y compara lista antes/después.
- **Placa desconocida:** selección manual Mega 2560.
- **Ubuntu ve el dispositivo pero IDE no puede abrirlo:** registrar el mensaje exacto; el adulto revisa permisos y grupos del sistema.
- **macOS muestra `bad CPU type`:** actualizar IDE/core y seguir la guía oficial para Rosetta si aplica.
- **Puerto ocupado:** cerrar otros monitores seriales.

## Quiz

1. ¿Qué hace Verify?
2. ¿Qué añade Upload?
3. ¿Por qué anotamos puertos antes y después?
4. ¿Qué placa se elige?
5. ¿Compilar requiere Mega conectada?
6. ¿Qué preparación evita que Blink afecte al servo?

Respuestas: [Solución 05](../../solutions/05-instalar-arduino-ide.md).

## Bitácora

Registrar sistema operativo, versión del IDE, placa, puerto, resultado de Verify y cualquier error completo.

## Lo que ya sabemos

Conocemos el cerebro y ahora sabemos cómo traducir un programa para él.

## Próxima misión

Cargaremos el primer programa y haremos que un LED siga un ritmo que podemos predecir.

## Fuentes

**OSOYOO:** capturas del IDE clásico, pp. 22-24. **Arduino vigente:** [instalación](https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE), [placa y puerto](https://support.arduino.cc/hc/en-us/articles/4406856349970-Select-board-and-port-in-Arduino-IDE). **CURSO PX-32:** experimento y seguridad.
