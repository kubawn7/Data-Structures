#include <iostream>
#include <time.h>
#include <cstdlib> 
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

template <class T>
class Element {
public:
    Element(const T& value) :value(value) {}
    Element<T>* next = nullptr;
    Element<T>* prev = nullptr;
    T value;

};


template<class T>
class LinkedList {

private:
    
    


public:
    Element<T>* head=nullptr;
    Element<T>* tail=nullptr;
    size_t size = 0;
   
    LinkedList()=default;

    LinkedList(T tab[], size_t size) {
        for (size_t i = 0; i < size; i++) {
            append(tab[i]);
        }
    }
    LinkedList(std::initializer_list<T> list)
    {
        for (const auto& val : list) {
            append(val);
        }
    }
    LinkedList(const LinkedList& other) {
        for (Element<T>* curr = other.head; curr != nullptr; curr = curr->next) {
            append(curr->value);
        }
    }

    
    void append(T e) {
        Element<T>* element = new Element<T>(e);
        if (head==nullptr) {
            head = tail = element;

        }
        else {
            tail->next = element;
            element->next = nullptr;
            element->prev = tail;
            tail = element;
        }
        size++;
    }

    void push_front(T e) {
        Element<T>* element = new Element<T>(e);
        if (head == nullptr) {
            head = tail = element;
        }
        else {
            head->prev = element;
            element->next = head;
            element->prev = nullptr;
            head = element;
        }
        size++;

    }

    void pop() {
        if (head == nullptr) return;
        Element<T>* toDelete = tail;
        if (size == 1) {
            head = nullptr;
            tail = nullptr;
        }
        else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete toDelete;
        size--;
        
    }

    void removeFirst() {
        if (head == nullptr) return;
        Element<T>* toDelete = head;
        if (size == 1) {
            head = nullptr;
            tail = nullptr;
        }
        else {
            head = head->next;
            head->prev = nullptr;
        }
        delete toDelete;
        size--;
    }


    Element<T>* findElement(T e) {
        Element<T>* curr = head;
        while (curr != nullptr) {
            if (curr->value == e) {
                return curr;
            }
            curr = curr->next;
        }
        return nullptr;
    }

    bool removeElement(T e) {
        Element<T>* curr = head;
        while (curr != nullptr) {
            if (curr->value == e) {
                Element<T>* toDelete = curr;
                if (toDelete == head) {
                    head = toDelete->next;
                    if (head) head->prev = nullptr;
                    else tail = nullptr;
                }
                else if (toDelete == tail) {
                    tail = toDelete->prev;
                    if (tail) tail->next = nullptr;
                    else head = nullptr;
                }
                else {
                    toDelete->prev->next = toDelete->next;
                    toDelete->next->prev = toDelete->prev;
                }
                delete toDelete;
                size--;
                return true;
            }
            else {
                curr = curr->next;
            }
        }
        return false;
    }

    const T& operator[](size_t index) const {
        if (index > size-1)
            throw std::out_of_range("Invalid index");
        Element<T>* curr = head;
        for (size_t i = 0; i < index; i++) {
            curr = curr->next;
        }
        return curr->value;
    }

    T& operator[](size_t index) {
        if (index > size - 1) {
            throw std::out_of_range("Invalid index");
        }
        Element<T>* curr = head;
        for (size_t i = 0; i < index; i++) {
            curr = curr->next;
        }
        return curr->value;
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) { 
            clear();
            for (Element<T>* curr = other.head; curr != nullptr; curr = curr->next) {
                append(curr->value);
            }
        }
        return *this;
    }

    bool operator==(const LinkedList& other) {
        if (size != other.size) return false;
            
        Element<T>* curr1 = head;
        Element<T>* curr2 = other.head;

        while (curr1&&curr2) {
            if (curr1->value != curr2->value) return false;

            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        return true;
            
        
        
    }

    bool isEmpty() const{
        return head == nullptr;
    }

    void clear() {
        if (head != nullptr) {
            Element<T>* curr = head;
            while (curr) {
                Element<T>* next = curr->next;
                delete curr;
                curr = next;
            }
        }
        head = tail = nullptr;
        size = 0;
    }
   
    void insertElement(T e, int index=-1) {
        
        if (index >=int(size) ){
            throw out_of_range("Invalid index");
            return;
            
        }
        

        Element<T>* toInsert = new Element<T>(e);
        Element<T>* curr = head;
        if (index == 0) {
            push_front(e);
            return;
        }

        if(isEmpty()) {
            tail = toInsert;
            head = toInsert;
            size++;
            return;
        }
        
        if (index==-1) {
            if constexpr (std::three_way_comparable<T>) {
                if (tail->value < toInsert->value) {
                    tail->next = toInsert;
                    toInsert->prev = tail;
                    toInsert->next = nullptr;
                    tail = toInsert;
                    
                }

                else if (head->value >= toInsert->value) {
                    head->prev = toInsert;
                    toInsert->next = head;
                    toInsert->prev = nullptr;
                    head = toInsert;

                }
                else {
                    while (curr->next != nullptr) {

                        if (curr->next->value >= toInsert->value) {

                            toInsert->prev = curr;
                            toInsert->next = curr->next;
                            curr->next->prev = toInsert;
                            curr->next = toInsert;
                            break;
                        }
                        curr = curr->next;

                    }
                }
                size++;
            }
            else {
                append(e);
            }
        }
        else {
            for (int i = 0; i < index-1; i++) {
                curr = curr->next;
            }
            curr->next->prev = toInsert;
            toInsert->next=curr->next;
            curr->next = toInsert;
            toInsert->prev = curr;
            size++;

        }
        
     
       

    }


    void print() const{
        if (!isEmpty()) {
           
                Element<T>* curr = head;
                while (curr != nullptr) {
                    if constexpr (std::is_convertible<T, int>::value || std::is_convertible<T, string>::value) {
                        cout << "wartosc: " << curr->value << " ||" << " adres: " << curr << endl;
                    }
                    else {
                        cout <<"adres: " << curr << endl;
             
                    }
                    curr = curr->next;
                }
                cout << "rozmiar listy: " << size << endl;

        }
        else {
            cout<<"brak elementow w liscie"<<endl;
        }
       
    }
    
    ~LinkedList() {
        clear();
    }


};

struct Object {

    Object(int a,int b) :a(a), b(b) {};
    int a;
    int b;
    
    
};


void testLinkedList() {
    LinkedList<int> list;
    auto start = high_resolution_clock::now();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    // Test dla czasu dodawania elementów na początek
    start = high_resolution_clock::now();
    for (int i = 0; i < 100000; i++) {
        list.push_front(i);
    }
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "Czas dodawania 10000 elementow na poczatek: " << duration.count() << " mikrosekund." << endl;
    cout << endl;
    // Test dla czasu dodawania elementów na koniec
    start = high_resolution_clock::now();
    for (int i = 0; i < 100000; i++) {
        list.append(i);
    }
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "Czas dodawania 10000 elementow na koniec: " << duration.count() << " mikrosekund." << endl;
    cout << endl;
    // Test dla czasu usuwania elementów z początku
    start = high_resolution_clock::now();
    for (int i = 0; i < 50000; i++) {
        list.removeFirst();
    }
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "Czas usuwania 10000 elementow z poczatku: " << duration.count() << " mikrosekund." << endl;
    cout << endl;
    // Test dla czasu usuwania elementów z końca
    start = high_resolution_clock::now();
    for (int i = 0; i < 50000; i++) {
        list.pop();
    }
    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "Czas usuwania 10000 elementow z konca: " << duration.count() << " mikrosekund." << endl;
    cout << endl;
}

void test2() {

    LinkedList<int> ll{};
    
    for (int i = 0; i < 10000; i++) {
        ll.append(i);
    }
    int random = 0;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < 10000; i++) {
        
        ll.findElement(rand()%10000);
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Calkowity czas wyszukiwania 10000 elementow po wartosci: " << duration << " mikrosekund." << endl;
    cout << "Sredni czas wyszukiwania elementu: " << duration/10000 << " mikrosekund." << endl;
    cout << endl;

    start = high_resolution_clock::now();
   /* for (int i = 0; i < 10000; i++) {

        ll.removeElement(rand() % 10000);
    }*/

    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "Calkowity czas usuwania 10000 elementow po wartosci: " << duration << " mikrosekund." << endl;
    cout << "Sredni czas usuwania elementu: " << duration / 10000 << " mikrosekund." << endl;
    cout << endl;


    start = high_resolution_clock::now();
    for (int i = 0; i < 10000; i++) {

        ll[rand() % 10000];
    }

    end = high_resolution_clock::now();
    duration = duration_cast<microseconds>(end - start);
    cout << "Calkowity czas dostępu do 10000 wartosci: " << duration << " mikrosekund." << endl;
    cout << "Sredni czas dostepu do wartosci: " << duration / 10000 << " mikrosekund." << endl;



}


int main()
{
    //Konstrukcja listy

    
    
    
   // LinkedList<int> list2{ 1,2,4,5 };
    

   



    

    ////Dołączanie elementów do listy na początku
    //list1.push_front(-1);
    //list1.print();

    ////Wstawianie elementów listy w środku
    //list1.insertElement(2); // bez drugiego argumentu wstawi do listy w porządku rosnącym
    //list1.insertElement(5,3); // drugi parametr oznacza indeks wstawienia elementu

    ////Usuwanie elementu z początku, końca i podanego jako argument funckji
    //list1.removeFirst();
    //list1.pop();
    //list1.removeElement(4); //Jeżeli nie znajdzie elementu do usunięcia zwraca false

    ////Wyszukiwanie elementu
    //list1.findElement(3);
    //list1[0];
    //list1[2]+=52;
    //list1.print();

    //test();
    //int n = 100;
    //for (int i = 1; i < n; i++) {
    //    cout <<  rand() % int(i) << endl;
    //    // ll.insertElement(n, );
    //}
    //testLinkedList();
    //test2();
    testLinkedList();
    test2();
    return 0;



}

