/* 
 * File:   Espacio.h
 *  Autor  : Juan Angelo Flores Rubio
 *  Codigo : 20196493
 * Created on 4 de octubre de 2024, 01:04 AM
 */


#ifndef ESPACIO_H
#define ESPACIO_H

#include <fstream>
#include <stack>
#include "Producto.h"
using namespace std;

class Espacio {
private:
    stack<Producto*> pilaDeProductos;  // Pila de productos en este espacio
    double alturaMaxima;               // Altura máxima que puede ser apilada
    double alturaActual;               // Altura actual ocupada

    double posX, posY, posZ;           // Coordenadas del espacio

    double largo;                      // Largo del espacio (basado en el primer producto)
    double ancho;                      // Ancho del espacio (basado en el primer producto)

public:
    
    Espacio(double alturaMaxVehiculo, double x, double y, double z, double alturaProducto)
    : alturaMaxima(alturaMaxVehiculo), alturaActual(alturaProducto), posX(x), posY(y), posZ(z), largo(0), ancho(0) {}

        
    double getLargo() const { return largo; }
    double getAncho() const { return ancho; }
    double getalturaActual() const { return alturaActual; }
    double getalturaMax() const {return alturaMaxima;}
    
    
    void setLargo(double la){largo=la;}
    void setAncho(double an){ancho=an;}

    // Método para verificar si un producto puede ser apilado en este espacio
    bool esApilable(Producto* nuevoProducto) const {
        
        if (pilaDeProductos.empty()) {
            return true;
        }

        // Verificar restricciones de apilamiento (altura y dimensiones)
        Producto* productoEnLaCima = pilaDeProductos.top();
        if (!productoEnLaCima->esApilableSobre(nuevoProducto)) {
            return false;  // No se puede apilar por restricciones del producto
        }

        // Verificar restricciones de altura, largo y ancho
        if (alturaActual + nuevoProducto->getAltura() > alturaMaxima || 
            nuevoProducto->getLargo() > largo || nuevoProducto->getAncho() > ancho) {
            return false;  // Excedería la altura o las dimensiones horizontales
        }
        return true;
    }

    // Método para agregar un producto al espacio
    bool agregarProducto(Producto* nuevoProducto) {
        // Si el espacio está vacío, las dimensiones se definen por el primer producto
        if (pilaDeProductos.empty()) {
            largo = nuevoProducto->getLargo();  // Definir el largo del espacio
            ancho = nuevoProducto->getAncho();  // Definir el ancho del espacio
        }

        // Verificar si el producto es apilable antes de agregarlo
        if (esApilable(nuevoProducto)) {
            pilaDeProductos.push(nuevoProducto);
            alturaActual += nuevoProducto->getAltura();
            return true;
        }
        return false;  // No se pudo agregar el producto
    }

    // Obtener las coordenadas del espacio
    vector<double> getCoordenadas() const {
        return {posX, posY, posZ};
    }

    // Obtener las dimensiones del espacio (después de agregar el primer producto)
    vector<double> getDimensiones() const {
        return {largo, ancho, alturaMaxima};
    }

    // Verificar si el espacio está vacío
    bool estaVacio() const {
        return pilaDeProductos.empty();
    }

};



#endif /* ESPACIO_H */

