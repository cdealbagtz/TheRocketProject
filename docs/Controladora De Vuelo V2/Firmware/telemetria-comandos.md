# Telemetría y comandos

La telemetría y los comandos permiten monitorear la controladora y enviar solicitudes durante fases permitidas. La misión nominal no debe depender de telemetría para ejecutar lanzamiento, recuperación o registro local.

!!! warning "Estado WIP"
    La telemetría se considera una función en desarrollo. Las funciones críticas deben operar de forma autónoma aunque no exista enlace con estación de tierra.

## Canales previstos

| Canal | Uso previsto |
| --- | --- |
| USB | Configuración local, descarga de datos y diagnóstico en banco. |
| SBUS | Entrada de comandos simples desde receptor compatible. |
| LoRa | Telemetría y comandos remotos cuando esté implementado y validado. |
| CAN | Integración futura con módulos externos. |

## Política de comandos

| Estado | Comandos permitidos |
| --- | --- |
| `SAFE` | Lectura de estado y diagnóstico. |
| `STANDBY` | Configuración, armado si las condiciones son válidas, lectura y borrado de logs. |
| `ARMED` | Desarmado y lectura de estado restringida. |
| `BOOST` / `COAST` | Solo comandos de emergencia explícitamente permitidos. |
| `RECOVERY_DEPLOYED` / `DESCENT` | Lectura restringida y acciones de emergencia si están habilitadas. |
| `LANDED` | Descarga de datos y revisión post-vuelo. |
| `FAULT` | Lectura y limpieza controlada del registro de falla. |

## Reglas

* Todo comando externo debe tratarse como solicitud, no como acción directa.
* Los comandos críticos deben validarse contra el estado actual.
* La configuración crítica debe bloquearse durante vuelo.
* Las salidas de recuperación no deben activarse directamente desde una interfaz de comunicación.
* Todo comando rechazado debe generar un evento de diagnóstico.
