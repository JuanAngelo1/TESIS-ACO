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
#include <map>
#include <unordered_set>
#include <math.h>
#include "Nodo.h"
#include "Producto.h"
#include "Espacio.h"
#include "Coordenada.h"
#include "Vehiculo.h"

using namespace std;

class Solucion{
    
private:
    
    vector<Nodo*> nodosOcupados;  
    vector<int> idsProductosCargados;  // Solo los IDs de los productos cargados
    map<Coordenada, Espacio> espaciosSolucion;  
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
    
    void calcularFitness(Vehiculo& vehiculo,double coefV, double coefVa, double coefEsta){
        double fitness=0;
        double volumenVehiculo= volumenTotalCargado+volRestante;
        
        double factorVolumen = (volumenTotalCargado / volumenVehiculo) * coefV;
        double factorEspacioVacio = (volRestante) * coefVa;
        double factorDesbalancePeso = calcularDesbalancePeso(vehiculo) * coefEsta;

        // Fitness basado en la fórmula que proporcionaste
        fitness = factorVolumen - factorEspacioVacio - factorDesbalancePeso;

        // Asignamos el valor del fitness a la solución actual
        setFitness(fitness);
    }
    
    double calcularDesbalancePeso(const Vehiculo& vehiculo) {
        double pesoFrontal = 0.0;
        double pesoTrasero = 0.0;

        // Definimos una coordenada límite que separe la parte frontal de la trasera
        double limiteFrontal = vehiculo.getAncho() / 2.0;

        for (pair<const Coordenada, Espacio>& espacioPar : espaciosSolucion) {
            const Coordenada& coord = espacioPar.first;
            const Espacio& espacio = espacioPar.second;

            // Sumamos el peso de los productos en este espacio
            double pesoEnEspacio = 0.0;

            // Crear una copia de la pila de productos para iterar sobre ella
            stack<Producto*> copiaPila = espacio.getPilaDeProductos();
            while (!copiaPila.empty()) {
                Producto* producto = copiaPila.top(); // Obtener el producto en la cima
                pesoEnEspacio += producto->getPeso();  // Acumular el peso
                copiaPila.pop();  // Eliminar el producto de la copia
            }

            // Clasificamos el espacio como frontal o trasero según su posición
            if (coord.y < limiteFrontal) {
                pesoFrontal += pesoEnEspacio;
            } else {
                pesoTrasero += pesoEnEspacio;
            }
        }

        // Calculamos el desbalance como la diferencia absoluta
        return abs(pesoFrontal - pesoTrasero);
    }
    
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
    
    void setEspaciosSolucion(const map<Coordenada, Espacio>& nuevosEspacios) {
        espaciosSolucion = nuevosEspacios;
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
    
    void agregarPrimerProducto(Producto producto){
        
        idsProductosCargados.push_back(producto.getIdProducto());  // Almacenar solo el ID
        
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
        
        cout<<"Fitness Solución: "<< fitness <<endl;
    }
    
    
#include <iostream>

void imprimirEspaciosSolucion() const {
    
    
    for (const pair<const Coordenada, Espacio>& par : espaciosSolucion) {
        const Coordenada& coord = par.first;
        const Espacio& espacio = par.second;

        // Imprimir las coordenadas del espacio
        cout << "Espacio en Coordenada (" << coord.x << ", " << coord.y << "):\n";

        // Crear una copia de la pila de productos para iterar
        stack<Producto*> copiaPila = espacio.getPilaDeProductos();
        int productoNum = 1;
        
        // Recorrer e imprimir cada producto en la pila
        while (!copiaPila.empty()) {
            Producto* producto = copiaPila.top();
            cout << "  Producto " << productoNum++ << ": "
                      << "ID = " << producto->getIdProducto() << ", "
                      << "Nombre = " << producto->getNombre() << ", "
                      << "Peso = " << producto->getPeso() << " kg, "
                      << "Volumen = " << producto->getVolumen() << " m3\n";
            copiaPila.pop();  // Desapilar el producto
        }

        if (productoNum == 1) {
            cout << "  (Sin productos apilados en este espacio)\n";
        }
        
        cout << "----------------------------------\n";
    }
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
