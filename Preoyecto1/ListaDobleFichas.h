//
// Created by yasmi on 23/03/2020.
//

#ifndef PREOYECTO1_LISTADOBLEFICHAS_H
#define PREOYECTO1_LISTADOBLEFICHAS_H
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <iostream>
#include <bits/stdc++.h>
#include <cctype>
#include <cstring>
#include <cstdio>


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
    void iniciarGenerarGraphviz();
    Nodo* buscarficha(char letra);
    void eliminarFicha(char letra);
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
    }
    else {
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

void ListaDobleFichas::iniciarGenerarGraphviz() {

    ofstream prueba;
    prueba.open("C:\\Users\\yasmi\\OneDrive\\Escritorio\\ListaFichasJugador.dot", ios::out);
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

    system("dot -Tpng C:\\Users\\yasmi\\OneDrive\\Escritorio\\ListaFichasJugador.dot > C:\\Users\\yasmi\\OneDrive\\Escritorio\\ListaFichasJugador.png");

    //
    char url[100] = "C:\\Users\\yasmi\\OneDrive\\Escritorio\\ListaFichasJugador.png";
    ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}

ListaDobleFichas::Nodo *ListaDobleFichas::buscarficha(char letra) {

    actual = this->primero;

    while(actual != NULL){

        if(char(tolower(actual->ficha.getLetra())) == char(tolower(letra))){

            return actual;

        }
        actual = actual->siguiente;
    }

    return NULL;
}

void ListaDobleFichas::eliminarFicha(char letra) {
    this->actual = this->primero;

    while(actual != NULL){
        if(actual->ficha.getLetra() == letra){

            if(actual == primero){
                primero = actual->siguiente;
                actual->siguiente->anterior = NULL;
                return;
            } else if(actual == ultimo){
                ultimo->anterior->siguiente = NULL;
                ultimo = ultimo->anterior;
                return;
            } else {
                auxiliar = actual->anterior;

                auxiliar->siguiente = actual->siguiente;
                actual->siguiente->anterior = auxiliar;
                return;
            }

        } else {
            actual = actual->siguiente;
        }
    }

    cout<<"No se entonctró el caracter"<<endl;
    return;

}


#endif //PREOYECTO1_LISTADOBLEFICHAS_H
