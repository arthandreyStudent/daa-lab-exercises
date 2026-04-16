#include <iostream>

using namespace std;

struct node {
    node* parent;
    node* left;
    node* right;
    int elem;

    int heightRec(node* n) {
        if (n == NULL) {
            return -1;
        }
        int lHeight = heightRec(n->left);
        int rHeight = heightRec(n->right);

        return 1 + max(lHeight, rHeight);
    }

    int height() {
        return heightRec(this);
    }
    
};