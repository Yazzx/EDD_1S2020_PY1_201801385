#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <stdio.h>
#include <windows.h>
#include <fstream>

#include "ListaDobleCircular.h"
#include "Cola.h"
#include "ListaOrdenadaPuntajes.h"
#include "ListaOrdenadaJugadores.h"
#include "ArbolBinario.h"

using namespace::std;


void generarGraphPrueba();

ListaDobleCircular CircularDoble;
Cola ColadeFichas;
ListaOrdenadaJugadores ListaMejoresJugadores;
ArbolBinario ArbolNombres;

int main() {
    std::cout << "Pruebas de estructuras" << std::endl;

    // circularDoble, Arboldenombres string
    // ordenadapuntajes: int

    int insertando, buscando;


    cout << "INSERTANDO" << endl;
    //getch();


    for (size_t i = 0; i < 8; i++)
    {
        string insertando;
        cout << "inserte algo" << endl;
        cin >> insertando;

        ArbolNombres.iniciarInsertar(insertando);
    }
    //getch();
    cout<<"Mostranding\n\n";
    ArbolNombres.iniciarmostrar();
    cout<<"\n\n\n\n";
    getch();

    /*cout << "BUSCANDO" << endl;
    getch();
    for (size_t i = 0; i < 4; i++)
    {
        cout << "Busque un caracter" << endl;
        cin >> buscando;
        ListaPuntajesdeJugador.buscar(buscando);
    }*/

    /* cout << "ELIMINANDO" << endl;
    getch();
    lista.eliminarFinal();
    lista.mostrarLista();
    getch(); */

    cout << "GENERANDO GRAPHVIZ" << endl;
    getch();

    //ColadeFichas.llenarCola();
   generarGraphPrueba();


    return 0;
}

void generarGraphPrueba(){

    ofstream prueba;
    prueba.open("C:\\Users\\yasmi\\OneDrive\\Escritorio\\Prueba.dot", ios::out);
    if(prueba.fail()){
        cout<<"No se ha podido abrir el archivo"<<endl;
        return;
    }
    // TODO
    // NOMBREDEESTRUCTURA.generarGraphviz()
    string kionda = ArbolNombres.iniciargenerarGraphviz();

    cout<<"\n\n\n"<<kionda<<"\n\n";
    prueba<<"digraph G {\n"
              "\n"
              " node [shape=box];\n"
            << kionda<<
            "}";

    prueba.close();

    system("dot -Tpng C:\\Users\\yasmi\\OneDrive\\Escritorio\\Prueba.dot > C:\\Users\\yasmi\\OneDrive\\Escritorio\\Prueba.png");

    char url[100] = "C:\\Users\\yasmi\\OneDrive\\Escritorio\\Prueba.png";
    ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}
