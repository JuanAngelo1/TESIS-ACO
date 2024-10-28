/* 
 * File:   Vehiculo.cpp
 * Autor  : Juan Angelo Flores Rubio
 * Codigo : 20196493
 * Created on 23 de septiembre de 2024, 10:15 PM
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <math.h>

#include "Vehiculo.h"
#include "Espacio.h"

using namespace std;

Vehiculo::Vehiculo(int idVehiculo,string n,double pMax, double l, double a, double h, int hr){
    
    id_vehiculo=idVehiculo;
    nombre=n;
    pesoMaximo=pMax;
    volMaximo=l*a*h;
    largo=l;
    ancho=a;
    alto=h;
    hora=hr;
    pesoActual=0;
    volumenActual=0;
}

    // Métodos getters
    int Vehiculo::getIdVehiculo()const{return id_vehiculo;}
    double Vehiculo::getPesoMaximo() const {return pesoMaximo; }
    double Vehiculo::getVolMaximo() const { return volMaximo; }
    double Vehiculo::getLargo() const { return largo; }
    double Vehiculo::getAncho() const { return ancho; }
    double Vehiculo::getAlto() const { return alto; }
    double Vehiculo::getPesoActual() const { return pesoActual; }
    double Vehiculo::getVolumenActual() const { return volumenActual; }
    int Vehiculo::getHora() const { return hora; }
    string Vehiculo::getNombre()const { return nombre;}
    
    // Métodos setters
    void Vehiculo::setIdVehiculo(int id){id_vehiculo=id;}
    void Vehiculo::setPesoMaximo(double pMax) { pesoMaximo = pMax; }
    void Vehiculo::setVolMaximo(double vMax) { volMaximo = vMax; }
    void Vehiculo::setLargo(double l) { largo = l; }
    void Vehiculo::setAncho(double a) { ancho = a; }
    void Vehiculo::setAlto(double h) { alto = h; }
    void Vehiculo::setHora(int hr) { hora = hr; }


    //Funciones Espacio
    void Vehiculo::definirEspaciosDisponibles(const vector<Espacio>& espacios) {
        espaciosDisponibles = espacios;
    }

    vector<Espacio> Vehiculo::getEspaciosDisponibles() const {
        return espaciosDisponibles;
    }


    void Vehiculo::mostrarEstado() const {
        cout << "Peso Actual: " << pesoActual << " / " << pesoMaximo << endl;
        cout << "Volumen Actual: " << volumenActual << " / " << volMaximo << endl;

    }
