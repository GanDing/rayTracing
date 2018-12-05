// Fall 2018

#include <glm/ext.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <limits>
#include <ctime>
#include <thread>
#include <numeric>

#include "A4.hpp"
#include "Ray.hpp"
#include "Intersect.hpp"
#include "Material.hpp"
using namespace glm;
using namespace std;

#ifdef ENABLE_MUTITHREAD
mutex m_lock;
uint lx = 0;
uint ly = 0;
uint count = 1;
#endif
vector<vector<vec3>> colorImage;

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

	const float distance = 10;

	uint h = image.height();
	uint w = image.width();
	float s = 2 * distance * tan(radians(fovy / 2));

	mat4 screenTrans = translate(mat4(), vec3(-(float)w/2, -(float)h/2, distance));
	mat4 screenScale = scale(mat4(), vec3(s / (float)w, -s / (float)h, 1));
	// mat4 screenScale = scale(mat4(), vec3(-s / (float)w, s / (float)h, 1));
	vec3 viewN = normalize(view);
	vec3 upN = normalize(up);
	vec3 viewUpNormal = normalize(cross(viewN, upN));
	mat4 screenRotate = mat4(
		vec4(viewUpNormal, 0),
		vec4(upN, 0),
		vec4(viewN, 0),
		vec4(0, 0, 0, 1));
	mat4 eyeTrans = translate(mat4(), vec3(eye));
	mat4 worldTranform = eyeTrans * screenRotate * screenScale * screenTrans;

	// cout << screenTrans << endl;
	// cout << screenScale << endl;
	// cout << cross(view, up) << endl;
	// cout << cross(cross(view, up), view) << endl;
	// cout << screenRotate << endl;
	// cout << eyeTrans << endl;
	// cout << worldTranform << endl;
	// cout << worldTranform * vec4(0,0,0,1) << endl;
	// cout << worldTranform * vec4(255,255,0,1) << endl;
	// cout << R3(up, view) << endl;

	for (uint y = 0; y < h; ++y) {
		for (uint x = 0; x < w; ++x) {
			// Red: increasing from Top to Bottom  
			image(x, y, 0) = (float)y / h;
			// Green: increasing from Left to Right  
			image(x, y, 1) = (float)x / w;
			// Blue: in Lower-Left and Upper-Right corners  
			image(x, y, 2) = ((y < h/2 && x < w/2)
						  || (y >= h/2 && x >= w/2)) ? 1.0 : 0.0;
		}
	}

	srand(time(0));
	// cout <<  numeric_limits<float>::infinity() << endl;
	// Ray ray = Ray(vec4(eye, 1), worldTranform * vec4(127, 127, 0, 1) - vec4(eye, 1));
	// Intersect intersect = root->intersect(ray);
	// cout << intersect.n << " " << intersect.t << endl;
	// vec3 pixelColour = lightShading(intersect, ray, lights, ambient, root);
	// cout << pixelColour << endl;

	// for (uint x = 251; x < w; x++) {
	// 		Ray ray = Ray(vec4(eye, 1), normalize(worldTranform * vec4(x, 253, 0, 1) - vec4(eye, 1)));
	// 		// cout << ray.origin << " " << ray.vec << endl;
	// 		// cout << x << " " << y << endl;
	// 		Intersect intersect = root->intersect(ray);
	// 		// cout << x << " " <<  intersect.t << endl;
	// 		// cout << x << " " <<  intersect.t << "   " << intersect.n << " " << pixelColour << endl;
	// 		if (intersect.t < numeric_limits<float>::infinity()) {
	// 			vec3 pixelColour = lightShading(intersect, ray, lights, ambient, root);
	// 			image(x, 140, 0) = pixelColour.x;
	// 			image(x, 140, 1) = pixelColour.y;
	// 			image(x, 140, 2) = pixelColour.z;
	// 			cout << x << " " <<  intersect.t << "   " << intersect.n << " " << pixelColour << endl;
	// 		}
	// 	}
#ifdef ENABLE_MUTITHREAD
	cout << "Enable Multithreading" << endl;
	vector<thread> thread_list(NUM_THREAD);
	// vector<vector<vec3>> colorImage;
	for (uint i = 0; i < w; i++) {
		vector<vec3> col(h, vec3());
		colorImage.push_back(col);
	}
	
	// uint lx = 0;
	// uint ly = 0;
	// uint count = 1;
	for (int i = 0; i < NUM_THREAD; i++) {
		thread_list[i] = thread(multithread_render, w, h,
			worldTranform, eye, lights, ambient, root);
		// multithread_render(w, h,
		// 	worldTranform, eye, lights, ambient, root,
		// 	colorImage, lx, ly, count);
	}
	for (int i = 0; i < NUM_THREAD; i++) {
		thread_list[i].join();
	}
	// for (uint y = 0; y < h; y++) {
	// 	for (uint x = 0; x < w; x++) {
	// 		vec3 colour = colorImage[x][y];
	// 		image(x, y, 0) = colour.x;
	// 		image(x, y, 1) = colour.y;
	// 		image(x, y, 2) = colour.z;
	// 	}
	// }
#else
	int step = h / 20;
	int count = 1;
	// for (uint y = 0; y < h; y++) {
	// 	for (uint x = 0; x < w; x++) {
	// 		Ray ray = Ray(vec4(eye, 1), normalize(worldTranform * vec4(x, y, 0, 1) - vec4(eye, 1)));
	// 		Intersect intersect = root->intersect(ray);
	// 		// cout << intersect.t << endl;
	// 		// cout << x << " " << y << endl;
	// 		if (intersect.t < numeric_limits<float>::infinity()) {
	// 			vec3 pixelColour = lightShading(intersect, ray, lights, ambient, root);
	// 			image(x, y, 0) = pixelColour.x;
	// 			image(x, y, 1) = pixelColour.y;
	// 			image(x, y, 2) = pixelColour.z;
	// 			// cout << x << " " << y << endl;
	// 		} else {
	// 			image(x, y, 0) = 0.5 + (float)(h-y) / h * 0.5;
	// 			image(x, y, 1) = 0.2 + (float)(h-y) / h * 0.7;
	// 			image(x, y, 2) = (float)0.2;
	// 		}
	// 	}
	// 	if (y > step * count) {
	// 		cout << (float) y / h * 100 << "% complete" << endl;
	// 		count++;
	// 	}
	// }
	for (uint y = 0; y < h; y++) {
		for (uint x = 0; x < w; x++) {
			vec3 colour = renderPixel(x, y, h, worldTranform, eye, lights, ambient, root);
			// image(x, y, 0) = colour.x;
			// image(x, y, 1) = colour.y;
			// image(x, y, 2) = colour.z;
			colorImage[x][y] = colour;
		}
		if (y > step * count) {
			cout << (float) y / h * 100 << "% complete" << endl;
			count++;
		}
	}
#endif

#ifdef ENABLE_ANTIALIASING
	for (uint y = 0; y < h - 1; y++) {
		for (uint x = 0; x < w - 1; x++) {
			vec3 color = colorImage[x][y] + colorImage[x+1][y] + colorImage[x][y+1] + colorImage[x+1][y+1];
			color /= 4.0f;
			image(x, y, 0) = color.x;
			image(x, y, 1) = color.y;
			image(x, y, 2) = color.z;
		}
	}
#else
	for (uint y = 0; y < h; y++) {
		for (uint x = 0; x < w; x++) {
			vec3 color = colorImage[x][y];
			image(x, y, 0) = color.x;
			image(x, y, 1) = color.y;
			image(x, y, 2) = color.z;
		}
	}
#endif
}


vec3 renderPixel(uint x, uint y, uint h, 
	mat4 worldTranform, vec3 eye, 
	const list<Light *> & lights, const vec3 & ambient, SceneNode * root) {
#ifndef ENABLE_DOF
	Ray pRay = Ray(vec4(eye, 1), normalize(worldTranform * vec4(x, y, 0, 1) - vec4(eye, 1)));
	return colorShading(pRay, 0, x, y, h, lights, ambient, root);
#else
	vec4 rayOri = vec4(eye, 1);
	vec4 rayDir = normalize(worldTranform * vec4(x, y, 0, 1) - rayOri);
	vec4 pointAimed = rayOri + rayDir * DOF_FOCAL;
	vec3 disperse_color = vec3();
	vector<float> r, s;
	jitterArray(DOF_SAMPLE, r, s);
	for (int i = 0; i < DOF_SAMPLE * DOF_SAMPLE; i++) {
		vec4 lens = vec4(eye, 1);
		// Ray pRay = Ray(lens, normalize(worldTranform * vec4(x, y, 0, 1) - lens));
		lens.x = lens.x + r[i] / (float)DOF_SAMPLE * DOF_FACTOR;
		lens.y = lens.y + fmod(r[i], (float)DOF_SAMPLE) * DOF_FACTOR;
		vec4 world = worldTranform * vec4(x, y, 0, 1);
		// world.x = world.x + s[i] / (float)DOF_SAMPLE * DOF_FACTOR * 0.2;
		// world.y = world.y + fmod(s[i], (float)DOF_SAMPLE) * DOF_FACTOR * 0.2;
		Ray pRay = Ray(lens, normalize(pointAimed - lens));
		disperse_color += colorShading(pRay, 0, x, y, h, lights, ambient, root);
	}
	return disperse_color /(float)(DOF_SAMPLE * DOF_SAMPLE);
#endif
}

vec3 colorShading(Ray ray, int depth,
	uint x, uint y, uint h, 
	const list<Light *> & lights, const vec3 & ambient, SceneNode * root) {
	Intersect intersect = root->intersect(ray);
	vec4 point = ray.origin + intersect.t * ray.vec;

	vec3 result = vec3();
	if (intersect.t < numeric_limits<float>::infinity()) {
		result = lightShading(intersect, ray, lights, ambient, root);
		vec3 reflectColor = vec3();
		vec3 refractColor = vec3();
		float transparency = intersect.m_material->get_trans();
		// result = (1 - transparency) * result;
#ifdef ENABLE_REFLACTION
		if (depth < RECURSION_DEPTH) {
			vec4 normal = intersect.n;
			if (dot(ray.vec, normal) < 0) {
				normal = -normal;
			}
			vec4 reflectDir = normalize(reflect(ray.vec, normal));
			Ray reflactRay = Ray(point + 0.001 * reflectDir, reflectDir);
			reflectColor = colorShading(reflactRay, depth + 1, x, y, h, lights, ambient, root);
			reflectColor = 0.5 * intersect.m_material->get_ks() * reflectColor;
		}
#endif
		float kr = 1;
		float cosi = glm::clamp(dot(ray.vec, intersect.n), -1.0f, 1.0f); 
	    float etai = 1, etat = 1.55; 
	    if (cosi > 0) { std::swap(etai, etat); } 
	    float sint = etai / etat * sqrtf(std::max(0.0f, 1 - cosi * cosi)); 
	    if (sint >= 1) { 
	        kr = 1; 
	    } 
	    else { 
	        float cost = sqrtf(std::max(0.f, 1 - sint * sint)); 
	        cosi = fabsf(cosi); 
	        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost)); 
	        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost)); 
	        kr = (Rs * Rs + Rp * Rp) / 2; 
	    }
#ifdef ENABLE_REFRACTION
		if (depth < RECURSION_DEPTH && kr < 1) {
			// transparency
			// float transparency = intersect.m_material->get_trans();
			// result = 0.2 * result;
			if (transparency > 0.0f) {
				float cos = dot(ray.vec, intersect.n);
				float startIndex = 1;
				float objectIndex = 1;
				vec4 normal = intersect.n;
				if (cos < 0.0f) {
					startIndex = 1;
					objectIndex = 1.55;
				} else {
					startIndex = 1.55;
					objectIndex = 1;
					normal = -1 * normal;
					// cos = -cos;
					// cos = dot(ray.vec, intersect.n);
				}
				float refractRatio = startIndex / objectIndex;
				if (1 - pow(refractRatio, 2) * (1 - pow(cos, 2)) >= 0) {
					vec4 refractDir = refractRatio * (ray.vec - normal * cos) - normal * sqrtf(1 - pow(refractRatio, 2) * (1 - pow(cos, 2)));
					// float cosineSquare = 1 - pow(startIndex / objectIndex, 2) * (1 - pow(dot(ray.vec, intersect.n), 2));
					// vec4 refractDir = (-startIndex / objectIndex * dot(ray.vec, intersect.n) - sqrtf(cosineSquare)) * intersect.n + startIndex / objectIndex * ray.vec;
					refractDir = normalize(refractDir);
					Ray refractRay = Ray(point + 0.001 * refractDir, refractDir);
					refractColor = colorShading(refractRay, depth + 1, x, y, h, lights, ambient, root);
					refractColor = transparency * refractColor;
				}

				// float cosi = glm::clamp(dot(ray.vec, intersect.n), -1.0f, 1.0f); 
			 //    float etai = 1, etat = 1.55; 
			 //    vec4 n = intersect.n; 
			 //    if (cosi < 0) { cosi = -cosi; } else { std::swap(etai, etat); n= -n; } 
			 //    float eta = etai / etat; 
			 //    float k = 1 - eta * eta * (1 - cosi * cosi); 
			 //    if (k >= 0.0f) {
				//     vec4 refractDir = normalize(eta * ray.vec + (eta * cosi - sqrtf(k)) * n);
				//     Ray refractRay = Ray(point + 0.001 * refractDir, refractDir);
				// 	vec3 refractColor = colorShading(refractRay, depth + 1, x, y, h, lights, ambient, root);
				// 	result += transparency * refractColor;
				// }
			}
		}
#endif
		
	    // result += reflectColor + refractColor;
	    if (transparency > 0.0f) {
			result += kr * reflectColor + (1.0f - kr) * refractColor;
		} else {
			result += reflectColor;
		}
	} else {
		// result.x = 0.5 + (float)(h-y) / h * 0.5;
		// result.y = 0.2 + (float)(h-y) / h * 0.7;
		// result.z = (float)0.2;
		result.x = 0;
		result.y = 0;
		result.z = 0;
	}
	return result;
}

vec3 lightShading(Intersect eyeIntersect, Ray ray, const list<Light *> & lights, const vec3 & ambient, SceneNode * root) {
	Material *material = eyeIntersect.m_material;
	vec3 kd = eyeIntersect.m_kd;
	vec3 ks = material->get_ks();
	float shininess = material->get_shininess();
	vec3 colour = kd * ambient;
	vec4 point = ray.origin + eyeIntersect.t * ray.vec;
	// cout << ray.origin << " " << ray.vec << endl;
	// cout << point << endl;
	for (Light * lightSource : lights) {
#ifndef ENABLE_SOFTSHADOW
		// cout << 1 << endl;
		vec4 lightPoint = vec4(lightSource->position, 1);
		// cout << lightPoint << endl;
		Ray lightRay = Ray(point + 0.0001 * normalize(lightPoint - point), normalize(lightPoint - point));
		// Ray lightRay = Ray(lightPoint, normalize(point - lightPoint));
		// change later
		float distance = length(point - lightPoint);
		Intersect lightIntersect = root->intersect(lightRay);
		// cout << "lightS 1 " <<  lightIntersect.t << endl;
		if (lightIntersect.t < distance) {
			continue;
		}
		// cout << 2 << endl;
		// cout <<lightIntersect.n << endl;
		// cout << lightRay.vec << endl;
		vec3 diffue = kd * glm::max(dot(lightRay.vec, eyeIntersect.n), 0.0f) * lightSource->colour;
		// cout << 2.1 << endl;
		float d = dot(lightRay.vec, eyeIntersect.n);
		d = std::max(d, 0.0f);
		vec4 r = -lightRay.vec + 2 * d * eyeIntersect.n;
		// cout << 2.2 << endl;
		vec3 specular = ks * pow(glm::max(dot(r, -ray.vec), 0.0f), shininess) * lightSource->colour;
		colour += diffue + specular;
		// cout << 3 << endl;
#else
		vec3 disperse_color = vec3();
		vector<float> r, s;
		jitterArray(LIGHT_RAY, r, s);
		for (int i = 0; i < LIGHT_RAY * LIGHT_RAY; i++) {
			vec4 lightPoint = vec4(lightSource->position, 1);
			// lightPoint.x = lightPoint.x - (float)LIGHT_RANGE * 0.5f + rand() % 100 * 0.01f * (float)LIGHT_RANGE;
			// lightPoint.z = lightPoint.z - (float)LIGHT_RANGE * 0.5f + rand() % 100 * 0.01f * (float)LIGHT_RANGE;
			lightPoint.x = lightPoint.x + s[i] / (float)LIGHT_RAY * LIGHT_RAY_FACTOR;
			lightPoint.z = lightPoint.z + fmod(s[i], (float)LIGHT_RAY) * LIGHT_RAY_FACTOR;
			vec4 sourePoint = vec4(point);
			sourePoint.x = sourePoint.x + r[i] / (float)LIGHT_RAY * LIGHT_RAY_FACTOR;
			sourePoint.z = sourePoint.z + fmod(r[i], (float)LIGHT_RAY) * LIGHT_RAY_FACTOR;
			// Ray lightRay = Ray(point + 0.001 * normalize(lightPoint - point), normalize(lightPoint - point));
			Ray lightRay = Ray(sourePoint + 0.001 * normalize(lightPoint - sourePoint), normalize(lightPoint - sourePoint));
			// Ray lightRay = Ray(lightPoint, normalize(point - lightPoint));
			// change later
			float distance = length(point - lightPoint);
			Intersect lightIntersect = root->intersect(lightRay);
			// cout << "lightS 1 " <<  lightIntersect.t << endl;
			if (lightIntersect.t < distance) {
				continue;
			}
			// cout << 2 << endl;
			// cout <<lightIntersect.n << endl;
			// cout << lightRay.vec << endl;
			vec3 diffue = kd * glm::max(dot(lightRay.vec, eyeIntersect.n), 0.0f) * lightSource->colour;
			// cout << 2.1 << endl;
			float d = dot(lightRay.vec, eyeIntersect.n);
			d = std::max(d, 0.0f);
			vec4 r = -lightRay.vec + 2 * d * eyeIntersect.n;
			// cout << 2.2 << endl;
			vec3 specular =ks * pow(glm::max(dot(r, -ray.vec), 0.0f), shininess) * lightSource->colour;
			disperse_color += diffue + specular;
		}
		colour += disperse_color / (float)(LIGHT_RAY * LIGHT_RAY);
#endif
	}
	return colour;
}

void jitterArray(int length, vector<float> &r, vector<float> &s) {
	vector<float> res(length * length);
	r = res;
	iota(std::begin(r), std::end(r), length * length * -0.5f);
	s = r;
	for (int i = length * length; i > 0; i--) {
		int j = rand() % (i + 1);
		swap(s[i], s[j]);
	}
}

#ifdef ENABLE_MUTITHREAD
void multithread_render(uint w, uint h,
	mat4 worldTranform, vec3 eye, 
	const list<Light *> lights, const vec3 ambient, SceneNode * root) {
	while (true) {
		uint x, y;
		{
			lock_guard<mutex> guard(m_lock);
			if (ly >= h) {
				return;
			}
			x = lx++;
			y = ly;
			if (lx >= w) {
				lx = 0;
				ly++;
			}
			if (y > h / 20 * count) {
				cout << (float) y / h * 100 << "% complete" << endl;
				count++;
			}
		}
		vec3 color = renderPixel(x, y, h, worldTranform, eye, lights, ambient, root);
		colorImage[x][y] = color;
	}
}
#endif
