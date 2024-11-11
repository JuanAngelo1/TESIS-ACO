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
#include <map>
#include "Nodo.h"
#include "Coordenada.h"

using namespace std;

class Arista{
   
private:
   
    Nodo* nodoOrigen;         
    Nodo* nodoDestino;         
    double feromona;
    double costo;                  
    
public:
    
    Arista(Nodo* origen, Nodo* destino, double feromonaInicial = 10.0, double heuristica= 10.0)
        : nodoOrigen(origen), nodoDestino(destino), feromona(feromonaInicial),costo(heuristica) {
        
    }

    double getFeromona() const { return feromona; }
    double getCosto() const { return costo; }

    void setFeromona(double nuevaFeromona) {
        feromona = nuevaFeromona;
    }

    void mostrarInfo(int i) const {
        cout <<i<<"-"<<"Arista entre productos " << nodoOrigen->getIdProducto() 
             << " (Posición " << nodoOrigen->getPosicionProducto() << ") y " 
             << nodoDestino->getIdProducto() 
             << " (Posición " << nodoDestino->getPosicionProducto() << ")"
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
    
    double getHeuristica(Producto& productoDestino, const Coordenada& coordenadasNodoDestino, const map<Coordenada, Espacio>& espacios) const {
        double heuristica = 1.0;  // Valor neutro inicial
        bool espacioEncontrado = false;

        // Verificar colisión con cada espacio en el mapa
        for (const pair<Coordenada, Espacio>& entry : espacios) {
            Coordenada coordExistente = entry.first;
            const Espacio& espacioExistente = entry.second;

            // Usar la función hayColision para verificar superposición
            if (hayColision(coordExistente, espacioExistente, coordenadasNodoDestino, productoDestino)) {
                espacioEncontrado = true;

                // Calcular ajuste volumétrico
                double ajusteVolumetrico = calcularAjusteVolumetrico(productoDestino, espacioExistente);

                // Calcular espacio restante en el espacio destino
                double espacioRestante = calcularEspacioRestante(productoDestino, espacioExistente);

                // Verificar compatibilidad de apilamiento
                if (!espacioExistente.esApilable(&productoDestino)) {
                    // Penalización fuerte si no se puede apilar en este espacio
                    heuristica = 0.1;  // Valor bajo para penalizar fuertemente esta opción
                } else {
                    // Si es apilable, calculamos la heurística normalmente
                    double compatibilidadApilamiento = espacioExistente.estaVacio() ? 0.6 : 0.8;

                    // Ajuste de heurística combinando los factores
                    heuristica = (ajusteVolumetrico * 0.4) + (espacioRestante * 0.3) + (compatibilidadApilamiento * 0.3);
                }
                break;
            }
        }

        // En caso de no encontrar espacio apilable o colisionable, dar una heurística neutra
        if (!espacioEncontrado) {
            heuristica = 1.0;  // Valor neutro en caso de no encontrar colisión o apilamiento
        }

        return heuristica;
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
        double zExistente = espacioExistente.getalturaActual();

        double largoExistente = espacioExistente.getLargo();
        double anchoExistente = espacioExistente.getAncho();
        double alturaExistente = espacioExistente.getalturaMax();

        double xNuevo = coordNueva.x;
        double yNuevo = coordNueva.y;
        double zNuevo = 0;  // El producto nuevo empieza en el suelo del espacio o se apila

        double largoNuevo = productoNuevo.getLargo();
        double anchoNuevo = productoNuevo.getAncho();
        double alturaNuevo = productoNuevo.getAltura();

        // Verificar colisión en los tres ejes: X, Y y Z
        bool colisionX = (xNuevo < (xExistente + largoExistente)) && ((xNuevo + largoNuevo) > xExistente);
        bool colisionY = (yNuevo < (yExistente + anchoExistente)) && ((yNuevo + anchoNuevo) > yExistente);
        bool colisionZ = (zNuevo < (zExistente + alturaExistente)) && ((zNuevo + alturaNuevo) > zExistente);

        // Retornamos true si hay colisión en los tres ejes
        return colisionX && colisionY && colisionZ;
    }


    
      
};
    

#endif /* ARISTA_H */
