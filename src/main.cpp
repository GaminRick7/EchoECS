#include <iostream>
#include <SDL2/SDL.h>

#include "../core/Coordinator.h"
#include "WindowManager.h"

struct PhysicsComponent
{
    float gravity = 9.81f;
};

struct AIComponent
{
    float gravity = 9.81f;
};
struct TransformComponent
{
    float gravity = 9.81f;
};

class PhysicsSystem : public System
{};

class AISystem : public System
{};

Coordinator gCoordinator;
WindowManager gWindow;
int main()

{
    gCoordinator.init();
    gWindow.Init("ECS Engine", 900, 600, 0,0);

    gCoordinator.registerComponent<PhysicsComponent>();
    gCoordinator.registerComponent<AIComponent>();
    gCoordinator.registerComponent<TransformComponent>();

    auto physicsSystem = gCoordinator.registerSystem<PhysicsSystem>();
    ComponentMask mask;
    mask.set(gCoordinator.getComponentType<PhysicsComponent>());
    mask.set(gCoordinator.getComponentType<AIComponent>());
    gCoordinator.setSystemMask<PhysicsSystem>(mask);

    auto aiSystem = gCoordinator.registerSystem<AISystem>();
    ComponentMask mask2;
    mask2.set(gCoordinator.getComponentType<PhysicsComponent>());
    mask2.set(gCoordinator.getComponentType<TransformComponent>());
    gCoordinator.setSystemMask<AISystem>(mask2);

    //PHYSICS + AI
    Entity e = gCoordinator.createEntity();
    gCoordinator.addComponent<PhysicsComponent>(e, PhysicsComponent());
    gCoordinator.addComponent<AIComponent>(e, AIComponent());
    std::cout << mask << std::endl;

    //PHYSICS + AI + TRANSFORM
    Entity e1 = gCoordinator.createEntity();
    gCoordinator.addComponent<PhysicsComponent>(e1, PhysicsComponent());
    gCoordinator.addComponent(e1, AIComponent());
    gCoordinator.addComponent<TransformComponent>(e1, TransformComponent());

    gCoordinator.printAllSystems();

    std::cout << "AFTER" << std::endl;

    gCoordinator.removeComponent<AIComponent>(e1);
    gCoordinator.printAllSystems();

    bool running = true;
    while (running){
        running = gWindow.ProcessEvents();
        gWindow.Update();
        SDL_Delay(16);
    }

    gWindow.Shutdown();
    return 0;
}
