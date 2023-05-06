#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Graph {
private:
    int V; // 節點數量
    vector<list<pair<int, int>>> adjList; // 鄰接表

public:
    Graph(int v) {
        V = v;
        adjList.resize(v);
    }

    // 新增邊
    void addEdge(int u, int v, int w) {
        adjList[u].push_back(make_pair(v, w));
    }

    // 顯示 Graph
    void printGraph() {
        for (int i = 0; i < V; ++i) {
            cout << "Node " << i << ": ";
            for (auto it = adjList[i].begin(); it != adjList[i].end(); ++it) {
                cout << "(" << it->first << ", " << it->second << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    // 建立 Graph
    Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 4, 5);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 4);
    g.addEdge(1, 4, 7);
    g.addEdge(2, 3, 3);
    g.addEdge(3, 4, 6);

    // 顯示 Graph
    g.printGraph();

    return 0;
}