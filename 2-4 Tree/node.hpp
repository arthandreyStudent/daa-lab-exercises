#include <iostream>

using namespace std;

struct node {

    node* parent;
    int keys[4];
    node** children;
    int size;

    node() : parent(nullptr), children(new node*[5]), size(0) {
        for (int i = 0; i < 5; i++) children[i] = nullptr;
    }

    node(int key, node* par) : parent(par), children(new node*[5]) {
        for (int i = 0; i < 5; i++) children[i] = nullptr;
        keys[0] = key;
        size = 1;
    }

    node(int key) : parent(nullptr), children(new node*[5]) {
        for (int i = 0; i < 5; i++) children[i] = nullptr;
        keys[0] = key;
        size = 1;
    }

    bool isFull() {
        return size == 4;
    }

    void insertKeysAt(int key, int idx) {
        int i;
        for (i = size; i > idx; i--) {
            keys[i] = keys[i - 1];
        }
        keys[i] = key;
        size++;
    }

    bool contains(int key) {
        for (int i = 0; i < size; i++) {
            if (keys[i] == key) return true;
        }
        return false;
    }

    void printKeys() {
        cout << "[";
        for (int i = 0; i < size; i++) {
            cout << keys[i];
            if (i == size - 1) {
                cout << "";
            } else {
                cout << " ";
            }
        }
        cout << "]";
    }

};