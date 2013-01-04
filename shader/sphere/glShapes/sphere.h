
#ifndef __SPHERE__
#define __SPHERE__


#include "ofMain.h"
#include "shape.h"

class Sphere : public Shape {
public:
    Sphere( float radius=50.f, int vSlices=32, int hSlices=16 );
    ~Sphere();
	
    virtual void draw();
	
private:
    bool init();
	
    float _radius;
    int _vSlices;
    int _hSlices;
	
    GLfloat* _vertices;
    GLfloat* _normals;
    GLfloat* _texCoords;
    GLushort* _indices;
	GLushort* _cap1Start;
    GLushort* _cap2Start;
	
    bool _valid;
    int _numSideVerts;
    int _numCapVerts;
};


#endif
