#ifndef POOL_H
#define POOL_H

#pragma once

#include <iostream>
#include <vector>

template <typename TType>
class pool
{
public:
    //////////////////////
    class object
    {
    public:
        object()
        {
            m_object = nullptr;
        }

        object(TType *p_object)
        {
            m_object = p_object;
        }

        object &operator=(TType *p_object)
        {
            m_object = p_object;
            return *this;
        }

        ~object()
        {
            if (m_object != nullptr)
            {
                delete m_object;
            }
        }

        TType *operator->()
        {
            return m_object;
        }

        TType &operator*()
        {
            return *m_object;
        }

    private:
        TType *m_object;
    };

    //////////////////////
    pool()
    {
    }

    void resize(const size_t &numberOfObjectStored)
    {
        m_pool.resize(numberOfObjectStored);
    }

    template <typename... TArgs>
    object acquire(TArgs &&...p_args)
    {
        for (size_t i = 0; i < m_pool.size(); i++)
        {
            if (m_pool[i] == nullptr)
            {
                m_pool[i] = new TType(std::forward<TArgs>(p_args)...);
                return object(m_pool[i]);
            }
        }

        return object(nullptr);
    }

    size_t size()
    {
        return m_pool.size();
    }

    TType *operator[](const size_t &index)
    {
        return m_pool[index];
    }

    ~pool()
    {
    }

private:
    std::vector<TType *> m_pool;
};

#endif