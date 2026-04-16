#include <cstdlib>
#include <iostream>
#include "binarytree.hpp"
using namespace std;

class MyBinaryTree : public BinaryTree {

	node* root;
	int size;

	node* create_node(int e, node* parent) {
		node* n = (node*) calloc( 1, sizeof(node) );
		n->elem = e;
		n->parent = parent;
		return n;
	}

	public:
    
    MyBinaryTree() {
        root = NULL;
        size = 0;
    }

	node* addRoot(int e) {
		if (root) {
			cout << "Root exists" << endl;
			return NULL;
		}
		node* n = create_node(e, NULL);
		root = n;
		size++;
		return n;
	}

	node* left(node* p) {
		return p->left;
	}

	node* right(node* p) {
		return p->right;
	}

	node* sibling(node* n) {
		node* par = n->parent;
		if (!par) {
			return NULL;
		}
		if (n == par->left) {
			return par->right;
		}
		return par->left;
	}

	node* addLeft(node* p, int e) {
		if (p->left) {
			cout << "Left of " << p->elem << " already exists" << endl;
			return NULL;
		}
		node* n = create_node(e, p);
		p->left = n;
		size++;
		return n;
	}

	node* addRight(node* p, int e) {
		if (p->right) {
			cout << "Right of " << p->elem << " already exists" << endl;
			return NULL;
		}
		node* n = create_node(e, p);
		p->right = n;
		size++;
		return n;
	}

    int remove(node* n) {
        int res = n->elem;
        if (left(n) && right(n)) {
            return -1;
        }
        if (!left(n) && !right(n)) {
            if (n->parent) {
                node* par = n->parent;
                if (left(par) == n) {
                    par->left = NULL;
                } else {
                    par->right = NULL;
                }
            } else {
                root = NULL;
            }
        } else {
            node* child;
            if (left(n)) {
                child = left(n);
            } else {
                child = right(n);
            }
            if (n->parent) {
                node* par = n->parent;
                if (left(par) == n) {
                    par->left = child;
                } else {
                    par->right = child;
                }
                if (child) child->parent = par;
            } else {
                root = child;
                child->parent = NULL;
            }
        }
        n->left = n->right = n->parent = NULL;
        size--;
        free(n);
        return res;
    }

	node* getRoot() {
		return root;
	}

    void setRoot(node* n) {
        root = n;
    }

    // TODO implement zigleft
    // params: curr - the right child that will be rotated with its parent
    // after which, curr shall be above its parent
    //  |
    //  y
    //   \
    //    x <- curr
    void zigleft(node* curr) {
        if (!curr) return;
        if (!curr->parent) return;

        if (curr != curr->parent->right) {
            cout << "Current node is not a right child of its parent: " << curr->parent->elem << endl;
            cout << "UNABLE TO PERFORM ZIGLEFT" << endl;
            return;
        }

        node* x = curr;
        node* y = curr->parent;
        node* z = y->parent;
        node* x_subtree = x->left;

        if (root == y) {
            x->left = y;
            y->parent = x;
            y->right = x_subtree;

            if (x_subtree) x_subtree->parent = y;

            root = x;
            x->parent = NULL;
        } else {
            if (z->left == y) {
                x->left = y;
                y->parent = x;
                y->right = x_subtree;

                if (x_subtree) x_subtree->parent = y;

                z->left = x;
                x->parent = z;
            } else {
                x->left = y;
                y->parent = x;
                y->right = x_subtree;

                if (x_subtree) x_subtree->parent = y;

                z->right = x;
                x->parent = z;
            }
        }
    }

    // TODO implement zigright
    // params: curr - the left child that will be rotated with its parent
    // after which, curr shall be above its parent
    //   |
    //   y
    //  /
    // x <- curr
    void zigright(node* curr) {
        if (!curr) return;
        if (!curr->parent) return;

        if (curr != curr->parent->left) {
            cout << "Current node is not a left child of its parent: " << curr->parent->elem << endl;
            cout << "UNABLE TO PERFORM ZIGRIGHT" << endl;
            return;
        }

        node* x = curr;
        node* y = curr->parent;
        node* z = y->parent;
        node* x_subtree = x->right;

        if (root == y) {
            x->right = y;
            y->parent = x;
            y->left = x_subtree;

            if (x_subtree) x_subtree->parent = y;

            root = x;
            x->parent = NULL;
        } else {
            if (z->left == y) {
                x->right = y;
                y->parent = x;
                y->left = x_subtree;

                if (x_subtree) x_subtree->parent = y;

                z->left = x;
                x->parent = z;
            } else {
                x->right = y;
                y->parent = x;
                y->left = x_subtree;

                if (x_subtree) x_subtree->parent = y;

                z->right = x;
                x->parent = z;
            }
        }
    }

	void print() {
		cout << "Size: " << size << endl;
		if (!root) {
			cout << "EMPTY" << endl;
			return;
		}
		node* curr = root;
		print_node("", root, false);
        cout << "Status: " << check_parent(root, NULL) << endl;
	}

	void print_node(string prefix, node* n, bool isLeft) {
		cout << prefix;
        cout << (isLeft ? "+--L: " : "+--R: " );
        cout << n->elem << endl;
		if (n->left) {
			print_node(prefix + "|   ", n->left, true);
		}
		if (n->right) {
			print_node(prefix + "|   ", n->right, false);
		}
	}

    bool check_parent(node* curr, node* par) {
        if (!curr) {
            return true;
        }
        if (curr->parent != par) {
            if (!curr->parent) {
                cout << "Illegal parent of " << curr->elem << ": NULL -- must be " << par->elem << endl;
            } else if (!par) {
                cout << "Illegal parent of " << curr->elem << ": " << curr->parent->elem << " -- must be NULL" << endl;
            } else {
                cout << "Illegal parent of " << curr->elem << ": " << curr->parent->elem << " -- must be " << par->elem << endl;
            }
            return false;
        }
        return check_parent(curr->left, curr) && check_parent(curr->right, curr);
    }

};