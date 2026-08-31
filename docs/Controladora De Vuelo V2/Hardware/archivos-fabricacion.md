# Archivos de fabricación

Esta sección contiene los archivos necesarios para revisar, fabricar o modificar la **Controladora de Vuelo V2**. El objetivo es centralizar los recursos de hardware del proyecto para que otros usuarios puedan consultar el diseño, proponer mejoras, verificar conexiones o fabricar sus propias versiones de la tarjeta.

La Controladora de Vuelo V2 fue diseñada como parte de TheRocketProject bajo una filosofía de hardware abierto. Por ello, los archivos de fabricación estarán disponibles públicamente para facilitar la revisión, reproducción y mejora del diseño.

## Proyecto en OSHWLab

El diseño de hardware será publicado en **OSHWLab**, donde se podrán consultar los esquemáticos, PCB, componentes y archivos relacionados con la fabricación de la tarjeta.

[Enlace al proyecto y archivos de fabricación](https://oshwlab.com/cdealba/rocket-stack-project_2)

## Recomendaciones antes de fabricar

Antes de fabricar la tarjeta, se recomienda revisar cuidadosamente:

* Versión del hardware.
* Esquemático eléctrico.
* Pinout de conectores.
* Rango de alimentación.
* Orientación de componentes.
* Componentes críticos o difíciles de conseguir.
* Reglas de diseño del fabricante.
* Espesor y número de capas de la PCB.
* Tolerancias mecánicas.
* Separación entre pistas de potencia y señales sensibles.

!!! warning "Revisión previa"
    No se recomienda fabricar la tarjeta sin revisar previamente los archivos de diseño, la lista de materiales y las notas de la versión correspondiente. El proyecto aún se encuentra en desarrollo y pueden existir cambios entre revisiones.

En el siguiente enlace hay un tutorial de como se puede generar los archivos de fabricación y solicitar su manufactura:

[Ordenar una tarjeta de proyectos de OSHWLab](https://blog.rambros3d.com/ordering-boards-for-oshwlab-projects).

## Versiones de hardware

Cada versión de hardware debe documentarse de forma independiente para mantener trazabilidad entre cambios de diseño, fabricación y pruebas.

| Versión | Estado           | Descripción                                             |
| ------- | ---------------- | ------------------------------------------------------- |
| V2.0    | En documentación | Primera versión pública de la Controladora de Vuelo V2. |

## Reporte de errores de hardware

Si encuentras un error en el esquemático, PCB, lista de materiales o documentación de hardware, puedes reportarlo mediante un issue en GitHub.

Al reportar un problema de hardware, incluye preferentemente:

* Versión de la tarjeta.
* Descripción del problema.
* Componente o bloque afectado.
* Evidencia del error.
* Propuesta de corrección, si aplica.
* Capturas del esquemático o PCB, si son necesarias.

## Páginas relacionadas

* [Introducción al hardware](Hardware.md)
* [Especificaciones técnicas](especificaciones.md)
* [Conectores y pinout](conectores-pinout.md)
