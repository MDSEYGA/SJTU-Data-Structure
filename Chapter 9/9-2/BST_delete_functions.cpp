#include <iostream>
using namespace std;

template <class Type>
class BinarySearchTree {
private:
    struct BinaryNode {
        Type data;
        BinaryNode* left;
        BinaryNode* right;
        BinaryNode(const Type& thedata, BinaryNode* lt = nullptr, BinaryNode* rt = nullptr) : data(thedata), left(lt), right(rt) {}
    };
    BinaryNode* root;

public:
    BinarySearchTree();
    ~BinarySearchTree();
    Type* find(const Type& x) const;
    void insert(const Type& x);
    void remove(const Type& x);

private:
    void insert(const Type& x, BinaryNode*& t);
    void remove(const Type& x, BinaryNode*& t);
    Type* find(const Type& x, BinaryNode* t) const;
    void makeEmpty(BinaryNode*& t);
    void display(BinaryNode* t) const;

public:
    void delete_less(const Type& x);
    void delete_greater(const Type& x);
    void delete_between(const Type& x, const Type& y);
    void display() const;

private:
    void delete_less(const Type& x, BinaryNode*& t);
    void delete_greater(const Type& x, BinaryNode*& t);
    void delete_between(const Type& x, const Type& y, BinaryNode*& t);
};

template <class Type>
Type* BinarySearchTree<Type>::find(const Type& x) const {
    return find(x, root);
}

template <class Type>
Type* BinarySearchTree<Type>::find(const Type& x, BinaryNode* t) const {
    if (t == nullptr || t->data == x) {
        return (Type*)t;
    }
    if (x < t->data) {
        return find(x, t->left);
    } else {
        return find(x, t->right);
    }
}

template <class Type>
void BinarySearchTree<Type>::insert(const Type& x) {
    insert(x, root);
}

template <class Type>
void BinarySearchTree<Type>::insert(const Type& x, BinaryNode*& t) {
    if (t == nullptr) {
        t = new BinaryNode(x, nullptr, nullptr);
    } else if (x < t->data) {
        insert(x, t->left);
    } else if (t->data < x) {
        insert(x, t->right);
    }
}

template <class Type>
void BinarySearchTree<Type>::remove(const Type& x) {
    remove(x, root);
}

template <class Type>
void BinarySearchTree<Type>::remove(const Type& x, BinaryNode*& t) {
    if (t == nullptr) return;
    if (x < t->data) {
        remove(x, t->left);
    } else if (t->data < x) {
        remove(x, t->right);
    } else if (t->left != nullptr && t->right != nullptr) {
        BinaryNode* tmp = t->right;
        while (tmp->left != nullptr) {
            tmp = tmp->left;
        }
        t->data = tmp->data;
        remove(t->data, t->right);
    } else {
        BinaryNode* oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
    }
}

template <class Type>
BinarySearchTree<Type>::BinarySearchTree() {
    root = nullptr;
}

template <class Type>
void BinarySearchTree<Type>::makeEmpty(BinaryNode*& t) {
    if (t == nullptr) return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}

template <class Type>
BinarySearchTree<Type>::~BinarySearchTree() {
    makeEmpty(root);
}

template <class Type>
void BinarySearchTree<Type>::display() const {
    display(root);
}

template <class Type>
void BinarySearchTree<Type>::display(BinaryNode* t) const {
    if (t != nullptr) {
        display(t->left);
        cout << t->data << " ";
        display(t->right);
    }
}

template <class Type>
void BinarySearchTree<Type>::delete_less(const Type& x) {
    delete_less(x, root);
}

// Recursively delete all nodes with data less than x
template <class Type>
void BinarySearchTree<Type>::delete_less(const Type& x, BinaryNode*& t) {
    if (t != nullptr) {
        // If the current node's data is less than x, remove this node and its left subtree
        if (x > t->data) {
            BinaryNode* tmp = t;
            t = t->right;
            makeEmpty(tmp->left);
            delete tmp;
            // Continue checking the new current node (the right subtree)
            delete_less(x, t);
        } else {
            // Continue checking the left subtree
            delete_less(x, t->left);
        }
    }
}

template <class Type>
void BinarySearchTree<Type>::delete_greater(const Type& x) {
    delete_greater(x, root);
}

// Recursively delete all nodes with data greater than x
template <class Type>
void BinarySearchTree<Type>::delete_greater(const Type& x, BinaryNode*& t) {
    if (t != nullptr) {
        // If the current node's data is greater than x, remove this node and its right subtree
        if (x < t->data) {
            BinaryNode* tmp = t;
            t = t->left;
            makeEmpty(tmp->right);
            delete tmp;
            // Continue checking the new current node (the left subtree)
            delete_greater(x, t);
        } else {
            // Continue checking the right subtree
            delete_greater(x, t->right);
        }
    }
}

template <class Type>
void BinarySearchTree<Type>::delete_between(const Type& x, const Type& y) {
    delete_between(x, y, root);
}

// Recursively delete all nodes with data between x and y (exclusive)
template <class Type>
void BinarySearchTree<Type>::delete_between(const Type& x, const Type& y, BinaryNode*& t) {
    if (t == nullptr) return;

    // If current node's data is less than x, no need to check the left subtree
    if (t->data <= x) {
        delete_between(x, y, t->right);
    }

    // If current node's data is greater than y, no need to check the right subtree
    else if (t->data >= y) {
        delete_between(x, y, t->left);
    } 

    // If current node's data is between x and y
    else {
        // Recurse into both subtrees before deleting the current node
        delete_between(x, y, t->left);
        delete_between(x, y, t->right);
        remove(t->data, t);
    }
}



int main() {
    BinarySearchTree<int> bst;

    cout << "Enter the number of elements to insert: ";
    int n;
    cin >> n;

    cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; ++i) {
        int value;
        cin >> value;
        bst.insert(value);
    }

    cout << "Initial tree (in-order traversal): ";
    bst.display();
    cout << endl;

    cout << "Enter a value for delete_less: ";
    int less_value;
    cin >> less_value;
    bst.delete_less(less_value);
    cout << "Tree after delete_less(" << less_value << "): ";
    bst.display();
    cout << endl;

    cout << "Enter a value for delete_greater: ";
    int greater_value;
    cin >> greater_value;
    bst.delete_greater(greater_value);
    cout << "Tree after delete_greater(" << greater_value << "): ";
    bst.display();
    cout << endl;

    cout << "Enter two values (low and high) for delete_between: ";
    int low, high;
    cin >> low >> high;
    bst.delete_between(low, high);
    cout << "Tree after delete_between(" << low << ", " << high << "): ";
    bst.display();
    cout << endl;

    return 0;
}