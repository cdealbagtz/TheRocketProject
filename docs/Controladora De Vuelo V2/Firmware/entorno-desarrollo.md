# Configurando el entorno de desarrollo

Para comenzar a trabajar en el firmware de la **Controladora de Vuelo V2** es necesario configurar un entorno de desarrollo que permita editar, compilar, cargar y documentar el proyecto correctamente.

El firmware fue desarrollado utilizando **STM32CubeIDE V2.1.1**. Este entorno de desarrollo de STMicroelectronics permite reducir la carga de configuración del desarrollador mediante herramientas de generación de código, administración de periféricos, configuración de GPIO, buses de comunicación, temporizadores e interrupciones.

En esta versión del flujo de trabajo también se utiliza **STM32CubeMX V6.17.0** para la configuración gráfica del microcontrolador y la generación de código base. A diferencia de versiones anteriores, donde la configuración de CubeMX podía encontrarse integrada directamente dentro del IDE, en este flujo se considera CubeMX como una herramienta independiente dentro del proceso de desarrollo.

Además del entorno de ST, será necesario instalar **Git**, **Python**, **PIP** y **MkDocs Material**. Estas herramientas permiten clonar el repositorio, administrar versiones del proyecto, editar la documentación y ejecutar un servidor local para visualizar los cambios antes de publicarlos.

También se recomienda instalar **Visual Studio Code** para editar la documentación y revisar archivos auxiliares del proyecto. Sin embargo, la documentación puede modificarse con cualquier otro IDE o editor de texto.

## Software requerido

La siguiente tabla muestra las herramientas utilizadas para el desarrollo del firmware y la documentación del proyecto.

| Herramienta                                                               | Versión utilizada | Propósito                                                               |
| ------------------------------------------------------------------------- | ----------------: | ----------------------------------------------------------------------- |
| [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) |            V2.1.1 | Desarrollo, compilación y depuración del firmware.                      |
| [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html)   |           V6.17.0 | Configuración gráfica del microcontrolador y generación de código base. |
| [Python](https://www.python.org/downloads/)                               |           V3.14.6 | Ejecución de herramientas auxiliares y entorno de documentación.        |
| [Git](https://git-scm.com/)                                               |           V2.54.0 | Control de versiones y descarga del repositorio.                        |
| [Visual Studio Code](https://code.visualstudio.com/)                      |          V1.124.0 | Edición de documentación, scripts y archivos auxiliares.                |
| [PIP](https://pip.pypa.io/en/stable/installation/)                        |             V25.3 | Instalación de paquetes de Python.                                      |
| [MkDocs Material](https://squidfunk.github.io/mkdocs-material/)           | Según instalación | Generación del sitio de documentación.                                  |

!!! note "Versiones del proyecto"
    Las versiones indicadas corresponden al entorno utilizado durante el desarrollo inicial de la Controladora de Vuelo V2. Es posible utilizar versiones más recientes, pero se recomienda verificar compatibilidad si aparecen errores de compilación, generación de código o configuración de periféricos.

## Instalación de dependencias

### Git

Git es necesario para clonar el repositorio, crear ramas de trabajo, registrar cambios y enviar contribuciones al proyecto.

Después de instalar Git, verifica la instalación desde una terminal:

```bash
git --version
```

### Python y PIP

Python y PIP son necesarios para instalar MkDocs Material y ejecutar el servidor local de documentación.

Verifica que Python esté instalado correctamente:

=== "Windows"
    ```powershell
    python --version
    ```
=== "Linux"
    ```bash
    python3 --version
    ```
=== "macOS"
    ```bash
    python3 --version
    ```


Verifica que PIP esté disponible:

=== "Windows"
    ```powershell
    pip --version
    ```

=== "Linux"
    ```bash
    pip3 --version
    ```

=== "macOS"
    ```bash
    pip3 --version
    ```


Si PIP no está instalado, puede instalarse o actualizarse con:

=== "Windows"
    ```powershell
    python -m ensurepip --upgrade
    ```
=== "Linux"
    ```bash
    python3 -m ensurepip --upgrade
    ```

=== "macOS"
    ```bash
    python3 -m ensurepip --upgrade
    ```


## Instalación de MkDocs Material

MkDocs Material se utiliza para construir y visualizar la documentación del proyecto.

Instala MkDocs Material con PIP:

=== "Windows"

    ```powershell
    pip install mkdocs-material
    ```

=== "Linux"

    ```bash
    pip3 install mkdocs-material
    ```

=== "macOS"

    ```bash
    pip3 install mkdocs-material
    ```

Para verificar la instalación:

```bash
mkdocs --version
```

## Documentación de referencia

Aunque no forma parte de la documentación oficial de MkDocs Material, el siguiente tutorial explica de forma práctica cómo instalar MkDocs, crear un entorno de pruebas y realizar configuraciones básicas:

* [Tutorial de MkDocs Material](https://jameswillett.dev/getting-started-with-material-for-mkdocs/#mkdocs-vs-material-for-mkdocs)

También se recomienda consultar la documentación oficial:

* [Documentación oficial de MkDocs Material](https://squidfunk.github.io/mkdocs-material/)

## Clonar el repositorio

Una vez instaladas las herramientas necesarias, clona el repositorio del proyecto:

```bash
git clone https://github.com/cdealbagtz/TheRocketProject.git
```

Después entra a la carpeta del proyecto:

```bash
cd TheRocketProject
```

## Ejecutar la documentación en local

Para visualizar la documentación localmente, ejecuta para generar una maquina virtual con `venv`:

=== "Windows"

    ```powershell
    .\venv\Scripts\activate
    ```
=== "Linux"

    ```bash
    .\venv\Scripts\activate
    ```
=== "macOS"

    ```bash
    source venv/bin/activate
    ```

Una vez generada la maquina virtual, abre Visual Studio Code con:

```bash
code .
```

Y escribe el siguiente comando en la terminal:

```bash
mkdocs serve
```

Esto levantará un servidor local y lo actualizará cada que haya un cambio. Normalmente la documentación estará disponible en:

```text
http://127.0.0.1:8000/
```

Para construir la documentación y revisar posibles errores:

```bash
mkdocs build --strict
```

!!! tip "Revisión antes de publicar"
    Se recomienda ejecutar `mkdocs build --strict` antes de enviar cambios al repositorio. Esto ayuda a detectar enlaces rotos, imágenes faltantes o errores en la estructura de navegación.

## Abrir el proyecto en STM32CubeIDE

Para abrir el firmware en STM32CubeIDE:

1. Abre **STM32CubeIDE**.
2. Selecciona o crea un workspace.
3. Ve a:

```text
File → Import
```

4. Selecciona:

```text
General → Existing Projects into Workspace
```

5. En `Select root directory`, selecciona la carpeta donde se encuentra el firmware.
6. Verifica que el proyecto aparezca en la lista.
7. Haz clic en `Finish`.

Una vez importado, el proyecto aparecerá en el explorador de proyectos de STM32CubeIDE.

## Abrir la configuración en STM32CubeMX

Si necesitas revisar o modificar la configuración de periféricos, abre el archivo `.ioc` correspondiente desde STM32CubeMX.

!!! info "Nota"
    A menos que haya un cambio en el hardware o se vaya a trabajar con perifericos, es poco común que se requiera reconfigurar el archivo de .ioc y generar código.

Desde este archivo se pueden configurar elementos como:

* Relojes del sistema.
* GPIO.
* UART.
* SPI.
* CAN.
* USB.
* Timers.
* DMA.
* Interrupciones.
* Configuración base del microcontrolador.

!!! warning "Regeneración de código"
    Al modificar la configuración en STM32CubeMX y regenerar código, verifica que no se sobrescriban secciones modificadas manualmente. Mantén el código de usuario dentro de los bloques `USER CODE BEGIN` y `USER CODE END` cuando aplique.

## Compilar el firmware

Para compilar el proyecto desde STM32CubeIDE:

1. Abre el proyecto en el explorador.
2. Selecciona el proyecto principal.
3. Haz clic derecho sobre el proyecto.
4. Selecciona:

```text
Build Project
```

También puedes usar el botón de compilación de la barra superior.

Si la compilación es exitosa, STM32CubeIDE generará los archivos de salida correspondientes dentro de la carpeta de compilación del proyecto.

## Cargar el firmware en la tarjeta

Para cargar el firmware en la Controladora de Vuelo V2 se utiliza una interfaz de programación **ST-Link** mediante el puerto de depuración correspondiente.

Procedimiento general:

1. Conecta el ST-Link a la computadora.
2. Conecta el ST-Link a la interfaz de programación de la tarjeta.
3. Alimenta la tarjeta según las recomendaciones de hardware.
4. Verifica que STM32CubeIDE detecte el programador.
5. Selecciona el proyecto.
6. Ejecuta:

```text
Run → Debug
```

o utiliza el botón de depuración del IDE.

!!! warning "Salidas críticas"
    Antes de cargar o probar firmware, asegúrate de que no haya sistemas de recuperación, cargas pirotécnicas, ignitores, actuadores críticos o mecanismos peligrosos conectados a la tarjeta. Las primeras pruebas deben realizarse únicamente en banco y con salidas críticas desconectadas.

## Verificación básica después de cargar el firmware

Después de programar la tarjeta, se recomienda realizar una verificación inicial:

* Confirmar que la tarjeta enciende correctamente.
* Verificar que no existan errores de alimentación.
* Revisar la salida de depuración, si está disponible.
* Confirmar la inicialización de sensores.
* Verificar la comunicación USB, UART, CAN o LoRa según corresponda.
* Revisar que el sistema permanezca en un estado seguro.
* Confirmar que las salidas críticas estén deshabilitadas por defecto.

## Problemas comunes

| Problema                             | Posible causa                                             | Solución recomendada                                              |
| ------------------------------------ | --------------------------------------------------------- | ----------------------------------------------------------------- |
| El proyecto no aparece al importarlo | Carpeta incorrecta o archivos del proyecto faltantes      | Verifica que estés seleccionando la carpeta raíz del firmware.    |
| Error al compilar                    | Dependencias, versión del IDE o configuración incompleta  | Limpia el proyecto y recompila. Verifica la versión del entorno.  |
| STM32CubeIDE no detecta el ST-Link   | Driver faltante, cable defectuoso o conexión incorrecta   | Reinstala drivers, cambia cable USB o revisa conexiones SWD.      |
| Error al generar código desde CubeMX | Versión incompatible o archivo `.ioc` dañado              | Verifica la versión de CubeMX y conserva una copia de seguridad.  |
| La documentación no compila          | Enlaces rotos, imágenes faltantes o error en `mkdocs.yml` | Ejecuta `mkdocs build --strict` y corrige los errores reportados. |

## Siguientes pasos:

Una vez configurado el entorno de desarrollo te recomendamos hacer la guia de [primeros pasos](primeros-pasos.md) para crear tu primer función y entender como se desarrolla en el entorno de trabajo. También se recomienda revisar el apartado de [¿Cómo contribuir?](../../Contribuir.md) para ver los "guidelines" de desarrollo, generar "ISUES" e interactuar con la comunidad.

## Páginas relacionadas

* [Arquitectura del firmware](arquitectura.md)
* [Mensajes en Blackbox](Blackbox.md)
* [Telemetría y comandos](telemetria-comandos.md)


```
```
