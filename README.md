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

# Consulta de Información de las Estructuras

## 1. Conexiones entre ciudades (`imprimirGrafo`)

### Salida: 
Al cargar los datos desde un archivo CSV, el sistema registra cada conexión con un mensaje en consola que indica las ciudades conectadas y la distancia, como:

``` bash
Cargando: toluca -> zacatecas (800 km)
Cargando: toluca -> villahermosa (500 km)
Cargando: toluca -> tuxtla gutierrez (500 km)
Cargando: toluca -> xalapa (400 km)
Cargando: tuxtla gutierrez -> zacatecas
```

También muestra una lista de todas las ciudades almacenadas en el grafo:

``` bash
Ciudades almacenadas en el grafo:
 - xalapa
 - queretaro
 - toluca
 ...
```

### Entrada:
Esta funcionalidad no requiere entradas adicionales del usuario, pero es llamada indirectamente como parte de la interacción principal con el menú del sistema. Por ejemplo:

```bash
--- Sistema de Rutas ---
1. Mostrar ruta más corta
2. Agregar nueva ruta
3. Guardar cambios
0. Salir
Seleccione una opción: 3
```

## 2. Distancia más corta entre dos ciudades (`encontrarRutaMasCorta`)

### Entrada:
El usuario interactúa con el menú principal y selecciona la opción para buscar la ruta más corta:

```bash
--- Sistema de Rutas ---
1. Mostrar ruta más corta
2. Agregar nueva ruta
3. Guardar cambios
0. Salir
Seleccione una opción: 1
```
Luego, se le solicita que ingrese las ciudades de origen y destino:

```bash
Ciudad origen: Xalapa
Ciudad destino: Queretaro
```

El sistema normaliza los nombres de las ciudades ingresadas para asegurar consistencia:

```bash
Ciudad origen (normalizada): xalapa
Ciudad destino (normalizada): queretaro
```

Salida:
El programa calcula y muestra la distancia más corta entre las dos ciudades, junto con la ruta específica que debe tomarse:

```bash
Distancia más corta de xalapa a queretaro: 400 km
Ruta: xalapa -> queretaro
```

Una vez completada, regresa al menú principal para continuar con otras acciones.

## 3. Agregar una nueva ciudad y sus rutas (`agregarRuta`)

### Entrada:
El usuario selecciona la opción para agregar una nueva ruta o ciudad en el menú principal:

```bash
--- Sistema de Rutas ---
1. Mostrar ruta más corta
2. Agregar nueva ruta
3. Guardar cambios
0. Salir
Seleccione una opción: 2
```

Se solicita:

- Ciudad existente: Una ciudad que ya debe estar en el sistema. Ejemplo: Monterrey.
- Nueva ciudad: La ciudad que se desea agregar al sistema. Ejemplo: Laredo.
- Distancia: La distancia entre la ciudad existente y la nueva ciudad. Ejemplo: 230.
La consola confirma las entradas y normaliza los nombres:

```bash
Ciudad existente (debe estar en el sistema): Monterrey
Nueva ciudad a agregar: Laredo
Distancia entre Monterrey y Laredo: 230
```

Salida:
Se agregan las rutas entre la nueva ciudad y todas las ciudades previamente conectadas a la ciudad existente, confirmando cada adición:

```bash
Ruta agregada exitosamente: monterrey -> laredo (230 km)
Ruta agregada exitosamente: laredo -> aguascalientes (630 km)
Ruta agregada exitosamente: laredo -> campeche (1430 km)
...
Ruta agregada exitosamente: laredo -> zacatecas (530 km)
```

Finalmente, muestra un mensaje que confirma que la nueva ciudad y todas sus rutas han sido agregadas:

```bash
La ciudad laredo y sus rutas adicionales han sido agregadas exitosamente.
```

## 4. Guardar los datos en un archivo CSV (`guardarEnCSV`)

### Entrada:
El usuario selecciona la opción para guardar los datos actuales del grafo en un archivo CSV:

```bash
--- Sistema de Rutas ---
1. Mostrar ruta más corta
2. Agregar nueva ruta
3. Guardar cambios
0. Salir
Seleccione una opción: 3
```

No se requiere ninguna entrada adicional, ya que el programa toma los datos directamente de la estructura interna del grafo.

# Conclusión

El Sistema de Rutas implementa eficientemente un grafo para modelar ciudades y rutas, utilizando estructuras y algoritmos adecuados para las operaciones requeridas. Además, se ha diseñado para ser extensible y cumplir con los indicadores evaluados en la materia.
