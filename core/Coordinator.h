#pragma once
#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"

class Coordinator {
    public:
    void init()
    {
        mEntityManager = std::make_unique<EntityManager>();
        mSystemManager = std::make_unique<SystemManager>();
        mComponentManager = std::make_unique<ComponentManager>();
    }

    Entity createEntity()
    {
        return mEntityManager->createEntity();
    }

    void destroyEntity(Entity entity)
    {
        mEntityManager->destroyEntity(entity);
        mSystemManager->EntityDestroyed(entity);
        mComponentManager->EntityDestroyed(entity);
    }

    template <typename T>
    void registerComponent()
    {
        mComponentManager->registerComponent<T>();
    }

    template <typename T>
    void addComponent(Entity e, T component)
    {
        auto mask = mEntityManager->getComponentMask(e);
        mask.set(mComponentManager->getComponentType<T>());
        mEntityManager->setComponentMask(e, mask);
        mComponentManager->addComponent<T>(e, component);
        mSystemManager->EntityMaskChanged(e, mask);
    }

    template <typename T>
    void removeComponent(Entity e)
    {
        auto mask = mEntityManager->getComponentMask(e);
        mask.reset(mComponentManager->getComponentType<T>());
        mEntityManager->setComponentMask(e, mask);
        mComponentManager->removeComponent<T>(e);
        mSystemManager->EntityMaskChanged(e, mask);
    }

    template <typename T>
    T& getComponent(Entity e)
    {
        return mComponentManager->getComponent<T>(e);
    }

    template <typename T>
    ComponentType getComponentType()
    {
        return mComponentManager->getComponentType<T>();
    }

    template <typename T>
    std::shared_ptr<T> registerSystem()
    {
        return mSystemManager->registerSystem<T>();
    }

    template <typename T>
    void setSystemMask(ComponentMask mask)
    {
        mSystemManager->setComponentMask<T>(mask);
    }

    void printAllComponents()
    {
        mComponentManager->printAllComponents();
    }
    void printAllSystems()
    {
        mSystemManager->printAllSystems();
    }

    private:
        std::unique_ptr<EntityManager> mEntityManager;
        std::unique_ptr<SystemManager> mSystemManager;
        std::unique_ptr<ComponentManager> mComponentManager;
};
