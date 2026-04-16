#include "binarytree.hpp"
#include <iostream>

#define SPACE 10

using namespace std;

class MyBinaryTree : public BinaryTree {
    private:
        node* root;

        node* createNewNode(int elem) {
            node* newNode = new node();
            newNode->val = elem;
            newNode->left = newNode->right = newNode->parent = nullptr;
            return newNode;
        }

        node* insertRecursive(node* curr, int elem) {
            if (curr == nullptr) return nullptr;

            // Go left
            if (elem < curr->val) {
                if (left(curr) == nullptr) {
                    cout << "Value " << elem << " has been inserted to the LEFT!" << endl;
                    return addLeft(curr, elem);
                }
                return insertRecursive(left(curr), elem);
            
            }
            // Go right
            else if (elem > curr->val) {
                if (right(curr) == nullptr) {
                    cout << "Value " << elem << " has been inserted to the RIGHT!" << endl;
                    return addRight(curr, elem);
                }
                return insertRecursive(right(curr), elem);
            }
            // Duplicate found
            else {
                return nullptr;
            }
        }

        int removeRecursive(node* curr) {
            if (curr == nullptr) return INT_MIN;

            int deletedVal = curr->val;

            // Case 1: Leaf
            if (left(curr) == nullptr && right(curr) == nullptr) {
                if (curr->parent) {
                    if (left(curr->parent) == curr) 
                        curr->parent->left = nullptr;
                    else 
                        curr->parent->right = nullptr;
                } else {
                    root = nullptr;
                }
                delete curr;
                return deletedVal;
            }

            // Case 2: One child
            if (left(curr) && !right(curr)) {
                replaceNode(curr, left(curr));
                return deletedVal;
            } else if (!left(curr) && right(curr)) {
                replaceNode(curr, right(curr));
                return deletedVal;
            }

            // Case 3: Two children
            node* succ = right(curr);
            while (left(succ)) succ = left(succ);
            curr->val = succ->val;
            removeRecursive(succ);

            return deletedVal;
        }

        void replaceNode(node* curr, node* child) {
            if (curr->parent) {
                if (left(curr->parent) == curr)
                    curr->parent->left = child;
                else
                    curr->parent->right = child;
            } else {
                root = child;
            }
            if (child) child->parent = curr->parent;
            delete curr;
        }

        node* findNodeRecursive(node* curr, int elem) {
            if (curr == nullptr) 
                return nullptr;
            if (elem == curr->val) 
                return curr;
            if (elem < curr->val)
                return findNodeRecursive(left(curr), elem);
            else
                return findNodeRecursive(right(curr), elem);
        }

    public:
        MyBinaryTree() {
            root = nullptr;
        }

        node* addRoot(int elem) override {
            if (root != nullptr) {
                cout << "Root already exists!" << endl;
                return root;
            }
            root = createNewNode(elem);
            return root;
        }

        node* getRoot() override {
            return root;
        }

        node* left(node* curr) override {
            if (curr == nullptr) 
                return nullptr;
            return curr->left;
        }

        node* right(node* curr) override {
            if (curr == nullptr) 
                return nullptr;
            return curr->right;
        }

        node* addLeft(node* p, int elem) override {
            if (p == nullptr) 
                return nullptr;
            if (p->left != nullptr) {
                cout << "Left child already exists!" << endl;
                return p->left;
            }
            node* child = createNewNode(elem);
            child->parent = p;
            p->left = child;
            return child;
        }

        node* addRight(node* p, int elem) override {
            if (p == nullptr) 
                return nullptr;
            if (p->right != nullptr) {
                cout << "Right child already exists!" << endl;
                return p->right;
            }
            node* child = createNewNode(elem);
            child->parent = p;
            p->right = child;
            return child;
        }

        bool insert(int elem) {
            if (getRoot() == nullptr) {
                addRoot(elem);
                cout << "Value " << elem << " has been inserted as the ROOT!" << endl;
                return true;
            }
            return insertRecursive(getRoot(), elem) != nullptr;
        }

        bool search(int elem) {
            return findNodeRecursive(getRoot(), elem) != nullptr;
        }

        int remove(node* curr) override {
            return removeRecursive(curr);
        }

        bool removeWithValidation(int elem) {
            node* targetNode = findNodeRecursive(getRoot(), elem);
            if (targetNode == nullptr)
                return false;
            else
                return remove(targetNode) != INT_MIN;
        }
        
        bool isTreeEmpty() {
            return getRoot() == nullptr;
        }

        void printBST2D(node* r, int space) {
            if (r == nullptr) {
                return;
            }
            space += SPACE;
            printBST2D(right(r), space);
            cout << endl;
            for (int i = SPACE; i < space; i++)
                cout << " ";
            cout << r->val << endl;
            printBST2D(left(r), space);
        }

        void preorder(node* r) {
            if (r == nullptr)
                return;

            preorder(left(r));
            cout << r->val << " ";
            preorder(right(r));
        }

        void inorder(node* r) {
            if (r == nullptr)
                return;

            cout << r->val << " ";
            inorder(left(r));
            inorder(right(r));
        }

        void postorder(node* r) {
            if (r == nullptr) {
                return;
            }

            postorder(left(r));
            postorder(right(r));
            cout << r->val << " ";
        }


};