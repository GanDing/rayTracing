// Fall 2018

#pragma once
#include <glm/glm.hpp>

class Material {
public:
  virtual ~Material();
  virtual glm::vec3 get_kd();
  virtual glm::vec3 get_ks();
  virtual double get_shininess();

protected:
  Material();
};
