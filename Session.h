#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include <queue>
#include "Graph.h"

class Agent;

enum TreeType{
    Cycle,
    MaxRank,
    Root
};

class Session{
public:
    Session(const std::string& path);
    virtual ~Session();
    void simulate();    //todo: Implement
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    int getCycle() const;
    const Graph &getG() const;
    const std::queue<int> &getInfectedQueue() const;
    void createOutputJson(const std::vector<std::vector<int>> &gEdges, std::queue<int> infectedQ);

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::queue<int> infectedQueue;
    int cycle;
};

#endif