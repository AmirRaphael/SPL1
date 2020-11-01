#include "Graph.h"

Graph::Graph(std::vector<std::vector<int>> &matrix) : edges(matrix), infected(matrix.size(), false) {}

Graph::Graph(const Graph &other) : edges(other.edges), infected(other.infected) {}  // copy constructor

void Graph::infectNode(int nodeInd) {
    infected[nodeInd] = true;

//    infected[nodeInd] = true;

}

bool Graph::isInfected(int nodeInd) {
    return infected[nodeInd];
}

std::vector<int> Graph::getNeighbors(int nodeId) const {
    std::vector<int> neighbors {};
    for(int i {0};i < edges[nodeId].size();++i){
        if (edges[nodeId][i]==1){
            neighbors.push_back(i);
        }
    }

    return neighbors;
}

int Graph::getSize() const{
    return edges.size();
}

