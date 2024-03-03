#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 eye, glm::vec3 worldUp, float pitch, float yaw) : eye(eye), worldUp(worldUp), pitch(pitch), yaw(yaw)
{
    speed = 30.0f;
    sensitivity = 0.1f;
    moveForward = moveRight = moveUp = 0;

    setViewMatrix(eye, worldUp, pitch, yaw);
    setProjectionMatrix(glm::radians(70.0f), 1024.0f, 768.0f, 0.01f, 1000.0f);
}

Camera::~Camera(void) {}

void Camera::calculateViewMatrix()
{
    frontAxis = glm::normalize(glm::vec3(
        cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
		sin(glm::radians(pitch)),
		sin(glm::radians(yaw)) * cos(glm::radians(pitch))
    ));

    sideAxis = glm::normalize(glm::cross(frontAxis, worldUp));
    upAxis = glm::normalize(glm::cross(sideAxis, frontAxis));

    viewMatrix = glm::lookAt(eye, eye + frontAxis, upAxis);
    viewProjectionMatrix = projectionMatrix * viewMatrix;
}

void Camera::setViewMatrix(glm::vec3 eye, glm::vec3 worldUp, float pitch, float yaw) 
{
    this->eye = eye;
    this->worldUp = worldUp;
    this->pitch = pitch;
    this->yaw = yaw;

    calculateViewMatrix();
}

void Camera::setProjectionMatrix(float fov, float width, float height, float nearPlane, float farPlane) 
{
    this->fov = fov;
    this->width = width;
    this->height = height;

    projectionMatrix = glm::perspective(fov, width / height, nearPlane, farPlane);
    viewProjectionMatrix = projectionMatrix * viewMatrix;
}

void Camera::setSpeed(float value)
{
    speed = value;
}

glm::mat4 Camera::getViewMatrix() const
{
    return viewMatrix;
}

glm::vec3 Camera::getEyePosition() const
{
    return eye;
}

glm::vec3 Camera::getForwardDirection() const
{
    return frontAxis;
}

glm::vec3 Camera::getSideDirection() const
{
    return sideAxis;
}

glm::vec3 Camera::getUpDirection() const
{
    return upAxis;
}

float Camera::getFOV() const
{
    return fov;
}

float Camera::getWidth() const
{
    return width;
}

float Camera::getHeight() const
{
    return height;
}

glm::mat4 Camera::getProjectionMatrix() const
{
    return projectionMatrix;
}

glm::mat4 Camera::getViewProjectionMatrix() const
{
    return viewProjectionMatrix;
}

void Camera::resize(int width, int height)
{
    setProjectionMatrix(glm::radians(60.0f), width, height, 0.01f, 1000.0f);
}

void Camera::updateView(float relPitch, float relYaw)
{
    yaw += relPitch * sensitivity;
	pitch -= relYaw * sensitivity;

	if (pitch > 89.0f)
		pitch = 89.0f;
	else if (pitch < -89.0f)
		pitch = -89.0f;

    calculateViewMatrix();
}

void Camera::update(float deltaTime)
{
    if (moveForward || moveRight || moveUp) 
	{
        glm::vec3 direction = glm::normalize(frontAxis * moveForward + sideAxis * moveRight + upAxis * moveUp);
		
        eye += direction * speed * deltaTime;
		
        calculateViewMatrix();
	}
}

void Camera::handleKeyDownEvent(const SDL_KeyboardEvent& key)
{
    switch (key.keysym.scancode)
    {
        case SDL_SCANCODE_W:
            moveForward = 1.0f;
            break;
        case SDL_SCANCODE_S:
            moveForward = -1.0f;
            break;
        case SDL_SCANCODE_A:
	        moveRight = -1.0f;
		    break;
        case SDL_SCANCODE_D:
            moveRight = 1.0f;
            break;
        case SDL_SCANCODE_SPACE:
            moveUp = 1.0f;
		    break;
        case SDL_SCANCODE_LCTRL:
            moveUp = -1.0f;
            break;
        default:
            break;
    }
}

void Camera::handleKeyUpEvent(const SDL_KeyboardEvent& key)
{
    switch (key.keysym.scancode)
    {
        case SDL_SCANCODE_W:
        case SDL_SCANCODE_S:
		    moveForward = 0.0f;
		    break;
        case SDL_SCANCODE_A:
        case SDL_SCANCODE_D:
            moveRight = 0.0f;
            break;
        case SDL_SCANCODE_SPACE:
        case SDL_SCANCODE_LCTRL:
		    moveUp = 0.0f;
		    break;
        default:
            break;
    }
}

void Camera::handleMouseMovedEvent(const SDL_MouseMotionEvent& mouse)
{
    if (mouse.state & SDL_BUTTON_LMASK) 
    {
        updateView(mouse.xrel, mouse.yrel);
    }
}
