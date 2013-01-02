#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(255, 255, 255);
    sample.loadImage("sample02.jpg");
    fbo.allocate(sample.width, sample.height);
    
    string shaderProgram = "#version 120\n \
    #extension GL_ARB_texture_rectangle : enable\n \
    \
    uniform sampler2DRect tex0;\
    uniform float threshold;\
    \
    void main (void){\
    vec2 pos = gl_TexCoord[0].st;\
    vec2 pos1 = pos + vec2(2.0, 0.0);\
    vec2 pos2 = pos + vec2(0.0, 2.0);\
    \
    vec3 src = texture2DRect(tex0, pos).rgb;\
    vec3 src1 = texture2DRect(tex0, pos1).rgb;\
    vec3 src2 = texture2DRect(tex0, pos2).rgb;\
    float dist = distance(src, src1);\
    if (distance(src, src1) > threshold || distance(src, src2) > threshold) {\
        src = vec3(0.0);\
    } else {\
        src = vec3(1.0);\
    }\
    \
    gl_FragColor = vec4(dist, dist, dist,1.0);\
    }";
    shader.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
    shader.linkProgram();
    threshold = 0;
    
    drawBuffer.allocate(sample.width, sample.height);
    drawBuffer.begin();
    ofClear(255, 255, 255);
    drawBuffer.end();
    
    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::update(){
    
    fbo.begin();
    shader.begin();
    shader.setUniform1f("threshold", 0.1);
    sample.draw(0,0);
    shader.end();
    fbo.end();
    
    ofPixels pixels;
    fbo.readToPixels(pixels);
    contourSample.setFromPixels(pixels);
    contourSample.setImageType(OF_IMAGE_COLOR);
    colorCVImg.setFromPixels(contourSample.getPixels(), sample.getWidth(),sample.getHeight());
    grayCVImg = colorCVImg;
    
    grayCVImg.threshold(threshold);
    contourFinder.findContours(grayCVImg, 10, (sample.getWidth()*sample.getHeight())/3, 10, true);
    threshold = (threshold + 1) % 255;
    
}

//--------------------------------------------------------------
void testApp::draw(){
    //grayCVImg.draw(0, 0);
    drawBuffer.begin();
    ofPushStyle();
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
    for (int i = 0; i < contourFinder.nBlobs; i++){
        //contourFinder.blobs[i].draw(0,0);
        ofSetColor(0, 0, 0, 68);
        ofNoFill();
        ofBeginShape();
        
        float dist = ofRandom(0,8);
        float angle = ofRandom(PI * 2);
        
        ofCurveVertex(contourFinder.blobs[i].pts[0].x + cos(angle) * dist, contourFinder.blobs[i].pts[0].y + sin(angle) * dist);
        for (int j = 1; j < contourFinder.blobs[i].nPts - 25; j += 25) {
            float dist2 = ofRandom(0,8);
            float angle2 = ofRandom(PI * 2);
            
            ofCurveVertex(contourFinder.blobs[i].pts[j].x + cos(angle2) * dist2, contourFinder.blobs[i].pts[j].y + sin(angle2) * dist2);
        }
        ofCurveVertex(contourFinder.blobs[i].pts[0].x + cos(angle) * dist, contourFinder.blobs[i].pts[0].y + sin(angle) * dist);
        ofEndShape();
    }
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    ofPopStyle();
    drawBuffer.end();
    drawBuffer.draw(0, 0);
    //grayCVImg.draw(0, 0);
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
