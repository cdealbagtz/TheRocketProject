# Introducción

La Controladora de Vuelo V2 integra los subsistemas electrónicos necesarios para adquisición de datos, comunicación, almacenamiento, control de actuadores y ejecución de eventos de misión en proyectos de cohetería experimental.

Esta sección documenta la arquitectura física de la tarjeta, sus especificaciones eléctricas, conectores, interfaces de comunicación, sensores integrados, sistema de alimentación y consideraciones de integración.

## Objetivos del hardware

- Proporcionar una plataforma electrónica compacta y modular.
- Centralizar sensores, comunicación, almacenamiento y salidas de misión.
- Facilitar la integración con cohetes experimentales y bancos de prueba.
- Permitir expansión mediante interfaces estándar.
- Servir como base para futuras revisiones de hardware dentro de TheRocketProject.

## Bloques principales

La tarjeta puede dividirse en los siguientes bloques funcionales:

- Microcontrolador principal.
- Sistema de alimentación.
- Sensores integrados.
- Memoria externa.
- Comunicación USB, UART, CAN y LoRa.
- Entrada SBUS.
- Salidas PWM.
- Salidas para eventos de misión.
- Interfaz de programación y depuración.

## Páginas relacionadas

* [Consideraciones de diseño](consideraciones-diseno.md)
* [Especificaciones técnicas](especificaciones.md)
* [Alimentación](alimentacion.md)
* [Conectores y pinout](conectores-pinout.md)
* [Archivos de fabricación](archivos-fabricacion.md)
