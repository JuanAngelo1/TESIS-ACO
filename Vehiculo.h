/* 
 * File:   Vehiculo.h
 * Autor  : Juan Angelo Flores Rubio
 * Codigo : 20196493
 * Created on 23 de septiembre de 2024, 10:15 PM
 */

#ifndef VEHICULO_H
#define VEHICULO_H
#include "Espacio.h"
#include <vector>
#include <fstream>
using namespace std;

class Vehiculo{
    
private:
    int id_vehiculo;
    string nombre;
    double pesoMaximo;
    double volMaximo;
    double largo;
    double ancho;
    double alto;
    int hora;

    double pesoActual;     
    double volumenActual;  
        
    // Lista de espacios generados en el vehículo
    vector<Espacio> espaciosDisponibles; 
 
public:
    
    // Constructor
    Vehiculo(int id,string n ,double pMax, double l, double a, double h, int hr);
    
    // Métodos setters
    void setIdVehiculo(int id);
    void setPesoMaximo(double pMax);
    void setVolMaximo(double vMax);
    void setLargo(double l);
    void setAncho(double a);
    void setAlto(double h);
    void setHora(int hr);
    
    // Métodos getters
    int getIdVehiculo() const;
    double getPesoMaximo() const;
    double getVolMaximo() const;
    double getLargo() const;
    double getAncho() const;
    double getAlto() const;
    double getPesoActual() const;
    double getVolumenActual() const;
    int getHora() const;
    string getNombre() const;
    
    //Funciones
    void mostrarEstado() const;
    
    // Definir los espacios disponibles en el vehículo (usada por la heurística)
    void definirEspaciosDisponibles(const vector<Espacio>& espacios);

    // Obtener los espacios disponibles
    vector<Espacio> getEspaciosDisponibles() const;
    
};

#endif /* VEHICULO_H */
