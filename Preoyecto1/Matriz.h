//
// Created by yasmi on 30/03/2020.
//

#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <stdio.h>
#include <windows.h>
#include <fstream>

#include "ObjJugador.h"
#include "ObjFicha.h"

#ifndef PREOYECTO1_MATRIZ_H
#define PREOYECTO1_MATRIZ_H

using namespace std;

class Matriz {

public:

    class Nodo{

    public:
        // posicion
        int pos_x;
        int pos_y;
        // nodo en si
        Nodo* arriba; Nodo* abajo;
        Nodo* anterior; Nodo* siguiente;
        //dato
        ObjFicha ficha;
        char letra;

        // CONSTRUCTORES

        Nodo(){
            this->siguiente = NULL;
            this->anterior = NULL;
            this->arriba = NULL;
            this->abajo = NULL;
        }
        Nodo(ObjFicha fichita, int p_x, int p_y){
            this->pos_x = p_x;
            this->pos_y = p_y;
            this->ficha = fichita;
            this->letra = fichita.getLetra();

            this->siguiente = NULL;
            this->anterior = NULL;
            this->arriba = NULL;
            this->abajo = NULL;
        }


    }*actual, *nuevo, *auxiliar;

    Nodo* raiz;
    int contanodos;

    Matriz(int cudrados){
        raiz->pos_x = -1;
        raiz->pos_y = -1;
    }
    Nodo* buscarFila(Nodo*& nodo, int y);
    Nodo* buscarColumna(Nodo*& nodo, int x);
    Nodo* crearNodo(ObjFicha ficha);
    Nodo* insertarOrdenadoColumna(ObjFicha ficha );




};


Matriz::Nodo *Matriz::buscarFila(Matriz::Nodo *&nodo, int y) {
    auxiliar = this->raiz;

    while(auxiliar != NULL){
        if(auxiliar->pos_y == y){
            return auxiliar;
        }
        auxiliar = auxiliar->abajo;
    }
    return NULL;
}

Matriz::Nodo *Matriz::buscarColumna(Matriz::Nodo *&nodo, int x) {
    auxiliar = this->raiz;

    while(auxiliar != NULL){
        if(auxiliar->pos_x == x){
            return auxiliar;
        }
        auxiliar = auxiliar->siguiente;
    }
    return NULL;
}




#endif //PREOYECTO1_MATRIZ_H
