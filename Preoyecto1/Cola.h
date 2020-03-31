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
#include <bits/stdc++.h>

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


    void insertar(ObjFicha ficha);
    void mostrarLista();
    bool buscar(char letra);
    ObjFicha pop();

    void llenarCola();

    string generarGraphviz();
    void iniciarGenerarGraphviz();

};


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

 ObjFicha arr_fichas[95];

    ObjFicha ficha_a('a', 1);
    ObjFicha ficha_e('e', 1);
    for (int i = 0; i < 12; ++i) {
        arr_fichas[i] = ficha_a;
    }
    for (int i = 12; i < 24; ++i) {
        arr_fichas[i] = ficha_e;
    }
    ObjFicha ficha_o('o', 1);
    for (int i = 24; i < 33; ++i) {
        arr_fichas[i] = ficha_o;
    }

    ObjFicha ficha_i('i', 1);
    ObjFicha ficha_s('s', 1);
    for (int i = 33; i < 39; ++i) {
        arr_fichas[i] = ficha_i;
    }
    for (int i = 39; i < 45; ++i) {
        arr_fichas[i] = ficha_s;
    }

    ObjFicha ficha_n('n', 1);
    ObjFicha ficha_r('r', 1);
    ObjFicha ficha_u('u', 1);
    ObjFicha ficha_d('d', 2);
    for (int i = 45; i < 50; ++i) {
        arr_fichas[i] = ficha_n;
    }
    for (int i = 50; i < 55; ++i) {
        arr_fichas[i] = ficha_r;
    }
    for (int i = 55; i < 60; ++i) {
        arr_fichas[i] = ficha_u;
    }
    for (int i = 60; i < 65; ++i) {
        arr_fichas[i] = ficha_d;
    }

    ObjFicha ficha_l('l', 1);
    ObjFicha ficha_t('t', 1);
    ObjFicha ficha_c('c', 3);
    for (int i = 65; i < 69; ++i) {
        arr_fichas[i] = ficha_l;
    }
    for (int i = 69; i < 73; ++i) {
        arr_fichas[i] = ficha_t;
    }
    for (int i = 73; i < 77; ++i) {
        arr_fichas[i] = ficha_c;
    }

    ObjFicha ficha_g('g', 2);
    ObjFicha ficha_b('b', 3);
    ObjFicha ficha_m('m', 3);
    ObjFicha ficha_p('p', 3);
    ObjFicha ficha_h('h', 4);
    for (int i = 77; i < 79; ++i) {
        arr_fichas[i] = ficha_g;
    }
    for (int i = 79; i < 81; ++i) {
        arr_fichas[i] = ficha_b;
    }
    for (int i = 81; i < 83; ++i) {
        arr_fichas[i] = ficha_m;
    }
    for (int i = 83; i < 85; ++i) {
        arr_fichas[i] = ficha_p;
    }
    for (int i = 85; i < 87; ++i) {
        arr_fichas[i] = ficha_h;
    }

    ObjFicha ficha_f('f', 4);
    ObjFicha ficha_v('v', 4);
    ObjFicha ficha_y('y', 4);
    ObjFicha ficha_q('q', 5);
    ObjFicha ficha_j('j', 8);
    ObjFicha ficha_enie(164, 8);
    ObjFicha ficha_x('x', 8);
    ObjFicha ficha_z('z', 10);

    arr_fichas[87] = ficha_f;
    arr_fichas[88] = ficha_v;
    arr_fichas[89] = ficha_y;
    arr_fichas[90] = ficha_q;
    arr_fichas[91] = ficha_j;
    arr_fichas[92] = ficha_enie;
    arr_fichas[93] = ficha_x;
    arr_fichas[94] = ficha_z;

    unsigned seed = 0;
    int n = 95;
    srand(std::time(0));

    random_shuffle(arr_fichas, arr_fichas + n);


    for (int i = 0; i < n; ++i){
     this->insertar(arr_fichas[i]);
    }


}
ObjFicha Cola::pop() {

    auxiliar = new (Nodo);
    auxiliar = this->primero;

    primero = primero->siguiente;

    return auxiliar->ficha;
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
void Cola::iniciarGenerarGraphviz() {
    ofstream prueba;
    prueba.open("C:\\Users\\yasmi\\OneDrive\\Escritorio\\Fichas.dot", ios::out);
    if(prueba.fail()){
        cout<<"No se ha podido abrir el archivo"<<endl;
        return;
    }
    // TODO
    // NOMBREDEESTRUCTURA.generarGraphviz()
    string kionda = this->generarGraphviz();

    //cout<<"\n\n\n"<<kionda<<"\n\n";
    prueba<<"digraph G {\n"
            "\n"
            " node [shape=box];\n"
          << kionda<<
          "}";

    prueba.close();

    system("dot -Tpng C:\\Users\\yasmi\\OneDrive\\Escritorio\\Fichas.dot > C:\\Users\\yasmi\\OneDrive\\Escritorio\\Fichas.png");

    char url[100] = "C:\\Users\\yasmi\\OneDrive\\Escritorio\\Fichas.png";
    ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}


#endif //PREOYECTO1_COLA_H
