#include "data_structures.hpp"

int main()
{
    // Create a pool of integers
    pool<int> intPool;
    intPool.resize(5);

    // Acquire objects from the pool
    pool<int>::object obj1 = intPool.acquire(10);
    pool<int>::object obj2 = intPool.acquire(20);
    pool<int>::object obj3 = intPool.acquire(30);
    \
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

    return 0;
}