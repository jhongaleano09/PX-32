#!/usr/bin/env python3
"""Validación estructural, curricular, de enlaces y sketches de PX-32."""
from pathlib import Path
import re, sys

ROOT=Path(__file__).resolve().parents[1]
errors=[]
lessons=sorted((ROOT/'course').glob('*[0-9]*/[0-9][0-9]-*.md'))

def fail(msg): errors.append(msg)

if len(lessons)!=75: fail(f"Se esperaban 75 lecciones; hay {len(lessons)}")
numbers=[]
processed_blocks={'00-fundamentos', '01-programacion'}
student_pillars=["## Lecturas y videos para explorar",
                 "## Referencias técnicas de la clase",
                 "## Cuéntale a papá"]
obsolete_template_headings=["## 2. Tiempo estimado", "## 6. Así aparece en PX-32",
                            "## 10. Código", "## 16. Resumen de la jornada"]

link_re=re.compile(r'(?<!!)\[[^]]+\]\(([^)]+)\)')
for p in lessons:
    txt=p.read_text(encoding='utf-8')
    m=re.match(r'(\d\d)-',p.name)
    if not m: fail(f"Nombre sin número: {p}"); continue
    n=int(m.group(1)); numbers.append(n)
    if not txt.startswith(f"# Lección {n:02d} —"): fail(f"Título/nombre no coinciden: {p}")
    if len(re.findall(r'\b[\wÁÉÍÓÚÜÑáéíóúüñ]+\b',txt)) < 800: fail(f"Menos de 800 palabras: {p}")
    if p.parent.name in processed_blocks:
        for section in student_pillars:
            if section not in txt: fail(f"Falta {section} en {p}")
        for heading in obsolete_template_headings:
            if heading in txt: fail(f"Queda encabezado de plantilla {heading} en {p}")
        if "**Total: 40 minutos.**" in txt:
            fail(f"Queda tiempo estimado de plantilla en {p}")
        if '[PENDIENTE VISUAL]' in txt:
            for field in ['**Tipo:**', '**Objetivo:**', '**Descripción:**',
                          '**Elementos que deben señalarse:**', '**Fuente técnica:**',
                          '**Texto alternativo sugerido:**']:
                if field not in txt: fail(f"Marcador visual incompleto ({field}) en {p}")
        linked_ino=re.findall(r'\[[^]]+\.ino\]\(([^)]+\.ino)\)', txt)
        for dest in linked_ino:
            sketch=(p.parent/dest).resolve()
            if sketch.exists():
                blocks=re.findall(r'```cpp\n(.*?)\n```', txt, flags=re.S)
                sketch_text=sketch.read_text(encoding='utf-8').strip()
                if not any(block.strip() == sketch_text for block in blocks):
                    fail(f"El bloque de código no coincide con {dest} en {p}")
    for dest in link_re.findall(txt):
        if dest.startswith(('http://','https://','#')): continue
        target=(p.parent/dest.split('#')[0]).resolve()
        if not target.exists(): fail(f"Enlace roto {dest} en {p}")

if numbers != list(range(1,76)): fail(f"Numeración real: {numbers}")

for block in processed_blocks:
    readme=ROOT/'course'/block/'README.md'
    if readme.exists(): fail(f"README de bloque procesado no eliminado: {readme}")
if (ROOT/'templates'/'LECCION-PLANTILLA.md').exists():
    fail("La plantilla rígida templates/LECCION-PLANTILLA.md todavía existe")

for p in ROOT.glob('**/*.md'):
    if '.git' in p.parts: continue
    txt=p.read_text(encoding='utf-8')
    for dest in link_re.findall(txt):
        if dest.startswith(('http://','https://','#','mailto:')): continue
        target=(p.parent/dest.split('#')[0]).resolve()
        if not target.exists(): fail(f"Enlace roto {dest} en {p.relative_to(ROOT)}")

sketches=sorted((ROOT/'code'/'educational').glob('*/*.ino'))
if len(sketches)!=44: fail(f"Se esperaban 44 sketches; hay {len(sketches)}")
for p in sketches:
    if p.parent.name != p.stem: fail(f"Carpeta/ino no coinciden: {p}")
    txt=p.read_text(encoding='utf-8')
    if 'void setup()' not in txt or 'void loop()' not in txt: fail(f"Falta estructura Arduino: {p}")
    # Balance sencillo de delimitadores fuera de cadenas no es compilador, pero detecta truncados.
    if txt.count('{')!=txt.count('}'): fail(f"Llaves desbalanceadas: {p}")

canonical=(ROOT/'docs/reference/mapa-conexiones-robot.md').read_text(encoding='utf-8')
for token in ['D11','D5','D6','D7','D8','D12','D9','D22','D24','D26','D28','D10','A4','A3','A2','A1','A0','D30','D31','D13','D19/RX1','D18/TX1']:
    if token not in canonical: fail(f"Falta pin canónico {token}")

obsolete=[]
for p in ROOT.glob('**/*.md'):
    if any(part in {'.git','tmp'} for part in p.parts): continue
    txt=p.read_text(encoding='utf-8')
    if re.search(r'PLANIFICADO|## Quiz|## Bitácora|solutions/|quizzes/|journal/',txt): obsolete.append(str(p.relative_to(ROOT)))
if obsolete: fail('Referencias obsoletas: '+', '.join(obsolete))

if errors:
    print('\n'.join('ERROR: '+e for e in errors)); sys.exit(1)
print(f"OK: {len(lessons)} lecciones, {len(sketches)} sketches, numeración 01–75, bloques procesados y enlaces internos válidos.")
