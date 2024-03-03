#pragma once

#include "Moveable.h"
#include <glm/glm.hpp>

class SpaceObject : public Movable
{
protected:
	glm::vec3 position;
	float radius;
	int materialIndex;
	int textureIndex;

public:
	SpaceObject(glm::vec3 position, float radius, int materialIndex, float orbitSpeed, float orbitAngle, float orbitRadius, int textureIndex = -1);

	void set_position(glm::vec3 position);
	glm::vec3 get_position() const;

	void set_radius(float radius);
	float get_radius() const;

	void set_material_index(int materialIndex);
	int get_material_index() const;

	void set_texture_index(int textureIndex);
	int get_texture_index() const;

	void move(float deltaTime) override;
};