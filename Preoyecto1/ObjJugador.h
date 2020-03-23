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

#ifndef PREOYECTO1_OBJJUGADOR_H
#define PREOYECTO1_OBJJUGADOR_H

using namespace::std;

class ObjJugador{

private:
    string nombre;
    ListaOrdenadaPuntajes ListaPuntajesdeJugador;
public:

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

};

void ObjJugador::insertarPuntaje(int punteo) {

    this->ListaPuntajesdeJugador.insertar(punteo);

}

int ObjJugador::getPuntajeAlto() {

 return  this->ListaPuntajesdeJugador.getPrimero();
}

#endif //PREOYECTO1_OBJJUGADOR_H
