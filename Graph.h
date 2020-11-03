#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    Graph(const Graph &other);  // copy constructor
    Graph& operator=(const Graph& other);   // copy assignment
    Graph()=default;    // default constructor
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);

    std::vector<int> getNeighbors(int nodeId) const;
    int getSize() const;
    void removeEdge(int node1, int node2);  // Used by contactTRacer [03/11]

private:
    std::vector<std::vector<int>> edges;
    std::vector<bool> infected; // used to track which nodes are infected
};

#endif