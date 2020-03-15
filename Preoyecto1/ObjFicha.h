//
// Created by yasmi on 14/03/2020.
//

#ifndef PREOYECTO1_OBJFICHA_H
#define PREOYECTO1_OBJFICHA_H

class ObjFicha{
private:
    char letra;
    int puntaje;
public:
    char getLetra() const;
    void setLetra(char letra);

    int getPuntaje() const;
    void setPuntaje(int puntaje);
};

char ObjFicha::getLetra() const {
    return letra;
}

void ObjFicha::setLetra(char letra) {
    ObjFicha::letra = letra;
}

int ObjFicha::getPuntaje() const {
    return puntaje;
}

void ObjFicha::setPuntaje(int puntaje) {
    ObjFicha::puntaje = puntaje;
}

#endif //PREOYECTO1_OBJFICHA_H
