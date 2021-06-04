// This program was made by Bannikov Nikita, group 9309
#include "Header.h"
#include <regex>
#include <iostream>
#include <fstream>

using namespace std;

class Util {
public:
    // Trims white-spaces and tabs
    static string trim(const string& str, const string& whitespace = " \t") {
        const auto strBegin = str.find_first_not_of(whitespace);
        if (strBegin == string::npos) {
            return ""; // no content
        }
        const auto strEnd = str.find_last_not_of(whitespace);
        const auto strRange = strEnd - strBegin + 1;

        return str.substr(strBegin, strRange);
    }

    // Split string by a delimeter
    static vector<string> split(const string& str, const string& delim) {
        vector<string> tokens;
        size_t prev = 0, pos = 0;
        do {
            pos = str.find(delim, prev);
            if (pos == string::npos) pos = str.length();
            string dirty_token = str.substr(prev, pos - prev);
            string token = trim(dirty_token);
            if (!token.empty()) tokens.push_back(token);
            prev = pos + delim.length();
        } while (pos < str.length() && prev < str.length());
        return tokens;
    }
};

// Adds an edge from node 'from' to node 'to' with certain price 
void Graph::addEdge(string from, string to, int price) {
    if (price < 0) {
        throw std::invalid_argument("Price must be positive");
    }

    string normalized_from = Util::trim(from);
    if (normalized_from.empty()) {
        throw std::invalid_argument("'from' shall not be empty");
    }

    string normalized_to = Util::trim(to);
    if (normalized_to.empty()) {
        throw std::invalid_argument("'to' shall not be empty");
    }

    int i_from = _nodePosition(normalized_from);
    int i_to = _nodePosition(normalized_to);

    _addEdge(i_from, i_to, price, normalized_from, normalized_to);
}

// Returns cost from/to on succes, if failed returns INT_MAX
int Graph::minimalCostBellmanFord(string from, string to) {
    int _from = _getNodeIndex(from);

    if (_from == -1) {
        throw std::invalid_argument("From not found");
    }

    int _to = _getNodeIndex(to);

    if (_to == -1) {
        throw std::invalid_argument("To not found");
    }

    int V = nodes.size();
    int E = edges.size();
    
    // Step 1: Initialize distances from src to all other vertices as INFINITE
    vector<int> dist(V);
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }
    dist[_from] = 0;

    // Step 2: Relax all edges |V| - 1 times. A simple shortest path from src
    // to any other vertex can have at-most |V| - 1 edges
    for (int i = 1; i <= V - 1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = edges[j].from;
            int v = edges[j].to;
            int price = edges[j].price;

            if (dist[u] != INT_MAX) {
                if (dist[u] + price < dist[v]) {
                    dist[v] = dist[u] + price;
                }
            }
        }
    }

    // Step 3: check for negative-weight cycles.
    for (int i = 0; i < E; i++)
    {
        int u = edges[i].from;
        int v = edges[i].to;
        int price = edges[i].price;
        if (dist[u] != INT_MAX && dist[u] + price < dist[v]) {
            return INT_MAX;
        }
    }
    return dist[_to];
}

// Adds an edge from node 'from' to node 'to' with certain price
void Graph::_addEdge(int from, int to, int price, string from_name, string to_name) {
    _resizeIfRequired();
    edges.push_back(Edge(from, to, price, from_name, to_name));
    g[from].push_back(edges.size() - 1);
    g[to].push_back(edges.size() - 1);
}

// Resize vectors if required
void Graph::_resizeIfRequired() {
    if (nodes.size() > g.size()) {
        g.resize(nodes.size());
    }
}

// Return an index of a node by name (if node is not found, -1 will be returned)
int Graph::_getNodeIndex(string node_name) {
    auto it = std::find(nodes.begin(), nodes.end(), node_name);
    if (it == nodes.end()) {
        return -1;
    }
    return std::distance(nodes.begin(), it);
}

// Adds (if required) a node by name, returning index int the nodes array
int Graph::_nodePosition(string node_name) {
    int index = _getNodeIndex(node_name);
    if (index == -1) {
        nodes.push_back(node_name);
        return nodes.size() - 1;
    }
    else {
        return index;
    }
}

// Loads graph from a file
//
// File format: 
//  1) a line is an edge: <from node name string>;<to node name string>;<price>;<price_back>
//  Price can be 'N/A'
//  2) Example of of lines: 
//      Madrid;Rome;10;20
//      Moscow;Chicago;N/A;1000
void Graph::load_from_file(const char* filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string str;
        int line_num = 0;
        while (std::getline(file, str)) {
            string delimiter = ";";
            vector<string> tokens = Util::split(str, delimiter);

            if (tokens.size() != 4) {
                throw std::invalid_argument("File invalid format");
            }
            else {
                string from = tokens.at(0);
                string to = tokens.at(1);
                string price = tokens.at(2);
                string price_back = tokens.at(3);

                if (price != "N/A") {
                    addEdge(from, to, std::stoi(price));
                }

                if (price_back != "N/A") {
                    addEdge(to, from, std::stoi(price_back));
                }
            }
        }
        file.close();
    }
    else {
        throw std::runtime_error("Can't open a file");
    }
}
