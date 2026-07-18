#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Miembro {
    int id;
    string name;
    string last_name;
    char gender;
    int age;
    int id_boss;
    bool is_dead;
    bool in_jail;
    bool was_boss;
    bool is_boss;

    Miembro* izquierdo = nullptr;
    Miembro* derecho = nullptr;
    Miembro* padre = nullptr;
};

Miembro* buscarPorId(Miembro* raiz, int id) {
    if (raiz == nullptr || raiz->id == id) return raiz;
    Miembro* izq = buscarPorId(raiz->izquierdo, id);
    if (izq != nullptr) return izq;
    return buscarPorId(raiz->derecho, id);
}

void insertarEnJerarquia(Miembro*& padreArbol, Miembro* nuevo) {
    if (padreArbol == nullptr) {
        if (nuevo->id_boss == 0 || nuevo->id_boss == -1) { // Es el jefe original
            padreArbol = nuevo;
        }
        return;
    }

    Miembro* jefeNodo = buscarPorId(padreArbol, nuevo->id_boss);
    if (jefeNodo != nullptr) {
        nuevo->padre = jefeNodo;
        if (jefeNodo->izquierdo == nullptr) {
            jefeNodo->izquierdo = nuevo;
        } else if (jefeNodo->derecho == nullptr) {
            jefeNodo->derecho = nuevo;
        } else {
            cout << "[!] Error: El jefe " << jefeNodo->id << " ya tiene 2 sucesores.\n";
        }
    }
}

void mostrarLineaSucesion(Miembro* nodo) {
    if (nodo == nullptr) return;
    
    if (!nodo->is_dead) {
        cout << "ID: " << nodo->id << " | " << nodo->name << " " << nodo->last_name 
             << " | Edad: " << nodo->age << (nodo->is_boss ? " [JEFE ACTUAL]" : "") 
             << (nodo->in_jail ? " (En Prisión)" : "") << "\n";
    }
    
    mostrarLineaSucesion(nodo->izquierdo);
    mostrarLineaSucesion(nodo->derecho);
}

void modificarMiembro(Miembro* raiz, int id) {
    Miembro* nodo = buscarPorId(raiz, id);
    if (nodo == nullptr) {
        cout << "Miembro no encontrado.\n";
        return;
    }
    
    cout << "Modificando a: " << nodo->name << " " << nodo->last_name << "\n";
    cout << "Nueva edad: "; cin >> nodo->age;
    cout << "¿Está muerto? (1=Sí, 0=No): "; cin >> nodo->is_dead;
    cout << "¿Está en la cárcel? (1=Sí, 0=No): "; cin >> nodo->in_jail;
    cout << "Datos actualizados con éxito.\n";
}

//main
int main() {
    Miembro* padre = nullptr; 

    //csv

    int opcion = 0;
    while (opcion != 5) {
        cout << "\n=== CONTI CORLEONE MANAGEMENT SYSTEM ===\n";
        cout << "1. Mostrar Línea de Sucesión Actual (Vivos)\n";
        cout << "2. Evaluar Estado del Jefe (Sucesión Automática)\n";
        cout << "3. Modificar Datos de un Miembro\n";
        cout << "4. Cargar/Recargar CSV\n";
        cout << "5. Salir del Programa\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "\n--- LINEA DE SUCESION ACTUAL ---\n";
                mostrarLineaSucesion(padre);
                break;
            case 2:
                // Aquí disparas la lógica del punto 3 si el jefe actual 
                // cumple las condiciones de muerte, cárcel o > 70 años.
                cout << "Ejecutando algoritmos de sucesión...\n";
                break;
            case 3: {
                int idMod;
                cout << "Ingrese el ID del miembro a modificar: ";
                cin >> idMod;
                modificarMiembro(padre, idMod);
                break;
            }
            case 4:
                cout << "Leyendo datos...\n";
                break;
            case 5:
                cout << "Cerrando sistema. Mantén los ojos abiertos.\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    }
    return 0;
}
