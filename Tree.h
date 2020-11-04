#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "Session.h"



//============Tree==============
class Tree{
public:
    Tree(int rootLabel);
    Tree(const Tree &other);   // copy constructor [03/11]
    Tree(Tree &&other);        // move constructor [03/11]
    virtual ~Tree();

    void addChild(const Tree& child);
    void addChild(Tree* child);
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    void bfs(const Session& session);
    virtual Tree* clone() const=0;  // used in "addChild" method [03/11]
    static Tree* compare(Tree *node1, Tree *node2); // used in maxRankTree::traceTree()
    int getTime() const;

    int getDepth() const;

    int getNode() const;    // Added getter
    const std::vector<Tree *> &getChildren() const;    // Added getter
    void setDepth(int _depth);

protected:
    int time;
    int depth;
private:
    int node;
    std::vector<Tree*> children;
    //int depth;
    //int time;
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

    virtual int traceTree();
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