# Solución - Evaluación del bloque inicial

## 1

Mega: procesamiento; MG90: actuador; tracker: sensor; Model Y: potencia/driver; chasis: estructura; ultrasónico: sensor; portabaterías: potencia.

## 2

`ultrasónico -> Mega2560 -> Model Y`.

## 3

Debe apagarse antes de retirar conexión; sujetar carcasa y no cables; levantar/detener ruedas antes de acercarse; retirar el tornillo conductor de la placa. Además, el área debe quedar estable y despejada.

## 4

El programa permanece en flash. Una variable ordinaria en SRAM no conserva el valor; al reiniciar vuelve a su inicialización.

## 5

250 + 750 = 1000 ms por ciclo. En 12 segundos caben idealmente 12 ciclos.

## 6

Ejemplos: cable sin datos, puerto equivocado/ocupado, placa incorrecta, bootloader/interfaz USB con problema, permisos del puerto.

## 7

```cpp
int prueba = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Hola, soy PX-32");
}

void loop() {
  Serial.print("Prueba: ");
  Serial.println(prueba);
  prueba = prueba + 1;
  delay(1000);
}
```

## 8

Debe distinguir: texto humano, traducción en el computador, transferencia por el puerto y ejecución autónoma desde flash. La redacción puede variar.
