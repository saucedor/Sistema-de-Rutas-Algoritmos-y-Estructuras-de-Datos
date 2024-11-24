#ifndef GRAFO_H
#define GRAFO_H

#include <map>
#include <vector>
#include <string>
#include "Ruta.h"

class Grafo {
private:
    std::map<std::string, std::vector<Ruta>> rutas;

public:
    Grafo(); // Constructor por defecto
    void cargarDesdeCSV(const std::string& archivo); // Carga datos desde un CSV
    void guardarEnCSV(const std::string& archivo) const; // Guarda datos en un CSV
    void agregarRuta(const std::string& origen, const std::string& destino, int distancia); // Agrega una ruta
    void encontrarRutaMasCorta(const std::string& origen, const std::string& destino) const; // Encuentra la ruta más corta usando Dijkstra
    void imprimirGrafo() const; // Imprime el grafo completo (ciudades y conexiones)
    void imprimirCiudades() const; // Imprime solo las ciudades almacenadas en el grafo
    std::vector<std::string> obtenerCiudades() const;
    int obtenerDistancia(const std::string& origen, const std::string& destino) const;
    bool existeCiudad(const std::string& ciudad) const;
};

#endif

