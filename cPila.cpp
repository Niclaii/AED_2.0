#include <iostream>

using namespace std;

template<class T>
class Pila
{
private:

	T* top = nullptr;
	T elem[10];

public:

	Pila()
	{
		top = elem + 10;
	}

	void push(T n)
	{
		if (top == elem)
		{
			cout << "Se ha llenado el almacenamiento\n";
		}
		else
		{
			--top;
			*top = n;
		}
	}

	void pop()
	{
		if (top == elem + 10)
		{
			cout << "No hay elementos a eliminar\n";
		}
		else
		{
			cout << "Se ha eliminado: " << *top << endl;
			top++;
			if (top == elem + 10)
			{
				cout << "Se ha vaciado la pila\n";
			}
		}
	}

	void print()
	{
		for (T* p = top; p < elem + 10; ++p)
		{
			cout << *p;
		}
		cout << endl;
	}
};


int main()
{
	Pila<int> array;

	array.push(5);
	
	array.print();
	
	array.push(3);
	array.push(1);
	array.push(4);
	array.push(6);

	array.print();

	array.pop();

	array.print();

	array.pop();
	array.pop();

	array.print();

	array.pop();
	array.pop();
	array.pop();

	Pila<char> arrayc;

	arrayc.push('a');
		 
	arrayc.print();
		 
	arrayc.push('c');
	arrayc.push('d');
	arrayc.push('h');
	arrayc.push('z');
	arrayc.push('z');
	arrayc.push('z');
	arrayc.push('z');
	arrayc.push('z');
	arrayc.push('z');
	arrayc.push('z');
	arrayc.push('z');
		 
	arrayc.print();
		 
	arrayc.pop();
		 
	arrayc.print();
		 
	arrayc.pop();
	arrayc.pop();
		 
	arrayc.print();
		 
	arrayc.pop();
	arrayc.pop();
	arrayc.pop();


	return 0;
}