#include <iostream>
using namespace std;

class Nodo {
public:
    int A[5];
    Nodo* next;

    Nodo() { next = nullptr; }
};

template<class T>
class Cola {
public:
    Nodo* head = nullptr;
    Nodo* tail = nullptr;
    int list = 0;        

    Cola() {
        head = tail = new Nodo();
        list = 0;
    }

    void push(T n) {
        if (tail == nullptr) {
            tail = new Nodo();
            head = tail;
        }

        int i = 0;
        while (i < 5 && tail->A[i] != 0) i++;

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

    void pop() {
        if (isEmpty()) {
            cout << "Cola vacía.\n";
            return;
        }

        while (list < 5 && head->A[list] == 0) list++;

        if (list < 5) {
            head->A[list] = 0;
            list++;
        }

        if (list == 5) {
            Nodo* temp = head;
            head = head->next;
            delete temp;
            list = 0;
        }

        if (head == nullptr) {
            head = tail = new Nodo();
            list = 0;
        }
    }

    bool isEmpty() {
        Nodo* temp = head;
        while (temp != nullptr) {
            for (int i = 0; i < 5; i++) {
                if (temp->A[i] != 0) return false;
            }
            temp = temp->next;
        }
        return true;
    }

    void print() {
        Nodo* current = head;
        while (current != nullptr) {
            for (int i = 0; i < 5; i++) {
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

    for (int i = 1; i <= 12; ++i) {
        c.push(i);
    }

    cout << "Cola tras 12 inserciones:\n";
    c.print();

    for (int i = 0; i < 6; ++i) {
        c.pop();
    }

    cout << "Cola tras 6 eliminaciones:\n";
    c.print();

    c.pop();
    c.pop();
    c.pop();

    cout << "Cola tras 3 eliminaciones:\n";
    c.print();


    c.push(100);
    c.push(200);

    cout << "Cola tras insertar 100 y 200:\n";
    c.print();

    return 0;
}
