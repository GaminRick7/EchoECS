#pragma once

#include <bitset>
#include <cstdint>

typedef std::uint32_t Entity;
constexpr Entity MAX_ENTITIES = 5000;

// A simple type alias
typedef std::uint8_t ComponentType;

// Used to define the size of arrays later on
constexpr ComponentType MAX_COMPONENTS = 32;

// maybe change later to a unit_32 to ensure closely packed since bitset does not guarantee size
typedef std::bitset<MAX_COMPONENTS> ComponentMask;
