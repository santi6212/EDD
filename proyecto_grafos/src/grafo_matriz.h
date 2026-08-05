#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

#include "grafo.h"
#include "nodo.h"
#include <iostream>

using namespace std;

template <typename T>
class GrafoMatriz : public Grafo<T> {
private:
    int capacidad;
    int numero_vertices;
    Nodo<T>** vertices;
    double** matriz;

    int obtener_indice(int id) const {
        for (int i = 0; i < numero_vertices; i++) {
            if (vertices[i]->obtener_id() == id) return i;
        }
        return -1;
    }

public:
    GrafoMatriz(int cap = 50) {
        capacidad = cap;
        numero_vertices = 0;
        vertices = new Nodo<T>*[capacidad];
        matriz = new double*[capacidad];
        for (int i = 0; i < capacidad; i++) {
            vertices[i] = nullptr;
            matriz[i] = new double[capacidad];
            for (int j = 0; j < capacidad; j++) {
                matriz[i][j] = 0; // 0 indica ausencia de arista (o peso 0)
            }
        }
    }

    ~GrafoMatriz() {
        for (int i = 0; i < capacidad; i++) {
            delete vertices[i];
            delete[] matriz[i];
        }
        delete[] vertices;
        delete[] matriz;
    }

    void agregar_vertice(int id, T dato) override {
        if (numero_vertices >= capacidad) {
            cerr << "Error: Overflow de memoria en matriz de adyacencia." << endl;
            return;
        }
        if (obtener_indice(id) != -1) {
            cout << "Aviso: Vertice con ID " << id << " ya existe." << endl;
            return;
        }
        vertices[numero_vertices++] = new Nodo<T>(id, dato);
    }

    void agregar_arista(int origen, int destino, double peso = 1.0) override {
        int idx_orig = obtener_indice(origen);
        int idx_dest = obtener_indice(destino);

        if (idx_orig == -1 || idx_dest == -1) {
            cerr << "Error: Out of index / Uno de los vertices no existe en la matriz." << endl;
            return;
        }

        matriz[idx_orig][idx_dest] = peso;
    }

    void mostrar_grafo() const override {
        cout << "\n--- GRAFO (MATRIZ DE ADYACENCIA) ---" << endl;
        cout << "    ";
        for (int i = 0; i < numero_vertices; i++) {
            cout << "[" << vertices[i]->obtener_id() << "] ";
        }
        cout << endl;

        for (int i = 0; i < numero_vertices; i++) {
            cout << "[" << vertices[i]->obtener_id() << "] ";
            for (int j = 0; j < numero_vertices; j++) {
                cout << " " << matriz[i][j] << "  ";
            }
            cout << endl;
        }
    }

    void recorrido_anchura(int inicio_id) const override {
        int idx_inicio = obtener_indice(inicio_id);
        if (idx_inicio == -1) {
            cerr << "Error: Vertice inicial no encontrado." << endl;
            return;
        }

        bool visitados[50] = {false};
        int cola[50];
        int frente = 0, fin = 0;

        cola[fin++] = idx_inicio;
        visitados[idx_inicio] = true;

        cout << "\nRecorrido Anchura Matriz (BFS): ";
        while (frente < fin) {
            int actual_idx = cola[frente++];
            cout << vertices[actual_idx]->obtener_id() << " ";

            for (int j = 0; j < numero_vertices; j++) {
                if (matriz[actual_idx][j] != 0 && !visitados[j]) {
                    visitados[j] = true;
                    cola[fin++] = j;
                }
            }
        }
        cout << endl;
    }

    void recorrido_profundidad(int inicio_id) const override {
        int idx_inicio = obtener_indice(inicio_id);
        if (idx_inicio == -1) {
            cerr << "Error: Vertice inicial no encontrado." << endl;
            return;
        }

        bool visitados[50] = {false};
        int pila[50];
        int tope = -1;

        pila[++tope] = idx_inicio;

        cout << "\nRecorrido Profundidad Matriz (DFS): ";
        while (tope >= 0) {
            int actual_idx = pila[tope--];

            if (!visitados[actual_idx]) {
                visitados[actual_idx] = true;
                cout << vertices[actual_idx]->obtener_id() << " ";

                for (int j = numero_vertices - 1; j >= 0; j--) {
                    if (matriz[actual_idx][j] != 0 && !visitados[j]) {
                        pila[++tope] = j;
                    }
                }
            }
        }
        cout << endl;
    }

    void camino_mas_corto(int origen_id, int destino_id) const override {
        int idx_orig = obtener_indice(origen_id);
        int idx_dest = obtener_indice(destino_id);

        if (idx_orig == -1 || idx_dest == -1) {
            cerr << "Error: Vertices de origen o destino invalidos." << endl;
            return;
        }

        double distancias[50];
        int padres[50];
        bool visitados[50];

        for (int i = 0; i < numero_vertices; i++) {
            distancias[i] = 1e9;
            padres[i] = -1;
            visitados[i] = false;
        }

        distancias[idx_orig] = 0;

        for (int i = 0; i < numero_vertices; i++) {
            int u = -1;
            double minDist = 1e9;
            for (int j = 0; j < numero_vertices; j++) {
                if (!visitados[j] && distancias[j] < minDist) {
                    minDist = distancias[j];
                    u = j;
                }
            }

            if (u == -1 || minDist == 1e9) break;
            visitados[u] = true;

            for (int v = 0; v < numero_vertices; v++) {
                if (matriz[u][v] != 0 && !visitados[v]) {
                    double peso = matriz[u][v];
                    if (distancias[u] + peso < distancias[v]) {
                        distancias[v] = distancias[u] + peso;
                        padres[v] = u;
                    }
                }
            }
        }

        cout << "\nCamino mas corto (Matriz) de " << origen_id << " a " << destino_id << ": ";
        if (distancias[idx_dest] >= 1e9) {
            cout << "No existe camino." << endl;
            return;
        }
        cout << "Distancia = " << distancias[idx_dest] << " | Ruta: ";
        
        int ruta[50];
        int pasos = 0;
        int curr = idx_dest;
        while (curr != -1) {
            ruta[pasos++] = vertices[curr]->obtener_id();
            curr = padres[curr];
        }
        for (int i = pasos - 1; i >= 0; i--) {
            cout << ruta[i] << (i > 0 ? " -> " : "");
        }
        cout << endl;
    }
};

#endif
