/* 
 * File:   Pedido.cpp
 * Autor  : Juan Angelo Flores Rubio
 * Codigo : 20196493
 * Created on 28 de septiembre de 2024, 12:11 AM
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <vector>
#include "Pedido.h"


using namespace std;

Pedido::Pedido(int id,vector <Producto> prods,int hora, string prio){

    id_pedido=id;
    productos=prods;
    horaEntrega=hora;
    prioridad=prio;
}

    // Métodos setters
    void Pedido::setIdPedido(int id){id_pedido=id;}
    void Pedido::setHoraEntrega(int hora) { horaEntrega = hora; }
    void Pedido::setPrioridad(string prio){ prioridad=prio; }
    void Pedido::setProductos(vector<Producto> prods) { productos = prods; }

    
    // Métodos getters
    int Pedido::getIdPedido()const{return id_pedido;}
    int Pedido::getHoraEntrega() const {return horaEntrega; }
    string Pedido::getPrioridad() const { return prioridad; }
    vector<Producto> Pedido::getProductos() const { return productos; }
    
    double Pedido::getVolumenTotalProductos()const{
        
        vector <Producto> prods=productos;
        
        double totalVolumen;
        
        for(Producto prod: prods)
            totalVolumen+=prod.getVolumen();
        
        return totalVolumen;
    }
    
    double Pedido::getPesoTotalProductos()const{
        vector <Producto> prods=productos;
        
        double totalPeso;
        
        for(Producto prod: prods)
            totalPeso+=prod.getPeso();
        
        return totalPeso;
        
    }
