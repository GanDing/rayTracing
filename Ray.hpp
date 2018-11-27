#pragma once

#include <glm/glm.hpp>

class Ray {
public:
	Ray(glm::dvec4 origin, glm::dvec4 vec);
	Ray();
	glm::dvec4 origin;
	glm::dvec4 vec;
};

