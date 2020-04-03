//
// Created by yasmi on 21/03/2020.
//

#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <stdio.h>
#include <windows.h>
#include <fstream>

#ifndef PREOYECTO1_LISTAORDENADAPUNTAJES_H
#define PREOYECTO1_LISTAORDENADAPUNTAJES_H


using namespace::std;

class ListaOrdenadaPuntajes{

public:
    bool esVacia = true;
    int contanodos = 0;
    class Nodo
    {
    public:
        int puntaje;
        int correlativo;
        Nodo *siguiente;
    } * ultimo,*primero, *actual, *nuevo, *auxiliar;

    ListaOrdenadaPuntajes(){
        this->primero = this->ultimo = this->actual = this->nuevo = this->auxiliar = NULL;
    }
    bool isVacia() const;

    void insertar(int puntaje);
    void mostrarLista();
    string generarGraphviz();
    void iniciarGenerarGraphviz();
    void ordenar();
    int getPrimero();
};

bool ListaOrdenadaPuntajes::isVacia() const {
    return this->esVacia;
}

void ListaOrdenadaPuntajes::insertar(int puntaje) {
    if(!primero){
        esVacia = false;
        primero = new (Nodo);
        ultimo = new (Nodo);
        nuevo = new (Nodo);

        nuevo->puntaje = puntaje;
        contanodos++;
        nuevo->correlativo = contanodos;

        primero = nuevo;
        ultimo = nuevo;
        return;
    }
    else {
        nuevo = new (Nodo);
        nuevo->puntaje = puntaje;
        contanodos++;
        nuevo->correlativo = contanodos;

        nuevo->siguiente = primero;
        primero = nuevo;
    }

    return;
}

void ListaOrdenadaPuntajes::mostrarLista() {
    cout<<endl;
    cout<<endl;
    if (esVacia)
    {
        cout << "La lista esta vacia :C" << endl;
        return;

    }


    this->ordenar();

    actual = primero;

    do
    {
        cout << actual->puntaje << endl;

        actual = actual->siguiente;

    } while (actual != ultimo->siguiente);

    cout<<endl;
    cout<<endl;
    cout << "La lista ha finalizado" << endl;
}

string ListaOrdenadaPuntajes::generarGraphviz() {
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
        string puntaje = to_string(actual->puntaje);

        lista = lista + numero + " [label = \"" + puntaje + " pts\"];\n";
        contador++;
        actual = actual->siguiente;
    }

    return lista;
}

void ListaOrdenadaPuntajes::ordenar() {

        actual = primero;

        while(actual != NULL){

            auxiliar = actual->siguiente;

            while(auxiliar != NULL){

                if(auxiliar != ultimo->siguiente && actual!= NULL){
                    cout<<"comparando "<<auxiliar->puntaje<<" con "<< actual->puntaje<<" ;\n";
                    if(auxiliar->puntaje > actual->puntaje){

                        int aux = auxiliar->puntaje;

                        auxiliar->puntaje = actual->puntaje;

                        actual->puntaje = aux;
                    }

                    auxiliar = auxiliar->siguiente;
                } else {
                    return;
                }
            }

            actual = actual->siguiente;
        }
}

int ListaOrdenadaPuntajes::getPrimero() {
    if(!primero){
        return 0;
    }
    return this->primero->puntaje;
}

void ListaOrdenadaPuntajes::iniciarGenerarGraphviz() {

    ofstream prueba;
    prueba.open("C:\\Users\\yasmi\\OneDrive\\Escritorio\\PuntajesIndividuales.dot", ios::out);
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

    system("dot -Tpng C:\\Users\\yasmi\\OneDrive\\Escritorio\\PuntajesIndividuales.dot > C:\\Users\\yasmi\\OneDrive\\Escritorio\\PuntajesIndividuales.png");

    //
    char url[100] = "C:\\Users\\yasmi\\OneDrive\\Escritorio\\PuntajesIndividuales.png";
    ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);

}


#endif //PREOYECTO1_LISTAORDENADAPUNTAJES_H
