#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Edge {
public:
    int src, dest, weight;

    Edge(int src, int dest, int weight) : src(src), dest(dest), weight(weight) {}

    bool operator<(const Edge &other) const {
        return weight < other.weight;
    }
};

class Graph {
public:
    int vertices;
    vector<Edge> edges;

    Graph(int vertices);
    void addEdge(int src, int dest, int weight);
    vector<Edge> kruskal();
};

Graph::Graph(int vertices) : vertices(vertices) {}

void Graph::addEdge(int src, int dest, int weight) {
    edges.emplace_back(src, dest, weight);
}

vector<Edge> Graph::kruskal() {
    vector<Edge> result;

    sort(edges.begin(), edges.end());

    vector<int> parent(vertices);
    vector<int> rank(vertices, 0);

    for (int i = 0; i < vertices; i++) {
        parent[i] = i;
    }

    for (const Edge &edge : edges) {
        int rootSrc = parent[edge.src];
        int rootDest = parent[edge.dest];

        if (rootSrc != rootDest) {
            result.push_back(edge);
            if (rank[rootSrc] < rank[rootDest]) {
                parent[rootSrc] = rootDest;
            } else if (rank[rootSrc] > rank[rootDest]) {
                parent[rootDest] = rootSrc;
            } else {
                parent[rootDest] = rootSrc;
                rank[rootSrc]++;
            }
        }
    }

    return result;
}

int main() {
    Graph g(8);

    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 0, 4);
    g.addEdge(2, 3, 3);
    g.addEdge(3, 4, 1);
    g.addEdge(4, 3, 1);
    g.addEdge(5, 4, 1);
    g.addEdge(6, 5, 1);
    g.addEdge(7, 6, 1);
    g.addEdge(6, 7, 1);

    vector<Edge> result = g.kruskal();

    cout << "Minimum spanning tree edges:" << endl;
    for (const Edge &edge : result) {
        cout << edge.src << " -- " << edge.dest << " Weight: " << edge.weight << endl;
    }

    return 0;
}
