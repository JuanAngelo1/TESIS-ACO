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
    void iniciarEnNodo(Nodo* nodoInicial) {
        nodoActual = nodoInicial;
        recorrido.clear();            // Limpiar el recorrido anterior
        recorrido.push_back(nodoActual); // Añadir el nodo inicial al recorrido
       
    }
    
    void imprimirRuta() const {
        cout << "Ruta seguida por la hormiga: ";
        for (const Nodo* nodo : recorrido) {
            cout << nodo->getIdProducto() << " -> ";  // Suponiendo que Nodo tiene un método getId() para obtener el identificador del nodo
        }
        cout << "Fin de la ruta" << endl;
    }
    
    bool getEsValida(){
        return true;
    }

    
    void agregarAristaSolucion(Arista *arista){
        solucionActual.agregarAristaUsada(arista);
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
    
    void setValidez(bool valido){
        solucionActual.setEsValida(valido);
    }
    
    void guardarPrimerProducto(Producto producto) {
        // Lógica para agregar el producto y espacio a la solución
        solucionActual.agregarPrimerProducto(producto);
    }
    
    void guardarProducto(Producto producto, Nodo* nodo) {
        // Lógica para agregar el producto
        solucionActual.agregarProducto(nodo, producto);
    }
    
    void iniciarSolu(double a,double b, vector<Producto> productos){
        solucionActual = Solucion();
        solucionActual.iniciarSolu(a,b);
       
        Producto& primerProducto = productos[nodoActual->getIdProducto() - 1]; 
        guardarProducto(primerProducto,nodoActual);
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
    
    void setEspaciosSolucion(const map<Coordenada, Espacio>& nuevosEspacios){
        solucionActual.setEspaciosSolucion(nuevosEspacios);
    }
};

#endif /* HORMIGA_H */
