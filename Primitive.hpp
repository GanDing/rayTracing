// Fall 2018

#pragma once

#include <glm/glm.hpp>
#include "Ray.hpp"
#include "Intersect.hpp"

class Primitive {
public:
  virtual ~Primitive();
  virtual Intersect intersect(Ray ray);
  bool ray_intersect_triangle(Ray ray, glm::dvec3 p0, glm::dvec3 p1, glm::dvec3 p2, double &t);
};

class NonhierSphere : public Primitive {
public:
  NonhierSphere(const glm::vec3& pos, double radius)
    : m_pos(glm::dvec4(pos, 1)), m_radius(radius)
  {
  }
  NonhierSphere() {}
  virtual ~NonhierSphere();
  virtual Intersect intersect(Ray ray);

protected:
  glm::dvec4 m_pos;
  double m_radius;
};

class Sphere : public NonhierSphere {
public:
  Sphere(const glm::vec3& pos, double radius) {}
  Sphere();
  virtual ~Sphere();
  // Intersect intersect(Ray ray);
};

class NonhierBox : public Primitive {
public:
  NonhierBox() {}
  NonhierBox(const glm::vec3& pos, double size);
  NonhierBox(const glm::vec3& minPos, const glm::vec3& maxPos);
  void initialTriangles(glm::vec3 minPos, glm::vec3 maxPos);
  
  virtual ~NonhierBox();
  virtual Intersect intersect(Ray ray);

protected:
  glm::dvec4 m_pos;
  glm::dvec3 bounds[2];
  glm::dvec3 triangle[12][3];
};

class Cube : public NonhierBox {
public:
  Cube();
  Cube(const glm::vec3& pos, double size) {}
  virtual ~Cube();
};

// class NonhierCyliner : public Primitive {
// public:
//   NonhierCyliner();
//   virtual ~NonhierCyliner();
//   Intersect intersect(Ray ray);
//   double r;
// };

class Cylinder : public Primitive {
public:
  Cylinder();
  ~Cylinder();
  Intersect intersect(Ray ray);
};
