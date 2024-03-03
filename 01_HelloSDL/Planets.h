#pragma once

#include "Sun.h"
#include "Planet.h"

const float sizeScaleFactor = 5.0f;
const float speedScaleFactor = 0.01f;

class Sun : public cSun {
public:
    Sun(int materialIndex = 0, int textureIndex = -1) : cSun(10.0f * sizeScaleFactor, 3000.0f, materialIndex, textureIndex) {}
    ~Sun() {}
};

class Mercury : public Planet {
public:
    Mercury(int materialIndex = 0, int textureIndex = -1) : Planet(0.383f * sizeScaleFactor, 0.330f, 47.87f * speedScaleFactor, 0.0f, 57.9f, materialIndex, textureIndex) {}
    ~Mercury() {}
};

class Venus : public Planet {
public:
    Venus(int materialIndex = 0, int textureIndex = -1) : Planet(0.569f * sizeScaleFactor, 4.867f, 35.02f * speedScaleFactor, 0.0f, 71.2f, materialIndex, textureIndex) {}
    ~Venus() {}
};

class Earth : public Planet {
public:
    Earth(int materialIndex = 0, int textureIndex = -1) : Planet(0.731f * sizeScaleFactor, 5.972f, 29.78f * speedScaleFactor, 0.0f, 129.6f, materialIndex, textureIndex) {
        this->add_moon(new Moon(0.2724f * sizeScaleFactor , 102.2f * speedScaleFactor, 0.0f, 38.4f, this, 0.3f));
    }

    ~Earth() {}
};
class Mars : public Planet {
public:
    Mars(int materialIndex = 0, int textureIndex = -1) : Planet(0.921f * sizeScaleFactor, 0.641f, 24.07f * speedScaleFactor, 0.0f, 168.9f, materialIndex, textureIndex) {
        moons.push_back(new Moon(0.124f * sizeScaleFactor, 240.08f * speedScaleFactor, 0.0f, 9.378f, this, 0.3f)); // Phobos
        moons.push_back(new Moon(0.102f * sizeScaleFactor, 76.67f * speedScaleFactor, 0.0f, 23.458f, this, 0.4f)); // Deimos
    }

    ~Mars() {}
};

class Jupiter : public Planet {
public:
    Jupiter(int materialIndex = 0, int textureIndex = -1) : Planet(1.53f * sizeScaleFactor, 1898.0f, 13.07f * speedScaleFactor, 0.0f, 192.5f, materialIndex, textureIndex) {}
    ~Jupiter() {}
};

class Saturn : public Planet {
public:
    Saturn(int materialIndex = 0, int textureIndex = -1) : Planet(1.32f * sizeScaleFactor, 568.0f, 9.68f * speedScaleFactor, 0.0f, 233.5f, materialIndex, textureIndex) {}
    ~Saturn() {}
};

class Uranus : public Planet {
public:
    Uranus(int materialIndex = 0, int textureIndex = -1) : Planet(1.23f * sizeScaleFactor, 86.8f, 6.8f * speedScaleFactor, 0.0f, 258.5f, materialIndex, textureIndex) {}
    ~Uranus() {}
};

class Neptune : public Planet {
public:
    Neptune(int materialIndex = 0, int textureIndex = -1) : Planet(1.10f * sizeScaleFactor, 102.0f, 5.43f * speedScaleFactor, 0.0f, 280.1f, materialIndex, textureIndex) {}
    ~Neptune() {}
};