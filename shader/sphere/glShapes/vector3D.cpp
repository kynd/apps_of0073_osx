#include "Vector3D.h"

Vector3D::Vector3D(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}

Vector3D* Vector3D::clone(){
	return new Vector3D(x,y,z);
}

Vector3D* Vector3D::zero(){
	x = y = z = 0;
	return this;
}

Boolean Vector3D::isZero(){
	return x == 0.f && y == 0.f && z == 0.f;
}

void Vector3D::setLength(float v){
	normalize();
	multiply(v);
}

float Vector3D::getLength(){
	return sqrt(getLengthSQ());
}

float Vector3D::getLengthSQ(){
	return x * x + y * y + z * z;
}

/*
 void Vector3D::setAngle(float v){
 float len = getLength();
 x = cos(v) * len;
 y = sin(v) * len;
 }
 */

float Vector3D::getAngleXY(float& xr, float& yr){
	float d = sqrt(z * z + x * x);
	xr = -atan2(y, d);
	yr = -atan2(x, z);
}

float Vector3D::getAngleYZ(float& yr, float& zr){
	float d = sqrt(x * x + y * y);
	yr = atan2(z, d);
	zr = atan2(y, x);
}

float Vector3D::getAngleZX(float& zr, float& xr){
	float d = sqrt(y * y + z * z);
	zr = -atan2(x, d);
	xr = atan2(z, y);
}


Vector3D* Vector3D::normalize(){
	float len = getLength();
	if (len == 0) {
		x = 1;
	} else {
		x /= len;
		y /= len;
		z /= len;
	}
	return this;
}

Vector3D* Vector3D::truncate(float v){
	setLength(min(v, getLength()));
	return this;
}

Vector3D* Vector3D::reverse(){
	x = -x;
	y = -y;
	z = -z;
	return this;
}

float Vector3D::dotProd(Vector3D* v2){
	return x * v2->x + y * v2->y + z * v2->z;
}

/*
 float Vector3D::angleBetween(Vector3D* v1, Vector3D* v2){
 float x1, y1, x2, y2;
 float len = v1->getLength();
 if (len == 0) {
 x1 = 1;
 y1 = 0;
 } else {
 x1 = v1->x / len;
 y1 = v1->y / len;
 }
 len = v2->getLength();
 if (len == 0) {
 x2 = 1;
 y2 = 0;
 } else {
 x2 = v2->x / len;
 y2 = v2->y / len;
 }
 
 return acos(x1 * x2 + y1 * y2);
 }
 */

/*
 int Vector3D::sign(Vector3D* v2){
 float x1 = -y;
 float y1 = x;
 float dp = x1 * v2->x + y1 * v2->y;
 return (dp < 0) ? -1: 1;
 }
 */
/*
 Vector3D* Vector3D::perp(){
 return new Vector3D(-y, x);
 }
 */
float Vector3D::dist(Vector3D* v2){
	return sqrt(distSQ(v2));
}


float Vector3D::distSQ(Vector3D* v2){
	float dx = v2->x - x;
	float dy = v2->y - y;
	float dz = v2->z - z;
	return dx * dx + dy * dy + dz * dz;
}

Vector3D* Vector3D::add(Vector3D* v2){
	x += v2->x;
	y += v2->y;
	z += v2->z;
	return this;
}

Vector3D* Vector3D::subtract(Vector3D* v2){
	x -= v2->x;
	y -= v2->y;
	z -= v2->z;
	return this;
}

Vector3D* Vector3D::multiply(float v){
	x *= v;
	y *= v;
	z *= v;
	return this;
}

Vector3D* Vector3D::divide(float v){
	x /= v;
	y /= v;
	z /= v;
	return this;
}

Boolean Vector3D::equals(Vector3D* v2){
	return x == v2->x && y == v2->y && z == v2->z;
}


void Vector3D::rotateX(float theta) {
	float _x, _y, _z;
	_x = x;
	_y = cos(theta) * y - sin(theta) * z;
	_z = sin(theta) * y + cos(theta) * z;
	x = _x;
	y = _y;
	z = _z;
}

void Vector3D::rotateY(float theta) {
	float _x, _y, _z;
	_x = cos(theta) * x - sin(theta) * z;
	_y = y;
	_z = sin(theta) * x + cos(theta) * z;
	x = _x;
	y = _y;
	z = _z;
	
}
void Vector3D::rotateZ(float theta) {
	float _x, _y, _z;
	_x = cos(theta) * x - sin(theta) * y;
	_y = sin(theta) * x + cos(theta) * y;
	_z = z;
	x = _x;
	y = _y;
	z = _z;
}

