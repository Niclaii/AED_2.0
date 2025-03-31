#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

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

class BubbleSortBase {
public:
    virtual void sort(vector<int>& arr) = 0;
    virtual ~BubbleSortBase() {}
};

class BubbleSortPolimorfismo : public BubbleSortBase {
public:
    void sort(vector<int>& arr)  {
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

// FUNCION PARA MEDIR EL TIEMPO
template <typename Func>
void measureTime(Func func, vector<int> arr, const string& method) {
    auto start = high_resolution_clock::now();
    func(arr);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Tiempo de ejecucion con " << method << ": " << duration.count() << " ms" << endl;
}

int main() {
    vector<int> sizes = { 100, 1000,5000, 10000,25000, 50000,75000,100000 };

    vector<int> base_data = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    for (int size : sizes) {    //ITERACION SOBRE CADA ELEMENTO
        vector<int> arr1(base_data.begin(), base_data.end());
        vector<int> arr2(base_data.begin(), base_data.end());
        vector<int> arr3(base_data.begin(), base_data.end());
        vector<int> arr4(base_data.begin(), base_data.end());

        while (arr1.size() < size) {
            arr1.insert(arr1.end(), base_data.begin(), base_data.end());
        }
        arr1.resize(size);
        arr2 = arr1;
        arr3 = arr1;
        arr4 = arr1;

        cout << "\nPrueba con " << size << " elementos:" << endl;

        measureTime(bubbleSortFunction<int>, arr1, "Funcion");

        BubbleSortFunctor sorter;
        measureTime([&sorter](vector<int>& arr) { sorter(arr); }, arr2, "Funtor");

        BubbleSortPolimorfismo PolimorfismoSorter;
        measureTime([&PolimorfismoSorter](vector<int>& arr) { PolimorfismoSorter.sort(arr); }, arr3, "Polimorfismo");

        BubbleSortFunctionObject functionObject;
        measureTime([&functionObject](vector<int>& arr) { functionObject(arr); }, arr4, "Function Object");
    }

    return 0;
}