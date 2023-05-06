#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <string.h>
#include <cmath>
using namespace std;


// Vertice, Edges, Graph


typedef struct {
    int message;
    float distance;
} weight;


class Vertex
{
private:
    string name;
    string type;
    list<pair<Vertex*, weight>> adjacentVertex;

public:
    Vertex(string name, string type);

    friend class Graph;
};

Vertex::Vertex(string name, string type) {
    this->name = name;
    this->type = type;
}


class Graph
{
private:
    vector<Vertex*> adjlist; // Adjecency list
    int totalVertex;
    

public:
    void insertVertex(string name, string type);
    void insertEdge(int from, int to, int message);

    Graph();
};

Graph::Graph() {
    adjlist = {};
    totalVertex = 0;
}

void Graph::insertVertex(string name, string type) {
    Vertex *newVertex = new Vertex(name, type);
    adjlist.push_back(newVertex);

    totalVertex += 1;
}

void Graph::insertEdge(int from, int to, int message) {
    // Vertex ID start from, but index of adjlist start from 0
    Vertex* fromVertex = adjlist[from-1];
    Vertex* toVertex   = adjlist[to-1];

    weight edgeInfo;
    edgeInfo.message = message;
    edgeInfo.distance = round(1000./(float)message * 100.)/100.;

    fromVertex->adjacentVertex.push_back(make_pair(toVertex, edgeInfo));
}




int main() {
    
    string input;
    Graph network;
    

    while (getline(cin, input))
    {
        int pos = input.find(' ');
        string command = input.substr(0, pos);

        if (command == "INSERT") {
            // .find(<the str you want to find>, <start pos>)
            int pos1 = input.find(' ', pos+1);

            // .substr(<start pos>, <length of the substring>)
            string nodeType = input.substr(pos+1, (pos1-1)-pos);
            string name = input.substr(pos1+1);

            network.insertVertex(name, nodeType);
            cout << "Inserting node of type " << nodeType << " with name " << name << endl;
        }

        else if (command == "INSERT_EDGE") {
            int pos1 = input.find(' ', pos+1);
            int pos2 = input.find(' ', pos1+1);

            int id_number1 = stoi( input.substr(pos+1, (pos1-1)-pos) );
            int id_number2 = stoi( input.substr(pos1+1, (pos2-1)-pos1));
            int total_message = stoi(input.substr(pos2+1));

            // Use undirected graph for this problem
            network.insertEdge(id_number1, id_number2, total_message);
            network.insertEdge(id_number2, id_number1, total_message);
            cout << "Inserting edge between nodes " << id_number1 << " and " << id_number2 << " with total message " << total_message << endl;
        }
    }
    

    return 0;
}