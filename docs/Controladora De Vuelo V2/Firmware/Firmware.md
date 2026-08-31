# Introducción

El firmware de la Controladora de Vuelo V2 es el software embebido encargado de inicializar la tarjeta, administrar los periféricos, adquirir datos de sensores, registrar información de vuelo, procesar comandos, controlar salidas y ejecutar eventos asociados a la misión. La documentación de firmware describe la arquitectura propuesta y debe validarse contra los archivos fuente disponibles en la copia local del repositorio.

Esta sección documenta la arquitectura general del firmware, su estructura de módulos, el flujo de ejecución, los drivers implementados, el manejo de errores y los procedimientos necesarios para compilar y cargar el programa en la tarjeta.

## 1. Objetivos del firmware

El objetivo del firmware es cumplir de forma segura y eficiente con el [concepto de operaciones](conops.md), buscando definir todas las fases operativas, los agentes que conforman el sistema, las acciones esperadas y cómo deben realizarlas para lograr que todas las directivas de diseño y requerimientos se cumplan satisfactoriamente, garantizando una operación confiable y segura del sistema, así como sistemas de falla predecibles y que reduzcan los riesgos operativos.

## 2. Estructura general

El firmware se organiza en módulos independientes para facilitar su mantenimiento y expansión. Cada módulo cumple una función específica dentro del sistema, como adquisición de sensores, almacenamiento, comunicación, control de salidas o administración de estados y debe estar asociado a un requerimiento. En caso de expandir la funcionalidad de la tarjeta, deberá justificarse y documentarse en el [concepto de operaciones](conops.md), además de crear los requerimientos técnicos asociados, esto para garantizar la seguridad operacional.

## 3. Primeros pasos

Si es tu primera vez desarrollando firmware para TheRocketProject o en STM32CubeIDE te recomendamos seguir el siguiente documento donde se explica a detalle el procedimiento para cargar firmware en la tarjeta y crear una función para entender cómo se desarrolla el firmware y cómo se gestiona dentro del microcontrolador:

[Primeros pasos](primeros-pasos.md)

## 4. Páginas relacionadas

- [Primeros pasos](primeros-pasos.md)
- [Configurar entorno de desarrollo](entorno-desarrollo.md)
- [Arquitectura del firmware](arquitectura.md)
- [Mensajes en Blackbox](Blackbox.md)
- [Telemetría y comandos](telemetria-comandos.md)

