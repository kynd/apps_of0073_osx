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
                                      if (dist < 3.0) {
                                          flag = true;
                                      }
                                  }
                                  gl_FragColor = (flag) ? vec4(1.0, 1.0, 0.0, 1.0) : vec4(0.0, 0.0, 0.0, 1.0);
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
                                      lev += abs(cos(dist * 0.1)) / float(numParticles) / dist * 100.0;
                                      if (dist < 3.0) {
                                          flag = true;
                                      }
                                  }
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
                                  float minDist = 2000.0;
                                  for (int i = 0; i < numParticles; i ++) {
                                      vec2 posSample = texture2DRect(tex1, vec2(i, 0) + vec2(0.5, 0.5)).rg;
                                      posSample.r *= float(width);
                                      posSample.g *= float(height);
                                      float dist = distance(posSample, gl_TexCoord[0].st);
                                      if (dist < minDist) {
                                          minDist = dist;
                                      }
                                      if (dist < 3.0) {
                                          flag = true;
                                      }
                                  }
                                  float lev = minDist / 200.0;
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
                                      lev += cos(dist * 0.05) / float(numParticles);
                                      if (dist < 3.0) {
                                          flag = true;
                                      }
                                  }
                                  gl_FragColor = (flag) ? vec4(1.0, 1.0, 0.0, 1.0) : vec4(lev, lev, lev, 1.0);
                              }
                              );
    
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
                                  float minDist = 2000.0;
                                  for (int i = 0; i < numParticles; i ++) {
                                      vec2 posSample = texture2DRect(tex1, vec2(i, 0) + vec2(0.5, 0.5)).rg;
                                      posSample.r *= float(width);
                                      posSample.g *= float(height);
                                      float dist = distance(posSample, gl_TexCoord[0].st);
                                      if (dist < minDist) {
                                          minDist = dist;
                                      }
                                      if (dist < 3.0) {
                                          flag = true;
                                      }
                                  }
                                  float lev = pow(cos(minDist * 0.2), 2.0);
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
                                      lev += cos(dist * 0.05) / float(numParticles);
                                      if (dist < 3.0) {
                                          flag = true;
                                      }
                                  }
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
                                  int ind0 = 0;
                                  int ind1 = 0;
                                  int ind2 = 0;
                                  float minDist = 2000.0;
                                  for (int i = 0; i < numParticles; i ++) {
                                      vec2 posSample = texture2DRect(tex1, vec2(i, 0) + vec2(0.5, 0.5)).rg;
                                      posSample.r *= float(width);
                                      posSample.g *= float(height);
                                      float dist = distance(posSample, gl_TexCoord[0].st);
                                      if (dist < minDist) {
                                          ind2 = ind1; ind1 = ind0; ind0 = i;
                                          minDist = dist;
                                      }
                                      if (dist < 3.0) {
                                          flag = true;
                                      }
                                  }
                                  float g = float(ind0) / float(numParticles);
                                  float b = float(ind1) / float(numParticles);
                                  float r = float(ind2) / float(numParticles);
                                  gl_FragColor = (flag) ? vec4(1.0, 1.0, 0.0, 1.0) : vec4(r, g, b, 1.0);
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
                                  float PI = 3.14159265;
                                  float rSum = 0.0;
                                  float gSum = 0.0;
                                  float bSum = 0.0;
                                  for (int i = 0; i < numParticles; i ++) {
                                      vec2 posSample = texture2DRect(tex1, vec2(i, 0) + vec2(0.5, 0.5)).rg;
                                      posSample.r *= float(width);
                                      posSample.g *= float(height);
                                      float dist = distance(posSample, gl_TexCoord[0].st);
                                      float angle = float(i) / float(numParticles) * PI;
                                      float adj = 1.0 / float(numParticles) / dist * 100.0;
                                      rSum += (sin(angle) + 1.0) / 2.0 * adj;
                                      gSum += (sin(angle + PI / 3.0) + 1.0) / 2.0 * adj;
                                      bSum += (sin(angle + PI / 3.0) + 1.0) / 2.0 * adj;
                                      if (dist < 3.0) {
                                          flag = true;
                                      }
                                  }
                                  gl_FragColor = (flag) ? vec4(1.0, 1.0, 0.0, 1.0) : vec4(rSum, gSum, bSum, 1.0);
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
                                  float PI = 3.14159265;
                                  vec2 pos0 = vec2(0.0);
                                  vec2 pos1 = vec2(0.0);
                                  float minDist = 2000.0;
                                  for (int i = 0; i < numParticles; i ++) {
                                      vec2 posSample = texture2DRect(tex1, vec2(i, 0) + vec2(0.5, 0.5)).rg;
                                      posSample.r *= float(width);
                                      posSample.g *= float(height);
                                      float dist = distance(posSample, gl_TexCoord[0].st);
                                      if (dist < minDist) {
                                          pos1 = pos0;
                                          pos0 = posSample;
                                          minDist = dist;
                                      }
                                      if (dist < 3.0) {
                                          flag = true;
                                      }
                                  }
                                  vec2 average = (pos0 + pos1) / 2.0;
                                  float angle = atan(average.r - gl_TexCoord[0].s, average.g- gl_TexCoord[0].t);
                                  
                                  float r = (sin(angle) + 1.0) / 2.0 / max(1.0, minDist * 0.05);
                                  float g = (sin(angle + PI / 3.0) + 1.0) / 2.0 / max(1.0, minDist * 0.05);
                                  float b = (sin(angle + PI / 3.0 * 2.0) + 1.0) / 2.0 / max(1.0, minDist * 0.05);
                                  gl_FragColor = (flag) ? vec4(1.0, 1.0, 0.0, 1.0) : vec4(r, g, b, 1.0);
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
                                  float PI = 3.14159265;
                                  float rSum = 0.0;
                                  float gSum = 0.0;
                                  float bSum = 0.0;
                                  for (int i = 0; i < numParticles; i ++) {
                                      vec2 posSample = texture2DRect(tex1, vec2(i, 0) + vec2(0.5, 0.5)).rg;
                                      posSample.r *= float(width);
                                      posSample.g *= float(height);
                                      float dist = distance(posSample, gl_TexCoord[0].st);
                                      float angle = float(i) / float(numParticles) * PI;
                                      float adj = 1.0 / float(numParticles) / dist * 100.0;
                                      rSum += (sin(angle) + 1.0) / 2.0 * adj;
                                      gSum += (sin(angle + PI / 3.0) + 1.0) / 2.0 * adj;
                                      bSum += (sin(angle + PI / 3.0) + 1.0) / 2.0 * adj;
                                      if (dist < 3.0) {
                                          flag = true;
                                      }
                                  }
                                  float r = sin(rSum * PI * 5.0);
                                  float g = sin(gSum * PI * 5.0);
                                  float b = sin(bSum * PI * 5.0);
                                  gl_FragColor = (flag) ? vec4(1.0, 1.0, 0.0, 1.0) : vec4(r, g, b, 1.0);
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
                                  float PI = 3.14159265;
                                  float r = 0.0;
                                  float g = 0.0;
                                  float b = 0.0;
                                  for (int i = 0; i < numParticles; i ++) {
                                      vec2 posSample = texture2DRect(tex1, vec2(i, 0) + vec2(0.5, 0.5)).rg;
                                      posSample.r *= float(width);
                                      posSample.g *= float(height);
                                      float dist = distance(posSample, gl_TexCoord[0].st);
                                      if (abs(posSample.r - gl_TexCoord[0].s) < 2.0) {
                                          r += 0.3;
                                          b += 0.2;
                                      }
                                      if (abs(posSample.g - gl_TexCoord[0].t) < 2.0) {
                                          g += 0.3;
                                          b += 0.2;
                                      }
                                      if (dist < 3.0) {
                                          flag = true;
                                      }
                                  }
                                  gl_FragColor = (flag) ? vec4(1.0, 1.0, 0.0, 1.0) : vec4(r, g, b, 1.0);
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
                                  float PI = 3.14159265;
                                  float r = 0.0;
                                  float g = 0.0;
                                  float b = 0.0;
                                  for (int i = 0; i < numParticles; i ++) {
                                      vec2 posSample = texture2DRect(tex1, vec2(i, 0) + vec2(0.5, 0.5)).rg;
                                      posSample.r *= float(width);
                                      posSample.g *= float(height);
                                      float dist = distance(posSample, gl_TexCoord[0].st);
                                      r += sin((posSample.r - gl_TexCoord[0].s) * 0.002 * float(i)) * 0.05;
                                      g += sin((posSample.g - gl_TexCoord[0].t) * 0.002 * float(i)) * 0.05;
                                      b += sin(r + g) * 0.2;
                                      if (dist < 3.0) {
                                          flag = true;
                                      }
                                  }
                                  gl_FragColor = (flag) ? vec4(1.0, 1.0, 0.0, 1.0) : vec4(r, g, b, 1.0);
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
                                  float PI = 3.14159265;
                                  float r = 0.0;
                                  float g = 0.0;
                                  float b = 0.0;
                                  for (int i = 0; i < numParticles; i ++) {
                                      vec2 posSample = texture2DRect(tex1, vec2(i, 0) + vec2(0.5, 0.5)).rg;
                                      posSample.r *= float(width);
                                      posSample.g *= float(height);
                                      float dist = distance(posSample, gl_TexCoord[0].st);
                                      b += sin((posSample.r - gl_TexCoord[0].s) * 0.001 * float(i)) * 0.03;
                                      g += sin((posSample.g - gl_TexCoord[0].t) * 0.001 * float(i)) * 0.03;
                                      r += sin(b + g) * 0.2;
                                      if (dist < 3.0) {
                                          flag = true;
                                      }
                                  }
                                  b = min(r, b);
                                  g = min(g, r);
                                  gl_FragColor = (flag) ? vec4(1.0, 1.0, 0.0, 1.0) : vec4(r, g, b, 1.0);
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
    cout << shaderIndex << " ";
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