//
// Created by yasmi on 10/03/2020.
//

#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <stdio.h>
#include <windows.h>
#include <fstream>

using namespace::std;

#ifndef PREOYECTO1_LISTADOBLECIRCULAR_H
#define PREOYECTO1_LISTADOBLECIRCULAR_H

// Acá van las palabras que ingresan del JSON

class CircularDoble
{
public:
    bool esVacia = true, palabradada= false;
    int contanodos = 0;
    class Nodo
    {
    public:
        string palabra;
        int correlativo;
        Nodo *siguiente;
        Nodo *anterior;
    } * ultimo, *actual, *nuevo, *auxiliar;

    bool isVacia() const;

    void insertar(string palabra);
    void mostrarLista();
    bool buscarEnLista(string palabra);
    string generarGraphviz();

};

bool CircularDoble::isVacia() const {
    return esVacia;
}

void CircularDoble::insertar(string palabra) {

    if (!ultimo)
    {

        ultimo = new (Nodo);
        nuevo = new (Nodo);

        nuevo->palabra = palabra;
        nuevo->correlativo = contanodos;
        contanodos++;

        ultimo = nuevo;
        ultimo->siguiente = ultimo;
        ultimo->anterior = ultimo;

        esVacia = false;
        return;
    }
    else
    {
        nuevo = new (Nodo);

        nuevo->palabra = palabra;
        nuevo->correlativo = contanodos;
        contanodos++;

        nuevo->siguiente = ultimo->siguiente; // ultimo->siguiente = primero
        ultimo->siguiente->anterior = nuevo;
        nuevo->anterior = ultimo;
        ultimo->siguiente = nuevo;
        ultimo = nuevo;
        esVacia = false;
    }

}

void CircularDoble::mostrarLista() {

    cout<<endl;
    cout<<endl;
    if (!ultimo)
    {
        cout << "La lista esta vacia :C" << endl;
        return;

    }
    actual = ultimo->siguiente;

    do
    {
        cout << "\t\t"<<actual->correlativo << " " << actual->palabra << endl;

        actual = actual->siguiente;

    } while (actual != ultimo->siguiente);

    cout<<endl;
    cout<<endl;
    cout << "La lista ha finalizado" << endl;
}

bool CircularDoble::buscarEnLista(string palabra) {
    bool encontrado = false;

    if (!ultimo)
    {
        cout << "La lista está vacía :c" << endl;
        palabradada = false;
        return false;
    }

    actual = ultimo->siguiente;

    do
    {
        if (actual->palabra.compare(palabra) == 0)
        {

            palabradada = true;

            return true;
        }

        actual = actual->siguiente;

    } while (actual != ultimo->siguiente);

    if (!encontrado)
    {
        cout << "No se econtro la referencia" << endl;
        palabradada = false;
        return false;
    }
    return false;
}

string CircularDoble::generarGraphviz() {
    string gg;

    actual = ultimo->siguiente;

    do{
        string correl = to_string(actual->correlativo);

        gg = gg + correl + " [label = \"" + actual->palabra + "\"];\n" ;

        actual = actual->siguiente;
    }while(actual != ultimo->siguiente);

    actual = ultimo->siguiente;

    int ultimo_correl;
    do{
        string correl = to_string(actual->correlativo);
        string correl_s = to_string(actual->siguiente->correlativo);

        gg = gg + correl + " -> "+ correl_s + ";";

        ultimo_correl = actual->siguiente->correlativo;

        actual = actual->siguiente;
    }while(actual != ultimo->siguiente);

    for(int i = --ultimo_correl; i>= 0 ;--i){
        string numero = to_string(i);

        if( i == 0){

            gg = gg + "0;";
        }else{
            gg = gg + numero + "->";
        }

    }

    return gg;
}


#endif //PREOYECTO1_LISTADOBLECIRCULAR_H
