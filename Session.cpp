#include <iostream>
#include <fstream>
#include "Session.h"
#include "Agent.h"
#include "json.hpp"

using json = nlohmann::json;

Session::Session(const std::string &path) : g(), treeType(), agents(), infectedQueue(), cycle(0) {   //Added member init list [02/11]
    json j;
    std::ifstream i(path);
    i >> j;
    // set treeType
    std::string type = j["tree"];
    if (type == "C") treeType = Cycle;
    else if (type == "M") treeType = MaxRank;
    else treeType = Root;
    // set Agents
    for (auto item : j["agents"]){
        if (item[0] == "V"){
            agents.push_back(new Virus(item[1], *this));
        } else {
            agents.push_back(new ContactTracer(*this));
        }
    }// set Graph
    int gSize = (int)j["graph"].size();
    std::vector<std::vector<int>> gMatrix(gSize,std::vector<int>(gSize,-1));
    for (int k = 0; k < gSize; ++k) {
        for (int l = 0; l < gSize; ++l) {
            gMatrix[k][l] = j["graph"][k][l];
        }
    }
    Graph graph(gMatrix);
    g = graph; //Copy assignment
}

Session::~Session() {
    for (auto agent : agents) {
        delete agent;
    }
}

void Session::simulate() {
    bool terminate {false};
    while (!terminate){
        size_t numOfAgents {agents.size()};
        for(size_t i {0};i<numOfAgents;++i){
            agents[i]->act();
        }
        terminate = g.condition();
        cycle++;
    }
    createOutputJson();
}
//todo: implement
/*void Session::createOutputJson(const std::vector<std::vector<int>> &gEdges, std::queue<int> infectedQ) {
    json jOutput;
    jOutput["graph"] = {};
    size_t gSize = gEdges.size();
    for (size_t i = 0; i < gSize; ++i) {
        for (size_t j = 0; j < gSize; ++j) {
            jOutput["graph"][i][j] = gEdges[i][j];
        }
    }
    jOutput["infected"] = {};
    size_t qSize = infectedQ.size();
    for (int i = 0; i < qSize; ++i) {
        jOutput["infected"][i] = infectedQ.front();
        infectedQ.pop();
    }
    std::ofstream o("output.json");
    o << jOutput << std::endl;
}*/

int Session::getCycle() const {
    return cycle;
}

const Graph &Session::getG() const {
    return g;
}

void Session::setGraph(const Graph &graph) {    // Added implementation [03/11]
    g = graph;
}

void Session::addAgent(const Agent &agent) {    // Added implementation [03/11]
    Agent *pAgent = agent.clone();  // Dynamic memory allocation of Agent happens in clone()
    agents.push_back(pAgent);
}

void Session::enqueueInfected(int nodeIndex) {
    infectedQueue.push(nodeIndex);
}

int Session::dequeueInfected() {
    int nodeIndex = infectedQueue.front();
    infectedQueue.pop();
    return nodeIndex;
}

TreeType Session::getTreeType() const {
    return treeType;
}

const std::queue<int> &Session::getInfectedQueue() const {
    return infectedQueue;
}
