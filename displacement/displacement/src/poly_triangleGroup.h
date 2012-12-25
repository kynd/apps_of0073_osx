#ifndef __POLY_TRIANGLE_GROUP__
#define __POLY_TRIANGLE_GROUP__

#include "ofMain.h"
#include "poly_triangle.h"

class PolyTriangleGroup {
public:
    PolyTriangleGroup();
    ~PolyTriangleGroup();
	void add(PolyTriangle*);
	vector<PolyTriangle*> triangles;
};


#endif