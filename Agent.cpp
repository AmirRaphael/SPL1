#include "Agent.h"
#include "Tree.h"


Agent::Agent() {}

Agent::~Agent() {}

//================Virus======================
Virus::Virus(int nodeInd):Agent(), nodeInd(nodeInd) {}


Virus::Virus(const Virus &other) : Agent(other), nodeInd(other.nodeInd) {}  // copy constructor [03/11]


Virus::~Virus(){}


void Virus::act(Session& session) {
    Graph graph (session.getG());   // todo: make sure this is efficient (maybe use move)
    if (!graph.isInfected(nodeInd)){
        graph.infectNode(nodeInd);
        session.enqueueInfected(nodeInd);
    }
    std::vector<int> neighbors = graph.getNeighbors(nodeInd);
    for(auto n : neighbors){
        if (!graph.isInfected(n) && !session.isCarrier(n)){
            Virus copyVirus(n);
            session.addAgent(copyVirus);
            session.makeCarrier(n);
            break;
        }
    }
    session.setGraph(graph);
}


Agent *Virus::clone() const { // creates a copy of the object on the heap and returns a pointer
    Agent *pClone = new Virus(*this);
    return pClone;
}
//===========================================
//=============ContactTracer=================
ContactTracer::ContactTracer() : Agent() {}


ContactTracer::ContactTracer(const ContactTracer &other) : Agent(other) {}


ContactTracer::~ContactTracer() {}


void ContactTracer::act(Session& session) {
    if(!session.getInfectedQueue().empty()) {
        int infectedNode = session.dequeueInfected();
        Tree *pTreeRoot = Tree::createTree(session, infectedNode);
        pTreeRoot->bfs(session);
        int isolateNode = pTreeRoot->traceTree();
        delete pTreeRoot;
        Graph graph(session.getG());    // todo: make sure this is efficient (maybe use move)
        std::vector<int> neighbors = graph.getNeighbors(isolateNode);
        for (auto neighbor : neighbors) {
            graph.removeEdge(isolateNode, neighbor);
        }
        session.setGraph(graph);
    }
}


Agent *ContactTracer::clone() const {
    Agent *pClone = new ContactTracer(*this);
    return pClone;
}