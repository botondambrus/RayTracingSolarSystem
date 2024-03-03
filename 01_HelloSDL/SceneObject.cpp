#include "SceneObject.h"

#include <glm/gtc/matrix_transform.hpp>

void SceneObject::setPosition(float x, float y, float z)
{
	mPosition = glm::vec3(x, y, z);
}

void SceneObject::setRotation(float xAngle, float yAngle, float zAngle)
{
	mRotation = glm::vec3(xAngle, yAngle, zAngle);
}

void SceneObject::setScale(float xScale, float yScale, float zScale)
{
	mScale = glm::vec3(xScale, yScale, zScale);
}

void SceneObject::translate(float x, float y, float z)
{
	mPosition += glm::vec3(x, y, z);
}

void SceneObject::rotate(float xAngle, float yAngle, float zAngle)
{
	mRotation += glm::vec3(xAngle, yAngle, zAngle);
}

void SceneObject::scale(float xScale, float yScale, float zScale)
{
	mScale = glm::vec3(mScale.x * xScale, mScale.y * yScale, mScale.z * zScale);
}

glm::vec3 SceneObject::getPosition() const
{
	return mPosition;
}

glm::vec3 SceneObject::getRotation() const
{
	return mRotation;
}

glm::vec3 SceneObject::getScale() const
{
	return mScale;
}

glm::mat4 SceneObject::getTransform() const
{
	glm::mat4 transform(1.0f);

	transform = glm::rotate(transform, mRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	transform = glm::rotate(transform, mRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::rotate(transform, mRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	transform = glm::scale(transform, mScale);

	transform = glm::translate(transform, mPosition);

	return transform;
}