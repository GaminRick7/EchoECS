cmake_minimum_required(VERSION 3.29)
project(ECS)

set(CMAKE_CXX_STANDARD 20)

add_executable(ECS src/main.cpp
        core/EntityManager.cpp
        core/EntityManager.h
        core/Types.h
        core/ComponentArray.cpp
        core/ComponentArray.h
        core/ComponentManager.cpp
        core/ComponentManager.h
        core/System.cpp
        core/System.h
        core/SystemManager.cpp
        core/SystemManager.h
        core/Coordinator.cpp
        core/Coordinator.h
        src/WindowManager.cpp
        src/WindowManager.h
        lib/external/dependencies/glad/glad.c
        src/components/MeshComponent.h
        src/components/Transform.h
        core/math/vec3.h
        core/math/vec2.h
        core/math/vec4.h
        core/math/mat4.h
)


find_package(SDL2 REQUIRED COMPONENTS SDL2)
target_link_libraries(ECS PRIVATE SDL2::SDL2)
target_include_directories(ECS PRIVATE ${SDL2_INCLUDE_DIRS})

target_include_directories(ECS PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/external/dependencies
)
