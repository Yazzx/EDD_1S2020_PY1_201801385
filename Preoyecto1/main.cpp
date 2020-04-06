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
#include "Matriz.h"
#include "DobleCircularJugadores.h"

using namespace::std;


// PRIMERO!!

int linea;
void menuDesplegable();
void coordenar(int xpos, int ypos);
void meterPrimerMarco();
void saltarlinea();

// SEGUNDO!!
bool yametiarchivo = false;
void abrirArchivo();
void mostrarGraphDiccionario();

// JUEGO !!

int puntaje1 = 0;
int puntaje2 = 0;

// Participantes
ObjJugador jugador1;
ObjJugador jugador2;

void faseParticipantes();
void participante1();
void participante2();

void insertarJugador();

void mostrarArbolJugadores();


// ASIGNACION DE FICHAS
void asignarFichas();

// SETTEANDO PRIMER TURNO
void settearTurno();
int turnoactual = 0;

//INICIANDO EL JUEGO
void iniciarJuego();
bool terminado = false;
bool terminar();
void queDeseaHacer(ObjJugador& jugador, int &puntaje, Cola &ColadeFichas);
void ingresarPalabra(ObjJugador& jugador, int &puntaje, Cola &ColadeFichas);
void canjearFichas(ObjJugador& jugador);

// MEJORES PUNTAJES
void mostrarMejoresPuntajes();
ObjJugador jugadorPuntaje;

void faseJuego();

int dimensionP;

ListaDobleCircular CircularDoble;
DobleCircularJugadores CircularJugadores;
Cola ColadeFichas;
ListaOrdenadaJugadores ListaMejoresJugadores;
ListaOrdenadaPuntajes ListaPuntajes;
ArbolBinario ArbolNombres;
ListaDobleFichas ListaFichasJugador;
ListaDobleFichas ListaFichasAux;
Matriz Matrizz;
Matriz MatrizAuxiliar;

int main() {

    meterPrimerMarco();
    return 0;
}

void mostrarMejoresPuntajes(){

    if(CircularJugadores.tienealgo ){
        int choice;
        cout<<"Que deseas hacer?\n1.Ver mejores jugadores\t\t2.Ver mejores puntajes por jugador"<<endl;
        cin>>choice;

        if(choice == 1){
            // mejores jugadores
            ListaMejoresJugadores.iniciarGenerarGraphviz();
            system("cls");
            menuDesplegable();

        } else if(choice == 2){
            CircularJugadores.iniciargenerarGraphviz();
            int correlativo1;
            cout<<"Por favor escoge el correlativo del jugador que deseas ver"<<endl;
            cin>>correlativo1;

            jugadorPuntaje = CircularJugadores.buscar(correlativo1);
            if(jugadorPuntaje.nombre != ""){

                cout<<"Estos son los mejores puntakes de:\n"<<endl;
                cout<<"-----------------> " + jugadorPuntaje.nombre <<endl;

                jugadorPuntaje.generarGraphMejoresPuntajes();
                getch();
                system("cls");
                menuDesplegable();

            } else {
                cout<<"Numero inivalido, por favor escoge otro :c"<<endl;
                getch();
                system("cls");
                menuDesplegable();
            }
        } else {
            cout<<"Numero inivalido, por favor escoge otro :c"<<endl;
            getch();
            system("cls");
            menuDesplegable();

        }

    }
    else {
        cout<<"Deben haber jugadores para mostrar esto!! D:"<<endl;
        getch();
        system("cls");
        menuDesplegable();
    }

}

void faseJuego(){
    if(CircularJugadores.tienealgo && yametiarchivo){
        faseParticipantes();
        asignarFichas();
        settearTurno();
        iniciarJuego();

        //getch();

    }
    else {
        cout<<"Deben haber jugadores y un archivo para jugar!! D:"<<endl;
        getch();
        system("cls");
        menuDesplegable();
    }
}
void iniciarJuego(){
    //system("cls");
    cout << endl;
    cout << "\t\t\t---------------------" << endl; // 15
    cout << "\t\t\t\tJUEGO\n" << endl;
    cout << "\t\t\t---------------------" << endl;

    Matrizz.iniciarGenerarGraphviz();

    if(turnoactual == 1){
        cout<<"El primer turno es de: " + jugador2.nombre <<endl;
    } else {
        cout<<"El primer turno es de: " + jugador1.nombre <<endl;
    }
    getch();

    cout << endl;
    system("cls");
    cout << "\t\t\t---------------------" << endl; // 15
    cout << "\t\t\t\tJUGANDO\n" << endl;
    cout << "\t\t\t---------------------" << endl;

    // turnoactual puede ser 0 o uno, si es 0 es el jugador1,
    // si es 1, es el jugador 2;

    while(!terminado){
        cout<<endl;cout<<endl;
        cout<<endl;

        if(turnoactual == 0){
            cout << "\t------------------------------------------" << endl; // 15
            cout << "\t\t" + jugador1.nombre + "\n" << endl;
            cout << "\t------------------------------------------" << endl;

            jugador1.mostrarFichas();

            cout<<endl;
            queDeseaHacer(jugador1, puntaje1, ColadeFichas);

            bool terminar0 = terminar();
            if(terminar0){
                puntaje1 = jugador1.getPuntajeParcial();
                jugador1.insertarPuntaje(puntaje1);
                break;
            } else {
                turnoactual = 1;
            }

        } else{
            cout << "\t------------------------------------------" << endl; // 15
            cout << "\t\t" + jugador2.nombre + "\n" << endl;
            cout << "\t------------------------------------------" << endl;

            jugador2.mostrarFichas();

            cout<<endl;
            queDeseaHacer(jugador2, puntaje2, ColadeFichas);

            bool terminar1 = terminar();
            if(terminar1){
                puntaje2 = jugador2.getPuntajeParcial();
                jugador2.insertarPuntaje(puntaje2);
                break;
            } else {
                turnoactual = 0;
            }

        }

    }

    //TODO aca muestro los punteos

    jugador1.insertarPuntaje(jugador1.getPuntajeParcial());
    jugador2.insertarPuntaje(jugador2.getPuntajeParcial());

    cout << "\t------------------------------------------" << endl;
    cout << "\t\t\t PUNTAJES FINALES\n" << endl;
    cout << "\t------------------------------------------" << endl;

    cout << "\t--------------------------> Jugador 1: "<<jugador1.getPuntajeParcial() << endl;
    cout << "\t--------------------------> Jugador 2: "<<jugador2.getPuntajeParcial() << endl;

    jugador1.setPuntajeParcial(0);
    jugador2.setPuntajeParcial(0);

    puntaje1 = 0;
    puntaje2 = 0;

    getch();
    //TODO
    //aca va todo lo demas
    system("cls");
    menuDesplegable();
}


void canjearFichas(ObjJugador& jugador){

    int contador = 0, choice;

    while(contador < 7 ){

        cout<<"Que desea hacer?\n1.Canjear letra\t2.Salir"<<endl;
        cin>> choice;

        // ingreso las fichas que necesito
        if(choice == 1){
            contador++;

            char ficha;
            cout<<"\nQue letra desea canjear?"<<endl;
            cin>> ficha;

            jugador.eliminarFicha(ficha);
            ObjFicha oficha = ColadeFichas.pop();
            jugador.insertarFicha(oficha);

            cout<<"Tus fichas son: "<<endl;
            jugador.mostrarFichas();
            getch();

        } else {
            break;
        }
    }

    if(choice == 1){
        cout<<"Ya has gastado todos tus canjes por este turno!"<<endl;
    }

    return;
}
void ingresarPalabra(ObjJugador& jugador, int &puntaje, Cola &ColadeFichas){


    jugador.copiarAuxiliar(ListaFichasAux);

    int choice = 1; int contafichas = 7; int insertadas = 0;
    // para ver cuantas fichas despaché
    // para ver cuantos get siguientes

    // palabra que se esta insertando
    string palabra  = "";

    int xo = -1, yo = -1; int x = 0, y = 0;
    int x_ini = 0, y_ini = 0, x_fin = 0, y_fin = 0;

    int intento = 1;

    while(choice == 1 && intento <= 7){

        intento++;

        cout<<"Que desea hacer?\n1.Ingresar letra\t2.Validar"<<endl;
        cin>> choice;

        // ingreso las fichas que necesito
        if(choice == 1){
            char ficha;
            cout<<"\nQue letra desea ingresar?"<<endl;
            cin>> ficha;

            ObjFicha meter = jugador.sacarficha(ficha);

            if(meter.getLetra() != 0){

                contafichas--;
                insertadas++;

                cout<<"Ingrese la coordenada en x:"<<endl;
                cin>> x;

                if(xo == -1){
                    xo = x;
                }

                cout<<"Ingrese la coordenada en y:"<<endl;
                cin>> y;

                if(yo == -1){
                    yo = x;
                }

                MatrizAuxiliar.insertarElementoEspecial(0, meter, x, y);
                MatrizAuxiliar.iniciarGenerarGraphviz();
                //Matrizz.insertarElementoEspecial(0, meter, x, y);
                //Matrizz.iniciarGenerarGraphviz();


            } else {
                cout<<"no tiene esa ficha"<<endl;
            }


        } else {
            break;
        }
    }

    // VALIDANDO
    // SE VALIDA EN LA MATRIZ AUXILIAR
    // SI NO ES VÁLIDO, MATRIZAUX = MATRIZZ


    int puntaje_final = 0;
    cout<<"xo= "<<xo<< " xf= "<<x<<endl;
    cout<<"yo= "<<yo<<" yf= "<<y<<endl;

    if(xo == x){
        int auxxxx = 0;
        cout<<"Validando vertical"<<endl;

        // aca miro donde de verdad comienza y termina la palabra
        for (int j = yo; j >= 0; --j) {
            string palabraaux = "";
            MatrizAuxiliar.getLetra(palabraaux, auxxxx, xo, j);
            if(palabraaux == ""){
                break;
            } else {
                y_ini = j;
            }
        }
        for (int k = y; k < dimensionP; ++k) {

            string palabraaux = "";
            MatrizAuxiliar.getLetra(palabraaux, auxxxx, xo, k);
            if(palabraaux == ""){
                break;
            } else {
                y_fin = k;
            }

        }


        // aca formo la palabra
        int numero = y_fin-y_ini;
        for (int i = 0; i <= numero; ++i) {

            MatrizAuxiliar.getLetra(palabra, puntaje_final, xo, y_ini);
            y_ini++;
            cout<<palabra<<endl;

            if(y_ini == y_fin+1){
                break;
            }
        }


    }
    else if(yo == y){

        cout<<"validando horizontal"<<endl;

        int nosirve = 0;
        // aca miro donde de verdad comienza y termina la palabra
        for (int j = xo; j >= 0; --j) {
            string palabraaux = "";
            MatrizAuxiliar.getLetra(palabraaux, nosirve, j, yo);
            if(palabraaux == ""){
                break;
            } else {
                x_ini = j;
            }
        }
        for (int k = y; k < dimensionP; ++k) {

            string palabraaux = "";
            MatrizAuxiliar.getLetra(palabraaux, nosirve, k, yo);
            if(palabraaux == ""){
                break;
            } else {
                x_fin = k;
            }

        }


        int numero = x_fin-x_ini;
        for (int i = 0; i <= numero; ++i) {

            MatrizAuxiliar.getLetra(palabra, puntaje_final, x_ini, yo);
            x_ini++;
            cout<<palabra<<endl;

            if(x_ini == x_fin+1){
                break;
            }
        }

    }
    else {
        cout<<"Las fichas solo se leen vertical u horizontal.\n"
              "Pierde turno por feo >:C"<<endl;
    }

    if(CircularDoble.buscar(palabra)){

        cout<<"----------- PALABRA ENCONTRADA -----------"<<endl;
        Matrizz = MatrizAuxiliar;

        int suma = puntaje_final + jugador.getPuntajeParcial();
        jugador.setPuntajeParcial(suma);

        cout<<"----------- TU PUNTAJE ES: "<< puntaje_final<<endl;
        puntaje_final = 0;

        cout<<"------------------> Volviendo a meter fichas. Hay "<<contafichas<<endl;
        for (int i = contafichas; i <= 7; ++i) {
            ObjFicha oficha = ColadeFichas.pop();
            jugador.insertarFicha(oficha);
        }



    }
    else {

        cout<<"----------- PALABRA NO ENCONTRADA -----------"<<endl;
        MatrizAuxiliar = Matrizz;
        jugador.copiarOriginal(ListaFichasAux);
        puntaje_final = 0;


    }



    return;
}

void queDeseaHacer(ObjJugador& jugador, int &puntaje, Cola &ColadeFichas){

    Matrizz.iniciarGenerarGraphviz();

    int choice;
    cout<<"Que desea hacer ahora?\n1.Insertar Palabra\t\t2.Canjear Fichas"<<endl;
    cin>>choice;

    if(choice == 1){
        ingresarPalabra(jugador, puntaje, ColadeFichas);
    } else{
        canjearFichas(jugador);
    }

}
bool terminar(){
    int terminar;
    cout<<"Deseas terminar el juego?\n1.Si\t\t2.No"<<endl;
    cin>> terminar;

    if(terminar == 1){
        return true;
    } else if(terminar == 2){
        return false;
    } else {
        return true;
    }
}
void settearTurno(){
    srand((unsigned) time(0));
    int random;
    random = (rand() % 10) + 1;
    if(random <6){
        turnoactual = 0;
    } else {
        turnoactual = 1;
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
    cout << "5. Insertar Jugador" << endl;
    cout << "6. Regresar" << endl;

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
            insertarJugador();
            break;
        case 6:
            system("cls");
            menuDesplegable();
            break;
        default:
            cout << "Ingresaste un caracter no válido :C" << endl;
    }
}
void insertarJugador(){

    system("cls");
    cout << endl;
    cout << "\t\t\t---------------------" << endl; // 15
    cout << "\t\t\t  INSERTAR JUGADOR\n" << endl;
    cout << "\t\t\t---------------------" << endl;


    string nombre1;
    cout<<"Por favor ingresa el nombre de tu jugador"<<endl;
    cin>>nombre1;

    ObjJugador uno(nombre1);
    uno.insertarPuntaje(0);

    ArbolNombres.iniciarInsertar(nombre1, CircularJugadores, ListaMejoresJugadores);
    if(ArbolNombres.insertcionexitosa){
        //CircularJugadores.insertar(uno);
        cout<<"Nombre del jugador guardado :D\n\n"<<endl;
        getch();
        //CircularJugadores.mostrarLista();
        //getch();
        mostrarArbolJugadores();
    }
    while(!ArbolNombres.insertcionexitosa){
        string nombree1;
        cout<<"Por favor ingresa el nombre de tu jugador"<<endl;
        cin>>nombree1;

        ArbolNombres.iniciarInsertar(nombree1, CircularJugadores, ListaMejoresJugadores);
        if(ArbolNombres.insertcionexitosa){
            //CircularJugadores.insertar(uno);
            cout<<"Nombre del jugador guardado :D\n\n"<<endl;
            getch();
            //CircularJugadores.mostrarLista();
            //getch();
            mostrarArbolJugadores();
        }
    }



    mostrarArbolJugadores();

}
void faseParticipantes(){

    system("cls");
    cout << endl;

    cout << "\t\t\t---------------------" << endl; // 15
    cout << "\t\t\t     JUGADOR 1\n" << endl;
    cout << "\t\t\t---------------------" << endl;

    cout<<"Por favor escoge el correlativo del jugador que deseas usar"<<endl;
    CircularJugadores.iniciargenerarGraphviz();
    participante1();
    getch();
    cout << endl;cout << endl;

    cout << "\t\t\t---------------------" << endl; // 15
    cout << "\t\t\t     JUGADOR 2\n" << endl;
    cout << "\t\t\t---------------------" << endl;

    cout<<"Por favor escoge el correlativo del jugador que deseas usar"<<endl;
    participante2();
    getch();

    cout << endl;cout << endl;

    cout<<"Jugadores:\n\n"<<endl;
    cout<<"Jugador 1: " + jugador1.nombre<<endl;
    cout<<"Jugador 2: " + jugador2.nombre<<endl;

    getch();
}
void participante1(){

    int correlativo1;
    cin>>correlativo1;

    ObjJugador uno = CircularJugadores.buscar(correlativo1);
    if(uno.nombre != ""){
        jugador1 = uno;
        cout<<"-----------------> El primer jugador es: " + jugador1.nombre<<endl;
    } else {
        cout<<"Numero inivalido, por favor escoge otro :c"<<endl;
        participante1();
    }
}
void participante2(){

    int correlativo1;
    cin>>correlativo1;

    ObjJugador uno = CircularJugadores.buscar(correlativo1);
    if(uno.nombre != ""){
        if(uno.nombre == jugador1.nombre){
            cout<<"Jugador ya escogido, por favor escoge otro :c"<<endl;
            participante2();
        }else {
            jugador2 = uno;
            cout<<"-----------------> El segundo jugador es: " + jugador2.nombre<<endl;
        }
    } else {
        cout<<"Numero inivalido, por favor escoge otro :c"<<endl;
        participante2();
    }
}


void asignarFichas(){

    system("cls");
    cout << endl;
    cout << "\t\t\t---------------------" << endl; // 15
    cout << "\t\t\t\tFICHAS\n" << endl;
    cout << "\t\t\t---------------------" << endl;

    ColadeFichas.borrarTodo();
    ColadeFichas.llenarCola();
    cout<<"Fichas Disponibles: "<<endl;
    ColadeFichas.iniciarGenerarGraphviz();
    getch();

    cout<<"Asignando Fichas..."<<endl;

    for (int i = 0; i < 7; ++i) {
        ObjFicha ficha = ColadeFichas.pop();
        jugador1.insertarFicha(ficha);
    }

    //cout<<"Las fichas del jugador 1 son:"<<endl;
    //jugador1.mostrarFichas();
    getch();
    cout<<endl;cout<<endl;

    for (int i = 0; i < 7; ++i) {
        ObjFicha ficha = ColadeFichas.pop();
        jugador2.insertarFicha(ficha);
    }

    //cout<<"Las fichas del jugador 2 son:"<<endl;
    //jugador2.mostrarFichas();
    getch();
    cout<<endl;cout<<endl;


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
    Matrizz.iniciarMatriz(dimension);
    dimensionP = dimension-1;

    // Dobles
    for(int i = 0; i < mijson.at("casillas").at("dobles").size(); i++){
        int x = mijson.at("casillas").at("dobles")[i].at("x");
        int y = mijson.at("casillas").at("dobles")[i].at("y");
        ObjFicha o1 (0,1);
        Matrizz.insertarElementoEspecial(2, o1, x, y);
    }

    // Triples
    for(int i = 0; i < mijson.at("casillas").at("triples").size(); i++){
        int x = mijson.at("casillas").at("triples")[i].at("x");
        int y = mijson.at("casillas").at("triples")[i].at("y");
        ObjFicha o1 (0,1) ;
        Matrizz.insertarElementoEspecial(3, o1, x, y);
    }

    MatrizAuxiliar = Matrizz;
    //Matrizz.iniciarGenerarGraphviz();
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
    cout << "6. Salir\n\n" << endl;
    cout << endl;

    int respuesta;
    cin >> respuesta;

    switch (respuesta) {
        case 1: // jugar
            faseJuego();
            break;
        case 2:  // insertar archivo
            abrirArchivo();
            break;
        case 3: // jugadores
            mostrarArbolJugadores();
            break;
        case 4: // mejores puntajes
            mostrarMejoresPuntajes();

            break;
        case 5: // Diccionario
            CircularDoble.iniciargenerarGraphviz();
            system("cls");
            menuDesplegable();
            break;
        case 6: // salir
            cout<< "Gracias por usar este programa!! :D"<<endl;
            //getch();
            exit(0);
            break;
        default:
            cout << "Ingresaste un caracter no válido :C" << endl;
            system("cls");
            //menuDesplegable();
            //
            // getch();
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





// EL FONDO DE LA VERGUENZA
/*void generarGraphPrueba(){

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
/*void faseParticipante2(){
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
            cout<<"Nombre del jugador 2 guardado :D\n\n"<<endl;
            jugadoor2 = nombre1;
            getch();
        }
        while(!ArbolNombres.insertcionexitosa){
            string nombree1;
            cout<<"Por favor ingresa el nombre de tu jugador"<<endl;
            cin>>nombree1;
            ArbolNombres.iniciarInsertar(nombree1);
            if(ArbolNombres.insertcionexitosa){
                cout<<"Nombre del jugador 2 guardado :D\n\n"<<endl;
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
}*/