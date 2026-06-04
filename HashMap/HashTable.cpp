#include <iostream>
#include <chrono>
#include <cmath>
#include "DynamicArray.h"
#include "LinkedList.h"
using namespace std;


template <class T>
class hashTable {
public:
	class KeyValue {
	public:
		string key;
		T value;
		KeyValue(string key = "", T value = T()) : key(key), value(value) {}

		friend ostream& operator<<(ostream& os, const KeyValue& kv) {
			os << "[" << kv.key << ": " << kv.value << "]";
			return os;
		}

		bool operator==(const KeyValue& other) const {
			return key == other.key;
		}
	};
private:
	Vector<LinkedList<KeyValue>> data;
	int size = 0;

	size_t hash(const string& str, int capacity) {
		size_t sum = 0;
		for (size_t i{}; i < str.length(); ++i) {
			sum += int(str[i]) * pow(31, str.length() - i - 1);
		}

		return sum % capacity;
	}

	void rehash() {
		Vector<LinkedList<KeyValue>> newVector(data.getCapacity() * 2);

		for (int i{}; i < data.getCapacity(); i++) {
			if (!data[i].isEmpty()) {
				auto* currentNode = data[i].head;

				while (currentNode != nullptr) {
					string key = currentNode->value.key;
					T value = currentNode->value.value;


					size_t index = hash(key, newVector.getCapacity());


					KeyValue element(key, value);
					newVector[index].append(element);

					currentNode = currentNode->next;
				}
			}
		}
		data = newVector;




	}


public:
	hashTable() {

	}

	int getSize() {
		return size;
	}
	void append(string key, T value) {
		if ((float)size / data.getCapacity() >= 0.75) {
			rehash();

		}
		auto element1 = find(key);
		if (element1) {
			element1->value = value;
			return;
		}
		size_t index = hash(key, data.getCapacity());
		KeyValue element(key, value);
		data[index].append(element);
		size++;


	}

	KeyValue* find(string key) {
		size_t index = hash(key, data.getCapacity());
		if (data[index].isEmpty()) {
			return nullptr;
		}
		auto* current_node = data[index].head;
		while (current_node != nullptr) {
			if (current_node->value.key == key) {
				return &current_node->value;
			}
			else {
				current_node = current_node->next;
			}
		}
		return nullptr;


	}

	bool remove(string key) {
		size_t index = hash(key, data.getCapacity());
		if (data[index].isEmpty()) {
			return false;
		}
		auto* current_node = data[index].head;

		if (data[index].removeElement(KeyValue(key, T()))) {
			size--;
			return true;
		}
		return false;

	}
	void clear() {
		for (int i{}; i < data.getCapacity(); i++) {
			if (!data[i].isEmpty()) {
				data[i].clear();

			}
		}
		size = 0;
	}

	void print() {
		
		for (int i{}; i < data.getCapacity(); i++) {
			cout << "[" << i << "] ";
			data[i].print();
		}
		cout << "size: " << getSize() << endl;
		cout << "rozmiar tablicy: " << data.getCapacity() << endl;
	}

	T& operator[](string key) {
		return find(key)->value;
	}

};

string randstr() {
	string str = "";
	
	for (int i = 0; i < 6; i++) {
		str += char(rand() % (90 - 65) + 65);
	}
	return str;
}

int main()
{
	using namespace std::chrono;
	hashTable<int> h;
	srand(time(NULL));

	/*const int MAX_ORDER = 7;

	for (int i{}; i < MAX_ORDER; i++) {
		long long n = pow(10, i);


		auto start = high_resolution_clock::now();
		for (int j = 0; j < n; j++) {
			h.append(randstr(), i);
		}
		auto end = high_resolution_clock::now();
		auto durationAdd = duration_cast<milliseconds>(end - start);

		start = high_resolution_clock::now();
		for (int j = 0; j < n; j++) {
			h.find(randstr());
		}
		end = high_resolution_clock::now();
		auto durationFind = duration_cast<milliseconds>(end - start);
		start = high_resolution_clock::now();
		for (int j = 0; j < n; j++) {
			h.remove(randstr());
		}
		end = high_resolution_clock::now();
		auto durationRemove = duration_cast<milliseconds>(end - start);

		cout << "-------------------------------------------------" << endl;
		cout << "czas dodawania " << n << " elementow: " << durationAdd << endl;
		cout << "czas wyszukania " << n << " elementow: " << durationFind << endl;

		cout << "czas usuniecia " << n << " elementow: " << durationRemove << endl;




	}*/
	for (int i = 0; i < 100; i++) {
		h.append(randstr(), i);
	}

	h.print();
	//cout << randstr();



}