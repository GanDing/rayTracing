// Fall 2018

#include <iostream>
#include <limits>
#include <glm/gtx/io.hpp>
#include "GeometryNode.hpp"
using namespace glm;
using namespace std;

//---------------------------------------------------------------------------------------
GeometryNode::GeometryNode(
	const std::string & name, Primitive *prim, Material *mat )
	: SceneNode( name )
	, m_material( mat )
	, m_primitive( prim )
{
	m_nodeType = NodeType::GeometryNode;
}

void GeometryNode::setMaterial( Material *mat )
{
	// Obviously, there's a potential memory leak here.  A good solution
	// would be to use some kind of reference counting, as in the 
	// C++ shared_ptr.  But I'm going to punt on that problem here.
	// Why?  Two reasons:
	// (a) In practice we expect the scene to be constructed exactly
	//     once.  There's no reason to believe that materials will be
	//     repeatedly overwritten in a GeometryNode.
	// (b) A ray tracer is a program in which you compute once, and 
	//     throw away all your data.  A memory leak won't build up and
	//     crash the program.

	m_material = mat;
}

Intersect GeometryNode::intersect(Ray ray) {
	vec4 newOrigin = invtrans * ray.origin;
	vec4 newVector = invtrans * ray.vec;

	Ray newRay = Ray(newOrigin, newVector);
	Intersect newIntersect = m_primitive->intersect(newRay);
	newIntersect.m_material = m_material;
	if (newIntersect.t < numeric_limits<float>::infinity() && newIntersect.t >= 0) {
		newIntersect.m_kd = m_material->get_kd(m_primitive->texturePosition(newRay.origin + newIntersect.t * newRay.vec));
		newIntersect.n = m_material->get_bumpNormal(m_primitive->texturePosition(newRay.origin + newIntersect.t * newRay.vec), newIntersect.n);
	}

	for (SceneNode *node : children) {
		Intersect childIntersect = node->intersect(newRay);
		if (childIntersect.t < newIntersect.t && childIntersect.t >= 0) {
			newIntersect = childIntersect;
		}
	}
	// newIntersect.n = invtrans * newIntersect.n;
	newIntersect.n = vec4(normalize(vec3(newIntersect.n) * mat3(
		invtrans[0][0], invtrans[0][1], invtrans[0][2],
		invtrans[1][0], invtrans[1][1], invtrans[1][2],
		invtrans[2][0], invtrans[2][1], invtrans[2][2])), 0);
	// cout << "node " << newIntersect.n << endl;
	return newIntersect;
}
