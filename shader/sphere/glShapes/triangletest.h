

#ifndef __TTEST__
#define __TTEST__

#include "ofMain.h"
#include "poly_triangle.h"
#include "poly_vertex.h"
#include "poly_triangleGroup.h"
#include "polygonShape.h"
#include "shape.h"

class TriangleTest : public Shape {
public:
    TriangleTest();
    ~TriangleTest();
    void draw();
private:
	PolygonShape polygon;
	vector<PolyVertex*> vertices;
	vector<PolyTriangle*> triangles;
};


#endif