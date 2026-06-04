#include <iostream>
//#include <vector>
#include "dynamicArray.h"
using namespace std;

template <typename T>
class binaryHeap {
private:
    Vector<T> data;
public:
    void append(const T& value) {
            /*data.push_back(value);
            int current = data.size() - 1;
            int parent = getParent(current);
            while(value > data[parent]&&current>0) {
                int temp = data[parent];
                data[parent] = value;
                data[current] = temp;
                current = parent;
                parent = getParent(current);

            }*/
        data.push_back(value);
        przekopcowanie_w_gore(data.size - 1);
        
    }

    void poll() {
        if (data.empty()) {
            return;
        }
        else if(data.size==1) {
            data.pop_back();
        }
        else {
            data[0] = data.back();
            data.pop_back();
            przekopcowanie_w_dol(0);
        }
    }
    void print() {
        for (int i = 0; i < data.size; i++) {
            cout << data[i] << endl;
        }
    }
    void clear() {
        data.clear();
    }
    bool empty() {
        return data.empty();
    }
private:
    void przekopcowanie_w_gore(int i) {
        if (i == 0) return;

        int parent = getParent(i);
        if (data[i] > data[parent]) {
            T temp = data[i];
            data[i] = data[parent];
            data[parent] = temp;
            przekopcowanie_w_gore(parent);
        }
    }
    void przekopcowanie_w_dol(int i) {
        if (i == data.size-1) return;
        int child=i;
        if (getRightChild(i) < data.size&&data[getRightChild(i)]>data[i]) {
            child = getRightChild(i);
        }
        if (getLeftChild(i) < data.size && data[getLeftChild(i)] > data[child]) {
      
                child = getLeftChild(i);

        }
        if (data[i] < data[child]) {
            T temp = data[i];
            data[i] = data[child];
            data[child] = temp;
            przekopcowanie_w_dol(child);
        }
        
    }


    int getParent(int index) {
        return (index - 1) / 2;
    }
    int getLeftChild(int index) {
        return 2*index+1;
    }
    int getRightChild(int index) {
        return 2 * index + 2;
    }


    
};

int main()
{
    
    srand(time(NULL));

    const int MAX_ORDER = 7;
    for (int o = 1; o <= MAX_ORDER; o++) {
        long long n = pow(10, o);
        binaryHeap<int> heap;
        clock_t t1 = clock();
        for (long long i = 0; i < n; i++) {
            int randomValue = rand();
            heap.append(randomValue);
        }
        clock_t t2 = clock();

        clock_t t3 = clock();
        while (!heap.empty()) {
            heap.poll();
        }
        clock_t t4 = clock();

        double timeAddTotal = double(t2 - t1) / CLOCKS_PER_SEC;
        double timeAddAvg = timeAddTotal / n;

        double timePollTotal = double(t4 - t3) / CLOCKS_PER_SEC;
        double timePollAvg = timePollTotal / n;

        cout << "--------------------------------------------------" << endl;
        cout << "ilosc danych: 10^" << o << " (n = " << n << ")" << endl;
        cout << "Append:" << endl;
        cout << "  Czas calkowity: " << timeAddTotal << " s" << endl;
        cout << "  Sredni czas na element: " << timeAddAvg << " s" << endl;
        cout << "Usuwanie:" << endl;
        cout << "  Czas calkowity: " << timePollTotal << " s" << endl;
        cout << "  Sredni czas na element: " << timePollAvg << " s" << endl;
    }
}
