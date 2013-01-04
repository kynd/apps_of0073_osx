

#ifndef __ICOSAHEDRON__
#define __ICOSAHEDRON__

#include "ofMain.h"
#include "poly_triangle.h"
#include "poly_vertex.h"
#include "poly_triangleGroup.h"
#include "polygonShape.h"
#include "shape.h"

class Icosahedron : public Shape {
public:
    Icosahedron(float = 50.f);
    ~Icosahedron();
    void draw();
private:
	int addVertex(float, float, float);
	PolygonShape polygon;
	vector<PolyVertex*> vertices;
	vector<PolyTriangle*> triangles;
	float radius;
};


#endif