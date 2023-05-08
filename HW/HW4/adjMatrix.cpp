#include <iostream>
#include <vector>

using namespace std;

// 節點的結構體
struct Node {
    int id;
    // 其他屬性
};

// 圖的類別
class Graph {
private:
    vector<vector<int>> adjMatrix;
    vector<Node> nodes;
public:
    Graph() {
        adjMatrix.resize(0, vector<int>(0, 0));
    }

    void addNode(int id) {
        Node node = { id };
        nodes.push_back(node);
        int n = nodes.size();
        adjMatrix.resize(n, vector<int>(n, 0));
    }

    void addEdge(int src, int dest, int weight) {
        adjMatrix[src][dest] = weight;
        adjMatrix[dest][src] = weight;
    }

    void printGraph() {
        int n = nodes.size();
        for (int i = 0; i < n; i++) {
            cout << "Node " << nodes[i].id << " is connected to: ";
            for (int j = 0; j < n; j++) {
                if (adjMatrix[i][j] > 0) {
                    cout << nodes[j].id << "(" << adjMatrix[i][j] << ") ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    // 創建圖
    Graph g;

    // 添加節點
    g.addNode(0);
    g.addNode(1);
    g.addNode(2);
    g.addNode(3);

    // 添加邊
    g.addEdge(0, 1, 2);
    g.addEdge(1, 2, 3);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 0, 4);

    // 打印圖
    g.printGraph();

    return 0;
}