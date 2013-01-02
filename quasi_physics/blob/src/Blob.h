
#pragma once

#include "ofMain.h"

#define NUM_CONTOUR 30

class Blob {
	
public:
	Blob();
    ~Blob();
    
	void update();
	void draw();
	void react(Blob* b);
    void accelerate(float _x, float _y);
    void drawShape();
    void reset();
    
    float x, y, vx, vy, radius, elasticity, deceleration;
    float contour[NUM_CONTOUR];
    float ccos[NUM_CONTOUR];
    float csin[NUM_CONTOUR];
    int r,g,b;
};


