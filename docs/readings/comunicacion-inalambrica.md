# Bluetooth, Wi-Fi y UART

Bluetooth y Wi-Fi usan radio, pero organizan enlaces distintos. En PX-32, el módulo inalámbrico intercambia bytes con la Mega por UART. TX de un extremo llega a RX del otro y ambos acuerdan velocidad. Bluetooth y ESP8266 comparten Serial1: solo una ruta B/E puede estar activa. Un comando desconocido o antiguo debe producir STOP.

## Para pensar

¿Qué parte de la cadena entrada → transformación → salida describe mejor esta lectura? Explica un límite del modelo antes de aplicarlo a PX-32.
