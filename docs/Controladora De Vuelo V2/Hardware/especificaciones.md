# Especificaciones técnicas

Esta sección resume las especificaciones principales de la **Controladora de Vuelo V2** a partir de los bloques visibles en el esquemático eléctrico y el diagrama general de conexiones.

La tarjeta integra procesamiento embebido, sensores inerciales y ambientales, memoria externa, comunicación USB, CAN, LoRa, entrada SBUS, salidas PWM y canales dedicados para eventos de misión. Su diseño está orientado a aplicaciones de cohetería experimental, adquisición de datos, recuperación electrónica y validación de sistemas de vuelo.

!!! warning "Proyecto en desarrollo"
    Las especificaciones aquí descritas corresponden a la revisión actual documentada del hardware. Antes de fabricar, integrar o utilizar la tarjeta en pruebas reales, revisa los esquemáticos, archivos de fabricación y notas de versión más recientes.

## Resumen general

| Característica               | Especificación                                                                     |
| ---------------------------- | ---------------------------------------------------------------------------------- |
| Nombre de la tarjeta         | Controladora de Vuelo V2                                                           |
| Aplicación principal         | Aviónica, adquisición de datos, telemetría, recuperación y validación experimental |
| Microcontrolador             | STM32F722RET6                                                                      |
| Arquitectura del MCU         | ARM Cortex-M7                                                                      |
| Alimentación principal       | 5 V a 28 V                                                                         |
| Regulación principal         | Convertidor step-down a 5 V                                                        |
| Regulación lógica            | Regulador lineal a 3.3 V                                                           |
| Memoria externa              | Flash SPI S25FL064L                                                                |
| Capacidad de memoria externa | 64 Mbit / 8 MB                                                                     |
| Comunicación USB             | Micro USB con protección ESD                                                       |
| Comunicación CAN             | Transceptor CAN externo                                                            |
| Comunicación RF              | Módulo LoRa RA-01SH-P                                                              |
| Entrada RC                   | SBUS con inversión de señal                                                        |
| Sensores inerciales          | MPU-6050 e ICM-42670-P                                                             |
| Sensor ambiental             | BME280                                                                             |
| Salidas PWM                  | 4 canales para servos o actuadores                                                 |
| Eventos de misión            | 2 salidas independientes mediante relevadores de estado sólido                     |
| Programación y depuración    | Interfaz SWD mediante ST-Link                                                      |

## Procesamiento

La tarjeta utiliza un microcontrolador **STM32F722RET6**, encargado de ejecutar el firmware principal, administrar periféricos, adquirir sensores, registrar datos y controlar salidas.

| Parámetro              | Descripción   |
| ---------------------- | ------------- |
| Microcontrolador       | STM32F722RET6 |
| Encapsulado observado  | LQFP64        |
| Núcleo                 | ARM Cortex-M7 |
| Alimentación lógica    | 3.3 V         |
| Oscilador externo      | 25 MHz        |
| Programación           | SWD           |
| Interfaz de depuración | ST-Link       |

El microcontrolador centraliza las señales de sensores, memoria, comunicaciones, salidas PWM y canales de eventos de misión.

## Alimentación

La tarjeta está diseñada para aceptar una alimentación principal en el rango de **5 V a 28 V**. Internamente, el sistema genera los rieles necesarios para alimentar la lógica, periféricos y módulos externos.

| Riel     | Descripción                                     |
| -------- | ----------------------------------------------- |
| `VCC`    | Entrada principal de alimentación               |
| `5V`     | Riel generado mediante convertidor step-down    |
| `3V3`    | Riel lógico generado mediante regulador lineal  |
| `3V3_RF` | Riel dedicado para el módulo de radiofrecuencia |

### Bloques de alimentación

El sistema de alimentación está compuesto por:

* Entrada principal `VCC`.
* Convertidor step-down a 5 V.
* Regulador lineal de 3.3 V.
* Regulador dedicado para el riel `3V3_RF`.
* Capacitores de desacoplo en rieles principales.
* Red de habilitación para el convertidor step-down.

!!! note "Rango de alimentación"
    El diagrama visual de conexiones indica una alimentación compatible con baterías de 2S a 6S, equivalente aproximadamente a un rango de 5 V a 28 V.

!!! warning "Revisión antes de energizar"
    Antes de alimentar la tarjeta, verifica polaridad, continuidad, rango de voltaje, conexión de tierra y ausencia de cortocircuitos. No conectes sistemas críticos durante las primeras pruebas de alimentación.

## Memoria externa

La tarjeta integra una memoria flash externa para registro de datos de vuelo, eventos y mensajes del sistema.

| Parámetro    | Especificación                                          |
| ------------ | ------------------------------------------------------- |
| Componente   | S25FL064L                                               |
| Tipo         | Memoria flash SPI                                       |
| Capacidad    | 64 Mbit / 8 MB                                          |
| Alimentación | 3.3 V                                                   |
| Interfaz     | SPI                                                     |
| Uso previsto | Blackbox, registro de eventos y almacenamiento de datos |

### Señales principales

| Señal         | Descripción                                     |
| ------------- | ----------------------------------------------- |
| `FLASH_CS`    | Selección de chip                               |
| `FLASH_SCK`   | Reloj SPI                                       |
| `FLASH_MISO`  | Datos del dispositivo hacia el microcontrolador |
| `FLASH_MOSI`  | Datos del microcontrolador hacia el dispositivo |
| `FLASH_WP`    | Protección de escritura                         |
| `FLASH_RESET` | Reinicio del dispositivo                        |

## Sensores integrados

La Controladora de Vuelo V2 integra sensores inerciales y ambientales para adquisición de datos y estimación básica del estado del vehículo.

### MPU-6050

| Parámetro           | Descripción                       |
| ------------------- | --------------------------------- |
| Sensor              | MPU-6050                          |
| Tipo                | IMU de 6 ejes                     |
| Mediciones          | Acelerómetro y giroscopio         |
| Interfaz            | I2C                               |
| Alimentación        | 3.3 V                             |
| Señales principales | `I2C2_SDA`, `I2C2_SCL`, `MPU_INT` |

### ICM-42670-P

| Parámetro           | Descripción                                                            |
| ------------------- | ---------------------------------------------------------------------- |
| Sensor              | ICM-42670-P                                                            |
| Tipo                | IMU de 6 ejes                                                          |
| Mediciones          | Acelerómetro y giroscopio                                              |
| Interfaz            | SPI                                                                    |
| Alimentación        | 3.3 V                                                                  |
| Señales principales | `SPI2_MISO`, `SPI2_MOSI`, `SPI2_SCLK`, `ICM_CS`, `ICM_INT`, `ICM_INT2` |

### BME280

| Parámetro           | Descripción                                        |
| ------------------- | -------------------------------------------------- |
| Sensor              | BME280                                             |
| Tipo                | Sensor ambiental                                   |
| Mediciones          | Presión, temperatura y humedad                     |
| Interfaz            | SPI                                                |
| Alimentación        | 3.3 V                                              |
| Señales principales | `SPI2_MISO`, `SPI2_MOSI`, `SPI2_SCLK`, `BME280_CS` |

## Comunicación

La tarjeta integra múltiples interfaces de comunicación para depuración, expansión, telemetría y conexión con periféricos externos.

### USB

| Parámetro    | Descripción                                                       |
| ------------ | ----------------------------------------------------------------- |
| Conector     | Micro USB                                                         |
| Señales      | `USB_D+`, `USB_D-`                                                |
| Protección   | USBLC6-2SC6                                                       |
| Uso previsto | Comunicación local, configuración, descarga de datos o depuración |

El puerto USB incluye protección ESD mediante un arreglo dedicado para las líneas diferenciales.

### CAN

| Parámetro                    | Descripción                                                          |
| ---------------------------- | -------------------------------------------------------------------- |
| Interfaz                     | CAN                                                                  |
| Señales MCU                  | `CAN_TX`, `CAN_RX`                                                   |
| Señales externas             | `CAN_H`, `CAN_L`                                                     |
| Alimentación del transceptor | 5 V                                                                  |
| Terminación                  | Resistencia de 120 Ω visible en el bloque CAN                        |
| Uso previsto                 | Expansión, periféricos externos o comunicación robusta entre módulos |

El bloque CAN incluye transceptor externo, capacitores de filtrado y conector dedicado.

### LoRa

| Parámetro    | Descripción                        |
| ------------ | ---------------------------------- |
| Módulo       | RA-01SH-P                          |
| Tipo         | Módulo LoRa                        |
| Alimentación | `3V3_RF`                           |
| Interfaz     | SPI y señales de control           |
| Uso previsto | Telemetría y recepción de comandos |

Señales principales observadas:

| Señal      | Descripción                             |
| ---------- | --------------------------------------- |
| `RF_MISO`  | Datos desde módulo RF                   |
| `RF_MOSI`  | Datos hacia módulo RF                   |
| `RF_SCK`   | Reloj SPI                               |
| `RF_CS`    | Selección de chip                       |
| `RF_RESET` | Reinicio del módulo                     |
| `RF_BUSY`  | Estado ocupado del módulo               |
| `RF_DIO1`  | Interrupción o señal digital del módulo |

### SBUS

| Parámetro         | Descripción                                        |
| ----------------- | -------------------------------------------------- |
| Entrada           | SBUS                                               |
| Circuito asociado | Inversor de señal                                  |
| Uso previsto      | Recepción de comandos desde receptor RC compatible |
| Señal lógica      | `SBUS_UC`                                          |

El bloque SBUS incluye una etapa de inversión para adaptar la señal al microcontrolador.

## Conectores externos

La tarjeta cuenta con conectores para alimentación, servos, SBUS, CAN, GPS, USB, eventos de misión y programación.

### Conector de servos y SBUS

El conector de servos agrupa alimentación, tierra, entrada SBUS y salidas PWM.

| Señal    | Descripción                            |
| -------- | -------------------------------------- |
| `GND`    | Tierra                                 |
| `5V`     | Alimentación para periféricos o servos |
| `SBUS`   | Entrada de receptor                    |
| `SERVO1` | Salida PWM 1                           |
| `SERVO2` | Salida PWM 2                           |
| `SERVO3` | Salida PWM 3                           |
| `SERVO4` | Salida PWM 4                           |

!!! warning "Carga en salidas de 5 V"
    Antes de alimentar servos desde la tarjeta, verifica la capacidad de corriente del sistema de alimentación y del conector correspondiente. Los servos pueden demandar corrientes elevadas durante arranque o bloqueo mecánico.

### Conector CAN

| Señal   | Descripción    |
| ------- | -------------- |
| `+5V`   | Alimentación   |
| `GND`   | Tierra         |
| `CAN_H` | Línea alta CAN |
| `CAN_L` | Línea baja CAN |

### Conector GPS

| Señal     | Descripción           |
| --------- | --------------------- |
| `GPS_TX`  | Transmisión desde GPS |
| `GPS_RX`  | Recepción hacia GPS   |
| `GPS_SCL` | Línea I2C SCL         |
| `GPS_SDA` | Línea I2C SDA         |
| `5V`      | Alimentación          |
| `GND`     | Tierra                |

## Salidas PWM

La tarjeta dispone de cuatro salidas PWM etiquetadas como:

| Canal | Señal    |
| ----- | -------- |
| PWM 1 | `SERVO1` |
| PWM 2 | `SERVO2` |
| PWM 3 | `SERVO3` |
| PWM 4 | `SERVO4` |

Estas salidas pueden utilizarse para servos, actuadores auxiliares o mecanismos compatibles con señal PWM.

## Eventos de misión

La Controladora de Vuelo V2 incluye dos canales independientes para eventos de misión. Estos canales están implementados mediante relevadores de estado sólido **GAQY212GSX** y cuentan con indicadores visuales asociados.

| Canal  | Señal de control | Descripción                                 |
| ------ | ---------------- | ------------------------------------------- |
| Pyro 1 | `MCU_PYRO1`      | Canal independiente para evento de misión 1 |
| Pyro 2 | `MCU_PYRO2`      | Canal independiente para evento de misión 2 |

Cada canal incluye:

* Relevador de estado sólido.
* Resistencia limitadora.
* Indicador LED.
* Conector de salida.
* Interruptor físico de armado según el diagrama visual.

!!! danger "Salidas de eventos de misión"
    Los canales de eventos de misión pueden interactuar con sistemas críticos. Durante pruebas de firmware, depuración o integración inicial, estos canales deben permanecer deshabilitados y sin cargas críticas conectadas.

!!! warning "Armado físico"
    El diagrama visual muestra interruptores físicos de armado para las salidas de eventos de misión. Estos interruptores deben utilizarse como parte de un procedimiento de seguridad y no deben sustituirse por comandos de software.

## Indicadores y depuración

La tarjeta incluye elementos de apoyo para diagnóstico, depuración e interacción básica.

| Elemento       | Descripción                                     |
| -------------- | ----------------------------------------------- |
| LED de usuario | Indicadores controlados por el microcontrolador |
| LED de eventos | Indicadores asociados a canales de misión       |
| Botón de reset | Reinicio manual del microcontrolador            |
| Interfaz SWD   | Programación y depuración mediante ST-Link      |
| Puerto USB     | Comunicación local o depuración, según firmware |

## Protecciones visibles

A partir del esquemático se observan las siguientes protecciones o elementos de acondicionamiento:

| Bloque       | Protección o acondicionamiento                               |
| ------------ | ------------------------------------------------------------ |
| USB          | Protección ESD USBLC6-2SC6                                   |
| Alimentación | Capacitores de entrada y salida en reguladores               |
| RF           | Regulador dedicado para alimentación del módulo LoRa         |
| Sensores     | Capacitores de desacoplo cercanos a los circuitos integrados |
| CAN          | Terminación y filtrado en líneas diferenciales               |
| SBUS         | Inversor de señal para adaptación lógica                     |

## Interfaces del microcontrolador

Resumen de interfaces utilizadas por el microcontrolador:

| Interfaz | Uso                                                          |
| -------- | ------------------------------------------------------------ |
| SPI      | Flash externa, BME280, ICM-42670-P, LoRa                     |
| I2C      | MPU-6050 y conector GPS                                      |
| UART     | GPS, SBUS o comunicación auxiliar según firmware             |
| USB      | Comunicación local                                           |
| CAN      | Bus CAN externo                                              |
| GPIO     | Control de eventos, LEDs, selección de chip e interrupciones |
| Timers   | Generación PWM para servos                                   |
| SWD      | Programación y depuración                                    |

## Consideraciones de integración

Antes de integrar la tarjeta en un vehículo o banco de pruebas, revisa:

* Rango de alimentación.
* Polaridad de entrada.
* Pinout de conectores.
* Tierra común entre módulos.
* Capacidad de corriente de salidas de 5 V.
* Aislamiento de canales de eventos de misión.
* Configuración del firmware cargado.
* Estado de interruptores físicos.
* Continuidad de conexiones.
* Fijación mecánica de la PCB.
* Protección contra vibración y desconexión accidental.

## Limitaciones conocidas

Las siguientes limitaciones deben considerarse durante el uso y documentación de la tarjeta:

* La documentación del hardware aún se encuentra en desarrollo.
* Las capacidades reales de corriente deben validarse mediante pruebas.
* Las funciones de telemetría dependen del estado actual del firmware.
* Las salidas críticas requieren procedimientos de seguridad externos.
* Las especificaciones pueden cambiar entre revisiones de hardware.

## Páginas relacionadas

* [Introducción al hardware](Hardware.md)
* [Alimentación](alimentacion.md)
* [Conectores y pinout](conectores-pinout.md)
* [Archivos de fabricación](archivos-fabricacion.md)
* [Consideraciones de diseño](consideraciones-diseno.md)
