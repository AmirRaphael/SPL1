#include "Tree.h"
#include "Session.h"
#include <queue>


Tree::Tree(int rootLabel) : time(-1), depth(0), node(rootLabel), children() {}


Tree::Tree(const Tree &other) : time(other.time), depth(other.depth), node(other.node), children() {
    for (auto child : other.children) {
        addChild(*child); // -used original addchild.
    }
}

Tree::Tree(Tree &&other) :  time(other.time), depth(other.depth), node(other.node), children() {
    for (auto child : other.children) {
        Tree* pChild = child;
        children.push_back(pChild);
        child = nullptr;
    }
}


const Tree &Tree::operator=(const Tree &other) {
    if (this!=&other){
        time = other.time;
        depth = other.depth;
        node = other.node;
        for (auto child : children){
            if (child && child!=&other){ // edge case when assigning node to be one of its children.
                delete child;
            }
        }
        children.clear();
        for (auto otherChild : other.children) {
            addChild(*otherChild); // -used original addchild.
        }
    }
    return *this;
}

const Tree &Tree::operator=(Tree &&other) {
    time = other.time;
    depth = other.depth;
    node = other.node;
    for (auto child : children){
        if (child){
            delete child;
        }
    }
    children.clear();
    for (auto otherChild : other.children) {
        Tree* pChild = otherChild;
        children.push_back(pChild);
        otherChild = nullptr;
    }
    return *this;
}


Tree::~Tree() {
    for (auto subTree : children){
        delete subTree;
    }
}


void Tree::addChild(const Tree &child) {
    Tree *pTree = child.clone();
    children.push_back(pTree);
}


void Tree::addChild(Tree *child) {
    children.push_back(child);
}


Tree* Tree::createTree(const Session &session, int rootLabel) {
    Tree *tree;
    switch (session.getTreeType()) {
        case Cycle:
            tree = new CycleTree(rootLabel, session.getCycle());
            break;
        case MaxRank:
            tree = new MaxRankTree(rootLabel);
            break;
        case Root:
            tree = new RootTree(rootLabel);
            break;
    }
    return tree;
}


void Tree::bfs(const Session &session) {
    const Graph &graph = session.getG();
    std::queue<Tree*> bfsQueue;
    bfsQueue.push(this);
    int count = 0;
    std::vector<bool> visited (graph.getSize(), false); // array that keeps track of visited nodes in the bfs algorithm.
    visited[this->getNode()] = true;
    while (!(bfsQueue.empty())){
        Tree* u = bfsQueue.front();
        u->time = count;
        bfsQueue.pop();
        std::vector<int> neighbors {graph.getNeighbors(u->node)};
        for(auto n : neighbors){
            if (!visited[n]){
                visited[n]=true;
                Tree *child = createTree(session, n);
                u->addChild(child);
                bfsQueue.push(child);
            }
        }
        count++;
    }
}


int Tree::getNode() const {
    return node;
}


const std::vector<Tree *> &Tree::getChildren() const {
    return children;
}


int Tree::getTime() const {
    return time;
}


int Tree::getDepth() const {
    return depth;
}


Tree *Tree::compare(Tree *node1, Tree *node2) {
    if (node1 == node2) {return node1;}
    if (node1->getChildren().size() == node2->getChildren().size()){
        if (node1->getDepth() == node2->getDepth()){
            if (node1->getTime() < node2->getTime()){
                return node1;
            } else {
                return node2;
            }
        } else { // node1->depth != node2->depth
            if (node1->getDepth() < node2->getDepth()){
                return node1;
            } else {
                return node2;
            }
        }
    } else { // node1->size != node2->size
        if (node1->getChildren().size() > node2->getChildren().size()){
            return node1;
        } else {
            return node2;
        }
    }
}


void Tree::setDepth(int _depth) {
    Tree::depth = _depth;
}

//=====================CycleTree====================
CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {}


CycleTree::CycleTree(const CycleTree &other) : Tree(other), currCycle(other.currCycle) {}   // copy constructor [03/11]


CycleTree::CycleTree(CycleTree &&other) : Tree(std::move(other)), currCycle(std::move(other.currCycle)) {} // move constructor [03/11]


CycleTree::~CycleTree() {}


int CycleTree::traceTree() {    // Implemented [03/11]
    Tree *pCurrNode = this;
    bool lastNode = false;
    for (int i = 0; i < currCycle && !lastNode; ++i) {
        if (!pCurrNode->getChildren().empty()){
            pCurrNode = pCurrNode->getChildren().front();
        } else {
            lastNode = true;
        }
    }
    return pCurrNode->getNode();
}


Tree *CycleTree::clone() const { // creates a copy of the object on the heap and returns a pointer [03/11]
    Tree *pClone = new CycleTree(*this);
    return pClone;
}


//==================================================
//=====================MaxRankTree==================
MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}


MaxRankTree::MaxRankTree(const MaxRankTree &other) : Tree(other) {}


MaxRankTree::MaxRankTree(MaxRankTree &&other) : Tree(std::move(other)) {}


MaxRankTree::~MaxRankTree() {}


int MaxRankTree::traceTree() {
    Tree* maxNode = this->maxChild(1);
    return maxNode->getNode();
}


Tree* MaxRankTree::maxChild(int depth) {
    if (this->getChildren().empty()){
        return this;
    } else {
        Tree *maxNode = this->getChildren()[0];
        for(auto child : this->getChildren()){
            child->setDepth(depth);
            Tree *pMaxChild = dynamic_cast<MaxRankTree *>(child)->maxChild(depth + 1);  // todo: check about casting
            maxNode = compare(maxNode, pMaxChild);
        }
        return compare(this,maxNode);
    }
}


Tree *MaxRankTree::clone() const {
    Tree *pClone = new MaxRankTree(*this);
    return pClone;
}


//==================================================
//=====================RootTree=====================
RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}


RootTree::RootTree(const RootTree &other) : Tree(other) {}


RootTree::RootTree(RootTree &&other) : Tree(std::move(other)) {}


RootTree::~RootTree() {}


int RootTree::traceTree() {     // Implemented [03/11]
    return this->getNode();
}


Tree *RootTree::clone() const {
    Tree *pClone = new RootTree(*this);
    return pClone;
}