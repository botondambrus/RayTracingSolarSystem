#include "SpaceObject.h"

SpaceObject::SpaceObject(glm::vec3 position, float radius, int materialIndex, float orbitSpeed, float orbitAngle, float orbitRadius, int textureIndex) :
	position(position),
	radius(radius),
	materialIndex(materialIndex),
	textureIndex(textureIndex),
	Movable(orbitSpeed, orbitAngle, orbitRadius)
{
}

void SpaceObject::set_position(glm::vec3 position)
{
	this->position = position;
}

glm::vec3 SpaceObject::get_position() const
{
	return position;
}

void SpaceObject::set_radius(float radius)
{
	this->radius = radius;
}

float SpaceObject::get_radius() const
{
	return radius;
}

void SpaceObject::set_material_index(int materialIndex)
{
	this->materialIndex = materialIndex;
}

int SpaceObject::get_material_index() const
{
	return materialIndex;
}

void SpaceObject::set_texture_index(int textureIndex)
{
	this->textureIndex = textureIndex;
}

int SpaceObject::get_texture_index() const
{
	return textureIndex;
}

void SpaceObject::move(float deltaTime)
{
	orbitAngle += orbitSpeed * deltaTime;

	position.x = orbitRadius * cos(orbitAngle);
	position.z = orbitRadius * sin(orbitAngle);
}