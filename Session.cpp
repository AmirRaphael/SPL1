//
// Created by Amir Zaushnizer on 01/11/2020.
//

#include "Session.h"

int Session::getCycle() const {
    return cycle;
}

const Graph &Session::getG() const {
    return g;
}

const std::vector<Agent *> &Session::getAgents() const {
    return agents;
}
