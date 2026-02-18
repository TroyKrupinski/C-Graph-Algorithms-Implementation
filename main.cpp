/*
 * This is the main file for random testing of the Graph class. Undirected, unweighted graphs are supported.
 */

/* 
 * File:   Graph.cpp
 * Author: Troy Krupinski
 */
#include "main.h"
#include <iostream>
#include <ctime>

int main() {

    srand(time(nullptr)); // Initialize random seed
    
    std::cout << "\nAuthor: Troy Krupinski\n";
    std::cout << "\nCOSC2436-004 Fall 2023 Final\n";
    std::cout << "\nThis program demonstrates an undirected unweighted Graph with developer testing.\n";
    std::cout << "\nThis program demonstrates the following:";
    std::cout << "\n1. Adding random nodes and edges to the graph.";
    std::cout << "\n2. Removing random nodes and edges from the graph.";
    std::cout << "\n3. Checking if the graph is cyclic.";
    std::cout << "\n4. Checking if the graph is connected.";
    std::cout << "\n5. Running Dijkstra's Algorithm on the graph.";
    std::cout << "\n6. Running BFS on the graph.";
    std::cout << "\n7. Running DFS on the graph.";
    std::cout << "\n8. Getting the degree of a node in the graph.";
    std::cout << "\n9. Listing all nodes in the graph.";
    std::cout << "\n10. Printing the adjacency matrix of the graph.";
    std::cout << "\n11. Adding a node to the graph.";
    std::cout << "\n12. Adding an edge to the graph.";
    std::cout << "\n13. Removing a node from the graph.";
    std::cout << "\n14. Removing an edge from the graph.";
    std::cout << "\n15. Displaying the graph.";
    std::cout << "\n16. Displaying the degree of a node in the graph.";       
    std::cout << "\n17. Has the ability to add multiple graphs, not employed.";
    std::cout << "\n18. Developer testing.\n";
    std::cout <<" \nThis test program only uses one graph and demonstrates all features present in the graph class.\n";
    std::cout <<"\n=====================================\n"<<std::endl;

    std::vector<std::unique_ptr<Graph>> graphs; // Vector to store multiple graphs
    graphs.push_back(std::make_unique<Graph>()); // Add a new graph (test graph) to the vector, initialized with 0 nodes and 0 edges
    std::cout<<"Initializing Graph with 0 nodes and 0 edges:\n";
    Graph& g = *graphs.back(); // Reference to the graph. This is the graph we will be working with, can add more graphs!

    g.displayGraph();
    // Adding random nodes and edges
    std::cout<<"\nAdding random nodes (if duplicate, do not add):\n";
    g.addRandomNodes(TESTDATA1); // Add a fixed number of random nodes. Can be changed to add a random number of nodes
    std::cout<<"\nAdding random edges (if duplicate, do not add):\n";
    g.addRandomEdges(TESTDATA2); // Add a fixed number of random edges after adding edgesm can be changed to add a random number of edges
    int randomNodeId = g.getRandomNodeId(); // Get random node ID from Graph class after adding nodes

    // Display the initial state of the graph
    std::cout<<"\n====================================="<<std::endl;    
    std::cout << "\nInitial Graph State:\n";
    g.displayGraph();
    std::cout<<"=====================================\n"<<std::endl;

    // Perform various graph operations
    // Display the final state of the graph
    std::cout << "\nInitial Graph Adjacency Matrix:\n";
    g.printAdjacencyMatrix();

    // Perform various graph operations like checking for cycles, connectivity, 
    // running Dijkstra's algorithm, BFS, DFS, etc.

    std::cout << "\nChecking if the graph has a cycle:\n";
    std::cout << (g.isCyclic() ? "The graph has a cycle." : "The graph does not have a cycle.") << std::endl;

    std::cout << "\nChecking if the graph is connected:\n";
    std::cout << (g.isConnected() ? "The graph is connected." : "The graph is not connected.") << std::endl;

    // Demonstrate Dijkstra's Algorithm
    int startNodeId = g.getRandomNodeId(); // This would be a new method in Graph to get a random node ID
    if (startNodeId != -1) { // Assuming -1 denotes no valid ID was found
        std::cout << "\nPerforming Dijkstra's Algorithm from Node " << startNodeId << ":\n";
        auto distances = g.dijkstra(startNodeId);
        for (const auto& pair : distances) {
            std::cout << "Distance from Node " << startNodeId << " to Node " << pair.first << " is ";
            if (pair.second == INT_MAX) {
                std::cout << "infinity / unreachable";
            } else {
                std::cout << pair.second;
            }
            std::cout << std::endl;
        }
    }
    if (randomNodeId != -1) {
        std::cout << "\nPerforming BFS from Node " << randomNodeId << ":\n";
        g.bfs(randomNodeId);

        std::cout << "\nPerforming DFS from Node " << randomNodeId << ":\n";
        g.dfs(randomNodeId);
    }
    int nonExistentNode = g.getNonExistentNodeId(); // Implementation needed in Graph class
    std::cout << "\nAttempting to remove a non-existent node: Node " << nonExistentNode << std::endl;
    g.removeNode(nonExistentNode);

    // Attempting to remove a non-existent edge
    std::cout << "\nAttempting to remove a non-existent edge between Node " << nonExistentNode << " and Node " << nonExistentNode + 1 << std::endl;
    g.removeEdge(nonExistentNode, nonExistentNode + 1);

    // Attempting to add nodes and edges that already exist
 // Randomly select and remove an edge
    std::cout << "\nRandomly selecting an existing edge to be removed." << std::endl;
    auto edgeToRemove = g.getRandomEdge(); 
    if (edgeToRemove.first != -1) {
        std::cout << "Removing Edge between Node " << edgeToRemove.first << " and Node " << edgeToRemove.second << std::endl;
        g.removeEdge(edgeToRemove.first, edgeToRemove.second);
    }

    // Randomly select and remove a node
    std::cout << "\nRandomly selecting an existing node to be removed." << std::endl;
    int removeNodeId = g.getRandomNodeId();
    if (removeNodeId != -1) {
        std::cout << "Removing Node " << removeNodeId << std::endl;
        g.removeNode(removeNodeId);
    }
    std::cout<<"\n====================================="<<std::endl;
    // Display the graph after removals
    std::cout << "\nGraph after removals:" << std::endl;
    g.displayGraph();
    std::cout<<"=====================================\n"<<std::endl;

    // Randomly select a start node for BFS and DFS
    int startNode = g.getRandomNodeId();
    if (startNode != -1) {
        // BFS and DFS from the randomly selected node
        std::cout << "\nPerforming BFS from Node " << startNode << ":\n";
        g.bfs(startNode);

        std::cout << "\nPerforming DFS from Node " << startNode << ":\n";
        g.dfs(startNode);

        // Display degree of the node
        std::cout << "Degree of Node " << startNode << ": " << g.getNodeDegree(startNode) << std::endl;
    }

    // Listing all nodes in the graph
    std::cout << "\nListing all nodes in the graph:\n";
    g.listNodes();

    // Attempt BFS and DFS from a non-existent node
    std::cout << "\nAttempting to perform BFS and DFS from a non-existent node: Node " << nonExistentNode << std::endl;
    g.bfs(nonExistentNode);
    g.dfs(nonExistentNode);
    
    std::cout<<"Getting Node Degree from a random existing node:\n";
    int nodeDegree = g.getNodeDegree(randomNodeId);
    std::cout<<"Node Degree of Node "<<randomNodeId<<" is "<<nodeDegree<<std::endl;

    std::cout<<std::endl;
    

    std::cout<<"Getting Node Degree from a non-existent node:\n";
    nodeDegree = g.getNodeDegree(nonExistentNode);
    std::cout<<"Node Degree of Node "<<nonExistentNode<<" is "<<nodeDegree<<std::endl;

    std::cout << "\nAttempting to add a node that already exists:" << std::endl;
    int existingNodeId = g.getRandomNodeId();
    if (existingNodeId != -1) {
        std::cout << "Adding Node " << existingNodeId << std::endl;
        g.addNode(existingNodeId, "Node" + std::to_string(existingNodeId));
    }   

    // Attempting to add an edge that already exists
    std::cout << "\nAttempting to add an edge that already exists:" << std::endl;
    std::pair<int, int> existingEdge = g.getRandomEdge();
    if (existingEdge.first != -1) {
        std::cout << "Adding Edge between Node " << existingEdge.first << " and Node " << existingEdge.second << std::endl;
        g.addEdge(existingEdge.first, existingEdge.second);
    }
    std::cout<<"\n====================================="<<std::endl;

    // Print adjacency matrix after removals and algorithm tests
    std::cout << "Adjacency matrix after removals and algorithm tests:\n";
    std::cout<<std::endl;
    g.printAdjacencyMatrix();
    std::cout<<"=====================================\n"<<std::endl;
    std::cout<<"Graph after removals and algorithm tests:\n";
    g.displayGraph();
    std::cout<<"=====================================\n"<<std::endl;
    // Can add more graphs to the vector and perform operations on them
    
    
return 0;
}

