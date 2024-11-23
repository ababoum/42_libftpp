#include <iostream>
#include <cassert>
#include <string>
#include "pool.hpp"

// Custom class for testing
class TestClass
{
private:
    int value;
    std::string name;
    static int next_id;

public:
    TestClass() : value(0), name("Default") {}
    TestClass(int v, std::string n) : value(v), name(n) {}

    void setValue(int v) { value = v; }
    int getValue() const { return value; }
    std::string getName() const { return name; }
};

int TestClass::next_id = 0;

void testIntPool()
{
    std::cout << "Testing Pool<int>..." << std::endl;

    Pool<int> intPool;
    intPool.resize(5);

    {
        auto obj1 = intPool.acquire(10);
        assert(*obj1 == 10);
        *obj1 = 20;
        assert(*obj1 == 20);

        auto obj2 = intPool.acquire(30);
        assert(*obj2 == 30);

        // obj1 and obj2 will be automatically released here
    }

    // Test reuse of released objects
    {
        auto obj3 = intPool.acquire(40);
        assert(*obj3 == 40);
        // obj3 should be one of the previously released objects
    }

    std::cout << "Pool<int> tests passed!" << std::endl;
}

void testCustomClassPool()
{
    std::cout << "Testing Pool<TestClass>..." << std::endl;

    Pool<TestClass> customPool;
    customPool.resize(3);

    {
        auto obj1 = customPool.acquire(1, "First");
        assert(obj1->getValue() == 1);
        assert(obj1->getName() == "First");

        obj1->setValue(10);
        assert(obj1->getValue() == 10);

        auto obj2 = customPool.acquire(2, "Second");
        assert(obj2->getValue() == 2);
        assert(obj2->getName() == "Second");
    }

    {
        auto obj3 = customPool.acquire(3, "Third");
        assert(obj3->getValue() == 3);
        assert(obj3->getName() == "Third");
    }

    // Test acquiring more objects than the initial pool size
    {
        auto obj4 = customPool.acquire(4, "Fourth");
        auto obj5 = customPool.acquire(5, "Fifth");
        auto obj6 = customPool.acquire(6, "Sixth");
        auto obj7 = customPool.acquire(7, "Seventh");

        assert(obj7->getValue() == 7);
        assert(obj7->getName() == "Seventh");
    }

    std::cout << "Pool<TestClass> tests passed!" << std::endl;
}

void testObjectReuse()
{
    std::cout << "Testing object reuse..." << std::endl;

    Pool<TestClass> pool;
    pool.resize(1);
    Pool<TestClass>::Object *obj1_addr, *obj2_addr;

    {
        auto obj1 = pool.acquire(1, "First");
        obj1_addr = &obj1;
        std::cout << "First object address: " << obj1_addr << std::endl;
    }

    // Let obj1 go out of scope, returning it to the pool
    {
        auto temp = pool.acquire(2, "Second");
        std::cout << "Temporary object address: " << &temp << std::endl;
    }

    // Acquire second object (should be the same as the first)
    auto obj2 = pool.acquire(3, "Third");
    obj2_addr = &obj2;
    std::cout << "Second object address: " << obj2_addr << std::endl;

    // Check if the IDs are the same
    assert(obj1_addr == obj2_addr && "Object was not reused from the pool");
    std::cout << "Object reuse confirmed: both objects have address " << obj1_addr << std::endl;
}

int main()
{
    testIntPool();
    testCustomClassPool();
    testObjectReuse();

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}