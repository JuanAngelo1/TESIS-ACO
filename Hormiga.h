/* 
 * File:   Hormiga.h
 * Autor  : Juan Angelo Flores Rubio
 * Codigo : 20196493
 * Created on 29 de septiembre de 2024, 04:31 PM
 */

#ifndef HORMIGA_H
#define HORMIGA_H

#include <fstream>
#include <vector>
#include <iostream>
#include "Solucion.h"
#include "Nodo.h"
using namespace std;

class Hormiga{
    
private:
    
    Solucion solucionActual;  
    vector<Nodo*> recorrido;  
    Nodo* nodoActual; 
    
public:
    
    Hormiga() : nodoActual(nullptr) {}

    // Inicializa la hormiga en un nodo inicial
    void iniciarEnNodo(Nodo* nodoInicial, Producto& primerProducto) {
        nodoActual = nodoInicial;
        recorrido.clear();            // Limpiar el recorrido anterior
        recorrido.push_back(nodoActual); // Añadir el nodo inicial al recorrido
        
        guardarProducto(primerProducto,nodoInicial);
    }

    // Moverse al siguiente nodo
    bool moverAlSiguienteNodo(Nodo* nuevoNodo) {
        if (nuevoNodo) {
            nodoActual = nuevoNodo;    // Actualizar nodo actual
            recorrido.push_back(nodoActual); // Añadir al recorrido
            return true;
        }
        return false; 
    }

    Solucion obtenerSolucion() const {
        return solucionActual;
    }

    void guardarProducto(Producto producto, Nodo* nodo) {
        // Lógica para agregar el producto y espacio a la solución
        solucionActual.agregarProducto(nodo, producto);
    }
    
    void iniciarSolu(double a,double b){
        solucionActual = Solucion();
        solucionActual.iniciarSolu(a,b);
    }

    Nodo* obtenerNodoActual() const {
        return nodoActual;
    }

    vector<Nodo*> obtenerRecorrido() const {
        return recorrido;
    }
    
    bool esSolucionCompleta(const vector<Producto>& productos) const {
        return solucionActual.esCompleta(productos);
    }
    
    void imprimirSolucion() const{
        solucionActual.imprimirSolu();
    }
};

#endif /* HORMIGA_H */
