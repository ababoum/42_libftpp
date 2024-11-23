#ifndef POOL_HPP
#define POOL_HPP

#include <vector>
#include <memory>

template <typename TType>
class Pool {
private:
    std::vector<std::shared_ptr<TType>> objects;

public:
    class Object {
    private:
        std::shared_ptr<TType> ptr;
        Pool<TType>* pool;

    public:
        Object(std::shared_ptr<TType> p, Pool<TType>* pool) : ptr(p), pool(pool) {}
        ~Object() { pool->release(ptr); }
        TType* operator->() { return ptr.get(); }
        TType& operator*() { return *ptr; }
    };

    void resize(const size_t& numberOfObjectStored) {
        objects.reserve(numberOfObjectStored);
        while (objects.size() < numberOfObjectStored) {
            objects.push_back(std::make_shared<TType>());
        }
    }

    template<typename... TArgs>
    Object acquire(TArgs&&... p_args) {
        std::shared_ptr<TType> obj;
        if (objects.empty()) {
            obj = std::make_shared<TType>(std::forward<TArgs>(p_args)...);
        } else {
            obj = objects.back();
            objects.pop_back();
            *obj = TType(std::forward<TArgs>(p_args)...);
        }
        return Object(obj, this);
    }

private:
    void release(std::shared_ptr<TType> obj) {
        objects.push_back(obj);
    }
};

#endif // POOL_HPP
