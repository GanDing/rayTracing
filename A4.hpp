// Fall 2018

#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <mutex>

#include "SceneNode.hpp"
#include "Light.hpp"
#include "Image.hpp"
#include "Intersect.hpp"
#include "Ray.hpp"

// #define SHOW_BOUNDING_VOLUMN
#define ENABLE_MUTITHREAD 
#define NUM_THREAD 8
// #define ENABLE_REFLACTION
// #define ENABLE_REFRACTION
// #define RECURSION_DEPTH 6
// #define ENABLE_SOFTSHADOW
#define LIGHT_RAY_FACTOR 1.0f
#define LIGHT_RAY 3
#define ENABLE_ANTIALIASING
// #define ENABLE_DOF
#define DOF_FACTOR 0.2f
#define DOF_SAMPLE 3
#define DOF_FOCAL 75.0f

void A4_Render(
		// What to render
		SceneNode * root,

		// Image to write to, set to a given width and height
		Image & image,

		// Viewing parameters
		const glm::vec3 & eye,
		const glm::vec3 & view,
		const glm::vec3 & up,
		float fovy,

		// Lighting parameters
		const glm::vec3 & ambient,
		const std::list<Light *> & lights
);

glm::vec3 renderPixel(uint x, uint y, uint h, glm::mat4 worldTranform, glm::vec3 eye, const std::list<Light *> & lights, const glm::vec3 & ambient, SceneNode * root);

glm::vec3 colorShading(Ray ray, int depth, uint x, uint y, uint h, const std::list<Light *> & lights, const glm::vec3 & ambient, SceneNode * root);

glm::vec3 lightShading(Intersect eyeIntersect, Ray ray, const std::list<Light *> & lights, const glm::vec3 & ambient, SceneNode * root);

void jitterArray(int length, std::vector<float> &r, std::vector<float> &s);

#ifdef ENABLE_MUTITHREAD
void multithread_render(uint w, uint h, glm::mat4 worldTranform, glm::vec3 eye, 
	const std::list<Light *> lights, const glm::vec3 ambient, SceneNode * root);
#endif
