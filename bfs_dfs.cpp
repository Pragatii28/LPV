#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>
using namespace std;

class Graph {
public:
    int V;
    vector<vector<int>> adj;

    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected
    }

    void parallelBFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);

        cout << "Parallel BFS: ";

        while (!q.empty()) {
            int sz = q.size();

            #pragma omp parallel for
            for (int i = 0; i < sz; ++i) {
                int curr;
                #pragma omp critical
                {
                    if (!q.empty()) {
                        curr = q.front();
                        q.pop();
                        cout << curr << " ";
                    }
                }

                for (int neighbor : adj[curr]) {
                    #pragma omp critical
                    {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
            }
        }
        cout << endl;
    }

    void parallelDFS(int start) {
        vector<bool> visited(V, false);
        stack<int> stk;
        stk.push(start);

        cout << "Parallel DFS: ";

        while (!stk.empty()) {
            int curr = stk.top();
            stk.pop();

            if (!visited[curr]) {
                visited[curr] = true;
                cout << curr << " ";

                #pragma omp parallel for
                for (int i = 0; i < adj[curr].size(); ++i) {
                    int neighbor = adj[curr][i];
                    if (!visited[neighbor]) {
                        #pragma omp critical
                        stk.push(neighbor);
                    }
                }
            }
        }
        cout << endl;
    }
};

int main() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 5);

    g.parallelBFS(0);
    g.parallelDFS(0);

    return 0;
}
