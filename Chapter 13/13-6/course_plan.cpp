#include <iostream>
using namespace std;

template <class elemType>
class Queue {
public:
    virtual bool isEmpty() const = 0;
    virtual void enQueue(const elemType &x) = 0;
    virtual elemType deQueue() = 0;
    virtual elemType getHead() const = 0;
    virtual ~Queue() {}
};

template <class elemType>
class linkQueue : public Queue<elemType> {
private:
    struct node {
        elemType data;
        node* next;
        node(const elemType &x, node *N = nullptr) : data(x), next(N) {}
        node() : next(nullptr) {}
        ~node() {}
    };

    node* Front;
    node* rear;

public:
    linkQueue();
    ~linkQueue();
    bool isEmpty() const;
    void enQueue(const elemType &x);
    elemType deQueue();
    elemType getHead() const;
};

template <class elemType>
linkQueue<elemType>::linkQueue() {
    Front = rear = nullptr;
}

template <class elemType>
linkQueue<elemType>::~linkQueue() {
    node* tmp;
    while (Front != nullptr) {
        tmp = Front;
        Front = Front->next;
        delete tmp;
    }
}

template <class elemType>
bool linkQueue<elemType>::isEmpty() const {
    return Front == nullptr;
}

template <class elemType>
elemType linkQueue<elemType>::getHead() const {
    return Front->data;
}

template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x) {
    if (rear == nullptr)
        Front = rear = new node(x);
    else
        rear = rear->next = new node(x);
}

template <class elemType>
elemType linkQueue<elemType>::deQueue() {
    node* tmp = Front;
    elemType value = Front->data;
    Front = Front->next;
    if (Front == nullptr) rear = nullptr;
    delete tmp;
    return value;
}

template <class TypeOfVer, class TypeOfEdge>
class Graph {   
public:
    virtual void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) = 0;
    virtual void remove(TypeOfVer x, TypeOfVer y) = 0;
    virtual bool exist(TypeOfVer x, TypeOfVer y) const = 0;
    int numofVer() const { return Vers; }
    int numofEdge() const { return Edges; }

protected:
    int Vers, Edges;
};

template <class TypeOfVer, class TypeOfEdge>
class adjListGraph : public Graph<TypeOfVer, TypeOfEdge> {
public:
    adjListGraph(int vSize, const TypeOfVer d[]);
    void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
    void remove(TypeOfVer x, TypeOfVer y);
    bool exist(TypeOfVer x, TypeOfVer y) const;
    ~adjListGraph();

    void get_course_plan();

private:
    struct edgeNode {
        int end;
        TypeOfEdge weight;
        edgeNode* next;
        edgeNode(int e, TypeOfEdge w, edgeNode* n = nullptr) : end(e), weight(w), next(n) {}
    };

    struct verNode {
        TypeOfVer ver;
        edgeNode* head;
        verNode(edgeNode* h = nullptr) : head(h) {}

        int indegree; 
    };

    verNode* verList;
    int find(TypeOfVer v) const {
        for (int i = 0; i < this->Vers; ++i)
            if (verList[i].ver == v) return i;
        return -1;
    }

    void update_indegree();
};

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize, const TypeOfVer d[]) {
    this->Vers = vSize; this->Edges = 0;
    verList = new verNode[vSize];
    for (int i = 0; i < this->Vers; ++i) {
        verList[i].ver = d[i];
    }
}

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph() {
    int i;
    edgeNode* p;

    for (i = 0; i < this->Vers; ++i) {
        while ((p = verList[i].head) != nullptr) {
            verList[i].head = p->next;
            delete p;
        }
    }

    delete[] verList;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) {
    int u = find(x), v = find(y);
    if (u == -1 || v == -1) return;
    verList[u].head = new edgeNode(v, w, verList[u].head);
    ++this->Edges;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::remove(TypeOfVer x, TypeOfVer y) {
    int u = find(x), v = find(y);
    edgeNode* p = verList[u].head;
    edgeNode* q;

    if (p == nullptr) return;

    if (p->end == v) {
        verList[u].head = p->next;
        delete p;
        --this->Edges;
        return;
    }

    while (p->next != nullptr && p->next->end != v) p = p->next;
    if (p->next != nullptr) {
        q = p->next;
        p->next = q->next;
        delete q;
        --this->Edges;
    }
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::exist(TypeOfVer x, TypeOfVer y) const {
    int u = find(x), v = find(y);
    edgeNode* p = verList[u].head;

    while (p != nullptr && p->end != v) p = p->next;
    if (p == nullptr) return false;
    else return true;
}

// This function updates the indegree of each vertex in the graph.
template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::update_indegree() {
    for (int i = 0; i < this->Vers; ++i) {
        verList[i].indegree = 0;
    }
    for (int i = 0; i < this->Vers; ++i) {
        edgeNode* p = verList[i].head;
        while (p != nullptr) {
            verList[p->end].indegree++;
            p = p->next;
        }
    }
}

/**
 * @brief This function generates a course plan based on the prerequisites.
 * It uses a topological sort approach to determine the order in which courses can be taken.
 */
template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::get_course_plan()
{
    const int n = this->Vers;

    int *indeg = new int[n] {};
    bool *taken = new bool[n] {};

    // Calculate indegrees of each vertex
    for (int i = 0; i < n; ++i)
        for (edgeNode *p = verList[i].head; p; p = p->next)
            ++indeg[p->end];

            
    linkQueue<int> q;
    for (int i = 0; i < n; ++i)
        // Initialize the queue with courses that have no prerequisites
        if (indeg[i] == 0) q.enQueue(i);

    int semester = 1, printed = 0;

    while (!q.isEmpty())
    {
        linkQueue<int> next_sem;

        while (!q.isEmpty())
        {
            int u = q.deQueue();
            if (taken[u]) continue;

            cout << "Course " << verList[u].ver
                 << " can be taken in Semester " << semester << ".\n";

            taken[u] = true;  // Mark the course as taken
            ++printed;

            // Decrease indegree of adjacent vertices
            for (edgeNode *p = verList[u].head; p; p = p->next)
            {
                int v = p->end;
                if (!taken[v] && --indeg[v] == 0)
                    next_sem.enQueue(v);  // If indegree becomes zero, add to next semester queue
            }
        }

        // Deep copy the next semester queue to the main queue
        while (!next_sem.isEmpty()) {
            q.enQueue(next_sem.deQueue());
        }

        ++semester;
    }

    cout << "All courses have been scheduled." << endl;

    delete [] indeg;
    delete [] taken;
}


int main() {
    const int course_num = 7;
    string courses[course_num] = {
        "Programming",
        "Discrete Math",
        "Data Structures",
        "Algorithms",
        "Computer Organization",
        "Operating Systems",
        "Artificial Intelligence"
    };

    adjListGraph<string, int> g(course_num, courses);

    g.insert("Programming", "Data Structures", 1);
    g.insert("Programming", "Computer Organization", 1);
    g.insert("Discrete Math", "Data Structures", 1);
    g.insert("Data Structures", "Algorithms", 1);
    g.insert("Algorithms", "Artificial Intelligence", 1);
    g.insert("Computer Organization", "Operating Systems", 1);

    g.get_course_plan();

    return 0;
}
