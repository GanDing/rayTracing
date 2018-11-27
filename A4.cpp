// Fall 2018

#include <glm/ext.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <limits>

#include "A4.hpp"
#include "Ray.hpp"
#include "Intersect.hpp"
using namespace glm;
using namespace std;

void A4_Render(
		// What to render  
		SceneNode * root,

		// Image to write to, set to a given width and height  
		Image & image,

		// Viewing parameters  
		const glm::vec3 & eye,
		const glm::vec3 & view,
		const glm::vec3 & up,
		double fovy,

		// Lighting parameters  
		const glm::vec3 & ambient,
		const std::list<Light *> & lights
) {

  // Fill in raytracing code here...  

  std::cout << "Calling A4_Render(\n" <<
		  "\t" << *root <<
          "\t" << "Image(width:" << image.width() << ", height:" << image.height() << ")\n"
          "\t" << "eye:  " << glm::to_string(eye) << std::endl <<
		  "\t" << "view: " << glm::to_string(view) << std::endl <<
		  "\t" << "up:   " << glm::to_string(up) << std::endl <<
		  "\t" << "fovy: " << fovy << std::endl <<
          "\t" << "ambient: " << glm::to_string(ambient) << std::endl <<
		  "\t" << "lights{" << std::endl;

	for(const Light * light : lights) {
		std::cout << "\t\t" <<  *light << std::endl;
	}
	std::cout << "\t}" << std::endl;
	std:: cout <<")" << std::endl;

	const double distance = 10;

	uint h = image.height();
	uint w = image.width();
	double s = 2 * distance * tan(radians(fovy / 2));

	dmat4 screenTrans = translate(dmat4(), dvec3(-(double)w/2, -(double)h/2, distance));
	dmat4 screenScale = scale(dmat4(), dvec3(s / (double)w, -s / (double)h, 1));
	// dmat4 screenScale = scale(dmat4(), dvec3(-s / (double)w, s / (double)h, 1));
	dvec3 viewN = normalize(view);
	dvec3 upN = normalize(up);
	dvec3 viewUpNormal = normalize(cross(viewN, upN));
	dmat4 screenRotate = dmat4(
		dvec4(viewUpNormal, 0),
		dvec4(upN, 0),
		dvec4(viewN, 0),
		dvec4(0, 0, 0, 1));
	dmat4 eyeTrans = translate(dmat4(), dvec3(eye));
	dmat4 worldTranform = eyeTrans * screenRotate * screenScale * screenTrans;

	// cout << screenTrans << endl;
	// cout << screenScale << endl;
	// cout << cross(view, up) << endl;
	// cout << cross(cross(view, up), view) << endl;
	// cout << screenRotate << endl;
	// cout << eyeTrans << endl;
	// cout << worldTranform << endl;
	// cout << worldTranform * dvec4(0,0,0,1) << endl;
	// cout << worldTranform * dvec4(255,255,0,1) << endl;
	// cout << R3(up, view) << endl;

	for (uint y = 0; y < h; ++y) {
		for (uint x = 0; x < w; ++x) {
			// Red: increasing from Top to Bottom  
			image(x, y, 0) = (double)y / h;
			// Green: increasing from Left to Right  
			image(x, y, 1) = (double)x / w;
			// Blue: in Lower-Left and Upper-Right corners  
			image(x, y, 2) = ((y < h/2 && x < w/2)
						  || (y >= h/2 && x >= w/2)) ? 1.0 : 0.0;
		}
	}
	// cout <<  numeric_limits<double>::max() << endl;
	// Ray ray = Ray(dvec4(eye, 1), worldTranform * dvec4(127, 127, 0, 1) - dvec4(eye, 1));
	// Intersect intersect = root->intersect(ray);
	// cout << intersect.n << " " << intersect.t << endl;
	// dvec3 pixelColour = lightShading(intersect, ray, lights, ambient, root);
	// cout << pixelColour << endl;

	// for (uint x = 251; x < w; x++) {
	// 		Ray ray = Ray(dvec4(eye, 1), normalize(worldTranform * dvec4(x, 253, 0, 1) - dvec4(eye, 1)));
	// 		// cout << ray.origin << " " << ray.vec << endl;
	// 		// cout << x << " " << y << endl;
	// 		Intersect intersect = root->intersect(ray);
	// 		// cout << x << " " <<  intersect.t << endl;
	// 		// cout << x << " " <<  intersect.t << "   " << intersect.n << " " << pixelColour << endl;
	// 		if (intersect.t < numeric_limits<double>::max()) {
	// 			dvec3 pixelColour = lightShading(intersect, ray, lights, ambient, root);
	// 			image(x, 140, 0) = pixelColour.x;
	// 			image(x, 140, 1) = pixelColour.y;
	// 			image(x, 140, 2) = pixelColour.z;
	// 			cout << x << " " <<  intersect.t << "   " << intersect.n << " " << pixelColour << endl;
	// 		}
	// 	}
	int step = h / 20;
	int count = 1;
	for (uint y = 0; y < h; y++) {
		for (uint x = 0; x < w; x++) {
			Ray ray = Ray(dvec4(eye, 1), normalize(worldTranform * dvec4(x, y, 0, 1) - dvec4(eye, 1)));
			Intersect intersect = root->intersect(ray);
			// cout << intersect.t << endl;
			// cout << x << " " << y << endl;
			if (intersect.t < numeric_limits<double>::max()) {
				dvec3 pixelColour = lightShading(intersect, ray, lights, ambient, root);
				image(x, y, 0) = pixelColour.x;
				image(x, y, 1) = pixelColour.y;
				image(x, y, 2) = pixelColour.z;
				// cout << x << " " << y << endl;
			} else {
				image(x, y, 0) = 0.5 + (double)(h-y) / h * 0.5;
				image(x, y, 1) = 0.2 + (double)(h-y) / h * 0.7;
				image(x, y, 2) = (double)0.2;
			}
		}
		if (y > step * count) {
			cout << (float) y / h * 100 << "% complete" << endl;
			count++;
		}
	}
}

dvec3 lightShading(Intersect eyeIntersect, Ray ray, const list<Light *> & lights, const vec3 & ambient, SceneNode * root) {
	dvec3 colour = eyeIntersect.m_material->get_kd() * ambient;
	dvec4 point = ray.origin + eyeIntersect.t * ray.vec;
	// cout << ray.origin << " " << ray.vec << endl;
	// cout << point << endl;
	for (Light * lightSource : lights) {
		// cout << 1 << endl;
		dvec4 lightPoint = dvec4(lightSource->position, 1);
		// cout << lightPoint << endl;
		Ray lightRay = Ray(point + 0.0001 * normalize(lightPoint - point), normalize(lightPoint - point));
		// Ray lightRay = Ray(lightPoint, normalize(point - lightPoint));
		// change later
		double distance = length(point - lightPoint);
		Intersect lightIntersect = root->intersect(lightRay);
		// cout << "lightS 1 " <<  lightIntersect.t << endl;
		if (lightIntersect.t < distance) {
			continue;
		}
		// cout << 2 << endl;
		// cout <<lightIntersect.n << endl;
		// cout << lightRay.vec << endl;
		dvec3 diffue = eyeIntersect.m_material->get_kd() * glm::max(dot(lightRay.vec, eyeIntersect.n), 0.0) * lightSource->colour;
		// cout << 2.1 << endl;
		dvec4 r = -lightRay.vec + 2 * dot(lightRay.vec, eyeIntersect.n) * eyeIntersect.n;
		// cout << 2.2 << endl;
		dvec3 specular = eyeIntersect.m_material->get_ks() * pow(glm::max(dot(r, -ray.vec), 0.0), eyeIntersect.m_material->get_shininess()) * lightSource->colour;
		colour += diffue + specular;
		// cout << 3 << endl;
	}
	return colour;
}

