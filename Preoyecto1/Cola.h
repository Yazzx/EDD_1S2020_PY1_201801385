//
// Created by yasmi on 14/03/2020.
//

#ifndef PREOYECTO1_COLA_H
#define PREOYECTO1_COLA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

    void shufflear();
    void swap (ObjFicha *a, ObjFicha *b);
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

    ObjFicha ficha_a('a', 1);
    ObjFicha ficha_e('e', 1);
    for (int i = 0; i < 12; ++i) {
        this->insertar(ficha_a);
        this->insertar(ficha_e);
    }

    ObjFicha ficha_o('o', 1);
    for (int i = 0; i < 9; ++i) {
        this->insertar(ficha_o);
    }

    ObjFicha ficha_i('i', 1);
    ObjFicha ficha_s('s', 1);
    for (int i = 0; i < 6; ++i) {
        this->insertar(ficha_i);
        this->insertar(ficha_s);
    }

    ObjFicha ficha_n('n', 1);
    ObjFicha ficha_r('r', 1);
    ObjFicha ficha_u('u', 1);
    ObjFicha ficha_d('d', 2);
    for (int i = 0; i < 5; ++i) {
        this->insertar(ficha_n);
        this->insertar(ficha_r);
        this->insertar(ficha_u);
        this->insertar(ficha_d);
    }

    ObjFicha ficha_l('l', 1);
    ObjFicha ficha_t('t', 1);
    ObjFicha ficha_c('c', 3);
    for (int i = 0; i < 4; ++i) {
        this->insertar(ficha_l);
        this->insertar(ficha_t);
        this->insertar(ficha_c);
    }

    ObjFicha ficha_g('g', 2);
    ObjFicha ficha_b('b', 3);
    ObjFicha ficha_m('m', 3);
    ObjFicha ficha_p('p', 3);
    ObjFicha ficha_h('h', 4);
    for (int i = 0; i < 2; ++i) {
        this->insertar(ficha_g);
        this->insertar(ficha_b);
        this->insertar(ficha_m);
        this->insertar(ficha_p);
        this->insertar(ficha_h);
    }

    ObjFicha ficha_f('f', 4);
    ObjFicha ficha_v('v', 4);
    ObjFicha ficha_y('y', 4);
    ObjFicha ficha_q('q', 5);
    ObjFicha ficha_j('j', 8);
    ObjFicha ficha_enie(164, 8);
    ObjFicha ficha_x('x', 8);
    ObjFicha ficha_z('z', 10);

    this->insertar(ficha_f);
    this->insertar(ficha_v);
    this->insertar(ficha_y);
    this->insertar(ficha_q);
    this->insertar(ficha_j);
    this->insertar(ficha_enie);
    this->insertar(ficha_x);
    this->insertar(ficha_z);

}

string Cola::generarGraphviz() {
    string lista;

    actual = primero;
    int contador = 0;

    while(actual != ultimo->siguiente){

        string u;
        string numero = to_string(contador);

        if(actual == ultimo){
            lista = lista + numero + ";\n";}
        else {
                lista = lista + numero + "->";
            }

        contador++;
        actual = actual->siguiente;
    }

    actual = primero;
    contador = 0;
    while(actual != ultimo->siguiente){
        string u;
        string numero = to_string(contador);
        string puntaje = to_string(actual->ficha.getPuntaje());

        lista = lista + numero + " [label = \"" + actual->ficha.getLetra() + " x " + puntaje + " pts\"];\n";
        contador++;
        actual = actual->siguiente;
    }

    return lista;
}






#endif //PREOYECTO1_COLA_H
