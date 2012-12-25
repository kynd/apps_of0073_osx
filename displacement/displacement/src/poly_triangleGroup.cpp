#include "poly_triangleGroup.h"

PolyTriangleGroup::PolyTriangleGroup() {
}
PolyTriangleGroup::~PolyTriangleGroup() {
}
void PolyTriangleGroup::add(PolyTriangle* t) {
	Boolean flag = false;
	for (int i = 0; i < triangles.size(); i++) {
		if (triangles[i] == t) {
			flag = true;
		}
	}
	if (!flag) {
		triangles.push_back(t);
	}
}