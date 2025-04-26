#include <iostream>
#include <stack>
using namespace std;

class Nodo {
public:
    int* A;       
    Nodo* next;

    Nodo() : next(nullptr) {
        A = new int[5]();  
    }

    ~Nodo() {
        delete[] A;
    }
};

template<class T>
class Cola {
public:
    Nodo* head;
    Nodo* tail;
    int listIndex; 

    Cola() : head(nullptr), tail(nullptr), listIndex(0) {}

    void push(const T& n) {
        if (!tail) {
            head = tail = new Nodo();
            listIndex = 0;
            tail->A[0] = n;
            return;
        }
        int i = 0;
        while (i < 5 && tail->A[i] != 0) ++i;
        if (i == 5) {
            Nodo* nuevo = new Nodo();
            tail->next = nuevo;
            tail = nuevo;
            tail->A[0] = n;
        }
        else {
            tail->A[i] = n;
        }
    }

    bool pop(T& dato) {
        if (!head || isEmpty()) {
            cout << "Cola vacía.\n";
            return false;
        }
        while (listIndex < 5 && head->A[listIndex] == 0) ++listIndex;
        if (listIndex < 5) {
            dato = head->A[listIndex];
            head->A[listIndex] = 0;
            ++listIndex;
        }
        if (listIndex == 5) {
            Nodo* temp = head;
            head = head->next;
            delete temp;
            listIndex = 0;
            if (!head) {
                tail = nullptr;
            }
        }
        return true;
    }

    bool isEmpty() const {
        Nodo* temp = head;
        while (temp) {
            for (int i = 0; i < 5; ++i) {
                if (temp->A[i] != 0) return false;
            }
            temp = temp->next;
        }
        return true;
    }

    void print() const {
        Nodo* current = head;
        while (current) {
            for (int i = 0; i < 5; ++i) {
                if (current->A[i] != 0) {
                    cout << current->A[i] << " ";
                }
            }
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    Cola<int> c;

    cout << "Cola inicial (vacia):\n";
    c.print();

    for (int i = 1; i <= 12; ++i) {
        c.push(i);
    }
    cout << "Cola tras 12 inserciones:\n";
    c.print();

    stack<int> trash;
    int valor;

    cout << "Extracciones de 6 elementos:\n";
    for (int i = 0; i < 6; ++i) {
        if (c.pop(valor)) {
            cout << "  Extraído: " << valor << endl;
            trash.push(valor);
        }
    }
    cout << "Cola tras 6 eliminaciones:\n";
    c.print();

    cout << "Extracciones de 3 elementos:\n";
    for (int i = 0; i < 3; ++i) {
        if (c.pop(valor)) {
            cout << "  Extraido: " << valor << endl;
            trash.push(valor);
        }
    }
    cout << "Cola tras 3 eliminaciones adicionales:\n";
    c.print();

    c.push(100);
    c.push(200);
    cout << "Cola tras insertar 100 y 200:\n";
    c.print();

    
    cout << "\nValores extraidos: ";
    while (!trash.empty()) {
        cout << trash.top() << " ";
        trash.pop();
    }
    cout << endl;

    return 0;
}
