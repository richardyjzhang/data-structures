#include <iostream>
#include "bst.hpp"
#include "util.h"

class BstTest
{
private:
  BinarySearchTree<int> makeTree()
  {
    BinarySearchTree<int> tree;
    for (int i = 0; i < 100; ++i)
      tree.insert(i);
    return tree;
  }

public:
  void test()
  {
    BinarySearchTree<int> tree = makeTree();
    println(tree.isEmpty());
    println(tree.findMin());
    println(tree.findMax());
    tree.remove(99);
    tree.remove(50);
    println(tree.findMax());
    println(tree.contains(50));
  }
};