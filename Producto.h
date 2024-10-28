/* 
 * File:   Producto.h
 *  Autor  : Juan Angelo Flores Rubio
 *  Codigo : 20196493
 * Created on 8 de octubre de 2024, 09:10 PM
 */


#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <fstream>
#include <vector>

using namespace std;

class Producto {
private:
    int id_producto;
    string nombre;           
    double peso;             
    double largo,ancho,alto;             
    double limitePeso;   
    double volumen;

public:
    
        // Constructor
    Producto(int id, string n, double p, double l, double a, double al, double lp);
    
    Producto();

    // Setters
    void setIdProducto(int id);
    void setNombre(string n);
    void setPeso(double p);
    void setLargo(double l);
    void setAncho(double a);
    void setAlto(double al);
    void setLimitePeso(double lp);
    void setPuedeRotar(vector<int> pr);
    
    // Getters
    int getIdProducto() const;
    string getNombre() const;
    double getPeso() const;
    double getLargo() const;
    double getAncho() const;
    double getAltura() const;
    double getLimitePeso() const;
    double getVolumen()const;


    // Mostrar información del tipo de producto
    void mostrarInformacion() const;
    
    bool esValido() const ;
    
    
    bool esApilableSobre(Producto* nuevoProducto) const;

};

#endif /* PRODUCTO_H */

