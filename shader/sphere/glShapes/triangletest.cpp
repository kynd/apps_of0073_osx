#include "triangletest.h"


TriangleTest::TriangleTest() {	
	vertices.push_back(new PolyVertex(-50.f, -50.f, 0.f));
	vertices.push_back(new PolyVertex(50.f, 50.f, 0.f));
	vertices.push_back(new PolyVertex(50.f, -50.f, 0.f));
	triangles.push_back(new PolyTriangle(0, 1, 2));

	
	for (int i = 0; i < vertices.size(); i ++) {
		polygon.addVertex(vertices[i]);
	}
	
	for (int i = 0; i < triangles.size(); i ++) {
		polygon.addTriangle(triangles[i]);
	}
	
	for (int i = 0; i < vertices.size(); i ++) {
		vertices[i]->saveOriginal();
	}
	
	polygon.init();
}


TriangleTest::~TriangleTest() {
}

void TriangleTest::draw() {
	polygon.draw();
}
