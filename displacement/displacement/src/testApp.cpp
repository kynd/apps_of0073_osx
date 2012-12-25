#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	plane = new Plane(ofGetWidth(),ofGetHeight(),2,2);
	shader.load("shader.vs", "shader.fs");
	texture = new TextureUtil2D(2);
	
	//texture
	img0.loadImage("source.jpg");
	img1.loadImage("noisemap.jpg");
	glEnable(GL_TEXTURE_2D);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	ofPushMatrix();
	shader.begin();
	
	glActiveTexture(GL_TEXTURE0);
	texture->setTexture(img0.getPixels(), 0, img0.getWidth(), img0.getHeight(), GL_RGB);
	glBindTexture(GL_TEXTURE_2D, texture->getTexture(0));
	glActiveTexture(GL_TEXTURE1);
	texture->setTexture(img1.getPixels(), 1, img1.getWidth(), img1.getHeight(), GL_RGB);
	glBindTexture(GL_TEXTURE_2D, texture->getTexture(1));
	shader.setUniform1i("tex0", 0);
	shader.setUniform1i("tex1", 1);
	ofTranslate(ofGetWidth() / 2.0, ofGetHeight() / 2.0, 0.0);
	plane->draw();
	shader.end();
	ofPopMatrix();
    ofPushStyle();
    ofSetColor(0, 0, 0);
    ofCircle(mouseX, mouseY, 20);
	img0.grabScreen(0, 0, ofGetWidth(),ofGetHeight());
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