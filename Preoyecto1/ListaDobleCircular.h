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

class ListaDobleCircular
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
    bool buscar(string palabra);
    string generarGraphviz();

};

bool ListaDobleCircular::isVacia() const {
    return esVacia;
}

void ListaDobleCircular::insertar(string palabra) {

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

void ListaDobleCircular::mostrarLista() {

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

bool ListaDobleCircular::buscar(string palabra) {
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

string ListaDobleCircular::generarGraphviz() {
    string gg;

    actual = ultimo->siguiente;

    do{
        string correl = to_string(actual->correlativo);

        gg = gg + correl + " [label = \"" + actual->palabra + "\"];\n" ;

        actual = actual->siguiente;
    }while(actual != ultimo->siguiente);

    gg = gg + "{ rank=same ";
    do{
        string correl = to_string(actual->correlativo);

        gg = gg + correl + " " ;

        if(actual == ultimo){
            gg = gg + " }";
        }

        actual = actual->siguiente;
    }while(actual != ultimo->siguiente);

    actual = ultimo->siguiente;

    do{
        string correl = to_string(actual->correlativo);
        string correl_s = to_string(actual->siguiente->correlativo);

        gg = gg + correl + " -> "+ correl_s + ";\n";
        gg = gg + correl_s + " -> "+ correl + ";\n";

        actual = actual->siguiente;
    }while(actual != ultimo->siguiente);



    return gg;
}


#endif //PREOYECTO1_LISTADOBLECIRCULAR_H
