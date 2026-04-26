#include "rbtree.hpp"
#include <iostream>

using namespace std;

int main() {
    RBTree* rbtree = new RBTree();
    char op;
    int num;
    do {
        cout << "Op: ";
        cin >> op;
        node* n;
        switch (op) {
            case 'i':
                cin >> num;
                if (rbtree->insert(num)) cout << "INSERTED " << num << endl;
                else cout << "DUPLICATE " << num << endl;
                break;
            case 's':
                cin >> num;
                if (rbtree->search(num)) cout << "FOUND " << num << endl;
                else cout << "NOT FOUND " << num << endl;
                break;
            case 'd':
                cin >> num;
                if (rbtree->remove(num)) cout << "DELETED " << num << endl;
                else cout << "NOT FOUND " << num << endl;
                break;
            case 'p':
                rbtree->print();
                break;
            case 'x':
                cout << "Exiting";
                break;
            default:
                cout << "Invalid operation";
        }
    } while (op != 'x');
};