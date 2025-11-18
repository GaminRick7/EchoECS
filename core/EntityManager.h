#pragma once
#include <queue>

#include "Types.h"

class EntityManager
{
public:
    EntityManager();
    Entity createEntity();
    void destroyEntity(Entity e);
    ComponentMask getComponentMask(Entity e) const;
    void setComponentMask(Entity e, ComponentMask mask);
private:
    std::queue<Entity> m_availableEntities;
    std::array<ComponentMask, MAX_ENTITIES> m_componentMasks;
    uint32_t m_livingEntities{};
};
