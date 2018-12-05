
#include <lodepng/lodepng.h>
#include <iostream>
#include "BumpMaterial.hpp"

using namespace glm;
using namespace std;

BumpMaterial::BumpMaterial(std::string imageName) {
	// if (lodepng::decode(image, w, h, imageName, LCT_GREY_ALPHA, 8)) {
	// 	cerr << "load image " << imageName << " fail!";
	// 	exit(1);
	// }
	lodepng::decode(image, w, h, imageName);
}

BumpMaterial::~BumpMaterial() {}

vec4 BumpMaterial::get_bumpNormal(vec2 uv, vec4 normal) {
	float dw = 1 / (float)w;
	float dh = 1 / (float)h;
	float bu = (sum_color(uv.x + dw, uv.y) - sum_color(uv.x - dw, uv.y)) / (2 * dw);
	float bv = (sum_color(uv.x, uv.y + dh) - sum_color(uv.x, uv.y - dh)) / (2 * dh);
	return normalize(normal + vec4(bu * cross(vec3(normal), vec3(0.0f, 1.0f, 0.0f)) - bv * cross(vec3(normal), vec3(1.0f, 0.0f, 0.0f)), 0));
}

float BumpMaterial::get_texture(uint x, uint y) {
	if (x >= w) {
		x = w - 1;
	}
	if (y >= h) {
		y = h - 1;
	}
	uint index = (y * w + x) * 4;
	// return image[index] / 255.0f;
	return (image[index] / 255.0f + image[index + 1] / 255.0f + image[index + 2] / 255.0f) / 3.0f;
}

float BumpMaterial::sum_color(float u, float v){
  int iu = w * u;
  float du = w * u - iu;
  int iv = h * v;
  float dv = h * v - iv;
  float f00 = get_texture(iu ,iv);
  float f10 = get_texture(iu + 1,iv);
  float f01 = get_texture(iu,iv + 1);
  float f11 = get_texture(iu + 1,iv + 1);
  float fu0 = f00 + du * (f10 - f00);
  float fu1 = f01 + du * (f11 - f01);
  float fval = fu0 + dv * (fu1 - fu0);
  return fval;
}
