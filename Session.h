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
    void createOutputJson();
    bool isCarrier(int nodeIndex);  //Added [6/11]
    void makeCarrier(int nodeIndex);//Added [6/11]
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::queue<int> infectedQueue;
    int cycle;
    std::vector<bool> carriers;  // used to keep track which nodes carry a virus (including those which aren't infected)
};

#endif