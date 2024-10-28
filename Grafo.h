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
        srand(static_cast<unsigned>(time(0)));  // Inicializamos el generador de números aleatorios
    }

    // Generar nodos aleatorios
    int generarNodosAleatorios(vector<Producto> prods, double maxX, double maxY, int posicionesPorProducto) {
        int idNodo=0;
        
        for (int i = 0; i < prods.size(); i++) {
            for (int j = 0; j < posicionesPorProducto; j++) {  // Generar varias posiciones por producto
                double x = round((static_cast<double>(rand()) / RAND_MAX * maxX) * 100.0) / 100.0;  // Redondear a 2 decimales
                double y = round((static_cast<double>(rand()) / RAND_MAX * maxY) * 100.0) / 100.0;
                Nodo* nuevoNodo = new Nodo(idNodo+1,prods[i].getIdProducto(),j,x, y, 0);  
                nodos.push_back(nuevoNodo);
            }
        }
        return nodos.size();
    }
    
    void conectarProductos(int numProductos, int posicionesPorProducto) {
        // Conectar los 46 productos de forma secuencial
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
        // Paso 1: Asegurar conexiones mínimas para cada nodo
        for (int i = 0; i < nodos.size(); ++i) {
            int conexionesActuales = 0;

            // Conectar el nodo actual hasta alcanzar el mínimo de conexiones requerido
            while (conexionesActuales < minConexiones) {
                int nodo2 = rand() % nodos.size();

                // Evitar conectar el nodo consigo mismo o al mismo producto
                if (nodo2 != i && nodos[i]->getIdProducto() != nodos[nodo2]->getIdProducto()) {
                    // Verificar si ya existe la conexión para evitar duplicados
                    if (!existeConexion(i, nodo2)) {
                        Arista* nuevaArista = new Arista(nodos[i], nodos[nodo2]);
                        aristas.push_back(nuevaArista);
                        conexionesActuales++;
                    }
                }
            }
        }

        // Paso 2: Generar el resto de las conexiones aleatorias
        for (int i = 0; i < numAristas; ++i) {
            int nodo1 = rand() % nodos.size();
            int nodo2 = rand() % nodos.size();

            // Evitar conectar nodos consigo mismos o del mismo producto
            while (nodo2 == nodo1 || nodos[nodo1]->getIdProducto() == nodos[nodo2]->getIdProducto()) {
                nodo2 = rand() % nodos.size();
            }

            // Verificar si la conexión no existe antes de crearla
            if (!existeConexion(nodo1, nodo2)) {
                Arista* nuevaArista = new Arista(nodos[nodo1], nodos[nodo2]);
                aristas.push_back(nuevaArista);
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
            // Verificar si existe una conexión entre idNodo1 y idNodo2 en ambas direcciones
            if ((arista->getNodoInicial()->getIdNodo() == idNodo1 && arista->getNodoFinal()->getIdNodo() == idNodo2) ||
                (arista->getNodoInicial()->getIdNodo() == idNodo2 && arista->getNodoFinal()->getIdNodo() == idNodo1)) {
                return true;  // Conexión ya existe
            }
        }
        return false;  // No existe conexión
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
    
 
    
};

#endif /* GRAFO_H */
