#include "tree24.hpp"
#include <iostream>

using namespace std;

int main() {
    Tree24* tree24 = new Tree24();
    node* nodes[100];
    char op;
    int num;
    
    do {
        cout << "Op: ";
        cin >> op;
        switch (op) {
            bool status;
            case 'i': {
                cin >> num;
                status = tree24->insert(num);
                cout << "Status: ";
                if (status) {
                    cout << "1";
                } else {
                    cout << "0";
                }
                cout << endl;
                break;
            }
            case 'r': {
                cin >> num;
                status = tree24->remove(num);
                cout << "Status: ";
                if (status) {
                    cout << "1";
                } else {
                    cout << "0";
                }
                cout << endl;
                break;
            }
            case 'p':
                tree24->print();
                break;
            case 'x':
                cout << "Exiting";
                break;
            default:
                cout << "Invalid operation";
        }
    } while (op != 'x');
};