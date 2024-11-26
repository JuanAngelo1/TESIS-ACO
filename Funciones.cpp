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
#include <cstdlib> // Para atoi y atof

#include "Variables.h"
#include "Funciones.h"
#include "Vehiculo.h"
#include "Pedido.h"
#include "Espacio.h"
#include "Hormiga.h"
#include "Producto.h"

using namespace std;

vector<Producto> leerArchivoProductos(const char* nombreArchivo) {
    ifstream arch(nombreArchivo, ios::in);
    if (!arch) {
        cout << "ERROR: no se pudo abrir el archivo " << nombreArchivo << endl;
        exit(1);
    }

    vector<Producto> productos;
    string nombre;
    char name[200];
    int id;
    double largo,ancho,alto,pesoMax,peso;
    double lat,lon;
    char c;
    while (1){
        arch>>id;
        if(arch.eof())break;
        arch.get();
        arch.getline(name,200,',');
        arch>>peso>>c;
        arch>>largo>>c>>ancho>>c>>alto>>c>>pesoMax>>c;
        arch>>lat>>c>>lon;
        arch.get();
        
        nombre=name;
        Producto producto(id,nombre,peso,largo,ancho,alto,pesoMax,lat,lon);
        // Agregar el producto al vector
        productos.push_back(producto);
    }

    arch.close();
    return productos;
}



int obtenerCantidad(vector<Producto> productos){
    int i=0;
    for(Producto prod : productos){
        i++;
    }
    return i;
}

vector<Producto> obtenerProductosBase() {
    vector<Producto> productosBase;

    // Productos con coordenadas de destino ya asignadas
    productosBase.push_back(Producto(101, "Refrigeradora LG Top Freezer GT57BPSX", 85.5, 0.96, 0.80, 1.76, 40.0, -12.079270, -77.063227)); // Pueblo Libre
    productosBase.push_back(Producto(102, "Refrigeradora Samsung Side By Side RS52B3000M9", 93.0, 0.72, 0.97, 1.89, 50.0, -12.122452, -77.031293)); // Miraflores
    productosBase.push_back(Producto(103, "Refrigeradora MABE Side by Side No Frost Inverter", 94.0, 0.77, 0.92, 1.92, 50.0, -12.097622, -77.036002)); // San Isidro
    productosBase.push_back(Producto(104, "Refrigeradora LG Top Freezer VT37BPM", 70, 0.72, 0.73, 1.79, 40.0, -12.085846, -76.971214)); // La Molina

    productosBase.push_back(Producto(201, "Lavadora Samsung Bubble Smart WA19CG6886BVPE", 51, 0.74, 0.70, 1.17, 34.0, -12.053728, -76.948494)); // Ate
    productosBase.push_back(Producto(202, "Lavadora Mabe LMA8120WDGBB0", 47, 0.67, 0.66, 1.05, 35.0, -12.107380, -76.996883)); // San Borja
    productosBase.push_back(Producto(203, "Lavaseca LG WD9PVC4S6 AI DD", 66, 0.58, 0.66, 0.89, 40.0, -12.134781, -77.014236)); // Surquillo

    productosBase.push_back(Producto(301, "Horno Microonda Panasonic NN-GT34JBRPK", 15.4, 0.55, 0.34, 0.42, 10, -12.140356, -76.985933)); // Surco
    productosBase.push_back(Producto(302, "Horno Microondas Indurama MWI-20TCRP", 11.23, 0.48, 0.38, 0.29, 10, -12.158560, -76.989342)); // San Juan de Miraflores
    productosBase.push_back(Producto(303, "Horno Microondas LG MS2536GIS", 11.0, 0.54, 0.417, 0.294, 10, -12.054500, -77.117600)); // Callao

    productosBase.push_back(Producto(401, "Televisor TCL SMART TV 65 QLED 4K UHD", 17.3, 0.30, 1.09, 0.83 , 0.0, -12.079270, -77.063227)); // Pueblo Libre
    productosBase.push_back(Producto(402, "Televisor Samsung Smart TV 50 LED 4K UHD", 9.5, 0.25, 0.95, 0.69, 0.0, -12.122452, -77.031293)); // Miraflores
    productosBase.push_back(Producto(403, "Televisor LG Smart TV 55 Nanocell 4K UHD", 14.1, 0.23, 1.03, 0.78, 0.0, -12.097622, -77.036002)); // San Isidro
    productosBase.push_back(Producto(404, "Televisor Philips 50 4K Ultra HD Google TV", 9.31, 0.25, 0.94, 0.71, 0.0, -12.085846, -76.971214)); // La Molina

    productosBase.push_back(Producto(501, "Aspiradora Bosch Serie 4", 8.3, 0.58, 0.36, 0.31, 0, -12.053728, -76.948494)); // Ate
    productosBase.push_back(Producto(502, "Aspiradora Electrolux ERG36", 4.21, 0.15, 0.30, 0.69, 0, -12.107380, -76.996883)); // San Borja
    productosBase.push_back(Producto(503, "Aspiradora Thomas TH-1870", 5.2 , 0.33, 0.28, 0.28, 0, -12.134781, -77.014236)); // Surquillo
    productosBase.push_back(Producto(504, "Aspiradora Electrolux PTE10", 2.3, 0.27, 0.31, 1.28, 0, -12.140356, -76.985933)); // Surco

    productosBase.push_back(Producto(601, "Horno Eléctrico Modelo 1", 9.1, 0.78, 0.54, 0.54, 8, -12.158560, -76.989342)); // San Juan de Miraflores
    productosBase.push_back(Producto(602, "Horno Eléctrico Modelo 2", 7.10, 0.43, 0.51, 0.41, 6, -12.054500, -77.117600)); // Callao
    productosBase.push_back(Producto(603, "Horno Eléctrico Modelo 3", 7.25, 0.43, 0.52, 0.38, 6, -12.079270, -77.063227)); // Pueblo Libre
    productosBase.push_back(Producto(604, "Horno Eléctrico Modelo 4", 7.50, 0.42, 0.42, 0.36, 6, -12.122452, -77.031293)); // Miraflores
    productosBase.push_back(Producto(605, "Horno Eléctrico Empotrable Indurama HEI-75V2NET", 31.0, 0.57, 0.59, 0.59 , 20, -12.041548, -77.142166));

    productosBase.push_back(Producto(701, "Cocina Klimatic Munchen", 26.6, 0.552, 0.495, 0.85, 15, -12.097622, -77.036002)); // San Isidro
    productosBase.push_back(Producto(702, "Cocina MABE EMP5120GP1", 24.5, 0.540, 0.52, 0.915, 15, -12.085846, -76.971214)); // La Molina
    productosBase.push_back(Producto(703, "Cocina Indurama Parma Zafiro", 45.82, 0.636, 0.76, 0.95, 20, -12.053728, -76.948494)); // Ate
    productosBase.push_back(Producto(704, "Cocina MABE CMP5140FX0", 28.3, 0.540, 0.52, 0.925, 15, -12.107380, -76.996883)); // San Borja

    productosBase.push_back(Producto(801, "Licuadora Miray LIM-9", 1.3, 0.133, 0.22, 0.35, 0, -12.134781, -77.014236)); // Surquillo
    productosBase.push_back(Producto(802, "Licuadora Oster 250-22", 3.74, 0.23, 0.19, 0.335, 0, -12.140356, -76.985933)); // Surco
    productosBase.push_back(Producto(803, "Licuadora Thomas TH-780VR", 4.7, 0.22, 0.29, 0.38, 0, -12.158560, -76.989342)); // San Juan de Miraflores
    
    productosBase.push_back(Producto(901, "Cafetera Oster Prima Latte", 5.0, 0.32, 0.22 , 0.28, 5.0, -12.065700, -77.101260));
    productosBase.push_back(Producto(902, "Cafetera Electrolux ECM30", 6.85, 0.26, 0.32, 0.35 , 6.0, -12.143153, -77.128616));
    productosBase.push_back(Producto(903, "Cafetera Frappé Oster BVSTDC03B-053", 6.85, 0.26, 0.32, 0.35 , 6.0, -12.103733, -77.187358));
    
    productosBase.push_back(Producto(1001, "Parrilla Eléctrica Oster CKSTGR3006", 4.6, 0.17, 0.48, 0.38, 0, -12.109781, -77.073338));
    productosBase.push_back(Producto(1002, "Grill Parrillero Miray GPM-15", 2.6, 0.27, 0.52, 0.10 , 0.0, -12.057776, -77.184214));
    productosBase.push_back(Producto(1003, "Grill Oster CKSTGR4768-053", 2.7, 0.45, 0.32, 32.2, 0.0, -12.075262, -77.154321));

    productosBase.push_back(Producto(1101, "Lavavajillas Frigidaire GDPH-4515AF", 29.0, 0.62, 0.61, 0.85, 30.0, -12.160750,	-77.123898));
    productosBase.push_back(Producto(1102, "Lavavajillas Electrolux - EHFE14T2MSBXB", 48.0, 0.61, 0.60, 0.84, 40.0, -11.995199, -77.176887));
    productosBase.push_back(Producto(1103, "Lavavajilla SOLE - STILUX MAX SOLLAVAJ001V2", 45.0, 0.60, 0.60, 0.84, 40.0, -12.057169, -76.999832));

    return productosBase;
}

vector <Vehiculo> obtenerVehiculos(){
    
    vector<Vehiculo> listaVehiculos;
    
    Vehiculo vehiculo1(1,"Hyundai Mighty EX8", 3000, 4.9, 2.2, 2.2, 10);    
    Vehiculo vehiculo2(2,"Mercedes-Benz Atego 1725" ,3000, 5.5, 2.0, 2.4, 12);
    Vehiculo vehiculo3(3,"Isuzu NPR 4 TON" ,3500, 6, 2.0, 2.2, 9);
    Vehiculo vehiculo4(4,"Hyundai HD78", 4000, 6.5, 2.0, 2.2, 8);
    
    listaVehiculos.push_back(vehiculo1);
    listaVehiculos.push_back(vehiculo2);
    listaVehiculos.push_back(vehiculo3);
    listaVehiculos.push_back(vehiculo4);
    
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
    
//pp    cout<<"Volumen Pedidos:"<<ped.getVolumenTotalProductos()<<endl;

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
    mejorSol.setFitness(-100000);
    
    for(Solucion sol: soluciones){
        if(sol.getFitness()> mejorSol.getFitness())
            mejorSol=sol;
    }
    
    return mejorSol;
}

Solucion construirSolu(Grafo& grafo, vector<Producto>& productos, Hormiga& hormiga, double alpha, double beta, Vehiculo& vehiculo) {
    
    // Mapa de coordenadas a espacios ocupados durante esta construcción de solución.
    map<Coordenada, Espacio> espacios;  
    
    // Nodo inicial aleatorio para la hormiga
    Nodo* nodoActual = hormiga.obtenerNodoActual();
    
    bool encontrado=crearPrimerEspacio(hormiga,espacios,vehiculo.getAlto(),productos,vehiculo);
    
    //En caso no encuentre para
    if(!encontrado){
        hormiga.setValidez(false);
        return hormiga.obtenerSolucion();
    }
    
    int i = 0, iterSinAvance = 0, maxIterSinAvance = 40;
    bool soluEncontrada=false ,completa= false;
    
    // Recorre el grafo construyendo una solución
    while (!hormiga.esSolucionCompleta(productos) && iterSinAvance<maxIterSinAvance) {
//        cout<<"Entra"<<endl;
        vector<Arista*> aristasDisponibles = grafo.obtenerAristasDisponibles(nodoActual);
        vector<Arista*> aristasFiltradas = filtrarAristas(aristasDisponibles, productos, hormiga.obtenerSolucion());
                
        if (aristasFiltradas.empty()) {
//            cout << "No hay aristas disponibles para productos no cargados. Terminando." << endl;
            break;
        }
        
        // Seleccionar una arista basado en probabilidades de feromona y heurística
        Arista* aristaSeleccionada = calcularYSeleccionarArista(aristasFiltradas, espacios, productos, alpha, beta,vehiculo);
        
        if (!aristaSeleccionada) {
            cout << "No se pudo seleccionar una arista válida, terminando." << endl;
            break;
        }
        
        hormiga.agregarAristaSolucion(aristaSeleccionada);
        
        // Obtener el nodo destino de la arista seleccionada
        Nodo* nodoSiguiente = aristaSeleccionada->getNodoFinal();

        // Obtener el producto y coordenadas específicas para el nodo destino
        Producto& productoDestino = productos[nodoSiguiente->getIdProducto() - 1];
        Coordenada coordenadasNodoDestino(nodoSiguiente->getPosX(), nodoSiguiente->getPosY());

        // Verificar si el producto se puede colocar en un espacio existente o si necesitamos crear uno nuevo
        ResultadoEspacio resultado = buscarEspacioDisponible(espacios, productoDestino, coordenadasNodoDestino.x, coordenadasNodoDestino.y,vehiculo);

        if (resultado == PUDO_APILAR || resultado == NO_HAY_COLISION) {
            
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
            
            if(resultado == NO_SE_PUDO_APILAR || resultado == ESPACIO_INVALIDO){           
                iterSinAvance++;
            }
        }
//        cout<<iterSinAvance<<endl;
        i++;
    }
    
    completa =hormiga.esSolucionCompleta(productos);
    
    if (iterSinAvance >= maxIterSinAvance || !completa) {
        hormiga.setValidez(false);
        
    }else{
        hormiga.setValidez(true);
        soluEncontrada=true;        
    }
        
    if(soluEncontrada){
//        cout<<"Encontrada"<<endl;
        hormiga.setEspaciosSolucion(espacios);
    }
    
    return hormiga.obtenerSolucion();
}

bool crearPrimerEspacio(Hormiga& hormiga, map<Coordenada, Espacio>& espacios, double alturaVehiculo, vector<Producto>& productos, Vehiculo& vehiculo) {
    
    Nodo* nodoActual = hormiga.obtenerNodoActual();
    Producto& producto = productos[nodoActual->getIdProducto() - 1];
//    cout<<"ID: "<<producto.getIdProducto() <<"Primer Producto: "<<producto.getNombre()<<endl;
    double posX = nodoActual->getPosX();
    double posY = nodoActual->getPosY();

    // Intentar colocar el producto dentro de los límites del vehículo en cada orientación posible
    bool encontrado = false;
    for (int i = 0; i < 4; ++i) { // Máximo 4 orientaciones posibles
        if (cabeEnLimitesVehiculo(posX, posY, producto, vehiculo)) {
            encontrado = true;
            break;
        }

        // Cambiar orientación y ajustar coordenadas según la orientación actual del producto
        producto.cambiarOrientacion();
        
        // Actualizar coordenadas en función de la nueva orientación
        switch (producto.getOrientacion()) {
            case Producto::ARRIBA_DERECHA:
                break;
            case Producto::ARRIBA_IZQUIERDA:
                posX -= producto.getLargo();
                break;
            case Producto::ABAJO_DERECHA:
                posY -= producto.getAncho();
                break;
            case Producto::ABAJO_IZQUIERDA:
                posX -= producto.getLargo();
                posY -= producto.getAncho();
                break;
        }
    }

    if (!encontrado) {
        return encontrado;
    }

    // Crear un nuevo espacio con la altura y posición final del producto
    Espacio nuevoEspacio(alturaVehiculo, posX, posY, 0, 0);
    nuevoEspacio.agregarProducto(&producto);
    
    Coordenada coordenada(posX, posY);
    // Agregar el nuevo espacio al mapa de espacios
    espacios.emplace(coordenada, nuevoEspacio);
    
    return encontrado;
}

void crearNuevoEspacio(const Coordenada& coordenadas, map<Coordenada, Espacio>& espacios, Producto& producto,
                       double posX, double posY, double posZ, double alturaVehiculo) {

    // Ajustar `posX` y `posY` en función de la orientación actual del producto
    switch (producto.getOrientacion()) {
        case Producto::ARRIBA_DERECHA:
            // No se requiere ajuste
            break;
        case Producto::ARRIBA_IZQUIERDA:
            posX -= producto.getLargo(); // Mover hacia la izquierda
            break;
        case Producto::ABAJO_DERECHA:
            posY -= producto.getAncho(); // Mover hacia abajo
            break;
        case Producto::ABAJO_IZQUIERDA:
            posX -= producto.getLargo(); // Mover hacia la izquierda
            posY -= producto.getAncho(); // Mover hacia abajo
            break;
    }

    // Crear el nuevo espacio con las coordenadas ajustadas
    Espacio nuevoEspacio(alturaVehiculo, posX, posY, posZ,0);
    nuevoEspacio.agregarProducto(&producto);

    // Asignar las dimensiones del producto en el nuevo espacio
    nuevoEspacio.setLargo(producto.getLargo());
    nuevoEspacio.setAncho(producto.getAncho());

    // Agregar el nuevo espacio al mapa de espacios con las coordenadas ajustadas
    Coordenada coordAjustada(posX, posY);
    espacios.emplace(coordAjustada, nuevoEspacio);
}


bool hayColision(double xExistente, double largoExistente, double yExistente, double anchoExistente, 
                 double xNuevo, double largoNuevo, double yNuevo, double anchoNuevo) {
    // Verificar si las coordenadas del nuevo espacio caen dentro de las dimensiones del espacio existente
    bool colisionX = (xNuevo < (xExistente + largoExistente)) && ((xNuevo + largoNuevo) > xExistente);
    bool colisionY = (yNuevo < (yExistente + anchoExistente)) && ((yNuevo + anchoNuevo) > yExistente);

    // Si hay colisión en ambos ejes, retornamos true
    return colisionX && colisionY;
}


ResultadoEspacio buscarEspacioDisponible(map<Coordenada, Espacio>& espacios, Producto& producto, double posX, double posY,Vehiculo& vehiculo) {
    
    // Verificar si el producto excede los límites del vehículo en su orientación actual
    if (!cabeEnLimitesVehiculo(posX, posY, producto, vehiculo)) {
        // Intentar cambiar la orientación hasta encontrar una que permita colocar el producto
        bool encontrado = false;
        for (int i = 0; i < 4; ++i) {  // Máximo 4 orientaciones posibles
            producto.cambiarOrientacion();
            if (cabeEnLimitesVehiculo(posX, posY, producto, vehiculo)) {
                encontrado = true;
                break;
            }
        }
        // Si ninguna orientación permite que el producto quepa, retornamos un estado especial
        if (!encontrado) {
            return ESPACIO_INVALIDO;
        }
    }
    
    // Ajustar posX y posY según la orientación final del producto
    switch (producto.getOrientacion()) {
        case Producto::ARRIBA_IZQUIERDA:
            posX -= producto.getLargo(); // Mover hacia la izquierda
            break;
        case Producto::ABAJO_DERECHA:
            posY -= producto.getAncho(); // Mover hacia abajo
            break;
        case Producto::ABAJO_IZQUIERDA:
            posX -= producto.getLargo(); // Mover hacia la izquierda
            posY -= producto.getAncho(); // Mover hacia abajo
            break;
        case Producto::ARRIBA_DERECHA:
            // No se realiza ajuste
            break;
    }
        
    for (pair<const Coordenada, Espacio>& entry : espacios) {
        Coordenada coordExistente = entry.first;
        Espacio& espacioExistente = entry.second;

        // Verificar si hay colisión entre las coordenadas del nodo actual y el espacio existente
        if (hayColision(coordExistente.x, espacioExistente.getLargo(), coordExistente.y, espacioExistente.getAncho(), 
                posX, producto.getLargo(), posY, producto.getAncho())) {
            
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

bool cabeEnLimitesVehiculo(double posX, double posY, Producto& producto, Vehiculo& vehiculo) {
    switch (producto.getOrientacion()) {
        case Producto::ARRIBA_DERECHA:
            return posX + producto.getLargo() <= vehiculo.getLargo() && posY + producto.getAncho() <= vehiculo.getAncho();
        case Producto::ARRIBA_IZQUIERDA:
            return posX - producto.getLargo() >= 0 && posY + producto.getAncho() <= vehiculo.getAncho();
        case Producto::ABAJO_DERECHA:
            return posX + producto.getLargo() <= vehiculo.getLargo() && posY - producto.getAncho() >= 0;
        case Producto::ABAJO_IZQUIERDA:
            return posX - producto.getLargo() >= 0 && posY - producto.getAncho() >= 0;
        default:
            return false;
    }
}



void actualizarFeromonasOffline(const Solucion& mejorSol, Grafo& grafo, double rho, double Q) {
    double incFerom = mejorSol.getFitness()*Q;
    
    if(incFerom<0)incFerom=0;

   
    // Recorrer todas las aristas del grafo para actualizar las feromonas
    for (Arista* arista : grafo.getAristas()) {
        double feromonaActual = arista->getFeromona();
        double nuevaFeromona;

        if (mejorSol.contieneArista(arista)) {
            // Refuerza la feromona en la arista de la mejor solución
            nuevaFeromona = (1 - rho) * feromonaActual + incFerom;
        } else {
            // Evapora la feromona de las demás aristas
            nuevaFeromona = (1 - rho) * feromonaActual;
        }

        // Limita el valor de feromona para evitar sesgo extremo
        if (nuevaFeromona > 50.0) { 
            cout<<"avr"<<endl;
            nuevaFeromona = 50.0;
        }
        
        if(nuevaFeromona< 0.01){
            nuevaFeromona=0.01;
        }

        arista->setFeromona(nuevaFeromona);
    }
}

double obtenerPromedio(vector<Solucion> solus){
    
    double prom=0;
    int cant=solus.size();
    
    for(Solucion sol: solus){
        prom+=sol.getFitness();
    }
    return prom/cant;
}

void imprimirEspaciosSolucion(map<Coordenada, Espacio>& espaciosSolucion)  {
    
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

Arista* calcularYSeleccionarArista(const vector<Arista*>& aristasDisponibles, map<Coordenada, 
        Espacio>& espacios, vector<Producto>& productos, double alpha, double beta, Vehiculo &vehiculo) {
    vector<double> probabilidades;
    double sumaProbabilidades = 0.0;

    // Calcular las probabilidades de cada arista
    for (Arista* arista : aristasDisponibles) {
        Nodo* nodoDestino = arista->getNodoFinal();
        Producto& productoDestino = productos[nodoDestino->getIdProducto() - 1];
        Coordenada coordenadasNodoDestino(nodoDestino->getPosX(), nodoDestino->getPosY());

        // Calcular la heurística para el nodo destino considerando la posición actual
        double heuristica = arista->getHeuristica(productoDestino, coordenadasNodoDestino, espacios,vehiculo);
//        arista->setHeuristica(heuristica);
        // Probabilidad para la arista usando feromona y heurística
        double prob = pow(arista->getFeromona(), alpha) * pow(1.0 / heuristica, beta);
//        
//        cout<<"Feromona: "<<arista->getFeromona()<<endl;
//        cout<<"Valor Heuristica: "<<pow(1.0 / heuristica, beta)<<endl;
//        cout<<"Prob "<<prob<<endl;
        
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
//    cout<<random<<endl;
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
