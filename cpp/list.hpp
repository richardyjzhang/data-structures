#ifndef __LIST_H__
#define __LIST_H__

#include <algorithm>

template <typename Object>
class List
{
private:
  struct Node
  {
    Object mData;
    Node *mpPrev;
    Node *mpNext;

    Node(const Object &d = Object{}, Node *pPrev = nullptr, Node *pNext = nullptr)
        : mData{d}, mpPrev{pPrev}, mpNext{pNext} {}
    Node(const Object &&d, Node *pPrev = nullptr, Node *pNext = nullptr)
        : mData{std::move(d)}, mpPrev{pPrev}, mpNext{pNext} {}
  };

public:
  class const_iterator
  {
    friend class List<Object>;

  protected:
    Node *mpCurrent;

    Object &retrieve() const
    {
      return mpCurrent->mData;
    }

    const_iterator(Node *p) : mpCurrent{p} {}

  public:
    const_iterator() : mpCurrent{nullptr} {}

    const Object &operator*() const
    {
      return retrieve();
    }

    const_iterator &operator++()
    {
      mpCurrent = mpCurrent->mpNext;
      return *this;
    }
    const_iterator operator++(int)
    {
      const_iterator pOld = *this;
      ++(*this);
      return pOld;
    }
    const_iterator &operator--()
    {
      mpCurrent = mpCurrent->mpPrev;
      return *this;
    }
    const_iterator operator--(int)
    {
      const_iterator pOld = *this;
      --(*this);
      return pOld;
    }

    bool operator==(const const_iterator &rhs) const
    {
      return mpCurrent == rhs.mpCurrent;
    }
    bool operator!=(const const_iterator &rhs) const
    {
      return !(*this == rhs);
    }
  };

  class iterator : public const_iterator
  {
    friend class List<Object>;

  protected:
    iterator(Node *p) : const_iterator{p} {}

  public:
    iterator() {}

    Object &operator*()
    {
      return const_iterator::retrieve();
    }
    const Object &operator*() const
    {
      return const_iterator::operator*();
    }

    iterator &operator++()
    {
      this->mpCurrent = this->mpCurrent->mpNext;
      return *this;
    }
    iterator operator++(int)
    {
      iterator pOld = *this;
      ++(*this);
      return pOld;
    }
    iterator &operator--()
    {
      this->mpCurrent = this->mpCurrent->mpPrev;
      return *this;
    }
    iterator operator--(int)
    {
      iterator pOld = *this;
      --(*this);
      return pOld;
    }
  };

private:
  int mSize;
  Node *mpHead;
  Node *mpTail;

  void init()
  {
    mSize = 0;
    mpHead = new Node;
    mpTail = new Node;
    mpHead->mpNext = mpTail;
    mpTail->mpPrev = mpHead;
  }

public:
  List()
  {
    init();
  }
  ~List()
  {
    clear();
    delete mpHead;
    delete mpTail;
  }
  List(const List &rhs)
  {
    init();
    for (auto &x : rhs)
    {
      push_back(x);
    }
  }
  List &operator=(const List &rhs)
  {
    List copy = rhs;
    std::swap(*this, copy);
    return *this;
  }
  List(List &&rhs)
      : mSize{rhs.mSize}, mpHead{rhs.mpHead}, mpTail{rhs.mpTail}
  {
    rhs.mSize = 0;
    rhs.mpHead = nullptr;
    rhs.mpTail = nullptr;
  }
  List &operator=(List &&rhs)
  {
    std::swap(mSize, rhs.mSize);
    std::swap(mpHead, rhs.mpHead);
    std::swap(mpTail, rhs.mpTail);

    return *this;
  }

  iterator begin()
  {
    return mpHead->mpNext;
  }
  const_iterator begin() const
  {
    return mpHead->mpNext;
  }
  iterator end()
  {
    return mpTail;
  }
  const_iterator end() const
  {
    return mpTail;
  }

  int size() const
  {
    return mSize;
  }
  bool empty() const
  {
    return size() == 0;
  }

  void clear()
  {
    while (!empty())
    {
      pop_front();
    }
  }

  Object &front()
  {
    return *begin();
  }
  const Object &front() const
  {
    return *begin();
  }
  Object &back()
  {
    return *--end();
  }
  const Object &back() const
  {
    return *--end();
  }

  void push_front(const Object &x)
  {
    insert(begin(), x);
  }
  void push_front(Object &&x)
  {
    insert(begin(), std::move(x));
  }
  void push_back(const Object &x)
  {
    insert(end(), x);
  }
  void push_back(Object &&x)
  {
    insert(end(), std::move(x));
  }
  void pop_front()
  {
    erase(begin());
  }
  void pop_back()
  {
    erase(--end());
  }

  iterator insert(iterator itr, const Object &x)
  {
    Node *p = itr.mpCurrent;
    ++mSize;
    return {p->mpPrev = p->mpPrev->mpNext = new Node{x, p->mpPrev, p}};
  }
  iterator insert(iterator itr, Object &&x)
  {
    Node *p = itr.mpCurrent;
    ++mSize;
    return {p->mpPrev = p->mpPrev->mpNext = new Node{std::move(x), p->mpPrev, p}};
  }
  iterator erase(iterator itr)
  {
    Node *p = itr.mpCurrent;
    iterator retVal{p->mpNext};
    p->mpPrev->mpNext = p->mpNext;
    p->mpNext->mpPrev = p->mpPrev;

    delete p;
    --mSize;

    return retVal;
  }
  iterator erase(iterator from, iterator to)
  {
    for (iterator itr = from; itr != to; ++itr)
    {
      itr = erase(itr);
    }

    return to;
  }
};

#endif