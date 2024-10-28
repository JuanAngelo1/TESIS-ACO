/* 
 * File:   Colonia.h
 * Autor  : Juan Angelo Flores Rubio
 * Codigo : 20196493
 * Created on 29 de septiembre de 2024, 04:29 PM
 */

#ifndef COLONIA_H
#define COLONIA_H

#include <fstream>
#include <vector>
#include "Hormiga.h"
#include "Solucion.h"
#include "Grafo.h"

using namespace std;

class Colonia{
    
private:  
    vector<Hormiga> hormigas;        
    Solucion mejorSolucion;               
    int numeroHormigas;                   
    int numeroIteraciones;                
    double tasaEvaporacion;               
    double alpha;                         
    double beta; 


public:
    // Constructor
    Colonia(int numHormigas, int numIteraciones, double evaporacion, double a, double b);

    // Métodos
    void inicializarColonia(Grafo &);            // Inicializa las hormigas
    void actualizarFeromonas();           // Actualiza las feromonas en las aristas
    Solucion obtenerMejorSolucion() const; // Devuelve la mejor solución

    // Getters
    int getNumeroHormigas() const;
    int getNumeroIteraciones() const;
    double getTasaEvaporacion() const;
    double getAlpha() const;
    double getBeta() const;
    vector<Hormiga> getHormigas() const;

    // Setters
    void setNumeroHormigas(int numHormigas);
    void setNumeroIteraciones(int numIteraciones);
    void setTasaEvaporacion(double evaporacion);
    void setAlpha(double a);
    void setBeta(double b);
    
    double calcularContribucionFeromona(const Solucion& solucion) const;
    
};

#endif /* COLONIA_H */
