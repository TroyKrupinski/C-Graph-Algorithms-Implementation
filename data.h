/*
 * This stores the data for the graph
 */

/* 
 * File:   data.h
 * Node class, stores the data for the nodes in the graph
 * Author: Troy Krupinski
 */
#ifndef GRAPH_DATA
#define GRAPH_DATA

#include <vector>
#include <string>
#include <iostream>

struct Node {
    int id;
    std::string data;
    std::vector<Node*> adjacent;
    Node(int id, std::string data) : id(id), data(data) {}
};

#define TESTDATA1 10
#define TESTDATA2 15

#endif
