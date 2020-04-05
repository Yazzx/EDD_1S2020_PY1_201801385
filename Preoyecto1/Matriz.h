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
        Nodo(ObjFicha fichita, int p_x, int p_y){
            this->pos_x = p_x;
            this->pos_y = p_y;
            this->ficha = fichita;

            this->siguiente = NULL;
            this->anterior = NULL;
            this->arriba = NULL;
            this->abajo = NULL;
        }


    }*actual, *nuevo, *auxiliar, *nodoColumna, *nodoFila, *parcial;


    Nodo* raiz;
    int contanodos = 1;



    void iniciarMatriz(int cuadrados);

    Nodo* buscarFila(int y);
    Nodo* buscarColumna(int x);
    Nodo* crearNodo(ObjFicha ficha, int x, int y);
    Nodo* insertarColumnaOrdenada(Nodo *&nuevo, Nodo *&cabeza_col);
    Nodo* insertarFilaOrdenada(Nodo *&nuevo, Nodo *&cabeza_fila);

    Nodo* crearColumna(int x);
    Nodo* crearFila(int y);

    void insertarElementoJuego(ObjFicha ficha, int x, int y);
    Nodo* elementoexiste(int x, int y);

    void insertarElementoEspecial(int puntaje, ObjFicha ficha, int x, int y);
    Nodo* crearNodoEspecial(int puntaje, int x, int y);
    Nodo* insertarEspeciaColumna(Nodo *&nuevo, Nodo *&cabeza_col);
    Nodo* insertarEspecialFila(Nodo *&nuevo, Nodo *&cabeza_fila);

    void getLetra(string &palabra, int x, int y);

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

Matriz::Nodo *Matriz::crearNodoEspecial(int puntaje, int x, int y) {
    nuevo = new (Nodo);
    nuevo->siguiente = NULL; nuevo->anterior = NULL;
    nuevo->arriba = NULL; nuevo->abajo = NULL;

    nuevo->pos_y = y;
    nuevo->pos_x = x;
    nuevo->puntaje = puntaje;

    return nuevo;
}

Matriz::Nodo *Matriz::crearNodo(ObjFicha ficha, int x, int y) {
    nuevo = new (Nodo);
    nuevo->siguiente = NULL; nuevo->anterior = NULL;
    nuevo->arriba = NULL; nuevo->abajo = NULL;

    nuevo->pos_y = y;
    nuevo->pos_x = x;
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

// ESTO INsERTA LAS COSAS

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


Matriz::Nodo *Matriz::insertarEspecialFila(Matriz::Nodo *&nuevo, Matriz::Nodo *&cabeza_fila) {
    auxiliar = cabeza_fila;
    bandera_fila = true;

    while(true){
        if(auxiliar->pos_y == nuevo->pos_y){
            auxiliar->pos_x = nuevo->pos_x;
            if(nuevo->puntaje == 1 || nuevo->puntaje == 0){
                auxiliar->ficha = nuevo->ficha;
            } else {

                auxiliar->puntaje = nuevo->puntaje;
            }
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
Matriz::Nodo *Matriz::insertarEspeciaColumna(Matriz::Nodo *&nuevo, Matriz::Nodo *&cabeza_col) {
    auxiliar = cabeza_col;
    //la bandera es para ver si necesito insertar un nodo
    bandera_col = false;

    while(true){
        if(auxiliar->pos_x == nuevo->pos_x){
            auxiliar->pos_y = nuevo->pos_y;

            if(nuevo->puntaje == 1 || nuevo->puntaje == 0){
                auxiliar->ficha = nuevo->ficha;
            } else {

                auxiliar->puntaje = nuevo->puntaje;
            }

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

// Esto inicia la incersion de cabeceras

Matriz::Nodo *Matriz::crearColumna(int equis) {

    ObjFicha uno;
    //uno.setLetra('=');
    Nodo* hola = crearNodo(uno, equis, -1);

    Nodo* columna_nueva = this->insertarColumnaOrdenada(hola, this->raiz);
    return columna_nueva;
}

Matriz::Nodo *Matriz::crearFila(int ye) {
    ObjFicha uno;
    //uno.setLetra('=');

    Nodo* hola = crearNodo(uno, -1, ye);

    Nodo* fila_nueva = this->insertarFilaOrdenada(hola, this->raiz);
    return fila_nueva;
}

Matriz::Nodo *Matriz::elementoexiste(int x, int y) {
    nodoColumna = buscarColumna(x);
    nodoFila = buscarFila(y);

    actual = nodoColumna;
    while(actual  != NULL){
        if(actual->pos_y = y){
            parcial = actual;
            cout<<"Match en columna!! :D"<<endl;
            break;
        }

        actual = actual->abajo;
    }

    actual = nodoFila;
    while(actual != NULL){
        if(actual->pos_x = x){
            cout<<"Match en fila!! :D"<<endl;
            if(parcial->pos_x == actual->pos_x && parcial->pos_y == actual->pos_y){
                cout<<"Match en nodo!! :D"<<endl;
                return parcial;
            }
            break;
        }
        actual = actual->siguiente;
    }

    return NULL;
}

void Matriz::insertarElementoEspecial(int puntaje, ObjFicha ficha, int x, int y) {

    if(puntaje == 0 || puntaje == 1){
        nuevo = this->crearNodo(ficha, x, y);
    } else {
        nuevo = this->crearNodoEspecial(puntaje, x, y);
    }

    nodoColumna = buscarColumna(x);
    nodoFila = buscarFila(y);

    if(nodoColumna == NULL || nodoFila == NULL){
        cout<<"El nodo está fuera de los límites de la matriz"<<endl;
        return;
    }
    else if(nodoColumna != NULL && nodoFila != NULL){
        nuevo = insertarEspeciaColumna(nuevo, nodoFila);
        nuevo = insertarEspecialFila(nuevo, nodoColumna);
    }


}

string Matriz::generarGraphviz() {

    int contanodos = 1, contacolumnas = 1, contafilas = 1;
    int contagrupos = 0;

    string grafo = "";

    grafo += "// nodos vacíos\n"
             "e0[ shape = point, width = 0 ];\n"
             "e1[ shape = point, width = 0 ];\n"
             "\n"
             "\n"
             "// raiz\n"
             "1[label = \"Raiz(-1,-1)\" width = 1  group = -1];\n";


    this->actual = this->raiz->siguiente;
    while(actual != NULL){
        // fila -1
        string numero = to_string(contanodos);
        string x = to_string(actual->pos_x);
        string grupo = to_string(contagrupos);

        grafo += "X" + x + "[label = \"(" + x + ", -1)\" width = 1 group =" + grupo +"];\n";

        contacolumnas = actual->pos_x;
        contagrupos++;
        actual = actual->siguiente;
    }

    grafo += " rank=same{\n";
    string auxiliar = "";
    for (int i = 0; i <= contacolumnas; ++i) {
        string numero = to_string(i);
        auxiliar += "X" + numero + "->";
    }
    if (!auxiliar.empty()) {
        auxiliar.resize(auxiliar.size() - 1);
        auxiliar.resize(auxiliar.size() - 1);
    }
    grafo += "1->"+auxiliar;
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

        grafo += "Y"+y + "[label = \"( -1 ," + y +")\" width = 1 group = -1 ];\n";

        contafilas = actual->pos_y;
        contanodos++;
        actual = actual->abajo;
    }

    string auxiliar1 = "";
    for (int i = 0; i <= contafilas; ++i) {
        string numero = to_string(i);
        auxiliar1 += "Y"+numero + "->";
    }
    if (!auxiliar1.empty()) {
        auxiliar1.resize(auxiliar1.size() - 1);
        auxiliar1.resize(auxiliar1.size() - 1);
    }
    grafo += "1->" +auxiliar1;
    grafo += " [dir = both];\n\n\n";

    // acá creo los nodos que estan en medio de todo


    // TODO  ACA COMIENZA LO QUE ES MUERTE
    int pos_x = 0, pos_y = 0;

    string auxiliarnodos = "\n";
    actual = raiz->abajo;
    while(actual != NULL){

        this->auxiliar = actual->siguiente;

        while(this->auxiliar != NULL){

            string equis = to_string(this->auxiliar->pos_x);
            string ye = to_string(this->auxiliar->pos_y);

            // si auxiliar tiene una ficha
            if(this->auxiliar->ficha.getLetra() != 0 || this->auxiliar->ficha.getLetra() != '='){
                if(this->auxiliar->puntaje == 2){
                    auxiliarnodos += "X" + equis + "_Y" + ye + "[label = \""+ this->auxiliar->ficha.getLetra() + ".\" width = 1  group = " + equis +", style = filled, fillcolor = pink];\n";
                } else if(this->auxiliar->puntaje == 3){
                    auxiliarnodos += "X" + equis + "_Y" + ye + "[label = \""+ this->auxiliar->ficha.getLetra() + ".\" width = 1  group = " + equis +", style = filled, fillcolor = lightskyblue];\n";
                } else {
                    grafo += "X" + equis + "_Y" + ye + "[label = \""+ this->auxiliar->ficha.getLetra() + ".\" width = 1  group = " + equis +"];\n";
                }
            }
                // si el auxiliar no tiene ficha pero si puntaje
            else {

                if(this->auxiliar->puntaje == 2){

                    auxiliarnodos += "X" + equis + "Y" + ye + " [label = \" ..\", width = 1,  group = " + equis +", style = filled, fillcolor = pink];\n";

                } else if(this->auxiliar->puntaje == 3){

                    auxiliarnodos += "X" + equis + "Y" + ye + " [label = \" .. \", width = 1,  group = " + equis +", style = filled, fillcolor = lightskyblue];\n";

                }

            }
            pos_x++;
            this->auxiliar = this->auxiliar->siguiente;
        }
        pos_y++;
        actual = actual->abajo;
    }

    grafo += auxiliarnodos + "\n";
    // TODO  ACA TERMINA TODO LO QUE ESTÁ MAL CON EL MUNDO

    // aca comienzo a linkear todo

    // linkeando filas
    actual = raiz->abajo;
    while(actual != NULL){

        this->auxiliar = actual->siguiente;
        if(this->auxiliar != NULL){
            string yee = to_string(this->auxiliar->pos_y);
            grafo += "rank=same{\n Y" + yee + "->";
            string auxiliar2 = "";
            while(this->auxiliar != NULL){

                string equis = to_string(this->auxiliar->pos_x);
                string ye = to_string(this->auxiliar->pos_y);

                auxiliar2 += "X" + equis + "_Y" + ye + "->";

                this->auxiliar = this->auxiliar->siguiente;
            }

            if (!auxiliar2.empty()) {
                auxiliar2.resize(auxiliar2.size() - 1);
                auxiliar2.resize(auxiliar2.size() - 1);
            }

            auxiliar2 += "[dir = both];\n";
            grafo += auxiliar2 + "}\n";
        }

        actual = actual->abajo;
    }



    // linkeando columnas

    actual = raiz->siguiente;
    while(actual != NULL){
        this->auxiliar = actual->abajo;
        if(this->auxiliar != NULL){
            string equiss = to_string(this->auxiliar->pos_x);
            grafo += " X" + equiss + "->";
            string auxiliar3 = "";
            while(this->auxiliar != NULL){
                string equis = to_string(this->auxiliar->pos_x);
                string ye = to_string(this->auxiliar->pos_y);
                auxiliar3 += "X" + equis + "_Y" + ye + "->";

                this->auxiliar = this->auxiliar->abajo;
            }

            if (!auxiliar3.empty()) {
                auxiliar3.resize(auxiliar3.size() - 1);
                auxiliar3.resize(auxiliar3.size() - 1);
            }

            auxiliar3 += "[dir = both];\n";
            grafo += auxiliar3 + "\n";

        }

        actual = actual->siguiente;
    }

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

    char url[100] = "C:\\Users\\yasmi\\OneDrive\\Escritorio\\Matriz.dot";
    ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);

}

void Matriz::getLetra(string &palabra, int x, int y) {

    actual = raiz->abajo;
    while(actual != NULL){

        if(actual->pos_y == y){

            auxiliar = actual->siguiente;
            while(auxiliar != NULL){

                if(auxiliar->pos_y == y && auxiliar->pos_x == x){

                    palabra += auxiliar->ficha.getLetra();

                }

                auxiliar = auxiliar->siguiente;
            }
        }

        actual = actual->abajo;
    }

}


#endif //PREOYECTO1_MATRIZ_H
