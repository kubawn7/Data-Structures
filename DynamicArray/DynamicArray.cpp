#include <iostream>
#include <cassert>


using namespace std;
template<typename T>
class Vector {
private:
    
    int size;
    int capacity;
    T* data;

    void reAllocate(){
        
        capacity=capacity*2;
        cout << "realloc " << capacity << endl;
        T* newData = new T[capacity];

        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        
        delete[] data;
        data = newData;
    }
public:

    Vector() {
        size = 0;
        capacity = 1;
        data = new T[capacity];
    }

    Vector(const Vector& other) {
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    void push_back(const T& element) {
        if (size >= capacity) {
            reAllocate();
        }
        data[size] = element;
        size++;
    }

    void print(int amount=0) {
        if (!amount) {
            amount = size;
        }
        for (int i = 0; i < amount; i++) {
            cout << data[i]<<endl;
        }
    }

    const T& operator[](int index) const {
        if(index < 0 || index >= size) {
            throw std::out_of_range("Invalid index");
        }
        return data[index];

        
    }

    T& operator[](int index){
        
        if(index < 0 || index >= size) {
            throw std::out_of_range("Invalid index");
        }
        return data[index];
        
    }
    void clear(bool flag=false) {
        size = 0;
        for (int i = 0; i < size; i++) {
            data[i].~T();
        }
       

        if (flag) {
            delete[] data;
        }
    }




    void sort() {
        for (int i = 0; i < size-1; i++) {
            for (int j = 0; j < size-1-i; j++) {
                if (data[j] > data[j + 1])
                    swap(data[j], data[j + 1]);
            }
        }
    }
    
};

struct Object {
    int a;
    char b;

    Object() = default;
    Object(int a,char b):a(a), b(b) {

    }
    
    bool operator>(Object& other) {
        return a > other.a;
    }

    friend std::ostream& operator<<(std::ostream& out, const Object& object)
    {
        return out << object.a << " " << object.b;
    }
};

int main()
{
   
    Vector<Object>* da = new Vector<Object>();
    const int order = 7;
    const int n = pow(10, order);

    clock_t t1 = clock();

    double total_time = 0.0;
    double max_time_per_element = 0.0;
    double min_time_per_element = DBL_MAX;

    for (int i = 0; i < n; i++) {
        Object* so = new Object(rand() % 100, char((rand() % 25)+65));

        clock_t t1_element = clock(); 
        da->push_back(*so);
        clock_t t2_element = clock(); 

        double time_per_element = double(t2_element - t1_element) / CLOCKS_PER_SEC;
        total_time += time_per_element;

        if (time_per_element < min_time_per_element) {
            min_time_per_element = time_per_element;
        }

        if (time_per_element > max_time_per_element) {
            max_time_per_element = time_per_element;
        }


        delete so; 
    }

    clock_t t2 = clock();

    cout << "100 pierwszych elementow wektora:" << endl;
    da->print(100);
    
    double total_time_seconds = double(t2 - t1) / CLOCKS_PER_SEC;
    double amortized_time = total_time / n; 

    
    cout << "Czas calkowity dla wstawienia " << n << " elementow: " << total_time_seconds << " sekund" << endl;
    cout << "Sredni (zamortyzowany) czas dla pojedynczego wstawienia: " << amortized_time << " sekund" << endl;
    cout << "Maksymalny czas wstawienia elementu: " << max_time_per_element << " sekund" << endl;
    cout << "Minimalny czas wstawienia elementu: " << min_time_per_element << " sekund" << endl;

    
    da->clear(true);
    delete da;

    return 0;
   
}
