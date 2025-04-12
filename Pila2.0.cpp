#include <iostream>

using namespace std;

class Nodo
{
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
class Pila
{
public:
	Nodo* A; 

	Pila() {
		A = new Nodo;
	}

	void push(T n)
	{
		if (A->indice < 5)
		{
			A->elem[A->indice++] = n;
		}
		else
		{
			Nodo* nuevo = new Nodo;
			nuevo->elem[nuevo->indice++] = n;
			nuevo->next = A;
			A = nuevo;
		}
	}

	void pop()
	{
		if (A == nullptr || (A->indice == 0 && A->next == nullptr))
		{
			cout << "Pila vacía\n";
			return;
		}

		if (A->indice > 0)
		{
			cout << "Se eliminó: " << A->elem[--A->indice] << endl;
		}
		else
		{
			Nodo* temp = A;
			A = A->next;
			delete temp;
			pop(); // seguir eliminando
		}
	}

	void print()
	{
		Nodo* nodo = A;
		while (nodo != nullptr) {
			for (int i = nodo->indice - 1; i >= 0; i--) {
				cout << nodo->elem[i] << " ";
			}
			nodo = nodo->next;
		}
		cout << endl;
	}
};

int main()
{
	Pila<int> pila;

	for (int i = 1; i <= 13; ++i) {
		pila.push(i);
	}

	pila.print();

	pila.pop();
	pila.pop();
	pila.pop();
	pila.pop();
	pila.pop();
	pila.pop();
	pila.pop();
	pila.pop();

	pila.print();

	return 0;
}
