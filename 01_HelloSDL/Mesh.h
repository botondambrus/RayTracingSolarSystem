#pragma once

#include <vector>

#include "DataTypes.h"
#include "Shader.h"

class Mesh
{
protected:
    std::vector<DataTypes::Vertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<DataTypes::Texture> textures;

    uint32_t vertexArrayObject, vertexBufferObject, elementBufferObject;

public:
    Mesh(): vertexArrayObject(0), vertexBufferObject(0), elementBufferObject(0) { }
    Mesh(const std::vector<DataTypes::Vertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<DataTypes::Texture>& textures);
    ~Mesh();

    void setup_mesh();
    void set_vertices(const std::vector<DataTypes::Vertex>& vertices);
    void set_indices(const std::vector<uint32_t>& indices);
    void set_textures(const std::vector<DataTypes::Texture>& textures);

    void add_texture(GLuint texture_id);
    
    static GLuint create_texture_from_file(const char* texturePath);
    static GLuint create_cubemap_from_files(std::vector<std::string> filePaths);

    virtual void draw(Shader *shader);

    void destroy();
};