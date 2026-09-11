# Erratas e incertidumbres del manual OSOYOO

No se corrigen silenciosamente. Cada caso mantiene la evidencia y la decisión del curso.

| ID | Ubicación | Hallazgo | Evidencia/decisión | Estado |
|---|---|---|---|---|
| E-001 | pp. 17 y 34, texto | Lista IR1-IR5 con pines duplicados: p. 17 dice A4,A3,A2,A3,A1; p. 34 dice A4,A3,A2,A2,A1 | Diagramas de pp. 18 y 35 coinciden: IR1 A4, IR2 A3, IR3 A2, IR4 A1, IR5 A0. Ese es el mapa canónico. | RESUELTO_POR_PDF |
| E-002 | p. 15, tabla voltímetro | Encabezado `Model Y v1.0 board` | La placa en pp. 13, 15 y 17 está marcada `Model Y v2.0`; se documenta V2.0 y se conserva la discrepancia. | RESUELTO_POR_SERIGRAFÍA |
| E-003 | pp. 16-17, 26-29 | El texto habla de tornillos o kit SG90, mientras inventario y tabla nombran MG90 | El componente del inventario es MG90. Los tornillos pueden ser compatibles o texto heredado. Confirmar etiqueta física. | MG90_VERIFICADO_PDF / FÍSICO_PENDIENTE |
| E-004 | p. 2 | Introducción dice que hay “five step by step lessons” | El índice y el documento contienen seis lecciones. | RESUELTO_POR_ÍNDICE |
| E-005 | p. 4 | `fully compatible with Arduino UNO/Mega2560` mezcla dos formatos/capacidades | El hardware ilustrado y seleccionado en IDE es Mega2560. No se asume pinout de UNO. | RESUELTO_POR_PDF |
| E-006 | p. 19 | Tornillos de rueda M2.5x20 o M2.6x20 | La variante exacta depende del contenido físico. No forzar; verificar ajuste. | PENDIENTE_DE_VERIFICAR |
| E-007 | listas de partes | Cable de dos pines aparece como PnP, XH.25 o XH2.54 | La foto de p. 15 dice XH2.54. Se identifica por función y conectores físicos, no solo por nombre OCR. | PENDIENTE_DE_NORMALIZAR |
| E-008 | pp. 22-24 y repetidas | Capturas y menús de Arduino IDE 1.8.x | El curso usa Arduino IDE 2 vigente; las capturas quedan como referencia histórica. | ACTUALIZADO_PEDAGÓGICAMENTE |
| E-009 | p. 24 vs p. 52 | Bluetooth y Wi-Fi comparten D18/D19 con rótulos B/E | El manual indica desconectar B y conectar E; nunca usar ambos a la vez. | RESUELTO_POR_SECUENCIA |
| E-010 | p. 51 | Procedimiento AT usa un HC-05 en la ilustración y menciona HC-02 en texto | No usar esa imagen para identificar el módulo. La reconfiguración del nombre queda pospuesta hasta verificar la placa real y su firmware. | PENDIENTE_DE_VERIFICAR |
| E-011 | p. 15 | La ruta de potencia se ilustra, pero no especifica límites ni serie/paralelo del portabaterías | No inferir límites. Verificar documentación/etiquetas antes de experimentos de potencia. | PENDIENTE_DE_VERIFICAR |

## Cómo añadir una errata

Registra página, frase o figura, efecto técnico, evidencia alternativa y una decisión explícita. Si afecta alimentación o pinout, suspende el experimento hasta resolverla.
