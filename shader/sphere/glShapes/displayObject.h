#ifndef DISPLAYOBJECT
#define DISPLAYOBJECT


#include "ofMain.h"
#include "shape.h"

class DisplayObject {
public:
    DisplayObject( Shape*, GLfloat = 0.f, GLfloat = 0.f, GLfloat = 0.f, GLfloat = 0.f, GLfloat = 0.f, GLfloat = 0.f );
    ~DisplayObject();
	void update();
    virtual void draw();
	GLfloat x, y, z, vx, vy, vz, xr, yr, zr;
	string extra;
	Shape* shape;
};


#endif
