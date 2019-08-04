#include "vector_test.hpp"
#include "list_test.hpp"
#include "bst_test.hpp"

int main()
{
    VectorTest vectorTest;
    vectorTest.test();

    ListTest listTest;
    listTest.test();

    BstTest bstTest;
    bstTest.test();
}