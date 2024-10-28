/* 
 * File:   Producto.cpp
 * Autor  : Juan Angelo Flores Rubio
 * Codigo : 20196493
 * Created on 8 de octubre de 2024, 09:10 PM
 */

#include "Producto.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>

#include <vector>

using namespace std;

//luego añadir puedeRotar
Producto::Producto(int id, string n, double p, double l, double a, double al, double lp){
    id_producto=id;
    nombre=n;
    peso=p;
    largo=l;
    ancho=a;
    alto=al;
    limitePeso=lp;
    volumen=l*a*al;
}

Producto::Producto() : id_producto(0), nombre(""), peso(0.0), largo(0.0), ancho(0.0), alto(0.0), limitePeso(0.0), volumen(0.0) {
        // Constructor por defecto que inicializa con valores "vacíos"
 }

    // Getters
    int Producto::getIdProducto() const { return id_producto; }
    string Producto::getNombre() const { return nombre; }
    double Producto::getPeso() const { return peso; }
    double Producto::getLargo() const { return largo; }
    double Producto::getAncho() const { return ancho; }
    double Producto::getAltura() const { return alto; }
    double Producto::getLimitePeso() const { return limitePeso; }
    double Producto::getVolumen()const {return volumen;}

    // Setters
    void Producto::setIdProducto(int id) { id_producto = id; }
    void Producto::setNombre(string n) { nombre = n; }
    void Producto::setPeso(double p) { peso = p; }
    void Producto::setLargo(double l) { largo = l; }
    void Producto::setAncho(double a) { ancho = a; }
    void Producto::setAlto(double al) { alto = al; }
    void Producto::setLimitePeso(double lp) { limitePeso = lp; }

    // Mostrar información del tipo de producto
    void Producto::mostrarInformacion() const {
        cout << "ID: " << id_producto 
             << " | Nombre: " << nombre 
             << " | Peso: " << peso << " kg"
             << " | Dimensiones: " << largo << " x " << ancho << " x " << alto << " m"
             << " | Límite de Peso: " << limitePeso << " kg";
        cout << endl;
    }
    
    bool Producto::esValido() const {
        // Considera válido si el id_producto es mayor a 0 y todas las dimensiones y peso son positivos
        return id_producto > 0 && peso > 0.0 && largo > 0.0 && ancho > 0.0 && alto > 0.0 && limitePeso > 0.0;
    }
    
    bool Producto::esApilableSobre(Producto* nuevoProducto) const {
        // Verificar si el producto actual puede soportar el peso del nuevo producto
        return nuevoProducto->getPeso() <= limitePeso;
    }


