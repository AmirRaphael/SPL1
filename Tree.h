#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "Session.h"



//============Tree==============
class Tree{
public:
    Tree(int rootLabel);
    Tree(const Tree &other);
    void addChild(const Tree& child);
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    static Tree* createChild(TreeType type,int label,int cycle);
private:
    int node;
    std::vector<Tree*> children;
};
//============CycleTree==============
class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
private:
    int currCycle;
};
//============MaxRankTree==============
class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
};
//============RootTree==============
class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
};

#endif