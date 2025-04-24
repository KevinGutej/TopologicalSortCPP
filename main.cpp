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

    void resetInDegree() {
        for (int i = 0; i < V; ++i) {
            in_degree[i] = 0;
        }
        for (int u = 0; u < V; ++u) {
            for (int v = 0; v < V; ++v) {
                if (adj[u][v] == 1) {
                    in_degree[v]++;
                }
            }
        }
    }

    void dfsTopo(int u, bool* visited, int* result, int& idx) {
        visited[u] = true;
        for (int v = 0; v < V; ++v) {
            if (adj[u][v] && !visited[v]) {
                dfsTopo(v, visited, result, idx);
            }
        }
        result[idx--] = u;
    }

    bool dfsCycleUtil(int u, bool* visited, bool* recStack) {
        visited[u] = true;
        recStack[u] = true;

        for (int v = 0; v < V; ++v) {
            if (adj[u][v]) {
                if (!visited[v] && dfsCycleUtil(v, visited, recStack)) return true;
                else if (recStack[v]) return true;
            }
        }
        recStack[u] = false;
        return false;
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
        if (adj[u][v] == 0) {
            adj[u][v] = 1;
        }
    }

    void printGraph() {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                std::cout << adj[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    void printInDegree() {
        resetInDegree();
        for (int i = 0; i < V; ++i) {
            std::cout << "In-degree of " << i << " is " << in_degree[i] << "\n";
        }
    }

    bool topologicalSortKahn() {
        resetInDegree();

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
                if (adj[u][v]) {
                    in_degree[v]--;
                    if (in_degree[v] == 0) {
                        push(queue, rear, v);
                    }
                }
            }
        }

        if (idx != V) {
            std::cout << "Cycle detected\n";
            delete[] queue;
            delete[] topo_order;
            return false;
        }

        for (int i = 0; i < V; ++i) {
            std::cout << topo_order[i] << " ";
        }
        std::cout << "\n";

        delete[] queue;
        delete[] topo_order;
        return true;
    }

    bool hasCycleDFS() {
        bool* visited = new bool[V];
        bool* recStack = new bool[V];
        for (int i = 0; i < V; ++i) {
            visited[i] = false;
            recStack[i] = false;
        }
        for (int i = 0; i < V; ++i) {
            if (!visited[i] && dfsCycleUtil(i, visited, recStack)) {
                delete[] visited;
                delete[] recStack;
                return true;
            }
        }
        delete[] visited;
        delete[] recStack;
        return false;
    }

    void topologicalSortDFS() {
        int* result = new int[V];
        bool* visited = new bool[V];
        for (int i = 0; i < V; ++i) visited[i] = false;
        int idx = V - 1;

        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                dfsTopo(i, visited, result, idx);
            }
        }

        for (int i = 0; i < V; ++i) {
            std::cout << result[i] << " ";
        }
        std::cout << "\n";

        delete[] visited;
        delete[] result;
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

    g.printGraph();
    g.printInDegree();

    std::cout << "Kahn's Topological Sort:\n";
    g.topologicalSortKahn();

    std::cout << "DFS Topological Sort:\n";
    g.topologicalSortDFS();

    if (g.hasCycleDFS()) {
        std::cout << "Cycle exists\n";
    } else {
        std::cout << "No cycle detected\n";
    }

    return 0;
}
