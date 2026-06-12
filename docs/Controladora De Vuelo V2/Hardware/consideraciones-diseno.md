# Consideraciones de diseño

Esta sección reúne las principales consideraciones técnicas tomadas en cuenta durante el diseño de hardware de la **Controladora de Vuelo V2**. Su objetivo es documentar criterios de diseño, decisiones importantes, limitaciones conocidas y recomendaciones para futuras revisiones de la tarjeta.

La Controladora de Vuelo V2 fue diseñada como una plataforma modular para cohetería experimental, por lo que debe operar en un entorno con vibración, cambios de aceleración, ruido eléctrico, restricciones de espacio y posibles cargas críticas asociadas a eventos de misión.

!!! note "Alcance"
    Esta página no reemplaza el esquemático ni los archivos de fabricación. Su propósito es explicar criterios generales de diseño y servir como referencia para futuras modificaciones de hardware.

## Objetivos de diseño

Los objetivos principales considerados durante el diseño de la tarjeta fueron:

* Integrar sensores, almacenamiento, comunicación y salidas de misión en una sola PCB.
* Mantener una arquitectura compacta y adecuada para bahías de aviónica en cohetes experimentales.
* Permitir alimentación desde baterías comunes en proyectos de cohetería y aeromodelismo.
* Facilitar la conexión de periféricos externos mediante interfaces estándar.
* Separar funciones críticas, como eventos de misión, de funciones de comunicación o depuración.
* Permitir programación y depuración mediante herramientas accesibles como ST-Link.
* Mantener una base abierta y modificable para futuras revisiones.

## Arquitectura general de hardware

La tarjeta está organizada alrededor del microcontrolador **STM32F722RET6**, que actúa como unidad central de procesamiento. A partir de este dispositivo se conectan los principales bloques funcionales:

* Sistema de alimentación.
* Sensores inerciales y ambientales.
* Memoria flash externa.
* Comunicación USB.
* Comunicación CAN.
* Módulo LoRa.
* Entrada SBUS.
* Salidas PWM.
* Canales de eventos de misión.
* Interfaz de programación SWD.

Esta organización permite que cada bloque pueda documentarse, probarse y modificarse de forma relativamente independiente.

## Consideraciones de alimentación

El sistema de alimentación fue diseñado para aceptar una entrada principal `VCC` y generar los rieles internos necesarios para la tarjeta.

| Riel     | Uso principal                                         |
| -------- | ----------------------------------------------------- |
| `VCC`    | Entrada principal de alimentación.                    |
| `5V`     | Alimentación intermedia y conectores externos.        |
| `3V3`    | Microcontrolador, sensores, memoria y lógica digital. |
| `3V3_RF` | Alimentación dedicada para el módulo LoRa.            |

Separar el riel de radiofrecuencia `3V3_RF` del riel lógico principal ayuda a reducir la interacción directa entre el consumo variable del módulo LoRa y el resto de la lógica digital.

!!! warning "Capacidad de corriente"
    La corriente disponible en los rieles de alimentación debe validarse mediante pruebas. No se debe asumir que el riel de `5V` puede alimentar servos, radios o periféricos de alta corriente sin revisar el diseño térmico y la capacidad del regulador.

## Desacoplo y estabilidad eléctrica

Los circuitos integrados principales incluyen capacitores de desacoplo cercanos a sus pines de alimentación. Esto ayuda a reducir ruido local, transitorios y caídas momentáneas de voltaje.

Se recomienda mantener esta práctica en futuras revisiones:

* Colocar capacitores de desacoplo cerca de cada circuito integrado.
* Usar capacitores de mayor valor en entradas y salidas de reguladores.
* Separar, cuando sea posible, rieles de alta demanda de rieles sensibles.
* Mantener trayectorias de alimentación cortas y con suficiente ancho de pista.
* Evitar que corrientes de actuadores o cargas externas circulen por zonas sensibles de sensores.

## Consideraciones de sensores

La tarjeta integra sensores inerciales y ambientales para adquisición de datos y estimación del estado del vehículo.

Sensores principales:

* **MPU-6050** como IMU de 6 ejes.
* **ICM-42670-P** como IMU de 6 ejes.
* **BME280** como sensor ambiental de presión, temperatura y humedad.

Para mejorar la calidad de medición en futuras revisiones, se recomienda:

* Colocar los sensores inerciales cerca del centro geométrico de la tarjeta cuando sea posible.
* Evitar colocar sensores cerca de reguladores, inductores o fuentes de ruido.
* Reducir vibraciones mecánicas mediante una integración adecuada en la bahía de aviónica.
* Mantener referencias claras de orientación de ejes en la PCB y en la documentación.
* Documentar la orientación física de cada sensor respecto al sistema de coordenadas del vehículo.

!!! note "Orientación de sensores"
    La orientación física de los sensores debe documentarse explícitamente para evitar errores en algoritmos de estimación, reconstrucción de vuelo o control.

## Memoria externa

La memoria flash externa permite registrar datos de vuelo, eventos y mensajes del sistema. Este bloque es importante para análisis post-vuelo y validación experimental.

Consideraciones relevantes:

* Mantener las líneas SPI cortas y ordenadas.
* Evitar interferencia con señales de alta corriente.
* Usar resistencias o configuraciones adecuadas para señales de control como `CS`, `WP` y `RESET`.
* Documentar la capacidad de memoria y el formato de almacenamiento.
* Validar ciclos de escritura, borrado y lectura durante pruebas de banco.

## Comunicación USB

El puerto Micro USB permite comunicación local, configuración, descarga de datos o depuración, dependiendo del firmware.

El diseño incluye protección ESD para las líneas USB, lo cual es recomendable debido a la manipulación frecuente del conector.

Consideraciones:

* Mantener las líneas `USB_D+` y `USB_D-` como par diferencial.
* Evitar rutas largas o cercanas a fuentes de ruido.
* Mantener protección ESD cerca del conector.
* Revisar la interacción entre alimentación USB y alimentación principal externa.

!!! warning "Alimentación simultánea"
    Antes de conectar alimentación externa y USB al mismo tiempo, se debe revisar el esquemático de la revisión correspondiente para confirmar que no exista conflicto entre fuentes de alimentación.

## Comunicación CAN

La interfaz CAN está pensada para comunicación robusta con periféricos externos o módulos de expansión.

Consideraciones de diseño:

* Usar par trenzado para `CAN_H` y `CAN_L` en cableado externo.
* Mantener una tierra común entre dispositivos.
* Verificar la terminación del bus.
* Evitar topologías con derivaciones largas.
* Documentar velocidad de bus y protocolo utilizado por firmware.

La presencia de CAN permite que futuras versiones del proyecto puedan integrar módulos externos sin depender únicamente de UART, USB o conexiones punto a punto.

## Comunicación LoRa

El módulo LoRa permite telemetría y recepción de comandos, según el estado actual del firmware.

Consideraciones relevantes:

* Utilizar un riel dedicado `3V3_RF`.
* Mantener desacoplo adecuado cerca del módulo.
* Evitar colocar la antena cerca de planos, cables o estructuras que afecten la radiación.
* Considerar la ubicación física de la antena dentro del vehículo.
* Validar alcance, pérdida de paquetes y comportamiento durante vibración.

!!! note "Telemetría"
    La funcionalidad de telemetría depende del firmware y puede encontrarse en desarrollo. El hardware proporciona la base para implementar esta función, pero su comportamiento final debe validarse mediante pruebas.

## Entrada SBUS

La entrada SBUS utiliza una etapa de inversión de señal para adaptarse al microcontrolador. Esta interfaz permite recibir comandos desde receptores compatibles.

Consideraciones:

* Verificar niveles lógicos del receptor.
* Mantener tierra común entre receptor y tarjeta.
* Validar que la señal SBUS llegue invertida o no invertida según el circuito usado.
* Documentar el mapeo de canales en firmware.
* No depender de SBUS como único mecanismo de seguridad para salidas críticas.

## Salidas PWM

Las salidas PWM están destinadas a servos o actuadores compatibles.

Consideraciones:

* Verificar corriente requerida por cada servo.
* Evitar alimentar servos de alta corriente desde la tarjeta sin validación.
* Usar alimentación externa si el consumo supera la capacidad del riel de `5V`.
* Mantener cables de servos cortos o adecuadamente asegurados.
* Revisar posibles caídas de voltaje durante movimiento o bloqueo mecánico.

!!! warning "Servos y reinicios"
    Los servos pueden generar picos de corriente capaces de provocar caídas de voltaje. Si el microcontrolador se reinicia al mover servos, se debe revisar la alimentación, el cableado y la separación entre potencia y lógica.

## Canales de eventos de misión

La tarjeta incluye dos canales independientes para eventos de misión. Estos canales están implementados mediante relevadores de estado sólido y se complementan con interruptores físicos de armado.

Consideraciones de diseño:

* Mantener los canales críticos separados de señales de baja potencia.
* Incluir indicadores visuales de estado cuando sea posible.
* Usar interruptores físicos como barrera adicional de seguridad.
* Documentar claramente el estado seguro de cada canal.
* Garantizar que el firmware inicie con salidas críticas deshabilitadas.
* Validar cada canal con cargas no críticas antes de usarlo en una prueba real.

!!! danger "Funciones críticas"
    Los canales de eventos de misión pueden activar sistemas de recuperación, separación u otros mecanismos críticos. Cualquier modificación de hardware o firmware relacionada con estos canales debe revisarse y probarse bajo condiciones controladas.

## Programación y depuración

La tarjeta utiliza interfaz **SWD** para programación y depuración mediante ST-Link.

Consideraciones:

* Mantener accesibles las señales `SWDIO`, `SWCLK`, `GND` y referencia de voltaje.
* Evitar que el conector de depuración quede bloqueado durante integración.
* Mantener disponible la señal `NRST` si la revisión de hardware lo permite.
* Proteger mecánicamente el conector durante pruebas de vibración o transporte.

## Diseño mecánico

La geometría circular de la tarjeta facilita su integración en bahías de aviónica cilíndricas, comunes en cohetes experimentales.

Consideraciones mecánicas:

* Verificar diámetro disponible dentro del fuselaje.
* Considerar separación entre PCB, estructura y tornillería.
* Evitar contacto eléctrico con partes metálicas.
* Usar separadores adecuados.
* Asegurar conectores y cables contra vibración.
* Evitar que cables o conectores interfieran con sistemas de recuperación.
* Considerar acceso físico a interruptores de armado y puerto USB.

## Vibración y ambiente de operación

Los cohetes experimentales pueden exponer la electrónica a vibración, aceleración, golpes y cambios de presión.

Recomendaciones:

* Asegurar firmemente la PCB dentro de la bahía de aviónica.
* Usar conectores con retención mecánica cuando sea posible.
* Evitar cables largos sin sujeción.
* Proteger componentes altos o delicados.
* Realizar pruebas de continuidad después de manipulación e integración.
* Validar el comportamiento de sensores durante pruebas de vibración o movimiento.

## Separación entre potencia, lógica y señales críticas

Para mejorar confiabilidad y reducir interferencia, se recomienda mantener una separación funcional entre:

| Grupo            | Ejemplos                                                  |
| ---------------- | --------------------------------------------------------- |
| Potencia         | `VCC`, `5V`, alimentación de servos, alimentación externa |
| Lógica           | `3V3`, MCU, sensores, memoria                             |
| Comunicación     | USB, CAN, LoRa, SBUS, GPS                                 |
| Eventos críticos | `PYRO1`, `PYRO2`, interruptores de armado                 |

En futuras revisiones, esta separación debe reflejarse tanto en el esquemático como en el diseño PCB.

## Manufactura y ensamble

Para facilitar la fabricación y revisión del hardware, se recomienda:

* Mantener una lista de materiales actualizada.
* Documentar el número de capas de la PCB.
* Incluir archivos Gerber y taladros.
* Publicar esquemático y diseño PCB.
* Documentar orientación de componentes.
* Incluir referencias visibles en la serigrafía.
* Revisar disponibilidad de componentes antes de fabricar.
* Validar huellas de componentes críticos.
* Documentar cambios entre revisiones.

## Validación recomendada

Antes de considerar una revisión de hardware como estable, se recomienda realizar pruebas en etapas:

1. Inspección visual.
2. Prueba de continuidad.
3. Primer encendido con fuente limitada en corriente.
4. Verificación de rieles de alimentación.
5. Programación del microcontrolador.
6. Prueba de sensores internos.
7. Prueba de memoria externa.
8. Prueba de USB.
9. Prueba de CAN.
10. Prueba de LoRa.
11. Prueba de SBUS.
12. Prueba de PWM sin carga.
13. Prueba de PWM con carga controlada.
14. Prueba de canales de eventos con cargas no críticas.
15. Prueba de integración completa en banco.

## Limitaciones conocidas

Las siguientes características deben validarse con pruebas o documentación adicional:

* Corriente máxima real disponible en el riel de `5V`.
* Corriente máxima para servos y periféricos externos.
* Compatibilidad entre alimentación USB y alimentación externa.
* Comportamiento térmico del regulador step-down.
* Comportamiento térmico del regulador lineal de 3.3 V.
* Alcance real y estabilidad del módulo LoRa.
* Robustez de conectores ante vibración.
* Repetibilidad de lectura de sensores durante pruebas dinámicas.
* Capacidad de los canales de eventos bajo distintas cargas.

## Recomendaciones para futuras revisiones

Para futuras versiones de hardware se recomienda evaluar:

* Protección contra inversión de polaridad.
* Medición de voltaje de batería.
* Medición de corriente del sistema.
* Supervisión de rieles de alimentación.
* Protección adicional para salidas críticas.
* Conectores con bloqueo mecánico.
* Separación física mayor entre RF, potencia y sensores.
* Puntos de prueba para `VCC`, `5V`, `3V3` y `3V3_RF`.
* Compatibilidad con telemetría modular o antena externa.
* Buzzer integrado

## Páginas relacionadas

* [Introducción al hardware](Hardware.md)
* [Especificaciones técnicas](especificaciones.md)
* [Alimentación](alimentacion.md)
* [Conectores y pinout](conectores-pinout.md)
* [Archivos de fabricación](archivos-fabricacion.md)
