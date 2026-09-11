# Reglas obligatorias del agente

## Publicación automática en GitHub

- Después de realizar cualquier cambio en el repositorio, por pequeño que sea, el agente DEBE crear el commit correspondiente y hacer `push` a la rama `main` de GitHub antes de dar la tarea por terminada.
- Esta obligación incluye TODOS los tipos de cambios: código, configuración, documentación, Markdown, comentarios, recursos, renombres, movimientos y eliminaciones de archivos.
- El agente DEBE incluir en el commit únicamente los cambios pertenecientes a la tarea actual y preservar cualquier cambio previo o ajeno que exista en el árbol de trabajo.
- El agente no debe dejar cambios solicitados solamente en local ni limitarse a preparar un commit: SIEMPRE debe intentar completar el `push` a `origin/main`.
- Antes de publicar, debe verificar que el commit que va a enviar contiene los cambios correctos. No debe usar `push --force` ni sobrescribir historia remota.
- Si el `push` no puede completarse por una causa técnica real (por ejemplo, autenticación, red, protección de rama o conflicto remoto), el agente debe informar claramente el bloqueo y dejar el commit local listo para publicar. Esa imposibilidad técnica es la única excepción admisible.
