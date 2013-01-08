#include "testApp.h"

/*
This example creates an effect like black ink melts and disappears into water.
R and G values in the FBO(s) are used as force of turbulence that moves the ink, while B value represents the actual density(blackness) of the ink.
*/

#define STRINGIFY(A) #A
//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    
    string shaderProgram = STRINGIFY(
                                     uniform sampler2DRect tex0;
                                     void main (void){
                                         vec2 forceSample = texture2DRect(tex0, gl_TexCoord[0].st).rg;
                                         vec2 force = (forceSample - vec2(0.5, 0.5)) * 5.0; // R and B channels are used as the force to move the ink
                                         float b = texture2DRect(tex0, gl_TexCoord[0].st + force).b; // sample the B value with the coordinate slightly displaced with the force
                                         forceSample = mix(forceSample, vec2(0.5,0.5), 0.02); // mix with the neutral value to weaken the force

                                         vec4 outCol = vec4(forceSample.r, forceSample.g, b, 1.0); // combine the values from two samples
                                         gl_FragColor = outCol;
                                     }
                                     );
    
    
    processShader.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
    processShader.linkProgram();
    
    shaderProgram = STRINGIFY(
                                     uniform sampler2DRect tex0;
                                     void main (void){
                                         float b = 1.0 - texture2DRect(tex0, gl_TexCoord[0].st).b; // Picks only B value for rendering
                                         gl_FragColor = vec4(b, b, b, 1.0);
                                     }
                                     );
    
    renderShader.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
    renderShader.linkProgram();
    
    for (int i = 0; i < 2; i ++) {
        FBOs[i].allocate(ofGetWidth(), ofGetHeight(), GL_RGB32F);
        FBOs[i].begin();
        ofClear(128, 128, 0);
        FBOs[i].end();
    }
    pingPongIndexA = 0;
    bDrag = false;
    brush.loadImage("brush.png");
    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::update(){
    //get noise values to be used as the force
    float t = ofGetFrameNum() * 0.01;
	float nx = ofNormalize(mouseX, 0, ofGetWidth());
	float ny = ofNormalize(mouseY, 0, ofGetHeight());
	float r = ofNoise(0 + t, nx * 5, ny * 5) * 255.f;
	float g = ofNoise(TWO_PI + t, nx * 10, ny * 10) * 255.f;
    
    //swap the indices
    pingPongIndexB = pingPongIndexA;
    pingPongIndexA = (pingPongIndexA + 1) % 2;
    
    //draw the brush on the first FBO
    FBOs[pingPongIndexA].begin();
    ofPushStyle();
    ofSetColor(r, g, 255, 50);
    if (bDrag) {
        brush.draw(mouseX - brush.width / 2, mouseY - brush.height / 2);
    }
    ofPopStyle();
    FBOs[pingPongIndexA].end();
    
    //draw the first FBO onto the second FBO applying the processShader
    FBOs[pingPongIndexB].begin();
    processShader.begin();
    FBOs[pingPongIndexA].draw(0,0);
    processShader.end();
    FBOs[pingPongIndexB].end();
}

//--------------------------------------------------------------
void testApp::draw(){
    //draw the FBO with render shader so that it appears in black and white
    renderShader.begin();
    FBOs[pingPongIndexB].draw(0, 0);
    renderShader.end();
    
    ofPushStyle();
    ofSetColor(128);
    ofDrawBitmapString("Drag the mouse to draw on the screen", 10, 20);
    ofPopStyle();
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
    bDrag = true;

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    bDrag = false;
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