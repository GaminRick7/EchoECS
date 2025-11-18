#pragma once
#include <cassert>
#include <iostream>
#include <unordered_map>

#include "System.h"
#include "Types.h"


class SystemManager {
    public:
    template <typename T>
    std::shared_ptr<T> registerSystem()
    {
        const char* name = typeid(T).name();
        assert(!mSystems.contains(name));
        auto system = std::make_shared<T>();
        mSystems[name] = system;
        return system;
    }
    template <typename T>
    void setComponentMask(const ComponentMask mask)
    {
        const char * name = typeid(T).name();
        assert(mSystems.contains(name));
        mMasks[name] = mask;
    }

    void EntityDestroyed(Entity entity)
    {
        for (auto const& pair : mSystems)
        {
            auto system = pair.second;
            system->mEntities.erase(entity);
        }
    }

    void EntityMaskChanged(Entity entity, ComponentMask mask)
    {
        for (auto const& pair : mSystems)
        {
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& systemMask = mMasks[type];
            if ((systemMask & mask) == systemMask)
            {
                std::cout << "Success!" << entity << std::endl;
                system->mEntities.insert(entity);
            }
            else
            {
                system->mEntities.erase(entity);
            }
            printAllSystems();
        }
    }

    void printAllSystems()
    {
        for (auto const& pair : mSystems)
        {
            std::cout << "System mask: " << mMasks[pair.first] << std::endl;
            for (const auto& e : pair.second->mEntities)
            {
                std::cout << e << std::endl;
            }
        }
    }

    private:
        // Map from system type string pointer to a signature
        std::unordered_map<const char*, ComponentMask> mMasks{};

        // Map from system type string pointer to a system pointer
        std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};
};
