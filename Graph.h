#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include "Tree.h"

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    Graph(const Graph &other);  // copy constructor
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
private:
    std::vector<std::vector<int>> edges;
    std::vector<bool> infected; // used to track which nodes are infected
};

#endif
