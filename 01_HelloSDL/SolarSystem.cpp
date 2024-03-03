#include "SolarSystem.h"
#include "Planets.h"

SolarSystem::SolarSystem(std::vector<SpaceObject*> planets)
{
    canvasMesh = new CanvasMesh();
    sceneShader = new SceneShader("planet.vert", "planet.frag");

    canvas = new Canvas();
    canvas->attach_mesh(canvasMesh);
    canvas->attach_shader(sceneShader);

    DataTypes::Material material;
    material.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    material.diffuse = glm::vec3(0.2f, 0.2f, 0.2f);
    material.specular = glm::vec3(0.3f, 0.3f, 0.3f);
    material.shininess = 7;

    DataTypes::Light light1;
    light1.position = glm::vec3(0.0f, 0.0f, 0.0f);
    light1.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    light1.diffuse = glm::vec3(0.3f, 0.3f, 0.3f);
    light1.specular = glm::vec3(0.9f, 0.9f, 0.9f);
    light1.constant = 1.0f;
    light1.linear = 0.09f;
    light1.quadratic = 0.032f;

    DataTypes::Light light2;
    light2.position = glm::vec3(0.1f, 0.1f, 0.1f);
    light2.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    light2.diffuse = glm::vec3(0.3f, 0.3f, 0.3f);
    light2.specular = glm::vec3(0.9f, 0.9f, 0.9f);
    light2.constant = 1.0f;
    light2.linear = 0.09f;
    light2.quadratic = 0.032f;

    materials.push_back(material);
    lights.push_back(light1);
    lights.push_back(light2);

    this->planets = planets;

    addMoonsToSpaceObjects();
}

SolarSystem::~SolarSystem()
{
    for (auto& planet : planets)
    {
        delete planet;
    }

    delete canvas;
    delete canvasMesh;
    delete sceneShader;
}

void SolarSystem::addPlanet(Planet* planet)
{
    planets.push_back(planet);
}

void SolarSystem::draw(Camera* camera)
{
    sceneShader->setCamera("camera", camera);
    
    sceneShader->setLightArr("lights", lights);
    sceneShader->setInt("lightCount", lights.size());
    
    sceneShader->setMaterialArr("materials", materials);
    sceneShader->setInt("materialCount", materials.size());

    sceneShader->setPlanetArr("planets", planets);
    sceneShader->setInt("planetCount", planets.size());
    sceneShader->setInt("maxDepth", maxDepth);

    canvas->allignToCamera(camera);

    sceneShader->setMat4("model", canvas->getTransform());
    sceneShader->setMat4("view", camera->getViewMatrix());
    sceneShader->setMat4("projection", camera->getProjectionMatrix());

    canvas->draw();
}

void SolarSystem::update(float deltaTime)
{
    for (auto& planet : planets)
    {
        planet->move(deltaTime);
    }
}

void SolarSystem::addMoonsToSpaceObjects()
{
    std::vector<SpaceObject*> moons;

    for (int i = 1; i < planets.size(); ++i)
    {
        for (const auto& moon : ((Planet*)planets[i])->get_moons())
        {
			moons.push_back(moon);
		}
	}

    for (const auto& moon : moons)
    {
        planets.push_back(moon);
    }
}

void SolarSystem::handleKeyUpEvent(const SDL_KeyboardEvent& key)
{
    switch (key.keysym.scancode)
    {
        case SDL_SCANCODE_N:
            if (maxDepth > 1)
                maxDepth--;
            break;

        case SDL_SCANCODE_M:
			if (maxDepth < 30)
				maxDepth++;
			break;
        default:
            break;
    }
}

