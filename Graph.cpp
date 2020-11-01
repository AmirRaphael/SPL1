#include "Graph.h"

Graph::Graph(std::vector<std::vector<int>> matrix) : edges(matrix), infected(matrix.size(), false) {}

Graph::Graph(const Graph &other) : edges(other.edges), infected(other.infected) {}  // copy constructor

Graph &Graph::operator=(const Graph &other) {
    edges = other.edges;
    infected = other.infected;
    return *this;
}

void Graph::infectNode(int nodeInd) {
    infected[nodeInd] = true;
}

bool Graph::isInfected(int nodeInd) {
    return infected[nodeInd];
}

