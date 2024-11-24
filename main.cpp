#include <iostream>
#include "Grafo.h"
#include "Utils.h"

int main() {
    Grafo grafo;

    // Cargar datos desde el archivo CSV
    grafo.cargarDesdeCSV("rutas.csv");

    // Depuración: Imprimir ciudades cargadas en el grafo
    grafo.imprimirCiudades();

    int opcion;
    do {
        std::cout << "\n--- Sistema de Rutas ---\n";
        std::cout << "1. Mostrar ruta mas corta\n";
        std::cout << "2. Agregar nueva ruta\n";
        std::cout << "3. Guardar cambios\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        if (opcion == 1) {
            std::string origen, destino;
            std::cout << "Ciudad origen: ";
            std::cin.ignore(); // Limpiar el buffer
            std::getline(std::cin, origen); // Permitir nombres con espacios
            std::cout << "Ciudad destino: ";
            std::getline(std::cin, destino);

            // Normalizar las entradas
            origen = normalizarNombre(origen);
            destino = normalizarNombre(destino);

            // Autocompletar nombres
            origen = encontrarCiudadMasCercana(origen, grafo.obtenerCiudades());
            destino = encontrarCiudadMasCercana(destino, grafo.obtenerCiudades());

            // Mostrar las entradas normalizadas para depuración
            std::cout << "Ciudad origen (normalizada): " << origen << "\n";
            std::cout << "Ciudad destino (normalizada): " << destino << "\n";

            // Buscar la ruta más corta
            grafo.encontrarRutaMasCorta(origen, destino);
        } 
        
        else if (opcion == 2) {
            std::string origen, nuevaCiudad;
            int distanciaElegida;

            std::cout << "Ciudad existente (debe estar en el sistema): ";
            std::cin.ignore(); // Limpiar el buffer
            std::getline(std::cin, origen);

            std::cout << "Nueva ciudad a agregar: ";
            std::getline(std::cin, nuevaCiudad);

            std::cout << "Distancia entre " << origen << " y " << nuevaCiudad << ": ";
            std::cin >> distanciaElegida;

            origen = normalizarNombre(origen);
            nuevaCiudad = normalizarNombre(nuevaCiudad);

            if (!grafo.existeCiudad(origen)) {
                std::cout << "La ciudad " << origen << " no existe en el sistema. No se puede agregar la nueva ruta.\n";
                continue; // Regresa al menú
            }

            grafo.agregarRuta(origen, nuevaCiudad, distanciaElegida);

            std::vector<std::string> ciudades = grafo.obtenerCiudades();
            for (const std::string& ciudad : ciudades) {
                if (ciudad != origen && ciudad != nuevaCiudad) {
                    int nuevaDistancia = distanciaElegida + grafo.obtenerDistancia(origen, ciudad);
                    grafo.agregarRuta(nuevaCiudad, ciudad, nuevaDistancia);
                }
            }

            std::cout << "La ciudad " << nuevaCiudad << " y sus rutas adicionales han sido agregadas exitosamente.\n";
        }

        else if (opcion == 3) {
            grafo.guardarEnCSV("rutas.csv");
            std::cout << "Cambios guardados exitosamente.\n";
        }

    } while (opcion != 0);

    return 0;
}
