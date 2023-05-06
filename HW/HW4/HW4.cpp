#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<list>
#include<string.h>
#include<cmath>
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
};

Vertex::Vertex(string name, string type) {
    this->name = name;
    this->type = type;
}


class Graph
{
private:
    vector<Vertex*> adjlist; // Adjecency list
    int vertexId;  // If we insert a new vertex, its ID is vertexId
    

public:
    void insertVertex(string name, string type);
    void insertEdge(int from, int to, int message);

    Graph();
};

Graph::Graph() {
    adjlist = {};
    vertexId = 0;
}

void Graph::insertVertex(string name, string type) {
    Vertex *newVertex = new Vertex(name, type);
    adjlist.push_back(newVertex);

    vertexId += 1;
}

void Graph::insertEdge(int from, int to, int message) {
    // Vertex ID start from, but index of adjlist start from 0
    Vertex* fromVertex = adjlist[from-1];
    Vertex* toVertex   = adjlist[to-1];

    weight edgeInfo;
    edgeInfo.message = message;
    edgeInfo.distance = round(1000./(float)message * 100.)/100.

    
}




int main() {
    
    string input;

    while (cin >> input)
    {
        
    }
    

    return 0;
}