#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

// **Genera un array aleatorio**
template <typename T>
void generateRandomArray(T* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000; // Valores entre 0 y 9999 (para tipos numéricos)
    }
}

// **Bubble Sort como función tradicional**
template <typename T>
void bubbleSortFunction(T* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// **Bubble Sort usando un Functor**
template <typename T>
struct BubbleSortFunctor {
    void operator()(T* arr, int n) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
};

// **Bubble Sort con Polimorfismo**
template <typename T>
class BubbleSortBase {
public:
    virtual void sort(T* arr, int n) = 0;
    virtual ~BubbleSortBase() {}
};

template <typename T>
class BubbleSortDerived : public BubbleSortBase<T> {
public:
    void sort(T* arr, int n) override {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
};

// **Bubble Sort usando Function Object**
template <typename T>
class BubbleSortFunctionObject {
public:
    void operator()(T* arr, int n) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
};

// **Función auxiliar para medir el tiempo de ejecución**
template <typename T, typename Func>
void measureTime(Func func, T* arr, int n, const string& method) {
    auto start = high_resolution_clock::now();
    func(arr, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Tiempo de ejecución con " << method << ": " << duration.count() << " ms" << endl;
}

int main() {
    srand(time(0)); // Inicializar la semilla aleatoria

    int sizes[] = {1000, 5000, 10000}; // Reduciendo las pruebas para evitar tiempos largos
    int numTests = sizeof(sizes) / sizeof(sizes[0]);

    for (int t = 0; t < numTests; t++) {
        int n = sizes[t];

        // Crear arreglos dinámicos
        int* arr1 = new int[n];
        int* arr2 = new int[n];
        int* arr3 = new int[n];
        int* arr4 = new int[n];

        // Generar nuevos datos aleatorios en cada iteración
        generateRandomArray(arr1, n);
        for (int i = 0; i < n; i++) {
            arr2[i] = arr1[i];
            arr3[i] = arr1[i];
            arr4[i] = arr1[i];
        }

        cout << "\nPrueba con " << n << " elementos:" << endl;

        // Usando la función
        measureTime<int>(bubbleSortFunction<int>, arr1, n, "Función");

        // Usando el funtor
        BubbleSortFunctor<int> sorter;
        measureTime<int>([&sorter](int* arr, int n) { sorter(arr, n); }, arr2, n, "Funtor");

        // Usando polimorfismo
        BubbleSortDerived<int> derivedSorter;
        measureTime<int>([&derivedSorter](int* arr, int n) { derivedSorter.sort(arr, n); }, arr3, n, "Polimorfismo");

        // Usando Function Object
        BubbleSortFunctionObject<int> functionObject;
        measureTime<int>([&functionObject](int* arr, int n) { functionObject(arr, n); }, arr4, n, "Function Object");

        // Liberar memoria
        delete[] arr1;
        delete[] arr2;
        delete[] arr3;
        delete[] arr4;
    }

    return 0;
}