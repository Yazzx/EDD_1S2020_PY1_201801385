#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <stdio.h>
#include <windows.h>
#include <fstream>

#include "ListaDobleCircular.h"

using namespace::std;


void generarGraphPrueba();

ListaDobleCircular CircularDoble;

int main() {
    std::cout << "Pruebas de estructuras" << std::endl;

    // circularDoble: string
    string insertando, buscando;

    cout << "INSERTANDO" << endl;
    getch();
    for (size_t i = 0; i < 4; i++)
    {
        cout << "inserte una palabra" << endl;
        cin >> insertando;
        CircularDoble.insertar(insertando);
    }
    CircularDoble.mostrarLista();
    getch();

    cout << "BUSCANDO" << endl;
    getch();
    for (size_t i = 0; i < 4; i++)
    {
        cout << "Busque un caracter" << endl;
        cin >> buscando;
        CircularDoble.buscar(buscando);
    }

    /* cout << "ELIMINANDO" << endl;
    getch();
    lista.eliminarFinal();
    lista.mostrarLista();
    getch(); */

    cout << "GENERANDO GRAPHVIZ" << endl;
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
    string kionda = CircularDoble.generarGraphviz();

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
