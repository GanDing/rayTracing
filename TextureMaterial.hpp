#pragma once

#include <glm/glm.hpp>

#include "Material.hpp"

class TextureMaterial : public Material {
public:
	TextureMaterial(std::string imageName, const glm::vec3& ks, float shininess, float trans);
	~TextureMaterial();
	glm::vec3 get_kd();
	glm::vec3 get_kd(glm::vec2 uv);
  	glm::vec3 get_ks();
  	float get_shininess();
  	float get_trans();

private:
	std::vector<unsigned char> image;
	uint w;
	uint h;
	glm::vec3 m_ks;
 	float m_shininess;
 	float m_trans;

 	glm::vec3 get_texture(uint x, uint y);
};
