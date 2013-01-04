

#ifndef __IcoMenbrane_h
#define __IcoMenbrane_h

#include "ofMain.h"
#include "poly_triangle.h"
#include "poly_vertex.h"
#include "poly_triangleGroup.h"
#include "polygonShape.h"
#include "shape.h"

class IcoMembrane : public Shape {
public:
    IcoMembrane(int _length, float* coords, float _max = 50.f, float _min = 2.f, int _maxPolygon = 150000);
    ~IcoMembrane();
	void update(int _length, float* coords);
    void draw();
protected:
    float distance(PolyVertex v1, PolyVertex v2);
    float minThreshold,maxThreshold;
    GLfloat* _vertices;
    GLfloat* _normals;
    GLushort* _indices;
    int numTriangle;
    int maxPolygon;
    
};

#endif
