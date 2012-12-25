#pragma once


class Tracer {
    
public:
    Tracer();
    ~Tracer();
    void proceed();
    float x, y;
    float vx, vy;
    float maxSpeed;
    int target0;
    int target1;
};

