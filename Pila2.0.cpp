#include <iostream>
#include <vector>
using namespace std;

class Nodo {
public:
    int elem[5];
    int indice;
    Nodo* next;

    Nodo() {
        indice = 0;
        next = nullptr;
    }
};

template<class T>
class Pila {
public:
    Nodo* A;

    Pila() {
        A = new Nodo;
    }

    ~Pila() {
        while (A) {
            Nodo* temp = A;
            A = A->next;
            delete temp;
        }
    }

    void push(T n) {
        if (A->indice < 5) {
            A->elem[A->indice++] = n;
        }
        else {
            Nodo* nuevo = new Nodo;
            nuevo->elem[nuevo->indice++] = n;
            nuevo->next = A;
            A = nuevo;
        }
    }

    // Pop devuelve false si la pila está vacía, o true y almacena el valor en 'out'.
    bool pop(T& out) {
        if (A == nullptr || (A->indice == 0 && A->next == nullptr)) {
            // Pila vacía
            return false;
        }
        if (A->indice > 0) {
            out = A->elem[--A->indice];
        }
        else {
            // Nodo vacío, avanzar al siguiente
            Nodo* temp = A;
            A = A->next;
            delete temp;
            return pop(out);
        }
        // Si el nodo se vació tras pop, eliminarlo
        if (A->indice == 0 && A->next) {
            Nodo* temp = A;
            A = A->next;
            delete temp;
        }
        return true;
    }

    bool isEmpty() const {
        return A == nullptr || (A->indice == 0 && A->next == nullptr);
    }

    void print() const {
        Nodo* nodo = A;
        while (nodo) {
            for (int i = nodo->indice - 1; i >= 0; --i) {
                cout << nodo->elem[i] << " ";
            }
            nodo = nodo->next;
        }
        cout << endl;
    }
};

int main() {
    Pila<int> pila;

    // Insertar 13 elementos
    for (int i = 1; i <= 13; ++i) {
        pila.push(i);
    }

    cout << "Contenido inicial de la pila:\n";
    pila.print();

    vector<int> eliminados;
    int valor;

    // Eliminar 8 elementos y almacenarlos externamente
    for (int i = 0; i < 8; ++i) {
        if (pila.pop(valor)) {
            eliminados.push_back(valor);
        }
    }

    cout << "Contenido final de la pila:\n";
    pila.print();

    cout << "Datos eliminados:\n";
    for (int v : eliminados) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}
