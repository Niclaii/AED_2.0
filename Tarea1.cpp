#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

// 1. Bubble Sort como función tradicional
template <typename T>
void bubbleSortFunction(vector<T>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 2. Bubble Sort usando un Funtor
struct BubbleSortFunctor {
    template <typename T>
    void operator()(vector<T>& arr) {
        size_t n = arr.size();
        for (size_t i = 0; i < n - 1; i++) {
            for (size_t j = 0; j < n - i - 1; j++) {
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
    virtual void sort(vector<int>& arr) = 0;
    virtual ~BubbleSortBase() {}
};

class BubbleSortDerived : public BubbleSortBase {
public:
    void sort(vector<int>& arr) override {
        size_t n = arr.size();
        for (size_t i = 0; i < n - 1; i++) {
            for (size_t j = 0; j < n - i - 1; j++) {
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
    void operator()(vector<int>& arr) {
        size_t n = arr.size();
        for (size_t i = 0; i < n - 1; i++) {
            for (size_t j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
};

// Función auxiliar para medir el tiempo de ejecución y guardar en archivo
template <typename Func>
void measureTime(Func func, vector<int> arr, const string& method) {
    auto start = high_resolution_clock::now();
    func(arr);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Tiempo de ejecucion con " << method << ": " << duration.count() << " ms" << endl;
    
}

int main() {
    vector<int> sizes = { 100, 1000, 10000, 50000 };

    for (int size : sizes) {
        vector<int> arr1(size);
        vector<int> arr2(size);
        vector<int> arr3(size);
        vector<int> arr4(size);

        // Rellenamos con valores aleatorios
        generate(arr1.begin(), arr1.end(), rand);
        arr2 = arr1;
        arr3 = arr1;
        arr4 = arr1;

        cout << "\nPrueba con " << size << " elementos:" << endl;

        // Usando la función
        measureTime(bubbleSortFunction<int>, arr1, "Funcion");

        // Usando el funtor
        BubbleSortFunctor sorter;
        measureTime([&sorter](vector<int>& arr) { sorter(arr); }, arr2, "Funtor");

        // Usando polimorfismo
        BubbleSortDerived derivedSorter;
        measureTime([&derivedSorter](vector<int>& arr) { derivedSorter.sort(arr); }, arr3, "Polimorfismo");

        // Usando Function Object
        BubbleSortFunctionObject functionObject;
        measureTime([&functionObject](vector<int>& arr) { functionObject(arr); }, arr4, "Function Object");
    }
    return 0;
}
