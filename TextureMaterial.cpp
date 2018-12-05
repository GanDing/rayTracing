#include <lodepng/lodepng.h>
#include <iostream>

#include "TextureMaterial.hpp"

using namespace glm;
using namespace std;

TextureMaterial::TextureMaterial(string imageName, const vec3& ks, float shininess, float trans) 
	: m_ks(ks)
	, m_shininess(shininess)
	, m_trans(trans) 
{
	if (lodepng::decode(image, w, h, imageName)) {
		cerr << "load image " << imageName << " fail!";
		exit(1);
	}
}

TextureMaterial::~TextureMaterial()
{}

vec3 TextureMaterial::get_kd() {
	return get_kd(vec2(0.5f, 0.5f));
}

vec3 TextureMaterial::get_texture(uint x, uint y) {
	if (x == w) {
		x--;
	}
	if (y == h) {
		y--;
	}
	uint index = (y * w + x) * 4;
	return vec3(image[index] / 255.0f, image[index + 1] / 255.0f, image[index + 2] / 255.0f);
}

vec3 TextureMaterial::get_kd(vec2 uv) {
	float x = (float)(w - 1) * uv.x;
	float y = (float)(h - 1) * uv.y;
	uint ix = floor(x);
	uint iy = floor(y);
	float rx = x - ix;
	float ry = y - iy;

  vec3 kd = (1.0f - rx) * (1.0f - ry) * get_texture(ix, iy) + rx * (1.0f - ry) * get_texture(ix + 1, iy) + 
  	(1.0f - rx) * ry * get_texture(ix, iy + 1) + rx * ry * get_texture(ix + 1, iy + 1);
  return kd;
}

vec3 TextureMaterial::get_ks() {
	return m_ks;
}

float TextureMaterial::get_shininess() {
	return m_shininess;
}

float TextureMaterial::get_trans() {
	return m_trans;
}
