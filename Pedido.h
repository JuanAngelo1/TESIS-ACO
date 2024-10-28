/* 
 * File:   Pedido.h
 * Autor  : Juan Angelo Flores Rubio
 * Codigo : 20196493
 * Created on 28 de septiembre de 2024, 12:11 AM
 */

#ifndef PEDIDO_H
#define PEDIDO_H

#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include "TipoProducto.h"
#include "Producto.h"
using namespace std;

class Pedido{
    
private:
    
    int id_pedido;
    vector<Producto> productos;
    int horaEntrega;
    string prioridad;
    
public:
    
    Pedido(int id,vector<Producto> productos,int hora, string prio);
    
    //Setters
    void setIdPedido(int id);
    void setHoraEntrega(int hora);
    void setPrioridad(string prio);
    void setProductos(vector<Producto> prods);
    
    //Getters
    int getIdPedido() const;
    int getHoraEntrega() const;
    string getPrioridad() const;
    vector<Producto> getProductos() const;
    
    double getVolumenTotalProductos()const;
    double getPesoTotalProductos()const;
    
};


#endif /* PEDIDO_H */
