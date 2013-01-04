#ifndef __VECTOR_3D__
#define __VECTOR_3D__

#include "ofMain.h"

class Vector3D {
public:
	Vector3D(float = 0.f, float = 0.f, float = 0.f);
	float x, y, z;
	Vector3D* clone();
	Vector3D* zero();
	Boolean isZero();
	void setLength(float);
	float getLength();
	float getLengthSQ();
	//void setAngle(float);
	float getAngleXY(float& xr, float& yr);
	float getAngleYZ(float& yr, float& zr);
	float getAngleZX(float& zr, float& xr);
	Vector3D* normalize();
	Vector3D* truncate(float);
	Vector3D* reverse();
	float dotProd(Vector3D*);
	//static float angleBetween(Vector3D*, Vector3D*);
	//int sign(Vector3D*);
	//Vector3D* perp();
	float dist(Vector3D*);
	float distSQ(Vector3D*);
	Vector3D* add(Vector3D*);
	Vector3D* subtract(Vector3D*);
	Vector3D* multiply(float);
	Vector3D* divide(float);
	Boolean equals(Vector3D*);
	void rotateX(float theta);
	void rotateY(float theta);
	void rotateZ(float theta);
	
private:
	
};

#endif;