#include "Ruta.h"

// Constructor
Ruta::Ruta(const std::string& destino, int distancia)
    : ciudadDestino(destino), distancia(distancia) {}

// Getter para la ciudad destino
std::string Ruta::getCiudadDestino() const {
    return ciudadDestino;
}

// Getter para la distancia
int Ruta::getDistancia() const {
    return distancia;
}
