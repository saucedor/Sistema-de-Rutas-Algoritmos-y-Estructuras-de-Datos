#ifndef RUTA_H
#define RUTA_H

#include <string>

class Ruta {
private:
    std::string ciudadDestino; // Nombre de la ciudad destino
    int distancia; // Distancia a la ciudad destino en kilómetros

public:
    // Constructor
    Ruta(const std::string& destino, int distancia);

    // Métodos de acceso (getters)
    std::string getCiudadDestino() const;
    int getDistancia() const;
};

#endif
