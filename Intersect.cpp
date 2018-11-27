#include <limits>
#include "Intersect.hpp"
using namespace std;


Intersect::Intersect() : t(numeric_limits<double>::max()), n(glm::dvec4()), m_material(0)
{}
