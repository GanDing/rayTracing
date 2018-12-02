#pragma once

#include <glm/glm.hpp>
#include "Material.hpp"

class Intersect {
public:
	Intersect();

	float t;
	glm::vec4 n;
	Material *m_material;
};
