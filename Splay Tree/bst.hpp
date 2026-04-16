// DO NOT modify this file.
// Go to mybinarytree's zigleft and zigright methods.

#include "mybinarytree.hpp"

class BST {
	BinaryTree* tree = new MyBinaryTree();

    void splay(node* n) {
        while (n->parent) {
            restructure(n);
        }
    }

    node* search_node_rtrn_node_rec(node* n, int num) {
        if (n == NULL || n->elem == num) {
            return n;
        }

        if (num < n->elem) {
            return search_node_rtrn_node_rec(n->left, num);
        } else {
            return search_node_rtrn_node_rec(n->right, num);
        }
    }

    node* search_node_rtrn_node(node* n, int num) {
        return search_node_rtrn_node_rec(tree->getRoot(), num);
    }

    node* minNode(node* n) {
        node* curr = n;

        while (curr->left) {
            curr = curr->left;
        }
        return curr;
    }

	public:
    bool search(int num) {
        node* last_accessed = NULL;
        return search_node(tree->getRoot(), num, last_accessed);
    }

	bool search_node(node* n, int num, node*& last_accessed) {
		if (n == NULL) {
            if (last_accessed) {
                cout << "SPLAYING..." << endl;
                splay(last_accessed);
            }
			return false;
		}

        last_accessed = n;

		if (n->elem == num) {
            cout << "SPLAYING..." << endl;
            splay(n);
			return true;
		}
		if (num > n->elem) {
			// proceed to right
			return search_node(n->right, num, last_accessed);
		} else {
			return search_node(n->left, num, last_accessed);
		}
	}

    int getBalanceFactor(node* n) {
        if (n == NULL) {
            return 0;
        }
        return (n->left->height() - n->right->height());
    }

    // TODO perform post-processing by splaying from the recently accessed node after insertion, deletion, or searching until the root
	node* insert(int num) {
		node* n = tree->getRoot();
        node* targetNode;
        node* last_accessed = NULL;
        node* res;
		if (n == NULL) {
			targetNode = tree->addRoot(num);
            res = targetNode;
		} else {
		    targetNode = insert_node(n, num, last_accessed);
            res = targetNode;
        }

        if (targetNode) {
            cout << "SPLAYING..." << endl;
            splay(targetNode);
        } else {
            if (last_accessed) {
                cout << "SPLAYING..." << endl;
                splay(last_accessed);
            }
        }

        return res;
	}

	node* insert_node(node* n, int num, node*& last_accessed) {
		if (n == NULL) {
			return NULL;
		}

        last_accessed = n;

		if (n->elem == num) {
			return NULL;
		}

		if (num > n->elem) {
			if (!n->right) {
				return tree->addRight(n, num);
			} else {
				return insert_node(n->right, num, last_accessed);
			}
		} else {
			if (!n->left) {
				return tree->addLeft(n, num);
			} else {
				return insert_node(n->left, num, last_accessed);
			}
		}
	}

    // TODO perform post-processing by splaying from the recently accessed node after insertion, deletion, or searching until the root
    bool remove(int num) {
        node* last_accessed = NULL;
        return remove_node(tree->getRoot(), num, last_accessed);
    }

	bool remove_node(node* n, int num, node*& last_accessed) {
		if (n == NULL) {
            if (last_accessed) {
                cout << "SPLAYING..." << endl;
                splay(last_accessed);
            }
			return false;
		}

        last_accessed = n;

		if (n->elem == num) {
            cout << "SPLAYING..." << endl;
            splay(n);

            if (n->left && n->right) {
                node* l_subtree = n->left;
                node* r_subtree = n->right;

                n->left = NULL;
                n->right = NULL;

                l_subtree->parent = NULL;
                r_subtree->parent = NULL;

                delete n;

                tree->setRoot(r_subtree);

                node* successor = minNode(r_subtree);

                cout << "SPLAYING..." << endl;
                splay(successor);

                node* newRoot = tree->getRoot();
                newRoot->left = l_subtree;
                if (l_subtree) l_subtree->parent = newRoot;
            } else {
                tree->remove(n);
            }
            return true;
		}
		if (num > n->elem) {
			return remove_node(n->right, num, last_accessed);
		} else {
			return remove_node(n->left, num, last_accessed);
		}
	}

    bool restructure(node* child) {
        
        node* par; // parent
        //TODO find parent (y)
        par = child->parent;

        if (!par) return false;

        // This is an indicator of the placement of parent to child (ptoc)
        bool ptoc_right = false;
        if (par->right == child) {
            ptoc_right = true;
        }

        node* gp;
        // TODO find grandparent (z)
        gp = par->parent;

        // This is an indicator of the placement of grandparent to parent (gtop)
        bool gtop_right = false;
        if (gp && gp->right == par) {
            gtop_right = true;
        }

        // FOR THE FOLLOWING: Write in each of the if statements a console output
        // on its corresponding operation (ZIGZIGLEFT, ZIGZIGRIGHT, ZIGZAGLEFT, ZIGZAGRIGHT, ZIGLEFT, or ZIGRIGHT)
        
        // z
        //  \ 
        //   y
        //    \ 
        //     x
        if (gp && gtop_right && ptoc_right) {
            zigleft(par);
            zigleft(child);
            cout << "ZIGZIGLEFT" << endl;
        }

        //     z
        //    /
        //   y
        //  /
        // x

        else if (gp && !gtop_right && !ptoc_right) {
            zigright(par);
            zigright(child);
            cout << "ZIGZIGRIGHT" << endl;
        }

        //  z
        //   \ 
        //    y
        //   /
        //  x

        else if (gp && gtop_right && !ptoc_right) {
            zigright(child);
            zigleft(child);
            cout << "ZIGZAGLEFT" << endl;
        }

        //      z
        //     /
        //    y
        //     \ 
        //      x

        else if (gp && !gtop_right && ptoc_right) {
            zigleft(child);
            zigright(child);
            cout << "ZIGZAGRIGHT" << endl;
        }

        else if (!gp && ptoc_right) {
            zigleft(child);
            cout << "ZIGLEFT" << endl;
        }

        else {
            zigright(child);
            cout << "ZIGRIGHT" << endl;
        }

        return true;
    }

    void zigleft(node* curr) {
        tree->zigleft(curr);
    }

    void zigright(node* curr) {
        tree->zigright(curr);
    }

	void print() {
		tree->print();
	}
};