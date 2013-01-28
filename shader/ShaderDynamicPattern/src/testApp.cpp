#include "testApp.h"



#define STRINGIFY(A) #A
//--------------------------------------------------------------
void testApp::setup(){
    posFbo.allocate(NUM_PAERICLES, 1, GL_RGB32F);
    for (int i = 0; i < NUM_PAERICLES; i ++) {
        pos[i].x = ofRandom(0, ofGetWidth());
        pos[i].y = ofRandom(0, ofGetHeight());
        float speed = ofRandom(0.5, 3.0);
        float angle = ofRandom(0.0, TWO_PI);
        vec[i].x = cos(angle) * speed;
        vec[i].y = sin(angle) * speed;
    }
    ofShader* shader;
    string shaderProgram;
    //--------------------------------------------------------------
    shader = new ofShader();
    shaderProgram = STRINGIFY(
                                     uniform sampler2DRect tex0;
                                     uniform sampler2DRect tex1;
                                     uniform int numParticles;
                                     uniform int width;
                                     uniform int height;
                                     void main (void){
                                         bool flag = false;
                                         for (int i = 0; i < numParticles; i ++) {
                                             vec2 posSample = texture2DRect(tex1, vec2(i, 0) + vec2(0.5, 0.5)).rg;
                                             posSample.r *= float(width);
                                             posSample.g *= float(height);
                                             
                                             float dist = distance(posSample, gl_TexCoord[0].st);
                                             if (dist <  3.0) {
                                                 flag = true;
                                             }
                                         }
                                         gl_FragColor = (flag) ? vec4(1.0, 1.0, 0.0, 1.0) : vec4(0.0, 0.0, 0.0, 1.0) ;
                                     }
                                     );
    
    shader->setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
    shader->linkProgram();
    shaders.push_back(shader);
    
    //--------------------------------------------------------------
    
    shader = new ofShader();
    shaderProgram = STRINGIFY(
                              uniform sampler2DRect tex0;
                              uniform sampler2DRect tex1;
                              uniform int numParticles;
                              uniform int width;
                              uniform int height;
                              void main (void){
                                  bool flag = false;
                                  float maxDist = 2000.0;
                                  for (int i = 0; i < numParticles; i ++) {
                                      vec2 posSample = texture2DRect(tex1, vec2(i, 0) + vec2(0.5, 0.5)).rg;
                                      posSample.r *= float(width);
                                      posSample.g *= float(height);
                                      float dist = distance(posSample, gl_TexCoord[0].st);
                                      if (dist < maxDist) {
                                          maxDist = dist;
                                      }
                                      if (dist < 3.0) {
                                          flag = true;
                                      }
                                  }
                                  float lev = maxDist / 200.0;
                                  gl_FragColor = (flag) ? vec4(1.0, 1.0, 0.0, 1.0) : vec4(lev, lev, lev, 1.0);
                              }
                              );
        
    shader->setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
    shader->linkProgram();
    shaders.push_back(shader);
    
    //--------------------------------------------------------------
    
    shader = new ofShader();
    shaderProgram = STRINGIFY(
                              uniform sampler2DRect tex0;
                              uniform sampler2DRect tex1;
                              uniform int numParticles;
                              uniform int width;
                              uniform int height;
                              void main (void){
                                  bool flag = false;
                                  float lev = 0.0;
                                  for (int i = 0; i < numParticles; i ++) {
                                      vec2 posSample = texture2DRect(tex1, vec2(i, 0) + vec2(0.5, 0.5)).rg;
                                      posSample.r *= float(width);
                                      posSample.g *= float(height);
                                      float dist = distance(posSample, gl_TexCoord[0].st);
                                      float pow = max(0.0, 200.0 - dist) / 200.0;
                                      lev += pow * pow;
                                      if (dist < 3.0) {
                                          flag = true;
                                      }
                                  }
                                  gl_FragColor = (flag) ? vec4(1.0, 1.0, 0.0, 1.0) :
                                  (lev < 0.5 ) ? vec4(1.0, 1.0, 1.0, 1.0) : vec4(0.0, 0.0, 0.0, 1.0);
                              }
                              );
    
    shader->setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
    shader->linkProgram();
    shaders.push_back(shader);
    //--------------------------------------------------------------
    
    shaderIndex = 0;
    renderImage.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
}

//--------------------------------------------------------------
void testApp::update(){
    
    ofFloatPixels pixels;
    posFbo.readToPixels(pixels);
    for (int i = 0; i < NUM_PAERICLES; i++){
        pos[i] += vec[i];
        
        if (pos[i].x < 0) {
            vec[i].x *= -1;
        }
        if (pos[i].x > ofGetWidth()) {
            vec[i].x *= -1;
        }
        if (pos[i].y < 0) {
            vec[i].y *= -1;
        }
        if (pos[i].y > ofGetHeight()) {
            vec[i].y *= -1;
        }
        
        pixels[i * 3 + 0] = pos[i].x / ofGetWidth();
        pixels[i * 3 + 1] = pos[i].y / ofGetHeight();
    }
    
    posFbo.getTextureReference().loadData(pixels);
}

//--------------------------------------------------------------
void testApp::draw(){
    shaders[shaderIndex]->begin();
    shaders[shaderIndex]->setUniform1i("numParticles", NUM_PAERICLES);
    shaders[shaderIndex]->setUniform1i("width", ofGetWidth());
    shaders[shaderIndex]->setUniform1i("height", ofGetHeight());
    shaders[shaderIndex]->setUniformTexture("tex0", renderImage.getTextureReference() , 0 );
    shaders[shaderIndex]->setUniformTexture("tex1", posFbo.getTextureReference() , 1 );
    
    renderImage.draw(0, 0);
    shaders[shaderIndex]->end();
    
    
    //ofDrawBitmapString("Fps: " + ofToString( ofGetFrameRate()), 15,15);
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
    shaderIndex = (shaderIndex + 1) % shaders.size();
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