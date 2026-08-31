# Configuraciones

Esta página resume los parámetros de configuración previstos para la Controladora de Vuelo V2. La implementación final debe mantenerse alineada con el [concepto de operaciones](conops.md) y con la [arquitectura del firmware](arquitectura.md).

!!! warning "Estado de implementación"
    Esta sección documenta la configuración propuesta. Antes de usarla en vuelo, valida que el firmware cargado implemente estos parámetros y que los valores hayan sido probados en banco.

## Parámetros críticos

| Parámetro | Uso | Modificable en vuelo |
| --- | --- | --- |
| Umbral de lanzamiento | Detectar transición de `ARMED` a `BOOST`. | No |
| Criterio de MECO | Detectar fin de empuje y transición a `COAST`. | No |
| Criterio de apogeo | Determinar `APOGEE_DETECTED`. | No |
| Temporizador de respaldo | Activar recuperación si no se detecta apogeo. | No |
| Duración de pulso | Definir cuánto tiempo permanece activa la salida de recuperación. | No |
| Canal de recuperación | Seleccionar salida pirotécnica o actuador mecánico. | No |
| Frecuencia de logging | Ajustar tasa de registro por fase. | No durante vuelo |

## Reglas

* La configuración crítica solo debe modificarse en `STANDBY`.
* Toda configuración debe incluir versión y mecanismo de integridad, como CRC.
* Si la configuración es inválida, el sistema no debe permitir armado.
* Los valores usados en una misión deben quedar registrados en la blackbox.

## Flujo recomendado

1. Encender la controladora en condición segura.
2. Ejecutar autodiagnóstico.
3. Cargar o revisar configuración en `STANDBY`.
4. Validar rangos y CRC.
5. Armar únicamente si la configuración es válida.

## Pendientes de definición

* Formato binario o textual de almacenamiento.
* Valores por defecto de cada parámetro.
* Comandos exactos para lectura, escritura y borrado.
* Política de compatibilidad entre versiones de configuración.
