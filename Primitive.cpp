// Fall 2018
#include <algorithm>
#include <iostream>
#include <glm/gtx/io.hpp>
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

bool Primitive::ray_intersect_triangle(Ray ray, dvec3 v0, dvec3 v1, dvec3 v2, double &t) {
	dvec3 u = v1 - v0;
	dvec3 v = v2 - v0;
	dvec3 dir = dvec3(ray.vec);
	dvec3 orig = dvec3(ray.origin);

	dvec3 N = cross(u, v);
	// dvec3 N = u * v;
	// cout << N << endl;
	double denom = dot(N, N);

	double epsilon = 0.0001;
	double nDotRayDir = dot(N, dir);
	if (fabs(nDotRayDir) < epsilon) {
		return false; // parallel
	}

	double d = dot(N, v0);
	t = -dot(N, orig - v0) / nDotRayDir;
	if (t < 0.0) {
		return false; // behind
	}

	dvec3 P = orig + t * dir;
	double uu, uv, vv , wu, wv, D;
	uu = dot(u, u);
	uv = dot(u, v);
	vv = dot(v, v);
	dvec3 w = P - v0;
	wu = dot(w, u);
	wv = dot(w, v);
	D = uv * uv - uu * vv;
	double s, r;
	s = (uv * wv - vv * wu) / D;
	if (s < 0.0 || s > 1.0) {
		return false;
	}
	r = (uv * wu - uu * wv) / D;
	if (r < 0.0 || (s + r) > 1.0) {
		return false;
	}
	return true;
}

Sphere::Sphere()// : m_pos(dvec4(0, 0, 0, 1)), m_radius(1)
{
	m_pos = dvec4(0, 0, 0, 1);
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
	double a = dot(ray.vec, ray.vec);
	double b = dot(ray.vec, (ray.origin - m_pos)) * 2;
	double c = dot((ray.origin - m_pos), (ray.origin - m_pos)) - m_radius * m_radius;
	// cout << a << " " << b << " " << c << endl;
	double roots[2];
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
	dvec4 intersectPoint = ray.origin + newIntersect.t * ray.vec;
	newIntersect.n = normalize(intersectPoint - m_pos);
	// cout << "premitive: " << newIntersect.n << " " << newIntersect.t << endl;
	return newIntersect;
}


NonhierBox::NonhierBox(const glm::vec3& pos, double size) : m_pos(dvec4(pos, 1))
{
	dvec3 newPoint = pos;
	initialTriangles(newPoint, newPoint + size);
}

NonhierBox::NonhierBox(const glm::vec3& minPos, const glm::vec3& maxPos) {
	// bounds[0] = dvec3(minPos);
	// bounds[1] = dvec3(maxPos);
	initialTriangles(minPos, maxPos);
}

void NonhierBox::initialTriangles(glm::vec3 minPos, glm::vec3 maxPos) {
	dvec3 v1 = dvec3(minPos.x, minPos.y, minPos.z);
	dvec3 v2 = dvec3(maxPos.x, minPos.y, minPos.z);
	dvec3 v3 = dvec3(minPos.x, maxPos.y, minPos.z);
	dvec3 v4 = dvec3(minPos.x, minPos.y, maxPos.z);
	dvec3 v5 = dvec3(maxPos.x, maxPos.y, minPos.z);
	dvec3 v6 = dvec3(maxPos.x, minPos.y, maxPos.z);
	dvec3 v7 = dvec3(minPos.x, maxPos.y, maxPos.z);
	dvec3 v8 = dvec3(maxPos.x, maxPos.y, maxPos.z);

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
	double t = numeric_limits<double>::max();
	Intersect newIntersect = Intersect();
	for (int i = 0; i < 12; ++i) {
		bool is_intersect = ray_intersect_triangle(ray, triangle[i][0], triangle[i][1], triangle[i][2], t);
		if (is_intersect) {
			if (t < newIntersect.t && t >= 0) {
				newIntersect.t = t;
				dvec3 n = normalize(cross(triangle[i][1] - triangle[i][0], triangle[i][2] - triangle[i][0]));
				newIntersect.n = dvec4(n, 0);
			}
		}
	}
	return newIntersect;
}

Cylinder::Cylinder() {
}

Cylinder::~Cylinder() 
{
}

Intersect Cylinder::intersect(Ray ray) {
	double a = ray.vec.x * ray.vec.x + ray.vec.z * ray.vec.z;
	double b = 2 * ray.origin.x * ray.vec.x + 2 * ray.origin.z * ray.vec.z;
	double c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - 1;

	double roots[2];
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
		double t0 = std::min(roots[0], roots[1]);
		double t1 = std::max(roots[0], roots[1]);
		double y0 = ray.origin.y + ray.vec.y * t0;
		double y1 = ray.origin.y + ray.vec.y * t1;
		// cout << "t0 " << t0 << " t1 " << t1 << endl;
		// cout << "y0 " << y0 << " y1 " << y1 << endl;
		if (y0 < -1) {
			if (y1 < -1) {
				return newIntersect;
			} else {
				// hit the cap
				double th = t0 + (t1-t0) * (y0+1) / (y0-y1);
				if (th <= 0) {
					return newIntersect;
				}
				newIntersect.t = th;
				newIntersect.n = dvec4(0, -1, 0, 0);
				return newIntersect;
			}
		} else if (y0>=-1 && y0<=1) {
			// hit the cylinder bit
			if (t0 <= 0) {
				return newIntersect;
			}
			
			newIntersect.t = t0;
			dvec4 point = ray.origin + ray.vec * t0;
			dvec4 n = dvec4(point.x, 0, point.z, 0);
			newIntersect.n = normalize(n);
			return newIntersect;
		} else if (y0 > 1) {
			if (y1 > 1) {
				return newIntersect;
			} else {
				// hit the cap
				double th = t0 + (t1-t0) * (y0-1) / (y0-y1);
				if (th <= 0) {
					return newIntersect;
				}
				newIntersect.t = th;
				newIntersect.n = dvec4(0, 1, 0, 0);
				return newIntersect;
			}
		}
		return newIntersect;
	}
}
