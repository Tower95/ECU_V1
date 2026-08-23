# Plataforma Vehicular Simulada - Gateway ECU y Control ECU

## Descripción

Este proyecto implementa una plataforma vehicular simulada en C++ formada por dos unidades principales:

- Gateway ECU: recibe y valida las señales vehiculares.
- Control ECU: utiliza únicamente las señales validadas para determinar la condición operativa del sistema y solicitar cambios de estado.

El programa permite ingresar manualmente cinco señales mediante consola, validar sus rangos físicos, comparar las señales válidas contra referencias operativas y actualizar una máquina de estados.

---

## Señales utilizadas

| Señal       | Unidad | Rango físico |
|-------------|--------|--------------|
| Velocidad   |   km/h |   0 a 250    |
| RPM         |   rpm  |   0 a 8000   |
| Temperatura |   °C   |   -40 a 150  |
| Acelerador  |    %   |   0 a 100    |
| Voltaje     |    V   |   9 a 16     |

Los rangos físicos son utilizados por la Gateway ECU para determinar si una lectura es confiable.

---

## Gateway ECU

La Gateway ECU valida cada señal y asigna uno de los siguientes estados:

- VALID: la señal está dentro del rango físico.
- OUT_OF_RANGE: la señal está fuera del rango físico.
- NOT_AVAILABLE: la señal no está disponible.

Una señal que no sea válida no se utiliza para evaluar referencias operativas.

---

## Referencias operativas de la Control ECU

### Temperatura

| Condición   |          Valor           |
|-------------|--------------------------|
| Normal      | menor de 100 °C          |
| Advertencia | 100 °C a menos de 110 °C |
| Crítica     | 110 °C o más             |

### RPM

| Condición   |       Valor       |
|-------------|-------------------|
| Normal      |   hasta 6000 rpm  |
| Advertencia | mayor de 6000 rpm |
| Crítica     | mayor de 7000 rpm |

### Voltaje

| Condición   |    Valor      |
|-------------|---------------|
| Normal      | 12 a 16 V     |
| Advertencia | menor de 12 V |
| Crítica     | menor de 11 V |

---

## Señales inválidas

La Control ECU también toma en cuenta la cantidad de señales rechazadas por la Gateway.

- 0 señales inválidas: condición normal.
- 1 o 2 señales inválidas: advertencia / falla menor.
- 3 o más señales inválidas: condición crítica.

---

## Reglas de coherencia

Además de analizar señales individuales, se revisan algunas relaciones entre señales:

- Velocidad mayor que 0 km/h con RPM iguales a 0.
- Acelerador mayor que 80 % con RPM menores de 500.
- Temperatura de advertencia junto con voltaje de advertencia.

Estas condiciones pueden generar una advertencia.

---

## Máquina de estados

La plataforma utiliza los siguientes estados:

- INIT: inicialización del sistema.
- SELF_TEST: autoprueba antes de operar.
- OPERATIONAL: funcionamiento normal.
- DEGRADED: advertencia o falla menor.
- SAFE_STATE: condición crítica.
- SHUTDOWN: apagado controlado.

### Transiciones principales

- INIT -> SELF_TEST
- SELF_TEST -> OPERATIONAL
- SELF_TEST -> DEGRADED
- SELF_TEST -> SAFE_STATE
- OPERATIONAL -> DEGRADED
- OPERATIONAL -> SAFE_STATE
- OPERATIONAL -> SHUTDOWN
- DEGRADED -> OPERATIONAL
- DEGRADED -> SAFE_STATE
- DEGRADED -> SHUTDOWN
- SAFE_STATE -> SHUTDOWN
- SHUTDOWN es el estado final.

Si una transición solicitada no está permitida, la máquina conserva el estado actual.

---

## Flujo del programa

1. El sistema inicia en INIT.
2. Cambia a SELF_TEST.
3. Se ejecuta una autoprueba básica.
4. El usuario ingresa las cinco señales.
5. La Gateway ECU valida los rangos físicos.
6. La Control ECU evalúa las señales válidas.
7. Se determina la condición global del sistema.
8. La Control ECU solicita un estado.
9. La máquina de estados verifica si la transición está permitida.
10. El usuario puede ingresar otro conjunto de señales o solicitar salir.
11. Al salir, el sistema pasa a SHUTDOWN.

---