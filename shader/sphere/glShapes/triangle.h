
#ifndef __TRIANGLE__
#define __TRIANGLE__


#include "ofMain.h"
#include "shape.h"

class Triangle : public Shape {
public:
    Triangle( GLfloat[9] );
    ~Triangle();
	
    virtual void draw();
	
private:
    bool init();
	
    GLfloat* _vertices;
    GLfloat* _normals;
    GLushort* _indices;
	
    GLuint _idxStart, _idxEnd;
	
    bool _valid;
    int _numVerts;
};


#endif
