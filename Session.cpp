#include <iostream>
#include <fstream>
#include "Session.h"
#include "Agent.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

Session::Session(const std::string &path) {
    json j;
    std::ifstream i(path);
    i >> j;

    std::string type = j["tree"];
    if (type == "C") treeType = Cycle;
    else if (type == "M") treeType = MaxRank;
    else treeType = Root;

    for (auto item : j["agents"]){
        if (item[0] == "V"){
            agents.push_back(new Virus(item[1], *this));
        } else {
            agents.push_back(new ContactTracer(*this));
        }
    }
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

void Session::simulate() {
    std::cout << "Simulate" << std::endl;
}

int Session::getCycle() const {
    return cycle;
}

const Graph &Session::getG() const {
    return g;
}
