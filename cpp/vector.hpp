#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <algorithm>

template <typename Object>
class Vector
{
private:
  int mSize;                             // 当前元素数量
  int mCapacity;                         // 存储空间大小
  Object *mObjects;                      // 存储的元素
  static const int _SPACE_CAPACITY = 16; // 初始备用空间大小

public:
  typedef Object *iterator;
  typedef const Object *const_iterator;

public:
  // 默认构造函数
  explicit Vector(int initSize = 0) : mSize{initSize},
                                      mCapacity{initSize + _SPACE_CAPACITY}
  {
    mObjects = new Object[mCapacity];
  }

  // 析构函数
  ~Vector()
  {
    delete[] mObjects;
  }

  // 拷贝构造函数
  Vector(const Vector &rhs) : mSize{rhs.mSize},
                              mCapacity{rhs.mCapacity},
                              mObjects{nullptr}
  {
    mObjects = new Object[rhs.mCapacity];
    for (int i = 0; i < rhs.mSize; ++i)
      mObjects[i] = rhs.mObjects[i];
  }

  // 拷贝赋值运算符
  Vector &operator=(const Vector &rhs)
  {
    Vector copy = rhs;
    std::swap(*this, copy);
    return *this;
  }

  // 移动构造函数
  Vector(Vector &&rhs) : mSize{rhs.mSize},
                         mCapacity{rhs.mCapacity},
                         mObjects{rhs.mObjects}
  {
    rhs.mObjects = nullptr;
  }

  // 移动赋值运算符
  Vector &operator=(Vector &&rhs)
  {
    std::swap(mSize, rhs.mSize);
    std::swap(mCapacity, rhs.mCapacity);
    std::swap(mObjects, rhs.mObjects);

    return *this;
  }

  // 改变容器存储元素数目
  void resize(int newSize)
  {
    if (newSize > mCapacity)
      reserve(newSize * 2);
    mSize = newSize;
  }

  // 改变内部存储空间大小
  void reserve(int newCapacity)
  {
    if (newCapacity < mCapacity)
      return;

    Object *newArray = new Object[newCapacity];
    for (int i = 0; i < mSize; ++i)
      newArray[i] = mObjects[i];

    mCapacity = newCapacity;
    std::swap(mObjects, newArray);
    delete[] newArray;
  }

  // 下标运算符重载
  Object &operator[](int index)
  {
    return mObjects[index];
  }

  // 下标运算符重载（返回const）
  const Object &operator[](int index) const
  {
    return mObjects[index];
  }

  // 返回容器内元素数量
  int size() const
  {
    return mSize;
  }

  // 返回容器内部存储能力
  int capacity() const
  {
    return mCapacity;
  }

  // 判断是否为容器
  bool empty() const
  {
    return size() == 0;
  }

  // 向最后添加一个元素
  void push_back(const Object &x)
  {
    if (mSize == mCapacity)
      reserve(2 * mCapacity + 1);
    mObjects[mSize++] = x;
  }

  // 向最后添加一个元素（传入右值引用）
  void push_back(Object &&x)
  {
    if (mSize == mCapacity)
      reserve(2 * mCapacity + 1);
    mObjects[mSize++] = std::move(x);
  }

  // 删除最后一个元素
  void pop_back()
  {
    --mSize;
  }

  // 获取最后一个元素
  const Object &back() const
  {
    return mObjects[mSize - 1];
  }

  // 获取首部迭代器
  iterator begin()
  {
    return &mObjects[0];
  }

  // 获取const版首部迭代器
  const_iterator begin() const
  {
    return &mObjects[0];
  }

  // 获取尾后迭代器
  iterator end()
  {
    return &mObjects[size()];
  }

  // 获取const版尾后迭代器
  const_iterator end() const
  {
    return &mObjects[size()];
  }
};

#endif