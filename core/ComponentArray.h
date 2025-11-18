#pragma once
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "Types.h"
class IComponentArray
{
public:
    // ensures component Array's destructor is called
    virtual ~IComponentArray() = default;
    virtual void EntityDestroyed(Entity e) = 0;
    virtual void print() const = 0;
};
template<class T>
class ComponentArray : public IComponentArray{
public:
    void addComponent(const Entity e, T component)
    {
        assert(!m_EntityToIndex.contains(e) && "Component for this entity already exists");
        m_componentArray[m_size] = component;
        m_EntityToIndex[e] = m_size;
        m_indexToEntity[m_size] = e;
        m_size++;
    }

    T& getComponent(const Entity e)
    {
        assert(m_EntityToIndex.contains(e)&& "Cannot retrieve non-existent component");
        return m_componentArray[m_EntityToIndex[e]];
    }

    void removeComponent(const Entity e)
    {
        assert(m_EntityToIndex.contains(e) && "Cannot remove non-existent component;");

        size_t indexRem = m_EntityToIndex[e];
        size_t indexLast = m_size - 1;
        Entity& entLast = m_indexToEntity[indexLast];

        m_componentArray[indexRem] = m_componentArray[indexLast];
        m_EntityToIndex[entLast] = indexRem;
        m_indexToEntity[indexRem] = entLast;

        m_EntityToIndex.erase(e);
        m_indexToEntity.erase(indexLast);
        m_size--;
    }

    void print() const override
    {
        std::cout << "ComponentArray<" << typeid(T).name() << ">:\n";
        for (size_t i = 0; i < m_size; ++i)
        {
            Entity e = m_indexToEntity.at(i);
            std::cout << "  Entity " << e << ": "  << "\n";
        }
    }



private:
    std::array<T, MAX_ENTITIES> m_componentArray;
    std::unordered_map<Entity, size_t> m_EntityToIndex;
    std::unordered_map<size_t, Entity> m_indexToEntity;

    void EntityDestroyed(const Entity e) override
    {
        if (m_EntityToIndex.contains(e)) removeComponent(e);
    }

    size_t m_size{};
};
