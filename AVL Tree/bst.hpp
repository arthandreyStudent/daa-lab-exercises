// DO NOT modify this file.
// Go to mybinarytree's zigleft and zigright methods.

#include "mybinarytree.hpp"

class BST {
	BinaryTree* tree = new MyBinaryTree();

	public:
	bool search(int num) {
		return search_node(tree->getRoot(), num);
	}

	bool search_node(node* n, int num) {
		if (n == NULL) {
			return false;
		}
		if (n->elem == num) {
			return true;
		}
		if (num > n->elem) {
			// proceed to right
			return search_node(n->right, num);
		} else {
			return search_node(n->left, num);
		}
	}

    int getBalanceFactor(node* n) {
        if (n == NULL) {
            return 0;
        }
        return (n->left->height() - n->right->height());
    }

    // TODO perform post-processing by checking for violation after insertion
    // from the node inserted (or from its parent) until the root
	node* insert(int num) {
		node* n = tree->getRoot();
        node* targetNode;
        node* res;
		if (n == NULL) {
			targetNode = tree->addRoot(num);
            res = targetNode;
		} else {
		    targetNode = insert_node(n, num);
            res = targetNode;
            targetNode = targetNode->parent ? targetNode->parent : NULL;
        }

        while (targetNode) {
            if (getBalanceFactor(targetNode) < -1 || getBalanceFactor(targetNode) > 1) {
                restructure(targetNode);
            }
            targetNode = targetNode->parent;
        }

        return res;
	}

	node* insert_node(node* n, int num) {
		if (n == NULL) {
			return NULL;
		}
		if (n->elem == num) {
			return NULL;
		}
		if (num > n->elem) {
			if (!n->right) {
				return tree->addRight(n, num);
			} else {
				return insert_node(n->right, num);
			}
		} else {
			if (!n->left) {
				return tree->addLeft(n, num);
			} else {
				return insert_node(n->left, num);
			}
		}
	}

    // TODO perform post-processing by checking for violation after deletion
    // from the parent of the node removed until the root
    bool remove(int num) {
        node* removedNode = NULL;
        bool status = remove_node(tree->getRoot(), num, removedNode);

        if (removedNode) {
            node* targetNode = removedNode->parent ? removedNode->parent : NULL;

            while (targetNode) {
                if (getBalanceFactor(targetNode) < -1 || getBalanceFactor(targetNode) > 1) {
                    restructure(targetNode);
                }
                targetNode = targetNode->parent;
            }
        }
        return status;
    }

	bool remove_node(node* n, int num, node*& removedNode) {
		if (n == NULL) {
			return false;
		}
		if (n->elem == num) {
            if (n->left && n->right) {
                node* r = n->right;
                while (r->left) {
                    r = r->left;
                }
                removedNode = r;
                int rem = tree->remove(r);
                n->elem = rem;
            } else {
                removedNode = n;
    			tree->remove(n);
            }
            return true;
		}
		if (num > n->elem) {
			return remove_node(n->right, num, removedNode);
		} else {
			return remove_node(n->left, num, removedNode);
		}
	}

    // GIVEN the grandparent (or z), find the parent (or y), and the child (or x).
    bool restructure(node* gp) {
        
        node* par; // parent
        // TODO find parent
        if (gp->left->height() > gp->right->height()) {
            par = gp->left;
        } else {
            par = gp->right;
        }
        
        // This is an indicator of the placement of grandparent to parent (gtop)
        bool gtop_right = false;
        if (gp->right == par) {
            gtop_right = true;
        }

        node* child;
        // TODO find child
        if (par->left && par->right) {
            int leftHeight = par->left->height();
            int rightHeight = par->right->height();

            if (leftHeight > rightHeight) {
                child = par->left;
            } else if (leftHeight < rightHeight) {
                child = par->right;
            } else {
                child = gtop_right ? par->right : par->left;
            }
        } else {
            child = par->left ? par->left : par->right;
        }
        
        // This is an indicator of the placement of parent to child (ptoc)
        bool ptoc_right = false;
        if (par->right == child) {
            ptoc_right = true;
        }

        // FOR THE FOLLOWING: Write in each of the if statements a console output
        // on its corresponding operation (ZIGLEFT, ZIGRIGHT, ZIGZAGLEFT, or ZIGZAGRIGHT)

        // z
        //  \ 
        //   y
        //    \ 
        //     x
        if (gtop_right && ptoc_right) {
            // TODO call to either zigleft or zigright or both
            zigleft(par);
            cout << "ZIGLEFT" << endl;
        }

        //  z
        //   \ 
        //    y
        //   /
        //  x
        else if (gtop_right && !ptoc_right) {
            // TODO call to either zigleft or zigright or both
            zigright(child);
            zigleft(child);
            cout << "ZIGZAGLEFT" << endl;
        }

        //     z
        //    /
        //   y
        //  /
        // x
        else if (!gtop_right && !ptoc_right) {
            // TODO call to either zigleft or zigright or both
            zigright(par);
            cout << "ZIGRIGHT" << endl;
        }

        //      z
        //     /
        //    y
        //     \ 
        //      x
        else {
            // TODO call to either zigleft or zigright or both
            zigleft(child);
            zigright(child);
            cout << "ZIGZAGRIGHT" << endl;
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