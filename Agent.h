#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"

//============Agent==============
class Agent{
public:
    Agent();
    virtual void act(Session& session)=0;
    virtual Agent* clone() const=0; // Used in "addAgent" method [03/11]
    virtual ~Agent();
//protected:
//    Session& session;
};
//============ContactTracer==============
class ContactTracer: public Agent{
public:
    ContactTracer();
    ContactTracer(const ContactTracer& other);  //copy constructor [03/11]
    virtual ~ContactTracer();
    virtual void act(Session& session);
    virtual Agent* clone() const;
};
//============Virus==============
class Virus: public Agent{
public:
    Virus(int nodeInd);
    Virus(const Virus& other);  // copy constructor [03/11]
    virtual ~Virus();
    virtual void act(Session& session);
    virtual Agent* clone() const;
private:
    const int nodeInd;
};

#endif