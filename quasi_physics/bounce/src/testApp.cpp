#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    for (int i = 0; i < blobs.size(); i ++) {
        delete blobs[i];
        blobs[i] = NULL;
    }
    blobs.clear();
    for (int i = 0; i < NUM_BLOBS; i ++) {
        addBlob(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
    }
    bg.loadImage("bg.png");
}

void testApp::addBlob(float x, float y) {
    Blob* b = new Blob();
    /*
    b->x = x;
    b->y = y;
    //float dir = ofRandom(PI * 2);
    //b->vx = cos(dir) * 15;
    //b->vy = sin(dir) * 15;
     */
    blobs.push_back(b);
}

//--------------------------------------------------------------
void testApp::update(){
    
	float ax = 0;
    float ay = -0.5;
    for (int i = 0; i < blobs.size(); i ++) {
        for (int j = i; j < blobs.size(); j ++) {
            blobs[i]->react(blobs[j]);
        }
    }
    for (int i = 0; i < blobs.size(); i ++) {
        blobs[i]->accelerate(ax, -ay);
        blobs[i]->update();
        if (ofGetFrameNum() == 2000) {
            blobs[i]->vx += ofRandom(-5, 5);
            blobs[i]->vy += ofRandom(-25, 5);
        }
        if (ofGetFrameNum() >= 2000) {
            blobs[i]->vx += (blobs[i]->x - ofGetWidth() / 2) / 1000;
        }
    }
    
    if (ofGetFrameNum() == 2000) {
        Blob* b = new Blob();
        
        b->x = ofGetWidth() / 2;
        b->y = 600;
        b->radius = 60;
        blobs.push_back(b);
    }
    if (ofRandom(1.0) < 0.1 && ofRandom(3000) < ofGetFrameNum() && ofGetFrameNum() < 2000) {
        addBlob(0, 0);
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofClear(255,255,255,255);
    ofPushMatrix();
    for (int i = 0; i < blobs.size(); i ++) {
        blobs[i]->draw();
    }
    ofPopMatrix();
    
    
    //pop
    ofPopMatrix();
    ofPushStyle();
    ofSetColor(255, 255, 255, 200);
    glBlendFunc(GL_ONE, GL_ONE);
    bg.draw(0, 0);
    
    ofSetColor(255, 255, 255, 255);
    glBlendFunc(GL_ZERO, GL_SRC_COLOR);
    bg.draw(0, 0);
    
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    ofPopStyle();
    
    if (ofGetFrameNum() % 2 == 0) {
        //v.save();
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}