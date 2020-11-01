#include "Agent.h"

Agent::Agent(Session &session) : session(session){

}

Virus::Virus(int nodeInd, Session &session): Agent(session),nodeInd(nodeInd) {

}

void Virus::act() {
    Graph graph (session.getG());
    graph.infectNode(nodeInd);
    //need to infect in the infected queue.
    std::vector<int> neighbors = graph.getNeighbors(nodeInd);
    for(auto n : neighbors){
        if (!graph.isInfected(n)){
            Virus* copyVirus = new Virus(n,session);
            session.addAgent(*copyVirus);
            break;
        }
    }
    session.setGraph(graph);

}