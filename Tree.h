#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session; //added by Raphael - Session was used in the file but not defined

//============Tree==============
class Tree{
public:
    Tree(int rootLabel);
    void addChild(const Tree& child);


    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
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
