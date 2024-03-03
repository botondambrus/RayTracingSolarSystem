#include "Shader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	std::string vertexShaderCode, fragmentShaderCode;

	try 
	{
		std::ifstream vertexShaderFile, fragmentShaderFile;
		
		vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		vertexShaderFile.open(vertexShaderSource);
		fragmentShaderFile.open(fragmentShaderSource);

		std::stringstream vertexShaderFileContent, fragmentShaderFileContent;
		vertexShaderFileContent << vertexShaderFile.rdbuf();
		fragmentShaderFileContent << fragmentShaderFile.rdbuf();

		vertexShaderCode = vertexShaderFileContent.str();
		fragmentShaderCode = fragmentShaderFileContent.str();
	}
	catch (std::ifstream::failure e)
	{
		throw std::runtime_error("Failed to load shader file");
	}

	const char *vShaderCode = vertexShaderCode.c_str();
	const char *fShaderCode = fragmentShaderCode.c_str();

	GLuint vertexShaderId, fragmentShaderId;

	// Creating the vertex shader
	vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vShaderCode, NULL);
	glCompileShader(vertexShaderId);
	check_for_errors(vertexShaderId, "VERTEX");

	// Creating the fragment shader
	fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShaderId);
	check_for_errors(fragmentShaderId, "FRAGMENT");

	// Creating the shader program
	program_id = glCreateProgram();
	glAttachShader(program_id, vertexShaderId);
	glAttachShader(program_id, fragmentShaderId);
	glLinkProgram(program_id);
	check_for_errors(program_id, "PROGRAM");

	// Deleting the shaders
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
}

Shader::~Shader()
{
	glDeleteProgram(program_id);
}

void Shader::check_for_errors(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			throw std::runtime_error("Failed to compile shader: " + type + "\n" + infoLog);
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			throw std::runtime_error("Failed to link shader: " + type + "\n" + infoLog);
		}
	}
}

GLuint Shader::getProgramID()
{
	return program_id;
}

void Shader::activate()
{
	glUseProgram(program_id);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(program_id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(program_id, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, glm::vec3 value) const 
{
	glUniform3fv(glGetUniformLocation(program_id, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const 
{
	glUniform3f(glGetUniformLocation(program_id, name.c_str()), x, y, z);
}

void Shader::setMat4(const std::string& name, glm::mat4 mat) const 
{
	glUniformMatrix4fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMaterial(const std::string& name, DataTypes::Material material) const
{
	setVec3(name + ".ambient", material.ambient);
	setVec3(name + ".diffuse", material.diffuse);
	setVec3(name + ".specular", material.specular);
	setFloat(name + ".shininess", material.shininess);
}

void Shader::setLight(const std::string& name, DataTypes::Light light) const
{
	setVec3(name + ".position", light.position);

	setVec3(name + ".ambient", light.ambient);
	setVec3(name + ".diffuse", light.diffuse);
	setVec3(name + ".specular", light.specular);
	
	setFloat(name + ".constant", light.constant);
	setFloat(name + ".linear", light.linear);
	setFloat(name + ".quadratic", light.quadratic);
}

void Shader::setMaterialArr(const std::string& name, std::vector<DataTypes::Material> materials) const
{
	for (size_t i = 0; i < materials.size(); ++i)
	{
		std::string varName = name + "[" + std::to_string(i) + "]";
		setMaterial(varName, materials[i]);
	}
}

void Shader::setLightArr(const std::string& name, std::vector<DataTypes::Light> lights) const
{
	for (size_t i = 0; i < lights.size(); ++i)
	{
		std::string varName = name + "[" + std::to_string(i) + "]";
		setLight(varName, lights[i]);
	}
}
