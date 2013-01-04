
#ifndef __CUBE__
#define __CUBE__


#include "ofMain.h"
#include "shape.h"

class Cube : public Shape {
public:
    Cube( float size=100.f );
    ~Cube();
	
    virtual void draw();
	
private:
    bool init();
	
    float _size;
	
    GLfloat* _vertices;
    GLfloat* _normals;
    GLushort* _indices;
	
    GLuint _idxStart, _idxEnd;
	
    bool _valid;
    int _numVerts;
};


#endif
