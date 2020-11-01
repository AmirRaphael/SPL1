//
// Created by Amir Zaushnizer on 31/10/2020.
//

#include "Tree.h"
#include "Session.h"
#include <queue>

Tree::Tree(int rootLabel) : node(rootLabel) {

}


void Tree::addChild(const Tree &child) {
    Tree* pchild = const_cast<Tree *>(&child); // silence issue of const child - check with mister nitay
    this->children.push_back(pchild);
}

Tree* Tree::createTree(const Session &session, int rootLabel) {
    TreeType type = session.getTreeType();
    int cycle = session.getCycle();
    const Graph &graph = session.getG();
    Tree* tree = createChild(type,rootLabel,cycle);
    std::queue<Tree*> bfsQueue;
    bfsQueue.push(tree);
    std::vector<bool> visited (graph.getSize(), false); // array to keep track of visited nodes in the bfs algorithm.
    while (!(bfsQueue.empty())){
        Tree* u = bfsQueue.front();
        bfsQueue.pop();
        std::vector<int> neighbors {graph.getNeighbors(u->node)};
        for(auto n : neighbors){
            if (!visited[n]){
                visited[n]=true;
                Tree* child = createChild(type,n,cycle);
                u->addChild(*child);
                bfsQueue.push(child);
            }
        }
    }
    return tree;
}

Tree *Tree::createChild(TreeType type,int label,int cycle) {
    Tree* tree;
    if(type==Cycle){
        tree = new CycleTree(label,cycle);
    }
    else if (type==MaxRank){
        tree = new MaxRankTree(label);
    }
    else{
        tree = new RootTree(label);
    }
    return tree;

}






