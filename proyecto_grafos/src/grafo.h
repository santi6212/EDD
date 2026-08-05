#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Grafo {
public:
    virtual ~Grafo() {}
    virtual void agregar_vertice(int id, T dato) = 0;
    virtual void agregar_arista(int origen, int destino, double peso = 1.0) = 0;
    virtual void mostrar_grafo() const = 0;
    virtual void recorrido_anchura(int inicio_id) const = 0;
    virtual void recorrido_profundidad(int inicio_id) const = 0;
    virtual void camino_mas_corto(int origen_id, int destino_id) const = 0;
};

#endif
