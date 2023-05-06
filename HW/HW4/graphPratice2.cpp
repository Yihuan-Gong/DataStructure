#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Node {
public:
    int val;
    list<pair<Node*, int>> neighbors;
    Node(int v) : val(v) {}
};

class Graph {
private:
    int V; // �`�I�ƶq
    vector<Node*> nodes; // �s�x�`�I����

public:
    Graph(int v) {
        V = v;
        nodes.resize(v);
        for (int i = 0; i < v; ++i) {
            nodes[i] = new Node(i);
        }
    }

    // �s�W��A�a�v��
    void addEdge(int u, int v, int w) {
        Node* fromNode = nodes[u];
        Node* toNode = nodes[v];
        fromNode->neighbors.push_back(make_pair(toNode, w));
    }

    // ��� Graph
    void printGraph() {
        for (int i = 0; i < V; ++i) {
            Node* curNode = nodes[i];
            cout << "Node " << curNode->val << ": ";
            for (auto it = curNode->neighbors.begin(); it != curNode->neighbors.end(); ++it) {
                Node* neighbor = it->first;
                int weight = it->second;
                cout << "(" << neighbor->val << ", " << weight << ") ";
            }
            cout << endl;
        }
    }

    // �Ѻc�l
    ~Graph() {
        for (int i = 0; i < V; ++i) {
            delete nodes[i];
        }
    }
};

int main() {
    // �إߥ[�v��
    Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 4, 5);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 4);
    g.addEdge(1, 4, 7);
    g.addEdge(2, 3, 3);
    g.addEdge(3, 4, 6);

    // ��� Graph
    g.printGraph();

    return 0;
}