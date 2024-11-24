#include "Utils.h"
#include <algorithm>
#include <cctype>
#include <limits>
#include <vector>

// Función para normalizar nombres (convierte a minúsculas y elimina acentos)
std::string normalizarNombre(const std::string& nombre) {
    std::string normalizado = nombre;

    // Convertir a minúsculas
    std::transform(normalizado.begin(), normalizado.end(), normalizado.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    // Eliminar acentos
    const std::string acentos = "áéíóúÁÉÍÓÚ";
    const std::string sinAcentos = "aeiouAEIOU";
    for (size_t i = 0; i < acentos.size(); ++i) {
        std::replace(normalizado.begin(), normalizado.end(), acentos[i], sinAcentos[i]);
    }

    // Retornar el nombre normalizado
    return normalizado;
}

int distanciaLevenshtein(const std::string& a, const std::string& b) {
    size_t n = a.size(), m = b.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));

    for (size_t i = 0; i <= n; ++i) dp[i][0] = i;
    for (size_t j = 0; j <= m; ++j) dp[0][j] = j;

    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= m; ++j) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
        }
    }
    return dp[n][m];
}

std::string encontrarCiudadMasCercana(const std::string& entrada, const std::vector<std::string>& ciudades) {
    std::string mejorCoincidencia;
    int distanciaMinima = std::numeric_limits<int>::max();

    for (const auto& ciudad : ciudades) {
        int distancia = distanciaLevenshtein(entrada, ciudad);
        if (distancia < distanciaMinima) {
            distanciaMinima = distancia;
            mejorCoincidencia = ciudad;
        }
    }

    return mejorCoincidencia;
}

