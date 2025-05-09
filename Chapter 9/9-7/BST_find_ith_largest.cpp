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
    void find_ith_largest(BinaryNode* t, int& i, Type& result) const;

public:
    void display() const;
    Type find_ith_largest(int i) const;
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

/**
 * @brief Finds the i-th largest element in the binary search tree.
 * 
 * Performs a reverse-order traversal (right -> root -> left)
 * to locate the i-th largest element. The result is stored in the
 * 'result' parameter when found.
 */
template <class Type>
void BinarySearchTree<Type>::find_ith_largest(BinaryNode* t, int& i, Type& result) const {
    if (t == nullptr) return;

    // Traverse the right subtree first
    find_ith_largest(t->right, i, result);

    --i;
    if (i == 0) {
        result = t->data;
        return;
    }

    // Then traverse the left subtree
    find_ith_largest(t->left, i, result);
}

template <class Type>
Type BinarySearchTree<Type>::find_ith_largest(int i) const {
    Type result;
    int counter = i;
    find_ith_largest(root, counter, result);
    if (counter <= 0) return result;
    else return -1;
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

    cout << "Enter i to find the i-th largest element: ";
    int i;
    cin >> i;

    int result = -1;
    result = bst.find_ith_largest(i);

    if (result != -1) {
        cout << "The requested element is: " << result << endl;
    } else {
        cout << "The i-th largest element does not exist." << endl;
    }

    return 0;
}