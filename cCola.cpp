#include <iostream>

using namespace std;

template<class T>
class Cola
{
private:
    T* head = nullptr;
    T* tail = nullptr;

    T elem[10];
    int count = 0; // nuevo: contador de elementos

public:

    Cola()
    {
        head = elem;
        tail = elem;
    }

    void push(T n)
    {
        if (count >= 10)
        {
            cout << "No hay mas espacio" << endl;
            return;
        }

        *tail = n;
        tail++;

        if (tail == elem + 10) // rebote al inicio si llegamos al final
            tail = elem;

        count++;
    }

    void pop()
    {
        if (count == 0)
        {
            cout << "No hay elementos a borrar" << endl;
            return;
        }

        head++;
        if (head == elem + 10)
            head = elem;

        count--;

        if (count == 0)
            cout << "No hay mas elementos" << endl;
    }

    void print()
    {
        for (int i = 0; i < count; i++)
        {
            T* p = head + i;
            if (p >= elem + 10) p -= 10; // rebote circular
            cout << *p << " ";
        }
        cout << endl;
    }
};

int main()
{
    Cola<int> array;

    array.pop();

    array.push(5);
    array.push(3);
    array.push(1);

    array.print();

    array.pop();

    array.print();

    array.pop();

    array.print();

    Cola<char> arraych;

    arraych.pop();

    arraych.push('a');
    arraych.push('z');
    arraych.push('e');

    arraych.print();

    arraych.pop();

    arraych.print();

    arraych.pop();

    arraych.print();

    arraych.push('a');
    arraych.push('a');
    arraych.push('a');
    arraych.push('a');
    arraych.push('a');
    arraych.push('a');
    arraych.push('a');
    arraych.push('d');
    arraych.push('z');
    arraych.push('z');

    arraych.print();

    return 0;
}
