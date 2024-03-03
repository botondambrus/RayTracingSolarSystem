#pragma once

#include <vector>

#include "SolarSystem.h"
#include "Planet.h"

class Scene
{
private:
	SolarSystem* solarSystem;

	std::vector<SpaceObject*> initPlanetsVector();
	void initSolarSystem(uint32_t nrPlanets, std::vector<SpaceObject*> planets);
public:
	Scene(uint32_t nrPlanets = 9);
	~Scene();

	void set_solar_system(SolarSystem* solarSystem);
	
	SolarSystem* get_solar_system();
};