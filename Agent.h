#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"

//============Agent==============
class Agent{
public:
    Agent(Session& session);
    virtual void act()=0;
    virtual Agent* clone() const=0; // Used in "addAgent" method [03/11]
protected:
    Session& session;
};
//============ContactTracer==============
class ContactTracer: public Agent{
public:
    ContactTracer(Session& session);
    ContactTracer(const ContactTracer& other);  //copy constructor [03/11]
    virtual void act();
    virtual Agent* clone() const;
};
//============Virus==============
class Virus: public Agent{
public:
    Virus(int nodeInd, Session& session);
    Virus(const Virus& other);  // copy constructor [03/11]
    virtual void act();
    virtual Agent* clone() const;
private:
    const int nodeInd;
};

#endif