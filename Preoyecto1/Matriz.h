//
// Created by yasmi on 30/03/2020.
//

#ifndef PREOYECTO1_MATRIZ_H
#define PREOYECTO1_MATRIZ_H

class Matriz {

    class Nodo{
        int correlativo;
        Nodo* arriba;
        Nodo* abajo;
        Nodo* anterior;
        Nodo* siguiente;
    };

    Nodo* raiz; // el que va afuera, sería (-1,-1)

};

#endif //PREOYECTO1_MATRIZ_H
