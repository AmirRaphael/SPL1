#include "Agent.h"

Agent::Agent(Session &session) : session(session) {}

//========VIRUS=======
Virus::Virus(int nodeInd, Session &session) : Agent(session), nodeInd(nodeInd) {}

void Virus::act() {
    
}
//====================