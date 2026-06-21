#include <iostream>
using namespace std;

const int MAX = 100; // Tamaño máximo para las versiones con arreglos

// IMPLEMENTACIONES CON LISTAS ENLAZADAS

template<typename T>
struct Nodo {
    T dato;
    Nodo* next;
    Nodo(T valor) : dato(valor), next(nullptr) {}
};

template<typename T>
class PilaLista {
private:
    Nodo<T>* tope;
public:
    PilaLista() : tope(nullptr) {}
    void push(T valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        nuevo->next = tope;
        tope = nuevo;
    }
    T pop() {
        T valor = tope->dato;
        Nodo<T>* temp = tope;
        tope = tope->next;
        delete temp;
        return valor;
    }
};

template<typename T>
class ColaLista {
private:
    Nodo<T> *frente, *fin;
public:
    ColaLista() : frente(nullptr), fin(nullptr) {}
    void push(T valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        if (!fin) frente = fin = nuevo;
        else { fin->next = nuevo; fin = nuevo; }
    }
    T pop() {
        T valor = frente->dato;
        Nodo<T>* temp = frente;
        frente = frente->next;
        if (!frente) fin = nullptr;
        delete temp;
        return valor;
    }
};

// IMPLEMENTACIONES CON ARREGLOS

template<typename T>
class PilaArreglo {
private:
    T datos[MAX];
    int tope;
public:
    PilaArreglo() : tope(-1) {}
    void push(T valor) { if (tope < MAX - 1) datos[++tope] = valor; }
    T pop() { return datos[tope--]; }
};

template<typename T>
class ColaArreglo {
private:
    T datos[MAX];
    int frente, fin;
public:
    ColaArreglo() : frente(0), fin(0) {}
    void push(T valor) { datos[fin++] = valor; }
    T pop() { return datos[frente++]; }
};

int main() {
    PilaLista<int> pLista;
    PilaArreglo<int> pArr;
    ColaLista<int> cLista;
    ColaArreglo<int> cArr;

    cout << "=== PRUEBAS LARGAS DE ESTRUCTURAS ===" << endl << endl;

    cout << "--- PILAS (Ingresando 10, 20, 30) ---" << endl;
    pLista.push(10); pLista.push(20); pLista.push(30);
    pArr.push(10);   pArr.push(20);   pArr.push(30);

    cout << "Pila Lista: " << pLista.pop() << ", " << pLista.pop() << ", " << pLista.pop() << endl;
    cout << "Pila Arreglo: " << pArr.pop() << ", " << pArr.pop() << ", " << pArr.pop() << endl;

    cout << "\n--- COLAS (Ingresando 10, 20, 30) ---" << endl;
    cLista.push(10); cLista.push(20); cLista.push(30);
    cArr.push(10);   cArr.push(20);   cArr.push(30);

    cout << "Cola Lista: " << cLista.pop() << ", " << cLista.pop() << ", " << cLista.pop() << endl;
    cout << "Cola Arreglo: " << cArr.pop() << ", " << cArr.pop() << ", " << cArr.pop() << endl;

    cout << "\n--- PRUEBA DE LLENADO ---" << endl;
    for(int i = 1; i <= 5; i++) {
        pArr.push(i * 100);
        cArr.push(i * 100);
    }
    cout << "Se han insertado 5 elementos adicionales en las versiones de arreglo." << endl;
    cout << "Ultimo valor en Pila Arreglo: " << pArr.pop() << endl;
    cout << "Primer valor en Cola Arreglo: " << cArr.pop() << endl;

    return 0;
}
