#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "DataTypes.h"

class Shader {
private:
	GLuint program_id;

	void check_for_errors(GLuint shader, std::string type);

public:
	Shader(const char *vertexShaderSource, const char *fragmentShaderSource);
	~Shader();

	GLuint getProgramID();

	void activate();

	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	
	void setVec3(const std::string& name, glm::vec3 value) const;
	void setVec3(const std::string& name, float x, float y, float z) const;
	void setMat4(const std::string& name, glm::mat4 value) const;

	void setMaterial(const std::string& name, DataTypes::Material material) const;
	void setLight(const std::string& name, DataTypes::Light light) const;

	void setMaterialArr(const std::string& name, std::vector<DataTypes::Material> materials) const;
	void setLightArr(const std::string& name, std::vector<DataTypes::Light> lights) const;
};