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
#include <ctime> 

#include "Colonia.h"
#include "Vehiculo.h"
#include "Pedido.h"
#include "Producto.h"
#include "Grafo.h"
#include "Arista.h"
#include "Nodo.h"
#include "Espacio.h"
#include "Funciones.h"
#include "Coordenada.h"
#include "Rutas.h"


using namespace std;

int main(int argc, char** argv) {
        
    //Inicializar Flotas Vehículos
    vector<Vehiculo> listaVehiculos = obtenerVehiculos();
    
    //Inicializar Productos Base
    vector<Producto> productosBase = obtenerProductosBase();
    
    //Inicializar cantidades para pedido prueba
    vector<int> cantidad = {1, 0, 0, 1,   // Refrigeradoras (cuatro)
                            1, 0, 1,      // Lavadoras (tres modelos)
                            1, 0, 1,      // Microondas (tres modelos)
                            1, 0, 0, 1,   // Televisores (cuatro modelos)
                            1, 0, 0, 1,   // Aspiradoras (cuatro modelos)
                            1, 0, 0, 1,   // Hornos eléctricos (cuatro modelos)
                            1, 0, 0, 1,   // Cocinas (cinco modelos)
                            1, 0, 0};     // Licuadoras (tres modelos)
    
    //Productos a cargar generados
    vector<Producto> productosCargar = generarProductos(productosBase,cantidad);
    
    //Inicializar Pedidos
    Pedido pedido1(1, productosCargar, 8, "alta");
    
    //En caso haya más pedidos se debera realizar bucle
//    vector<Pedido> listaPedidos;
//    listaPedidos.push_back(pedido1);
     
    Vehiculo vehiculo=SeleccionarVehiculo(pedido1,listaVehiculos);
    double maxX = vehiculo.getLargo(); // Dimensión máxima X (largo)
    double maxY = vehiculo.getAncho(); // Dimensión máxima Y (ancho)
    double pesoMax= vehiculo.getPesoMaximo();
    double volMax= vehiculo.getVolMaximo();
    

    int numIter=0, sinMej=0,cantSoluciones=0;
    int cantNodos,numAristas;
    Solucion mejorSol;
    mejorSol.setFitness(-1000);
    double alpha = 1.5, beta = 2;
    double rho = 0.2; // Tasa de evaporación
    double Q = 0.5; // Constante para el depósito de feromonas
    
    double coefEsta=0.4,coefApilamiento=0.2 ,coefProximidad= 0.4,coefAccesibilidad=1; 
        
    int posxProducto=10;
    int iterMax = 30;
    
    int numHormigas = 50;
    
    int numCorrida=0,corridasMax=30;
    
    unsigned t0, t1;
 
    Colonia colonia(numHormigas,iterMax,rho,alpha,beta);
    
    //Coordenadas Tienda
    Coordenada tiendaOrigen = Coordenada(-12.077275894793303, -77.09255117444374);
    
    optimizarRuta(productosCargar,tiendaOrigen.x,tiendaOrigen.y);
    
//    for(int i=0;i<productosCargar.size();i++){
//        productosCargar[i].mostrarInformacion();
//    } 
    
    while(numCorrida < corridasMax){
        Grafo grafo;
        cantNodos=grafo.generarNodosAleatorios(productosCargar, maxX, maxY, posxProducto);
        numAristas=cantNodos*(cantNodos-1);
        mejorSol.setFitness(-1000);
//        cout<<"Cantidad Nodo: "<<cantNodos<<endl;

        grafo.generarGrafoCompleto();

        numIter=0,cantSoluciones=0;
        
        vector<Solucion> solucionesCalibracion;
        solucionesCalibracion.clear();
//        grafo.mostrarGrafo();

        while(numIter < iterMax){

            vector<Solucion> soluciones;
            Solucion mejorSolIter;

            //Las hormigas se renuevan y toman un nuevo nodo aleatorio del grafo
            colonia.inicializarColonia(grafo);
            vector<Hormiga> hormigas=colonia.getHormigas();
            Solucion solActual;

//            t0=clock();

            //Aqui las hormigas recorren el grafo
            for(int h = 0 ; h < numHormigas ; h++){
                Hormiga& hormiga = hormigas[h];

                hormiga.iniciarSolu(volMax,pesoMax,productosCargar);

                //Se construye la solu
                solActual=construirSolu(grafo,productosCargar,hormiga,alpha,beta,vehiculo); 

                if(solActual.getEsValida()){
//                    cout<<"Sol Encontrada"<<endl;
                    cantSoluciones++;
                    solActual.calcularFitness(vehiculo,coefEsta,coefApilamiento,coefProximidad,coefAccesibilidad,0);
                    soluciones.push_back(solActual);
                }
                
//                if(cantSoluciones==0 &&)
            }

//            t1=clock();

            mejorSolIter = mejorSolucion(soluciones);
            if(soluciones.size()>0){
                solucionesCalibracion.push_back(mejorSolIter);
            }

            if(mejorSolIter.getFitness() > mejorSol.getFitness()){
                mejorSol=mejorSolIter;
                sinMej=0;
            }else
                sinMej++;
            
            // Actualiza las feromonas en el grafo usando la mejor solución
            actualizarFeromonasOffline(mejorSolIter, grafo, rho, Q); 
            
            for (Solucion& sol : soluciones) {
                sol.limpiarSolucion();
            }
            
            numIter++;
                
        } 
//        cout<<"Cantidad Soluciones: "<< cantSoluciones<<endl;
//        if(cantSoluciones==0)
//            corridasMax++;
        
//        cout<<"Mejor Solución:"<<endl;
        cout<<"Mejor Fitness:"<<endl;
        mejorSol.imprimirSolu();
        double promedioCorrida=obtenerPromedio(solucionesCalibracion);
        cout<<"Promedio Fitness:"<<endl;
        cout<<promedioCorrida<<endl;
        
        
        numCorrida++;
    }
    
//    cout<<endl;
    cout<<"Cantidad de Soluciones Encontradas: "<<cantSoluciones<<endl;
//    cout<<"Mejor Solución:"<<endl;
//    
//    mejorSol.calcularFitness(vehiculo,coefEsta,coefApilamiento,coefProximidad,coefAccesibilidad,1);
//    
//    mejorSol.imprimirProductosCargados();
//    mejorSol.imprimirSolu();
//    mejorSol.imprimirEspaciosSolucion();
    
}