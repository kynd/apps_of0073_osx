#include "plane.h"


Plane::Plane(float _w, float _h, int _ws, int _hs):
w(_w),
h(_h),
wslices(_ws),
hslices(_hs)
{	
	
	for (int j = 0; j <= hslices; j ++) {
		for (int i = 0; i <= wslices; i ++) {
			vertices.push_back(new PolyVertex(w / wslices * i - w / 2, h / hslices * j - h / 2, 0.0, 1.0 / wslices * i, 1.0 / hslices * j));
			if (j > 0 && i > 0) {
				int crnt = i + j * (wslices + 1);
				triangles.push_back(new PolyTriangle(crnt - wslices - 2, crnt - 1, crnt - wslices - 1));
				triangles.push_back(new PolyTriangle(crnt - wslices - 1, crnt - 1, crnt));
			}
							   
		}
	}
	
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


Plane::~Plane() {
}

void Plane::draw() {
	polygon.draw();
}
