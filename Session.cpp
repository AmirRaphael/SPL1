#include <iostream>
#include <fstream>
#include "Session.h"
#include "Agent.h"
#include "json.hpp"


using json = nlohmann::json;


Session::Session(const std::string &path) : g(), treeType(), agents(), infectedQueue(), carriers(), cycle(0) {
    json j;
    std::ifstream i(path);
    i >> j;
    // set treeType
    std::string type = j["tree"];
    if (type == "C") treeType = Cycle;
    else if (type == "M") treeType = MaxRank;
    else treeType = Root;
    // set Graph
    int gSize = (int)j["graph"].size();
    std::vector<std::vector<int>> gMatrix(gSize,std::vector<int>(gSize,-1));
    for (int k = 0; k < gSize; ++k) {
        for (int l = 0; l < gSize; ++l) {
            gMatrix[k][l] = j["graph"][k][l];
        }
    }
    g = Graph(gMatrix);
    // init carriers vector
    carriers = std::vector<bool>(gSize, false);
    // set Agents
    for (auto item : j["agents"]){
        if (item[0] == "V"){
            int nodeIndex = (int)item[1];
            agents.push_back(new Virus(nodeIndex));
            carriers[nodeIndex] = true;
        } else {
            agents.push_back(new ContactTracer());
        }
    }
}

Session::Session(const Session &other) : g(other.g), treeType(other.treeType), agents(), infectedQueue(other.infectedQueue), carriers(other.carriers), cycle(other.cycle){
    for(auto agent : other.agents) {
        addAgent(*agent);
    }
}


Session::Session(const Session &&other) : g(other.g), treeType(other.treeType), agents(), infectedQueue(other.infectedQueue), carriers(other.carriers), cycle(other.cycle){
    for(auto agent : other.agents) {
        Agent* pAgent = agent;
        agents.push_back(pAgent);
        agent = nullptr;
    }
}


const Session &Session::operator=(const Session &other) {
    g = other.g;
    treeType = other.treeType;
    infectedQueue = other.infectedQueue;
    carriers = other.carriers;
    cycle = other.cycle;
    for (auto agent : agents){
        delete agent;
    }
    agents.clear();
    for (auto otherAgent : other.agents) {
        addAgent(*otherAgent);
    }
    return *this;
}


const Session &Session::operator=(Session &&other) {
    g = other.g;
    treeType = other.treeType;
    infectedQueue = other.infectedQueue;
    carriers = other.carriers;
    cycle = other.cycle;
    for (auto agent : agents){
        delete agent;
    }
    agents.clear();
    for(auto otherAgent : other.agents) {
        Agent* pAgent = otherAgent;
        agents.push_back(pAgent);
        otherAgent = nullptr;
    }
    return *this;
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
            agents[i]->act(*this);
        }
        terminate = g.condition(*this);
        cycle++;
    }
    createOutputJson();
}


void Session::createOutputJson() {
    json jOutput;
    jOutput["graph"] = {};
    const std::vector<std::vector<int>> &gEdges = g.getEdges();
    size_t gSize = g.getSize();
    for (size_t i = 0; i < gSize; ++i) {
        for (size_t j = 0; j < gSize; ++j) {
            jOutput["graph"][i][j] = gEdges[i][j];
        }
    }
    jOutput["infected"] = {};
    for (size_t nodeIndex = 0; nodeIndex < gSize; ++nodeIndex) {
        if (g.isInfected(nodeIndex))
            jOutput["infected"].push_back(nodeIndex);
    }
    std::ofstream o("./output.json");
    o << jOutput << std::endl;
}


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


bool Session::isCarrier(int nodeIndex) const {    //Added [6/11]
    return carriers[nodeIndex];
}


void Session::makeCarrier(int nodeIndex) {  //Added [6/11]
    carriers[nodeIndex] = true;
}
