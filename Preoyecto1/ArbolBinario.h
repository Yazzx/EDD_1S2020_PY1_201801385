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
        ObjJugador objjugador;
        Nodo * derecha;
        Nodo * izquierda;
    }*nuevo;

    int supercontador = 0, contagraphviz = 0;
    Nodo* arbol; // la raiz de las raices

    Nodo* crearNodo(string nombre);

    void buscar(ArbolBinario::Nodo *&arbol, string n);
    void iniciarbuscar(string nombre);

    bool yaesta = false, insertcionexitosa = false;

    void insertar(Nodo* &arbol, string n);
    void iniciarInsertar(string dato);

    void mostrarArbol(Nodo* arbol, int contador);
    void iniciarmostrar();

    string generarGraphviz(ArbolBinario::Nodo *raiz, int contador);
    void iniciargenerarGraphviz();

    void generarPreorder(ArbolBinario::Nodo *raiz);
    string pre = "";
    void iniciarPreorder();

    void generarEnorder(ArbolBinario::Nodo *raiz);
    string en = "";
    void iniciarEnorder();

    void generarPostorder(ArbolBinario::Nodo *raiz);
    string post = "";
    void iniciarPostorder();


    string grafo = "";
};

ArbolBinario::Nodo *ArbolBinario::crearNodo(string nombre) {
    ObjJugador uno(nombre);
    nuevo = new Nodo();
    nuevo->nombre = nombre;
    nuevo->objjugador = uno;
    nuevo->derecha = NULL;
    nuevo->izquierda = NULL;
    return nuevo;
}

void ArbolBinario::iniciarbuscar(string nombre){
    this->buscar(arbol, nombre);
}
void ArbolBinario::buscar(ArbolBinario::Nodo *&arbol, string n) {

    if(arbol == NULL){
        //cout<< "nel\n";
        yaesta = false;
    } else {
        string valor_raiz = arbol->nombre;

        if(n.compare(valor_raiz) < 0){
            buscar(arbol->izquierda, n);
        } else if(n.compare(valor_raiz) > 0){
            buscar(arbol->derecha, n);
        } else if (arbol->nombre.compare(n) == 0){
            yaesta = true;
            //cout<<"simon\n";
        } else {
           // cout<< "nel\n";
            yaesta = false;
        }

    }
}

void ArbolBinario::insertar(ArbolBinario::Nodo *&arbol, string n) {

    if(arbol == NULL){ // si el arbol está vacío
        nuevo = crearNodo(n);
        arbol = nuevo;
        //cout<<"nodo primero insertado :D\n";
    } else {
        string valor_raiz = arbol->nombre;

        if(n.compare(valor_raiz) < 0){
            insertar(arbol->izquierda, n);
        }else {
            insertar(arbol->derecha, n);
        }
       // cout<<"nodo insertado :D\n";
    }
}
void ArbolBinario::iniciarInsertar(string dato) {

    buscar(arbol, dato);
   // cout<<"Esta antes? "<<yaesta<<endl;

    if(!yaesta){

        this->insertar(arbol, dato);
        insertcionexitosa = true;
    } else {
        cout<<"Ese nombre ya existe, por favor escoge otro :C"<<endl;
        insertcionexitosa = false;
    }
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
void ArbolBinario::iniciargenerarGraphviz() {
    ofstream prueba;
    prueba.open("C:\\Users\\yasmi\\OneDrive\\Escritorio\\ArbolNombres.dot", ios::out);
    if(prueba.fail()){
        cout<<"No se ha podido abrir el archivo"<<endl;
        return;
    }
    // TODO
    // NOMBREDEESTRUCTURA.generarGraphviz()
    string kionda = this->generarGraphviz(arbol, contagraphviz);

    //cout<<"\n\n\n"<<kionda<<"\n\n";
    prueba<<"digraph G {\n"
            "\n"
          << kionda<<
          "}";

    prueba.close();
    system("dot -Tpng C:\\Users\\yasmi\\OneDrive\\Escritorio\\ArbolNombres.dot > C:\\Users\\yasmi\\OneDrive\\Escritorio\\ArbolNombres.png");

    char url[100] = "C:\\Users\\yasmi\\OneDrive\\Escritorio\\ArbolNombres.png";
    ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);


}

void ArbolBinario::generarPreorder(ArbolBinario::Nodo *raiz) {

    // raiz izq der

    if(raiz == NULL){
        pre += "";
    } else{
        pre += raiz->nombre + " ->";
        if(raiz->izquierda){
            generarPreorder(raiz->izquierda);
        }
        if(raiz->derecha){
            generarPreorder(raiz->derecha);
        }
    }

}
void ArbolBinario::iniciarPreorder() {
    generarPreorder(this->arbol);

    if (!pre.empty()) {
        pre.resize(pre.size() - 1);
        pre.resize(pre.size() - 1);
    }

    pre += ";";

    ofstream prueba;
    prueba.open("C:\\Users\\yasmi\\OneDrive\\Escritorio\\ArbolPreorder.dot", ios::out);
    if(prueba.fail()){
        cout<<"No se ha podido abrir el archivo"<<endl;
        return;
    }
    // TODO
    // NOMBREDEESTRUCTURA.generarGraphviz()
    string kionda = this->pre;

    //cout<<"\n\n\n"<<kionda<<"\n\n";
    prueba<<"digraph G {\n"
            "rankdir=\"LR\";\n\n"
          << kionda<<
          "}";

    prueba.close();
    system("dot -Tpng C:\\Users\\yasmi\\OneDrive\\Escritorio\\ArbolPreorder.dot > C:\\Users\\yasmi\\OneDrive\\Escritorio\\ArbolPreorder.png");

    char url[100] = "C:\\Users\\yasmi\\OneDrive\\Escritorio\\ArbolPreorder.png";
    ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}

void ArbolBinario::generarEnorder(ArbolBinario::Nodo *raiz) {
// izq raiz der

    if(raiz == NULL){
        en += "";
    } else{

        if(raiz->izquierda){
            generarEnorder(raiz->izquierda);
        }
        en += raiz->nombre + " ->";
        if(raiz->derecha){
            generarEnorder(raiz->derecha);
        }
    }
}
void ArbolBinario::iniciarEnorder() {
    generarEnorder(this->arbol);

    if (!en.empty()) {
        en.resize(en.size() - 1);
        en.resize(en.size() - 1);
    }

    en += ";";

    ofstream prueba;
    prueba.open("C:\\Users\\yasmi\\OneDrive\\Escritorio\\ArbolEnOrder.dot", ios::out);
    if(prueba.fail()){
        cout<<"No se ha podido abrir el archivo"<<endl;
        return;
    }
    // TODO
    // NOMBREDEESTRUCTURA.generarGraphviz()
    string kionda = this->en;

    //cout<<"\n\n\n"<<kionda<<"\n\n";
    prueba<<"digraph G {\n"
            "rankdir=\"LR\";\n\n"
          << kionda<<
          "}";

    prueba.close();
    system("dot -Tpng C:\\Users\\yasmi\\OneDrive\\Escritorio\\ArbolEnOrder.dot > C:\\Users\\yasmi\\OneDrive\\Escritorio\\ArbolEnOrder.png");

    char url[100] = "C:\\Users\\yasmi\\OneDrive\\Escritorio\\ArbolEnOrder.png";
    ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}

void ArbolBinario::generarPostorder(ArbolBinario::Nodo *raiz) {
// izq  der raiz

    if(raiz == NULL){
        post += "";
    } else{

        if(raiz->izquierda){
            generarPostorder(raiz->izquierda);
        }
        if(raiz->derecha){
            generarPostorder(raiz->derecha);
        }
        post += raiz->nombre + " ->";
    }
}
void ArbolBinario::iniciarPostorder() {
    generarPostorder(this->arbol);

    if (!post.empty()) {
        post.resize(post.size() - 1);
        post.resize(post.size() - 1);
    }

    post += ";";

    ofstream prueba;
    prueba.open("C:\\Users\\yasmi\\OneDrive\\Escritorio\\ArbolPostOrder.dot", ios::out);
    if(prueba.fail()){
        cout<<"No se ha podido abrir el archivo"<<endl;
        return;
    }
    // TODO
    // NOMBREDEESTRUCTURA.generarGraphviz()
    string kionda = this->post;

    //cout<<"\n\n\n"<<kionda<<"\n\n";
    prueba<<"digraph G {\n"
            "rankdir=\"LR\";\n\n"
          << kionda<<
          "}";

    prueba.close();
    system("dot -Tpng C:\\Users\\yasmi\\OneDrive\\Escritorio\\ArbolPostOrder.dot > C:\\Users\\yasmi\\OneDrive\\Escritorio\\ArbolPostOrder.png");

    char url[100] = "C:\\Users\\yasmi\\OneDrive\\Escritorio\\ArbolPostOrder.png";
    ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}




#endif //PREOYECTO1_ARBOLBINARIO_H
