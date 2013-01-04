#include "displayObject.h"

DisplayObject::DisplayObject( Shape* _shape, GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _xr, GLfloat _yr, GLfloat _zr ) :
x( _x ), y( _y ), z( _z ),
vx(0.0), vy(0.0), vz(0.0),
xr( _xr ), yr( _yr ), zr( _zr ),
shape (_shape)
{}
DisplayObject::~DisplayObject() {
	if (shape) { delete shape; }
}


void DisplayObject::update() {
	x += vx;
	y += vy;
	z += vz;
}

void DisplayObject::draw() {
	ofPushMatrix();
		ofTranslate(x, y, z);
		ofRotateX(xr);
		ofRotateY(yr);
		ofRotateZ(zr);
		shape->draw();
	ofPopMatrix();
}