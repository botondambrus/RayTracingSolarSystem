#pragma once

#include "Shader.h"
#include "Planet.h"
#include "Camera.h"

class SceneShader : public Shader
{
public:
	SceneShader(const char* vertexShaderSource, const char* fragmentShaderSource);
	~SceneShader();

	void setPlanet(const std::string& name, SpaceObject* planet) const;
	void setCamera(const std::string& name, Camera* camera) const;
	
	void setPlanetArr(const std::string& name, std::vector<SpaceObject*> planets) const;
};