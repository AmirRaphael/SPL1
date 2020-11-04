#include "Graph.h"

Graph::Graph(std::vector<std::vector<int>> matrix) : edges(matrix), infected(matrix.size(), false) {}

Graph::Graph(const Graph &other)  = default;  // copy constructor

Graph &Graph::operator=(const Graph &other) {   // copy assignment
    if (this == &other) {return *this;}
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

std::vector<int> Graph::getNeighbors(int nodeId) const {
    std::vector<int> neighbors {};
    for(int i {0};i < edges[nodeId].size();++i){
        if (edges[nodeId][i]==1){
            neighbors.push_back(i);
        }
    }
    return neighbors;
}

int Graph::getSize() const{return edges.size();}

void Graph::removeEdge(int node1, int node2) {
    int matrixSize = getSize();
    if (node1 < matrixSize && node2 < matrixSize){
        edges[node1][node2] = 0;
        edges[node2][node1] = 0;
    }
}

bool Graph::condition() {
    int size = this->getSize();
    bool check {true};
    std::vector<char> color (size,'w');
    for (int i {0};i<size && check;++i){
        if (color[i]=='w'){
            bool sick {isInfected(i)};
            check = dfsVisit(i,sick,color);
        }
    }
    return check;

}

bool Graph::dfsVisit(int i, bool sick, std::vector<char> &color) {
    color[i] = 'g';
    std::vector<int> neighbors(this->getNeighbors(i));
    for (auto node : neighbors ){
        if (color[node]=='w'){
            if(sick!=isInfected(node)) return false;
            else dfsVisit(node,sick,color);
        }
    }
    color[i]='b';
    return true;
}
