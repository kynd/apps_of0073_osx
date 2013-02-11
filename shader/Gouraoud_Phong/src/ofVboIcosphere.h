

#ifndef __ICOSHERE__
#define __ICOSHERE__

#include "ofMain.h"


struct PolyTriangle {
	int indices[3];
public:
	PolyTriangle(int a, int b, int c){
		indices[0] = a;
		indices[1] = b;
		indices[2] = c;
	}
};


class ofVboIcosphere {
public:
    ofVboIcosphere(float = 100.f,int = 3);
    ~ofVboIcosphere();
	void update();
    void draw(bool wireframe = false);
	vector<ofVec3f> vertices;
	vector<ofVec3f> normals;
protected:
	int addVertex(float, float, float);
	int getMiddlePoint(int i1, int i2);
	vector<PolyTriangle> triangles;
    ofVboMesh mesh;
	float radius;
	int recursion;
	map<int, int> cache;
};

#endif