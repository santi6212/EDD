#include <iostream>
#include "grafo_lista.h"
#include "grafo_matriz.h"

using namespace std;

void mostrar_menu() {
    cout << "\n=== LIBRERIA DE GRAFOS - MENU PRINCIPAL ===" << endl;
    cout << "1. Probar Grafo por Lista de Adyacencia" << endl;
    cout << "2. Probar Grafo por Matriz de Adyacencia" << endl;
    cout << "3. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

int main() {
    int opcion = 0;

    while (opcion != 3) {
        mostrar_menu();
        cin >> opcion;

        if (opcion == 1) {
            cout << "\n--- DEMO: GRAFO DE LISTAS (Datos tipo string: Ciudades) ---" << endl;
            GrafoLista<string> grafo_l(10);
            
            // Carga de datos iniciales
            grafo_l.agregar_vertice(1, "Maracaibo");
            grafo_l.agregar_vertice(2, "Caracas");
            grafo_l.agregar_vertice(3, "Valencia");
            grafo_l.agregar_vertice(4, "Barquisimeto");

            grafo_l.agregar_arista(1, 2, 500.5);
            grafo_l.agregar_arista(1, 3, 300.0);
            grafo_l.agregar_arista(3, 4, 150.2);
            grafo_l.agregar_arista(2, 4, 400.0);

            grafo_l.mostrar_grafo();
            grafo_l.recorrido_anchura(1);
            grafo_l.recorrido_profundidad(1);
            grafo_l.camino_mas_corto(1, 4);

        } else if (opcion == 2) {
            cout << "\n--- DEMO: GRAFO DE MATRIZ (Datos tipo int: Codigos de servidor) ---" << endl;
            GrafoMatriz<int> grafo_m(10);

            // Carga de datos iniciales
            grafo_m.agregar_vertice(10, 1001);
            grafo_m.agregar_vertice(20, 2002);
            grafo_m.agregar_vertice(30, 3003);

            grafo_m.agregar_arista(10, 20, 4.5);
            grafo_m.agregar_arista(20, 30, 2.1);
            grafo_m.agregar_arista(10, 30, 10.0);

            grafo_m.mostrar_grafo();
            grafo_m.recorrido_anchura(10);
            grafo_m.recorrido_profundidad(10);
            grafo_m.camino_mas_corto(10, 30);

        } else if (opcion == 3) {
            cout << "Saliendo del programa..." << endl;
        } else {
            cout << "Opcion invalida, intente de nuevo." << endl;
        }
    }

    return 0;
}
