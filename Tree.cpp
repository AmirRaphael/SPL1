#include "Tree.h"
#include "Session.h"
#include <queue>

Tree::Tree(int rootLabel) : node(rootLabel), children() {}  // Added member init list [03/11]

Tree::Tree(const Tree &other) : node(other.node), children(other.children) {}   // copy constructor [03/11]

Tree::Tree(Tree &&other) : node(std::move(other.node)), children(std::move(other.children)) {}  // move constructor

Tree::~Tree() {
    for (auto subTree : children){
        delete subTree;
    }
}

void Tree::addChild(const Tree &child) {
    Tree *pTree = child.clone();
    children.push_back(pTree);
}

Tree* Tree::createTree(const Session &session, int rootLabel) {
    TreeType type = session.getTreeType();
    int cycle = session.getCycle();
    const Graph &graph = session.getG();
    Tree *tree = createChild(type,rootLabel,cycle); // receives new dynamically allocated tree of the correct type
    // BFS algorithm
    std::queue<Tree*> bfsQueue;
    bfsQueue.push(tree);
    std::vector<bool> visited (graph.getSize(), false); // array that keeps track of visited nodes in the bfs algorithm.
    while (!(bfsQueue.empty())){
        Tree* u = bfsQueue.front();
        bfsQueue.pop();
        std::vector<int> neighbors {graph.getNeighbors(u->node)};
        for(auto n : neighbors){
            if (!visited[n]){
                visited[n]=true;
                Tree *child = createChild(type,n,cycle);
                u->children.push_back(child);// Changed - does not use addChild, instead adds new child to children vector
                bfsQueue.push(child);
            }
        }
    }
    return tree;
}
///Factory method
Tree* Tree::createChild(TreeType type, int label, int cycle) {  // changed to switch statements
    Tree *tree;
    switch (type) {
        case Cycle:
            tree = new CycleTree(label, cycle);
            break;
        case MaxRank:
            tree = new MaxRankTree(label);
            break;
        case Root:
            tree = new RootTree(label);
            break;
    }
    return tree;
}

int Tree::getNode() const {
    return node;
}

const std::vector<Tree *> &Tree::getChildren() const {
    return children;
}

/*Tree *Tree::compare(Tree *node1, Tree *node2) {
    if (node1 == node2) {return node1;}
    if (node1->getChildren().size() == node2->getChildren().size()){
        if (node1->getDepth() == node2->getDepth()){
            if (node1->getTime() < node2->getTime()){
                return node1;
            } else {
                return node2;
            }
        } else {
            if (node1->getDepth() < node2->getDepth()){
                return node1;
            } else {
                return node2;
            }
        }
    } else {
        if (node1->getChildren().size() > node2->getChildren().size()){
            return node1;
        } else {
            return node2;
        }
    }
}*/

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

int MaxRankTree::traceTree() {  // todo: Implement
    Tree *maxNode = compare(this, this->helper());
    return maxNode->getNode();
}

Tree* MaxRankTree::helper() {
    if (this->getChildren().empty()){
        return this;
    } else {
        Tree *maxNode = this;
        for(auto child : this->getChildren()){
            Tree *pMaxChild = dynamic_cast<MaxRankTree*>(child)->helper();  // todo: check about casting
            maxNode = compare(this, pMaxChild);
        }
        return maxNode;
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
