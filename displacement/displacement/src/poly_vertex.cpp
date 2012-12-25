#include "poly_vertex.h"

PolyVertex::PolyVertex(float _x, float _y, float _z, float _s, float _t) {
	x = _x;
	y = _y;
	z = _z;
	s = _s;
	t = _t;
}


void PolyVertex::normalize() {
	float d = sqrt(x * x + y * y + z * z);
	x /= d;
	y /= d;
	z /= d;
}

void PolyVertex::scaleBy(float n) {
	x *= n;
	y *= n;
	z *= n;
}


void PolyVertex::saveOriginal() {
	ox = x;
	oy = y;
	oz = z;
}

void PolyVertex::loadOriginal() {
	x = ox;
	y = oy;
	z = oz;
}


float PolyVertex::distanceSQ(PolyVertex* v) {
	float dx = x - v->x;
	float dy = y - v->y;
	float dz = z - v->z;
	return 	dx * dx + dy * dy + dz * dz;
}
float PolyVertex::distance(PolyVertex* v) {
	return sqrt(distanceSQ(v));
}
