# Sistema de Rutas
Este proyecto implementa un sistema de gestión de rutas que permite registrar ciudades y distancias entre ellas, encontrar la ruta más corta entre dos ciudades utilizando el algoritmo de Dijkstra y guardar los cambios en un archivo CSV. En el caso preciso de este .csv se encuentran las capitales de cada estado de México Este README detalla el avance del proyecto, las instrucciones para usar el programa, y cómo cumple con los criterios de evaluación establecidos.

---

# Avance del Proyecto

## Estructuras de Datos Utilizadas

### Grafo:
- Representa las ciudades y sus conexiones (rutas).
- Implementado mediante un `std::map` donde:
  - Las claves son los nombres de las ciudades (`std::string`).
  - Los valores son vectores de rutas (`std::vector<Ruta>`).

### Clase Ruta:
- Modela una conexión entre ciudades, incluyendo:
  - La ciudad de destino.
  - La distancia entre las ciudades.

### Archivo CSV:
- Los datos de las rutas se almacenan y leen desde un archivo CSV.
- Ejemplo de formato:
  ```csv
  CiudadOrigen,CiudadDestino,Distancia
  Aguascalientes,Mexico,900
  Zacatecas,Durango,100

# Cómo Usar el Programa

## Requisitos Previos
- Compilador de C++ compatible con C++11 o superior.
- Archivo `rutas.csv` con los datos iniciales de las ciudades y distancias.

## Compilación y Ejecución

-Compila el programa utilizando:
  ``` bash
  g++ main.cpp Grafo.cpp Ruta.cpp Utils.cpp -o sistema_rutas
  ```
-Ejecuta el programa:
  ``` bash
  ./sistema_rutas
  ```
# Opciones del Menú

El programa presenta un menú interactivo con las siguientes opciones:

## Mostrar Ruta Más Corta:
- Solicita la ciudad de origen y destino.
- Utiliza el algoritmo de Dijkstra para encontrar y mostrar la distancia más corta.

## Agregar Nueva Ruta:
- Permite agregar una ciudad nueva conectada a una existente.
- Genera automáticamente rutas hacia otras ciudades basándose en las distancias existentes.
  Ejemplo:
  Si es que el usuario agrega la ciudad "El paso" con la ciudad que ya está en el grafo "Chihuahua" que se encuentran a 360 km, el paso va a generar rutas a las otras ciudades
  del grafo basado en las distancias que ya tenía "Chihuahua". Un caso sería de "El paso" a "Ciudad de México" sería la distancia entre "El paso" y "Chihuahua" + "Chihuahua" y "Ciudad de   México".
  

## Guardar Cambios:
- Guarda las rutas nuevas al final del archivo `rutas.csv`.

## Salir:
- Termina la ejecución del programa.

# Cumplimiento de Indicadores

## SICT0301: Evalúa los Componentes

### Análisis de Complejidad

#### Carga de Rutas desde CSV:
- **Complejidad**: \( O(n) \), donde \( n \) es el número de líneas en el archivo CSV.

#### Búsqueda de la Ruta Más Corta (Dijkstra):
- **Complejidad**: \( O((V+E)\log V) \), donde:
  - \( V \) es el número de ciudades.
  - \( E \) es el número de rutas.

#### Guardado de Rutas en CSV:
- **Complejidad**: \( O(r) \), donde \( r \) es el número de rutas generadas.

#### Agregar Nueva Ruta:
- **Complejidad**: \( O(c+n) \), donde:
  - \( c \) es la cantidad de ciudades existentes.
  - \( n \) es el número de nuevas rutas generadas.

# SICT0302: Toma Decisiones

# Estructura de Datos: Grafo

## Justificación
El uso de un grafo es necesario porque este permite modelar ciudades como nodos y rutas entre ellas como arcos. Esto resulta ideal para representar sistemas de transporte donde cada conexión tiene un peso asociado, en este caso, la distancia entre las ciudades. Usar un `std::map<std::string, std::vector<Ruta>>` facilita la implementación al asociar cada ciudad (clave) con un conjunto de rutas (valor), lo que hace eficiente la representación y la manipulación de las conexiones.

## Implementación
En el proyecto, el grafo se implementa mediante:

- **Claves** (`std::string`): Representan los nombres de las ciudades.
- **Valores** (`std::vector<Ruta>`): Almacenan los arcos, donde cada arco tiene atributos como la ciudad de destino y la distancia.

### Ejemplo de cómo se cargan las conexiones al grafo desde un archivo CSV:
```cpp
std::ifstream file(archivo);
while (std::getline(file, linea)) {
    std::stringstream ss(linea);
    std::getline(ss, origen, ',');
    std::getline(ss, destino, ',');
    ss >> distancia;

    rutas[origen].emplace_back(destino, distancia);
    rutas[destino].emplace_back(origen, distancia); // Si es bidireccional
}
```
Este enfoque permite modelar tanto conexiones unidireccionales como bidireccionales de forma flexible.

# Algoritmo: Dijkstra

## Justificación
El algoritmo de Dijkstra se emplea porque es eficiente para encontrar las rutas más cortas en grafos ponderados donde los pesos son no negativos, como en este caso, las distancias entre ciudades. Su capacidad de actualizar las distancias mínimas de forma iterativa lo hace ideal para este tipo de problemas de optimización.

## Aplicación en el Proyecto
En el proyecto, Dijkstra se utiliza para calcular la ruta más corta entre dos ciudades dadas. La implementación incluye:

- **Inicialización de las distancias**: Se establece una distancia inicial infinita para todas las ciudades, excepto la de origen, que comienza en 0.
- **Cola de prioridad**: Para procesar las ciudades de acuerdo con la distancia mínima conocida.
- **Actualización de rutas**: Al procesar cada ciudad, se revisan y actualizan las distancias hacia sus vecinos si se encuentra un camino más corto.

### Fragmento del código que muestra la lógica clave:
```cpp
std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, std::greater<>> cola;
cola.push({0, origen});

while (!cola.empty()) {
    auto [distanciaActual, ciudadActual] = cola.top();
    cola.pop();

    for (const auto& ruta : rutas.at(ciudadActual)) {
        int nuevaDistancia = distanciaActual + ruta.getDistancia();
        if (nuevaDistancia < distancias[vecino]) {
            distancias[vecino] = nuevaDistancia;
            predecesor[vecino] = ciudadActual;
            cola.push({nuevaDistancia, vecino});
        }
    }
}
```
Este método asegura que se obtenga la distancia más corta y el camino entre dos ciudades, respetando las restricciones del problema.

# SICT0303: Implementa Acciones Científicas

## Consulta de Información de las Estructuras

El programa incluye mecanismos interactivos para consultar:
- Las conexiones entre ciudades (`imprimirGrafo`).
- La distancia más corta entre dos ciudades (`encontrarRutaMasCorta`).

## Lectura de Archivos CSV

- Los datos de las ciudades y rutas se cargan desde el archivo `rutas.csv` al inicializar el programa.
- Los nombres de las ciudades se normalizan (sin acentos ni mayúsculas) para evitar inconsistencias.

## Escritura de Archivos CSV

- Las rutas nuevas se guardan en el archivo `rutas.csv` al final, preservando los datos existentes.

# Casos de Prueba

## Carga de Datos Inicial

- **Archivo de entrada**: `rutas.csv`.
- **Resultado esperado**:
  - Todas las rutas se cargan correctamente al grafo.
  - Los nombres de las ciudades se normalizan.

## Búsqueda de Rutas Más Cortas

- **Entrada**: Ciudad A -> Ciudad B.
- **Resultado esperado**:
  - Se muestra la distancia más corta y la ruta completa.

## Agregar Nueva Ruta

- **Entrada**: Ciudad existente, nueva ciudad, distancia.
- **Resultado esperado**:
  - La nueva ciudad se conecta con todas las demás, calculando las distancias correctas.

## Guardar Cambios

- **Entrada**: Opción 3 en el menú.
- **Resultado esperado**:
  - El archivo `rutas.csv` se actualiza correctamente, preservando los datos originales.

# Conclusión

El Sistema de Rutas implementa eficientemente un grafo para modelar ciudades y rutas, utilizando estructuras y algoritmos adecuados para las operaciones requeridas. Además, se ha diseñado para ser extensible y cumplir con los indicadores evaluados en la materia.
