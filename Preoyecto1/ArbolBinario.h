//
// Created by yasmi on 19/03/2020.
//

#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <stdio.h>
#include <windows.h>
#include <fstream>

#include "ObjJugador.h"

#ifndef PREOYECTO1_ARBOLBINARIO_H
#define PREOYECTO1_ARBOLBINARIO_H

class ArbolBinario{
public:
    class Nodo{
    public:
        string nombre;

        Nodo * derecha;
        Nodo * izquierda;
    }*nuevo;

    int supercontador = 0, contagraphviz = 0;
    Nodo* arbol; // la raiz de las raices

    Nodo* crearNodo(string nombre);
    void insertar(Nodo* &arbol, string n);
    void iniciarInsertar(string dato);
    void mostrarArbol(Nodo* arbol, int contador);
    void iniciarmostrar();

    string generarGraphviz(ArbolBinario::Nodo *raiz, int contador);
    string iniciargenerarGraphviz();
    string grafo = "";
};

ArbolBinario::Nodo *ArbolBinario::crearNodo(string nombre) {
    nuevo = new Nodo();
    nuevo->nombre = nombre;
    nuevo->derecha = NULL;
    nuevo->izquierda = NULL;
    return nuevo;
}

void ArbolBinario::insertar(ArbolBinario::Nodo *&arbol, string n) {

    if(arbol == NULL){ // si el arbol está vacío
        nuevo = crearNodo(n);
        arbol = nuevo;
        cout<<"nodo primero insertado :D\n";
    } else {
        string valor_raiz = arbol->nombre;

        if(n.compare(valor_raiz) < 0){
            insertar(arbol->izquierda, n);
        }else {
            insertar(arbol->derecha, n);
        }
        cout<<"nodo insertado :D\n";
    }

}

void ArbolBinario::iniciarInsertar(string dato) {
        this->insertar(arbol, dato);
}

void ArbolBinario::mostrarArbol(ArbolBinario::Nodo *raiz, int contador) {
if(raiz == NULL){
    return;
} else{
    mostrarArbol(raiz->derecha, contador+1);
    for (int i = 0; i < contador; ++i) {
        cout<<"   ";
    }
    cout << raiz->nombre<<endl;
    mostrarArbol(raiz->izquierda, contador+1);
}

}
void ArbolBinario::iniciarmostrar() {
    this->mostrarArbol(arbol, supercontador);
    cout<<"\n";
}

string ArbolBinario::generarGraphviz(ArbolBinario::Nodo *raiz, int contador) {


    if(raiz == NULL){
        grafo += "";
    } else{
        if(raiz->izquierda){
            grafo += raiz->nombre + " -> " + raiz->izquierda->nombre + ";\n";
            generarGraphviz(raiz->izquierda, contador+1);
        }
        if(raiz->derecha){
            grafo += raiz->nombre + " -> " + raiz->derecha->nombre + ";\n";
            generarGraphviz(raiz->derecha, contador+1);
        }

    }

    return grafo;
}

string ArbolBinario::iniciargenerarGraphviz() {
    return this->generarGraphviz(arbol, contagraphviz);
}




#endif //PREOYECTO1_ARBOLBINARIO_H
