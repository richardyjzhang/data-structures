#include <iostream>
#include "vector.hpp"
#include "utils.hpp"

class VectorTest
{
private:
  Vector<int> makeVector(int size, int val)
  {
    Vector<int> vec{size};
    for (int i = 0; i < size; ++i)
      vec[i] = val;
    return vec;
  }

public:
  void test()
  {
    Vector<int> vec1{10};
    for (int i = 0; i < 10; ++i)
      vec1[i] = i + 1;

    Vector<int> vec2 = vec1;
    vec2 = vec2;
    vec2.push_back(11);
    println(vec2.back());
    println(vec1.back());

    vec2 = std::move(vec2);
    for (Vector<int>::const_iterator it = vec1.begin(); it != vec1.end(); ++it)
      println(*it);
  }
};