#include "node.hpp"
#include <iostream>

using namespace std;

class RBTree {

    private:
    node* root;
    int size;

    bool isEmpty() {
        return size == 0;
    }

    node* createNode(int e, node* par) {
        node* newNode = new node(e);
        newNode->parent = par;
        return newNode;
    }

    node* addRoot(int e) {
        node* newNode = createNode(e, nullptr);
        newNode->is_red = false;
        root = newNode;
        size++;
        return newNode;
    }

    node* addLeft(int e, node* par) {
        node* newNode = createNode(e, par);
        par->left = newNode;
        size++;
        return newNode;
    }

    node* addRight(int e, node* par) {
        node* newNode = createNode(e, par);
        par->right = newNode;
        size++;
        return newNode;
    }

    node* insert_node(node* n, int e) {
        if (!n) return nullptr;
        if (e == n->element) return nullptr;
        
        if (e > n->element) {
            if (!n->right) return addRight(e, n);
            else return insert_node(n->right, e);
        } else {
            if (!n->left) return addLeft(e, n);
            else return insert_node(n->left, e);
        }
    }

    node* search_node(node* n, int e) {
        if (!n) return nullptr;
        if (e == n->element) return n;

        if (e > n->element) return search_node(n->right, e);
        else return search_node(n->left, e);
    }

    void preorder_helper(node* n) {
        if (!n) return;
        cout << n->element << " (" << (n->is_red ? "R" : "B") << ") ";
        preorder_helper(n->left);
        preorder_helper(n->right);
    }

    void inorder_helper(node* n) {
        if (!n) return;
        inorder_helper(n->left);
        cout << n->element << " (" << (n->is_red ? "R" : "B") << ") ";
        inorder_helper(n->right);
    }

    void postorder_helper(node* n) {
        if (!n) return;
        postorder_helper(n->left);
        postorder_helper(n->right);
        cout << n->element << " (" << (n->is_red ? "R" : "B") << ") ";
    }

    void preorder(node* n) {
        cout << "PREORDER: ";
        preorder_helper(getRoot());
        cout << endl;
    }

    void inorder(node* n) {
        cout << "INORDER: ";
        inorder_helper(getRoot());
        cout << endl;
    }

    void postorder(node* n) {
        cout << "POSTORDER: ";
        postorder_helper(getRoot());
        cout << endl;
    }

    bool check_parent(node* curr, node* par) {
        if (!curr) {
            return true;
        }
        if (curr->parent != par) {
            if (!curr->parent) {
                cout << "Illegal parent of " << curr->element << ": NULL -- must be " << par->element << endl;
            } else if (!par) {
                cout << "Illegal parent of " << curr->element << ": " << curr->parent->element << "must be NULL" << endl;
            } else {
                cout << "Illegal parent of " << curr->element << ": " << curr->parent->element << " -- must be " << par->element << endl;
            }
            return false;
        }
        return check_parent(curr->left, curr) && check_parent(curr->right, curr);
    }

    bool isNodeRed(node* n) {
        return (n ? n->is_red : false);
    }

    node* getSibling(node* n) {
        if (!n || !n->parent) return nullptr;
        node* par = n->parent;
        if (par->left == n) return par->right;
        else return par->left;
    }

    node* getUncle(node* n) {
        if (!n || !n->parent || !n->parent->parent) return nullptr;
        node* par = n->parent;

        return getSibling(par);
    }


    void zigleft(node* curr) {
        if (!curr || !curr->parent) return;

        node* x = curr;
        node* x_lsubtree = x->left;
        node* y = x->parent;
        node* z = y->parent;

        x->left = y;
        y->parent = x;
        y->right = x_lsubtree;
        if (x_lsubtree) x_lsubtree->parent = y;

        if (!z) {
            root = x;
            x->parent = nullptr;
        } else {
            if (z->left == y) z->left = x;
            else z->right = x;

            x->parent = z;  
        }
    }

    void zigright(node* curr) {
        if (!curr || !curr->parent) return;

        node* x = curr;
        node* x_lsubtree = x->right;
        node* y = x->parent;
        node* z = y->parent;

        x->right = y;
        y->parent = x;
        y->left = x_lsubtree;
        if (x_lsubtree) x_lsubtree->parent = y;

        if (!z) {
            root = x;
            x->parent = nullptr;
        } else {
            if (z->left == y) z->left = x;
            else z->right = x;
            
            x->parent = z;  
        }
    }

    void recolor(node* n) {
        if (!n) return;

        node* par = n->parent;
        node* grandpar = par->parent;
        node* uncle = getUncle(n);

        grandpar->is_red = true;
        par->is_red = false;
        if (uncle) uncle->is_red = false;
    }

    node* restructure(node* child) {
        if (!child || !child->parent || !child->parent->parent) return nullptr;

        node* par = child->parent;
        node* grandpar = par->parent;

        bool gtop_right = (grandpar->right == par);
        bool ptoc_right = (par->right == child);

        if (gtop_right && ptoc_right) {
            zigleft(par);
            cout << "ZIGLEFT" << endl;
            return par;
        } else if (!gtop_right && !ptoc_right) {
            zigright(par);
            cout << "ZIGRIGHT" << endl;
            return par;
        } else if (gtop_right && !ptoc_right) {
            zigright(child);
            zigleft(child);
            cout << "ZIGZAGLEFT" << endl;
            return child;
        } else {
            zigleft(child);
            zigright(child);
            cout << "ZIGZAGRIGHT" << endl;
            return child;
        }
    }

    void fixInsert(node* n) {
        while (n != getRoot() && isNodeRed(n->parent)) {
            node* par = n->parent;
            node* grandpar = par ? par->parent : nullptr;

            if (!grandpar) break;

            node* uncle = getUncle(n);

            if (isNodeRed(uncle)) {
                cout << "INSERTION VIOLATION: Case 2" << endl;
                recolor(n);
                n = grandpar;
            } else {
                cout << "INSERTION VIOLATION: Case 1" << endl;
                node* newSubroot = restructure(n);
                if (!newSubroot) break;

                newSubroot->is_red = false;
                if (newSubroot->left) newSubroot->left->is_red = true;
                if (newSubroot->right) newSubroot->right->is_red = true;
                n = grandpar;
            }
        }

        getRoot()->is_red = false;
    }

    node* getSuccessor(node* n) {
        if (!n) return nullptr;
        node* curr = n;
        while (curr->left) {
            curr = curr->left;
        }
        return curr;
    }

    void fixDoubleBlack(node* p, node* par) {
        // p represents the node carrying the double black deficit.
        // It might be nullptr if the deficit is on a leaf path.
        // par is the parent of p.
        
        // Base case: reached the root, deficit is absorbed.
        if (p == getRoot()) return;
        
        // TODO: Implement the 3 cases here!
        // node* sibling = (par && par->left == x) ? par->right : par->left;
        // ...
        node* sibling_y = (par && par->left == p) ? par->right : par->left;

        // Case 1: The Sibling y of p is Black and has a Red Child x
        if (sibling_y && !isNodeRed(sibling_y) && (isNodeRed(sibling_y->left) || isNodeRed(sibling_y->right))) {
            cout << "DELETION VIOLATION: Case 1" << endl;
            node* red_child_x = nullptr;
            bool par_to_sibling_y_left = (par && par->left == sibling_y);

            if (sibling_y) {
                if (par_to_sibling_y_left) {
                    // y is left child: prefer its left child to form a straight line (single rotation)
                    if (isNodeRed(sibling_y->left)) red_child_x = sibling_y->left;
                    else if (isNodeRed(sibling_y->right)) red_child_x = sibling_y->right;
                } else {
                    // y is right child: prefer its right child to form a straight line (single rotation)
                    if (isNodeRed(sibling_y->right)) red_child_x = sibling_y->right;
                    else if (isNodeRed(sibling_y->left)) red_child_x = sibling_y->left;
                }
            }
            
            // Save the original color of the parent before restructuring changes the tree
            bool old_par_red = isNodeRed(par);
            
            node* newSubroot = restructure(red_child_x);
            if (newSubroot) {
                newSubroot->is_red = old_par_red;
                if (newSubroot->left) newSubroot->left->is_red = false;
                if (newSubroot->right) newSubroot->right->is_red = false;
            }
        }

        // Case 2: The Sibling y of p is Black and has both Children Black
        else if (sibling_y && !isNodeRed(sibling_y) && !isNodeRed(sibling_y->left) && !isNodeRed(sibling_y->right)) {
            cout << "DELETION VIOLATION: Case 2" << endl;
            if (par) {
                sibling_y->is_red = true;
                if (isNodeRed(par)) {
                    par->is_red = false;
                } else {
                    fixDoubleBlack(par, par->parent);
                }
            }
        }

        // Case 3: The Sibling y of p is Red
        else if (sibling_y && isNodeRed(sibling_y)) {
            cout << "DELETION VIOLATION: Case 3" << endl;
            if (par) {
                sibling_y->is_red = false;
                par->is_red = true;
                if (par->left == sibling_y) {
                    zigright(sibling_y);
                } else {
                    zigleft(sibling_y);
                }
                // Case 3 denotes a reorientation that turns the sibling black
                // After this adjustment, we RECONSIDER the problem at p
                fixDoubleBlack(p, par);
            }
        }
        
    }

    public:
    RBTree() {
        root = nullptr;
        size = 0;
    }

    node* getRoot() {
        return root;
    }

    bool insert(int e) {
        node* n = getRoot();
        if (!n) {
            return addRoot(e);
        }

        node* inserted = insert_node(n, e);
        if (!inserted) return false;

        fixInsert(inserted);

        return true;
    }

    bool search(int e) {
        node* res = search_node(getRoot(), e);
        return res != nullptr;
    }

    bool remove(int e) {
        node* target = search_node(getRoot(), e);
        
        if (!target) return false;

        // 1. If 2 children, reduce to 1 or 0 children by swapping with successor
        if (target->left && target->right) {
            node* successor = getSuccessor(target->right);
            target->element = successor->element;
            target = successor; // Physically remove the successor instead
        }

        // 2. target now has at most 1 child. Keep references before unlinking.
        node* child = target->left ? target->left : target->right;
        node* par = target->parent;
        bool is_target_red = target->is_red;
        bool target_was_left = (par && par->left == target);

        // 3. Unlink target
        if (child) {
            child->parent = par;
        }
        
        if (!par) {
            root = child;
        } else if (target_was_left) {
            par->left = child;
        } else {
            par->right = child;
        }

        // 4. Safely delete the node
        delete target;
        size--;

        // 5. Rebalance if we removed a black node
        if (!is_target_red) {
            if (isNodeRed(child)) {
                // Simple case: promoted child was red, just color it black
                child->is_red = false;
            } else {
                // Complex case: promoted child is black or null, causes double-black deficit
                fixDoubleBlack(child, par);
            }
        }

        return true;
    }

    void print() {
        cout << "Size: " << (isEmpty() ? "EMPTY" : to_string(size)) << endl;
        preorder(getRoot());
        inorder(getRoot());
        postorder(getRoot());
        cout << "Status: " << check_parent(getRoot(), nullptr) << endl;
    }
};