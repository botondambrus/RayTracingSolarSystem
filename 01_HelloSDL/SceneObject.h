#pragma once

#include <glm/glm.hpp>

class SceneObject {
protected:
    glm::vec3 mPosition;
    glm::vec3 mRotation;
    glm::vec3 mScale;

public:
    SceneObject() : mPosition(0.0f), mRotation(0.0f), mScale(1.0f) {};

    void setPosition(float x, float y, float z);
    void setRotation(float xAngle, float yAngle, float zAngle);
    void setScale(float xScale, float yScale, float zScale);

    void translate(float x, float y, float z);
    void rotate(float xAngle, float yAngle, float zAngle);
    void scale(float xScale, float yScale, float zScale);

    glm::vec3 getPosition() const;
    glm::vec3 getRotation() const;
    glm::vec3 getScale() const;

    glm::mat4 getTransform() const;
};