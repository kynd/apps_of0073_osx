

#ifndef __FLEX_TUBE__
#define __FLEX_TUBE__

#include "ofMain.h"
#include "poly_triangle.h"
#include "poly_vertex.h"
#include "poly_triangleGroup.h"
#include "polygonShape.h"
#include "shape.h"
#include "vector3D.h"

class FlexTube : public Shape {
public:
    FlexTube(int _length, int _slices, float* coords, float* broadth, bool _drawCap1 = true, bool _drawCap2 = true);
    ~FlexTube();
	void update(float* coords, float* broadth);
    void draw();
protected:
	PolygonShape polygon;
	vector<PolyVertex*> vertices;
	vector<PolyTriangle*> triangles;
	int length, slices, capIndex1, capIndex2;
	bool drawCap1, drawCap2;
};


#endif