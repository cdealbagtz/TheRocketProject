# Introducción

El firmware de la Controladora de Vuelo V2 es el software embebido encargado de inicializar la tarjeta, administrar los periféricos, adquirir datos de sensores, registrar información de vuelo, procesar comandos, controlar salidas y ejecutar eventos asociados a la misión. El firmware del proyecto se puede encontrar en [GitHub](https://github.com/cdealbagtz/TheRocketProject/).

Esta sección documenta la arquitectura general del firmware, su estructura de módulos, el flujo de ejecución, los drivers implementados, el manejo de errores y los procedimientos necesarios para compilar y cargar el programa en la tarjeta.

## Objetivos del firmware

- Inicializar los periféricos principales de la tarjeta.
- Adquirir datos de sensores inerciales y ambientales.
- Registrar datos de vuelo en memoria externa.
- Administrar la comunicación por USB, UART, CAN o LoRa.
- Ejecutar eventos de misión de forma controlada.
- Proporcionar una base extensible para futuras funciones de control y telemetría.

## Estructura general

El firmware se organiza en módulos independientes para facilitar su mantenimiento y expansión. Cada módulo cumple una función específica dentro del sistema, como adquisición de sensores, almacenamiento, comunicación, control de salidas o administración de estados.

## Páginas relacionadas

- [Arquitectura del firmware](arquitectura.md)
- [Mensajes en Blackbox](Blackbox.md)
- [Telemetría y comandos](telemetria-comandos.md)
- [Compilación y carga](compilacion-carga.md)