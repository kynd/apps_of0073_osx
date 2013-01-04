#include "icosahedron.h"


Icosahedron::Icosahedron(float rad):
radius(rad)
{	
	float t = (1.0 + sqrt(5.0)) / 2.0;
	addVertex(-1,  t,  0);
	addVertex( 1,  t,  0);
	addVertex(-1, -t,  0);
	addVertex( 1, -t,  0);
	
	addVertex( 0, -1,  t);
	addVertex( 0,  1,  t);
	addVertex( 0, -1, -t);
	addVertex( 0,  1, -t);
	
	addVertex( t,  0, -1);
	addVertex( t,  0,  1);
	addVertex(-t,  0, -1);
	addVertex(-t,  0,  1);
	
	
	triangles.push_back(new PolyTriangle(0, 5, 11));
	triangles.push_back(new PolyTriangle(0, 1, 5));
	triangles.push_back(new PolyTriangle(0, 7, 1));
	triangles.push_back(new PolyTriangle(0, 10, 7));
	triangles.push_back(new PolyTriangle(0, 11, 10));
	
	triangles.push_back(new PolyTriangle(1, 9, 5));
	triangles.push_back(new PolyTriangle(5, 4, 11));
	triangles.push_back(new PolyTriangle(11, 2, 10));
	triangles.push_back(new PolyTriangle(10, 6, 7));
	triangles.push_back(new PolyTriangle(7, 8, 1));
	
	triangles.push_back(new PolyTriangle(3, 4, 9));
	triangles.push_back(new PolyTriangle(3, 2, 4));
	triangles.push_back(new PolyTriangle(3, 6, 2));
	triangles.push_back(new PolyTriangle(3, 8, 6));
	triangles.push_back(new PolyTriangle(3, 9, 8));
	
	triangles.push_back(new PolyTriangle(4, 5, 9));
	triangles.push_back(new PolyTriangle(2, 11, 4));
	triangles.push_back(new PolyTriangle(6, 10, 2));
	triangles.push_back(new PolyTriangle(8, 7, 6));
	triangles.push_back(new PolyTriangle(9, 1, 8));
	
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

int Icosahedron::addVertex(float _x, float _y, float _z) {
	int d = vertices.size();
	PolyVertex* v = new PolyVertex(_x,_y,_z);
	v->normalize();
	v->scaleBy(radius);
	vertices.push_back(v);
	return vertices.size() - 1;
}

Icosahedron::~Icosahedron() {
}

void Icosahedron::draw() {
	polygon.draw();
}
