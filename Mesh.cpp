// Fall 2018

#include <iostream>
#include <fstream>
#include <glm/gtx/io.hpp>
#include <glm/ext.hpp>
#include <limits>

// #include "cs488-framework/ObjFileDecoder.hpp"
#include "Mesh.hpp"
using namespace std;
using namespace glm;

#define SHOW_BOUNDING_VOLUMN false

Mesh::Mesh( const std::string& fname )
	: m_vertices()
	, m_faces()
{
	std::string code;
	double vx, vy, vz;
	size_t s1, s2, s3;

	std::ifstream ifs( fname.c_str() );

	if (ifs.fail()) {
	    string file = "Assets/" + fname;
	    ifs = std::ifstream(file.c_str());
  	}
  	dvec3 minPoint = dvec3(numeric_limits<double>::max(), numeric_limits<double>::max(), numeric_limits<double>::max());
  	dvec3 maxPoint = dvec3(-numeric_limits<double>::max(), -numeric_limits<double>::max(), -numeric_limits<double>::max());
	while( ifs >> code ) {
		if( code == "v" ) {
			ifs >> vx >> vy >> vz;
			minPoint.x = std::min(vx, minPoint.x);
			minPoint.y = std::min(vy, minPoint.y);
			minPoint.z = std::min(vz, minPoint.z);
			maxPoint.x = std::max(vx, maxPoint.x);
			maxPoint.y = std::max(vy, maxPoint.y);
			maxPoint.z = std::max(vz, maxPoint.z);
			m_vertices.push_back( glm::vec3( vx, vy, vz ) );
			// cout << "v" << endl;
		} else if( code == "f" ) {
			ifs >> s1 >> s2 >> s3;
			m_faces.push_back( Triangle( s1 - 1, s2 - 1, s3 - 1 ) );
			// cout << "f" << endl;
		}
		// cout << "code: " << code << endl;
	}
	// minPoint -= 0.0001;
	// cout << "final min max " << minPoint << " " << maxPoint << endl;
	bounding = NonhierBox(minPoint, maxPoint);
	// cout << "end" << endl;
}

std::ostream& operator<<(std::ostream& out, const Mesh& mesh)
{
  out << "mesh {";
  /*
  
  for( size_t idx = 0; idx < mesh.m_verts.size(); ++idx ) {
  	const MeshVertex& v = mesh.m_verts[idx];
  	out << glm::to_string( v.m_position );
	if( mesh.m_have_norm ) {
  	  out << " / " << glm::to_string( v.m_normal );
	}
	if( mesh.m_have_uv ) {
  	  out << " / " << glm::to_string( v.m_uv );
	}
  }

*/
  out << "}";
  return out;
}

Intersect Mesh::intersect(Ray ray) {
	Intersect newIntersect = bounding.intersect(ray);
	// newIntersect.t = 0;
	if (SHOW_BOUNDING_VOLUMN) {
		return newIntersect;
	}
	double t = numeric_limits<double>::max();
	if (newIntersect.t < t && newIntersect.t >= 0) {
		newIntersect.t = numeric_limits<double>::max();
		for (Triangle face : m_faces) {
			bool is_intersect = ray_intersect_triangle(ray, m_vertices[face.v1], m_vertices[face.v2], m_vertices[face.v3], t);
			if (is_intersect) {
				if (t < newIntersect.t && t >= 0) {
					newIntersect.t = t;
					dvec3 n = normalize(cross(m_vertices[face.v2] - m_vertices[face.v1], m_vertices[face.v3] - m_vertices[face.v1]));
					newIntersect.n = dvec4(n, 0);
				}
			}
		}
	}
	return newIntersect;
}
