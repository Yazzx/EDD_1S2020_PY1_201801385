#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <stdio.h>
#include <windows.h>
#include <fstream>

#include "Libreria/json.hpp"

using json = nlohmann::json;

#include "ListaDobleCircular.h"
#include "Cola.h"
#include "ListaOrdenadaPuntajes.h"
#include "ListaOrdenadaJugadores.h"
#include "ArbolBinario.h"
#include "ListaDobleFichas.h"

using namespace::std;

// bools

bool yametiarchivo = false;

// PRIMERO!!

    int linea;
    void menuDesplegable();
    void coordenar(int xpos, int ypos);
    void meterPrimerMarco();
    void saltarlinea();

// SEGUNDO!!

    void abrirArchivo();
    void mostrarGraphDiccionario();

// JUEGO !!
        // Participantes
        string jugadoor1, jugadoor2;

        void faseParticipantes();

        void faseParticipante1();
        void faseParticipante2();

        void mostrarArbolJugadores();

void faseJuego();


void generarGraphPrueba();


ListaDobleCircular CircularDoble;
Cola ColadeFichas;
ListaOrdenadaJugadores ListaMejoresJugadores;
ListaOrdenadaPuntajes ListaPuntajes;
ArbolBinario ArbolNombres;
ListaDobleFichas ListaFichasJugador;

int main() {
    ColadeFichas.llenarCola();
    meterPrimerMarco();
    return 0;
}



void faseParticipantes(){
    faseParticipante1();
    faseParticipante2();

    cout<<"Jugadores:\n\n"<<endl;
    cout<<"Jugador 1: " + jugadoor1<<endl;
    cout<<"Jugador 2: " + jugadoor2<<endl;

    getch();
    system("cls");
    menuDesplegable();
}
void faseParticipante1(){

    system("cls");
    cout << endl;
    cout << "\t\t\t---------------------" << endl; // 15
    cout << "\t\t\t   JUGADOR 1\n" << endl;
    cout << "\t\t\t---------------------" << endl;

    int choice;
    cout<<"Jugador1: \nQue deseas usar?\n\n1.Jugador Existente\n2.Nuevo Jugador\n3.Regresar"<<endl;
    cin>>choice;

    if(choice ==1){
        string nombre1;
        cout<<"Por favor ingresa el nombre de tu jugador"<<endl;
        cin>>nombre1;

        ArbolNombres.yaesta = false;
        ArbolNombres.iniciarbuscar(nombre1);
        if(ArbolNombres.yaesta){
            ArbolNombres.yaesta = false;
            cout<<"Nombre del jugador 1 guardado :D\n\n"<<endl;
            jugadoor1 = nombre1;
            getch();
        }
        else {
            cout<<"No se encuentra el nombre del jugador\n\n"<<endl;
            getch();
            faseParticipante1();

        }

    }
    else if(choice == 2){
        string nombre1;
        cout<<"Por favor ingresa el nombre de tu jugador"<<endl;
        cin>>nombre1;

        ArbolNombres.iniciarInsertar(nombre1);
        if(ArbolNombres.insertcionexitosa){
            cout<<"Nombre del jugador 1 guardado :D\n\n"<<endl;
            jugadoor1 = nombre1;
            getch();
        }
        while(!ArbolNombres.insertcionexitosa){
            string nombree1;
            cout<<"Por favor ingresa el nombre de tu jugador"<<endl;
            cin>>nombree1;

            ArbolNombres.iniciarInsertar(nombree1);
            if(ArbolNombres.insertcionexitosa){
                cout<<"Nombre del jugador 1 guardado :D\n\n"<<endl;
                jugadoor1 = nombree1;
                getch();
            }
        }

    }
    else if(choice == 3){
        system("cls");
        jugadoor1 = "";
        jugadoor2 = "";
        menuDesplegable();
    }
    else {
        cout<<"Por favor escoge una opcion valida\n\n"<<endl;
        getch();
        system("cls");

        jugadoor1 = "";
        jugadoor2 = "";
        menuDesplegable();
    }
}
void faseParticipante2(){
    system("cls");
    cout << endl;
    cout << "\t\t\t---------------------" << endl; // 15
    cout << "\t\t\t   JUGADOR 2\n" << endl;
    cout << "\t\t\t---------------------" << endl;

    int choice;
    cout<<"Jugador2: \nQue deseas usar?\n\n1.Jugador Existente\n2.Nuevo Jugador\n3.Regresar"<<endl;
    cin>>choice;

    if(choice ==1){
        string nombre1;
        cout<<"Por favor ingresa el nombre de tu jugador"<<endl;
        cin>>nombre1;

        ArbolNombres.yaesta = false;
        ArbolNombres.iniciarbuscar(nombre1);
        if(ArbolNombres.yaesta){
            if(nombre1.compare(jugadoor1) != 0){
                ArbolNombres.yaesta = false;
                cout<<"Nombre del jugador 2 guardado :D\n\n"<<endl;
                jugadoor2 = nombre1;
                getch();
            }
            else {
                cout<<"El nombre que elegiste es invalido :C\n\n"<<endl;
                getch();
                faseParticipante2();

            }
        } else {
            cout<<"No se encuentra el nombre del jugador\n\n"<<endl;
            faseParticipante2();
            getch();
        }

    }
    else if(choice == 2){
        string nombre1;
        cout<<"Por favor ingresa el nombre de tu jugador"<<endl;
        cin>>nombre1;

        ArbolNombres.iniciarInsertar(nombre1);
        if(ArbolNombres.insertcionexitosa){
            cout<<"Nombre del jugador 1 guardado :D\n\n"<<endl;
            jugadoor2 = nombre1;
            getch();
        }
        while(!ArbolNombres.insertcionexitosa){
            string nombree1;
            cout<<"Por favor ingresa el nombre de tu jugador"<<endl;
            cin>>nombree1;

            ArbolNombres.iniciarInsertar(nombree1);
            if(ArbolNombres.insertcionexitosa){
                cout<<"Nombre del jugador 1 guardado :D\n\n"<<endl;
                jugadoor2 = nombree1;
                getch();
            }
        }

    }
    else if(choice == 3){
        system("cls");
        jugadoor1 = "";
        jugadoor2 = "";
        menuDesplegable();
    }
    else {
        cout<<"Por favor escoge una opcion valida\n\n"<<endl;
        getch();
        system("cls");
        jugadoor1 = "";
        jugadoor2 = "";
        menuDesplegable();
    }
}

void mostrarArbolJugadores(){
    system("cls");
    cout << endl;
    cout << "\t\t\t---------------------" << endl; // 15
    cout << "\t\t\t\tJUGADORES\n" << endl;
    cout << "\t\t\t---------------------" << endl;

    cout << "1. Arbol Binario" << endl;
    cout << "2. Arbol Preorder" << endl;
    cout << "3. Arbol Enorder" << endl;
    cout << "4. Arbol Postorder" << endl;
    cout << "5. Regresar" << endl;

    int respuesta;
    cin >> respuesta;

    switch (respuesta) {
        case 1: // arbol
            ArbolNombres.iniciargenerarGraphviz();
            mostrarArbolJugadores();
            ArbolNombres.grafo = "";
            break;
        case 2:  // pre
            ArbolNombres.iniciarPreorder();
            mostrarArbolJugadores();
            ArbolNombres.pre = "";
            break;
        case 3: // en
            ArbolNombres.iniciarEnorder();
            mostrarArbolJugadores();
            ArbolNombres.en = "";
            break;
        case 4: // post
            ArbolNombres.iniciarPostorder();
            mostrarArbolJugadores();
            ArbolNombres.post = "";
            break;
        case 5:
            system("cls");
            menuDesplegable();
            break;
        default:
            cout << "Ingresaste un caracter no válido :C" << endl;
    }
}

void abrirArchivo(){
    system("cls");
    string ruta;
    printf("Ingrese ruta de su archivo: ");
    cin >> ruta;

    CircularDoble.eliminarTodo();

    ifstream i(ruta);
    json mijson;
    i >> mijson;

    // Leyendo Archivo

    int dimension = mijson.at("dimension");
    printf("el tamaño de la tabla es: " + dimension);


    //table = new Matrix(dimension);
/*
    // Special cells
    // Doubles
    for(int i = 0; i < j.at("casillas").at("dobles").size(); i++){
        int x = j.at("casillas").at("dobles")[i].at("x");
        int y = j.at("casillas").at("dobles")[i].at("y");
        table->InsertSpecialNode(x, y, 2);
    }

    // Triples
    for(int i = 0; i < j.at("casillas").at("triples").size(); i++){
        int x = j.at("casillas").at("triples")[i].at("x");
        int y = j.at("casillas").at("triples")[i].at("y");
        table->InsertSpecialNode(x, y, 3);
    }
*/
    // Diccionario

    for(int i = 0; i < mijson.at("diccionario").size(); i++){
        CircularDoble.insertar(mijson.at("diccionario")[i].at("palabra"));
    }

    CircularDoble.mostrarLista();
    yametiarchivo = true;
    getch();
    system("cls");
    menuDesplegable();

}
void mostrarGraphDiccionario(){
    if(yametiarchivo){
        char url[100] = "C:\\Users\\yasmi\\OneDrive\\Escritorio\\ListaCircular.png";
        ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
    } else {
        cout<<"Por favor ingresa un archivo"<<endl;
    }
    system("cls");
    menuDesplegable();
}

void saltarlinea(){
    linea++;
    coordenar(3,linea);
}
void meterPrimerMarco(){

    system("cls");

    for (int j = 1; j < 7; ++j) {
        coordenar(1, j);
        printf("|");
        coordenar(90, j);
        printf("|");

    }
    for (int i = 2; i < 90; ++i) {
        coordenar(i,0);
        printf("-");
        coordenar(i,7);
        printf("-");
    }

    coordenar(1,3);
    saltarlinea();

    printf("UNIVERSIDAD DE SAN CARLOS DE GUATEMALA"); saltarlinea();
    printf("FACULTAD DE INGENIERIA"); saltarlinea();
    printf("ESTRUCTURAS DE DATOS"); saltarlinea();
    printf("PROYECTO 1"); saltarlinea();
    printf("YASMIN ELISA MONTERROSO ESCOBEDO"); saltarlinea();
    printf("201801385"); saltarlinea();

    menuDesplegable();
}
void menuDesplegable() {

    cout << endl;
    cout << "\t\t\t---------------------" << endl; // 15
    cout << "\t\t\t\tMENU\n" << endl;
    cout << "\t\t\t---------------------" << endl;
    cout << "1. Jugar" << endl;
    cout << "2. Insertar Archivo" << endl;
    cout << "3. Jugadores" << endl;
    cout << "4. Mejores Puntajes" << endl;
    cout << "5. Diccionario" << endl;
    cout << "6. Fichas Disponibles" << endl;
    cout << "7. Salir\n\n" << endl;
    cout << endl;

    int respuesta;
    cin >> respuesta;

    switch (respuesta) {
        case 1: // jugar
            faseParticipantes();
            break;
        case 2:  // insertar archivo
            abrirArchivo();
            break;
        case 3: // jugadores
            mostrarArbolJugadores();
        break;
        case 4: // mejores puntajes

            break;
        case 5: // Diccionario
            CircularDoble.iniciargenerarGraphviz();
            system("cls");
            menuDesplegable();
            break;
        case 6: // fichas disponibles
            ColadeFichas.iniciarGenerarGraphviz();
            system("cls");
            menuDesplegable();
            break;
        case 7: // salir
            cout<< "Gracias por usar este programa!! :D"<<endl;
            getch();
            exit(0);
            break;
        default:
            cout << "Ingresaste un caracter no válido :C" << endl;
    }

}
void coordenar(int xpos, int ypos){

    // pone el cursor en cierta posicion
    HANDLE handle_consola;
    handle_consola = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD posicion;
    posicion.X = xpos;
    posicion.Y = ypos;
    SetConsoleCursorPosition(handle_consola, posicion);

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