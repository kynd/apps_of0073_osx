#include "poly_ribbon.h"


PolyRibbon::PolyRibbon(int len, float* _verts)
{	
	
	//TraceBuffer::buff = "";
	for (int i = 0; i < len; i ++) {
		vertices.push_back(new PolyVertex(_verts[i * 6], _verts[i * 6 + 1], _verts[i * 6 + 2], 1.f / (len - 1) * i, 0.f));
		vertices.push_back(new PolyVertex(_verts[i * 6 + 3], _verts[i * 6 + 4], _verts[i * 6 + 5], 1.f / (len - 1) * i, 1.f));
		
		
		//TraceBuffer::buff += ofToString(_verts[i * 6]) + ", " + ofToString(_verts[i * 6 + 1]) + ", " + ofToString(_verts[i * 6 + 2]) + ", "; 
		//TraceBuffer::buff += ofToString(_verts[i * 6 + 3]) + ", " +  ofToString(_verts[i * 6 + 4]) + ", " +  ofToString(_verts[i * 6 + 5]) + "\n";
		
		if (i > 0) {
			triangles.push_back(new PolyTriangle(i * 2 - 2, i * 2 + 1, i * 2));
			triangles.push_back(new PolyTriangle(i * 2 - 2, i * 2 - 1, i * 2 + 1));
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


PolyRibbon::~PolyRibbon() {
}

void PolyRibbon::draw() {
	polygon.draw();
}
