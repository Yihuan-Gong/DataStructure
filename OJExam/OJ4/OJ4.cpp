#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<list>
#include<string.h>
#include<cmath>

#define inf 2147483647

using namespace std;


class Vertex
{
private:
    int id;
    bool visited;
    list<pair<Vertex*, int>> adjVertex;
public:
    Vertex(int id);

    friend class Graph;
};

Vertex::Vertex(int id)
{
    this->id = id;
    this->visited = false;
}

class Graph
{
private:
    vector<Vertex*> adjlist;
    int totalVertice;

public:
    void insertVertex(int num);
    void insertEdge(int from, int to, int distance);
    int dijkstra(int start, int end);

    Graph();
};

Graph::Graph()
{
    Vertex *header = new Vertex(0);
    adjlist.push_back(header);

    totalVertice = 0;
}

void Graph::insertVertex(int num) {
    for (int i = 1; i <= num; i++) {   
        totalVertice += 1;
        Vertex *newVertex = new Vertex(totalVertice);
        adjlist.push_back(newVertex);
    } 
}

void Graph::insertEdge(int from, int to, int distance) {
    Vertex* fromVertex = adjlist[from]; 
    Vertex* toVertex   = adjlist[to];

    fromVertex->adjVertex.push_back(make_pair(toVertex, distance));
}

int Graph::dijkstra(int start, int end) {
    int D[totalVertice+1], Y[totalVertice+1];
    int currentVertex, adjVertexId, distance, minDist;
    bool visited;
    
    // Initialize
    for (int i=1; i<=totalVertice; i++) {
        D[i] = inf;
        Y[i] = start;
    }
    D[start] = 0;

    // Iterate
    currentVertex = start;
    for (int i=1; i<totalVertice; i++) 
    {
        // Visit current vertex
        adjlist[currentVertex]->visited = true;
        for (auto j  = adjlist[currentVertex]->adjVertex.begin(); 
                  j != adjlist[currentVertex]->adjVertex.end(); ++j)
        {
            adjVertexId = j->first->id;
            visited     = j->first->visited;
            distance    = j->second;

            if (visited)
                continue;
            
            if ((D[currentVertex] + distance) < D[adjVertexId]) {
                D[adjVertexId] = D[currentVertex] + distance;
                Y[adjVertexId] = currentVertex;
            }
        }


        // Decide next vertex to be visited
        minDist = inf;
        for (int i=1; i<=totalVertice; i++) {
            if (D[i]<minDist && !(adjlist[i]->visited)) {
                minDist = D[i];
                currentVertex = i;
            }
        }
    }

    // Resume all vertice to UNVISITED
    for (int i = 1; i <= totalVertice; i++) {
        adjlist[i]->visited = false;
    }

    // Output shortest distance
    return D[end];
}


int main() {

    Graph Network;
    string input, command;
    int pos, pos1, pos2;
    int numOfVertice, vertexId, vertex1, vertex2, distance;
    int shortestDist;


    while (getline(cin, input))
    {
        if (input == "TERMINATE") {
            break;
        }
            
        pos = input.find(' ');
        command = input.substr(0, pos);

        if (command == "INSERT_LOCATIONS") {
            numOfVertice = stoi( input.substr(pos+1) );
            Network.insertVertex(numOfVertice);
        }
        else if (command == "CALCULATE") {
            vertexId = stoi( input.substr(pos+1) );
            shortestDist = Network.dijkstra(1, vertexId);
            cout << shortestDist << "\n";
        }
        else if (command == "INSERT_DISTANCE") {
            pos1 = input.find(' ', pos+1);
            pos2 = input.find(' ', pos1+1);

            vertex1 = stoi( input.substr(pos+1, (pos1-1)-pos) );
            vertex2 = stoi( input.substr(pos1+1, (pos2-1)-pos1));
            distance = stoi(input.substr(pos2+1));

            Network.insertEdge(vertex1, vertex2, distance);
            Network.insertEdge(vertex2, vertex1, distance);
        }
    }
    
    return 0;
}