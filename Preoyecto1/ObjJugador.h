//
// Created by yasmi on 19/03/2020.
//
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <stdio.h>
#include <windows.h>
#include <fstream>

#include "ListaOrdenadaPuntajes.h"
#include "ListaDobleFichas.h"

#ifndef PREOYECTO1_OBJJUGADOR_H
#define PREOYECTO1_OBJJUGADOR_H

using namespace::std;

class ObjJugador{

public:
    string nombre;
    ListaOrdenadaPuntajes ListaPuntajesdeJugador;
    ListaDobleFichas Lista7Fichas;



    void insertarFicha(ObjFicha ficha);
    void mostrarFichas();

    void insertarPuntaje(int punteo);
    int getPuntajeAlto();

    explicit ObjJugador(string nombree){
        this->nombre = nombree;
    }
    ObjJugador()= default;

    const string &getNombre() const {
        return nombre;
    }
    void setNombre(const string &nombre) {
        ObjJugador::nombre = nombre;
    }

    char buscarFicha(char ficha);
    void eliminarFicha(char ficha);

    void generarGraphMejoresPuntajes();
};

void ObjJugador::insertarPuntaje(int punteo) {

    ListaPuntajesdeJugador.insertar(punteo);

}

int ObjJugador::getPuntajeAlto() {

 return  this->ListaPuntajesdeJugador.getPrimero();
}

void ObjJugador::insertarFicha(ObjFicha ficha) {
this->Lista7Fichas.insertar(ficha);
}

void ObjJugador::mostrarFichas() {
    this->Lista7Fichas.iniciarGenerarGraphviz();
}

char ObjJugador::buscarFicha(char ficha) {

    if(this->Lista7Fichas.buscarficha(ficha) == NULL){
        return 0;
    }

    return this->Lista7Fichas.buscarficha(ficha)->ficha.getLetra();
}

void ObjJugador::eliminarFicha(char ficha) {
    this->Lista7Fichas.eliminarFicha(ficha);

}

void ObjJugador::generarGraphMejoresPuntajes() {

    this->ListaPuntajesdeJugador.iniciarGenerarGraphviz();
}


#endif //PREOYECTO1_OBJJUGADOR_H
