# PX-32: laboratorio de robótica en familia

PX-32 es nuestro robot Mecanum. Este repositorio convierte el kit OSOYOO Mecanum Wheel Robotic Car Kit V2 en un curso de ciencia, electrónica, programación y robótica para un estudiante de 11 años que comienza desde cero, acompañado por su padre.

La meta no es copiar un programa y ver moverse el carro. La meta es poder explicar la cadena completa:

```text
MUNDO FÍSICO -> SENSOR -> SEÑAL ELÉCTRICA -> MEGA2560
             -> PROGRAMA -> DECISIÓN -> DRIVER -> MOTOR -> MOVIMIENTO
```

## Cómo empezar

1. Lee [Cómo usar este curso](COURSE-MAP.md).
2. Prepara el cuaderno con la [plantilla de bitácora](journal/PLANTILLA.md).
3. Comienza por [Lección 01 - Conocer nuestro laboratorio](course/00-fundamentos/01-conocer-nuestro-laboratorio.md).
4. Marca avances en [PROGRESS.md](PROGRESS.md).

No hace falta montar ni energizar PX-32 para las primeras lecciones. Las actividades que involucran baterías, cableado de potencia o motores indican explícitamente cuándo debe intervenir un adulto.

## Qué contiene el repositorio

| Ruta | Para qué sirve |
|---|---|
| `course/` | Lecciones ordenadas por bloques |
| `docs/hardware/` | Una ficha verificable por componente |
| `docs/reference/` | Glosario, conexiones, seguridad y solución de fallos |
| `docs/readings/` | Lecturas científicas para profundizar |
| `code/educational/` | Programas pequeños escritos para aprender |
| `code/osoyoo-original/` | Espacio reservado para código oficial, sin modificar |
| `quizzes/` y `solutions/` | Evaluaciones y respuestas separadas |
| `journal/` | Bitácora científica de padre e hijo |
| `projects/` | Proyectos integradores |
| `reference/original/` | Fuentes originales preservadas |
| `assets/osoyoo-manual/` | Selección de páginas visuales del PDF |

## Regla de procedencia

El material usa cuatro etiquetas:

- **OSOYOO:** dato o conexión tomada del manual entregado.
- **CURSO PX-32:** explicación pedagógica creada para este curso.
- **EXPERIMENTO PX-32:** actividad propuesta por nosotros.
- **OPCIONAL:** ampliación o recomendación no incluida en el kit.

Si una conexión no está confirmada, aparece `STATUS: PENDIENTE_DE_VERIFICAR`. No se conecta nada basándose en una suposición.

## Fuentes

- [PDF original del manual](reference/original/osoyoo-mecanum-wheel-robotic-car-kit-v2.pdf)
- [Markdown/OCR original](reference/original/osoyoo-mecanum-wheel-robotic-car-kit-v2-ocr.md)
- [Versión limpia y mapa de páginas](reference/osoyoo-manual.md)
- [Erratas e incertidumbres](docs/reference/errata-osoyoo.md)

El PDF es la fuente primaria para diagramas y cableado. El OCR solo facilita búsquedas. Para Arduino IDE se usa documentación oficial vigente, porque las capturas del manual corresponden al IDE 1.8 clásico.

## Dos computadores, un mismo laboratorio

El curso puede abrirse en macOS y Ubuntu. Al principio el padre puede encargarse de Git:

```bash
git clone URL_DEL_REPOSITORIO
git pull
git status
```

Más adelante PX-32 enseñará qué significan repositorio, commit, push, pull y branch. Por ahora basta con saber que Git guarda la historia del laboratorio.

Guía ampliada: [Git en dos computadores](docs/reference/git-dos-computadores.md).

## Estado actual

Esta es la fase de arquitectura: inventario, conexiones verificadas, mapa curricular, referencias, plantillas y ocho lecciones completas. Los bloques posteriores están diseñados, pero todavía no se presentan como terminados. Consulta [PROGRESS.md](PROGRESS.md) para el estado exacto.
