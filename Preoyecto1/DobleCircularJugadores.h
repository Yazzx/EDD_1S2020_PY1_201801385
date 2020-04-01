//
// Created by yasmi on 31/03/2020.
//

#ifndef PREOYECTO1_DOBLECIRCULARJUGADORES_H
#define PREOYECTO1_DOBLECIRCULARJUGADORES_H

#include "ObjJugador.h"
class DobleCircularJugadores
{
public:
    bool tienealgo = false, existe= false;
    int contanodos = 0;
    class Nodo
    {
    public:
        ObjJugador jugador;
        int correlativo;
        Nodo *siguiente;
        Nodo *anterior;
    } * ultimo, *actual, *nuevo, *auxiliar;

    void eliminarTodo();
    void insertar(ObjJugador jugador);
    void mostrarLista();
    ObjJugador buscar(int correlativo);
    string generarGraphviz();
    void iniciargenerarGraphviz();
    bool tieneAlgo();

};


void DobleCircularJugadores::insertar(ObjJugador jugador) {

    if (!ultimo)
    {

        ultimo = new (Nodo);
        nuevo = new (Nodo);

        nuevo->jugador = jugador;
        nuevo->correlativo = contanodos;
        contanodos++;

        ultimo = nuevo;
        ultimo->siguiente = ultimo;
        ultimo->anterior = ultimo;

        tienealgo = true;
        return;
    }
    else
    {
        nuevo = new (Nodo);

        nuevo->jugador = jugador;
        nuevo->correlativo = contanodos;
        contanodos++;

        nuevo->siguiente = ultimo->siguiente; // ultimo->siguiente = primero
        ultimo->siguiente->anterior = nuevo;
        nuevo->anterior = ultimo;
        ultimo->siguiente = nuevo;
        ultimo = nuevo;
        tienealgo = true;
    }

}

void DobleCircularJugadores::mostrarLista() {

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
        cout << "\t\t"<<actual->correlativo << " " << actual->jugador.nombre << endl;

        actual = actual->siguiente;

    } while (actual != ultimo->siguiente);

    cout<<endl;
    cout<<endl;
    cout << "La lista ha finalizado" << endl;
}

string DobleCircularJugadores::generarGraphviz() {

    string gg;

    actual = ultimo->siguiente;

    do{
        string correl = to_string(actual->correlativo);

        gg = gg + correl + " [label = \"" + correl + ". " + actual->jugador.nombre + "\"];\n" ;

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

void DobleCircularJugadores::iniciargenerarGraphviz() {

    ofstream prueba;
    prueba.open("C:\\Users\\yasmi\\OneDrive\\Escritorio\\ListaCircular.dot", ios::out);
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

    system("dot -Tpng C:\\Users\\yasmi\\OneDrive\\Escritorio\\ListaCircular.dot > C:\\Users\\yasmi\\OneDrive\\Escritorio\\ListaCircular.png");

    //
    char url[100] = "C:\\Users\\yasmi\\OneDrive\\Escritorio\\ListaCircular.png";
    ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}

void DobleCircularJugadores::eliminarTodo() {

    if(!ultimo){
        cout<<"La lista está vacia"<<endl;
        return;
    }

    ultimo = NULL;
    contanodos = 0;

    tienealgo = false;

    this->mostrarLista();
    cout<<"Lista Mostrada\n";

}

ObjJugador DobleCircularJugadores::buscar(int correlativo) {
    if (!ultimo)
    {
        cout << "La lista está vacía :c" << endl;
        existe = false;
        return ObjJugador();
    }

    actual = ultimo->siguiente;

    do
    {
        if (actual->correlativo == correlativo)
        {

            existe = true;
            return actual->jugador;
        }

        actual = actual->siguiente;

    } while (actual != ultimo->siguiente);

    if (!existe)
    {
        cout << "No se econtro la referencia" << endl;
        existe = false;
        return ObjJugador();
    }
    return ObjJugador();

}



#endif //PREOYECTO1_DOBLECIRCULARJUGADORES_H
