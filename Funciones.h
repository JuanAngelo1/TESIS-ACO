/* 
 * File:   Funciones.h
 * Autor  : Juan Angelo Flores Rubio
 * Codigo : 20196493
 * Created on 30 de septiembre de 2024, 12:38 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "Vehiculo.h"
#include "Pedido.h"
#include "Grafo.h"
#include "Hormiga.h"
#include "Producto.h"
#include "Solucion.h"
#include <fstream>
using namespace std;

enum ResultadoEspacio {
    PUDO_APILAR,
    NO_SE_PUDO_APILAR,
    NO_HAY_COLISION,
    ESPACIO_INVALIDO
};

vector<Producto> leerArchivoProductos(const char* nombreArchivo);

int obtenerCantidad(vector<Producto> productos);

Vehiculo SeleccionarVehiculo(Pedido , vector<Vehiculo>);

bool VerificarCompatibilidad(TipoProducto& ,Espacio& );

void ActualizarEspacio(Espacio& , TipoProducto& , bool );

Solucion mejorSolucion(vector<Solucion> );

vector<Producto> generarProductos(vector<Producto>& ,vector<int>& );

vector<Producto> obtenerProductosBase();

vector <Vehiculo> obtenerVehiculos();

Solucion construirSolu(Grafo& , vector<Producto>& , Hormiga& , double , double , Vehiculo& );

Arista* seleccionarArista(const vector<double>& , const vector<Arista*>& );

Arista* calcularYSeleccionarArista(const vector<Arista*>& , map<Coordenada, Espacio>& ,
        vector<Producto>& , double , double ,Vehiculo&);

bool cabeEnLimitesVehiculo(double , double , Producto& , Vehiculo& );

bool hayColision(double , double , double , double ,
                 double , double , double , double );

ResultadoEspacio buscarEspacioDisponible(map<Coordenada, Espacio>& , 
        Producto& , double , double , Vehiculo& );

void crearNuevoEspacio(const Coordenada& , map<Coordenada, Espacio>& , Producto& , 
        double , double , double , double );

vector<Arista*> filtrarAristas(const vector<Arista*>& , const vector<Producto>& , const Solucion& );

bool crearPrimerEspacio(Hormiga& , map<Coordenada, Espacio>& , double , vector<Producto>& productos, Vehiculo& );

void imprimirEspaciosSolucion(map<Coordenada, Espacio>& );

void actualizarFeromonasOffline(const Solucion& , Grafo& , double , double );

double obtenerPromedio(vector<Solucion> );

#endif /* FUNCIONES_H */
