#include "testApp.h"

#define STRINGIFY(A) #A
//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0, 0, 0);
    sphere = new ofVboIcosphere(150);
    
    string vert = STRINGIFY(
                            varying vec3 normal;
                            
                            void main(void)
                            {
                                normal = normalize(gl_NormalMatrix * gl_Normal).xyz;
                                gl_Position = ftransform();
                            }
                            );
    string frag = STRINGIFY(
                            
                            varying vec3 normal;
                            uniform vec3 lightDir;
                            uniform vec4 ambientColor;
                            uniform vec4 diffuseColor;
                            uniform vec4 specularColor;
                            
                            void main(void)
                            {
                                float diffuse = max(0.0, dot(normalize(normal), normalize(lightDir)));
                                vec4 flagColor = diffuse * diffuseColor;
                                flagColor += ambientColor;
                                vec3 vReflection = normalize(reflect(-normalize(lightDir), normalize(normal)));
                                float specular = pow(max(0.0, dot(normalize(normal), vReflection)), 128.0);
                                flagColor += specular * specularColor;
                                gl_FragColor = flagColor;
                            }
                            
                            );
    shaders[0].setupShaderFromSource(GL_VERTEX_SHADER, vert);
    shaders[0].setupShaderFromSource(GL_FRAGMENT_SHADER, frag);
    shaders[0].linkProgram();
    
    vert = STRINGIFY(
                     varying vec4 color;
                     
                     uniform vec3 lightDir;
                     uniform vec4 ambientColor;
                     uniform vec4 diffuseColor;
                     uniform vec4 specularColor;
                     
                     void main(void)
                     {
                         vec3 normal = normalize(gl_NormalMatrix * gl_Normal).xyz;
                         float diffuse = max(0.0, dot(normalize(normal), normalize(lightDir)));
                         vec4 vertColor = diffuse * diffuseColor;
                         vertColor += ambientColor;
                         vec3 vReflection = normalize(reflect(-normalize(lightDir), normalize(normal)));
                         float specular = pow(max(0.0, dot(normalize(normal), vReflection)), 128.0);
                         vertColor += specular * specularColor;
                         color = vertColor;
                         gl_Position = ftransform();
                     }
                     );
    frag = STRINGIFY(
                     varying vec4 color;
                     
                     void main(void)
                     {
                         gl_FragColor = color;
                     }
                     
                     );
    shaders[1].setupShaderFromSource(GL_VERTEX_SHADER, vert);
    shaders[1].setupShaderFromSource(GL_FRAGMENT_SHADER, frag);
    shaders[1].linkProgram();
    
    glEnable(GL_DEPTH_TEST);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    float lightAngle = ofGetElapsedTimef();
    float lightDir[3] = {cos(lightAngle), 0.3, sin(lightAngle)};
    float ambientColor[4] = {0.2, 0.2, 0.2, 1.0};
    float diffuseColor[4] = {0.5, 0.5, 0.5, 1.0};
    float specularColor[4] = {1.0, 1.0, 1.0, 1.0};
    
    for (int i = 0; i < 2; i ++) {
        ofPushMatrix();
        ofTranslate(ofGetWidth()/ 2 + ((i == 0) ? - 200 : 200), ofGetHeight() / 2);
        shaders[i].begin();
        shaders[i].setUniform3fv("lightDir", lightDir);
        shaders[i].setUniform4fv("ambientColor", ambientColor);
        shaders[i].setUniform4fv("diffuseColor", diffuseColor);
        shaders[i].setUniform4fv("specularColor", specularColor);
        sphere->draw();
        shaders[i].end();
        ofPopMatrix();
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