/* 
 * File:   Arista.h
 * Autor  : Juan Angelo Flores Rubio
 * Codigo : 20196493
 * Created on 29 de septiembre de 2024, 11:31 AM
 */

#ifndef ARISTA_H
#define ARISTA_H

#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm> 
#include <map>
#include <unordered_set>
#include <math.h>
#include <cmath>
#include "Nodo.h"
#include "Vehiculo.h"
#include "Coordenada.h"

using namespace std;

class Arista{
   
private:
   
    Nodo* nodoOrigen;         
    Nodo* nodoDestino;         
    double feromona;
    double costo;                  
    
public:
    
    Arista(Nodo* origen, Nodo* destino, double feromonaInicial = 1.0, double heuristica= 1.0)
        : nodoOrigen(origen), nodoDestino(destino), feromona(feromonaInicial),costo(heuristica) {
        
    }

    double getFeromona() const { return feromona; }
    double getCosto() const { return costo; }

    void setFeromona(double nuevaFeromona) {
        feromona = nuevaFeromona;
    }
    
    void setHeuristica(double heu){
        costo=heu;
    }

    void mostrarInfo(int i) const {
        cout <<i<<"-"<<"Arista entre productos " << nodoOrigen->getIdProducto()<<" (Nodo "<<nodoOrigen->getIdNodo()<<")" 
             << " (Posición " << nodoOrigen->getPosicionProducto()+1 << ") y " 
             << nodoDestino->getIdProducto() <<" (Nodo "<<nodoDestino->getIdNodo()<<")"
             << " (Posición " << nodoDestino->getPosicionProducto()+1 << ")"
             << " - Feromona: " << feromona 
             << " - Costo (heurística): " << costo << endl;
    }
    
    Nodo* getNodoInicial() const {
        return nodoOrigen;
    }

    // Método para obtener el nodo final (nodo destino)
    Nodo* getNodoFinal() const {
        return nodoDestino;
    }
    
        
    double calcularDistanciaEuclidiana(double x1, double y1, double x2, double y2)const {
        return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    }

    
    double calcularProximidadPuertaProducto( Vehiculo& vehiculo,  Coordenada& posicionProducto,  Producto& productoDestino) const{
        Coordenada puerta(vehiculo.getLargo(), vehiculo.getAncho() / 2.0);
        double distancia = this->calcularDistanciaEuclidiana(
            puerta.x, puerta.y,
            posicionProducto.x, posicionProducto.y
        );
        int ordenEntrega = productoDestino.getOrden();
        return distancia * (1.0 / ordenEntrega);  // Consistente con la fórmula del fitness
    }
    
    double getHeuristica(Producto& productoDestino, Coordenada& coordenadasNodoDestino, map<Coordenada, Espacio>& espacios, Vehiculo &vehiculo) {
        double heuristica = 1.0;  // Valor neutro inicial

        // 1. Calcular penalización por proximidad a la puerta
        double penalizacionPuerta = calcularProximidadPuertaProducto(vehiculo, coordenadasNodoDestino, productoDestino);

        // 2. Verificar impacto en el balance del vehículo (baja ponderación)
        double desbalancePeso = this->calcularDesbalancePeso(espacios,vehiculo) * 0.1; // Reducir el impacto del balance

        // Ajustar heurística combinando penalizaciones
        heuristica *= (1.0 / (1.0 + penalizacionPuerta));  // Penalización por proximidad
        heuristica *= (1.0 / (1.0 + desbalancePeso));      // Penalización leve por desbalance
                
//        cout<<heuristica<<endl;
        
        return heuristica;
    }
    
    double calcularDesbalancePeso(const map<Coordenada, Espacio>& espacios,const Vehiculo& vehiculo) {
        double pesoFrontal = 0.0;
        double pesoTrasero = 0.0;

        // Definimos un límite en el eje X para dividir la parte frontal de la trasera
        double limiteFrontal = vehiculo.getLargo() / 2.0;

        for (map<Coordenada, Espacio>::const_iterator it = espacios.begin(); it != espacios.end(); ++it) {
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

        return abs(pesoFrontal - pesoTrasero);
    }

    
    double calcularAjusteVolumetrico(const Producto& producto, const Espacio& espacio) const {
        // Volumen del producto
        double volumenProducto = producto.getLargo() * producto.getAncho() * producto.getAltura();

        // Volumen del espacio disponible (basado en su largo, ancho, y altura máxima)
        double volumenEspacio = espacio.getLargo() * espacio.getAncho() * espacio.getalturaMax();

        // Ajuste volumétrico basado en la proporción de volumen ocupado
        return (volumenProducto / volumenEspacio);  // Entre 0 y 1, cuanto más cercano a 1, mejor aprovechamiento
    }
    
    double calcularEspacioRestante(const Producto& producto, const Espacio& espacio) const {
        // Volumen del producto
        double volumenProducto = producto.getLargo() * producto.getAncho() * producto.getAltura();

        // Volumen del espacio restante (calculado usando la altura disponible)
        double volumenRestante = (espacio.getLargo() * espacio.getAncho() * (espacio.getalturaMax() - espacio.getalturaActual()));

        // Si el espacio está lleno o no queda altura, el espacio restante es 0
        if (volumenRestante <= 0) {
            return 0.0;
        }

        // Ajuste basado en el volumen restante, cuanto menor el espacio restante, mejor aprovechamiento
        return 1.0 - (volumenProducto / volumenRestante);  // Cuanto más cercano a 0, menos espacio restante
    }


    bool hayColision(const Coordenada& coordExistente, const Espacio& espacioExistente, const Coordenada& coordNueva, const Producto& productoNuevo) const {
        double xExistente = coordExistente.x;
        double yExistente = coordExistente.y;
//        double zExistente = espacioExistente.getalturaActual();

        double largoExistente = espacioExistente.getLargo();
        double anchoExistente = espacioExistente.getAncho();
//        double alturaExistente = espacioExistente.getalturaMax();

        double xNuevo = coordNueva.x;
        double yNuevo = coordNueva.y;
//        double zNuevo = 0;  // El producto nuevo empieza en el suelo del espacio o se apila

        double largoNuevo = productoNuevo.getLargo();
        double anchoNuevo = productoNuevo.getAncho();
//        double alturaNuevo = productoNuevo.getAltura();

        // Verificar colisión en los tres ejes: X, Y y Z
        bool colisionX = (xNuevo < (xExistente + largoExistente)) && ((xNuevo + largoNuevo) > xExistente);
        bool colisionY = (yNuevo < (yExistente + anchoExistente)) && ((yNuevo + anchoNuevo) > yExistente);
//        bool colisionZ = (zNuevo < (zExistente + alturaExistente)) && ((zNuevo + alturaNuevo) > zExistente);

        // Retornamos true si hay colisión en los tres ejes
        return colisionX && colisionY;
        
    }


    
      
};
    

#endif /* ARISTA_H */
