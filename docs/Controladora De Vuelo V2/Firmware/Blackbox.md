# Blackbox

La blackbox es el registro local de eventos, estados y datos de misión. Su objetivo es permitir el análisis posterior al vuelo incluso cuando no exista telemetría en tiempo real.

!!! warning "Estado de implementación"
    Esta página describe el comportamiento esperado. El formato definitivo de paquetes debe confirmarse contra el firmware implementado.

## Datos mínimos

| Dato | Descripción |
| --- | --- |
| Timestamp | Tiempo relativo del evento o muestra. |
| Estado de misión | Estado actual de la máquina de estados. |
| Evento | Transiciones, fallas, armado, recuperación o aterrizaje. |
| Sensores | Lecturas seleccionadas de IMU y barómetro. |
| Salidas | Estado de actuadores y canales de recuperación. |
| Configuración | Versión y parámetros usados durante la misión. |

## Eventos recomendados

* `SYSTEM_BOOT`
* `SELF_TEST_PASS`
* `SELF_TEST_FAIL`
* `CONFIG_LOADED`
* `ARMED`
* `DISARMED`
* `LAUNCH_DETECTED`
* `BOOST_END`
* `APOGEE_DETECTED`
* `RECOVERY_OUTPUT_ACTIVATED`
* `RECOVERY_OUTPUT_FINISHED`
* `LANDING_DETECTED`
* `FAULT_DETECTED`
* `SYSTEM_RESET`

## Reglas de operación

* `BlackboxTask` no debe escribir directamente en memoria; debe enviar paquetes a `Write_Queue`.
* `MemoryTask` debe encapsular el acceso físico a memoria externa.
* La escritura de logs no debe bloquear tareas críticas.
* Si la memoria falla, la misión debe continuar y la falla debe registrarse si existe un medio disponible.

## Pendientes

* Definir estructura de paquete.
* Definir tamaño máximo de log.
* Definir método de descarga post-vuelo.
* Definir política de borrado y protección contra sobrescritura.
