/* 
 * File:   Colonia.cpp
 * Autor  : Juan Angelo Flores Rubio
 * Codigo : 20196493
 * Created on 29 de septiembre de 2024, 04:29 PM
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include "Grafo.h"
#include "Colonia.h"

using namespace std;

// Constructor
Colonia::Colonia(int numHormigas, int numIteraciones, double evaporacion, double a, double b)
    : numeroHormigas(numHormigas), numeroIteraciones(numIteraciones),
      tasaEvaporacion(evaporacion), alpha(a), beta(b) {
}

void Colonia::inicializarColonia(Grafo& grafo) {
    hormigas.clear();
    for (int i = 0; i < numeroHormigas; i++) {
        Hormiga nuevaHormiga;
        Nodo* nodoInicial = grafo.obtenerNodoAleatorio();  // Selección aleatoria del nodo inicial
        if (nodoInicial != nullptr) {
            nuevaHormiga.iniciarEnNodo(nodoInicial);  // Inicializas la hormiga en un nodo aleatorio
        }
        hormigas.push_back(nuevaHormiga);
    }
    cout << "Colonia inicializada con " << numeroHormigas << " hormigas." << endl;
}

// Actualiza las feromonas en las aristas
void Colonia::actualizarFeromonas() {
    // Implementa la lógica para evaporar y depositar feromonas
    // Dependiendo del rastro de feromonas dejado por cada hormiga y el costo de su solución.
    std::cout << "Actualizando feromonas con tasa de evaporación: " << tasaEvaporacion << std::endl;
}

// Devuelve la mejor solución encontrada por la colonia
Solucion Colonia::obtenerMejorSolucion() const {
    return mejorSolucion;
}

// Getters
int Colonia::getNumeroHormigas() const {
    return numeroHormigas;
}

int Colonia::getNumeroIteraciones() const {
    return numeroIteraciones;
}

double Colonia::getTasaEvaporacion() const {
    return tasaEvaporacion;
}

double Colonia::getAlpha() const {
    return alpha;
}

double Colonia::getBeta() const {
    return beta;
}

vector<Hormiga> Colonia::getHormigas() const{
    
    return hormigas;
}

// Setters
void Colonia::setNumeroHormigas(int numHormigas) {
    numeroHormigas = numHormigas;
}

void Colonia::setNumeroIteraciones(int numIteraciones) {
    numeroIteraciones = numIteraciones;
}

void Colonia::setTasaEvaporacion(double evaporacion) {
    tasaEvaporacion = evaporacion;
}

void Colonia::setAlpha(double a) {
    alpha = a;
}

void Colonia::setBeta(double b) {
    beta = b;
}

double Colonia::calcularContribucionFeromona(const Solucion& solucion) const {
    return 1.0 / solucion.getFitness();  // Si fitness es el costo, la contribución sería inversa al costo.
}