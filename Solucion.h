/* 
 * File:   Solucion.h
 * Autor  : Juan Angelo Flores Rubio
 * Codigo : 20196493
 * Created on 29 de septiembre de 2024, 04:31 PM
 */

#ifndef SOLUCION_H
#define SOLUCION_H

#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm> 
#include <unordered_set>
#include "Nodo.h"
#include "Producto.h"


using namespace std;

class Solucion{
    
private:
    
    vector<Nodo*> nodosOcupados;  
    vector<int> idsProductosCargados;  // Solo los IDs de los productos cargados
    double pesoTotalCargado;      
    double volumenTotalCargado;   
    double volRestante;
    double pesoRestante;
    double fitness;              
    bool esValida;              
    
public:
    
    Solucion() : pesoTotalCargado(0), volumenTotalCargado(0), volRestante(0),pesoRestante(0), fitness(0), esValida(false) {}

    Solucion(double volumenDisponible, double pesoDisponible) 
        : volRestante(volumenDisponible),pesoRestante(pesoDisponible), pesoTotalCargado(0), volumenTotalCargado(0), fitness(0), esValida(true) {}

    bool esNodoValido(Nodo* nodo, Producto producto) {
        for (const Nodo* nodoOcupado : nodosOcupados) {
            if (nodo->posicionIgual(*nodoOcupado)) {
                return false;  // Superposición de posiciones
            }
        }

        if (producto.getVolumen() > volRestante && producto.getPeso() > pesoRestante) {
            return false;  // No hay espacio suficiente
        }

        return true;
    }
    
    void agregarNodo(Nodo *nodo){
        nodosOcupados.push_back(nodo);
    }

    void agregarProducto(Nodo* nodo, Producto producto) {
        idsProductosCargados.push_back(producto.getIdProducto());  // Almacenar solo el ID
        nodosOcupados.push_back(nodo);  // Continuar almacenando los nodos

        volumenTotalCargado += producto.getVolumen();
        volRestante -= producto.getVolumen();
        
        pesoTotalCargado += producto.getPeso();
        pesoRestante -= producto.getPeso();

    }
    
    void iniciarSolu(double vol, double peso){
        pesoRestante=peso;
        volRestante=vol;
        volumenTotalCargado=0;
        pesoTotalCargado=0;
    }

    // Método para obtener el fitness (lo puedes ajustar según los criterios de optimización que desees)
    void calcularFitness() {
        fitness = volumenTotalCargado / (volumenTotalCargado + volRestante);
    }

    // Método para verificar si la solución es válida
    bool esSolucionValida() const {
        return esValida;
    }
    
    bool esCompleta(const vector<Producto>& productos) const {
        // Verificar si todos los productos necesarios están en el vector de IDs cargados
        for (const Producto& producto : productos) {
            if (!esProductoCargado(producto.getIdProducto())) {
                return false;  // Si algún producto no está cargado, la solución no está completa
            }
        }
        // Si todos los productos están cargados, la solución está completa
        return true;
    }
    
    bool esProductoCargado(int idProducto) const {
        return find(idsProductosCargados.begin(), idsProductosCargados.end(), idProducto) != idsProductosCargados.end();
    }
    
    void imprimirProductosCargados() const {
        cout << "IDs de productos cargados: ";
        int i=0;
        for (int id : idsProductosCargados) {
            cout << id << " ";
            i++;
        }
        cout <<endl;
        cout<<"Cantidad Productos: "<<i<<endl;
    }
    
    void imprimirSolu() const{
        
        cout<<"Peso Cargado: "<< pesoTotalCargado <<endl;
        cout<<"Peso Restante: "<< pesoRestante <<endl<<endl;

        cout<<"Volumen Cargado: "<< volumenTotalCargado<<endl;
        cout<<"Volumen Restante: "<< volRestante <<endl<<endl;
    }



    // Getters para obtener información de la solución
    double getPesoTotalCargado() const { return pesoTotalCargado; }
    double getVolumenTotalCargado() const { return volumenTotalCargado; }
    double getEspacioRestante() const { return volRestante; }
    double getFitness() const { return fitness; }
    double getPesoRestante() const {return pesoRestante;}
    bool getEsValida() const {return esValida;}
    vector<Nodo*> getNodosOcupados() const { return nodosOcupados; }
    vector<int> getidsProducto()const {return idsProductosCargados;}
    
        // Setters
    void setPesoTotalCargado(double peso) {
        pesoTotalCargado = peso;
    }

    void setVolumenTotalCargado(double volumen) {
        volumenTotalCargado = volumen;
    }

    void setVolumenRestante(double espacio) {
        volRestante = espacio;
    }
    
    void setPesoRestante(double espacio) {
        pesoRestante = espacio;
    }

    void setFitness(double f) {
        fitness = f;
    }

    void setEsValida(bool validez) {
        esValida = validez;
    }
    
    
};

#endif /* SOLUCION_H */
