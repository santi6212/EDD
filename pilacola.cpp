#include <iostream>
using namespace std;
//-std=c++11
// Estructura de Nodo para las listas enlazadas
template<typename T>
struct Nodo {
    T dato;
    Nodo* next;
    Nodo(T valor) : dato(valor), next(nullptr) {}
};

// Implementación de Pila (Stack) - LIFO (Last In, First Out)
template<typename T>
class Pila {
private:
    Nodo<T>* tope;
    int tamano;

public:
    Pila() : tope(nullptr), tamano(0) {}

    // Destructor para liberar memoria
    ~Pila() {
        while (tope != nullptr) {
            pop();
        }
    }

    void push(T valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);
        nuevoNodo->next = tope;
        tope = nuevoNodo;
        tamano++;
    }

    T pop() {
        Nodo<T>* temp = tope;
        T valor = temp->dato;
        tope = tope->next;
        delete temp;
        tamano--;
        return valor;
    }

    int getSize() const {
        return tamano;
    }
};

// Implementación de Cola (Queue) - FIFO (First In, First Out)
template<typename T>
class Cola {
private:
    Nodo<T>* frente;
    Nodo<T>* fin;
    int tamano;

public:
    Cola() : frente(nullptr), fin(nullptr), tamano(0) {}

    // Destructor para liberar memoria
    ~Cola() {
        while (frente != nullptr) {
            pop();
        }
    }

    void push(T valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);
        if (fin == nullptr) {
            frente = fin = nuevoNodo;
        } else {
            fin->next = nuevoNodo;
            fin = nuevoNodo;
        }
        tamano++;
    }

    T pop() {
        Nodo<T>* temp = frente;
        T valor = temp->dato;
        frente = frente->next;
        if (frente == nullptr) {
            fin = nullptr;
        }
        delete temp;
        tamano--;
        return valor;
    }

    int getSize() const {
        return tamano;
    }
};

int main() {
    // Prueba de la Pila
    Pila<int> miPila;
    miPila.push(10);
    miPila.push(20);
    miPila.push(30);

    cout << "Tamano de la pila: " << miPila.getSize() << endl;
    cout << "pop: " << miPila.pop() << endl;
    cout << "pop: " << miPila.pop() << endl;
    cout << "Tamano de la pila otra vez: " << miPila.getSize() << endl << endl;

    // Prueba de la Cola
    Cola<int> miCola;
    miCola.push(10);
    miCola.push(20);
    miCola.push(30);
    miCola.push(40);
    miCola.push(50);

    cout << "Tamano de la cola: " << miCola.getSize() << endl;
    cout << "pop: " << miCola.pop() << endl;
    cout << "pop: " << miCola.pop() << endl;
    cout << "pop: " << miCola.pop() << endl;
    cout << "Tamano de la cola otra vez: " << miCola.getSize() << endl;

    return 0;
}
