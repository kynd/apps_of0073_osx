

#ifndef __CONE__
#define __CONE__


#include "ofMain.h"
#include "shape.h"

class Cone : public Shape {
public:
    Cone( float radius=50.f, float length=100.f, int slices=48 );
    ~Cone();
	
    virtual void draw();
	virtual void cap( bool);
	
private:
    bool init();
	
    float _radius;
    float _length;
    int _slices;
    bool _drawCap;
	
    GLfloat* _vertices;
    GLfloat* _normals;
    GLushort* _indices;
    GLushort* _capStart;
	
    GLuint _idxStart, _capIdx, _idxEnd;
	
    bool _valid;
    int _numVerts;
    int _numCapVerts;
};


#endif
