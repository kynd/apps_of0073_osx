
#include <Tracer.h>

Tracer::Tracer() {
    x = y = vx = vy = 0;
    maxSpeed = ofRandom(1,15);
    target0 = target1 = 0;
    r,g,b = 0;
}
Tracer::~Tracer() {
    
}

void Tracer::proceed() {
    float spd = sqrt(vx * vx + vy * vy);
    if (spd > maxSpeed) {
        vx = vx / spd * maxSpeed;
        vy = vy / spd * maxSpeed;
    }
    x += vx;
    y += vy;
    
    if (x >= 1279) {
        x = 1279;
        vy *= -1;
    }
    if (y >= 719) {
        y = 719;
        vy *= -1;
    }
    if (x < 0) {
        x = 0;
        vy *= -1;
    }
    if (y < 0) {
        y = 0;
        vy *= -1;
    }
    vx *= 0.99;
    vy *= 0.99;
}