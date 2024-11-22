#include "data_structures.hpp"
#include "string.h"
#include <string>

class test
{
public:
    int val;
    std::string name;

    test(int v, const char *n) {
        this->val = v;
        this->name = n;
    }

    ~test() {
        std::cout << "Destroying test object" << std::endl;
    }
};

std::ostream& operator<<(std::ostream& os, const test& t) {
    os << "val: " << t.val << ", name: " << t.name;
    return os;
}

int main()
{
    // Create a pool of integers
    pool<int> intPool;
    intPool.resize(5);

    // Acquire objects from the pool
    pool<int>::object obj1 = intPool.acquire(10);
    pool<int>::object obj2 = intPool.acquire(20);
    pool<int>::object obj3 = intPool.acquire(30);

    // Current state of the pool
    std::cout << "Pool size: " << intPool.size() << std::endl;

    // Access objects using operator*
    std::cout << "obj1: " << *obj1 << std::endl;
    std::cout << "obj2: " << *obj2 << std::endl;
    std::cout << "obj3: " << *obj3 << std::endl;

    // After acquiring objects from the pool, we can access them using operator* and operator[]

    std::cout << "Loading new values to the objects" << std::endl;
    *obj1 = 100;
    std::cout << "obj1: " << *obj1 << std::endl;

    *obj2 = 200;
    std::cout << "obj2: " << *obj2 << std::endl;

    *obj3 = 300;
    std::cout << "obj3: " << *obj3 << std::endl;

    // Access objects using operator[]
    for (size_t i = 0; i < intPool.size(); i++)
    {
        if (intPool[i] != nullptr)
        {
            std::cout << "intPool[" << i << "]: " << *intPool[i] << std::endl;
        }
    }

    ///////////////////////////////////
    // Create a pool of test objects
    std::cout << "Creating a pool of test objects" << std::endl;

    pool<test> testPool;
    testPool.resize(10);

    // Acquire objects from the pool
    pool<test>::object objx1 = testPool.acquire(10, "hello");
    pool<test>::object objx2 = testPool.acquire(20, "bonjour");
    pool<test>::object objx3 = testPool.acquire(30, "hola");

    // Current state of the pool
    std::cout << "Pool size: " << testPool.size() << std::endl;

    // Access objects using operator*
    std::cout << "objx1: " << *objx1 << std::endl;
    std::cout << "objx2: " << *objx2 << std::endl;
    std::cout << "objx3: " << *objx3 << std::endl;

    return 0;
}