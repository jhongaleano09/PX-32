# Git en dos computadores

Esta guía permite recibir las lecciones actualizadas en el MacBook Air y el equipo Ubuntu. Al principio el adulto administra publicación y conflictos.

## Primera copia: `git clone`

`clone` crea una copia local con su historial. Se ejecuta una sola vez por computador, reemplazando la URL por la del repositorio real:

```bash
git clone URL_DEL_REPOSITORIO
cd genomo_bot
```

No inventar ni pegar credenciales dentro de la URL. Usar el método de autenticación configurado por el adulto.

## Antes de una sesión: `git status`

Dentro del repositorio:

```bash
git status
```

Muestra rama y archivos modificados. No borra ni sube nada. Si aparecen cambios inesperados, se detiene el flujo y se identifica quién los hizo.

## Recibir cambios: `git pull`

Con el trabajo local guardado y entendido:

```bash
git pull
```

`pull` trae cambios del repositorio remoto e intenta integrarlos. Si informa un conflicto, no elegir una versión al azar; conservar ambos trabajos y pedir ayuda.

## Rutina inicial

```text
abrir terminal -> entrar al repositorio -> git status
               -> si está limpio, git pull -> abrir la lección
```

El estudiante no necesita `commit` o `push` para comenzar. Sus primeras bitácoras pueden ser guardadas por el adulto.

## Microlección futura: guardar la historia

Cuando el estudiante domine archivos y errores de sintaxis se introducirá:

- **repository:** proyecto con historial;
- **commit:** fotografía explicada de un cambio;
- **push:** publicar commits propios;
- **pull:** recibir e integrar;
- **branch:** línea de trabajo separada.

La práctica creará una rama para una modificación de Blink, un commit con mensaje que explique el experimento y una comparación antes/después. No se usará Git como castigo ni requisito para comprender electrónica.
