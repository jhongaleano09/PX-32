# Lección 02 - Inventario de PX-32

## Misión

Identificar, contar y documentar el hardware real sin confundir una fotografía con una prueba.

## Antes de tocar a PX-32

Un inventario científico no dice “creo que hay un servo”. Registra evidencia: etiqueta, cantidad, posición, fotografía y estado. Hay tres niveles distintos:

- el manual dice que debería existir;
- una fotografía muestra que existe un tipo de pieza;
- nosotros leemos la pieza real y confirmamos su modelo.

El manual también puede tener erratas. Por eso usamos identificadores estables `HW-001`, `HW-002`... aunque el nombre se refine después.

## La pregunta

¿El PX-32 físico coincide con las veinte familias de componentes del inventario documental?

## Nuestra predicción

Escribe tres componentes que probablemente coincidan exactamente y dos cuyo modelo podría variar.

## Conceptos nuevos

Inventario, identificador, evidencia, revisión, cantidad y estado de verificación.

## Hardware utilizado

- PX-32 apagado.
- [Inventario HW-001 a HW-020](../../docs/hardware/README.md).
- [Página 4 del manual](../../assets/osoyoo-manual/pagina-04-inventario-kit.png).

## Conexiones

No se modifica ninguna. Si una etiqueta está oculta, se registra como pendiente; no se desmonta para “ganar” la actividad.

## Seguridad

**Nivel amarillo.** El adulto verifica USB retirado e interruptores apagados. Las baterías y el cargador solo los manipula el adulto. No apoyar PX-32 sobre sensores salientes ni ruedas inestables.

## Experimento PX-32: auditoría de inventario

1. Abran [docs/hardware/README.md](../../docs/hardware/README.md).
2. Recorran cada ID sin saltos.
3. Marquen cantidad observada y ubicación.
4. Lean exactamente las etiquetas visibles; respeten mayúsculas, números y versión.
5. Tomen una fotografía general y detalles de servo, ESP, baterías y cargador si es seguro.
6. Para cada diferencia, escriban `FALTA`, `ADICIONAL`, `MODELO_DISTINTO` o `NO_VISIBLE`.
7. No cambien todavía los archivos del diccionario. Primero comparen toda la evidencia.

## Antes de ejecutar

¿Qué cuenta como mejor evidencia: el color de una placa, una etiqueta legible o el recuerdo de quien la compró? Ordena las tres.

## Resultado esperado

Una tabla completa. Es normal que ESP, protección de baterías, cargador o cable USB queden pendientes. El objetivo es reconocer incertidumbre, no forzar una respuesta.

## Observaciones

| ID | Cantidad PDF | Cantidad real | Texto visible | Estado físico | Foto |
|---|---:|---:|---|---|---|
| HW-001 | 1 | | | | |
| HW-002 | 1 | | | | |

Continúen hasta HW-020 en la bitácora.

## Cambia una cosa

Repite la inspección con otra iluminación o ángulo, sin desmontar. ¿Una marca antes ilegible se vuelve legible?

## ¿Qué ocurrió?

Clasifica cada cambio como nueva pieza o mejor evidencia sobre la misma pieza.

## Desafío

Elige un componente desconocido y escribe una descripción que permita reconocerlo sin usar su nombre.

## Depuración

Si la fotografía contradice el manual, abre la ficha HW y [errata-osoyoo.md](../../docs/reference/errata-osoyoo.md). Si afecta pinout o alimentación, no se resuelve por parecido visual.

## Quiz

1. ¿Qué diferencia hay entre `VERIFICADO_PDF` y `VERIFICADO_FÍSICAMENTE`?
2. ¿Por qué usamos IDs aunque cambie el nombre?
3. ¿Qué se hace si una etiqueta no es visible?
4. Nombra dos datos que el PDF no permite verificar completamente.
5. ¿Por qué una discrepancia no se corrige en silencio?

Respuestas: [Solución 02](../../solutions/02-inventario-de-px32.md).

## Bitácora

Adjuntar tabla, fotografías y lista de pendientes. Escribir quién observó cada dato.

## Lo que ya sabemos

Podemos distinguir función general de identidad exacta.

## Próxima misión

Aprenderemos la física que permite que las piezas se alimenten y se comuniquen.

## Fuentes

**OSOYOO:** listas de partes pp. 4, 26, 34, 39, 44 y 52. **CURSO PX-32:** método de auditoría.
