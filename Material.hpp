// Fall 2018

#pragma once
#include <glm/glm.hpp>

class Material {
public:
  virtual ~Material();
  virtual glm::vec3 get_kd();
  virtual glm::vec3 get_kd(float u, float v);
  virtual glm::vec3 get_ks();
  virtual float get_shininess();
  virtual float get_trans();

protected:
  Material();
};
