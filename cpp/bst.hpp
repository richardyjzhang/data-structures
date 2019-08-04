#ifndef __BST_H__
#define __BST_H__

#include <iostream>

template <typename Comparable>
class BinarySearchTree
{
private:
  struct BinaryNode
  {
    Comparable mElement;
    BinaryNode *mpLeft;
    BinaryNode *mpRight;

    BinaryNode(const Comparable &theElement, BinaryNode *pL, BinaryNode *pR)
        : mElement(theElement), mpLeft(pL), mpRight(pR) {}
    BinaryNode(Comparable &&theElement, BinaryNode *pL, BinaryNode *pR)
        : mElement(std::move(theElement)), mpLeft(pL), mpRight(pR) {}
  };

private:
  BinaryNode *mpRoot;

private:
  void insert(const Comparable &x, BinaryNode *&t)
  {
    if (t == nullptr)
      t = new BinaryNode{x, nullptr, nullptr};
    else if (x < t->mElement)
      insert(x, t->mpLeft);
    else if (t->mElement < x)
      insert(x, t->mpRight);
    else
      return;
  }
  void insert(Comparable &&x, BinaryNode *&t)
  {
    if (t == nullptr)
      t = new BinaryNode{std::move(x), nullptr, nullptr};
    else if (x < t->mElement)
      insert(std::move(x), t->mpLeft);
    else if (x > t->mElement)
      insert(std::move(x), t->mpRight);
    else
      return;
  }
  void remove(const Comparable &x, BinaryNode *&t)
  {
    if (t == nullptr)
      return;
    if (x < t->mElement)
      remove(x, t->mpLeft);
    else if (t->mElement < x)
      remove(x, t->mpRight);
    else if (t->mpLeft != nullptr && t->mpRight != nullptr)
    {
      t->mElement = findMin(t->mpRight)->mElement;
      remove(t->mElement, t->mpRight);
    }
    else
    {
      BinaryNode *oldNode = t;
      t = (t->mpLeft != nullptr) ? t->mpLeft : t->mpRight;
      delete oldNode;
    }
  }
  BinaryNode *findMin(BinaryNode *t) const
  {
    if (t == nullptr)
      return nullptr;
    if (t->mpLeft == nullptr)
      return t;
    return findMin(t->mpLeft);
  }
  BinaryNode *findMax(BinaryNode *t) const
  {
    if (t != nullptr)
    {
      while (t->mpRight != nullptr)
        t = t->mpRight;
    }
    return t;
  }
  bool contains(const Comparable &x, BinaryNode *t) const
  {
    if (t == nullptr)
      return false;
    else if (x < t->mElement)
      return contains(x, t->mpLeft);
    else if (t->mElement < x)
      return contains(x, t->mpRight);
    else
      return true;
  }
  void makeEmpty(BinaryNode *&t)
  {
    if (t != nullptr)
    {
      makeEmpty(t->mpLeft);
      makeEmpty(t->mpRight);
      delete t;
    }
    t = nullptr;
  }
  BinaryNode *clone(BinaryNode *t) const
  {
    if (t == nullptr)
      return nullptr;
    else
      return new BinaryNode{t->mElement, clone(t->mpLeft), clone(t->mpRight)};
  }

public:
  BinarySearchTree() : mpRoot{nullptr} {}
  BinarySearchTree(const BinarySearchTree &rhs)
      : mpRoot{nullptr} { mpRoot = clone(rhs.mpRoot); }
  BinarySearchTree(BinarySearchTree &&rhs)
      : mpRoot{nullptr} { mpRoot = clone(std::move(rhs.mpRoot)); }
  BinarySearchTree &operator=(const BinarySearchTree &rhs)
  {
    BinarySearchTree copy = rhs;
    std::swap(*this, copy);
    return *this;
  }
  BinarySearchTree &operator=(BinarySearchTree &&rhs)
  {
    std::swap(mpRoot, rhs.mpRoot);
    return *this;
  }
  ~BinarySearchTree() { makeEmpty(); }

  const Comparable &findMin() const { return findMin(mpRoot)->mElement; }
  const Comparable &findMax() const { return findMax(mpRoot)->mElement; }
  bool contains(const Comparable &x) const { return contains(x, mpRoot); }
  bool isEmpty() const { return mpRoot == nullptr; }

  void makeEmpty() { makeEmpty(mpRoot); }
  void insert(const Comparable &x) { return insert(x, mpRoot); }
  void insert(Comparable &&x) { return insert(x, mpRoot); }
  void remove(const Comparable &x) { remove(x, mpRoot); }
};

#endif