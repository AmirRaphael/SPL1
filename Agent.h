#ifndef AGENT_H_
#define AGENT_H_

#include <vector>

class Session;
//============Agent==============
class Agent{
public:
    Agent(Session& session);
    virtual void act()=0;
private:
    Session& session;
};
//============ContactTracer==============
class ContactTracer: public Agent{
public:
    ContactTracer(Session& session);
    virtual void act();
};
//============Virus==============
class Virus: public Agent{
public:
    Virus(int nodeInd, Session& session);
    virtual void act();
private:
    const int nodeInd;
};

#endif
