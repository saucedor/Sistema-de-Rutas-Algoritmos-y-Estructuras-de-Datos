#include "Grafo.h"
#include "Utils.h"
#include <fstream>
#include <sstream>
#include <queue>
#include <iostream>
#include <limits>
#include <set>

// Constructor por defecto
Grafo::Grafo() {}

// Cargar datos desde el archivo CSV
void Grafo::cargarDesdeCSV(const std::string& archivo) {
    std::ifstream file(archivo);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo: " << archivo << std::endl;
        return;
    }

    std::string linea, origen, destino;
    int distancia;

    // Ignorar la primera línea (encabezado)
    std::getline(file, linea);

    while (std::getline(file, linea)) {
        std::stringstream ss(linea);
        std::getline(ss, origen, ',');
        std::getline(ss, destino, ',');
        ss >> distancia;

        // Normalizar los nombres
        origen = normalizarNombre(origen);
        destino = normalizarNombre(destino);

        // Imprimir nombres normalizados para depuración
        std::cout << "Cargando: " << origen << " -> " << destino << " (" << distancia << " km)\n";

        // Agregar las rutas al grafo
        rutas[origen].emplace_back(destino, distancia);
        rutas[destino].emplace_back(origen, distancia); // Si es bidireccional
    }

    file.close();
}

// Guardar datos en el archivo CSV
void Grafo::guardarEnCSV(const std::string& archivo) const {
    // Abrir el archivo en modo de anexar
    std::ofstream file(archivo, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error al escribir en el archivo: " << archivo << std::endl;
        return;
    }

    // Para evitar duplicar rutas, usamos un set
    static std::set<std::pair<std::string, std::string>> rutasGuardadas;

    for (const auto& [origen, conexiones] : rutas) {
        for (const auto& ruta : conexiones) {
            std::string destino = ruta.getCiudadDestino();
            int distancia = ruta.getDistancia();

            // Verificar si la ruta ya fue guardada (en ambos sentidos)
            if (rutasGuardadas.find({origen, destino}) == rutasGuardadas.end() &&
                rutasGuardadas.find({destino, origen}) == rutasGuardadas.end()) {
                file << origen << "," << destino << "," << distancia << "\n";
                rutasGuardadas.insert({origen, destino}); // Marcar como guardada
            }
        }
    }

    file.close();
    std::cout << "Nuevas rutas guardadas en el archivo.\n";
}


// Agregar una nueva ruta
void Grafo::agregarRuta(const std::string& origen, const std::string& destino, int distancia) {
    rutas[origen].emplace_back(destino, distancia);
    rutas[destino].emplace_back(origen, distancia); // Bidireccional
    std::cout << "Ruta agregada exitosamente: " << origen << " -> " << destino << " (" << distancia << " km)\n";
}

// Encontrar la ruta más corta usando Dijkstra
void Grafo::encontrarRutaMasCorta(const std::string& origen, const std::string& destino) const {
    if (rutas.find(origen) == rutas.end() || rutas.find(destino) == rutas.end()) {
        std::cerr << "Una de las ciudades no existe en el grafo.\n";
        return;
    }

    // Mapa de distancias inicializado en infinito
    std::map<std::string, int> distancias;
    for (const auto& [ciudad, _] : rutas) {
        distancias[ciudad] = std::numeric_limits<int>::max();
    }
    distancias[origen] = 0;

    // Cola de prioridad para procesar las ciudades por distancia mínima
    using Par = std::pair<int, std::string>; // {distancia, ciudad}
    std::priority_queue<Par, std::vector<Par>, std::greater<Par>> cola;
    cola.push({0, origen});

    // Mapa para reconstruir el camino
    std::map<std::string, std::string> predecesor;

    while (!cola.empty()) {
        auto [distanciaActual, ciudadActual] = cola.top();
        cola.pop();

        // Procesar cada vecino de la ciudad actual
        for (const auto& ruta : rutas.at(ciudadActual)) {
            std::string vecino = ruta.getCiudadDestino();
            int nuevaDistancia = distanciaActual + ruta.getDistancia();

            // Actualizar si encontramos una distancia más corta
            if (nuevaDistancia < distancias[vecino]) {
                distancias[vecino] = nuevaDistancia;
                predecesor[vecino] = ciudadActual;
                cola.push({nuevaDistancia, vecino});
            }
        }
    }

    // Reconstruir y mostrar el camino
    if (distancias[destino] == std::numeric_limits<int>::max()) {
        std::cout << "No hay ruta entre " << origen << " y " << destino << ".\n";
        return;
    }

    std::cout << "Distancia más corta de " << origen << " a " << destino << ": " << distancias[destino] << " km\n";
    std::cout << "Ruta: ";

    std::string ciudad = destino;
    std::vector<std::string> camino;
    while (ciudad != origen) {
        camino.push_back(ciudad);
        ciudad = predecesor[ciudad];
    }
    camino.push_back(origen);

    for (auto it = camino.rbegin(); it != camino.rend(); ++it) {
        std::cout << *it;
        if (it + 1 != camino.rend()) std::cout << " -> ";
    }
    std::cout << "\n";
}

// Imprimir el grafo completo
void Grafo::imprimirGrafo() const {
    for (const auto& [origen, conexiones] : rutas) {
        std::cout << origen << " está conectado a:\n";
        for (const auto& ruta : conexiones) {
            std::cout << "  -> " << ruta.getCiudadDestino() << " (" << ruta.getDistancia() << " km)\n";
        }
    }
}

// Imprimir solo las ciudades almacenadas en el grafo
void Grafo::imprimirCiudades() const {
    std::cout << "Ciudades almacenadas en el grafo:\n";
    for (const auto& [ciudad, _] : rutas) {
        std::cout << " - " << ciudad << "\n";
    }
}

std::vector<std::string> Grafo::obtenerCiudades() const {
    std::vector<std::string> ciudades;
    for (const auto& [ciudad, _] : rutas) {
        ciudades.push_back(ciudad);
    }
    return ciudades;
}

int Grafo::obtenerDistancia(const std::string& origen, const std::string& destino) const {
    if (rutas.find(origen) != rutas.end()) {
        for (const auto& ruta : rutas.at(origen)) {
            if (ruta.getCiudadDestino() == destino) {
                return ruta.getDistancia();
            }
        }
    }
    return std::numeric_limits<int>::max(); // Retorna un valor muy alto si no están conectadas
}

bool Grafo::existeCiudad(const std::string& ciudad) const {
    return rutas.find(ciudad) != rutas.end();
}
