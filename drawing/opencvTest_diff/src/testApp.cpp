#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    sample.loadImage("sample01.jpg");
    benchmark.allocate(sample.width, sample.height, OF_IMAGE_COLOR);
    sampleCVImg.allocate(sample.getWidth(), sample.getHeight());
    benchmarkCVImg.allocate(sample.getWidth(), sample.getHeight());
    diffCVImg.allocate(sample.getWidth(), sample.getHeight());
    buffCVImage.allocate(sample.getWidth(), sample.getHeight());
    
    fbo.allocate(sample.width, sample.height);
    threshold = 0;
}

//--------------------------------------------------------------
void testApp::update(){
    threshold = (threshold + 1) % 255;
    
    buffCVImage.setFromPixels(sample.getPixels(), sample.getWidth(),sample.getHeight());
    sampleCVImg = buffCVImage;

    fbo.begin();
    ofClear(threshold, threshold, threshold);
    fbo.end();
    ofPixels pixels;
    fbo.readToPixels(pixels);
    benchmark.setFromPixels(pixels);
    benchmark.setImageType(OF_IMAGE_COLOR);
    buffCVImage.setFromPixels(benchmark.getPixels(), sample.getWidth(),sample.getHeight());
    benchmarkCVImg = buffCVImage;
    diffCVImg.absDiff(sampleCVImg, benchmarkCVImg);
    diffCVImg.threshold(80);
}

//--------------------------------------------------------------
void testApp::draw(){
    diffCVImg.draw(0, 0);
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
