#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    sample.loadImage("sample01.jpg");
    colorImg.allocate(sample.getWidth(), sample.getHeight());
    grayImg.allocate(sample.getWidth(), sample.getHeight());
    threshold = 0;
}

//--------------------------------------------------------------
void testApp::update(){
    
    colorImg.setFromPixels(sample.getPixels(), sample.getWidth(),sample.getHeight());
    grayImg = colorImg;
    
    grayImg.threshold(threshold);
    contourFinder.findContours(grayImg, 20, (340*240)/3, 10, true);
    threshold = (threshold + 1) % 255;
}

//--------------------------------------------------------------
void testApp::draw(){
    grayImg.draw(0, 0);
    for (int i = 0; i < contourFinder.nBlobs; i++){
        contourFinder.blobs[i].draw(0,0);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

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
