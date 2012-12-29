#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofBackground(0, 0, 0);
    srcImg.loadImage("B.jpg");
    brushImg.loadImage("brush.png");
    
    int width = srcImg.getWidth();
    int height = srcImg.getHeight();
    
    forceFbo.allocate(width,height);
    fbo.allocate(width,height);
    
    ofSetWindowShape(width, height);
    
    string shaderProgram = "#version 120\n \
    #extension GL_ARB_texture_rectangle : enable\n \
    \
    uniform sampler2DRect tex0;\
    uniform sampler2DRect forceTex;\
    \
    void main (void){\
    vec2 pos = gl_TexCoord[0].st;\
    \
    vec2 force = texture2DRect(forceTex, pos).rg;\
    pos.s += (force.r - 0.5) * 300.0;\
    pos.t += (force.g - 0.5) * 300.0;\
    vec3 src = texture2DRect(tex0, pos).rgb;\
    \
    gl_FragColor = vec4(src , 1.0);\
    }";
    shader.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
    shader.linkProgram();
    
    forceFbo.begin();
    ofClear(128,128,128,0);
    forceFbo.end();
    
    fbo.begin();
    ofClear(0,0,0,255);
    fbo.end();
    
    bBrushDown = false;
}

//--------------------------------------------------------------
void testApp::update(){
    
    forceFbo.begin();
    if (bBrushDown){
        ofPushStyle();
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
        ofSetColor(ofNoise((float)mouseX / 100.0) * 255.0, ofNoise((float)mouseY / 100.0 + 0.5) * 255.0, 0);
        brushImg.draw(mouseX-25,mouseY-25,50,50);
        ofPopStyle();
    }
    forceFbo.end();
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
    fbo.begin();
    // Cleaning everthing with alpha mask on 0 in order to make it transparent for default
    ofClear(0, 0, 0, 0); 
    
    shader.begin();
    shader.setUniformTexture("forceTex", forceFbo.getTextureReference(), 1 );
    
    srcImg.draw(0,0);

    shader.end();
    fbo.end();

}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255,255);
    
    
    fbo.draw(0,0);
    
    ofDrawBitmapString("Drag the Mouse to draw", 15,15);
    ofDrawBitmapString("Press spacebar to clear", 15, 30);
    
    
    //forceFbo.draw(0, 0);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    forceFbo.begin();
    ofClear(0,0,0,255);
    forceFbo.end();
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
    bBrushDown = true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    bBrushDown = false;
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