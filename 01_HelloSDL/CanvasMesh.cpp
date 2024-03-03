#include "CanvasMesh.h"

#include <stdexcept>

CanvasMesh::CanvasMesh() : Mesh()
{
	std::vector<DataTypes::Vertex> verts(4);
	verts[0].position = glm::vec3(-1.0f, -1.0f, -1.0f);
	verts[1].position = glm::vec3(1.0f, -1.0f, -1.0f);
	verts[2].position = glm::vec3(1.0f, 1.0f, -1.0f);
	verts[3].position = glm::vec3(-1.0f, 1.0f, -1.0f);

	std::vector<uint32_t> inds = {
		0, 1, 2,
		2, 3, 0
	};

	std::vector<DataTypes::Texture> texts(10);
	texts[0] = DataTypes::Texture(create_texture_from_file("Textures/sun.jpg"), "diffuse");
	texts[1] = DataTypes::Texture(create_texture_from_file("Textures/venus.jpg"), "diffuse");
	texts[2] = DataTypes::Texture(create_texture_from_file("Textures/mercury.jpg"), "diffuse");
	texts[3] = DataTypes::Texture(create_texture_from_file("Textures/earth.jpg"), "diffuse");
	texts[4] = DataTypes::Texture(create_texture_from_file("Textures/mars.jpg"), "diffuse");
	texts[5] = DataTypes::Texture(create_texture_from_file("Textures/jupiter.jpg"), "diffuse");
	texts[6] = DataTypes::Texture(create_texture_from_file("Textures/saturn.jpg"), "diffuse");
	texts[7] = DataTypes::Texture(create_texture_from_file("Textures/uranus.jpg"), "diffuse");
	texts[8] = DataTypes::Texture(create_texture_from_file("Textures/neptune.jpg"), "diffuse");

	std::vector<std::string> skyboxFaces = {
		"Textures/skybox/right.jpg",
		"Textures/skybox/left.jpg",
		"Textures/skybox/top.jpg",
		"Textures/skybox/bottom.jpg",
		"Textures/skybox/front.jpg",
		"Textures/skybox/back.jpg"
	};

	texts[9] = DataTypes::Texture(create_cubemap_from_files(skyboxFaces), "cubemap");

	set_vertices(verts);
	set_indices(inds);
	set_textures(texts);
	setup_mesh();
}

CanvasMesh::~CanvasMesh() {}
