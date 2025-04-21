## 📘 Sobre el proyecto

Este proyecto implementa y compara diferentes técnicas **metaheurísticas** aplicadas al problema de **Aprendizaje de Pesos en Características (APC)** para mejorar la precisión del clasificador **1-Nearest Neighbor (1-NN)**. El objetivo es optimizar la asignación de pesos a las características de entrada, logrando así una clasificación más precisa y eficiente.

Se trabaja con bases de datos reales y se evalúan distintas estrategias de optimización utilizando **validación cruzada (5-fold cross validation)**. Las métricas consideradas combinan la precisión del clasificador y la reducción de dimensionalidad, permitiendo valorar tanto el rendimiento como la simplicidad del modelo generado.

### 🧠 Técnicas implementadas
- Metaheurísticas para búsqueda en espacios de codificación real: 
- Clasificación con 1-NN
- Cálculo de funciones de fitness combinadas (precisión + reducción)

### 🧪 Conjuntos de datos utilizados
- **Ecoli** – Localización de proteínas en células bacterianas
- **Parkinsons** – Detección de Parkinson a partir de biomarcadores de voz
- **Breast Cancer** – Clasificación de tumores benignos y malignos

### 🛠️ Tecnologías utilizadas
- Lenguaje: **C++**
- Compilación y construcción: **CMake**
- Paradigma: **Programación orientada a objetos**

## 📁 Estructura del proyecto 

La estructura de directorios del proyecto es la siguiente:

- Directorio `BIN`: contiene el ejectuable del programa, APC_problem, junto con el directorio
InstanciasAPC, con los ficheros ARRF de las tres bases de datos mencionadas en la descripción,
y el directorio Resultados con ficheros en texto plano que almacenan en formato tabulado los datos
obtenidos de la ejecución del programa.

- Directorio `FUENTES`: Contiene el código fuente del proyecto. En el directorio inc se encuentran los
ficheros de cabecera .hpp y en el directorio src los ficheros .cpp con las implementaciones y el
programa principal main.cpp.

- Al mismo nivel que los directorios anteriores se encuentra el fichero `CMakeLists.txt` que se usa
para la compilación del proyecto.

## 🧩 Diseño del código fuente

El proyecto está diseñado siguiendo el paradigma de **Programación Orientada a Objetos**. A continuación, se detallan las clases, estructuras y responsabilidades principales:

### 📦 Estructuras y archivos generales

- `structures.hpp`
  Define estructuras y tipos enumerados:
  - `Data`: representa un conjunto de instancias.
  - `Result`: almacena métricas, pesos y tiempo de cómputo de cada algoritmo.

- `arff_file.hpp/.cpp` 
  - Clase `ARFF_file`: transforma datos en formato ARFF a la estructura `Data`.

- `metaheuristics.hpp/.cpp` 
  - Clase abstracta `Metaheuristics`: interfaz base para todos los algoritmos. 
  Métodos clave: 
    - `compute_weights()`: método virtual puro. 
    - `train()`: entrena el modelo. 
    - `test()`: evalúa las métricas con los pesos aprendidos.

### 🔄 Implementaciones de algoritmos

- `classifier_1NN.hpp/.cpp`, `greedy_relief.hpp/.cpp`, `local_search.hpp/.cpp`, `ag.hpp/.cpp`: 
  Implementan `Classifier_1NN`, `Greedy_relief`, `Local_search`, `AG`, cada una con su propio `compute_weights()`.

- `agg.hpp/.cpp`, `age.hpp/.cpp`: 
  Heredan de `AG` y redefinen métodos `mutate` y `replace`.

- `am.hpp/.cpp`: 
  Hereda de `AGG` y redefine `compute_weights()`.

- `am_all.hpp/.cpp`, `am_best.hpp/.cpp`, `am_rand.hpp/.cpp`: 
  Heredan de `AM` y redefinen el método `exploitation`.

### ⚙️ Otros componentes clave

- `crossing.hpp`: interfaz para operadores de cruce.

- `blx.hpp/.cpp`, `ca.hpp/.cpp`: 
  Implementan `BLX` y `CA`, que heredan de `crossing` e implementan el método `cross`.

- `tournament.hpp/.cpp`: 
  Clase `Tournament`: realiza torneos entre individuos de una población.

- `apc.hpp/.cpp`: 
  Clase `APC`: aplica 5-fold cross validation con múltiples metaheurísticas. 
  Métodos principales: 
    - `train()` y `test()`: ejecutan la evaluación por partición. 
    - `get_train_results()` y `get_test_results()`: almacenan resultados en matrices `Result`. 
    - `add_metaheuristics()`: añade los algoritmos a aplicar al problema.

- `main.cpp`: 
  Crea un objeto `APC` por base de datos y muestra resultados tabulados.

