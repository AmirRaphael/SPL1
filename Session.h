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
    Session(const std::string& path); // constructor
    Session(const Session& other);// copy constructor
    Session(const Session&& other);// move constructor
    const Session& operator=(const Session& other);//copy assignment
    const Session& operator=(Session&& other);//move assignment


    virtual ~Session(); // destructor
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
    bool isCarrier(int nodeIndex) const;  //Added [6/11]
    void makeCarrier(int nodeIndex);//Added [6/11]
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::queue<int> infectedQueue;
    std::vector<bool> carriers;  // used to keep track which nodes carry a virus (including those which aren't infected)
    int cycle;
};

#endif