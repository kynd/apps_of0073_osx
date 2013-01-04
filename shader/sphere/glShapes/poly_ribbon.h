

#ifndef __POLY_RIBBON__
#define __POLY_RIBBON__

#include "ofMain.h"
#include "poly_triangle.h"
#include "poly_vertex.h"
#include "poly_triangleGroup.h"
#include "polygonShape.h"
#include "shapes.h"

class PolyRibbon : public Shape {
public:
    PolyRibbon(int len, float* _verts);
    ~PolyRibbon();
    void draw();
	PolygonShape polygon;
private:
	vector<PolyVertex*> vertices;
	vector<PolyTriangle*> triangles;
};


#endif