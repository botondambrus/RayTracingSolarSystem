#include "Sun.h"

cSun::cSun(float radius, float weight, int materialIndex, int textureIndex) : 
	SpaceObject(glm::vec3(0.0f), radius, materialIndex, 0.0f, 0.0f, 0.0f, textureIndex) {}

cSun::~cSun() {}