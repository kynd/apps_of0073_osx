#include "testApp.h"

#define STRINGIFY(A) #A
//--------------------------------------------------------------
void testApp::setup(){
    sample.loadImage("sample01.jpg"); // ofImage
    //shader.load("shader.vs","shader.fs");
    string vert = STRINGIFY(
                            varying vec3 p;
                            varying vec3 n;
                            
                            void main(void)
                            {
                                p = vec3(gl_ModelViewMatrix * gl_Vertex);
                                n = normalize(gl_NormalMatrix * gl_Normal).xyz;
                                gl_TexCoord[0] = gl_MultiTexCoord0;
                                gl_Position = ftransform();
                            }
                            );
    string frag = STRINGIFY(
                            
                            varying vec3 p;
                            varying vec3 n;
                            
                            uniform sampler2D tex0;
                            
                            void main(void)
                            {
                                vec4 texCol = texture2D(tex0, gl_TexCoord[0].st);
                                texCol.r += n.x;
                                texCol.g += n.y;
                                gl_FragColor = texCol;
                            }
                            
                            );
    shader.setupShaderFromSource(GL_VERTEX_SHADER, vert);
    shader.setupShaderFromSource(GL_FRAGMENT_SHADER, frag);
    shader.linkProgram();
    
    glEnable(GL_DEPTH_TEST);
    fbo.allocate(1280, 720, GL_RGB32F);
    
    fbo.begin();
    
    ofClear(0, 0, 0);
    fbo.end();
}

//--------------------------------------------------------------
void testApp::update(){
    fbo.begin();
    ofPushStyle();
    for (int i = 1; i < 20; i ++) {
        if (i % 2 == 0) {ofSetColor(255, 255, 0);} else {ofSetColor(255, 255, 255);}
        ofLine(0, i * fbo.getHeight() / 20, fbo.getWidth(), i * fbo.getHeight() / 20);
    }
    for (int i = 1; i < 40; i ++) {
        if (i % 2 == 0) {ofSetColor(255, 255, 0);} else {ofSetColor(255, 255, 255);}
        ofLine(i * fbo.getWidth() / 40, 0, i * fbo.getWidth() / 40, fbo.getHeight());
    }
    ofPopStyle();
    fbo.end();
    
    ofPixels pixels;
    fbo.readToPixels(pixels);
    sample.setFromPixels(pixels);
    sample.setImageType(OF_IMAGE_COLOR);
}

//--------------------------------------------------------------
void testApp::draw(){
    
    sample.draw(0, 0, 600, 600);
    drawSphere();
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

//--------------------------------------------------------------
void testApp::drawSphere() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glEnable(GL_DEPTH_TEST);
    ofPushMatrix();
    shader.begin();
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sample.width,sample.height, 0, GL_RGB, GL_UNSIGNED_BYTE, sample.getPixels());
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    ofRotateY((float) ofGetFrameNum() / 5);
    ofSphere(0, 0, 0, 300);
    shader.end();
    ofPopMatrix();
    glDisable(GL_CULL_FACE);
}