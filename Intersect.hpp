#pragma once

#include <glm/glm.hpp>
#include "Material.hpp"

class Intersect {
public:
	Intersect();

	double t;
	glm::dvec4 n;
	Material *m_material;
};
