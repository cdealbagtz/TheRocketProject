# Conectores y pinout

Esta sección describe los conectores principales de la **Controladora de Vuelo V2**, sus señales asociadas y su uso previsto durante la integración con el vehículo, banco de pruebas o periféricos externos.

La siguiente imagen muestra un resumen visual de las conexiones principales de la tarjeta:

![Diagrama visual de conexiones](../Diagrama%20visual%20de%20conexiones.png)

!!! note "Referencia visual"
    El diagrama anterior muestra una vista simplificada de conexión. Para integración final, fabricación o revisión eléctrica, consulta también el esquemático completo y los archivos de fabricación de la tarjeta.

## Resumen de conectores

| Conector                         | Uso principal                                     | Señales principales                                         |
| -------------------------------- | ------------------------------------------------- | ----------------------------------------------------------- |
| Alimentación y eventos de misión | Entrada de energía y conexión de canales críticos | `VCC`, `GND`, `PYRO1`, `PYRO2`                              |
| Servos / SBUS                    | Entrada RC y salidas PWM                          | `SBUS`, `SERVO1`, `SERVO2`, `SERVO3`, `SERVO4`, `5V`, `GND` |
| CAN                              | Comunicación con periféricos externos             | `+5V`, `GND`, `CAN_H`, `CAN_L`                              |
| Micro USB                        | Comunicación local y depuración                   | `USB_D+`, `USB_D-`, `VBUS`, `GND`                           |
| GPS                              | Conexión de módulo GPS externo                    | `GPS_TX`, `GPS_RX`, `GPS_SCL`, `GPS_SDA`, `5V`, `GND`       |
| SWD                              | Programación y depuración                         | `SWDIO`, `SWCLK`                                            |
| Interruptores de armado          | Habilitación física de eventos críticos           | Armado de canales `PYRO1` y `PYRO2`                         |

## Alimentación principal y eventos de misión

La tarjeta cuenta con un conector principal para alimentación y salidas asociadas a eventos de misión. En el diagrama visual este conector se muestra como una bornera verde.

Este bloque permite conectar:

* Entrada principal de alimentación.
* Tierra del sistema.
* Canal de evento de misión 1.
* Canal de evento de misión 2.

| Señal   | Descripción                                      |
| ------- | ------------------------------------------------ |
| `VCC`   | Entrada principal de alimentación de la tarjeta. |
| `GND`   | Referencia de tierra del sistema.                |
| `PYRO1` | Canal independiente para evento de misión 1.     |
| `PYRO2` | Canal independiente para evento de misión 2.     |

La tarjeta está diseñada para aceptar alimentación en un rango aproximado de **5 V a 28 V**, equivalente a baterías de **2S a 6S**, según el diagrama de conexión.

!!! warning "Polaridad de alimentación"
    Antes de energizar la tarjeta, verifica la polaridad de entrada, continuidad, ausencia de cortocircuitos y rango de voltaje. Una conexión incorrecta puede dañar la tarjeta o los periféricos conectados.

!!! danger "Canales de eventos de misión"
    Los canales `PYRO1` y `PYRO2` pueden estar asociados a sistemas críticos de recuperación, separación o activación de eventos. Durante pruebas de firmware, depuración o integración inicial, estos canales deben permanecer desconectados de cualquier carga crítica.

## Interruptores físicos de armado

La Controladora de Vuelo V2 incluye interruptores físicos de armado para los canales de eventos de misión. Estos interruptores funcionan como una barrera adicional de seguridad entre el firmware y las salidas críticas.

| Elemento            | Función                                              |
| ------------------- | ---------------------------------------------------- |
| Interruptor `PYRO1` | Habilita físicamente el canal de evento de misión 1. |
| Interruptor `PYRO2` | Habilita físicamente el canal de evento de misión 2. |

!!! warning "El armado físico no sustituye al procedimiento de seguridad"
    Los interruptores físicos reducen el riesgo de activación no deseada, pero no sustituyen un procedimiento formal de seguridad. Antes de armar cualquier canal crítico, se debe verificar el estado del firmware, alimentación, continuidad, conexión de cargas y condiciones de prueba.

## Conector de servos y SBUS

El conector de servos agrupa la entrada `SBUS`, las salidas PWM y las líneas de alimentación para periféricos o actuadores compatibles.

| Señal    | Descripción                                                       |
| -------- | ----------------------------------------------------------------- |
| `SBUS`   | Entrada de señal desde receptor RC compatible con protocolo SBUS. |
| `SERVO1` | Salida PWM 1.                                                     |
| `SERVO2` | Salida PWM 2.                                                     |
| `SERVO3` | Salida PWM 3.                                                     |
| `SERVO4` | Salida PWM 4.                                                     |
| `5V`     | Alimentación para receptor, servos o periféricos compatibles.     |
| `GND`    | Tierra común para señales y alimentación.                         |

Las salidas `SERVO1` a `SERVO4` pueden utilizarse para servos, actuadores auxiliares o mecanismos que acepten señales PWM.

!!! warning "Corriente en servos"
    Los servos pueden demandar corrientes elevadas, especialmente durante arranque, carga mecánica o bloqueo. Antes de alimentar servos desde la tarjeta, verifica que el sistema de alimentación pueda suministrar la corriente necesaria sin provocar caídas de voltaje o reinicios del microcontrolador.

## Conector CAN

El conector CAN permite comunicación diferencial con periféricos externos, módulos de expansión u otros sistemas compatibles.

| Orden visual | Señal   | Descripción                             |
| ------------ | ------- | --------------------------------------- |
| 1            | `+5V`   | Alimentación para periféricos externos. |
| 2            | `GND`   | Tierra común.                           |
| 3            | `CAN_H` | Línea alta del bus CAN.                 |
| 4            | `CAN_L` | Línea baja del bus CAN.                 |

El bloque CAN incluye un transceptor externo y terminación del bus, de acuerdo con el esquemático de la tarjeta.

!!! note "Integración CAN"
    Para una comunicación confiable, verifica que todos los dispositivos del bus compartan tierra común, que las líneas `CAN_H` y `CAN_L` no estén invertidas y que la terminación del bus sea adecuada para la topología utilizada.

## Conector Micro USB

El conector Micro USB permite comunicación local con la tarjeta. Dependiendo del firmware cargado, puede utilizarse para configuración, depuración, descarga de datos o comunicación con herramientas externas.

| Señal    | Descripción                       |
| -------- | --------------------------------- |
| `USB_D+` | Línea diferencial positiva USB.   |
| `USB_D-` | Línea diferencial negativa USB.   |
| `VBUS`   | Alimentación detectada desde USB. |
| `GND`    | Tierra de USB.                    |

El diseño incluye protección ESD en las líneas USB mediante un arreglo de protección dedicado.

!!! note "Uso del puerto USB"
    El puerto USB puede estar disponible para comunicación dependiendo del estado actual del firmware. Consulta la documentación del firmware para conocer los comandos, mensajes o funciones disponibles.

## Conector GPS

La tarjeta cuenta con un conector dedicado para integrar un módulo GPS externo. Este conector expone señales UART, señales I2C y alimentación.

| Pin / señal | Descripción                                    |
| ----------- | ---------------------------------------------- |
| `GPS_TX`    | Línea de transmisión del GPS hacia la tarjeta. |
| `GPS_RX`    | Línea de recepción del GPS desde la tarjeta.   |
| `GPS_SCL`   | Línea de reloj I2C.                            |
| `GPS_SDA`   | Línea de datos I2C.                            |
| `5V`        | Alimentación para el módulo GPS.               |
| `GND`       | Tierra común.                                  |

!!! warning "Niveles lógicos"
    Antes de conectar un módulo GPS externo, verifica sus niveles lógicos. Las señales del microcontrolador operan a **3.3 V**, por lo que no deben conectarse señales de datos de 5 V directamente si el módulo no es compatible.

## Interfaz de programación SWD

La programación y depuración del microcontrolador se realiza mediante interfaz **SWD** utilizando un programador compatible, como **ST-Link**.

| Señal           | Descripción                                                                  |
| --------------- | ---------------------------------------------------------------------------- |
| `SWDIO`         | Línea de datos de depuración.                                                |
| `SWCLK`         | Línea de reloj de depuración.                                                |
| `GND`           | Tierra común entre programador y tarjeta.                                    |
| `3V3` / `VTref` | Referencia de voltaje para el programador, si aplica.                        |
| `NRST`          | Reset del microcontrolador, si está disponible en la conexión de depuración. |

!!! note "Conexión mínima"
    Para depuración básica mediante ST-Link normalmente se requiere `SWDIO`, `SWCLK`, `GND` y referencia de voltaje. Verifica el conector físico de tu revisión de hardware antes de conectar el programador.

## Señales de sensores internos

Los sensores principales se encuentran integrados directamente en la tarjeta, por lo que normalmente no requieren conexión externa. Sin embargo, sus señales se documentan como referencia.

| Componente     | Interfaz   | Señales principales                                                            |
| -------------- | ---------- | ------------------------------------------------------------------------------ |
| MPU-6050       | I2C        | `I2C2_SDA`, `I2C2_SCL`, `MPU_INT`                                              |
| ICM-42670-P    | SPI        | `SPI2_MISO`, `SPI2_MOSI`, `SPI2_SCLK`, `ICM_CS`, `ICM_INT`, `ICM_INT2`         |
| BME280         | SPI        | `SPI2_MISO`, `SPI2_MOSI`, `SPI2_SCLK`, `BME280_CS`                             |
| Flash externa  | SPI        | `FLASH_CS`, `FLASH_SCK`, `FLASH_MISO`, `FLASH_MOSI`, `FLASH_WP`, `FLASH_RESET` |
| LoRa RA-01SH-P | SPI / GPIO | `RF_MISO`, `RF_MOSI`, `RF_SCK`, `RF_CS`, `RF_RESET`, `RF_BUSY`, `RF_DIO1`      |

## Recomendaciones de conexión

Antes de conectar periféricos externos, se recomienda revisar lo siguiente:

* Confirmar el pinout del conector físico.
* Verificar polaridad y nivel de voltaje.
* Confirmar que todos los módulos compartan `GND`.
* Evitar conectar o desconectar periféricos con la tarjeta energizada.
* Mantener cables de señales sensibles alejados de líneas de potencia.
* Verificar continuidad antes de conectar cargas.
* Realizar pruebas iniciales sin cargas críticas.
* Documentar cualquier modificación realizada al cableado.

## Errores comunes

| Problema                           | Posible causa                                                                | Revisión recomendada                             |
| ---------------------------------- | ---------------------------------------------------------------------------- | ------------------------------------------------ |
| La tarjeta no enciende             | Polaridad incorrecta, voltaje insuficiente o corto en alimentación           | Verificar `VCC`, `GND` y consumo de entrada.     |
| El GPS no comunica                 | TX/RX invertidos o niveles lógicos incompatibles                             | Revisar `GPS_TX`, `GPS_RX` y configuración UART. |
| El bus CAN no responde             | `CAN_H` y `CAN_L` invertidos, falta de tierra común o terminación incorrecta | Revisar cableado y terminación del bus.          |
| El receptor SBUS no funciona       | Señal incorrecta, falta de alimentación o configuración de firmware          | Revisar `SBUS`, `5V`, `GND` y protocolo.         |
| Los servos se reinician o tiemblan | Caída de voltaje o corriente insuficiente                                    | Verificar alimentación de 5 V y consumo total.   |
| No se puede programar la tarjeta   | Conexión SWD incorrecta o falta de referencia de voltaje                     | Revisar `SWDIO`, `SWCLK`, `GND` y `VTref`.       |

## Páginas relacionadas

* [Introducción al hardware](Hardware.md)
* [Especificaciones técnicas](especificaciones.md)
* [Alimentación](alimentacion.md)
* [Archivos de fabricación](archivos-fabricacion.md)
* [Consideraciones de diseño](consideraciones-diseno.md)
