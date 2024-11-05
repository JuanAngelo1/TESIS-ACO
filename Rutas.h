/* 
 * File:   Rutas.h
 * Autor  : Juan Angelo Flores Rubio
 * Codigo : 20196493
 * Created on 4 de noviembre de 2024, 10:24 PM
 */

#ifndef RUTAS_H
#define RUTAS_H

#include <fstream>
#include <vector>
#include "Coordenada.h"
#include "Producto.h"
using namespace std;

double calcularDistanciaHaversine(double lat1, double lon1, double lat2, double lon2);

vector<vector<double>> calcularMatrizDistancias(vector<Producto>& );

vector<int> obtenerRutaGreedy(int inicio, const vector<vector<double>>& distancias);

void optimizarRuta(vector<Producto>& , double ,double);

#endif /* RUTAS_H */
