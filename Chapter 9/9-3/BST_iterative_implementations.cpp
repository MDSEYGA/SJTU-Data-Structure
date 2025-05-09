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
    void makeEmpty(BinaryNode*& t);
    void display(BinaryNode* t) const;

public:
    void display() const;

private:
};

template <class Type>
Type* BinarySearchTree<Type>::find(const Type& x) const {
    BinaryNode* current = root;
    while (current != nullptr) {
        if (current->data < x) {
            current = current->right;
        } else if (current->data > x) {
            current = current->left;
        } else {
            return &current->data;
        }
    }
    return nullptr;
}

template <class Type>
void BinarySearchTree<Type>::insert(const Type& x) {
    BinaryNode* current = root;
    BinaryNode* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (x < current->data) {
            current = current->left;
        } else if (current->data < x) {
            current = current->right;
        } else {
            return; // Duplicate value, do not insert
        }
    }

    BinaryNode* newNode = new BinaryNode(x);
    if (parent == nullptr) {
        root = newNode; // Tree was empty, new node becomes root
    } else if (x < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

}

template <class Type>
void BinarySearchTree<Type>::remove(const Type& x) {
    BinaryNode* parent = nullptr;
    BinaryNode* current = root;

    // First find the node to be deleted
    while (current != nullptr) {
        if (current->data < x) {
            parent = current;
            current = current->right;
        } else if (current->data > x) {
            parent = current;
            current = current->left;
        } else {
            break;
        }
    }

    if (current == nullptr) return; // Node not found

    if (current->left == nullptr && current->right == nullptr) {
        // Node is a leaf
        if (parent == nullptr) { // Node is root
            delete root;
            root = nullptr;
        } else {
            if (parent->left == current) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
            delete current;
        }
    }

    else if (current->right == nullptr) {
        // Node has only left child
        if (parent == nullptr) { // Node is root
            root = current->left;
        } else if (parent->left == current) {
            parent->left = current->left;
        } else {
            parent->right = current->left;
        }
        delete current;
    }

    else if (current->left == nullptr) {
        // Node has only right child
        if (parent == nullptr) { // Node is root
            root = current->right;
        } else if (parent->left == current) {
            parent->left = current->right;
        } else {
            parent->right = current->right;
        }
        delete current;
    }

    else {
        // Node has two children
        // Find the inorder successor
        BinaryNode* successor = current->right;
        BinaryNode* successorParent = current;
        while (successor->left != nullptr) {
            successorParent = successor;
            successor = successor->left;
        }

        // Replace current with successor
        current->data = successor->data;

        // Delete the successor
        if (successorParent->left == successor) {
            successorParent->left = successor->right;
        } else {
            successorParent->right = successor->right;
        }
        delete successor;
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

    cout << "Enter a value to find: ";
    int searchValue;
    cin >> searchValue;

    int* result = bst.find(searchValue);
    if (result != nullptr) {
        cout << "Value " << searchValue << " found in the tree." << endl;
    } else {
        cout << "Value " << searchValue << " not found." << endl;
    }

    cout << "Enter a value to remove: ";
    int removeValue;
    cin >> removeValue;

    bst.remove(removeValue);
    cout << "Tree after removing " << removeValue << ": ";
    bst.display();
    cout << endl;

    cout << "Enter a new value to insert: ";
    int newInsert;
    cin >> newInsert;
    bst.insert(newInsert);

    cout << "Tree after inserting " << newInsert << ": ";
    bst.display();
    cout << endl;

    cout << "Enter another value to remove: ";
    cin >> removeValue;

    bst.remove(removeValue);
    cout << "Tree after removing " << removeValue << ": ";
    bst.display();
    cout << endl;

    return 0;
}