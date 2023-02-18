#ifndef BINARYTREE
#define BINARYTREE
#include <iostream>
static int maxLevel = 0;
struct Branch{
    Branch * left;
    Branch * right;
    ~Branch(){};
    int level;
    int value;
};
class BinaryTree{
public:
    Branch * root;
    int level;
    BinaryTree(int v);
    ~BinaryTree(){};
    void addValue(int v, Branch ** br, int level);
    void addValue(int v, Branch ** br);
    void showTree(Branch ** root);
};
BinaryTree::BinaryTree(int v){
    root = new Branch;
    level = 0;
    root->value = v;
    root->left = nullptr;
    root->right = nullptr;
}
void BinaryTree::addValue(int v, Branch ** br,int level){
    if(!(*br==nullptr))
    {
        if(v>(*br)->value)
            addValue(v,&((*br)->right),((*br)->level)+1);
        else
            addValue(v,&((*br)->left),((*br)->level)+1);
    }
    else{
        *br = new Branch;
        (*br)->value = v;
        (*br)->left = nullptr;
        (*br)->right = nullptr;
        (*br)->level = level;
        if(level>maxLevel)
            maxLevel=level;
    }
}
void BinaryTree::addValue(int v, Branch ** br){
    if(!(*br==nullptr))
    {
        if(v>(*br)->value)
            addValue(v,&((*br)->right),1);
        else
            addValue(v,&((*br)->left),1);
    }
    else{
        *br = new Branch;
        (*br)->value = v;
        (*br)->left = nullptr;
        (*br)->right = nullptr;
        (*br)->level = level;
    }
}
void BinaryTree::showTree(Branch ** br){
    if(*br==nullptr)
        return;
    showTree(&((*br)->left));
    std::cout<<(*br)->value<<" "<<(*br)->level<<", ";
    showTree(&((*br)->right));
}
#endif