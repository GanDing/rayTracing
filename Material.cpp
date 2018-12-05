// Fall 2018

#include "Material.hpp"
using namespace glm;

Material::Material()
{}

Material::~Material()
{}

vec3 Material::get_kd() {}

vec3 Material::get_kd(vec2 uv) {}

vec3 Material::get_ks() {}

float Material::get_shininess() {}

float Material::get_trans() {}

void Material::set_bumpMaterial(BumpMaterial *bumpMaterial) {
	this->bumpMaterial = bumpMaterial;
}

vec4 Material::get_bumpNormal(vec2 uv, vec4 normal) {
	if (bumpMaterial == 0) {
		return normal;
	}
	return bumpMaterial->get_bumpNormal(uv, normal);
}
