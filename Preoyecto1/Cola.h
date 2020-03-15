//
// Created by yasmi on 14/03/2020.
//

#ifndef PREOYECTO1_COLA_H
#define PREOYECTO1_COLA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <iostream>

#include "ObjFicha.h"

using namespace ::std;

class Cola {

public:
    bool esVacia = true;
    int contanodos = 1;

    class Nodo
    {
    public:
        ObjFicha ficha;
        int correlativo;
        Nodo *siguiente;
    } * primero, *ultimo, *actual, *nuevo, *auxiliar;

    bool isVacia() const;

    void insertar(ObjFicha ficha);
    void mostrarLista();
    bool buscar(char letra);

    void llenarCola();

    string generarGraphviz();
};

bool Cola::isVacia() const {
    return esVacia;
}

void Cola::insertar(ObjFicha ficha)
{
    if (!primero)
    {
        esVacia = false;
        primero = new (Nodo);
        ultimo = new (Nodo);

        primero->siguiente = NULL;
        primero->ficha = ficha;
        primero->correlativo = contanodos;
        contanodos++;

        // si son los mismos porque primero y ultimo son
        // punteros, NO NODOS alv
        ultimo = primero;
        return;
    }

    nuevo = new (Nodo);

    nuevo->ficha = ficha;
    nuevo->correlativo = contanodos;
    contanodos++;

    ultimo->siguiente = nuevo;
    ultimo = nuevo;
    return;
}

void Cola::mostrarLista() {

    cout<<endl;
    cout<<endl;
    if (esVacia)
    {
        cout << "La lista esta vacia :C" << endl;
        return;

    }
    actual = primero;

    do
    {
        cout << "\t\t"<<actual->correlativo << " " << actual->ficha.getLetra() << endl;

        actual = actual->siguiente;

    } while (actual != ultimo->siguiente);

    cout<<endl;
    cout<<endl;
    cout << "La lista ha finalizado" << endl;
}

bool Cola::buscar(char letra) {

    if (esVacia)
    {
        cout << "La lista está vacía :c" << endl;
        return false;
    }

    actual = primero;

    do
    {
        if (actual->ficha.getLetra() == letra)
        {
            return true;
        }

        actual = actual->siguiente;

    } while (actual != ultimo->siguiente);

        cout << "No se econtro la referencia" << endl;
        return false;

}

void Cola::llenarCola() {

    // esto llena y shufflea la cola

}


#endif //PREOYECTO1_COLA_H
