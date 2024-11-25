# Sistema de Rutas
Este proyecto implementa un sistema de gestión de rutas que permite registrar ciudades y distancias entre ellas, encontrar la ruta más corta entre dos ciudades utilizando el algoritmo de Dijkstra y guardar los cambios en un archivo CSV. Este README detalla el avance del proyecto, las instrucciones para usar el programa, y cómo cumple con los criterios de evaluación establecidos.

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




