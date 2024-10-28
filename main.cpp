/* 
 * File:   main.cpp
 * Autor  : Juan Angelo Flores Rubio
 * Codigo : 20196493
 * Created on 23 de septiembre de 2024, 04:04 PM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <math.h>

#include "Colonia.h"
#include "Vehiculo.h"
#include "Pedido.h"
#include "Producto.h"
#include "Grafo.h"
#include "Arista.h"
#include "Nodo.h"
#include "Espacio.h"
#include "Funciones.h"

using namespace std;

int main(int argc, char** argv) {
        
    //Inicializar Flotas Vehículos
    vector<Vehiculo> listaVehiculos = obtenerVehiculos();
    
    //Inicializar Productos Base
    vector<Producto> productosBase = obtenerProductosBase();
    
    //Inicializar cantidades para pedido prueba
    vector<int> cantidad = {1, 1, 1, 1,   // Refrigeradoras (cuatro)
                            2, 2, 2,      // Lavadoras (tres modelos)
                            2, 2, 2,      // Microondas (tres modelos)
                            1, 1, 1, 1,   // Televisores (cuatro modelos)
                            2, 2, 2, 2,   // Aspiradoras (cuatro modelos)
                            2, 2, 2, 2,   // Hornos eléctricos (cuatro modelos)
                            1, 1, 1, 1,   // Cocinas (cinco modelos)
                            2, 2, 2};     // Licuadoras (tres modelos)
    
    //Productos a cargar generados
    vector<Producto> productosCargar = generarProductos(productosBase,cantidad);
    
    //Inicializar Pedidos
    Pedido pedido1(1, productosCargar, 8, "alta");
    
    //Prueba productos a cargar
    
//    for(int i=0; i<productosCargar.size();i++){
//        productosCargar[i].mostrarInformacion();
//        cout<<endl;
//    }
    
    //En caso haya más pedidos se debera realizar bucle
//    vector<Pedido> listaPedidos;
//    listaPedidos.push_back(pedido1);
    
    //Parametros ACO
    
    int numHormigas = 100;
    int iterMax = 100;
    int tolerancia = 10;
    double alpha = 1.0;
    double beta = 2.0;
    double tasaEva = 0.5; 
    
    Colonia colonia(numHormigas,iterMax,tasaEva,alpha,beta);
    
    Vehiculo vehiculo=SeleccionarVehiculo(pedido1,listaVehiculos);
    double maxX = vehiculo.getLargo(); // Dimensión máxima X (largo)
    double maxY = vehiculo.getAncho(); // Dimensión máxima Y (ancho)
    double maxZ = vehiculo.getAlto(); // Dimensión máxima Z (altura)
    
    int posxProducto=1;
    int numIter=0;
    int sinMej=0;
    int cantNodos,numAristas;
    Solucion mejorSol;
    
    while(numIter < 1 && sinMej < tolerancia){
        cout << "Iteración: " << numIter + 1 << endl;
        
        Grafo grafo;
        cantNodos=grafo.generarNodosAleatorios(productosCargar, maxX, maxY, posxProducto);
        numAristas=cantNodos*18;
        
        grafo.generarAristasAleatorias(numAristas);
        
        grafo.conectarProductos(productosCargar.size(), posxProducto);
        
        cout<<numAristas<<endl;
        
//        grafo.mostrarGrafo();
  
        
        vector<Solucion> soluciones;
        Solucion mejorSolIter;
        
        //Las hormigas se renuevan y toman un nuevo nodo aleatorio del grafo
        colonia.inicializarColonia(grafo);
        vector<Hormiga> hormigas=colonia.getHormigas();
        Solucion solActual;
        
        
        //Aqui las hormigas recorren el grafo
        for(int h = 0 ; h < 1 ; h++){
            Hormiga& hormiga = hormigas[h];
           
            //se construye la solu
            solActual=construirSolu(grafo,productosCargar,hormiga,alpha,beta,tasaEva,vehiculo); 
            
            if(solActual.getEsValida())
                soluciones.push_back(solActual);
            }
        
        mejorSolIter = mejorSolucion(soluciones);
        
        if(mejorSolIter.getFitness() < mejorSol.getFitness()){
            mejorSol=mejorSolIter;
            sinMej=0;
        }else
            sinMej++;
        
        
        numIter++;
    }
    
}