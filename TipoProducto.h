/* 
 * File:   TipoProducto.h
 * Autor  : Juan Angelo Flores Rubio
 * Codigo : 20196493
 * Created on 24 de septiembre de 2024, 12:23 AM
 */

#ifndef TIPOPRODUCTO_H
#define TIPOPRODUCTO_H

#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

class TipoProducto{

private:
    int id_producto;
    string nombre;           
    double peso;             
    
    double largo;            
    double ancho;            
    double alto;             
    double limitePeso;   
    double volumen;
    vector<int> puedeRotar;  
    
public:
    
    // Constructor
    TipoProducto(int id, string n, double p, double l, double a, double al, double lp);
    
    TipoProducto();

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
    double getAlto() const;
    double getLimitePeso() const;
    vector<int> getPuedeRotar() const;
    double getVolumen()const;


    // Mostrar información del tipo de producto
    void mostrarInformacion() const;
    
    bool esValido() const ;
           
};

#endif /* TIPOPRODUCTO_H */
