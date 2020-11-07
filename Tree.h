#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "Session.h"


//============Tree==============
class Tree{
public:
    Tree(int rootLabel);
    Tree(const Tree &other);   // copy constructor [06/11]
    Tree(Tree &&other);        // move constructor [06/11]
    const Tree& operator=(const Tree& other); // copy assignment
    const Tree& operator=(const Tree&& other); // move assignment
    virtual ~Tree();

    void addChild(const Tree& child);
    void addChild(Tree *child);
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    virtual Tree* clone() const=0;  // used in "addChild" method [03/11]
    int getNode() const;    // Added getter
    const std::vector<Tree *> &getChildren() const;    // Added getter
    void bfs(const Session &session);
    static Tree* compare(Tree *node1, Tree *node2); // used in maxRankTree::traceTree()
    int getTime() const;
    int getDepth() const;
    void setDepth(int _depth);
protected:
    int time;
    int depth;
private:
    int node;
    std::vector<Tree*> children;

};
//============CycleTree==============
class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    CycleTree(const CycleTree& other);   // copy constructor [03/11]
    CycleTree(CycleTree &&other);       // move constructor [03/11]
    virtual ~CycleTree();

    virtual int traceTree();
    virtual Tree* clone() const;    // Added[03/11]
private:
    int currCycle;
};
//============MaxRankTree==============
class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    MaxRankTree(const MaxRankTree& other);  // copy constructor [03/11]
    MaxRankTree(MaxRankTree &&other);   // move constructor [03/11]
    virtual ~MaxRankTree();

    virtual int traceTree();    //todo: Implement
    Tree* maxChild(int depth); // todo: change name of func
    virtual Tree* clone() const;    // Added [03/11]
};
//============RootTree==============
class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    RootTree(const RootTree& other);    // copy constructor [03/11]
    RootTree(RootTree &&other); // move constructor [03/11]
    virtual ~RootTree();

    virtual int traceTree();
    virtual Tree* clone() const;    // Added [03/11]
};

#endif