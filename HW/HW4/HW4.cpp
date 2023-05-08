#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <string.h>
#include <cmath>

#define inf 1e10

using namespace std;

// Vertice, Edges, Graph

typedef struct {
    int message;
    float distance;
} weight;


class Vertex
{
private:
    int id;
    string name;
    string type;
    bool visited;
    list<pair<Vertex*, weight>> adjacentVertex;

public:
    Vertex(int id, string name, string type);

    friend class Graph;
};

Vertex::Vertex(int id, string name, string type) {
    this->id = id;
    this->name = name;
    this->type = type;
    this->visited = false;
}


class Graph
{
private:
    vector<Vertex*> adjlist; // Adjecency list
    int totalVertex;
    int source;
    int headquarter;  
    float shortestDist;  // The shortest distance from source to HQ
    string shortestPath; // The shortest path from source to HQ
    int totalMessage;    // Total message in shortest path

public:
    int getSource() { return source; }
    int getHQ() { return headquarter; }
    float  getShortestDist() { return shortestDist; }
    string getShortestPath() { return shortestPath; }
    int    getTotalMessage() { return totalMessage; }

    void insertVertex(string name, string type);
    void insertEdge(int from, int to, int message);
    void dijkstra(int start);

    Graph();
};

Graph::Graph() {
    // Creat a header node to "fill" the index 0
    // So if one create a new vertex, its index start from 1
    Vertex *header = new Vertex(0, "header", "header");
    adjlist.push_back(header);

    totalVertex = 0;
}

void Graph::insertVertex(string name, string type) {
    totalVertex += 1;

    Vertex *newVertex = new Vertex(totalVertex, name, type);
    adjlist.push_back(newVertex);

    // Mark source or headquarter
    if (type == "SOURCE")
        source = totalVertex;
    else if (type == "HQ")
        headquarter = totalVertex;
}

void Graph::insertEdge(int from, int to, int message) {
    // Vertex ID start from, but index of adjlist start from 0
    Vertex* fromVertex = adjlist[from];  // from-1 if no header
    Vertex* toVertex   = adjlist[to]; // to-1 if no header

    // Check if this edge is allowed
    if (fromVertex->type == "SOURCE") {
        if (toVertex->type=="SPY")
            return;
    }
    else if (fromVertex->type == "SPY") {
        if (toVertex->type=="SPY" || toVertex->type=="SOURCE")
            return;
    }
    else if (fromVertex->type == "CIV") {
        if (toVertex->type=="HQ")
            return;
    }
    else if (fromVertex->type == "HQ") {
        if (toVertex->type=="CIV")
            return;
    }
        
    weight edgeInfo;
    edgeInfo.message = message;
    edgeInfo.distance = round(1000./(float)message * 100.)/100.;

    fromVertex->adjacentVertex.push_back(make_pair(toVertex, edgeInfo));
}

void Graph::dijkstra(int start) {

    /* Initialize shortestDist array (D[i] array in the text book)
       Note: We want index start from 1, so there's +1 here  */
    float D[totalVertex+1]; 
    int Y[totalVertex+1];  
    int M[totalVertex+1];
    for (int i=1; i<=totalVertex; i++) {
        D[i] = inf;
        Y[i] = start;
        M[i] = 0;
    }
    D[start] = 0.;

    // Debug
    // cout << "Initialize" << endl;
    // for (int i=1; i<=totalVertex; i++) {
    //         cout << M[i] << "  ";
    // }
    // cout << endl;


    // Visit each vertex by Dijkstra alogrithm
    int currentVertex = start;
    for (int j=1; j<totalVertex; j++) 
    {
        /* Visit that vertex decided just now
           Visit "start" for the first visit */
        adjlist[currentVertex]->visited = true;  
        for (auto i  = adjlist[currentVertex]->adjacentVertex.begin(); 
                  i != adjlist[currentVertex]->adjacentVertex.end(); ++i)
        {
            int adjVertexId = i->first->id; // The Id of adjcent vertex
            float distance = i->second.distance;
            int message    = i->second.message; 

            // If passing "nextVertex" can reduce the distance from "start" to "vertexId"
            bool visited = adjlist[adjVertexId]->visited;
            bool shorter = (D[currentVertex] + distance) < D[adjVertexId];
            if (shorter && !visited) {  // I'm wondering if "shorter" is necessary here
                D[adjVertexId] = D[currentVertex] + distance;
                M[adjVertexId] = M[currentVertex] + message;
                Y[adjVertexId] = currentVertex;
            }
        }

        // Debug
        // cout << j << "th visit.  Visit node " << currentVertex << endl;
        // for (int i=1; i<=totalVertex; i++) {
        //     cout << M[i] << "  ";
        // }
        // cout << endl;


        // Decide the vertex to be visited
        float minDist = inf;
        for (int i=1; i<=totalVertex; i++) {
            if (D[i]<minDist && !(adjlist[i]->visited)) {
                minDist = D[i];
                currentVertex = i;
            }
        }
    }
    
    // Update the shortest distance from source to HQ
    shortestDist = D[headquarter];

    // Update total message
    totalMessage = M[headquarter];

    // Update the shortest PATH
    stack<int> path;

    currentVertex = headquarter;
    while (currentVertex != source) {
        currentVertex = Y[currentVertex];
        path.push(currentVertex);
    }
    
    while (!path.empty()) {
        shortestPath += adjlist[path.top()]->name;
        shortestPath += " -> ";
        path.pop();
    }
    shortestPath += adjlist[headquarter]->name;
}


int main() {
    
    string input;
    Graph network;

    while (getline(cin, input))
    {
        if (input == "ANALYZE")
            break;

        int pos = input.find(' ');
        string command = input.substr(0, pos);

        if (command == "INSERT") {
            // .find(<the str you want to find>, <start pos>)
            int pos1 = input.find(' ', pos+1);

            // .substr(<start pos>, <length of the substring>)
            string nodeType = input.substr(pos+1, (pos1-1)-pos);
            string name = input.substr(pos1+1);

            network.insertVertex(name, nodeType);
            // cout << "Inserting node of type " << nodeType << " with name " << name << endl;
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
            // cout << "Inserting edge between nodes " << id_number1 << " and " << id_number2 << " with total message " << total_message << endl;
        }
    }

    // cout << "source = " << network.getSource() << endl;
    // cout << "HQ = " << network.getHQ() << endl;

    // Do excute the Dijkstra alogrithm
    network.dijkstra(network.getSource());
    
    // Out put the results
    cout << network.getShortestPath() << "\n";
    cout << network.getTotalMessage() << "\n";
    cout << network.getShortestDist() << "\n";

    return 0;
}