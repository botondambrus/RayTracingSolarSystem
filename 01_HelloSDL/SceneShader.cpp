#include "SceneShader.h"

SceneShader::SceneShader(const char* vertexShaderSource, const char* fragmentShaderSource) : Shader(vertexShaderSource, fragmentShaderSource) {}

SceneShader::~SceneShader() {}

void SceneShader::setPlanet(const std::string& name, SpaceObject* planet) const
{
	setVec3(name + ".position", planet->get_position());
	setFloat(name + ".radius", planet->get_radius());
	setInt(name + ".materialIndex", planet->get_material_index());
	setInt(name + ".textureIndex", planet->get_texture_index());
}

void SceneShader::setCamera(const std::string& name, Camera* camera) const
{
	setVec3(name + ".position", camera->getEyePosition());

	setVec3(name + ".frontAxis", camera->getForwardDirection());
	setVec3(name + ".upAxis", camera->getUpDirection());
	setVec3(name + ".sideAxis", camera->getSideDirection());

	setFloat(name + ".fov", camera->getFOV());
	setFloat(name + ".width", camera->getWidth());
	setFloat(name + ".height", camera->getHeight());
}

void SceneShader::setPlanetArr(const std::string& name, std::vector<SpaceObject*> planets) const
{
	for (size_t i = 0; i < planets.size(); i++)
	{
		std::string varName = name + "[" + std::to_string(i) + "]";
		setPlanet(varName, planets[i]);
	}
}
