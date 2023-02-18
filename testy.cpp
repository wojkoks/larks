#include <iostream>
#include "./datastructures/binarytree.h"

int main(){
    int i;
    BinaryTree tree(4);
    tree.addValue(2,&tree.root);
    tree.addValue(5,&tree.root);
    tree.addValue(5,&tree.root);
    tree.addValue(7,&tree.root);
    tree.addValue(5,&tree.root);
    tree.addValue(1,&tree.root);
    tree.addValue(3,&tree.root);
    tree.addValue(10,&tree.root);
    tree.addValue(1,&tree.root);
    tree.showTree(tree.root);
    return 0;
}