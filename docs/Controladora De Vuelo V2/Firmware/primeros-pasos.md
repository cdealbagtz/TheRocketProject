# Primeros pasos

Esta guía resume el flujo mínimo para trabajar con la documentación y preparar el entorno de firmware de la Controladora de Vuelo V2.

## 1. Clonar el repositorio

```bash
git clone https://github.com/cdealbagtz/TheRocketProject.git
cd TheRocketProject
```

## 2. Crear el entorno de documentación

```bash
python -m venv venv
venv\Scriptsctivate
pip install mkdocs-material
```

## 3. Ejecutar la documentación

```bash
mkdocs serve
```

Después abre:

```text
http://127.0.0.1:8000/
```

## 4. Revisar el firmware

Antes de compilar o cargar firmware, valida que tu copia local incluya los archivos fuente de aplicación, el archivo `.ioc` y la configuración de STM32CubeIDE. Si la carpeta `Firmware/` solo contiene una estructura parcial, trata la documentación de firmware como arquitectura propuesta hasta integrar los fuentes correspondientes.

## 5. Siguientes lecturas

* [Entorno de desarrollo](entorno-desarrollo.md)
* [Concepto de operaciones](conops.md)
* [Arquitectura del firmware](arquitectura.md)
* [Configuraciones](configuraciones.md)
