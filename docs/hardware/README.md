# Diccionario de hardware de PX-32

## Estados

- `VERIFICADO_PDF`: nombre, cantidad o conexión visible en el PDF entregado.
- `VERIFICADO_FÍSICAMENTE`: padre e hijo lo confirmaron sobre PX-32.
- `PENDIENTE_DE_VERIFICAR`: el manual no basta o contiene una contradicción.

Una pieza puede estar verificada en el PDF y seguir pendiente de confirmación física.

## Inventario formal

| ID | Componente | Cantidad | Estado documental | Fuente principal |
|---|---|---:|---|---|
| [HW-001](HW-001-mega2560.md) | OSOYOO Mega2560 R3 | 1 | VERIFICADO_PDF | pp. 4, 23 |
| [HW-002](HW-002-uart-wifi-shield.md) | OSOYOO UART WiFi Shield V1.3 | 1 | VERIFICADO_PDF | pp. 13, 17-18, 24 |
| [HW-003](HW-003-esp8266-esp12s.md) | ESP8266 / módulo marcado ESP12/S | 1 | PENDIENTE_DE_VERIFICAR subversión | pp. 2, 13, 53 |
| [HW-004](HW-004-model-y-v2.md) | OSOYOO Model Y V2.0 | 1 | VERIFICADO_PDF; una tabla dice v1.0 | pp. 13, 15 |
| [HW-005](HW-005-motores-dc.md) | Motores DC con reductora | 4 | VERIFICADO_PDF | pp. 4-8 |
| [HW-006](HW-006-ruedas-mecanum.md) | Ruedas Mecanum, dos orientaciones | 4 | VERIFICADO_PDF | pp. 19-22 |
| [HW-007](HW-007-ir-tracker-5ch.md) | OSOYOO 5-Channel IR Tracker | 1 | VERIFICADO_PDF | pp. 18, 34-35 |
| [HW-008](HW-008-ir-obstaculos.md) | Sensores IR de obstáculos | 2 | VERIFICADO_PDF | pp. 39-40 |
| [HW-009](HW-009-ultrasonico.md) | Módulo ultrasónico | 1 | VERIFICADO_PDF | pp. 26, 29 |
| [HW-010](HW-010-servo-mg90.md) | Microservo OSOYOO MG90 | 1 | VERIFICADO_PDF | pp. 26, 29 |
| [HW-011](HW-011-bluetooth-hc02.md) | Bluetooth HC-02 | 1 | VERIFICADO_PDF | pp. 44-45, 51 |
| [HW-012](HW-012-voltimetro.md) | Voltímetro LED de tres dígitos | 1 | VERIFICADO_PDF | pp. 4, 14-15 |
| [HW-013](HW-013-leds-delanteros.md) | Luces LED delanteras | 2 | VERIFICADO_PDF | pp. 15-16 |
| [HW-014](HW-014-portabaterias.md) | Portabaterías con interruptor | 1 | VERIFICADO_PDF | pp. 10, 15, 24 |
| [HW-015](HW-015-baterias-18650.md) | Baterías 18650 nominales de 3.7 V | 2 | VERIFICADO_PDF; protección pendiente | pp. 4, 26 |
| [HW-016](HW-016-cargador.md) | Cargador de baterías | 1 | PENDIENTE_DE_VERIFICAR modelo/especificación | pp. 4, 26 |
| [HW-017](HW-017-chasis.md) | Chasis Mecanum acrílico | 1 conjunto | VERIFICADO_PDF | pp. 4-21 |
| [HW-018](HW-018-cables.md) | Cables y jumpers suministrados | 1 conjunto | VERIFICADO_PDF con variación por lección | pp. 4, 26, 34, 39, 44, 52 |
| [HW-019](HW-019-mecanica.md) | Soportes, acoples, separadores y tornillería | 1 conjunto | VERIFICADO_PDF | pp. 5-12, 19, 26-28 |
| [HW-020](HW-020-cable-usb.md) | Cable USB de datos | 1 | Uso verificado; inclusión física pendiente | pp. 22-24 |

## Inspección física pendiente

Con PX-32 apagado y sin baterías, completar una fotografía y marcar cada ficha como `VERIFICADO_FÍSICAMENTE`. En particular hay que leer las etiquetas del servo, ESP, baterías y cargador. No energizar el sistema durante el inventario.
