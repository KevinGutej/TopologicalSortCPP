#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    bool topologicalSort() {
        vector<int> in_degree(V, 0);
        for (int u = 0; u < V; ++u) {
            for (int v : adj[u]) {
                in_degree[v]++;
            }
        }

        queue<int> q;
        for (int i = 0; i < V; ++i) {
            if (in_degree[i] == 0) {
                q.push(i);
            }
        }

        vector<int> topo_order;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo_order.push_back(u);

            for (int v : adj[u]) {
                if (--in_degree[v] == 0) {
                    q.push(v);
                }
            }
        }

        if (topo_order.size() != V) {
            cout << "Cycle detected!" << endl;
            return false;
        }

        for (int node : topo_order) {
            cout << node << " ";
        }
        cout << endl;
        return true;
    }
};

int main() {
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    if (!g.topologicalSort()) {
        cout << "Graph has a cycle" << endl;
    }

    return 0;
}
