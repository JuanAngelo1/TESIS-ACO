/* 
 * File:   Funciones.cpp
 * Autor  : Juan Angelo Flores Rubio
 * Codigo : 20196493
 * Created on 30 de septiembre de 2024, 12:38 AM
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

#include "Funciones.h"
#include "Vehiculo.h"
#include "Pedido.h"
#include "Espacio.h"
#include "Hormiga.h"
#include "Producto.h"

using namespace std;


vector<Producto> obtenerProductosBase(){
    
    vector <Producto> productosBase;
    
    //Lavadoras
    Producto refri_1(101, "Refrigeradora LG Top Freezer GT57BPSX", 85.5, 0.96, 0.80, 1.76, 40.0);
    Producto refri_2(102, "Refrigeradora Samsung Side By Side RS52B3000M9", 93.0, 0.72, 0.97, 1.89, 50.0);
    Producto refri_3(103, "Refrigeradora MABE Side by Side No Frost Inverter", 94.0, 0.77, 0.92, 1.92, 50.0);
    Producto refri_4(104, "Refrigeradora LG Top Freezer VT37BPM", 70, 0.72, 0.73, 1.79, 40.0);
    
    productosBase.push_back(refri_1);
    productosBase.push_back(refri_2);
    productosBase.push_back(refri_3);
    productosBase.push_back(refri_4);

    //Lavadoras
    Producto lavadora_1(201, "Lavadora Samsung Bubble Smart WA19CG6886BVPE", 51, 0.74, 0.70, 1.17, 34.0);
    Producto lavadora_2(201, "Lavadora Mabe LMA8120WDGBB0", 47, 0.67, 0.66, 1.05, 35.0);
    Producto lavadora_3(201, "Lavaseca LG WD9PVC4S6 AI DD", 66, 0.58, 0.66, 0.89, 40.0);
    
    productosBase.push_back(lavadora_1);
    productosBase.push_back(lavadora_2);
    productosBase.push_back(lavadora_3);
    
    //Microondas
    Producto microondas_1(301, "Horno Microonda Panasonic NN-GT34JBRPK", 15.4, 0.55, 0.34, 0.42, 10);
    Producto microondas_2(302, "Horno Microondas Indurama MWI-20TCRP", 11.23, 0.488, 0.38, 0.29, 10);
    Producto microondas_3(303, "Horno Microondas LG MS2536GIS", 11.0, 0.54, 0.417, 0.294, 10);
    
    productosBase.push_back(microondas_1);
    productosBase.push_back(microondas_2);
    productosBase.push_back(microondas_3);
    
    //TV  
    Producto tv_1(401, "Televisor TCL SMART TV 65 QLED 4K UHD", 17.3, 0.30, 1.44, 89.3 , 0.0);
    Producto tv_2(402, "Televisor Samsung Smart TV 50 LED 4K UHD", 9.5, 0.23, 1.12, 69.4, 0.0);
    Producto tv_3(403, "Televisor LG Smart TV 55 Nanocell 4K UHD", 14.1, 0.23, 1.235, 78.0, 0.0);
    Producto tv_4(404, "Televisor Philips 50 4K Ultra HD Google TV", 9.31, 0.25, 1.11, 71.8, 0.0);
    
    productosBase.push_back(tv_1);
    productosBase.push_back(tv_2);
    productosBase.push_back(tv_3);
    productosBase.push_back(tv_4);
    
    //Aspiradoras
    Producto aspiradora_1(501, "Aspiradora Bosch Serie 4", 8.3, 0.58, 0.36, 0.31, 0);
    Producto aspiradora_2(502, "Aspiradora Electrolux ERG36", 4.21, 0.15, 0.30, 0.69, 0);
    Producto aspiradora_3(503, "Aspiradora Thomas TH-1870", 5.2 , 0.33, 0.28, 0.28, 0);
    Producto aspiradora_4(504, "Aspiradora Electrolux PTE10", 2.3, 0.27, 0.31, 1.28, 0);
    
    productosBase.push_back(aspiradora_1);
    productosBase.push_back(aspiradora_2);
    productosBase.push_back(aspiradora_3);
    productosBase.push_back(aspiradora_4);
    
    //Hornos
    Producto horno_1(601, "Horno Eléctrico Modelo 1", 20.1, 0.78, 0.54, 0.54, 10);
    Producto horno_2(602, "Horno Eléctrico Modelo 2", 7.10, 0.43, 0.51, 0.41, 6);
    Producto horno_3(603, "Horno Eléctrico Modelo 3", 7.25, 0.43, 0.52, 0.38, 6);
    Producto horno_4(604, "Horno Eléctrico Modelo 4", 7.50, 0.42, 0.42, 0.36, 6);
    
    productosBase.push_back(horno_1);
    productosBase.push_back(horno_2);
    productosBase.push_back(horno_3);
    productosBase.push_back(horno_4);
    
    //Cocinas
    Producto cocina_1(701, "Cocina Klimatic Munchen", 26.6, 0.552, 0.495, 0.85, 15);
    Producto cocina_2(702, "Cocina MABE EMP5120GP1", 24.5, 0.540, 0.52, 0.915, 15);
    Producto cocina_3(703, "Cocina Indurama Parma Zafiro", 45.82, 0.636, 0.76, 0.95, 20);
    Producto cocina_4(704, "Cocina MABE CMP5140FX0", 28.3, 0.540, 0.52, 0.925, 15);

    productosBase.push_back(cocina_1);
    productosBase.push_back(cocina_2);
    productosBase.push_back(cocina_3);
    productosBase.push_back(cocina_4);
    
    //Licuadoras
    Producto licuadora_1(801, "Licuadora Miray LIM-9", 1.3, 0.133, 0.225, 0.35, 0);
    Producto licuadora_2(802, "Licuadora Oster 250-22", 3.74, 0.2381, 0.1937, 0.335, 0);
    Producto licuadora_3(803, "Licuadora Thomas TH-780VR", 4.7, 0.22, 0.29, 0.38, 0);
    
    productosBase.push_back(licuadora_1);
    productosBase.push_back(licuadora_2);
    productosBase.push_back(licuadora_3);
    
    return productosBase;
    
}

vector <Vehiculo> obtenerVehiculos(){
    
    vector<Vehiculo> listaVehiculos;
    
    Vehiculo camioneta(1,"camioneta", 1000, 4.0, 2.0, 2.0, 10);    
    Vehiculo furgonetaPequena(2,"furgonetaPequena" ,800, 3.0, 1.7, 1.6, 12);
    Vehiculo furgonetaMediana(3,"furgonetaMediana" ,1200, 4.0, 1.8, 2.0, 9);
    Vehiculo furgonetaGrande(4,"furgonetaGrande", 1500, 4.5, 2.0, 2.2, 8);
    
    listaVehiculos.push_back(camioneta);
    listaVehiculos.push_back(furgonetaPequena);
    listaVehiculos.push_back(furgonetaMediana);
    listaVehiculos.push_back(furgonetaGrande);
    
    return listaVehiculos;
}

vector<Producto> generarProductos(vector<Producto>& productosBase,vector<int>& cantidades) {
    vector<Producto> productosGenerados;
    int id = 1;  

    for (int i = 0; i < productosBase.size(); i++) {
        Producto productoBase = productosBase[i];
        int cantidad = cantidades[i];

        for (int j = 0; j < cantidad; j++) {
            Producto nuevoProducto = productoBase; 
            nuevoProducto.setIdProducto(id++);
            productosGenerados.push_back(nuevoProducto);
        }
    }

    return productosGenerados;
}

Vehiculo SeleccionarVehiculo(Pedido ped, vector<Vehiculo> lista){
    
    Vehiculo vehiculoSeleccionado = lista[0];
    bool encontrado = false;

    for (Vehiculo v : lista) {
        // Primero, verificamos si la hora de salida del vehículo coincide con la prioridad
        if ((ped.getPrioridad() == "alta" && v.getHora() <= 8) ||  // Alta prioridad, vehículos que salen antes de las 8 am
            (ped.getPrioridad() == "media" && v.getHora() <= 12) ||  // Media prioridad, vehículos que salen antes del mediodía
            (ped.getPrioridad() == "baja" && v.getHora() <= 18)) {  // Baja prioridad, vehículos que salen antes de las 6 pm
            
            // Verificar si el vehículo tiene suficiente espacio para el pedido (volumen y peso)
            if (v.getVolMaximo() >= ped.getVolumenTotalProductos() && 
                v.getPesoMaximo() >= ped.getPesoTotalProductos()) {
                vehiculoSeleccionado = v;
                encontrado = true;
                break;
            }
        }
    }

    if (!encontrado) {
        // Si no encontramos un vehículo con suficiente espacio y que cumpla con la prioridad, usar otro criterio.
        // Por ejemplo, escoger el vehículo con la mayor capacidad disponible
        for (Vehiculo v : lista) {
            if (v.getVolMaximo() >= ped.getVolumenTotalProductos() && 
                v.getPesoMaximo() >= ped.getPesoTotalProductos()) {
                vehiculoSeleccionado = v;
                break;
            }
        }
    }

    return vehiculoSeleccionado;
}

Solucion mejorSolucion(vector<Solucion> soluciones){
    
    Solucion mejorSol;
    mejorSol.setFitness(-100);
    
    for(Solucion sol: soluciones){
        if(sol.getFitness()> mejorSol.getFitness())
            mejorSol=sol;
    }
    
    return mejorSol;
}

Solucion construirSolu(Grafo& grafo, vector<Producto>& productos, Hormiga& hormiga, double alpha, double beta, double tasaEva, Vehiculo& vehiculo) {
    
    // Mapa de coordenadas a espacios ocupados durante esta construcción de solución.
    map<Coordenada, Espacio> espacios;  
    
    // Nodo inicial aleatorio para la hormiga
    Nodo* nodoActual = hormiga.obtenerNodoActual();
    Producto& primerProducto = productos[nodoActual->getIdProducto() - 1]; 
    
    //Guardamos el primer Nodo y primer Producto en Hormiga
    hormiga.iniciarEnNodo(nodoActual,primerProducto);

    int i = 0, maxIter = 40;
    int iterSinAvance = 0, maxIterSinAvance = 20;

    // Recorre el grafo construyendo una solución
    while (!hormiga.esSolucionCompleta(productos) && iterSinAvance<maxIterSinAvance) {
        
        cout << "Construyendo solución, iteración " << i + 1 << endl;
        
        nodoActual->mostrarInfo();
        // Obtener Aristas del NodoActual
        
        vector<Arista*> aristasDisponibles = grafo.obtenerAristasDisponibles(nodoActual);
        vector<Arista*> aristasFiltradas = filtrarAristas(aristasDisponibles, productos, hormiga.obtenerSolucion());
        
        if (aristasFiltradas.empty()) {
            cout << "No hay aristas disponibles para productos no cargados. Terminando." << endl;
            break;
        }

        // Seleccionar una arista basado en probabilidades de feromona y heurística
        Arista* aristaSeleccionada = calcularYSeleccionarArista(aristasFiltradas, espacios, productos, alpha, beta);
        
        aristaSeleccionada->mostrarInfo(1);

        if (!aristaSeleccionada) {
            cout << "No se pudo seleccionar una arista válida, terminando." << endl;
            break;
        }

        // Obtener el nodo destino de la arista seleccionada
        Nodo* nodoSiguiente = aristaSeleccionada->getNodoFinal();

        // Obtener el producto y coordenadas específicas para el nodo destino
        Producto& productoDestino = productos[nodoSiguiente->getIdProducto() - 1];
        Coordenada coordenadasNodoDestino(nodoSiguiente->getPosX(), nodoSiguiente->getPosY());

        // Verificar si el producto se puede colocar en un espacio existente o si necesitamos crear uno nuevo
        ResultadoEspacio resultado = buscarEspacioDisponible(coordenadasNodoDestino, espacios, productoDestino, coordenadasNodoDestino.x, coordenadasNodoDestino.y);

        if (resultado == PUDO_APILAR || resultado == NO_HAY_COLISION) {
            if(resultado == PUDO_APILAR)
                cout<<"-----------Producto Apilado-----------"<<endl;
            if (resultado == NO_HAY_COLISION) {
                // Crear un nuevo espacio si no hubo colisión
                crearNuevoEspacio(coordenadasNodoDestino, espacios, productoDestino, coordenadasNodoDestino.x, coordenadasNodoDestino.y, 0, vehiculo.getAlto());
            }
            
            // Agregar el nodo destino a la solución
            hormiga.guardarProducto(productoDestino,nodoSiguiente);
            hormiga.moverAlSiguienteNodo(nodoSiguiente);
            nodoActual=nodoSiguiente;
            iterSinAvance=0;
        } else {
            if(resultado == NO_SE_PUDO_APILAR)
                cout<<"-----------NO SE PUDO APILAR-----------"<<endl;
            iterSinAvance++;
//            continue;
        }

        i++;
    }
    
    if (iterSinAvance >= maxIterSinAvance) {
        cout << "Se alcanzó el límite de iteraciones sin avance, finalizando la construcción." << endl;
    }
    
    Solucion soluFinal= hormiga.obtenerSolucion();
    soluFinal.imprimirProductosCargados();
    soluFinal.imprimirSolu();

    return hormiga.obtenerSolucion();
}



Arista* calcularYSeleccionarArista(const vector<Arista*>& aristasDisponibles, map<Coordenada, Espacio>& espacios, vector<Producto>& productos, double alpha, double beta) {
    vector<double> probabilidades;
    double sumaProbabilidades = 0.0;

    // Calcular las probabilidades de cada arista
    for (Arista* arista : aristasDisponibles) {
        Nodo* nodoDestino = arista->getNodoFinal();
        Producto& productoDestino = productos[nodoDestino->getIdProducto() - 1];
        Coordenada coordenadasNodoDestino(nodoDestino->getPosX(), nodoDestino->getPosY());

        // Calcular la heurística para el nodo destino considerando la posición actual
        double heuristica = arista->getHeuristica(productoDestino, coordenadasNodoDestino, espacios);

        // Probabilidad para la arista usando feromona y heurística
        double prob = pow(arista->getFeromona(), alpha) * pow(1.0 / heuristica, beta);
        probabilidades.push_back(prob);
        sumaProbabilidades += prob;  // Sumar la probabilidad
    }

    // Normalizar las probabilidades
    for (double& prob : probabilidades) {
        prob /= sumaProbabilidades;
    }

    // Usar la función seleccionarArista para elegir la arista basada en las probabilidades
    return seleccionarArista(probabilidades, aristasDisponibles);
}

vector<Arista*> filtrarAristas(const vector<Arista*>& aristasDisponibles, const vector<Producto>& productos, const Solucion& solucion) {
    vector<Arista*> aristasFiltradas;

    for (Arista* arista : aristasDisponibles) {
        Nodo* nodoDestino = arista->getNodoFinal();
        int idProductoDestino = productos[nodoDestino->getIdProducto() - 1].getIdProducto();

        // Verificar si el producto del nodo destino ya está en la solución
        if (!solucion.esProductoCargado(idProductoDestino)) {
            aristasFiltradas.push_back(arista);  // Solo agregar aristas que llevan a productos no cargados
        }
    }

    return aristasFiltradas;
}



Arista* seleccionarArista(const vector<double>& probabilidades, const vector<Arista*>& aristasDisponibles) {
    // Generar un número aleatorio entre 0 y 1
    double random = static_cast<double>(rand()) / RAND_MAX;
    double probAcumulada = 0.0;

    // Recorrer todas las aristas y seleccionar la que corresponde a la probabilidad acumulada
    for (int i = 0; i < probabilidades.size(); ++i) {
        probAcumulada += probabilidades[i];  // Sumar la probabilidad de la arista actual

        // Si el número aleatorio es menor a la probabilidad acumulada, seleccionamos esta arista
        if (random <= probAcumulada) {
            return aristasDisponibles[i];
        }
    }
    // Si no se seleccionó ninguna arista (por redondeo o error), devolver la última
    return aristasDisponibles.back();
}


bool hayColision(double xExistente, double largoExistente, double yExistente, double anchoExistente, 
                 double xNuevo, double largoNuevo, double yNuevo, double anchoNuevo) {
    // Verificar si las coordenadas del nuevo espacio caen dentro de las dimensiones del espacio existente
    bool colisionX = (xNuevo < (xExistente + largoExistente)) && ((xNuevo + largoNuevo) > xExistente);
    bool colisionY = (yNuevo < (yExistente + anchoExistente)) && ((yNuevo + anchoNuevo) > yExistente);

    // Si hay colisión en ambos ejes, retornamos true
    return colisionX && colisionY;
}


ResultadoEspacio buscarEspacioDisponible(const Coordenada& coordenadasNodo, map<Coordenada, Espacio>& espacios, Producto& producto, double posX, double posY) {
    for (pair<const Coordenada, Espacio>& entry : espacios) {
        Coordenada coordExistente = entry.first;
        Espacio& espacioExistente = entry.second;

        // Verificar si hay colisión entre las coordenadas del nodo actual y el espacio existente
        if (hayColision(coordExistente.x, espacioExistente.getLargo(), coordExistente.y, espacioExistente.getAncho(), posX, producto.getLargo(), posY, producto.getAncho())) {
            
            // Si hay colisión, verificar si el producto puede ser apilado en ese espacio
            if (espacioExistente.esApilable(&producto)) {
                espacioExistente.agregarProducto(&producto);  // Apilar el producto en el espacio existente
                return PUDO_APILAR;  // Producto apilado correctamente
            } else {
                return NO_SE_PUDO_APILAR;  // No se pudo apilar el producto por restricciones
            }
        }
    }

    return NO_HAY_COLISION;  // No se encontró colisión con ningún espacio existente
}


void crearNuevoEspacio(const Coordenada& coordenadas, map<Coordenada, Espacio>& espacios, Producto& producto, 
        double posX, double posY, double posZ, double alturaVehiculo) {
    
    // Crear un nuevo espacio con la altura del primer producto
    Espacio nuevoEspacio(alturaVehiculo, posX, posY, posZ, producto.getAltura());
    
    // Asignar las dimensiones del primer producto
    nuevoEspacio.setLargo(producto.getLargo());
    nuevoEspacio.setAncho(producto.getAncho());

    // Agregar el nuevo espacio al mapa de espacios
    espacios.emplace(coordenadas, nuevoEspacio);

}



