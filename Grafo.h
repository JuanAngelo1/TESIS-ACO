/* 
 * File:   Grafo.h
 * Autor  : Juan Angelo Flores Rubio
 * Codigo : 20196493
 * Created on 29 de septiembre de 2024, 06:14 PM
 */

#ifndef GRAFO_H
#define GRAFO_H

#include <fstream>
#include <vector>
#include <math.h>
#include <stack>
#include <unordered_set>  // Para el conjunto de productos visitados
#include <unordered_map>
#include <chrono> // Para std::chrono
#include <cmath>  // Para round()
#include <random>
#include "Grafo.h"
#include "Nodo.h"
#include "Arista.h"
#include "Producto.h"

using namespace std;

class Grafo {
private:
    vector<Nodo*> nodos;      // Lista de nodos
    vector<Arista*> aristas;  // Lista de aristas

public:
    Grafo() {
    }

    // Generar nodos aleatorios
    int generarNodosAleatorios(vector<Producto> prods, double maxX, double maxY, int posicionesPorProducto) {
        int idNodo = 0;

        auto seed = std::chrono::steady_clock::now().time_since_epoch().count(); // Obtener semilla única basada en el tiempo
        std::mt19937 rng(static_cast<unsigned>(seed));                           // Generador Mersenne Twister
        std::uniform_real_distribution<> disX(0.0, maxX);                        // Distribución uniforme para X
        std::uniform_real_distribution<> disY(0.0, maxY);    

        for (int i = 0; i < prods.size(); i++) {
            for (int j = 0; j < posicionesPorProducto; j++) {
                // Generar coordenadas aleatorias redondeadas a 2 decimales
                double x = round(disX(rng) * 100.0) / 100.0;
                double y = round(disY(rng) * 100.0) / 100.0;

                // Crear un nuevo nodo
                Nodo* nuevoNodo = new Nodo(idNodo + 1, prods[i].getIdProducto(), j, x, y, 0);
                nodos.push_back(nuevoNodo);

                idNodo++;
            }
        }

        return nodos.size(); // Retorna el total de nodos creados
    }
    
    
    void conectarProductos(int numProductos, int posicionesPorProducto) {

        for (int i = 0; i < numProductos - 1; ++i) {
            // Seleccionar aleatoriamente una posición (nodo) del producto i
            int nodo1 = rand() % posicionesPorProducto + (i * posicionesPorProducto);
            // Seleccionar aleatoriamente una posición (nodo) del producto i+1
            int nodo2 = rand() % posicionesPorProducto + ((i + 1) * posicionesPorProducto);

            Nodo* origen = nodos[nodo1];   // Nodo aleatorio de producto i
            Nodo* destino = nodos[nodo2];  // Nodo aleatorio de producto i+1

            // Verificar si ya existe una conexión entre estos nodos
            if (!existeConexion(nodo1, nodo2)) {
                // Crear una nueva arista entre los nodos seleccionados
                Arista* nuevaArista = new Arista(origen, destino);
                aristas.push_back(nuevaArista);
            }
        }
    }

        // Generar conexiones aleatorias entre nodos
    void generarAristasAleatorias(int numAristas, int minConexiones) {
        // Inicializar el generador de números aleatorios con std::chrono
        auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
        std::mt19937 rng(static_cast<unsigned>(seed));
        std::uniform_int_distribution<> dist(0, nodos.size() - 1);

        // Paso 1: Asegurar conexiones mínimas para cada nodo
        for (int i = 0; i < nodos.size(); ++i) {
            int conexionesActuales = 0;

            // Conectar el nodo actual hasta alcanzar el mínimo de conexiones requerido
            while (conexionesActuales < minConexiones) {
                int nodo2 = dist(rng); // Generar un índice aleatorio

                // Evitar conectar el nodo consigo mismo o al mismo producto
                if (nodo2 != i && nodos[i]->getIdProducto() != nodos[nodo2]->getIdProducto()) {
                    
                    cout<<"Conexion : "<<i<<" -> "<<nodo2<<endl;
                    // Verificar si ya existe la conexión para evitar duplicados
                    if (!existeConexion(i, nodo2)) {
                        Arista* nuevaArista = new Arista(nodos[i], nodos[nodo2]);
                        
                        nuevaArista->mostrarInfo(1);
                        
                        aristas.push_back(nuevaArista);
                        conexionesActuales++;
                    }
                }
            }
        }

        // Paso 2: Generar el resto de las conexiones aleatorias
//        for (int i = 0; i < numAristas; ++i) {
//            int nodo1 = dist(rng); // Generar un índice aleatorio
//            int nodo2 = dist(rng); // Generar otro índice aleatorio
//
//            // Evitar conectar nodos consigo mismos o del mismo producto
//            while (nodo2 == nodo1 || nodos[nodo1]->getIdProducto() == nodos[nodo2]->getIdProducto()) {
//                nodo2 = dist(rng);
//            }
//
//            // Verificar si la conexión no existe antes de crearla
//            if (!existeConexion(nodo1, nodo2)) {
//                Arista* nuevaArista = new Arista(nodos[nodo1], nodos[nodo2]);
//                aristas.push_back(nuevaArista);
//            }
//        }
//        cout<<"End"<<endl<<endl;
    }
    
    
    void generarGrafoCompleto() {
        int idProd1,idProd2; 
        for (int i = 0; i < nodos.size(); i++) {
            for (int j = 0; j < nodos.size(); j++) {
                
                idProd1=nodos[i]->getIdProducto();
                idProd2= nodos[j]->getIdProducto();
                if (i != j && nodos[i]->getIdProducto() != nodos[j]->getIdProducto()) {
                    // Verificar si la conexión ya existe para evitar duplicados
                    if (!existeConexion(i+1, j+1)) {
//                        cout <<"Productos: "<<idProd1<<" - "<<idProd2<<endl;
                        Arista* nuevaArista = new Arista(nodos[i], nodos[j]);
                        aristas.push_back(nuevaArista);
                    }
                }
            }
        }
    }

    
    vector<Arista*> obtenerAristasDisponibles(Nodo* nodoActual) const {
        vector<Arista*> aristasDisponibles;

        // Recorrer todas las aristas y buscar aquellas que están conectadas al nodo actual
        for (Arista* arista : aristas) {
            if (arista->getNodoInicial() == nodoActual) {
                aristasDisponibles.push_back(arista);
            }
        }

        return aristasDisponibles;  // Devolver las aristas disponibles
    }
    


    // Mostrar información del grafo
    void mostrarGrafo() const {
        cout << "Nodos:" << endl;
        for (const Nodo* nodo : nodos) {
            nodo->mostrarInfo();
        }
        cout << "Aristas:" << endl;
        int i=1;
        for (const Arista* arista : aristas) {
            arista->mostrarInfo(i);
            i++;
        }
    }

    ~Grafo() {
        for (Nodo* nodo : nodos) delete nodo;
        for (Arista* arista : aristas) delete arista;
    }
    
    Nodo* obtenerNodoAleatorio() const {
        if (nodos.empty()) {
            return nullptr;  // Si no hay nodos, devolver un puntero nulo
        }
        int indiceAleatorio = rand() % nodos.size();  // Obtener un índice aleatorio
        return nodos[indiceAleatorio];  // Devolver el nodo en ese índice
    }
    
    bool existeConexion(int idNodo1, int idNodo2) const {
        for (const Arista* arista : aristas) {
            // Verificar si existe una conexión del nodo1 al nodo2
            if (arista->getNodoInicial()->getIdNodo() == idNodo1 &&
                arista->getNodoFinal()->getIdNodo() == idNodo2) {
                return true; // Conexión ya existe
            }
        }
        return false; // No existe conexión
    }


    // Imprimir todas las aristas generadas
    void imprimirAristas() {
        cout << "Aristas generadas:" << endl;
        for (const Arista* arista : aristas) {
            int productoInicial = arista->getNodoInicial()->getIdProducto();
            int productoFinal = arista->getNodoFinal()->getIdProducto();
            cout << "Producto " << productoInicial << " conectado con Producto " << productoFinal << endl;
        }
    }
    
    vector<Arista*> getAristas()const {
        return aristas;
    } 
    
 
};

#endif /* GRAFO_H */
