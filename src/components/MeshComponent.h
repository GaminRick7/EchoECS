#pragma once
#include <cstdint>

using MeshHandle = uint32_t;

struct MeshComponent
{
    MeshHandle mesh = 0;
}