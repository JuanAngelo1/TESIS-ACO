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
                            1, 0, 1, 1,   // Televisores (cuatro modelos)
                            1, 0, 1, 1,   // Aspiradoras (cuatro modelos)
                            1, 0, 1, 0,   // Hornos eléctricos (cuatro modelos)
                            1, 0, 1, 1,   // Cocinas (cinco modelos)
                            1, 1, 1};     // Licuadoras (tres modelos)
    
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
    
    int posxProducto=3;
    int numIter=0, sinMej=0,cantSoluciones=0;
    int cantNodos,numAristas;
    Solucion mejorSol;
    mejorSol.setFitness(-1000);
    Solucion solAnterior;
    solAnterior.setFitness(-1000);
    double alpha = 1.6, beta = 0.2;
    double rho = 0.15; // Tasa de evaporación
    double Q = 0.3; // Constante para el depósito de feromonas
    
    double coefEsta=0.2,coefApilamiento=0.3 ,coefProximidad= 0.4,coefAccesibilidad=0.2; 
    int iterMax = 70, tolerancia = 30;
    
    int numHormigas = 100;
    
    int numCorrida=0,corridasMax=5;
    
    unsigned t0, t1;
 
    Colonia colonia(numHormigas,iterMax,rho,alpha,beta);
    
    //Coordenadas Tienda
    Coordenada tiendaOrigen = Coordenada(-12.077275894793303, -77.09255117444374);
    
    optimizarRuta(productosCargar,tiendaOrigen.x,tiendaOrigen.y);
    
//    for(int i=0;i<productosCargar.size();i++){
//        productosCargar[i].mostrarInformacion();
//    } 
    
//    cout<<"Ancho: "<<vehiculo.getAncho()<<endl;
//    cout<<"Largo: "<<vehiculo.getLargo()<<endl;
    while(numCorrida < corridasMax){
        cout<<"Corrida "<< numCorrida+1<<endl;
        Grafo grafo;
        cantNodos=grafo.generarNodosAleatorios(productosCargar, maxX, maxY, posxProducto);
        numAristas=cantNodos*(cantNodos-1);

        grafo.generarAristasAleatorias(numAristas,50);
        grafo.conectarProductos(productosCargar.size(), posxProducto);
        
        numIter=0,sinMej=0;
        
        while(numIter < iterMax && sinMej < tolerancia){

            vector<Solucion> soluciones;
            Solucion mejorSolIter;

            //Las hormigas se renuevan y toman un nuevo nodo aleatorio del grafo
            colonia.inicializarColonia(grafo);
            vector<Hormiga> hormigas=colonia.getHormigas();
            Solucion solActual;

            t0=clock();

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
            }

            t1=clock();

            mejorSolIter = mejorSolucion(soluciones);
            
            if(mejorSolIter.getFitness() > mejorSol.getFitness()){
                mejorSol=mejorSolIter;
                sinMej=0;
            }else
                sinMej++;
            
            // Actualiza las feromonas en el grafo usando la mejor solución
            actualizarFeromonasOffline(mejorSolIter, grafo, rho, Q); 

            //PRUEBA CAJA BLANCA PARA ITERACIONES

//            double fitnessProm=obtenerPromedio(soluciones);
//            if(soluciones.size()>=1 ){
//                cout<< "Corrida: "<<numCorrida + 1<<endl;
//                cout <<"Iteración: " << numIter + 1<<endl;
//                cout <<"Aristas Evaluadas: "<<contadorAristas<<endl;
//                cout <<"Soluciones validas: "<<soluciones.size()<<endl;
//                cout <<"Incremento Feromona Total: "<<incrementoFeromona<<endl;
//                cout <<"Fitness Promedio: "<< fitnessProm<<endl;
//                cout <<"Mejor Fitness Iteracion: "<< mejorSolIter.getFitness()<<endl;
//                double time = (double(t1-t0)/CLOCKS_PER_SEC);
//                cout << "Execution Time: " << time << endl;
//                cout<<endl;
//                solAnterior=mejorSolIter;
//            }

            // Limpiar los datos innecesarios en cada solución después de actualizar feromonas
   
            for (Solucion& sol : soluciones) {
                sol.limpiarSolucion();
            }
            
            numIter++;
        } 
        cout<<"Cantidad Soluciones: "<< cantSoluciones<<endl;
        numCorrida++;
    }
    
    cout<<endl;
    cout<<"Cantidad de Soluciones Encontradas: "<<cantSoluciones<<endl;
    cout<<"Mejor Solución:"<<endl;
    mejorSol.imprimirProductosCargados();
    mejorSol.imprimirSolu();
    mejorSol.imprimirEspaciosSolucion();
    
}