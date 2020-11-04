// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <map>
#include <vector>
#include <strstream>
#include <sstream>


class Vertex;
using namespace std;

class Edge
{
public:
    shared_ptr<Vertex> dest;
    int flow;
    int capacity;

    Edge()
    {
        dest = nullptr;
        flow = 0;
        capacity = 0;
    }

    Edge(shared_ptr<Vertex> d, int c)
    {
        dest = d;
        capacity = c;
        flow = 0;
    }
};

class Vertex
{
public:
    int key;
    // vector<Edge>* adj = new vector<Edge>;
    vector<shared_ptr<Edge>> adj;

	// Vertex(){}

    Vertex(int n)
    {
        key = n;
    }

	string toString()
    {
        stringstream ss;
        ss << key << " [ ";
        for (auto item : adj)
        {
            ss << item->dest->key << "(" << item->capacity << ") ";
        }
        ss << "]";
        return ss.str();
    }
	
};

class Graph
{
public:
    map<int, shared_ptr<Vertex>> vertexMap;

    Graph()
    {
        // vertexMap = new map<int, Vertex*>;
        vertexMap = map<int, shared_ptr<Vertex>>();
    }

    void addVertex(int key)
    {
        if (vertexMap.find(key) != vertexMap.end())
            return;
        vertexMap.try_emplace(key, make_shared<Vertex>(key));
    }

    shared_ptr<Vertex> &getVertex(int key)
    {
        addVertex(key);
        return vertexMap[key];
    }

    void addEdge(int source, int dest, int capacity = 0)
    {
        shared_ptr<Vertex> s = getVertex(source);
        shared_ptr<Vertex> d = getVertex(dest);
        if (s->key == d->key)
            return;
        s->adj.emplace_back(make_shared<Edge>(d, capacity));
    }

	string toString()
    {
        stringstream ss;
	    for(auto item : vertexMap)
	    {
            ss << item.second->toString() << "\n";
	    }
        return ss.str();
    }
};



shared_ptr<Graph> createGraph()
{
	// ============ Local variables
    shared_ptr<Graph> graph = make_shared<Graph>();
	
    int nrCities;
    int nrRoads;
    int nrEndangered;
    int nrDesignated;
    vector<int> endangeredCities;
    vector<int> designatedCities;

	// ============ Line 1 -- nrCities & nrRoads
    cin >> nrCities >> nrRoads;
	// ============ Line 2 -- nrEndangered & nrDesignated
    cin >> nrEndangered >> nrDesignated;
	// ============ line 3 -- All endangered cities
    for (int i = 0; i < nrEndangered; ++i)
    {
        int hlp;
        cin >> hlp;
        endangeredCities.push_back(hlp);
    }
	// ============ line 4 -- All designated cities
    for (int i = 0; i < nrDesignated; ++i)
    {
        int hlp;
        cin >> hlp;
        designatedCities.push_back(hlp);
    }

	// ============ create graph with vertices

	// ------ start vertex
    graph->addVertex(designatedCities[0]);
	// point all indices of designated cities to a single vertex with the first key in designatedCities
    for (int i = 1; i < nrDesignated; ++i)
    {
        graph->vertexMap.try_emplace(designatedCities[i], graph->getVertex(designatedCities[0]));
    }
	
    // ------ sink vertex
    graph->addVertex(endangeredCities[0]);
    // point all indices of endangered cities to a single vertex with the first key in endangeredCities
    for (int i = 1; i < nrEndangered; ++i)
    {
        graph->vertexMap.try_emplace(endangeredCities[i], graph->getVertex(endangeredCities[0]));
    }

	// ------ default cities not endangered or designated
    for (int i = 0; i < nrCities; ++i) // TODO room for improvement don't need to loop through nr of cities and both the endangered and designated arrays
    {
        graph->addVertex(i); // addVertex checks if it already exists
    }
	
	// ============ Line 5 & greater then 5 -- all roads
    for (int i = 0; i < nrRoads; ++i)
    {
        int source;
    	int destination;
        int capacity;
        cin >> source >> destination >> capacity;
        graph->addEdge(source, destination, capacity);
    }
    
	// ============ Print all
    cout << "====== Variables" << endl;
	cout << "nrCities:          " << nrCities << endl;
	cout << "nrRoads:           " << nrRoads << endl;
	cout << "nrEndangered:      " << nrEndangered << endl;
	cout << "nrDesignated:      " << nrDesignated << endl;
	cout << "endangeredCities:  ";
	for (auto i : endangeredCities)
		cout << i << " ";
	cout << endl;
	cout << "designatedCities   ";
	for (auto i : designatedCities)
		cout << i << " ";
    cout << endl;
    cout << "====== Graph" << endl;
    cout << graph->toString();
	


    return graph;
}

int main()
{
    shared_ptr<Graph> g = createGraph();
	// TODO use flow algorithm on graph
	
    return 0;
}

