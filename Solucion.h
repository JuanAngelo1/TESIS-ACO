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
#include <cmath>
#include "Nodo.h"
#include "Arista.h"
#include "Producto.h"
#include "Espacio.h"
#include "Coordenada.h"
#include "Vehiculo.h"

using namespace std;

class Solucion{
    
private:
    
    vector<Nodo*> nodosOcupados; 
    vector<Arista*> aristasUsadas;
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
    
    
    void limpiarSolucion() {
        nodosOcupados.clear();
        aristasUsadas.clear();
        
        // Opcionalmente podrías liberar memoria de los vectores si es crítico
        nodosOcupados.shrink_to_fit();
        aristasUsadas.shrink_to_fit();
        idsProductosCargados.shrink_to_fit();
    }

    
    bool contieneArista(Arista* arista) const {
        return find(aristasUsadas.begin(), aristasUsadas.end(), arista) != aristasUsadas.end();
    }
    
    void agregarAristaUsada(Arista* arista) {
        aristasUsadas.push_back(arista);
    }
    
    double calcularDistanciaEuclidiana(double x1, double y1, double x2, double y2) {
        return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    }
    
    double calcularPenalizacionProximidadPuerta(double largoVehiculo, double anchoVehiculo) {
        // Coordenada de la puerta trasera del vehículo, en el lado derecho (x = largoVehiculo)
        Coordenada puerta(largoVehiculo, anchoVehiculo / 2.0);
        double penalizacionTotal = 0.0;

        for (pair<const Coordenada, Espacio>& par : espaciosSolucion) {
            const Coordenada& posicionProducto = par.first;
            const Espacio& espacio = par.second;

            // Si el espacio tiene productos, iteramos sobre ellos para calcular la penalización
            if (!espacio.estaVacio()) {
                stack<Producto*> productos = espacio.getPilaDeProductos();

                // Crear una copia de la pila de productos para no perder datos
                stack<Producto*> copiaPila = productos;

                while (!copiaPila.empty()) {
                    Producto* producto = copiaPila.top();
                    int ordenEntrega = producto->getOrden();  // Obtener el orden de entrega del producto

                    // Calcular la distancia euclidiana a la puerta trasera
                    double distancia = calcularDistanciaEuclidiana(
                        puerta.x, puerta.y,
                        posicionProducto.x, posicionProducto.y
                    );

                    // Penalización proporcional al orden de entrega: penaliza más si el orden es menor y el producto está lejos de la puerta
                    penalizacionTotal += distancia * (1.0 / ordenEntrega);

                    copiaPila.pop();  // Eliminar el producto de la copia
                }
            }
        }

        return penalizacionTotal;
    }

    void calcularFitness(Vehiculo& vehiculo, double coefEsta, double coefApilamiento, double coefProximidad, double coefAccesibilidad,int debug) {
        double fitness = 0;

        // Desbalance de peso
        double factorDesbalancePeso = calcularDesbalancePeso(vehiculo) * coefEsta/10;

        // Bonus por apilamiento
        double factorBonusApilamiento = calcularBonusApilamiento() * coefApilamiento;

        // Factor de proximidad: premiar si el promedio de distancia es bajo
        double factorProx=calcularFactorProximidad();
        
        double factorProximidad = (factorProx > 0) ? (1.0 / factorProx) * 100 *coefProximidad : 0.0;

        // Penalización por accesibilidad para el orden de entrega
        double penalizacionAccesibilidad = calcularPenalizacionProximidadPuerta(vehiculo.getLargo(),vehiculo.getAncho()) * coefAccesibilidad*10;
        
        
        // Cálculo final del fitness
        fitness = factorBonusApilamiento + factorProximidad - penalizacionAccesibilidad - factorDesbalancePeso + 10;

        // Asignar el fitness a la solución actual
        setFitness(fitness);
        
//        if(debug==1){
//            
//            cout<<"Bonus Apilamiento: "<<factorBonusApilamiento<<endl;
//            cout<<"Cantidad Apilados: "<<calcularBonusApilamiento()<<endl;
//
//            cout<<"Bonus Proximidad: "<<factorProximidad<<endl;
//            cout<<"Factor Proximidad:"<<factorProx<<endl;
//
//            cout<<"Penalización Accesibilidad: " << penalizacionAccesibilidad << endl;
//            cout<<"Calculo Accesabildiad: "<< calcularPenalizacionProximidadPuerta(vehiculo.getLargo(),vehiculo.getAncho())<<endl;
//
//            cout<<"Penalizacion Desbalance: "<<factorDesbalancePeso<<endl;
//            cout<<"Desbalance KG"<<calcularDesbalancePeso(vehiculo)<<endl;
//
//            cout<<"Fitness: "<<fitness<<endl;
//        }


    }
    
    double calcularFactorProximidad() {
        double sumaDistancias = 0.0;
        int count = 0;

        // Iterar sobre cada par de espacios en espaciosSolucion
        for (map<Coordenada, Espacio>::iterator it1 = espaciosSolucion.begin(); it1 != espaciosSolucion.end(); ++it1) {
            map<Coordenada, Espacio>::iterator it2 = it1;
            ++it2; // Empezamos it2 en la siguiente posición después de it1
            for (; it2 != espaciosSolucion.end(); ++it2) {
                const Coordenada& coord1 = it1->first;
                const Coordenada& coord2 = it2->first;

                // Calcular la distancia euclidiana entre coord1 y coord2
                double distancia = sqrt(pow(coord1.x - coord2.x, 2) + pow(coord1.y - coord2.y, 2));
                sumaDistancias += distancia;
                count++;
            }
        }

        // Si hay al menos un par, devolver la distancia promedio; de lo contrario, devolver 0.0
        return (count > 0) ? sumaDistancias / count : 0.0;
    }


    double calcularBonusApilamiento() {
        double bonusApilamiento = 0.0;
        for (pair<const Coordenada, Espacio>& parEspacio : espaciosSolucion) {
            const Espacio& espacio = parEspacio.second;
            int cant=espacio.getPilaDeProductos().size();
            if (cant > 1) {  // Si hay más de un producto en el espacio, es apilado
                bonusApilamiento += 10 * (cant - 1); // Suma un bonus por cada producto adicional en el apilamiento
            }
        }
        return bonusApilamiento;
    }


    
    double calcularDesbalancePeso(const Vehiculo& vehiculo) {
    double pesoFrontal = 0.0;
    double pesoTrasero = 0.0;

    // Definimos un límite en el eje X para dividir la parte frontal de la trasera
    double limiteFrontal = vehiculo.getLargo() / 2.0;

    for (map<Coordenada, Espacio>::const_iterator it = espaciosSolucion.begin(); it != espaciosSolucion.end(); ++it) {
        const Coordenada& coord = it->first;
        const Espacio& espacio = it->second;

        // Sumamos el peso de los productos en este espacio
        double pesoEnEspacio = 0.0;
        stack<Producto*> copiaPila = espacio.getPilaDeProductos();
        
        while (!copiaPila.empty()) {
            Producto* producto = copiaPila.top();
            pesoEnEspacio += producto->getPeso();
            copiaPila.pop();
        }

        // Usamos el eje X para clasificar el peso como frontal o trasero
        if (coord.x < limiteFrontal) {
            pesoFrontal += pesoEnEspacio;
        } else {
            pesoTrasero += pesoEnEspacio;
        }
    }

    // Debugging para verificar los pesos en cada solución
//    cout << "Debug - Peso Frontal: " << pesoFrontal << ", Peso Trasero: " << pesoTrasero << endl;

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
    const vector<Arista*>& getAristasUsadas() const {
        return aristasUsadas;
    }
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
