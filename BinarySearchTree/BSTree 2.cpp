#include <iostream>
#include <vector>
#include <chrono>
#include <string>

template<typename T>
class Node {
public:
    Node* left;
    Node* right;
    Node* parent;
    T value;
    Node(Node* parent, Node* left, Node* right, T value):parent(parent), left(left), right(right), value(value) {

    }

};

template<typename T>
class Tree {
public:
    int size = 0;
    int height = 0;
    Node<T>* root;
    
    Tree() {
        root = nullptr;
    }


    void append(T element) {
        Node<T>* newNode = new Node<T>{ nullptr, nullptr, nullptr, element };
        if (!root) {
            root = newNode;
            
            size++;
            return;
        }

        Node<T>* curr = root;
        

        while (curr) {
            if (element>curr->value) {
                if (!curr->right) {
                    curr->right = newNode;
                    curr->right->parent = curr;
                    break;
                }
                curr = curr->right;
            }
            else {
                if (!curr->left) {
                    curr->left = newNode;
                    curr->left->parent = curr;
                    break;
                }
                curr = curr->left;
            }
            
        }

        

        size++;
    }
    void inorder(Node<T>* node) {
        if (!node) {
            return;
        }
        
        inorder(node->left);
        std::cout << node->value << " ";
        inorder(node->right);

    }
 
    void preorder(Node<T>* node) {
        if (!node) {
            return;
        }

        std::cout << node->value << " ";
        preorder(node->left);
        preorder(node->right);



    }


    void print(Node<T>* node) {
        if (!node) {
            return;
        }
        if (node == root) {
            std::cout << "rozmiar: " << size<<"\n";
            std::cout << "wysokosc: " <<getHeight()<<"\n";
        }
        if (node->left && node->right) {
            std::cout << node->value << " ma dzieci: " << node->left->value << " i " << node->right->value <<"\n";
        }
        else if (node->left) {
            std::cout << node->value << " ma tylko lewe dziecko: " << node->left->value <<"\n";
        }
        else if (node->right) {
            std::cout << node->value << " ma tylko prawe dziecko: " << node->right->value <<"\n";
        }
        else {
            std::cout << node->value << " nie ma dzieci\n";
        }

        print(node->left);
        print(node->right);
        
    }


    Node<T>* find(T element){
        Node<T>* curr = root;
        while (curr != nullptr) {
           if (element>curr->value) {
                curr = curr->right;
           }
           else if (element<curr->value) {
               curr = curr->left;
           }
           else {
               return curr;
           }
        }
        return nullptr;
    }
    private:
    T deleteRecursive(Node<T>* toDelete) {
        Node<T>* minNode = toDelete->right;
        

        while (minNode && minNode->left) {
            minNode = minNode->left;
        }
        
        T value = minNode->value;
        
        deleteElement(minNode);
        return value;
    }
    public:
    void deleteElement(Node<T>* toDelete) {
        
        if (toDelete == nullptr) {
            std::cout << "Element nie istnieje w drzewie.\n";
            return;
        }

        if (toDelete->left == nullptr && toDelete->right == nullptr) {
            if (toDelete->parent == nullptr) {
                root = nullptr;
            }
            else if (toDelete->parent->left == toDelete) {
                toDelete->parent->left = nullptr;
            }
            else {
                toDelete->parent->right = nullptr;
            }
            delete toDelete;
            size--;
            
        }

        else if (toDelete->left == nullptr || toDelete->right == nullptr) {
            Node<T>* child = (toDelete->left) ? toDelete->left : toDelete->right;
            if (toDelete->parent == nullptr) {
                root = child;
            }
            else if (toDelete->parent->left == toDelete) {
                toDelete->parent->left = child;
            }
            else {
                toDelete->parent->right = child;
            }
            child->parent = toDelete->parent;
            delete toDelete;
            size--;
            
        }
        else {
            T value = deleteRecursive(toDelete);
            toDelete->value = value;
        }
       
    }
    public:
        

        int getHeightRecursive(Node<T>* node) {
            if (!node) return 0;

            int leftHeight = getHeightRecursive(node->left);
            int rightHeight = getHeightRecursive(node->right);

            return std::max(leftHeight, rightHeight) + 1;
        }
        private:
    void inOrderDel(Node<T>* node) {
        if (!node) {
            return;
        }


        inOrderDel(node->left);
        
        inOrderDel(node->right);
        delete node;
    }
    public:
    void clear() {
        if (!root) {
            std::cout << "Drzewo jest puste." << std::endl;
            return;
        }
        inOrderDel(root);
        root = nullptr;
        size = 0;
    }
   
    public:
    int getHeight() {
        return getHeightRecursive(root);
    }
    ~Tree() {
        clear();
    }
};


struct object {
    int a;
    std::string b;
    friend std::ostream& operator<<(std::ostream& os, const object& obj) {
        os << "(" << obj.a << "," << obj.b<<")";
        return os;
    }
    bool operator>(const object& other) {
        return a > other.a;
    }
    bool operator<(const object& other) {
        return a < other.a;
    }
    object(int a,std::string b) : a(a), b(b){}
};



int main()
{
    using namespace std::chrono;

    Tree<object> tree;

    auto start = high_resolution_clock::now();
    for (int i = 0; i < 100000; ++i) {
        tree.append(object(rand()%10000000,"obj"+std::to_string(i)));
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    std::cout << "Czas dodania 100000 elementow: " << duration.count() << " ms\n";
    


    
    start = high_resolution_clock::now();
    for (int i = 0; i < 100000; ++i) {
        Node<object>* node = tree.find(object(i, "obj" + std::to_string(i)));
        if (node) {
            tree.deleteElement(node);
        }
    }
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    std::cout << "Czas usuniecia 100000 elementow: " << duration.count() << " ms\n";
    tree.clear();
    tree.print(tree.root);
  
    return 0;
    
 
    
    
}