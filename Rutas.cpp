/* 
 * File:   Rutas.cpp
 * Autor  : Juan Angelo Flores Rubio
 * Codigo : 20196493
 * Created on 4 de noviembre de 2024, 10:24 PM
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <math.h>
#include "Rutas.h"
#include "Producto.h"
#include "Coordenada.h"

#define RADIO_TIERRA 6371.0
#define MAX_DISTANCIA 1e5

using namespace std;

// Función para calcular la distancia Haversine entre dos coordenadas
double calcularDistanciaHaversine(double lat1, double lon1, double lat2, double lon2) {
    
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    lat1 = lat1 * M_PI / 180.0;
    lat2 = lat2 * M_PI / 180.0;

    double a = sin(dLat / 2) * sin(dLat / 2) +
               sin(dLon / 2) * sin(dLon / 2) * cos(lat1) * cos(lat2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return RADIO_TIERRA * c;
}

vector<vector<double>> calcularMatrizDistancias(const vector<Producto>& productos, double latOrigen, double lonOrigen) {
    int n = productos.size();
    vector<vector<double>> distancias(n + 1, vector<double>(n + 1, 0));

    // Calcular distancias entre productos
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double distancia = calcularDistanciaHaversine(
                productos[i].getLatitud(), productos[i].getLongitud(),
                productos[j].getLatitud(), productos[j].getLongitud()
            );
            distancias[i + 1][j + 1] = distancia;
            distancias[j + 1][i + 1] = distancia;
        }
    }

    // Calcular distancias desde el origen a cada producto
    for (int i = 0; i < n; ++i) {
        double distanciaOrigen = calcularDistanciaHaversine(
            latOrigen, lonOrigen,
            productos[i].getLatitud(), productos[i].getLongitud()
        );
        distancias[0][i + 1] = distanciaOrigen;
        distancias[i + 1][0] = distanciaOrigen;
    }
    
    return distancias;
}


vector<int> obtenerRutaGreedy(int inicio, const vector<vector<double>>& distancias) {
    int n = distancias.size();
    vector<int> ruta;
    vector<bool> visitado(n, false);

    int actual = inicio;
    ruta.push_back(actual);
    visitado[actual] = true;

    for (int i = 1; i < n; ++i) {
        double minDistancia = MAX_DISTANCIA;
        int siguiente = -1;

        for (int j = 1; j < n; ++j) { 
            if (!visitado[j] && distancias[actual][j] < minDistancia) {
                minDistancia = distancias[actual][j];
                siguiente = j;
            }
        }

        if (siguiente != -1) {
            ruta.push_back(siguiente);
            visitado[siguiente] = true;
            actual = siguiente;
        }
    }

    return ruta;
}

void optimizarRuta(vector<Producto>& productos, double latOrigen, double lonOrigen) {
    vector<vector<double>> distancias = calcularMatrizDistancias(productos, latOrigen, lonOrigen);
    vector<int> ruta = obtenerRutaGreedy(0, distancias);

    for (int i = 1; i < ruta.size(); ++i) {  // Comenzamos desde i = 1 para omitir el origen
        int indiceProducto = ruta[i] - 1;    // Ajustamos el índice para productos
        productos[indiceProducto].setOrdenColocacion(i);
    }
}
