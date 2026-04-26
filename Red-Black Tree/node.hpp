struct node {
    node* parent;
    node* left;
    node* right;
    int element;
    bool is_red;

    node(int e = 0) : parent(nullptr), left(nullptr), right(nullptr), element(e), is_red(true) {}

};