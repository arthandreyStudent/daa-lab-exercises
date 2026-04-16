#include "mybinarytree.hpp"
#include <iostream>
#include <conio.h>

using namespace std;

int main(void) {
    int op;
    int val;
    bool status;
    MyBinaryTree* myBST = new MyBinaryTree();

    do {
        cout << "\nSelect option number below. Enter 0 to exit." << endl;
        cout << "1. Insert Node" << endl;
        cout << "2. Search Node" << endl;
        cout << "3. Delete Node" << endl;
        cout << "4. Print BST" << endl;
        cout << "5. Traverse BST" << endl;
        cout << "6. Clear Screen" << endl;
        cout << "0. Exit Program" << endl;

        cout << "> ";
        cin >> op;

        switch(op) {
            case 0: {
                cout << "Exiting..." << endl;
                break;
            }
            case 1: {
                cout << "INSERT NODE SELECTED..." << endl;
                cout << "Enter value to insert: ";
                cin >> val;
                status = myBST->insert(val);
                if (!status)
                    cout << "Value " << val << " already exists!" << endl;
                // Insert node code here
                break;
            }
            case 2: {
                cout << "SEARCH NODE SELECTED..." << endl;
                cout << "Enter value to search: ";
                cin >> val;
                status = myBST->search(val);
                cout << "Is there " << val << "? " << (status ? "YES" : "NO") << endl;
                // Search node code here
                break;
            }
            case 3: {
                cout << "DELETE NODE SELECTED..." << endl;
                cout << "Enter value to delete: ";
                cin >> val;
                status = myBST->removeWithValidation(val);
                cout << "Value " << val << " was " << (status ? "" : "NOT ") << "removed successfully" << endl;
                // Delete node code here
                break;
            }
            case 4: {
                cout << "PRINT BST SELECTED..." << endl;
                node* root = myBST->getRoot();
                if (myBST->isTreeEmpty()) {
                    cout << "BST is currently EMPTY!" << endl;
                    break;
                }
                myBST->printBST2D(root, 4);
                // Print BST code here
                break;
            }
            case 5: {
                cout << "TRAVERSE BST SELECTED..." << endl;
                int opBST;

                cout << "Depth-First Search (DFS)" << endl;
                cout << "Select the type of traversal below." << endl;
                cout << "1. Pre-order Traversal" << endl;
                cout << "2. In-order Traversal" << endl;
                cout << "3. Post-order Traversal" << endl;
                
                myBST->printBST2D(myBST->getRoot(), 4);

                cout << "\n> ";
                cin >> opBST;

                switch (opBST) {
                    case 1: {
                        cout << "PRE-ORDER TRAVERSAL SELECTED..." << endl;
                        node* root = myBST->getRoot();
                        myBST->preorder(root);
                        cout << endl;
                        break;
                    }
                    case 2: {
                        cout << "IN-ORDER TRAVERSAL SELECTED..." << endl;
                        node* root = myBST->getRoot();
                        myBST->inorder(root);
                        cout << endl;
                        break;
                    }
                    case 3: {
                        cout << "POST-ORDER TRAVERSAL SELECTED..." << endl;
                        node* root = myBST->getRoot();
                        myBST->postorder(root);
                        cout << endl;
                        break;
                    }
                    default: {
                        cout << "Invalid traversal type." << endl;
                        break;
                    }
                }
                // Traverse BST code here
                break;
            }
            case 6: {
                system("cls");
                break;
            }
            default: {
                cout << "Invalid option number. Try again." << endl;
            }
        }

        cout << "\nPress any key to continue...> ";
        _getch();
        system("cls");

    } while (op != 0);

    cout << endl;

    return 0;
}