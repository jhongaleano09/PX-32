# Alimentación de PX-32

## Modos de trabajo

### Modo laboratorio inicial

Solo Mega2560 por USB. Baterías retiradas o interruptores apagados y sistema de potencia aislado según preparación adulta. Ideal para Blink y Serial.

### Modo robot móvil

Dos celdas 18650 en el portabaterías alimentan VIN del Model Y; VOUT del Model Y alimenta VIN del UART WiFi Shield según OSOYOO. El voltímetro se conecta al Model Y.

## Lo confirmado y lo pendiente

| Dato | Estado |
|---|---|
| Dos celdas 18650 de 3.7 V nominal cada una | VERIFICADO_PDF |
| Portabaterías -> VIN Model Y | VERIFICADO_PDF |
| VOUT Model Y -> VIN UART WiFi Shield | VERIFICADO_PDF |
| Voltímetro GND/VCC/VT -> GND/5V/S | VERIFICADO_PDF |
| Celdas en serie o paralelo | PENDIENTE_DE_VERIFICAR |
| Voltaje/corriente máximos del Model Y | PENDIENTE_DE_VERIFICAR |
| Protección de cada celda | PENDIENTE_DE_VERIFICAR |
| Especificaciones del cargador | PENDIENTE_DE_VERIFICAR |

## USB y batería

No se asume que conectar USB y batería simultáneamente sea seguro en cualquier configuración. Para cada prueba se define una fuente principal y el adulto revisa el circuito. El manual indica programar primero, desconectar el PC y luego insertar/activar baterías para jugar.

## Señales de detención

Apagar y apartarse si aparece calor anormal, olor, humo, chispa, cable deformado, celda dañada, ruido mecánico fuerte o reinicios repetidos. No tocar una celda caliente con la mano desnuda; el adulto aplica el plan de seguridad del hogar.

## Batería baja

Puede causar motores lentos, reinicios, servo inestable y lecturas engañosas. El voltímetro ayuda a observar tendencia, pero sin curva de descarga y especificaciones no se convierte directamente en porcentaje.

## Fuente

Manual OSOYOO, pp. 14-15 y 24. Precauciones y pendientes: curso PX-32.
