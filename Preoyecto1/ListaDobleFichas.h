//
// Created by yasmi on 23/03/2020.
//

#ifndef PREOYECTO1_LISTADOBLEFICHAS_H
#define PREOYECTO1_LISTADOBLEFICHAS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <iostream>
#include <bits/stdc++.h>

#include "ObjFicha.h"

using namespace ::std;

class ListaDobleFichas{
public:
    int contanodos = 1;

    class Nodo{
    public:
        int correlativo;
        ObjFicha ficha;
        Nodo *siguiente, *anterior;
    }*primero, *ultimo, *actual, *nuevo, *auxiliar;

    ListaDobleFichas(){
        this->primero = this->ultimo = this->actual = this->nuevo = this->auxiliar = NULL;
    }
    void insertar(ObjFicha fichaa);
    void mostrarLista();
    string generarGraphviz();
};

void ListaDobleFichas::insertar(ObjFicha fichaa) {

    if(!primero){

        primero = new(Nodo);
        ultimo = new(Nodo);
        nuevo = new(Nodo);

        nuevo->ficha = fichaa;
        nuevo->correlativo = contanodos;
        contanodos++;

        primero = nuevo;
        ultimo = nuevo;

        return;
    } else {
        nuevo = new(Nodo);
        nuevo->ficha = fichaa;
        nuevo->correlativo = contanodos;
        contanodos++;

        // insertando al final

        nuevo->anterior = ultimo;
        ultimo->siguiente = nuevo;

        nuevo->siguiente = NULL;
        ultimo = nuevo;

    }


}

void ListaDobleFichas::mostrarLista() {

    int contador = 1;
    if(!primero){
        cout<<"La lista esta vacia :C"<<endl;
        return;
    }
    actual = primero;
    while(actual != NULL){
        cout<< contador << " - " << actual->ficha.getLetra()<<endl;
        contador++;
        actual = actual->siguiente;
    }
    cout << "La lista ha finalizado"<<endl;

}

string ListaDobleFichas::generarGraphviz() {
    string lista;

    actual = primero;
    int contador = 0;

    while(actual != ultimo->siguiente){

        string u;
        string numero = to_string(contador);

        if(actual == ultimo){
            lista = lista + numero + ";\n";
        } else {
            lista = lista + numero + "->";
        }

        contador++;
        actual = actual->siguiente;
    }

    for(int i = --contador; i>= 0 ;--i){
        string numero = to_string(i);

        if( i == 0){

            lista = lista + "0;";
        }else{
            lista = lista + numero + "->";
        }

    }

    int contador2 = 0;
    actual = primero;

    while(actual != ultimo->siguiente){

        string numero = to_string(contador2);

        lista = lista + numero + " [label = \"" + actual->ficha.getLetra() + "\"];\n";
        contador2++;
        actual = actual->siguiente;
    }

    return lista;
}


#endif //PREOYECTO1_LISTADOBLEFICHAS_H
