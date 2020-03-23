//
// Created by yasmi on 21/03/2020.
//

#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <stdio.h>
#include <windows.h>
#include <fstream>
#include "ObjJugador.h"

#ifndef PREOYECTO1_LISTAORDENADAJUGADORES_H
#define PREOYECTO1_LISTAORDENADAJUGADORES_H

using namespace::std;

class ListaOrdenadaJugadores{
public:
    bool esVacia = true;
    int contanodos = 0;
    class Nodo
    {
    public:
        ObjJugador jugador;
        int correlativo;
        Nodo *siguiente;
    } * ultimo,*primero, *actual, *nuevo, *auxiliar;

    bool isVacia() const;

    void editar(ObjJugador);
    void insertar(ObjJugador jugador);
    void mostrarLista();
    string generarGraphviz();
    bool buscar(ObjJugador jugador);
    void ordenar();
};

bool ListaOrdenadaJugadores::isVacia() const {
    return this->esVacia;
}

void ListaOrdenadaJugadores::insertar(ObjJugador jugador) {
    if(!primero){
        esVacia = false;
        primero = new (Nodo);
        ultimo = new (Nodo);
        nuevo = new (Nodo);

        nuevo->jugador = jugador;
        contanodos++;
        nuevo->correlativo = contanodos;

        primero = nuevo;
        ultimo = nuevo;
        return;
    }
    // si si lo encuentra
   /* else if(buscar(jugador) == true){
        editar(jugador);
        this->ordenar();
        return;
    }*/
    else {
        nuevo = new (Nodo);
        nuevo->jugador = jugador;
        contanodos++;
        nuevo->correlativo = contanodos;

        nuevo->siguiente = primero;
        primero = nuevo;
    }


    //this->ordenar();
    return;
}

void ListaOrdenadaJugadores::mostrarLista() {
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
        cout << "\t\t"<<actual->correlativo << " " << actual->jugador.getNombre()<< " "<<actual->jugador.getPuntajeAlto() << endl;

        actual = actual->siguiente;

    } while (actual != ultimo->siguiente);

    cout<<endl;
    cout<<endl;
    cout << "La lista ha finalizado" << endl;
}

string ListaOrdenadaJugadores::generarGraphviz() {
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
        string puntaje = to_string(actual->jugador.getPuntajeAlto());

        lista += numero + " [label = \"" + actual->jugador.getNombre() + ": " + puntaje + " pts\"];\n";
        contador++;
        actual = actual->siguiente;
    }

    return lista;
}

void ListaOrdenadaJugadores::ordenar() {
/*
    actual = primero;

    while(actual != ultimo->siguiente){

        auxiliar = actual->siguiente;

        while(auxiliar != ultimo->siguiente){

            if(auxiliar->jugador.ListaPuntajesdeJugador.getPrimero() > actual->jugador.ListaPuntajesdeJugador.getPrimero()){

                ObjJugador aux = auxiliar->jugador;

                auxiliar->jugador = actual->jugador;

                actual->jugador = aux;
            }

            auxiliar = auxiliar->siguiente;
        }

        actual = actual->siguiente;
    }
*/
}

void ListaOrdenadaJugadores::editar(ObjJugador jugador) {
    actual = primero;
    auxiliar = NULL;
    while(actual != NULL){

        if((actual->jugador.getNombre()).compare(jugador.getNombre()) == 0){

            actual->jugador = jugador;

            return;
        }
        actual = actual->siguiente;
    }
}

bool ListaOrdenadaJugadores::buscar(ObjJugador jugador) {

    if(!primero){
        cout<<"La lista está vacía :c"<<endl;
        return false;
    }
    actual = primero;
    auxiliar = NULL;
    while(actual != NULL){

        if((actual->jugador.getNombre()).compare(jugador.getNombre()) == 0){
            return true;
        }

        auxiliar = actual;
        actual = actual->siguiente;
    }

    return false;
}

#endif //PREOYECTO1_LISTAORDENADAJUGADORES_H
