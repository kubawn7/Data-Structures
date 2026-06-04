#pragma once
#pragma once
#include <iostream>
#include <cassert>


using namespace std;
template<typename T>
class Vector {
    public:

    int size;
    int capacity;
    T* data;

    void reAllocate() {

        capacity = capacity * 2;
        T* newData = new T[capacity];

        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
    }

    bool empty() {
        return size==0;
    }
    T& back() {
        return data[size - 1];
    }
    

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

    void print(int amount = 0) {
        if (!amount) {
            amount = size;
        }
        for (int i = 0; i < amount; i++) {
            cout << data[i] << endl;
        }
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Invalid index");
        }
        return data[index];


    }

    T& operator[](int index) {

        if (index < 0 || index >= size) {
            throw std::out_of_range("Invalid index");
        }
        return data[index];

    }
    void pop_back() {
        if (size > 0) {
            size--;
        }
    }
    void clear(bool flag = false) {
        size = 0;
    }




    void sort() {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - 1 - i; j++) {
                if (data[j] > data[j + 1])
                    swap(data[j], data[j + 1]);
            }
        }
    }
    ~Vector() {
        delete[] data;
    }

};
