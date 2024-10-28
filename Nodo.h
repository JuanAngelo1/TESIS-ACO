/* 
 * File:   Nodo.h
 * Autor  : Juan Angelo Flores Rubio
 * Codigo : 20196493
 * Created on 28 de septiembre de 2024, 01:29 AM
 */

#ifndef NODO_H
#define NODO_H

#include <fstream>
#include <vector>
#include "TipoProducto.h"
#include "Espacio.h"

using namespace std;

class Nodo{
    
private:
    int idNodo;
    int idProducto;  // Identificador del producto
    int posicionProducto;  // La posición específica de este nodo para el producto
    double posX, posY, posZ;  // Coordenadas dentro del vehículo
    
public:
    
    Nodo(int idNodo,int idProducto, int posicionProducto, double x, double y, double z)
        : idNodo(idNodo),idProducto(idProducto), posicionProducto(posicionProducto), posX(x), posY(y), posZ(z) {}
    
    // Getters
    int getIdProducto() const { return idProducto; }
    double getPosX() const { return posX; }
    double getPosY() const { return posY; }
    double getPosZ() const { return posZ; }
    
    
    void mostrarInfo() const {
        cout << "Producto ID: " << idProducto << " - Posición: " << posicionProducto << 
                " - Coordenadas: (" << posX<< ", " << posY << ", " << posZ << ")" << endl;
    }
    
    bool posicionIgual(const Nodo& otro) const {
        return (posX == otro.posX && posY == otro.posY && posZ == otro.posZ);
    }
    
    int getIdNodo() const {
        return idNodo;
    }
    
    int getPosicionProducto() const { return posicionProducto; }


};

#endif /* NODO_H */
