#include "node.hpp"

class BinaryTree {
    public:
        virtual node* getRoot() = 0;

        virtual node* left(node* curr) = 0;
        virtual node* right(node* curr) = 0;

        virtual node* addRoot(int elem) = 0;
        virtual node* addLeft(node* p, int elem) = 0;
        virtual node* addRight(node* p, int elem) = 0;

        virtual int remove(node* curr) = 0;


};