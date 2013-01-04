#include "testApp.h"

#define STRINGIFY(A) #A
//--------------------------------------------------------------
void testApp::setup(){
    sample.loadImage("sample01.jpg"); // ofImage
    //shader.load("shader.vs","shader.fs");
    string vert = STRINGIFY(
                            uvarying vec3 p;
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
                                    vec4 texCol0 = texture2D(tex0, gl_TexCoord[0].st);
                                     gl_FragColor = texCol0;
                             }

                            );
    shader.setupShaderFromSource(GL_VERTEX_SHADER, vert);
    shader.setupShaderFromSource(GL_FRAGMENT_SHADER, frag);
    shader.linkProgram();
    
    glEnable(GL_DEPTH_TEST);
    fbo.allocate(900, 300);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    fbo.begin();
    ofPushStyle();
    ofCircle(ofRandom(900), ofRandom(900), ofRandom(10,30));
    
    ofPopStyle();
    fbo.end();
    
    ofPushMatrix();
    shader.begin();
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sample.width,sample.height, 0, GL_RGB, GL_UNSIGNED_BYTE, sample.getPixels());
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    ofRotateY((float) ofGetFrameNum() / 5);
    ofSphere(0, 0, 0, 300);
    ofPopMatrix();
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