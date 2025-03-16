#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template <class elemType>
class Stack {
public:
    virtual bool isEmpty() const = 0;
    virtual void push(const elemType &x) = 0;
    virtual elemType pop() = 0;
    virtual elemType top() const = 0;
    virtual ~Stack() {}
};

template <class elemType>
class linkStack:public Stack<elemType> {
private:
    struct node{
        elemType data;
        node* next;

        node(const elemType &x, node* N = nullptr) : data(x), next(N) {}
        node() : next(nullptr) {}
        ~node() {}
    };

    node* top_p;

public:
    linkStack();
    ~linkStack();
    bool isEmpty() const;
    void push(const elemType &x);
    elemType pop();
    elemType top() const;
};

template <class elemType>
linkStack<elemType>::linkStack() {
    top_p = nullptr;
}

template <class elemType>
linkStack<elemType>::~linkStack() {
    node* tmp;
    while (top_p != nullptr) {
        tmp = top_p;
        top_p = top_p->next;
        delete tmp;
    }
}

template <class elemType>
bool linkStack<elemType>::isEmpty() const {
    return top_p == nullptr;
}

template <class elemType>
void linkStack<elemType>::push(const elemType &x) {
    top_p = new node(x, top_p);
}

template <class elemType>
elemType linkStack<elemType>::pop() {
    node* tmp = top_p;
    elemType x = tmp->data;
    top_p = top_p->next;
    delete tmp;
    return x;
}

template <class elemType>
elemType linkStack<elemType>::top() const {
    return top_p->data;
}

/**
 * Parses a Pascal file and checks for syntax errors
 * related to "begin-end" and "if-then-else" structures.
 */
void checkSyntax(const string &filename) {
    ifstream infile(filename);
    string word;
    linkStack<string> begin_end_stack;
    linkStack<string> if_then_else_stack;

    while (infile >> word) {

        if (word == "begin") {
            begin_end_stack.push(word);
        } 

        // Handle all the "end" variations
        else if (word == "end" || word == "end." || word == "end;") {
            if (begin_end_stack.isEmpty()) {
                cout << "ERROR: end without begin" << endl;
            } else {
                begin_end_stack.pop();
            }
        }
        
        else if (word == "if") {
            if_then_else_stack.push(word);
        } 
        
        else if (word == "then") {
            if (if_then_else_stack.isEmpty() || if_then_else_stack.top() != "if") {
                cout << "ERROR: then without if" << endl;
            } else {
                // Pop "if" and push "if-then" to match an "else" later
                if_then_else_stack.pop();
                if_then_else_stack.push("if-then");
            }
        } 
        
        else if (word == "else") {
            if (if_then_else_stack.isEmpty() || if_then_else_stack.top() != "if-then") {
                cout << "ERROR: else without if-then" << endl;
            } else {
                if_then_else_stack.pop();
            }
        }
    }

    // Final stack checks after reading the file for unmatched "begin" and "if"
    while (!begin_end_stack.isEmpty()) {
        cout << "ERROR: begin without end" << endl;
        begin_end_stack.pop();
    }

    while (!if_then_else_stack.isEmpty()) {
        if (if_then_else_stack.top() != "if-then") {
            cout << "ERROR: if without then" << endl;
        }
        if_then_else_stack.pop();
    }

    cout << endl;
    infile.close();
}



int main() {
    cout << "Test 1 (Correct):" << endl;
    checkSyntax("test1.txt");

    cout << "Test 2 (Correct):" << endl;
    checkSyntax("test2.txt");

    cout << "Test 3 (Correct):" << endl;
    checkSyntax("test3.txt");

    cout << "Test 4 (Wrong):" << endl;
    checkSyntax("test4.txt");

    cout << "Test 5 (Wrong):" << endl;
    checkSyntax("test5.txt");

    cout << "Test 6 (Wrong):" << endl;
    checkSyntax("test6.txt");

    return 0;
}
