# Simulador de Misiones Artemis – Orion en órbita LEO

## 1. Información del proyecto

**Universidad:** Universidad Tecnológica Nacional (UTN)  
**Facultad:** Facultad Regional Resistencia  
**Carrera:** Ingeniería en Sistemas de Información  
**Asignatura:** Algoritmos y Estructuras de Datos  
**Trabajo:** Trabajo Práctico Integrador Final  
**Lenguaje:** C  
**Escenario asignado:** Situación problemática 2 – Inserción y Estabilidad en Órbita Terrestre Baja (LEO)  
**Comisión:** ISI C

### Integrantes

- González Leyes, Thiago Iván
- González Leyes, Octavio Ariel
- Ferreyra Robles, Juan Manuel
- González, Nayla Aylén
- Noriega, Benjamín

---

## 2. Descripción del proyecto

El proyecto consiste en desarrollar un simulador por consola de una misión de la nave espacial Orion, perteneciente al programa Artemis de la NASA.

El sistema representa la etapa de inserción y estabilidad de la nave en una órbita terrestre baja (LEO), donde realiza un Movimiento Circular Uniforme (MCU) bajo la influencia de la fuerza gravitatoria terrestre.

El objetivo es aplicar los conceptos físicos de movimiento circular y gravitación universal mediante un programa desarrollado en lenguaje C, que permita modificar parámetros, realizar cálculos, simular una perturbación en la trayectoria orbital y consultar los resultados obtenidos.

El programa cuenta con una interfaz interactiva basada en un menú principal, validaciones de entrada, estructuras de datos para representar el estado de la misión y un historial de resultados.

## 3. Escenario asignado: Inserción y Estabilidad en Órbita LEO

### Situación planteada

Luego de apagar sus motores de ascenso, la nave Orion es inyectada en una órbita terrestre baja (LEO), a una altitud constante de 192 km sobre la superficie terrestre.

En esta órbita, la nave realiza un Movimiento Circular Uniforme. La fuerza de atracción gravitatoria ejercida por la Tierra proporciona la fuerza centrípeta necesaria para mantener su trayectoria circular.

Durante la misión se analizan las magnitudes físicas del movimiento orbital y el efecto que produce el encendido de un propulsor auxiliar lateral.

### Parámetros iniciales del escenario

| Parámetro | Valor inicial |
|---|---:|
| Masa de la Tierra (MT) | 5,972 × 10²⁴ kg |
| Radio terrestre (RT) | 6.371.000 m |
| Altitud orbital (h) | 192.000 m |
| Radio orbital (r) | 6.563.000 m |
| Constante gravitacional (G) | 6,674 × 10⁻¹¹ N·m²/kg² |
| Masa de Orion (m) | 33.000 kg |
| Aceleración lateral (a) | 0,50 m/s² |
| Duración del pulso (Δt) | 10 s |

El radio orbital se obtiene sumando el radio terrestre y la altitud de la nave.

### Objetivos de la simulación

El programa contempla los cuatro problemas físicos planteados por la consigna:

**1. Velocidad orbital y fuerzas**

Demostrar que la fuerza gravitatoria actúa como fuerza centrípeta del sistema y calcular la velocidad orbital necesaria para mantener la órbita circular.

**2. Período orbital**

Determinar cuánto tiempo tarda Orion en completar una vuelta alrededor de la Tierra, expresando el resultado en segundos y minutos.

**3. Aceleración centrípeta**

Calcular el módulo de la aceleración centrípeta que experimentan los astronautas dentro de la cápsula a la altitud establecida.

**4. Perturbación por propulsor lateral**

Simular el encendido de un propulsor auxiliar que genera una aceleración constante de 0,50 m/s², perpendicular a la velocidad orbital, durante 10 segundos.

Se calcula la velocidad lateral adquirida y la desviación lateral instantánea, además de describir cómo se modifica la trayectoria de la nave.

## 4. Funcionamiento del programa

El simulador presenta un menú principal desde el cual el usuario puede seleccionar las operaciones disponibles.

| Opción | Funcionalidad |
|---|---|
| 1 | Configurar parámetros de la misión. |
| 2 | Calcular velocidad orbital y fuerzas. |
| 3 | Calcular período orbital. |
| 4 | Calcular aceleración centrípeta. |
| 5 | Simular pulso del propulsor lateral. |
| 6 | Ejecutar simulación completa. |
| 7 | Consultar reporte e historial. |
| 8 | Restaurar valores originales del escenario. |
| 0 | Salir del programa. |

### Descripción de las funcionalidades

- **Configuración:** permite modificar los parámetros físicos utilizados en los cálculos, respetando las validaciones y rangos establecidos.
- **Velocidad orbital y fuerzas:** calcula la velocidad orbital, la fuerza gravitatoria y la fuerza centrípeta. También presenta el desarrollo analítico que demuestra la relación entre ambas fuerzas.
- **Período orbital:** calcula el tiempo necesario para completar una vuelta alrededor de la Tierra.
- **Aceleración centrípeta:** determina la aceleración que experimenta la nave debido a su movimiento circular.
- **Propulsor lateral:** calcula la velocidad lateral adquirida y la desviación producida durante el pulso.
- **Simulación completa:** ejecuta los cálculos principales y presenta un resumen de los resultados.
- **Reporte e historial:** muestra los parámetros actuales, los últimos resultados obtenidos y los registros de cálculos realizados.
- **Restauración:** permite recuperar los parámetros originales del escenario.

El historial almacena los resultados durante la ejecución del programa, con una capacidad máxima de 100 registros. Los datos se mantienen en memoria y no se conservan al finalizar la ejecución.

## 5. Modelos físicos y fórmulas utilizadas

El simulador utiliza las siguientes expresiones matemáticas:

### Radio orbital

r = RT + h

### Fuerza gravitatoria

Fg = (G · MT · m) / r²

### Fuerza centrípeta

Fc = m · v² / r

Como la fuerza gravitatoria proporciona la fuerza centrípeta:

Fg = Fc

Al igualar ambas expresiones y simplificar la masa de la nave se obtiene:

### Velocidad orbital

v = √(G · MT / r)

La masa de Orion se cancela durante la deducción, por lo que la velocidad orbital no depende de la masa de la nave en este modelo.

### Período orbital

T = (2 · π · r) / v

### Aceleración centrípeta

ac = v² / r

### Velocidad lateral adquirida

vlateral = a · Δt

### Desviación lateral

d = ½ · a · (Δt)²

Donde:

- G: constante de gravitación universal.
- MT: masa de la Tierra.
- m: masa de la nave Orion.
- RT: radio terrestre.
- h: altitud orbital.
- r: radio orbital.
- v: velocidad orbital.
- T: período orbital.
- ac: aceleración centrípeta.
- a: aceleración lateral.
- Δt: duración del pulso.
- d: desviación lateral.

### Consideraciones del modelo

La simulación del propulsor lateral considera una aceleración constante y perpendicular a la velocidad orbital inicial.

La desviación calculada representa el desplazamiento lateral instantáneo durante el pulso. No se modela la evolución orbital posterior ni las perturbaciones reales que podrían afectar a la trayectoria.

## 6. Arquitectura y organización del código

El proyecto está desarrollado mediante una estructura modular, separando las responsabilidades del programa en archivos fuente y archivos de cabecera.

### Estructura de directorios

```text
project_c_esc_2/
│
├── include/
│   ├── estructuras.h
│   ├── simulador.h
│   └── validaciones.h
│
├── src/
│   ├── main.c
│   ├── simulador.c
│   └── validaciones.c
│
├── Makefile
├── .gitignore
└── README.md
```

### Descripción de los módulos

| Archivo | Responsabilidad |
|---|---|
| `main.c` | Contiene la función principal, el menú y el flujo general del programa. |
| `simulador.c` | Implementa los cálculos físicos, la simulación y la gestión de resultados. |
| `simulador.h` | Declara las funciones y definiciones correspondientes al módulo del simulador. |
| `estructuras.h` | Define las estructuras de datos utilizadas para representar los parámetros y el estado de la misión. |
| `validaciones.c` | Implementa las funciones de validación y lectura segura de datos ingresados por el usuario. |
| `validaciones.h` | Declara las funciones de validación utilizadas por el programa. |

Esta organización permite mantener separadas la interfaz, la lógica de simulación y las validaciones, facilitando el mantenimiento y la comprensión del código.

## 7. Validaciones y manejo de errores

El programa incorpora mecanismos de validación para controlar los datos ingresados por el usuario y evitar comportamientos inesperados.

Entre las validaciones implementadas se encuentran:

- Control del tipo de dato ingresado.
- Verificación de rangos permitidos para las opciones del menú.
- Validación de los parámetros físicos de la misión.
- Rechazo de entradas que no correspondan al formato solicitado.
- Control de errores durante la lectura de datos.

Por ejemplo, si el usuario ingresa texto en un campo que requiere un número entero, el programa informa que la entrada es inválida y solicita nuevamente el dato.

De la misma manera, si se selecciona una opción fuera del rango permitido, se muestra un mensaje de advertencia y se vuelve a solicitar la opción.

## 8. Tecnologías y herramientas utilizadas

- **Lenguaje de programación:** C.
- **Compilador:** GCC.
- **Estándar del lenguaje:** C11.
- **Herramienta de compilación:** GNU Make.
- **Biblioteca matemática:** `math.h`.
- **Control de versiones:** Git.
- **Repositorio remoto:** GitHub.
- **Entorno de desarrollo en Windows:** MSYS2 UCRT64.

## 9. Requisitos e instalación

Para compilar y ejecutar el proyecto se requiere:

- GCC.
- GNU Make.
- Una terminal compatible con las herramientas anteriores.

### Instalación en Windows mediante MSYS2

1. Descargar e instalar MSYS2 desde su sitio oficial:

   https://www.msys2.org/

2. Abrir la terminal **MSYS2 UCRT64**.

3. Actualizar los paquetes:

```bash
pacman -Syu
```

4. Si la terminal solicita cerrarse, volver a abrir MSYS2 UCRT64 y ejecutar:

```bash
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-gcc
```

Esto instala las herramientas necesarias para compilar el proyecto, incluyendo GCC y GNU Make.

## 10. Compilación y ejecución

### Clonar el repositorio

```bash
git clone https://github.com/juanmarobles/project_c_esc_2.git
```

### Ingresar al directorio

```bash
cd project_c_esc_2
```

### Compilar

Desde la raíz del proyecto, ejecutar:

```bash
make
```

El `Makefile` automatiza la compilación de los módulos fuente, la generación de archivos objeto y el enlazado del ejecutable.

Si la compilación finaliza correctamente, se genera el archivo:

```text
artemis_leo.exe
```

### Ejecutar

```bash
./artemis_leo.exe
```

### Limpiar archivos generados

Para eliminar los archivos objeto y el ejecutable:

```bash
make clean
```

Esto permite realizar una nueva compilación desde cero.

## 11. Pruebas realizadas

Durante las pruebas del programa se verificaron las siguientes funcionalidades:

- Compilación de todos los módulos mediante GCC y GNU Make, sin errores ni advertencias.
- Ejecución del menú principal y navegación entre sus opciones.
- Rechazo de entradas de texto cuando se espera un número entero.
- Rechazo de opciones fuera del rango permitido.
- Cálculo de velocidad orbital y fuerzas gravitatoria y centrípeta.
- Cálculo del período orbital.
- Simulación del pulso del propulsor lateral.
- Registro de resultados en el historial.
- Consulta del reporte de misión.

También se comprobó que el historial registra correctamente los resultados obtenidos durante una misma ejecución.

## 12. Uso de herramientas de Inteligencia Artificial

Durante el desarrollo del proyecto se utilizó **ChatGPT** como herramienta de apoyo para el aprendizaje, la resolución de dudas técnicas, la depuración y la documentación.

La utilización de IA no reemplazó el trabajo de programación ni la comprensión del código por parte de los integrantes.

### Herramienta utilizada

- ChatGPT (OpenAI).

### Tareas en las que se utilizó

- Consultas sobre compilación de proyectos en C mediante GCC y GNU Make.
- Asistencia para comprender y configurar el archivo `Makefile`.
- Análisis de la organización modular del proyecto y de los archivos fuente y de cabecera.
- Asistencia en la revisión de validaciones de entrada y manejo de errores.
- Orientación para diseñar y ejecutar pruebas funcionales.
- Ayuda para interpretar los resultados de las pruebas y detectar posibles inconsistencias.
- Asistencia en la elaboración y organización de la documentación del proyecto.

### Ejemplos de consultas realizadas

- ¿Cómo compilar el proyecto en C utilizando GCC y Make?
- ¿Qué herramientas deben instalarse para compilar desde MSYS2 UCRT64?
- ¿Cómo organizar un Makefile para compilar archivos ubicados en directorios separados?
- ¿Cómo validar entradas incorrectas y evitar que el programa se cierre ante errores del usuario?
- ¿Cómo comprobar que los cálculos realizados se almacenen correctamente en el historial?
- ¿Cómo documentar la estructura, las funcionalidades y las instrucciones de compilación del proyecto?

Estas consultas representan ejemplos de las tareas de asistencia realizadas durante el desarrollo.

### Validación y adaptación de las sugerencias

Las sugerencias proporcionadas por ChatGPT fueron revisadas y adaptadas al código y a la estructura real del proyecto.

Para comprobar su funcionamiento se realizaron pruebas prácticas:

- Se compiló el proyecto desde la terminal MSYS2 UCRT64 utilizando `make clean` y `make`.
- Se ejecutó el programa generado.
- Se ingresaron datos válidos e inválidos para comprobar las validaciones.
- Se probaron distintas operaciones del simulador.
- Se verificó que los resultados se almacenaran correctamente en el historial.
- Se comprobó que el repositorio quedara sincronizado con GitHub.

Las propuestas de la herramienta se utilizaron como orientación y fueron contrastadas con el funcionamiento real del programa.

## 13. Repositorio

El código fuente y el historial de desarrollo se encuentran disponibles en GitHub:

https://github.com/juanmarobles/project_c_esc_2

