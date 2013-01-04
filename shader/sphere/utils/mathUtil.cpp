#include "mathUtil.h"
#include "ofMain.h"
MathUtil::MathUtil() {}

MathUtil::~MathUtil() {}

float MathUtil::dist(float x0, float y0, float x1, float y1) {
    float dx = x1 - x0;
    float dy = y1 - y0;
    return sqrt(dx * dx + dy * dy);
    
}


void MathUtil::rotate(float &a, float &b, float angle) {
    float ta = a;
    float tb = b;
    float co = cos(angle);
    float si = sin(angle);
    a = ta * co - tb * si;
    b = ta * si + tb * co;
}

