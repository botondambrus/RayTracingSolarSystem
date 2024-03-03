#pragma once

#include <string>
#include "glm/glm.hpp"

namespace DataTypes {
    
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };

    struct Texture {
        uint32_t id;
        std::string type;

        Texture() : id(0), type("") {}
        Texture(std::string type) : id(0), type(type) {}
        Texture(uint32_t id, std::string type) : id(id), type(type) {}
    };

    struct Material {
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		
        float shininess;
	};

    struct Light {
        glm::vec3 position;
        
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;

        float constant;
        float linear;
        float quadratic;
    };
}