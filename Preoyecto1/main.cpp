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
ListaOrdenadaPuntajes ListaPuntajes;
ArbolBinario ArbolNombres;

int main() {
    std::cout << "Pruebas de estructuras" << std::endl;
int insertando, buscando;

    cout << "INSERTANDO" << endl;
    //getch();

    ObjJugador uno;
    uno.setNombre("Carmen");


    for (size_t i = 0; i < 6; i++)
    {
        insertando;
        cout << "inserte algo a " << uno.getNombre()<< endl;
        cin >> insertando;

        uno.ListaPuntajesdeJugador.insertar(insertando);
    }
    uno.ListaPuntajesdeJugador.mostrarLista();
    ListaMejoresJugadores.insertar(uno);


    cout<<"\n\n";
    ObjJugador dos;
    dos.setNombre("Ithali");
    for (size_t i = 0; i < 6; i++)
    {
        insertando;
        cout << "inserte algo a " << dos.getNombre()<< endl;
        cin >> insertando;

        dos.ListaPuntajesdeJugador.insertar(insertando);
    }
    dos.ListaPuntajesdeJugador.mostrarLista();
    ListaMejoresJugadores.insertar(dos);

    cout<<"\n\n";
    ObjJugador tres;
    tres.setNombre("Maria");
    for (size_t i = 0; i < 6; i++)
    {
        insertando;
        cout << "inserte algo a " << tres.getNombre()<< endl;
        cin >> insertando;

        tres.ListaPuntajesdeJugador.insertar(insertando);
    }
    tres.ListaPuntajesdeJugador.mostrarLista();
    ListaMejoresJugadores.insertar(tres);


    cout<<"\nMOSTRANDO\n\n";

    ListaMejoresJugadores.mostrarLista();




    cout << "GENERANDO GRAPHVIZ" << endl;
    getch();

   ColadeFichas.llenarCola();
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
    string kionda = ListaMejoresJugadores.generarGraphviz();

    //cout<<"\n\n\n"<<kionda<<"\n\n";
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
