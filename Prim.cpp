#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

class Edge {
public:
    int src, dest, weight;

    Edge(int src, int dest, int weight) : src(src), dest(dest), weight(weight) {}

    bool operator<(const Edge &other) const {
        return weight < other.weight;
    }

    bool operator>(const Edge &other) const {
        return weight > other.weight;
    }
};


class Graph {
public:
    int vertices;
    vector<vector<pair<int, int>>> adj;

    Graph(int vertices);
    void addEdge(int src, int dest, int weight);
    vector<Edge> prim();
};

Graph::Graph(int vertices) : vertices(vertices) {
    adj.resize(vertices);
}

void Graph::addEdge(int src, int dest, int weight) {
    adj[src].emplace_back(dest, weight);
    adj[dest].emplace_back(src, weight);
}

vector<Edge> Graph::prim() {
    vector<Edge> result;
    vector<bool> visited(vertices, false);

    priority_queue<Edge, vector<Edge>, less<Edge>> pq;

    pq.push(Edge(0, 0, 0));

    while (!pq.empty()) {
        Edge current = pq.top();
        pq.pop();

        int currentVertex = current.dest;

        if (visited[currentVertex])
            continue;

        visited[currentVertex] = true;
        result.push_back(current);

        for (const auto &neighbor : adj[currentVertex]) {
            if (!visited[neighbor.first]) {
                pq.push(Edge(currentVertex, neighbor.first, neighbor.second));
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

    vector<Edge> result = g.prim();

    cout << "Minimum spanning tree edges:" << endl;
    for (const Edge &edge : result) {
        cout << edge.src << " -- " << edge.dest << " Weight: " << edge.weight << endl;
    }

    return 0;
}
