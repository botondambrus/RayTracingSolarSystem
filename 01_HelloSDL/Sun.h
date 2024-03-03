#pragma once

#include <glm/glm.hpp>
#include "SpaceObject.h"

class cSun : public SpaceObject
{
public:
    cSun(float radius, float weight, int materialIndex, int textureIndex);
    ~cSun();
};