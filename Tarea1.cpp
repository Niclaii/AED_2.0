#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace std::chrono;

// 1. Bubble Sort como función tradicional
void bubbleSortFunction(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 2. Bubble Sort usando un Funtor
struct BubbleSortFunctor {
    void operator()(int* arr, int n) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
};

// 3. Bubble Sort con Polimorfismo (clase base y herencia)
class BubbleSortBase {
public:
    virtual void sort(int* arr, int n) = 0;
    virtual ~BubbleSortBase() {}
};

class BubbleSortDerived : public BubbleSortBase {
public:
    void sort(int* arr, int n) override {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
};

// 4. Bubble Sort usando un Function Object
class BubbleSortFunctionObject {
public:
    void operator()(int* arr, int n) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
};

// Función auxiliar para medir el tiempo de ejecución
template <typename Func>
void measureTime(Func func, int* arr, int n, const string& method) {
    auto start = high_resolution_clock::now();
    func(arr, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    
    cout << "Tiempo de ejecución con " << method << ": " << duration.count() << " ms" << endl;
}

int main() {
    int sizes[] = {1000, 10000, 50000, 75000, 100000};
    int numTests = sizeof(sizes) / sizeof(sizes[0]);

    for (int t = 0; t < numTests; t++) {
        int n = sizes[t];

        // Crear arreglos dinámicos
        int* arr1 = new int[n];
        int* arr2 = new int[n];
        int* arr3 = new int[n];
        int* arr4 = new int[n];

        // Llenar los arreglos con datos en orden descendente
        for (int i = 0; i < n; i++) {
            arr1[i] = n - i;
        }
        // Copiar datos en los demás arreglos
        for (int i = 0; i < n; i++) {
            arr2[i] = arr1[i];
            arr3[i] = arr1[i];
            arr4[i] = arr1[i];
        }

        cout << "\nPrueba con " << n << " elementos:" << endl;

        // Usando la función
        measureTime(bubbleSortFunction, arr1, n, "Función");

        // Usando el funtor
        BubbleSortFunctor sorter;
        measureTime([&sorter](int* arr, int n) { sorter(arr, n); }, arr2, n, "Funtor");

        // Usando polimorfismo
        BubbleSortDerived derivedSorter;
        measureTime([&derivedSorter](int* arr, int n) { derivedSorter.sort(arr, n); }, arr3, n, "Polimorfismo");

        // Usando Function Object
        BubbleSortFunctionObject functionObject;
        measureTime([&functionObject](int* arr, int n) { functionObject(arr, n); }, arr4, n, "Function Object");

        // Liberar memoria
        delete[] arr1;
        delete[] arr2;
        delete[] arr3;
        delete[] arr4;
    }

    return 0;
}