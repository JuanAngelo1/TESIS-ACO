/* 
 * File:   TipoProducto.cpp
 * Autor  : Juan Angelo Flores Rubio
 * Codigo : 20196493
 * Created on 24 de septiembre de 2024, 12:23 AM
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <vector>
#include "TipoProducto.h"

using namespace std;

//luego añadir puedeRotar
TipoProducto::TipoProducto(int id, string n, double p, double l, double a, double al, double lp){
    id_producto=id;
    nombre=n;
    peso=p;
    largo=l;
    ancho=a;
    alto=al;
    limitePeso=lp;
    volumen=l*a*al;
}

TipoProducto::TipoProducto() : id_producto(0), nombre(""), peso(0.0), largo(0.0), ancho(0.0), alto(0.0), limitePeso(0.0), volumen(0.0) {
        // Constructor por defecto que inicializa con valores "vacíos"
 }

    // Getters
    int TipoProducto::getIdProducto() const { return id_producto; }
    string TipoProducto::getNombre() const { return nombre; }
    double TipoProducto::getPeso() const { return peso; }
    double TipoProducto::getLargo() const { return largo; }
    double TipoProducto::getAncho() const { return ancho; }
    double TipoProducto::getAlto() const { return alto; }
    double TipoProducto::getLimitePeso() const { return limitePeso; }
    vector<int> TipoProducto::getPuedeRotar() const { return puedeRotar; }
    double TipoProducto::getVolumen()const {return volumen;}

    // Setters
    void TipoProducto::setIdProducto(int id) { id_producto = id; }
    void TipoProducto::setNombre(string n) { nombre = n; }
    void TipoProducto::setPeso(double p) { peso = p; }
    void TipoProducto::setLargo(double l) { largo = l; }
    void TipoProducto::setAncho(double a) { ancho = a; }
    void TipoProducto::setAlto(double al) { alto = al; }
    void TipoProducto::setLimitePeso(double lp) { limitePeso = lp; }
    void TipoProducto::setPuedeRotar(vector<int> pr) { puedeRotar = pr; }

    // Mostrar información del tipo de producto
    void TipoProducto::mostrarInformacion() const {
        cout << "ID: " << id_producto 
             << " | Nombre: " << nombre 
             << " | Peso: " << peso << " kg"
             << " | Dimensiones: " << largo << " x " << ancho << " x " << alto << " m"
             << " | Límite de Peso: " << limitePeso << " kg"
             << " | Rotaciones permitidas: ";
        for (int r : puedeRotar) {
            cout << r << " ";
        }
        cout << endl;
    }
    
    bool TipoProducto::esValido() const {
        // Considera válido si el id_producto es mayor a 0 y todas las dimensiones y peso son positivos
        return id_producto > 0 && peso > 0.0 && largo > 0.0 && ancho > 0.0 && alto > 0.0 && limitePeso > 0.0;
    }