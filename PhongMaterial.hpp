// Fall 2018

#pragma once

#include <glm/glm.hpp>

#include "Material.hpp"

class PhongMaterial : public Material {
public:
  PhongMaterial(const glm::vec3& kd, const glm::vec3& ks, float shininess, float trans);
  virtual ~PhongMaterial();
  glm::vec3 get_kd();
  glm::vec3 get_kd(glm::vec2 uv);
  glm::vec3 get_ks();
  float get_shininess();
  float get_trans();

private:
  glm::vec3 m_kd;
  glm::vec3 m_ks;

  float m_shininess;
  float m_trans;
};
