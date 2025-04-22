#include <iostream>

class Graph {
private:
    int V;
    int** adj;
    int* in_degree;

    void push(int* q, int& rear, int val) {
        q[rear++] = val;
    }

    int pop(int* q, int& front) {
        return q[front++];
    }

public:
    Graph(int V) {
        this->V = V;
        adj = new int*[V];
        for (int i = 0; i < V; ++i) {
            adj[i] = new int[V];
            for (int j = 0; j < V; ++j) {
                adj[i][j] = 0;
            }
        }
        in_degree = new int[V];
        for (int i = 0; i < V; ++i) {
            in_degree[i] = 0;
        }
    }

    void addEdge(int u, int v) {
        adj[u][v] = 1;
    }

    bool topologicalSort() {
        for (int u = 0; u < V; ++u) {
            for (int v = 0; v < V; ++v) {
                if (adj[u][v] == 1) {
                    in_degree[v]++;
                }
            }
        }

        int* queue = new int[V];
        int front = 0, rear = 0;

        for (int i = 0; i < V; ++i) {
            if (in_degree[i] == 0) {
                push(queue, rear, i);
            }
        }

        int* topo_order = new int[V];
        int idx = 0;

        while (front < rear) {
            int u = pop(queue, front);
            topo_order[idx++] = u;

            for (int v = 0; v < V; ++v) {
                if (adj[u][v] == 1) {
                    in_degree[v]--;
                    if (in_degree[v] == 0) {
                        push(queue, rear, v);
                    }
                }
            }
        }

        if (idx != V) {
            std::cout << "Cycle detected!" << std::endl;
            return false;
        }

        for (int i = 0; i < V; ++i) {
            std::cout << topo_order[i] << " ";
        }
        std::cout << std::endl;

        delete[] queue;
        delete[] topo_order;
        return true;
    }

    ~Graph() {
        for (int i = 0; i < V; ++i) {
            delete[] adj[i];
        }
        delete[] adj;
        delete[] in_degree;
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
        std::cout << "Graph has a cycle" << std::endl;
    }

    return 0;
}
