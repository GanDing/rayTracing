// Fall 2018

#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

class BumpMaterial {
public:
	BumpMaterial(std::string imageName);
  	// BumpMaterial(std::string image);
  	~BumpMaterial();
  	glm::vec4 get_bumpNormal(glm::vec2 uv, glm::vec4 normal);

private:
  	std::vector<unsigned char> image;
	uint w;
	uint h;
	float get_texture(uint x, uint y);
	float sum_color(float x, float y);
};
