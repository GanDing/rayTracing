// Fall 2018

#pragma once
#include <glm/glm.hpp>
#include "BumpMaterial.hpp"

class Material {
public:
  virtual ~Material();
  virtual glm::vec3 get_kd();
  virtual glm::vec3 get_kd(glm::vec2 uv);
  virtual glm::vec3 get_ks();
  virtual float get_shininess();
  virtual float get_trans();
  virtual void set_bumpMaterial(BumpMaterial *bumpMaterial);
  virtual glm::vec4 get_bumpNormal(glm::vec2 uv, glm::vec4 normal);
  BumpMaterial *bumpMaterial = 0;
protected:
 	Material();
};
