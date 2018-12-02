// Fall 2018

#include "PhongMaterial.hpp"
using namespace glm;

PhongMaterial::PhongMaterial(
	const glm::vec3& kd, const glm::vec3& ks, float shininess, float trans )
	: m_kd(kd)
	, m_ks(ks)
	, m_shininess(shininess)
	, m_trans(trans)
{}

PhongMaterial::~PhongMaterial()
{}

vec3 PhongMaterial::get_kd() {
	return m_kd;
}

vec3 PhongMaterial::get_kd(float u, float v) {
	return m_kd;
}

vec3 PhongMaterial::get_ks() {
	return m_ks;
}

float PhongMaterial::get_shininess() {
	return m_shininess;
}

float PhongMaterial::get_trans() {
	return m_trans;
}
