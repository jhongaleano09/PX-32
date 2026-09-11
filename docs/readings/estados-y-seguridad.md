# Estados, prioridades y fallo seguro

Una máquina de estados enumera situaciones válidas y transiciones permitidas. STOP, MANUAL y AUTO evitan combinaciones implícitas. La seguridad es una prioridad de arbitraje: STOP domina órdenes de radio, línea o autonomía. Un timeout, sensor inválido o reinicio debe llevar a salidas detenidas. Integrar significa preservar esas invariantes mientras se añaden comportamientos.

## Para pensar

¿Qué parte de la cadena entrada → transformación → salida describe mejor esta lectura? Explica un límite del modelo antes de aplicarlo a PX-32.
