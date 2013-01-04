#ifndef __POLY_TRIANGLE__
#define __POLY_TRIANGLE__


#include "ofMain.h"
#include "poly_vertex.h"

class PolyTriangle {
public:
	PolyTriangle(int, int, int);
	int indices[3];
};


#endif