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
    vector<int> cantidad = {1, 1, 0, 1,   // Refrigeradoras (cuatro)
                            0, 0, 1,      // Lavadoras (tres modelos)
                            0, 1, 0,      // Microondas (tres modelos)
                            1, 1, 1, 1,   // Televisores (cuatro modelos)
                            1, 1, 1, 1,   // Aspiradoras (cuatro modelos)
                            1, 0, 1, 0,   // Hornos eléctricos (cuatro modelos)
                            1, 0, 1, 0,   // Cocinas (cinco modelos)
                            1, 1, 1};     // Licuadoras (tres modelos)
    
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
 
    double coefV=0.65,coefVa=0.10;
    
    Vehiculo vehiculo=SeleccionarVehiculo(pedido1,listaVehiculos);
    double maxX = vehiculo.getLargo(); // Dimensión máxima X (largo)
    double maxY = vehiculo.getAncho(); // Dimensión máxima Y (ancho)
    double pesoMax= vehiculo.getPesoMaximo();
    double volMax= vehiculo.getVolMaximo();
    
    int posxProducto=3;
    int numIter=0, sinMej=0,cantSoluciones=0;
    int cantNodos,numAristas;
    Solucion mejorSol;
    mejorSol.setFitness(-10000);
    
    double alpha = 1.6, beta = 0.3;
    double rho = 0.5; // Tasa de evaporación
    double Q = 100.0; // Constante para el depósito de feromonas
    
    double coefEsta=0.5;
    double coefApilamiento=0.5 ,coefProximidad= 10,coefAccesibilidad=0;
    int iterMax = 70, tolerancia = 40;

    int numHormigas = 60;
        
    Colonia colonia(numHormigas,iterMax,rho,alpha,beta);
    
    while(numIter < iterMax && sinMej < tolerancia){
//        cout << "Iteración: " << numIter + 1 << endl;
        
        Grafo grafo;
        cantNodos=grafo.generarNodosAleatorios(productosCargar, maxX, maxY, posxProducto);
        numAristas=cantNodos*30;
        
        grafo.generarAristasAleatorias(numAristas,50);
        grafo.conectarProductos(productosCargar.size(), posxProducto);
        
//        cout<<numAristas<<endl;
      
        vector<Solucion> soluciones;
        Solucion mejorSolIter;
        
        //Las hormigas se renuevan y toman un nuevo nodo aleatorio del grafo
        colonia.inicializarColonia(grafo);
        vector<Hormiga> hormigas=colonia.getHormigas();
        Solucion solActual;
        
        //Aqui las hormigas recorren el grafo
        for(int h = 0 ; h < numHormigas ; h++){
            Hormiga& hormiga = hormigas[h];

            hormiga.iniciarSolu(volMax,pesoMax,productosCargar);
            
            //Se construye la solu
            solActual=construirSolu(grafo,productosCargar,hormiga,alpha,beta,vehiculo); 
            
            if(solActual.getEsValida()){ 
                cantSoluciones++;
                cout<<"Solucion Encontrada #"<<cantSoluciones<<endl;
                solActual.calcularFitness(vehiculo,coefEsta,coefApilamiento,coefProximidad,coefAccesibilidad);
                soluciones.push_back(solActual);
            }  
        }
        
        mejorSolIter = mejorSolucion(soluciones);
        
        if(mejorSolIter.getFitness() > mejorSol.getFitness()){
            mejorSol=mejorSolIter;
            sinMej=0;
        }else
            sinMej++;
         
        // Actualiza las feromonas en el grafo usando la mejor solución
        actualizarFeromonasOffline(mejorSolIter, grafo, rho, Q); // Usa la mejor solución directamente
        
        // Limpiar los datos innecesarios en cada solución después de actualizar feromonas
        for (Solucion& sol : soluciones) {
            sol.limpiarSolucion();
        }
    
        numIter++;
    }
    
        cout<<"Cantidad de Soluciones Encontradas: "<<cantSoluciones<<endl;
        cout<<"FINAL:"<<endl;
        mejorSol.imprimirProductosCargados();
        mejorSol.imprimirSolu();
        mejorSol.imprimirEspaciosSolucion();
        
}