

#ifndef __PLANE__
#define __PLANE__

#include "ofMain.h"
#include "poly_triangle.h"
#include "poly_vertex.h"
#include "poly_triangleGroup.h"
#include "polygonShape.h"
#include "shape.h"

class Plane : public Shape {
public:
    Plane(float = 100.f, float = 100.f, int = 10, int = 10);
    ~Plane();
    void draw();
	PolygonShape polygon;
	float w,h;
	int wslices, hslices;
private:
	vector<PolyVertex*> vertices;
	vector<PolyTriangle*> triangles;
};


#endif