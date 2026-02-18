/*
 * This is the file for all the proto functions in the Graph class. Undirected, unweighted graphs are supported.
 */

/* 
 * File:   Graph.h
 * Author: Troy Krupinski
 */
#ifndef GRAPH_HEADER
#define GRAPH_HEADER
#include "data.h"
#include <unordered_map>
#include <random>
#include <algorithm>
#include <queue>
#include <set>
#include <random>

class Graph {
public:
    Graph();
    ~Graph();

    // Newly added methods
    void addRandomNodes(int);
    void addRandomEdges(int);
    void removeNode(int); // Removed the second parameter
    void removeEdge(int, int);
    int getRandomNodeId();
    int getNonExistentNodeId();
    std::pair<int, int> getRandomEdge();


    // Pre-existing methods
    void displayGraph();
    void addNode(int, std::string); 
    void addEdge(int, int);
    void bfs(int); 
    void dfs(int);
    void printAdjacencyMatrix();
    int getNodeDegree(int);
    void listNodes();
    bool isCyclic(); 
    bool isConnected();
    std::unordered_map<int, int> dijkstra(int); // Shortest path algorithm

private:
    std::unordered_map<int, Node*> nodes;
    std::set<int> nodeIds; // NodeIds are stored in a set for easy access
    std::set<std::pair<int, int>> edges; // Node edges are stored in a set for easy access

    //  helper methods
    bool nodeExists(int);
    void removeNodeHelper(int); 
    void removeEdgeHelper(int, int); 

    // Utility methods
    void dfsUtil(int, std::unordered_map<int, bool>&);
    bool isCyclicUtil(int, std::unordered_map<int, bool>&, int);
};

#endif // GRAPH_HEADER
