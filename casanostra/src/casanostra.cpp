#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <clocale>

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

// --- 1. FUNCIÓN DE LECTURA DE CSV ---
void cargarDesdeCSV(Miembro*& padreArbol, const string& rutaArchivo) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "[!] Error al abrir el archivo: " << rutaArchivo << "\n";
        return;
    }

    string linea;
    if (getline(archivo, linea)) {
    }

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string token;
        
        Miembro* nuevo = new Miembro();

        getline(ss, token, ','); nuevo->id = atoi(token.c_str());
        getline(ss, token, ','); nuevo->name = token;
        getline(ss, token, ','); nuevo->last_name = token;
        getline(ss, token, ','); nuevo->gender = token[0];
        getline(ss, token, ','); nuevo->age = atoi(token.c_str());
        getline(ss, token, ','); nuevo->id_boss = atoi(token.c_str());
        getline(ss, token, ','); nuevo->is_dead = (atoi(token.c_str()) == 1);
        getline(ss, token, ','); nuevo->in_jail = (atoi(token.c_str()) == 1);
        getline(ss, token, ','); nuevo->was_boss = (atoi(token.c_str()) == 1);
        getline(ss, token, ','); nuevo->is_boss = (atoi(token.c_str()) == 1);

        insertarEnJerarquia(padreArbol, nuevo);
    }

    archivo.close();
    cout << "[+] Datos cargados correctamente desde el CSV.\n";
}

// --- 2. FUNCIONES DE GUARDADO EN CSV ---
void escribirPreorden(Miembro* nodo, ofstream& archivo) {
    if (nodo == nullptr) return;

    archivo << nodo->id << ","
            << nodo->name << ","
            << nodo->last_name << ","
            << nodo->gender << ","
            << nodo->age << ","
            << nodo->id_boss << ","
            << (nodo->is_dead ? 1 : 0) << ","
            << (nodo->in_jail ? 1 : 0) << ","
            << (nodo->was_boss ? 1 : 0) << ","
            << (nodo->is_boss ? 1 : 0) << "\n";

    escribirPreorden(nodo->izquierdo, archivo);
    escribirPreorden(nodo->derecho, archivo);
}

void guardarEnCSV(Miembro* raiz, const string& rutaArchivo) {
    if (raiz == nullptr) {
        cout << "[!] El árbol está vacío. Nada que guardar.\n";
        return;
    }

    ofstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "[!] Error al abrir el archivo para guardar: " << rutaArchivo << "\n";
        return;
    }

    archivo << "id,name,last_name,gender,age,id_boss,is_dead,in_jail,was_boss,is_boss\n";

    escribirPreorden(raiz, archivo);

    archivo.close();
    cout << "[+] Árbol guardado con éxito en " << rutaArchivo << "\n";
}

void liberarArbol(Miembro* nodo) {
    if (nodo == nullptr) return;
    liberarArbol(nodo->izquierdo);
    liberarArbol(nodo->derecho);
    delete nodo;
}

//verificaciones para jefe

bool esAptoParaJefe(Miembro* nodo) {
    if (nodo == nullptr) return false;
    return (!nodo->is_dead && !nodo->in_jail && nodo->age <= 70);
}

Miembro* buscarSucesorEnSubarbol(Miembro* nodo) {
    if (nodo == nullptr) return nullptr;
    
    // Si el nodo actual es apto, lo encontramos
    if (esAptoParaJefe(nodo)) return nodo;
    
    // Si no, buscamos por la rama izquierda (primer sucesor asignado)
    Miembro* izq = buscarSucesorEnSubarbol(nodo->izquierdo);
    if (izq != nullptr) return izq;
    
    // Si no hay nadie apto en la izquierda, buscamos en la derecha
    return buscarSucesorEnSubarbol(nodo->derecho);
}

Miembro* obtenerCompaneroSucesor(Miembro* nodo) {
    if (nodo == nullptr || nodo->padre == nullptr) return nullptr;
    
    // Si yo soy el hijo izquierdo, mi compañero es el derecho
    if (nodo->padre->izquierdo == nodo) {
        return nodo->padre->derecho;
    }
    // Si yo soy el derecho, mi compañero es el izquierdo
    return nodo->padre->izquierdo;
}

//caso 2

Miembro* encontrarJefeActual(Miembro* nodo) {
    if (nodo == nullptr) return nullptr;
    if (nodo->is_boss) return nodo;
    Miembro* izq = encontrarJefeActual(nodo->izquierdo);
    if (izq != nullptr) return izq;
    return encontrarJefeActual(nodo->derecho);
}

Miembro* determinarNuevoJefe(Miembro* raiz, Miembro* jefeMuerto, bool permitirEnCarcel = false) {
    if (jefeMuerto == nullptr) return nullptr;

    if (!permitirEnCarcel) {
        Miembro* candidatoAbajo = buscarSucesorEnSubarbol(jefeMuerto->izquierdo);
        if (candidatoAbajo) return candidatoAbajo;
        candidatoAbajo = buscarSucesorEnSubarbol(jefeMuerto->derecho);
        if (candidatoAbajo) return candidatoAbajo;
    } else {
        if (jefeMuerto->izquierdo && !jefeMuerto->izquierdo->is_dead) return jefeMuerto->izquierdo;
        if (jefeMuerto->derecho && !jefeMuerto->derecho->is_dead) return jefeMuerto->derecho;
    }

    Miembro* companero = obtenerCompaneroSucesor(jefeMuerto);
    if (companero) {
        if (!permitirEnCarcel && esAptoParaJefe(companero)) return companero;
        if (!permitirEnCarcel) {
            Miembro* candidatoCompanero = buscarSucesorEnSubarbol(companero);
            if (candidatoCompanero) return candidatoCompanero;
        } else if (!companero->is_dead) {
            return companero;
        }
    }

    if (jefeMuerto->padre != nullptr) {
        return determinarNuevoJefe(raiz, jefeMuerto->padre, permitirEnCarcel);
    }

    if (!permitirEnCarcel) {
        Miembro* jefeActual = encontrarJefeActual(raiz);
        return determinarNuevoJefe(raiz, jefeActual, true);
    }

    return nullptr;
}

void evaluarEstadoDelJefe(Miembro* raiz) {
    Miembro* jefe = encontrarJefeActual(raiz);
    if (jefe == nullptr) {
        cout << "[!] Error: No se encontró ningún jefe activo en el sistema.\n";
        return;
    }

    cout << "Jefe Actual: " << jefe->name << " " << jefe->last_name 
         << " (Edad: " << jefe->age << ")\n";

    if (jefe->is_dead || jefe->in_jail || jefe->age > 70) {
        cout << "[!] Alerta: El jefe actual ya no es apto para liderar ";
        if (jefe->is_dead) cout << "(Fallecido).\n";
        else if (jefe->in_jail) cout << "(En Prisión).\n";
        else cout << "(Superó el límite de 70 años).\n";

        cout << "Buscando al legítimo sucesor según las leyes de la familia...\n";
        Miembro* sucesor = determinarNuevoJefe(raiz, jefe, false);

        if (sucesor != nullptr) {
            jefe->is_boss = false;
            jefe->was_boss = true;
            sucesor->is_boss = true;

            cout << "El nuevo jefe de la familia es:\n";
            cout << "ID: " << sucesor->id << " -> " << sucesor->name << " " << sucesor->last_name;
            if (sucesor->in_jail) cout << " (Gobernará desde prisión)";
        } else {
            cout << "No quedó ningún miembro vivo para heredar el control.\n";
        }
    } else {
        cout << "El Don goza de plena salud y libertad. No se requiere sucesión en este momento.\n";
    }
}

//main
int main() {
	setlocale(LC_ALL, "Spanish");
    Miembro* padre = nullptr; 

    cargarDesdeCSV(padre, "datos.csv"); 

    int opcion = 0;
    while (opcion != 5) {
    	system("cls");
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
                system("pause");
                break;
            case 2:
                cout << "Ejecutando algoritmos de sucesión...\n";
                evaluarEstadoDelJefe(padre); 
                guardarEnCSV(padre, "datos.csv");
                cout << "\n";
                system("pause");
                break;
            case 3: {
                int idMod;
                cout << "Ingrese el ID del miembro a modificar: ";
                cin >> idMod;
                modificarMiembro(padre, idMod);
                guardarEnCSV(padre, "datos.csv");
                system("pause");
                break;
            }
            case 4:
                cout << "Recargando datos desde el archivo...\n";
                liberarArbol(padre); 
                padre = nullptr; 
                cargarDesdeCSV(padre, "datos.csv"); 
                system("pause");
                break;
            case 5:
                guardarEnCSV(padre, "datos.csv");
                liberarArbol(padre);
                cout << "Cerrando sistema. Mantén los ojos abiertos.\n";
                break;
            default:
                cout << "Opción inválida.\n";
                system("pause");
        }
    }
    return 0;
}
