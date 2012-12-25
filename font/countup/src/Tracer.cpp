
#include <Tracer.h>

Tracer::Tracer() {
    x = y = vx = vy = 0;
    maxSpeed = 5;
    target0 = target1 = 0;
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
    if (x >= 1280) {
        x = 0;
    }
    if (y >= 720) {
        y = 0;
    }
    if (x < 0) {
        x = 1279;
    }
    if (y < 0) {
        y = 719;
    }
    vx *= 0.99;
    vy *= 0.99;
}