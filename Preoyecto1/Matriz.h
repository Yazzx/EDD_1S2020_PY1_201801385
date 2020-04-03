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
        int puntaje;
        // nodo en si
        Nodo* arriba; Nodo* abajo;
        Nodo* anterior; Nodo* siguiente;
        //dato
        ObjFicha ficha;

        // CONSTRUCTORES

        Nodo(){
            this->siguiente = NULL;
            this->anterior = NULL;
            this->arriba = NULL;
            this->abajo = NULL;
            this->puntaje = 1;
        }
        Nodo(ObjFicha fichita, int p_x, int p_y, int puntaje){
            this->pos_x = p_x;
            this->pos_y = p_y;
            this->ficha = fichita;
            this->puntaje = puntaje;

            this->siguiente = NULL;
            this->anterior = NULL;
            this->arriba = NULL;
            this->abajo = NULL;
        }


    }*actual, *nuevo, *auxiliar, *nodoColumna, *nodoFila;


    Nodo* raiz;
    int contanodos = 1;



    void iniciarMatriz(int cuadrados);

    Nodo* buscarFila(int y);
    Nodo* buscarColumna(int x);
    Nodo* crearNodo(ObjFicha ficha, int x, int y, int puntaje);
    Nodo* insertarColumnaOrdenada(Nodo *&nuevo, Nodo *&cabeza_col);
    Nodo* insertarFilaOrdenada(Nodo *&nuevo, Nodo *&cabeza_fila);

    Nodo* crearColumna(int x);
    Nodo* crearFila(int y);

    void insertarElemento(ObjFicha ficha, int x, int y, int puntaje);

    bool bandera_fila, bandera_col;

    string generarGraphviz();
    void iniciarGenerarGraphviz();

};

void Matriz::iniciarMatriz(int cuadrados) {
    // iniciando Matriz
    raiz = new (Nodo);
    raiz->siguiente = NULL; raiz->anterior = NULL;
    raiz->arriba = NULL; raiz->abajo = NULL;
    raiz->pos_x = -1;
    raiz->pos_y = -1;
    raiz->puntaje = 1;

    cout<<"Iniciando Matriz..."<<endl;

    for (int i = 0; i < cuadrados; ++i) {
        this->crearFila(i);
        //cout<<"Fila creada"<<endl;
        this->crearColumna(i);
        //cout<<"Columna creada"<<endl;
    }


}

Matriz::Nodo *Matriz::crearNodo(ObjFicha ficha, int x, int y, int puntaje) {
    nuevo = new (Nodo);
    nuevo->siguiente = NULL; nuevo->anterior = NULL;
    nuevo->arriba = NULL; nuevo->abajo = NULL;

    nuevo->pos_y = y;
    nuevo->pos_x = x;
    nuevo->puntaje = puntaje;
    nuevo->ficha = ficha;

    return nuevo;
}

Matriz::Nodo *Matriz::buscarFila(int y) {
    auxiliar = this->raiz;

    while(auxiliar != NULL){
        if(auxiliar->pos_y == y){
            return auxiliar;
        }
        auxiliar = auxiliar->abajo;
    }
    return NULL;
}

Matriz::Nodo *Matriz::buscarColumna(int x) {
    auxiliar = this->raiz;

    while(auxiliar != NULL){
        if(auxiliar->pos_x == x){
            return auxiliar;
        }
        auxiliar = auxiliar->siguiente;
    }
    return NULL;
}

// ESTO INsERTA COMO CABECERAS

Matriz::Nodo *Matriz::insertarColumnaOrdenada(Nodo *&nuevo, Nodo *&cabeza_col) {
    auxiliar = cabeza_col;
    //la bandera es para ver si necesito insertar un nodo
    bandera_col = false;

    while(true){
        if(auxiliar->pos_x == nuevo->pos_x){
            auxiliar->pos_y = nuevo->pos_y;
            auxiliar->ficha = nuevo->ficha;
            return auxiliar;
        }
        else if(auxiliar->pos_x > nuevo->pos_x){
            bandera_col = true;
            break;
        }
        if(auxiliar->siguiente != NULL){
            auxiliar = auxiliar->siguiente;
        }
        else {
            bandera_col = false;
            break;
        }
    }

    if(bandera_col){
        nuevo->siguiente = auxiliar;
        auxiliar->anterior->siguiente = nuevo;
        nuevo->anterior = auxiliar->anterior;
        auxiliar->anterior = nuevo;
    }
    else {
        auxiliar->siguiente = nuevo;
        nuevo->anterior = auxiliar;
    }
    return nuevo;

}

Matriz::Nodo *Matriz::insertarFilaOrdenada(Matriz::Nodo *&nuevo, Matriz::Nodo *&cabeza_fila) {
    auxiliar = cabeza_fila;
    bandera_fila = true;

    while(true){
        if(auxiliar->pos_y == nuevo->pos_y){
            auxiliar->pos_x = nuevo->pos_x;
            auxiliar->ficha = nuevo->ficha;
            return auxiliar;
        }
        else if(auxiliar->pos_y > nuevo->pos_y){
            bandera_fila = true;
            break;
        }
        if(auxiliar->abajo != NULL){
            auxiliar = auxiliar->abajo;
        }
        else {
            bandera_fila = false;
            break;
        }
    }

    if(bandera_fila){
        nuevo->abajo = auxiliar;
        auxiliar->arriba->abajo= nuevo;
        nuevo->arriba = auxiliar->arriba;
        auxiliar->arriba = nuevo;
    }
    else {
        auxiliar->abajo = nuevo;
        nuevo->arriba = auxiliar;
    }
    return  nuevo;
}

// Esto inicia la incersion de cabeceras

Matriz::Nodo *Matriz::crearColumna(int equis) {

    ObjFicha uno;
    //uno.setLetra('=');
    Nodo* hola = crearNodo(uno, equis, -1, 1);

    Nodo* columna_nueva = this->insertarColumnaOrdenada(hola, this->raiz);
    return columna_nueva;
}

Matriz::Nodo *Matriz::crearFila(int ye) {
    ObjFicha uno;
    //uno.setLetra('=');

    Nodo* hola = crearNodo(uno, -1, ye, 1);

    Nodo* fila_nueva = this->insertarFilaOrdenada(hola, this->raiz);
    return fila_nueva;
}

void Matriz::insertarElemento(ObjFicha ficha, int x, int y, int puntaje) {

    nuevo = crearNodo(ficha, x, y, puntaje);
    nodoColumna = buscarColumna(x);
    nodoFila = buscarFila(y);

    if(nodoColumna == NULL && nodoFila == NULL){
        cout<<"El nodo está fuera de los límites de la matriz"<<endl;
        /*nodoColumna = crearColumna(x);
        nodoFila = crearFila(y);

        nuevo = insertarColumnaOrdenada(nuevo, nodoColumna);
        nuevo = insertarFilaOrdenada(nuevo, nodoFila);*/
        return;
    }
    else if(nodoColumna != NULL && nodoFila == NULL){
        nuevo = insertarColumnaOrdenada(nuevo, nodoFila);
        nuevo = insertarFilaOrdenada(nuevo, nodoColumna);
        return;
    }

}

string Matriz::generarGraphviz() {

    int contanodos = 2, contacolumnas = 1, contafilas = 1;
    int contagrupos = 1;

    string grafo = "";

    grafo += "// nodos vacíos\n"
             "e0[ shape = point, width = 0 ];\n"
             "e1[ shape = point, width = 0 ];\n"
             "\n"
             "\n"
             "// raiz\n"
             " 1[label = \"Raiz(-1,-1)\" width = 1  group = 0];\n";


    this->actual = this->raiz->siguiente;
    while(actual != NULL){
        // fila -1
        string numero = to_string(contanodos);
        string x = to_string(actual->pos_x);
        string grupo = to_string(contagrupos);

        grafo += numero + "[label = \"(" + x + ", -1)\" width = 1 group =" + grupo +"];\n";

        contanodos++;
        contagrupos++;
        actual = actual->siguiente;
    }

    grafo += " rank=same{\n";
    string auxiliar = "";
    for (int i = 1; i < contanodos; ++i) {
        string numero = to_string(i);
        auxiliar += numero + "->";
    }
    if (!auxiliar.empty()) {
        auxiliar.resize(auxiliar.size() - 1);
        auxiliar.resize(auxiliar.size() - 1);
    }
    grafo += auxiliar;
    grafo += " [dir = both]\n}\n";

    contacolumnas = contanodos-1;
    // las filas empiezan a partir de contanodos
    contafilas = contanodos;

    this->actual = this->raiz->abajo;
    while(actual != NULL){
        // fila -1
        string numero = to_string(contanodos);
        string y = to_string(actual->pos_y);
        string grupo = to_string(contagrupos);

        grafo += numero + "[label = \"( -1 ," + y +")\" width = 1 group = 0 ];\n";

        contanodos++;
        actual = actual->abajo;
    }

    string auxiliar1 = "";
    for (int i = contafilas; i < contanodos; ++i) {
        string numero = to_string(i);
        auxiliar1 += numero + "->";
    }
    if (!auxiliar1.empty()) {
        auxiliar1.resize(auxiliar1.size() - 1);
        auxiliar1.resize(auxiliar1.size() - 1);
    }
    grafo += "1->" +auxiliar1;
    grafo += " [dir = both];\n";

    return grafo;

}

void Matriz::iniciarGenerarGraphviz() {

    ofstream prueba;
    prueba.open("C:\\Users\\yasmi\\OneDrive\\Escritorio\\Matriz.dot", ios::out);
    if(prueba.fail()){
        cout<<"No se ha podido abrir el archivo"<<endl;
        return;
    }
    // TODO
    // NOMBREDEESTRUCTURA.generarGraphviz()
    string kionda = this->generarGraphviz();

    //cout<<"\n\n\n"<<kionda<<"\n\n";
    prueba<<"digraph G {\n"
            "node [shape=box];\n"
          << kionda<<
          "}";

    prueba.close();
    system("dot -Tpng C:\\Users\\yasmi\\OneDrive\\Escritorio\\Matriz.dot > C:\\Users\\yasmi\\OneDrive\\Escritorio\\Matriz.png");

    char url[100] = "C:\\Users\\yasmi\\OneDrive\\Escritorio\\Matriz.png";
    ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);

}




#endif //PREOYECTO1_MATRIZ_H
