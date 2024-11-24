#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

// Declaración de la función
std::string normalizarNombre(const std::string& nombre);
int distanciaLevenshtein(const std::string& a, const std::string& b);
std::string encontrarCiudadMasCercana(const std::string& entrada, const std::vector<std::string>& ciudades);

#endif
