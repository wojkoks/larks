#ifndef BINARYTREE
#define BINARYTREE
#include <iostream>

struct Branch{
    Branch * left;
    Branch * right;
    int value;
};
class BinaryTree{
public:
    Branch * root;
    BinaryTree(int v);
    ~BinaryTree(){};
    void addValue(int v, Branch ** br);
    void showTree(Branch * root);
};
BinaryTree::BinaryTree(int v){
    root = new Branch;
    root->value = v;
    root->left = nullptr;
    root->right = nullptr;
}
void BinaryTree::addValue(int v, Branch ** br){
    if(!(*br==nullptr))
    {
        if(v>(*br)->value)
        {
            addValue(v,&((*br)->right));
        }
        else
        {
            addValue(v,&((*br)->left));
        }
    }
    else{
        *br = new Branch;
        (*br)->value = v;
        (*br)->left = nullptr;
        (*br)->right = nullptr;
    }
}
void BinaryTree::showTree(Branch * br){
    if(br==nullptr)
        return;
    showTree(br->left);
    std::cout<<br->value<<" ";
    showTree(br->right);
}
#endif