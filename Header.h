// This program was made by Bannikov Nikita, group 9309 
#pragma once
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>
#include <locale>
#include <stdexcept>

using namespace std;

class Edge {
public:
    int from, to;
    string from_name;
    string to_name;
    int price;

    Edge(int from, int to, int price, string from_name,
        string to_name) : from(from), to(to), price(price), from_name(from_name), to_name(to_name) {}

    int other(int node) const {
        return node == from ? to : from;
    }
};

class Graph {
    // Keeps nodes names
    vector<string> nodes;
    // Keeps edges
    vector<Edge> edges;
    // Keeps the graph
    vector<vector<int>> g;
public:
    // Constructor
    Graph() {
    }

    // Adds an edge from node 'from' to node 'to' with certain price 
    void addEdge(string from, string to, int price);
    
    // Calculate minimal cost from/to
    int minimalCostBellmanFord(string from, string to);

    // Loads graph from a file
    void load_from_file(const char* filename);
private:
    void _addEdge(int from, int to, int price, string from_name, string to_name);
    void _resizeIfRequired();
    int _getNodeIndex(string node_name);
    int _nodePosition(string node_name);
};
