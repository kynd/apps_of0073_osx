#include "Blob.h"

Blob::Blob() {
    x = y = vx = vy = 0;
    radius = ofRandom(30,60);
    elasticity = 0.1;
    deceleration = 0.98;
    r = ofRandom(255);
    g = ofRandom(255);
    b = ofRandom(255);
    for (int i = 0; i < NUM_CONTOUR; i ++) {
        contour[i] = radius;
        ccos[i] = cos(PI * 2 / (NUM_CONTOUR - 1) * i);
        csin[i] = sin(PI * 2 / (NUM_CONTOUR - 1) * i);
    }
    reset();
}
Blob::~Blob() {
    
}

void Blob::reset() {
    vx = ofRandom(-10,10);
    vy = 0;
    x = ofRandom(-200,200) + ofGetWidth() / 2;
    y = -ofRandom(100,300);
    
    radius = ofRandom(30,80);
}
    
void Blob::update() {
    x += vx;
    y += vy;
    vx *= deceleration;
    vy *= deceleration;
    if (x < radius && ofGetFrameNum() < 2000) {
        accelerate((radius - x) * elasticity, 0);
        //reset();
    }
    if (y < radius) {
        //accelerate(0, (radius - y) * elasticity);
    }
    if (x > ofGetWidth() - radius && ofGetFrameNum() < 2000) {
        accelerate(-(x - (ofGetWidth() - radius)) * elasticity, 0);
        //reset();
    }
    if (y > ofGetHeight() - radius) {
        accelerate(0, -(y - (ofGetHeight() - radius)) * elasticity);
    }
    
    for (int i = 0; i < NUM_CONTOUR; i ++) {
        int next = (i + 1) % NUM_CONTOUR;
        int prev = (i > 0) ? i - 1 : NUM_CONTOUR - 1;
        contour[i] += (radius - contour[i]) / 5;
        contour[i] += ((contour[next] + contour[prev]) / 2 - contour[i]) / 3;
        
        
        float cx = contour[i] * ccos[i] + x;
        float cy = contour[i] * csin[i] + y;
        /*
        if (cx < 0) {
            contour[i] += cx / 2;
        }
        if (cy < 0) {
            contour[i] += cy / 2;
        }
        if (cx > ofGetWidth()) {
            contour[i] -= (cx - ofGetWidth()) / 2;
        }
         */
        if (cy > ofGetHeight()) {
            contour[i] -= (cy - ofGetHeight()) / 2;
        }
    }
    
}

void Blob::draw() {
    ofPushStyle();
    ofSetColor(0,0,0, 55);
    drawShape();
    ofPopStyle();
}

void Blob::drawShape() {
    ofNoFill();
    for(int k = 0; k < 10; k ++) {
        ofBeginShape();
    
    
        float ang0 = ofRandom(PI * 2);
        float dist0 = ofRandom(2) * radius / 50;
    
        ofCurveVertex(contour[0] * ccos[0] + x + cos(ang0) * dist0, contour[0] * csin[0] + y + sin(ang0) * dist0);
        ofCurveVertex(contour[0] * ccos[0] + x + cos(ang0) * dist0, contour[0] * csin[0] + y + sin(ang0) * dist0);
        for (int i = 1; i < NUM_CONTOUR; i ++) {
            float ang = ofRandom(PI * 2);
            float dist = ofRandom(2) * radius / 50;
            ofCurveVertex(contour[i] * ccos[i] + x + cos(ang) * dist, contour[i] * csin[i] + y + sin(ang) * dist);
        }
        ofCurveVertex(contour[0] * ccos[0] + x + cos(ang0) * dist0, contour[0] * csin[0] + y + sin(ang0) * dist0);
        ofEndShape();
    }
    
    
    ofBeginShape();
    
    for(int k = 0; k < 450 * radius / 50; k ++) {
        float ang = ofRandom(PI * 2);
        float dist = ofRandom(2) * radius / 50;
        int i = ofRandom(NUM_CONTOUR);
        ofVertex(contour[i] * ccos[i] + x + cos(ang) * dist, contour[i] * csin[i] + y + sin(ang) * dist);
    }
    ofEndShape();
}

void Blob::react(Blob* b) {
    float dx = x - b->x;
    float dy = y - b->y;
    float dist = sqrt(dx * dx + dy * dy);
    if (dist < radius + b->radius && dist != 0) {
        float overlap = radius + b->radius - dist;
        accelerate(dx / dist * overlap * elasticity, dy / dist * overlap * elasticity);
        b->accelerate(-dx / dist * overlap * elasticity, -dy / dist * overlap * elasticity);
    
        for (int i = 0; i < NUM_CONTOUR; i ++) {
            float cx = contour[i] * ccos[i] + x;
            float cy = contour[i] * csin[i] + y;
            float dx2 = cx - b->x;
            float dy2 = cy - b->y;
            float dist = sqrt(dx2 * dx2 + dy2 * dy2);
            if (dist < b->radius) {
                contour[i] -= (b->radius - dist) / 2;
            }
        }
        for (int i = 0; i < NUM_CONTOUR; i ++) {
            float cx = b->contour[i] * b->ccos[i] + b->x;
            float cy = b->contour[i] * b->csin[i] + b->y;
            float dx2 = cx - x;
            float dy2 = cy - y;
            float dist = sqrt(dx2 * dx2 + dy2 * dy2);
            if (dist < radius) {
                b->contour[i] -= (radius - dist) / 2;
            }
        }
    
    }
    
}


void Blob::accelerate(float _x, float _y) {
    float antiMoment = radius * radius / 2500;
    vx += _x / antiMoment;
    vy += _y / antiMoment;
}