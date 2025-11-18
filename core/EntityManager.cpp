#include "EntityManager.h"

#include <cassert>

EntityManager::EntityManager()
{
    for (Entity i = 0; i < MAX_ENTITIES; i++)
    {
        m_availableEntities.push(i);
    }
}
Entity EntityManager::createEntity()
{
    assert(m_livingEntities < MAX_ENTITIES && "EntityManager::createEntity exceeded MAX_ENTITIES");
    const Entity id = m_availableEntities.front();
    m_availableEntities.pop();
    m_livingEntities++;
    return id;
}
void EntityManager::destroyEntity(const Entity e)
{
    assert(e < MAX_ENTITIES && "EntityManager::destroyEntity exceeded");
    m_availableEntities.push(e);
    m_livingEntities--;
}
ComponentMask EntityManager::getComponentMask(const Entity e) const
{
    assert(e < MAX_ENTITIES && "EntityManager::getComponentMask out of range");
    return m_componentMasks[e];
}
void EntityManager::setComponentMask(Entity e, ComponentMask mask)
{
    assert(e < MAX_ENTITIES && "EntityManager::setComponentMask out of range");
    m_componentMasks[e] = mask;
}