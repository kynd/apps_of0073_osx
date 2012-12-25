#ifndef __POLY_VERTEX__
#define __POLY_VERTEX__

#include "ofMain.h"

class PolyVertex {
public:
    PolyVertex(float x, float y, float z, float s = 0.0, float t = 0.0);
	void normalize();
	void scaleBy(float);
	float distanceSQ(PolyVertex*);
	float distance(PolyVertex*);
	void loadOriginal();
	void saveOriginal();
	float x, y, z, s, t;
	float ox, oy, oz;
};


#endif