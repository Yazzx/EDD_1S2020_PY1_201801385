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
#include "ListaDobleFichas.h"

using namespace::std;


void generarGraphPrueba();

ListaDobleCircular CircularDoble;
Cola ColadeFichas;
ListaOrdenadaJugadores ListaMejoresJugadores;
ListaOrdenadaPuntajes ListaPuntajes;
ArbolBinario ArbolNombres;
ListaDobleFichas ListaFichasJugador;

int main() {
    std::cout << "Pruebas de estructuras" << std::endl;
    ColadeFichas.llenarCola();


int insertando, buscando;

    cout << "INSERTANDO" << endl;
    //getch();

    for (int i = 0; i < 7; ++i) {

        ObjFicha ficha = ColadeFichas.pop();
        ListaFichasJugador.insertar(ficha);
    }

    cout<<"\nMOSTRANDO\n\n";

    ListaFichasJugador.mostrarLista();

    cout << "GENERANDO GRAPHVIZ" << endl;
    getch();


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
    string kionda = ListaFichasJugador.generarGraphviz();

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
