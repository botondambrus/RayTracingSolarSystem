#include "Planet.h"
#include "DataTypes.h"

Planet::Planet(float radius, float weight, float orbitSpeed, float orbitAngle, float orbitRadius, int materialIndex, int textureIndex) :
	SpaceObject(glm::vec3(0.0f), radius, materialIndex, orbitSpeed, orbitAngle, orbitRadius, textureIndex)
{
	this->radius = radius;
	this->weight = weight;
}

Planet::~Planet() {}

float Planet::get_weight() const
{
	return weight;
}

void Planet::add_moon(Moon* moon)
{
	moons.push_back(moon);
}

std::vector<Moon*> Planet::get_moons() const
{
	return moons;
}