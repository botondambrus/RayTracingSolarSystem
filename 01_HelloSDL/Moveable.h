#pragma once

class Movable 
{
protected:
    float orbitSpeed;
    float orbitAngle;
    float orbitRadius;

public:
    Movable(float orbitSpeed, float orbitAngle, float orbitRadius) : 
        orbitSpeed(orbitSpeed), orbitAngle(orbitAngle), orbitRadius(orbitRadius) {};

    virtual void move(float deltaTime) {};
};