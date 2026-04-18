#include <iostream>
#include "node.hpp"
#include <queue>

using namespace std;

class Tree24 {

    private:
    node* root;

    node* addRoot(int key) {
        node* newNode = new node(key, nullptr);
        return newNode;
    }

    void shiftChildrenRight(node* n, int start) {
        for (int i = n->size; i >= start + 1; i--) {
            n->children[i] = n->children[i - 1];
        }
    }

    void splitNode(node* n, node*& last_accessed_node) {
        node* par = n->parent;
        node* w_prime = new node();
        node* w_prime2 = new node();

        w_prime->insertKeysAt(n->keys[0], 0);
        w_prime->insertKeysAt(n->keys[1], 1);

        for (int i = 0; i < 3; i++) {
            w_prime->children[i] = n->children[i];
            if (n->children[i] != nullptr) {
                n->children[i]->parent = w_prime;
            }
        }

        w_prime2->insertKeysAt(n->keys[3], 0);

        for (int i = 3, j = 0; i < 5; i++, j++) {
            w_prime2->children[j] = n->children[i];
            if (n->children[i] != nullptr) {
                n->children[i]->parent = w_prime2;
            }
        }

        if (par == nullptr) {
            node* u = new node(n->keys[2], nullptr);
            u->children[0] = w_prime;
            u->children[1] = w_prime2;
            w_prime->parent = u;
            w_prime2->parent = u;
            root = u;
            last_accessed_node = u;
        } else {
            int insert_index = findInsertionIndex(par, n->keys[2]);
            par->insertKeysAt(n->keys[2], insert_index);
            //
            shiftChildrenRight(par, insert_index);

            par->children[insert_index] = w_prime;
            par->children[insert_index + 1] = w_prime2;
            w_prime->parent = par;
            w_prime2->parent = par;
            last_accessed_node = par;
        }
        delete n;
    }

    int findInsertionIndex(node* n, int key) {
        int i;
        for (i = n->size - 1; i >= 0; i--) {
            if (key == n->keys[i]) return -1;
            if (key > n->keys[i]) break;
        }
        return i + 1;
    }

    int findKeyIndex(node* n, int key) {
        for (int i = 0; i < n->size; i++) {
            if (n->keys[i] == key) return i;
        }
        return -1;
    }
    
    int getChildIndex(node* parent, node* child) {
        for (int i = 0; i <= parent->size; i++) {
            if (parent->children[i] == child) return i;
        }
        return -1;
    }

    node* getSuccessor(node* n, int idx) {
        node* curr = n->children[idx + 1];
        while (curr->children[0] != nullptr) {
            curr = curr->children[0];
        }
        return curr;
    }

    void borrowFromLeft(node* parent, int i) {
        node* child = parent->children[i];
        node* left = parent->children[i - 1];

        for (int j = child->size; j > 0; j--) {
            child->keys[j] = child->keys[j - 1];
        }

        child->keys[0] = parent->keys[i - 1];
        child->size++;

        if (left->children[left->size] != nullptr) {
            for (int j = child->size; j > 0; j--) {
                child->children[j] = child->children[j - 1];
            }
            child->children[0] = left->children[left->size];
            if (child->children[0]) child->children[0]->parent = child;
        }

        parent->keys[i - 1] = left->keys[left->size - 1];
        left->size--;
    }

    void borrowFromRight(node* parent, int i) {
        node* child = parent->children[i];
        node* right = parent->children[i + 1];

        child->keys[child->size++] = parent->keys[i];

        if (right->children[0] != nullptr) {
            child->children[child->size] = right->children[0];
            if (child->children[child->size])
                child->children[child->size]->parent = child;
        }

        parent->keys[i] = right->keys[0];

        for (int j = 0; j < right->size - 1; j++) {
            right->keys[j] = right->keys[j + 1];
        }

        for (int j = 0; j < right->size; j++) {
            right->children[j] = right->children[j + 1];
        }

        right->size--;
    }

    void mergeWithLeft(node* parent, int i) {
        node* child = parent->children[i];
        node* left = parent->children[i - 1];

        left->keys[left->size++] = parent->keys[i - 1];

        for (int j = 0; j < child->size; j++) {
            left->keys[left->size++] = child->keys[j];
        }

        int base = left->size - child->size;
        for (int j = 0; j <= child->size; j++) {
            left->children[base + j] = child->children[j];
            if (child->children[j])
                child->children[j]->parent = left;
        }

        for (int j = i - 1; j < parent->size - 1; j++) {
            parent->keys[j] = parent->keys[j + 1];
        }

        for (int j = i; j < parent->size; j++) {
            parent->children[j] = parent->children[j + 1];
        }

        parent->size--;
        delete child;
    }

    void mergeWithRight(node* parent, int i) {
        node* child = parent->children[i];
        node* right = parent->children[i + 1];

        child->keys[child->size++] = parent->keys[i];

        for (int j = 0; j < right->size; j++) {
            child->keys[child->size++] = right->keys[j];
        }

        int base = child->size - right->size;
        for (int j = 0; j <= right->size; j++) {
            child->children[base + j] = right->children[j];
            if (right->children[j])
                right->children[j]->parent = child;
        }

        for (int j = i; j < parent->size - 1; j++) {
            parent->keys[j] = parent->keys[j + 1];
        }

        for (int j = i + 1; j < parent->size; j++) {
            parent->children[j] = parent->children[j + 1];
        }

        parent->size--;
        delete right;
    }

    void fixUnderflow(node* n) {
        node* parent = n->parent;
        int i = getChildIndex(parent, n);

        node* left = (i > 0) ? parent->children[i - 1] : nullptr;
        node* right = (i < parent->size) ? parent->children[i + 1] : nullptr;

        if (left && left->size > 1) {
            borrowFromLeft(parent, i);
        } else if (right && right->size > 1) {
            borrowFromRight(parent, i);
        } else {
            if (left) mergeWithLeft(parent, i);
            else mergeWithRight(parent, i);
        }
    }

    void fixRoot() {
        if (root && root->size == 0) {
            node* old = root;
            root = root->children[0];
            if (root) root->parent = nullptr;
            delete old;
        }
    }

    bool isEmpty() {
        return root == nullptr; 
    }

    void printBFS(node* n) {
        if (n == nullptr) return;

        queue<node*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();

            for (int i = 0; i < levelSize; i++) {
                node* curr = q.front();
                q.pop();

                for (int j = 0; j <= curr->size; j++) {
                    if (curr->children[j] != nullptr) {
                        cout << "Child " << j + 1 << " of ";
                        curr->printKeys();
                        cout << ": ";
                        curr->children[j]->printKeys();
                        cout << endl;

                        q.push(curr->children[j]);
                    }
                }
            }
            cout << endl;
        }
    }

    public:
    Tree24() {
        root = nullptr;
    }

    bool insert(int key) {
        if (root == nullptr) {
            root = addRoot(key);
            return true;
        }

        node* curr = root;
        node* last_node = curr;
        int insert_idx;

        while (curr != nullptr) {
            insert_idx = findInsertionIndex(curr, key);

            if (insert_idx == -1) return false;

            last_node = curr;
            curr = curr->children[insert_idx];
        }

        last_node->insertKeysAt(key, insert_idx);
        node* last_accessed_node = nullptr;

        while (last_node->size == 4) {
            splitNode(last_node, last_accessed_node);
            last_node = last_accessed_node;
        }

        return true;
    }

    bool remove(int key) {
        node* curr = root;
        int idx;

        while (curr != nullptr) {
            idx = findKeyIndex(curr, key);

            if (idx != -1) break;

            int next = findInsertionIndex(curr, key);
            curr = curr->children[next];
        }

        if (curr == nullptr) return false;

        if (curr->children[0] != nullptr) {
            node* succ = getSuccessor(curr, idx);
            curr->keys[idx] = succ->keys[0];
            curr = succ;
            idx = 0;
        }

        for (int i = idx; i < curr->size - 1; i++) {
            curr->keys[i] = curr->keys[i + 1];
        }
        curr->size--;

        while (curr != root && curr->size == 0) {
            node* parent = curr->parent;
            fixUnderflow(curr);
            curr = parent;
        }

        fixRoot();
        return true;
    }

    void print() {
        if (isEmpty()) {
            cout << "\nTree is EMPTY." << endl << endl;
            return;
        }
        
        cout << "\nRoot: ";
        root->printKeys();
        cout << endl << endl;

        printBFS(root);
    }


};