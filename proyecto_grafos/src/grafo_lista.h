#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#include "grafo.h"
#include "nodo.h"
#include <iostream>

using namespace std;

template <typename T>
class GrafoLista : public Grafo<T> {
private:
    struct Arista {
        int destino;
        double peso;
        Arista* siguiente;
        Arista(int dest, double p) : destino(dest), peso(p), siguiente(nullptr) {}
    };

    struct VerticeLista {
        int id;
        Nodo<T>* nodo_info;
        Arista* lista_aristas;
        VerticeLista* siguiente;
        VerticeLista(int id, T dato) : id(id), lista_aristas(nullptr), siguiente(nullptr) {
            nodo_info = new Nodo<T>(id, dato);
        }
        ~VerticeLista() {
            delete nodo_info;
            Arista* actual = lista_aristas;
            while (actual != nullptr) {
                Arista* temp = actual;
                actual = actual->siguiente;
                delete temp;
            }
        }
    };

    VerticeLista* cabeza;
    int capacidad_maxima;
    int total_vertices;

    VerticeLista* buscar_vertice(int id) const {
        VerticeLista* actual = cabeza;
        while (actual != nullptr) {
            if (actual->id == id) return actual;
            actual = actual->siguiente;
        }
        return nullptr;
    }

public:
    GrafoLista(int max_v = 100) {
        cabeza = nullptr;
        capacidad_maxima = max_v;
        total_vertices = 0;
    }

    ~GrafoLista() {
        VerticeLista* actual = cabeza;
        while (actual != nullptr) {
            VerticeLista* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }

    void agregar_vertice(int id, T dato) override {
        if (total_vertices >= capacidad_maxima) {
            cerr << "Error: Overflow, capacidad maxima de vertices alcanzada." << endl;
            return;
        }
        if (buscar_vertice(id) != nullptr) {
            cout << "Aviso: El vertice con ID " << id << " ya existe." << endl;
            return;
        }
        VerticeLista* nuevo = new VerticeLista(id, dato);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        total_vertices++;
    }

    void agregar_arista(int origen, int destino, double peso = 1.0) override {
        VerticeLista* v_origen = buscar_vertice(origen);
        VerticeLista* v_destino = buscar_vertice(destino);

        if (v_origen == nullptr || v_destino == nullptr) {
            cerr << "Error: Out of index / Nodo no encontrado al intentar conectar arista." << endl;
            return;
        }

        Arista* nueva_arista = new Arista(destino, peso);
        nueva_arista->siguiente = v_origen->lista_aristas;
        v_origen->lista_aristas = nueva_arista;
    }

    void mostrar_grafo() const override {
        cout << "\n--- GRAFO (LISTA DE ADYACENCIA) ---" << endl;
        VerticeLista* actual = cabeza;
        while (actual != nullptr) {
            cout << "Vertice [" << actual->id << "] (Dato: " << actual->nodo_info->obtener_dato() << ") -> ";
            Arista* arista_actual = actual->lista_aristas;
            while (arista_actual != nullptr) {
                cout << "Node(" << arista_actual->destino << ", peso: " << arista_actual->peso << ") ";
                arista_actual = arista_actual->siguiente;
            }
            cout << endl;
            actual = actual->siguiente;
        }
    }

    void recorrido_anchura(int inicio_id) const override {
        VerticeLista* inicio = buscar_vertice(inicio_id);
        if (!inicio) {
            cerr << "Error: Vertice de inicio no encontrado." << endl;
            return;
        }

        int visitados_ids[100];
        int num_visitados = 0;
        int cola[100];
        int frente = 0, fin = 0;

        cola[fin++] = inicio_id;
        visitados_ids[num_visitados++] = inicio_id;

        cout << "\nRecorrido Anchura (BFS): ";
        while (frente < fin) {
            int actual_id = cola[frente++];
            cout << actual_id << " ";

            VerticeLista* v = buscar_vertice(actual_id);
            if (v) {
                Arista* a = v->lista_aristas;
                while (a != nullptr) {
                    bool ya_visitado = false;
                    for (int i = 0; i < num_visitados; i++) {
                        if (visitados_ids[i] == a->destino) {
                            ya_visitado = true;
                            break;
                        }
                    }
                    if (!ya_visitado) {
                        visitados_ids[num_visitados++] = a->destino;
                        cola[fin++] = a->destino;
                    }
                    a = a->siguiente;
                }
            }
        }
        cout << endl;
    }

    void recorrido_profundidad(int inicio_id) const override {
        VerticeLista* inicio = buscar_vertice(inicio_id);
        if (!inicio) {
            cerr << "Error: Vertice de inicio no encontrado." << endl;
            return;
        }

        int visitados_ids[100];
        int num_visitados = 0;
        int pila[100];
        int tope = -1;

        pila[++tope] = inicio_id;

        cout << "\nRecorrido Profundidad (DFS): ";
        while (tope >= 0) {
            int actual_id = pila[tope--];

            bool ya_visitado = false;
            for (int i = 0; i < num_visitados; i++) {
                if (visitados_ids[i] == actual_id) {
                    ya_visitado = true;
                    break;
                }
            }

            if (!ya_visitado) {
                visitados_ids[num_visitados++] = actual_id;
                cout << actual_id << " ";

                VerticeLista* v = buscar_vertice(actual_id);
                if (v) {
                    Arista* a = v->lista_aristas;
                    while (a != nullptr) {
                        pila[++tope] = a->destino;
                        a = a->siguiente;
                    }
                }
            }
        }
        cout << endl;
    }

    void camino_mas_corto(int origen_id, int destino_id) const override {
        // Dijkstra simplificado y seguro sin vectores dinamicos de STL
        double distancias[100];
        int padres[100];
        bool visitados[100];

        for (int i = 0; i < 100; i++) {
            distancias[i] = 1e9;
            padres[i] = -1;
            visitados[i] = false;
        }

        distancias[origen_id] = 0;

        for (int i = 0; i < total_vertices; i++) {
            int u = -1;
            double minDist = 1e9;
            VerticeLista* curr = cabeza;
            while (curr != nullptr) {
                int id = curr->id;
                if (!visitados[id] && distancias[id] < minDist) {
                    minDist = distancias[id];
                    u = id;
                }
                curr = curr->siguiente;
            }

            if (u == -1 || minDist == 1e9) break;
            visitados[u] = true;

            VerticeLista* v_node = buscar_vertice(u);
            if (v_node) {
                Arista* a = v_node->lista_aristas;
                while (a != nullptr) {
                    int v = a->destino;
                    double peso = a->peso;
                    if (!visitados[v] && distancias[u] + peso < distancias[v]) {
                        distancias[v] = distancias[u] + peso;
                        padres[v] = u;
                    }
                    a = a->siguiente;
                }
            }
        }

        cout << "\nCamino mas corto de " << origen_id << " a " << destino_id << ": ";
        if (distancias[destino_id] >= 1e9) {
            cout << "No existe camino." << endl;
            return;
        }
        cout << "Distancia total = " << distancias[destino_id] << " | Ruta: ";
        int actual = destino_id;
        int ruta[100];
        int pasos = 0;
        while (actual != -1) {
            ruta[pasos++] = actual;
            actual = padres[actual];
        }
        for (int i = pasos - 1; i >= 0; i--) {
            cout << ruta[i] << (i > 0 ? " -> " : "");
        }
        cout << endl;
    }
};

#endif
