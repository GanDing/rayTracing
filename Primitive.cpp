// Fall 2018
#include <algorithm>
#include <iostream>
#include <glm/gtx/io.hpp>
#include <glm/gtc/constants.hpp>
#include "Primitive.hpp"
#include "polyroots.hpp"
using namespace std;
using namespace glm;

Primitive::~Primitive()
{
}

Intersect Primitive::intersect(Ray ray) {
	return Intersect();
}

bool Primitive::ray_intersect_triangle(Ray ray, vec3 v0, vec3 v1, vec3 v2, float &t) {
	vec3 edge1, edge2, rayDir, normal, rayV0;
	edge1 = v1 - v0;
	edge2 = v2 - v0;
	rayDir = -vec3(ray.vec);
	normal = cross(edge1, edge2);
	if (dot(vec3(ray.vec), normal) > 0) {
		return false;
	}
	rayV0 = vec3(ray.origin) - v0;
	float beta = determinant(mat3({
		rayV0, edge2, rayDir
	})) / determinant(mat3({
		edge1, edge2, rayDir
	}));
	if (beta < 0) {
		return false;
	}
	float gamma = determinant(mat3({
		edge1, rayV0, rayDir
	})) / determinant(mat3({
		edge1, edge2, rayDir
	}));
	if (gamma < 0 || beta + gamma > 1) {
		return false;
	}
	t = determinant(mat3({
		edge1, edge2, rayV0
	})) / determinant(mat3({
		edge1, edge2, rayDir
	}));
	return true;
}

vec2 Primitive::texturePosition(vec4 point) {
	return vec2();
}

Sphere::Sphere()// : m_pos(vec4(0, 0, 0, 1)), m_radius(1)
{
	m_pos = vec4(0, 0, 0, 1);
	m_radius = 1;
}

Sphere::~Sphere()
{
}

// Sphere::Intersect(Ray ray) {
	
// }

Cube::Cube() : NonhierBox(vec3(0, 0, 0), 1.0) {
}

Cube::~Cube()
{
}

NonhierSphere::~NonhierSphere()
{
}

Intersect NonhierSphere::intersect(Ray ray) {
	Intersect newIntersect = Intersect();
	// cout << newIntersect.n << " " << newIntersect.t << endl;
	// cout << ray.origin << " " << ray.vec << " " << m_pos << endl;
	float a = dot(ray.vec, ray.vec);
	float b = dot(ray.vec, (ray.origin - m_pos)) * 2;
	float c = dot((ray.origin - m_pos), (ray.origin - m_pos)) - m_radius * m_radius;
	// cout << a << " " << b << " " << c << endl;
	float roots[2];
	size_t numRoot = quadraticRoots(a, b, c, roots);
	if (numRoot == 0) {
		// cout << "nima" << endl;
		return newIntersect;
	} else if (numRoot == 1) {
		cout << roots[0] << endl;
		newIntersect.t = roots[0];
	} else {
		// cout << roots[0] << " " << roots[1] << endl;
		newIntersect.t = std::min(roots[0], roots[1]);
	}
	vec4 intersectPoint = ray.origin + newIntersect.t * ray.vec;
	newIntersect.n = normalize(intersectPoint - m_pos);
	// cout << "premitive: " << newIntersect.n << " " << newIntersect.t << endl;
	return newIntersect;
}

vec2 NonhierSphere::texturePosition(vec4 point) {
  	vec3 normal = vec3(point - m_pos);
	normal = normalize(normal);
	float dx = -normal.x;
	float dy = normal.y;
	float dz = normal.z;
	vec2 result = vec2(0.5 + atan2(dz, dx) / (2 * pi<float>()), 0.5 - asin(dy) / pi<float>());
	result.x = std::min(std::max(result.x, 0.0f), 1.0f);
  	result.y = std::min(std::max(result.y, 0.0f), 1.0f);
	return result;
}

NonhierBox::NonhierBox(const glm::vec3& pos, float size) : m_pos(vec4(pos, 1)), m_size(size)
{
	vec3 newPoint = pos;
	initialTriangles(newPoint, newPoint + size);
}

NonhierBox::NonhierBox(const glm::vec3& minPos, const glm::vec3& maxPos) {
	// bounds[0] = vec3(minPos);
	// bounds[1] = vec3(maxPos);
	initialTriangles(minPos, maxPos);
}

void NonhierBox::initialTriangles(glm::vec3 minPos, glm::vec3 maxPos) {
	vec3 v1 = vec3(minPos.x, minPos.y, minPos.z);
	vec3 v2 = vec3(maxPos.x, minPos.y, minPos.z);
	vec3 v3 = vec3(minPos.x, maxPos.y, minPos.z);
	vec3 v4 = vec3(minPos.x, minPos.y, maxPos.z);
	vec3 v5 = vec3(maxPos.x, maxPos.y, minPos.z);
	vec3 v6 = vec3(maxPos.x, minPos.y, maxPos.z);
	vec3 v7 = vec3(minPos.x, maxPos.y, maxPos.z);
	vec3 v8 = vec3(maxPos.x, maxPos.y, maxPos.z);

	triangle[0][0] = v8;
	triangle[0][1] = v7;
	triangle[0][2] = v4;
	triangle[1][0] = v4;
	triangle[1][1] = v6;
	triangle[1][2] = v8;

	triangle[2][0] = v1;
	triangle[2][1] = v3;
	triangle[2][2] = v5;
	triangle[3][0] = v5;
	triangle[3][1] = v2;
	triangle[3][2] = v1;

	triangle[4][0] = v1;
	triangle[4][1] = v4;
	triangle[4][2] = v7;
	triangle[5][0] = v7;
	triangle[5][1] = v3;
	triangle[5][2] = v1;

	triangle[6][0] = v5;
	triangle[6][1] = v8;
	triangle[6][2] = v6;
	triangle[7][0] = v6;
	triangle[7][1] = v2;
	triangle[7][2] = v5;

	triangle[8][0] = v3;
	triangle[8][1] = v7;
	triangle[8][2] = v8;
	triangle[9][0] = v8;
	triangle[9][1] = v5;
	triangle[9][2] = v3;

	triangle[10][0] = v1;
	triangle[10][1] = v2;
	triangle[10][2] = v6;
	triangle[11][0] = v6;
	triangle[11][1] = v4;
	triangle[11][2] = v1;	
}

NonhierBox::~NonhierBox()
{
}

Intersect NonhierBox::intersect(Ray ray) {
	float t = numeric_limits<float>::infinity();
	Intersect newIntersect = Intersect();
	for (int i = 0; i < 12; ++i) {
		bool is_intersect = ray_intersect_triangle(ray, triangle[i][0], triangle[i][1], triangle[i][2], t);
		if (is_intersect) {
			if (t < newIntersect.t && t >= 0) {
				newIntersect.t = t;
				vec3 n = normalize(cross(triangle[i][1] - triangle[i][0], triangle[i][2] - triangle[i][0]));
				newIntersect.n = vec4(n, 0);
			}
		}
	}
	return newIntersect;
}

vec2 NonhierBox::texturePosition(glm::vec4 point) {
	vec4 curPos = m_pos;
  	vec3 d = vec3(point - m_pos);
  	float epsilon = 0.01;
  	vec2 result = vec2();
  	if (abs(d.x) < epsilon) {
  		result = vec2(d.z / m_size, (m_size-d.y) / m_size);
  	} else if (abs(d.x - m_size) < epsilon) {
  		result = vec2((m_size - d.z)  / m_size, (m_size - d.y) / m_size);
  	} else if (abs(d.y) < epsilon) {
  		result = vec2((m_size - d.x) / m_size, (m_size - d.z) / m_size);
  	} else if (abs(d.y - m_size) < epsilon) {
  		result = vec2(d.x / m_size, (m_size - d.z) / m_size);
  	} else if (abs(d.z) < epsilon) {
  		result = vec2((m_size - d.x) / m_size, (m_size - d.y) / m_size);
  	} else if (abs(d.z - m_size) < epsilon) {
  		result = vec2(d.x / m_size, (m_size - d.y) / m_size);
  	}
  	result.x = std::min(std::max(result.x, 0.0f), 1.0f);
  	result.y = std::min(std::max(result.y, 0.0f), 1.0f);
	return result;
}

Cylinder::Cylinder() {
}

Cylinder::~Cylinder() 
{
}

Intersect Cylinder::intersect(Ray ray) {
	float a = ray.vec.x * ray.vec.x + ray.vec.z * ray.vec.z;
	float b = 2 * ray.origin.x * ray.vec.x + 2 * ray.origin.z * ray.vec.z;
	float c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - 1;

	float roots[2];
	size_t numRoot = quadraticRoots(a, b, c, roots);

	Intersect newIntersect = Intersect();
	if (numRoot == 0) {
		// cout << 0 << endl;
		return newIntersect;
	} else if (numRoot == 1) {
		// cout << 1 << endl;
		return newIntersect;
	} else {
		// cout << 3 << endl;
		float t0 = std::min(roots[0], roots[1]);
		float t1 = std::max(roots[0], roots[1]);
		float y0 = ray.origin.y + ray.vec.y * t0;
		float y1 = ray.origin.y + ray.vec.y * t1;
		// cout << "t0 " << t0 << " t1 " << t1 << endl;
		// cout << "y0 " << y0 << " y1 " << y1 << endl;
		if (y0 < -1) {
			if (y1 < -1) {
				return newIntersect;
			} else {
				// hit the cap
				float th = t0 + (t1-t0) * (y0+1) / (y0-y1);
				if (th <= 0) {
					return newIntersect;
				}
				newIntersect.t = th;
				newIntersect.n = vec4(0, -1, 0, 0);
				return newIntersect;
			}
		} else if (y0>=-1 && y0<=1) {
			// hit the cylinder bit
			if (t0 <= 0) {
				return newIntersect;
			}
			
			newIntersect.t = t0;
			vec4 point = ray.origin + ray.vec * t0;
			vec4 n = vec4(point.x, 0, point.z, 0);
			newIntersect.n = normalize(n);
			return newIntersect;
		} else if (y0 > 1) {
			if (y1 > 1) {
				return newIntersect;
			} else {
				// hit the cap
				float th = t0 + (t1-t0) * (y0-1) / (y0-y1);
				if (th <= 0) {
					return newIntersect;
				}
				newIntersect.t = th;
				newIntersect.n = vec4(0, 1, 0, 0);
				return newIntersect;
			}
		}
		return newIntersect;
	}
}

Torus::Torus(float R, float r) : R(R), r(r) {}

Torus::~Torus() {}

Intersect Torus::intersect(Ray ray) {
	Intersect newIntersect = Intersect();
	vec4 m_pos = vec4(0, 0, 0, 0);
	// cout << newIntersect.n << " " << newIntersect.t << endl;
	// cout << ray.origin << " " << ray.vec << " " << m_pos << endl;
	vec3 o = vec3(ray.origin);
	vec3 d = vec3(ray.vec);
	double c4 = pow(pow(d.x, 2) + pow(d.y, 2) + pow(d.z, 2), 2);
	double c3 = 4.0f * (pow(d.x, 2) + pow(d.y, 2) + pow(d.z, 2)) * (o.x * d.x + o.y * d.y + o.z * d.z);
	double c2 = 2.0f * (pow(d.x, 2) + pow(d.y, 2) + pow(d.z, 2)) * (pow(o.x, 2) + pow(o.y, 2) + pow(o.z, 2) - (r * r + R * R)) + 4 * pow((o.x * d.x + o.y * d.y + o.z * d.z), 2) + 4 * R * R * pow(d.y, 2);
	double c1 = 4 * (pow(o.x, 2) + pow(o.y, 2) + pow(o.z, 2) - (r * r + R * R)) * (o.x * d.x + o.y * d.y + o.z * d.z) + 8 * R * R * o.y * d.y;
	double c0 = pow(pow(o.x, 2) + pow(o.y, 2) + pow(o.z, 2) - (r * r + R * R), 2) - 4 * R * R * (r * r - pow(o.y, 2));
	c3 /= c4;
	c2 /= c4;
	c1 /= c4;
	c0 /= c4;
	// cout << a << " " << b << " " << c << endl;
	float roots[4];
	size_t numRoot = quarticRoots(c3, c2, c1, c0, roots);
	if (numRoot == 0) {
		// cout << "nima" << endl;
		return newIntersect;
	}
	newIntersect.t = roots[0];
	for (int i = 1; i < 4; i++) {
		if (numRoot > i && roots[i] > 0.0f) {
			newIntersect.t = std::min(newIntersect.t, roots[i]);
		}
	}
	vec4 intersectPoint = ray.origin + newIntersect.t * ray.vec;
	// newIntersect.n = normalize(intersectPoint - m_pos + vec4(0, r));
	float paramSquared = R * R + r * r;
	float sumSquared = pow(intersectPoint.x, 2) + pow(intersectPoint.y, 2) + pow(intersectPoint.z, 2);
	vec4 normal = vec4(4 * intersectPoint.x * (sumSquared - paramSquared),  4.0 * intersectPoint.y * (sumSquared - paramSquared + 2.0 * R * R), 4.0 * intersectPoint.z * (sumSquared - paramSquared), 0);
	newIntersect.n = normalize(normal);
	// cout << "premitive: " << newIntersect.n << " " << newIntersect.t << endl;
	return newIntersect;


}