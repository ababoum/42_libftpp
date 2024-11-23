#ifndef MEMENTO_HPP
#define MEMENTO_HPP

#include <iostream>
#include <string>
#include <vector>

template <typename T>
class Memento : public T
{

    class Snapshot
    {
    };

public:
    Snapshot save()
    {
        Snapshot snapshot;
        _saveToSnapshot(snapshot);
        return snapshot;
    }

    void load(const Snapshot &snapshot)
    {
        _loadFromSnapshot(snapshot);
    }

private:
    Snapshot snapshot;

    void _saveToSnapshot(Memento::Snapshot &snapshot)
    {
        // Save the state of the object to the snapshot
    }

    void _loadFromSnapshot(const Memento::Snapshot &snapshot)
    {
        // Load the state of the object from the snapshot
    }
};

#endif // MEMENTO_HPP