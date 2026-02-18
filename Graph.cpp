/*
 * This is the file for all the functions in the Graph class. Undirected, unweighted graphs are supported.
 */

/* 
 * File:   Graph.cpp
 * Author: Troy Krupinski
 */
#include "data.h"
#include "Graph.h"

Graph::Graph() {}

Graph::~Graph() {
    for (auto pair : nodes) { // Deconstructor, iterate through the nodes and delete them
        delete pair.second;
    }
    nodes.clear(); // Clear the map of nodes
    nodeIds.clear(); // Clear the set of node IDs
    edges.clear(); // Clear the set of edges
}

void Graph::addNode(int id, std::string data) {
    if (!nodeExists(id)) { // If node does not exist, add it
        Node* newNode = new Node(id, data); // Create a new node, allocate memory on the heap
        nodes[id] = newNode;
        nodeIds.insert(id); 
        std::cout << "Added Node " << id << std::endl; 
    } else {
        std::cout << "Node already exists." << std::endl; 
    }
}

void Graph::addEdge(int id1, int id2) {
    if (nodeExists(id1) && nodeExists(id2) && id1 != id2) { // Check if both nodes exist and are not the same node
        if (edges.find({id1, id2}) == edges.end() && edges.find({id2, id1}) == edges.end()) {
            nodes[id1]->adjacent.push_back(nodes[id2]);
            nodes[id2]->adjacent.push_back(nodes[id1]); // For undirected graph
            edges.insert({id1, id2});
            edges.insert({id2, id1}); // For undirected graph
            std::cout << "Added Edge between Node " << id1 << " and Node " << id2 << std::endl;
        } else {
            std::cout << "Edge already exists between Node "<< id1 << " and Node " << id2 << std::endl;
        }
    } else {
        std::cout << "One or both nodes do not exist, or are the same node. There cannot be an edge." << std::endl;
    }
}

int Graph::getNonExistentNodeId() {
    int nodeId = 0;
    while (nodeExists(nodeId)) { // Loop until a non-existent node ID is found
        ++nodeId;
    }
    return nodeId;
}


void Graph::removeNode(int id) {
    if (!nodeExists(id)) {
        std::cout << "Node does not exist." << std::endl;
        return;
    }

    // Remove edges connected to the node in the graph
    for (auto adjNode : nodes[id]->adjacent) {
        adjNode->adjacent.erase(std::remove(adjNode->adjacent.begin(), adjNode->adjacent.end(), nodes[id]), adjNode->adjacent.end()); // Remove the node from the adjacent nodes
        edges.erase({id, adjNode->id}); // Remove the edge from the set of edges
        edges.erase({adjNode->id, id}); // Remove both edges for undirected graph
    }

    // Delete node and remove from map
    delete nodes[id];
    nodes.erase(id);
    nodeIds.erase(id);
    std::cout << "Successfully removed Node " << id << std::endl;
}

void Graph::removeEdge(int id1, int id2) {
    if (nodeExists(id1) && nodeExists(id2)) {
        auto it1 = std::remove(nodes[id1]->adjacent.begin(), nodes[id1]->adjacent.end(), nodes[id2]); // Remove the node from the adjacent nodes
        auto it2 = std::remove(nodes[id2]->adjacent.begin(), nodes[id2]->adjacent.end(), nodes[id1]); 

        // Check if any edge was actually removed
        bool edgeRemoved = (it1 != nodes[id1]->adjacent.end()) || (it2 != nodes[id2]->adjacent.end());

        if (edgeRemoved) {
            nodes[id1]->adjacent.erase(it1, nodes[id1]->adjacent.end()); // Remove the node from the adjacent nodes
            nodes[id2]->adjacent.erase(it2, nodes[id2]->adjacent.end());
            std::cout << "Successfully removed edge between Node " << id1 << " and Node " << id2 << std::endl;
            edges.erase({id1, id2});
            edges.erase({id2, id1}); // Remove both edges for undirected graph
        } else {
            std::cout << "Edge does not exist." << std::endl;
        }
    } else {
        std::cout << "One or both nodes do not exist. There cannot be an edge." << std::endl;
    }
}


bool Graph::nodeExists(int id) {
    return nodes.find(id) != nodes.end(); // Check if node exists in the map
}

void Graph::displayGraph() {
    for (auto pair : nodes) { //iterate through the nodes and print the nodes and their adjacent nodes
        std::cout << "Node " << pair.first << ": ";
        for (Node* node : pair.second->adjacent) { //iterate through the nodes and print the nodes and their adjacent nodes
            std::cout << node->id << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::bfs(int startNodeId) { //breadth first search
    if (!nodeExists(startNodeId)) {
        std::cout << "Node does not exist. Cannot start bfs\n" << std::endl;
        return;
    }

    std::unordered_map<int, bool> visited; // Map of node IDs to whether they have been visited
    std::queue<int> queue;

    visited[startNodeId] = true;
    queue.push(startNodeId);

    while (!queue.empty()) { 
        int nodeId = queue.front(); 
        queue.pop();
        std::cout << nodeId << " "; // Print the node

        for (Node* neighbor : nodes[nodeId]->adjacent) { //iterate through the nodes and print the nodes and their adjacent nodes
            if (!visited[neighbor->id]) { // If neighbor has not been visited
                visited[neighbor->id] = true; // Mark neighbor as visited
                queue.push(neighbor->id); // Add neighbor to queue
            }
        }
    }
    std::cout << std::endl;
}

void Graph::dfs(int startNodeId) { //depth first search
    if (!nodeExists(startNodeId)) {
        std::cout << "Node does not exist. Cannot start dfs\n" << std::endl;
        return;
    }
    std::unordered_map<int, bool> visited; // Creating map of node IDs to whether they have been visited
    dfsUtil(startNodeId, visited); // Call the recursive helper function
    std::cout << std::endl;
}

void Graph::dfsUtil(int nodeId, std::unordered_map<int, bool>& visited) {
    visited[nodeId] = true; // Mark the current node as visited
    std::cout << nodeId << " ";

    for (Node* neighbor : nodes[nodeId]->adjacent) { //iterate through the nodes and print the nodes and their adjacent nodes
        if (!visited[neighbor->id]) {
            dfsUtil(neighbor->id, visited); //recursive call
        }
    }
}

int Graph::getNodeDegree(int id) {
    int degree = -1;
    if (nodeExists(id)) {
        degree = nodes[id]->adjacent.size(); // Get the number of adjacent nodes
    } else{
    std::cout<<"Node does not exist."<<std::endl;
    }
    return degree;
}

void Graph::listNodes() {
    for (const auto& pair : nodes) {
        if(pair.first>=10){ //formatting, if more than or equal to 10, print 2 spaces, else print 3 spaces
            std::cout << pair.first << "  ";
        }else{
        std::cout << pair.first << "   ";
        }
    }
    std::cout << std::endl;
}

bool Graph::isCyclicUtil(int node, std::unordered_map<int, bool>& visited, int parent) {
    visited[node] = true;
    bool cycleFound = false;
    for (auto neighbor : nodes[node]->adjacent) { //Iterate through the nodes
        if (!visited[neighbor->id]) { // If neighbor has not been visited
            if (isCyclicUtil(neighbor->id, visited, node)) { // If a cycle is found in the subtree rooted at neighbor
                cycleFound = true; // Mark cycle found
                break;
            }
        } else if (neighbor->id != parent) { // If neighbor has been visited and is not the parent of the current node
            cycleFound = true; // Mark cycle found
            break;
        }
    }
    return cycleFound;
}

int Graph::getRandomNodeId() {
    if (nodeIds.empty()) {
        return -1; // Return -1 or any other suitable value to indicate no nodes are available
    }

    std::size_t index = rand() % nodeIds.size(); // Generate a random index
    auto it = nodeIds.begin();
    std::advance(it, index); // Advance the iterator to the random position
    return *it; // Return the node ID at the random position
}

bool Graph::isCyclic() {
    std::unordered_map<int, bool> visited;
    bool hasCycle = false;
    for (const auto& pair : nodes) {
        if (!visited[pair.first] && isCyclicUtil(pair.first, visited, -1)) {
            hasCycle = true;
            break;
        }
    }
    return hasCycle;
}

bool Graph::isConnected() {
    if (nodes.empty()) return true; // An empty graph is connected
    std::unordered_map<int, bool> visited; // Map of node IDs to whether they have been visited
    dfsUtil(nodes.begin()->first, visited);
    bool connected = true;
    for (const auto& pair : nodes) { // Check if all nodes were visited
        if (!visited[pair.first]) {
            connected = false;
            break;
        }
    }
    return connected;
}

void Graph::printAdjacencyMatrix() {
    if (nodes.empty()) {
        std::cout << "The graph is empty." << std::endl;
        return;
    }

    // Create a map from node IDs to matrix indices
    std::unordered_map<int, int> nodeIdToIndex;
    int index = 0;
    for (const auto& pair : nodes) {
        nodeIdToIndex[pair.first] = index++;
    }
    
    int n = nodeIdToIndex.size();
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));
    // Loop through the nodes and their adjacent nodes, and set the corresponding matrix entries to 1
    for (const auto& pair : nodes) {
        int row = nodeIdToIndex[pair.first]; // Get the row index
        for (const Node* neighbor : pair.second->adjacent) { // Iterate through the adjacent nodes
            int col = nodeIdToIndex[neighbor->id]; // Get the column index
            matrix[row][col] = 1;  // Set the matrix entry to 1
        }
    }

    std::cout << "Adjacency Matrix:" << std::endl;
    listNodes();
    std::cout<<"-------------------------------------"<<std::endl;
    for (int i = 0; i < n; i++) { //iterate through the nodes and print the nodes and their adjacent nodes
        for (int j = 0; j < n; j++) { // 2d vector
            std::cout << matrix[i][j] << "   "; // Print the matrix
        }
        std::cout << std::endl;
    }
}



std::unordered_map<int, int> Graph::dijkstra(int startNodeId) { //shortest path
    std::unordered_map<int, int> distances;
    for (auto pair : nodes) {
        distances[pair.first] = INT_MAX; // Initialize all distances to infinity
    }
    distances[startNodeId] = 0; // Set distance from start node to itself to 0

    std::set<std::pair<int, int>> nodeSet; // (distance, nodeId)
    nodeSet.insert({0, startNodeId}); // Add start node to set

    while (!nodeSet.empty()) { 
        int nodeId = nodeSet.begin()->second; // Get node with smallest distance
        nodeSet.erase(nodeSet.begin());

        for (auto neighbor : nodes[nodeId]->adjacent) { 
            int alt = distances[nodeId] + 1; // All edges have weight 1, due it being unweighted
            if (alt < distances[neighbor->id]) {// If a shorter path to neighbor is found
                nodeSet.erase({distances[neighbor->id], neighbor->id}); // Remove neighbor from set
                distances[neighbor->id] = alt; // Update distance
                nodeSet.insert({distances[neighbor->id], neighbor->id}); // Add neighbor to set
            }
        }
    }
    return distances;
}
void Graph::addRandomNodes(int numberOfNodes) {
    for (int i = 0; i < numberOfNodes; ++i) {
        int id = rand() % 99; // Nodes can be fro 0 to 99
        if (nodeIds.find(id) == nodeIds.end()) {
            addNode(id, "Node" + std::to_string(id)); // Add node if it does not exist
        }
    }
}

void Graph::addRandomEdges(int numberOfEdges) {
    for (int i = 0; i < numberOfEdges; ++i) {
        auto it1 = nodeIds.begin();
        std::advance(it1, rand() % nodeIds.size());
        auto it2 = nodeIds.begin();
        std::advance(it2, rand() % nodeIds.size());
        
        if (*it1 != *it2) { // Check if the two nodes are not the same
            addEdge(*it1, *it2); // Add edge if it does not exist
        }
    }
}
std::pair<int, int> Graph::getRandomEdge() {
    if (edges.empty()) {
        return {-1, -1}; // Indicate no edge is available
    }

    auto it = edges.begin();
    std::advance(it, rand() % edges.size()); // Move iterator to a random position
    return *it; // Return the randomly selected edge
}








