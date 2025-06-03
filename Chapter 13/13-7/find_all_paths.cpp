#include <iostream>
#include <vector>
using namespace std;

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

    void find(TypeOfVer start, int M);

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

    void dfs(int u, int depth, int M, vector<int>& path, bool visited[]);
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

/**
 * @brief Depth-first search to find all simple paths of length M starting from a given vertex.
 */
template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs(int u, int depth, int M, vector<int>& path, bool visited[]) {
    if (depth == M) {
        // Print the path if it has reached the desired length
        for (int i : path)
            cout << verList[i].ver << " ";
        cout << endl;
        return;
    }

    visited[u] = true;

    for (edgeNode* p = verList[u].head; p; p = p->next) {
        int v = p->end;
        if (!visited[v]) {
            path.push_back(v);
            dfs(v, depth + 1, M, path, visited);
            path.pop_back(); // Backtrack to explore other paths
        }
    }

    visited[u] = false; // Backtrack
}

/**
 * @brief Find all simple paths of length M starting from a given vertex.
 */
template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::find(TypeOfVer start, int M) {
    int u = find(start);
    if (u == -1) {
        cout << "Vertex not found." << endl;
        return;
    }

    vector<int> path;
    bool* visited = new bool[this->Vers]();
    
    path.push_back(u);
    dfs(u, 0, M, path, visited);

    delete[] visited;
}

int main() {
    const int n = 6;
    int nodes[n] = {0, 1, 2, 3, 4, 5};

    adjListGraph<int, int> g(n, nodes);

    g.insert(0, 1, 1);
    g.insert(0, 3, 1);
    g.insert(1, 2, 1);
    g.insert(1, 4, 1);
    g.insert(3, 4, 1);
    g.insert(4, 5, 1);

    for (int M = 1; M <= 4; ++M) {
        cout << endl << "All simple paths of length " << M << " starting from node 0:" << endl;
        g.find(0, M);
    }

    return 0;
}
