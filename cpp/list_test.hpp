#include <iostream>
#include "list.hpp"
#include "utils.hpp"

class ListTest
{
private:
  List<int> makeList(int size, int val)
  {
    List<int> lst;
    for (int i = 0; i < size; ++i)
    {
      lst.push_back(val);
    }
    return lst;
  }

public:
  void test()
  {
    List<int> lst1;
    for (int i = 0; i < 10; ++i)
    {
      lst1.push_back(i + 1);
    }

    List<int> lst2 = lst1;
    lst2.push_back(11);
    println(lst2.back());
    println(lst1.back());

    lst2 = std::move(lst1);
    lst2.erase(++lst2.begin());
    for (List<int>::const_iterator it = lst1.begin(); it != lst1.end(); ++it)
    {
      println(*it);
    }
  }
};