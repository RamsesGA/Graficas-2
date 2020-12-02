#pragma once
#include "CTexture.h"

#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

struct Matrices{

	glm::mat4 World;
	glm::mat4 Projection;
	glm::vec4 Color;
};

struct ViewCB{

	glm::mat4 View;
};

struct Vertex {

	glm::vec3 position;
	glm::vec2 texCoords;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 bitangent;
};

struct Texture {

	std::string type;
	std::string path;
	CTexture* texture;
};