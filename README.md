# PX-32 — curso autónomo de ciencia, programación y robótica

Este repositorio transforma un OSOYOO Mecanum Wheel Robotic Car Kit V2 ya ensamblado en una ruta de 75 sesiones para un estudiante de 11 años que comienza desde cero. La lectura guía la sesión; el padre acompaña la conversación y se encarga de baterías, potencia, cableado dudoso y primeras pruebas de movimiento.

## Empezar

1. Lee con el adulto las [reglas de seguridad](docs/reference/seguridad.md).
2. Abre el [mapa canónico](COURSE-MAP.md).
3. Comienza por la [Lección 01](course/00-fundamentos/01-que-es-un-robot.md).
4. Al terminar la actividad y “Cuéntale a papá”, marca la sesión en [PROGRESS.md](PROGRESS.md).

PX-32 permanece ensamblado siempre que sea posible. Si una sesión requiere una verificación o cambio, lo indica con semáforo 🟢/🟡/🔴, apagado, revisión y restauración. El cuaderno físico es opcional; no se exige diario digital ni evaluación escolar repetitiva.

## Fuentes y exactitud

El [PDF de OSOYOO](reference/original/osoyoo-mecanum-wheel-robotic-car-kit-v2.pdf) es la fuente primaria de conexiones. El [mapa canónico](docs/reference/mapa-conexiones-robot.md) registra los pines confirmados visualmente y la [errata](docs/reference/errata-osoyoo.md) conserva contradicciones y asuntos pendientes. Nunca se infieren voltajes o corrientes ausentes del fabricante.

## Estructura

- `course/`: 75 lecciones desarrolladas en una única secuencia.
- `code/educational/`: sketches mínimos enlazados desde las lecciones.
- `docs/readings/`: lecturas internas de apoyo.
- `docs/hardware/`: fichas de los componentes reales.
- `docs/reference/`: seguridad, pinout, conexiones, glosario y depuración.
- `assets/osoyoo-manual/`: recortes visuales verificados del manual.
- `reference/original/`: PDF original del fabricante.
