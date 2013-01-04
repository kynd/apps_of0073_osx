
#ifndef __LINES__
#define __LINES__


#include "ofMain.h"
#include "shape.h"

class Lines : public Shape {
public:
    Lines( int, GLfloat[], GLfloat[], GLfloat );
    ~Lines();
	
    virtual void draw();
	
private:
    bool init();
	
    GLfloat* _vertices;
	GLfloat* _normals;
    GLushort* _indices;

	GLfloat* _color;
	
    GLuint _idxStart, _idxEnd;
	
    bool _valid;
	int _numVerts;
	GLfloat _width;
};


#endif
