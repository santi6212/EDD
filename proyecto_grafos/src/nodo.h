#ifndef NODO_H
#define NODO_H

#include <iostream>

using namespace std;

template <typename T>
class Nodo {
private:
    T dato;
    int id;
public:
    Nodo(int id, T dato) {
        this->id = id;
        this->dato = dato;
    }

    int obtener_id() const {
        return id;
    }

    T obtener_dato() const {
        return dato;
    }

    void establecer_dato(T nuevo_dato) {
        dato = nuevo_dato;
    }
};

#endif
