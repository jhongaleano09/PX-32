# Guía de depuración de PX-32

Depurar no es probar cosas al azar. Es reducir posibilidades mediante evidencia.

## Método PISTA

1. **P**arar y dejar el sistema seguro.
2. **I**dentificar el síntoma exacto, no una conclusión.
3. **S**eparar el sistema en partes.
4. **T**estar una variable a la vez.
5. **A**notar resultado y siguiente hipótesis.

## El programa no carga

1. ¿La placa elegida es `Arduino Mega or Mega 2560`?
2. ¿Aparece un puerto nuevo al conectar el cable?
3. ¿El cable transporta datos?
4. ¿Otra aplicación tiene abierto el puerto?
5. ¿El código compila sin error antes de subir?
6. Copiar el primer mensaje de error útil a la bitácora.

## No aparece el puerto

Desconectar y observar la lista, reconectar y buscar el nuevo puerto. En macOS suele verse como `/dev/cu...`; en Linux puede ser `/dev/ttyACM0` o similar. Si existe pero el usuario no tiene permiso en Ubuntu, el adulto revisa grupos/permisos del sistema sin aplicar comandos no comprendidos.

## El Serial Monitor muestra basura

El baud rate del monitor debe coincidir con `Serial.begin(...)`. Reiniciar la placa puede repetir el mensaje inicial.

## Un motor no gira o solo gira en un sentido

Con todo apagado:

- revisar conector del motor;
- revisar cable de seis pines sujetando la carcasa;
- comparar M_A/M_B con el mapa;
- probar el motor aislado por software, no recablear al azar.

OSOYOO atribuye con frecuencia este síntoma a cable flojo o roto entre Mega/shield y Model Y (p. 25).

## Ultrasónico entrega 0 o lecturas imposibles

Verificar VCC 5V, TRIG D30, ECHO D31 y GND. Probar con un objeto plano al frente. Un timeout debe registrarse como “sin eco”, no interpretarse como cero centímetros.

## Tracker se desvía

Confirmar IR1->A4, IR2->A3, IR3->A2, IR4->A1, IR5->A0; luego revisar altura, patrón X de ruedas, contraste del piso, ancho de pista (OSOYOO sugiere 20-30 mm) y calibración.

## Bluetooth o Wi-Fi no responde

- Confirmar que TX llega a RX.
- Bluetooth: B_TX->D19 y B_RX->D18.
- Wi-Fi: E_TX->D19 y E_RX->D18.
- No activar las dos rutas a la vez.
- Probar primero recepción de caracteres sin motores.

## Formato de reporte

```text
Síntoma observable:
Última cosa que funcionó:
Cambio realizado:
Fuente de energía:
Programa exacto:
Salida Serial/error:
Prueba de aislamiento:
Resultado:
Siguiente hipótesis:
```
