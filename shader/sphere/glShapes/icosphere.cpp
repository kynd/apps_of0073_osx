#include "icosphere.h"


Icosphere::Icosphere(float rad, int rec):
radius(rad),
recursion(rec)
{
	/*
	a1 = ofRandom(0.f, TWO_PI);
	a2 = ofRandom(0.f, TWO_PI);
	a3 = ofRandom(0.f, TWO_PI);
	a4 = ofRandom(0.f, TWO_PI);
	a5 = ofRandom(0.f, TWO_PI);
	*/
	
	float t = (1.0 + sqrt(5.0)) / 2.0;
	addVertex(-1,  t,  0);
	addVertex( 1,  t,  0);
	addVertex(-1, -t,  0);
	addVertex( 1, -t,  0);
	
	addVertex( 0, -1,  t);
	addVertex( 0,  1,  t);
	addVertex( 0, -1, -t);
	addVertex( 0,  1, -t);
	
	addVertex( t,  0, -1);
	addVertex( t,  0,  1);
	addVertex(-t,  0, -1);
	addVertex(-t,  0,  1);

	
	triangles.push_back(new PolyTriangle(0, 5, 11));
	triangles.push_back(new PolyTriangle(0, 1, 5));
	triangles.push_back(new PolyTriangle(0, 7, 1));
	triangles.push_back(new PolyTriangle(0, 10, 7));
	triangles.push_back(new PolyTriangle(0, 11, 10));
	
	triangles.push_back(new PolyTriangle(1, 9, 5));
	triangles.push_back(new PolyTriangle(5, 4, 11));
	triangles.push_back(new PolyTriangle(11, 2, 10));
	triangles.push_back(new PolyTriangle(10, 6, 7));
	triangles.push_back(new PolyTriangle(7, 8, 1));
	
	triangles.push_back(new PolyTriangle(3, 4, 9));
	triangles.push_back(new PolyTriangle(3, 2, 4));
	triangles.push_back(new PolyTriangle(3, 6, 2));
	triangles.push_back(new PolyTriangle(3, 8, 6));
	triangles.push_back(new PolyTriangle(3, 9, 8));
	
	triangles.push_back(new PolyTriangle(4, 5, 9));
	triangles.push_back(new PolyTriangle(2, 11, 4));
	triangles.push_back(new PolyTriangle(6, 10, 2));
	triangles.push_back(new PolyTriangle(8, 7, 6));
	triangles.push_back(new PolyTriangle(9, 1, 8));

	for (int i = 0; i < recursion; i++) {
		vector<PolyTriangle*> triangles2;
		for (int j = 0; j < triangles.size();j ++) {
			int a = getMiddlePoint(triangles[j]->indices[0],triangles[j]->indices[1]);
			int b = getMiddlePoint(triangles[j]->indices[1],triangles[j]->indices[2]);
			int c = getMiddlePoint(triangles[j]->indices[2],triangles[j]->indices[0]);
			
			triangles2.push_back(new PolyTriangle(triangles[j]->indices[0], a, c));
			triangles2.push_back(new PolyTriangle(triangles[j]->indices[1], b, a));
			triangles2.push_back(new PolyTriangle(triangles[j]->indices[2], c, b));
			triangles2.push_back(new PolyTriangle(a, b, c));
		}
		triangles = triangles2;
	}
	
	PolyTriangle* b = triangles[0];

	
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

int Icosphere::getMiddlePoint(int i1, int i2) {
	
	Boolean IsFirstSmaller = i1<i2;
	int smallerIndex = IsFirstSmaller ? i1:i2;
	int greaterIndex = IsFirstSmaller ? i2:i1;
	int key = (smallerIndex << 16) + greaterIndex;
	
	if (cache[key]) {
		return cache[key] - 1;
	}
	
	PolyVertex* v1 = vertices[i1];
	PolyVertex* v2 = vertices[i2];
	
	int index = addVertex((v1->x + v2->x) / 2, (v1->y + v2->y) / 2, (v1->z + v2->z) / 2);
	cache[key] = index + 1;
	
	return index;
}

int Icosphere::addVertex(float _x, float _y, float _z) {
	int d = vertices.size();
	PolyVertex* v = new PolyVertex(_x,_y,_z);
	v->normalize();
	v->scaleBy(radius);
	vertices.push_back(v);
	return vertices.size() - 1;
}

Icosphere::~Icosphere() {
}

void Icosphere::draw() {
	polygon.draw();
}

/*
void Icosphere::update() {
	a1 += 0.01;
	a2 += 0.02;
	a3 += 0.03;
	a4 += 0.04;
	a5 += 0.05;
	//transform
	
	vector<PolyVertex*> rippleCenter;
	rippleCenter.push_back(new PolyVertex(cos(a1) * 50.f, sin(a1) * 20.f, sin(a3) * 80.f));
	rippleCenter.push_back(new PolyVertex(cos(a4) * 80.f, cos(a2) * 50.f, sin(a2) * 20.f));			
	rippleCenter.push_back(new PolyVertex(sin(a1) * 50.f, sin(a5) * 30.f, cos(a2) * 50.f));
	rippleCenter.push_back(new PolyVertex(cos(a3) * 50.f, sin(a2) * 40.f, cos(a3) * 30.f));
	float l = sin(a5) * 2.f + sin(a4) * 4.f;
	for (int i = 0; i < vertices.size(); i ++) {
		for (int j = 0; j < rippleCenter.size(); j ++) {
			float d = rippleCenter[j]->distance(vertices[i]);
			float a = sin(d / (float)(i + 10)) + sin(d * l / 80);
			vertices[i]->loadOriginal();
			vertices[i]->scaleBy(1.f + a * (j + 1) * (j + 1) / d * 2);
			
		}
	}
	
	polygon.init();
}
*/
